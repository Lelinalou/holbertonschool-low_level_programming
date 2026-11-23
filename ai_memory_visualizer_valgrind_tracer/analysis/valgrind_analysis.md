# Analyse Valgrind

Outil : Valgrind 3.26.0 (Memcheck). Programmes : `aliasing_example`, `crash_example`, `heap_example`, `stack_example`.
Références croisées : `analysis/memory_maps.md` (tâche 1).

## 0. Méthode

Les sorties analysées ont été obtenues avec `valgrind ./programme` (options par défaut). Pour une analyse complète, relancer avec :

```
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./programme
```

- `--leak-check=full` : donne la pile d'allocation de chaque fuite (absente de la sortie de `heap_example`, voir §3).
- `--track-origins=yes` : indique l'origine d'une valeur non initialisée.
- `-s` : affiche les erreurs supprimées.

Compiler avec `-g` pour obtenir les numéros de ligne. Les lignes citées ci-dessous sont celles rapportées par Valgrind.

## 1. Synthèse

| Programme | Avertissement Valgrind | Classification précise | Objet mémoire |
|---|---|---|---|
| `aliasing_example` | `Invalid read of size 4` (l. 42) | use-after-free, lecture via un alias | bloc tas de 20 o (`make_numbers`, l. 12), octet 8 |
| `aliasing_example` | `Invalid write of size 4` (l. 44) | use-after-free, écriture via un alias | même bloc, octet 12 |
| `aliasing_example` | `Invalid read of size 4` (l. 45) | use-after-free, relecture d'une écriture invalide | même bloc, octet 12 |
| `crash_example` | `Invalid write of size 4` (l. 32) puis `SIGSEGV` | déréférencement de pointeur nul (écriture) | aucun objet : adresse `0x0` |
| `crash_example` | `still reachable: 1,024 bytes in 1 blocks` | non-libération du tampon `stdout` (pas une fuite utilisateur) | tampon stdio de la libc |
| `heap_example` | `definitely lost: 6 bytes in 1 blocks` | fuite par perte de propriété (*lost ownership*) | chaîne `"Alice\0"` (`alice->name`) |
| `stack_example` | aucun | — | — |

Aucun avertissement de type `Conditional jump or move depends on uninitialised value(s)` ni `Use of uninitialised value` n'a été émis, sur aucun des quatre programmes (§5).

---

## 2. `aliasing_example`

### Contexte vérifié

- Premier `malloc` utilisateur : `make_numbers`, l. 12, appelé depuis `main` l. 30. Taille : 5 × 4 = 20 octets (« block of size 20 »).
- `free(a)` : `main`, l. 38.
- Les adresses `a=0x4a91480` et `b=0x4a91480` sont identiques : `b` est un alias de `a` (cf. schéma de `memory_maps.md` §4).
- Résumé : `2 allocs, 2 frees, 1,044 bytes` = tampon `stdout` (1 024) + bloc de 20. Le bloc est libéré exactement une fois ; **pas de fuite, pas de double free**.

### Avertissement 1 : `Invalid read of size 4`, l. 42

- **Type** : use-after-free (lecture).
- **Objet** : le bloc de 20 octets alloué en l. 12, libéré en l. 38. L'adresse `0x4a91488` est « 8 bytes inside », donc l'élément `b[2]` (2 × 4 = 8).
- **Violation de durée de vie** : la durée de vie d'un bloc du tas se termine à `free`, **pour tous les pointeurs qui le désignent**. `free(a)` a mis fin à la vie du bloc ; `b`, alias non informé de cette libération, est devenu un pointeur pendant (*dangling pointer*) et est déréférencé après. Le pointeur `b` lui-même (variable de pile de `main`) est toujours vivant : c'est sa **cible** qui est morte.

### Avertissement 2 : `Invalid write of size 4`, l. 44

- **Type** : use-after-free (écriture).
- **Objet** : même bloc, octet 12 (`b[3]`).
- **Pourquoi c'est plus grave** : une écriture dans un bloc libéré peut corrompre les métadonnées de l'allocateur ou les données d'un autre bloc qui réutiliserait cet espace. La corruption se manifeste souvent bien plus tard, loin de la cause.

### Avertissement 3 : `Invalid read of size 4`, l. 45

- **Type** : use-after-free (lecture).
- **Objet** : même bloc, même adresse `0x4a9148c` que l'écriture précédente.
- **Origine** : le `printf("wrote b[3]=%d", b[3])` relit l'élément qui vient d'être écrit. L'accès est une **lecture distincte**, d'où un contexte d'erreur distinct (Memcheck regroupe les erreurs par pile d'appels et ligne : `3 errors from 3 contexts`).
- La valeur `1234` relue est cohérente, mais cette cohérence est **sans valeur** : on lit une mémoire qui n'appartient plus au programme.

### Observations complémentaires

- `a` est lui aussi pendant après `free(a)` ; le programme n'affiche que « b dangling », ce qui est incomplet.
- `b[2]` affiche encore `22` après la libération. Sous Valgrind, `malloc`/`free` sont remplacés et les blocs libérés sont mis en quarantaine, sans réutilisation immédiate : la valeur subsiste. **Ce n'est pas une garantie du langage** ; ce comportement n'a pas été vérifié hors Valgrind dans cette analyse.
- Correction possible (non requise) : mettre `a = NULL; b = NULL;` après `free`, ou ne garder qu'un propriétaire du bloc.

---

## 3. `heap_example`

### Avertissement : `definitely lost: 6 bytes in 1 blocks`

- **Type** : fuite mémoire due à une perte de propriété (*memory leak due to lost ownership*).
- **Objet** : la chaîne `"Alice\0"` (5 caractères + `\0` = 6 octets), allouée dans `person_new` par `malloc(len + 1)` et pointée par `alice->name`.
- **Violation** : `Person` est propriétaire de `name`. `person_free_partial(alice)` libère la structure par `free(p)` **sans libérer `p->name`**. Le seul pointeur vers la chaîne se trouvait dans la structure qui vient d'être libérée : plus aucune référence valide n'existe, le bloc est irrécupérable.
- **Pourquoi `definitely lost` et non `indirectly lost`** : Valgrind qualifie d'*indirectly lost* un bloc atteignable uniquement depuis un autre bloc perdu. Ici le bloc propriétaire (`Person`) a été **libéré**, pas perdu ; la chaîne n'a donc plus aucun chemin d'accès, elle est directement perdue. Si `alice` avait elle-même fui, on aurait vu `definitely lost` (struct) + `indirectly lost` (chaîne).

### Vérification par les comptes

`5 allocs, 4 frees, 1,066 bytes` :

| Allocation | Taille |
|---|---|
| tampon `stdout` (libéré à la sortie par la libc) | 1 024 |
| `Person` alice | 16 (8 pour le pointeur + 4 pour `age` + 4 de padding) |
| `"Alice\0"` | 6 |
| `Person` bob | 16 |
| `"Bob\0"` | 4 |
| **Total** | **1 066** ✓ |

Libérations : tampon `stdout`, `bob->name`, `bob`, `alice` = 4. Écart : 5 − 4 = 1 bloc, de 6 octets : exactement `alice->name`. Cela confirme `memory_maps.md` §3 (`bob` correctement libéré, fuite sur `alice->name` uniquement).

### Points d'attention

- `ERROR SUMMARY: 0 errors` est **trompeur** : sans `--leak-check=full`, les fuites ne sont pas comptées comme des erreurs, et aucune pile d'allocation n'est affichée. Le bug existe malgré le « 0 error ». Relancer avec `--leak-check=full` doit afficher `at malloc ... by person_new ... by main`.
- Aucun `Invalid read/write` : les accès à `alice->name` (affichage) ont lieu avant les `free`, donc pendant la durée de vie.
- `alice` (variable de pile) pointe vers un `Person` libéré après `person_free_partial`, mais n'est plus déréférencé : pointeur pendant sans accès, donc non signalé.

---

## 4. `crash_example`

### Avertissement 1 : `Invalid write of size 4`, l. 32, `Address 0x0 is not stack'd, malloc'd or (recently) free'd`

- **Type** : déréférencement de pointeur nul (*NULL pointer dereference*), en écriture (`nums[0] = 42`).
- **Objet** : aucun. Le message « not stack'd, malloc'd or (recently) free'd » signifie que l'adresse `0x0` n'appartient à aucun objet connu (ni pile, ni tas actif, ni bloc récemment libéré). C'est la différence avec un use-after-free, où Valgrind nomme le bloc libéré.
- **Cause** : `n = 0` → `allocate_numbers` retourne `NULL` à cause de la garde `n <= 0`, **sans jamais appeler `malloc`**. `main` n'a pas testé `nums`. Ce n'est pas un échec de `malloc` (cf. `memory_maps.md` §5).
- **Durée de vie** : aucun objet n'a existé ; `nums` (pile de `main`) est vivant mais ne désigne rien.

### Avertissement 2 : `Process terminating with default action of signal 11 (SIGSEGV)`, `Access not within mapped region at address 0x0`

- **Type** : conséquence du précédent, pas une seconde erreur. C'est la même instruction (`0x400128A`) : Memcheck signale d'abord l'accès invalide, puis le noyau tue le processus. `ERROR SUMMARY: 1 errors from 1 contexts` le confirme. Le shell affiche « Erreur de segmentation » (code de sortie 139 = 128 + 11).
- Le conseil sur `--main-stacksize` est générique et **sans rapport** ici : l'adresse fautive est `0x0`, pas un dépassement de pile.

### Avertissement 3 : `still reachable: 1,024 bytes in 1 blocks` (`1 allocs, 0 frees`)

- **Type** : bloc encore accessible à la sortie, **pas une fuite** (`definitely lost: 0`, `indirectly lost: 0`, `possibly lost: 0`).
- **Objet** : le tampon de 1 024 octets de `stdout`, alloué par la libc lors du premier `printf`. Aucun `malloc` du programme n'a eu lieu.
- **Pourquoi non libéré** : en sortie normale (`stack_example` : `1 allocs, 1 frees`), la libc libère ce tampon. Ici le processus est tué par signal avant ce nettoyage ; le tampon reste référencé par la structure `stdout` de la libc, d'où « still reachable ».
- `free(nums)` n'est jamais exécuté (l. 36), mais ce n'est pas la cause : `free(NULL)` serait sans effet.

---

## 5. `stack_example` et mémoire non initialisée

### `stack_example` : aucune erreur (`0 errors`, `1 allocs, 1 frees` = tampon `stdout`)

Les adresses réelles confirment le modèle de `memory_maps.md` §2 :

- **La pile croît vers le bas** : `&marker` vaut `…fb14`, `…ae4`, `…ab4`, `…a84` pour les profondeurs 0 à 3, soit −0x30 (48 octets) par niveau.
- **`p_local` est un alias de `&local_int`** dans le même frame : valeurs identiques à chaque ligne (par exemple `0x1ffefffac4` en profondeur 0). Pas de problème : l'alias vit aussi longtemps que sa cible.
- **Même profondeur, même emplacement** : pour chaque profondeur, `&local_int` à `enter` est égal à celui de `exit` (par exemple `…a34` pour `[enter]` et `[exit]` à la profondeur 3). Ce sont deux appels différents de `dump_frame`, dont les frames, créés puis détruits l'un après l'autre, occupent la même zone.
- **`&marker` identique à `enter` et `exit`** : c'est la même variable, vivante pendant tout l'appel de `walk_stack(d)`, valeur inchangée (30 à la profondeur 3, etc.).
- **Réutilisation de zones** : le frame de `dump_frame` appelé depuis `walk_stack(0)` (`&local_int` = `…ac4`) est au même niveau d'appel que `walk_stack(1)` (`&marker` = `…ae4`). Les deux régions se recouvrent dans l'espace mais jamais dans le temps : leurs durées de vie sont disjointes.
- `local_buf` se trouve 12 octets au-dessus de `local_int` (`…ad0` contre `…ac4`) : les deux variables sont dans le même frame ; l'ordre en mémoire est choisi par le compilateur et ne suit pas l'ordre de déclaration.

### Mémoire non initialisée

Aucun avertissement d'usage de valeur non initialisée dans les quatre sorties. Cas qui pouvait prêter à confusion : `local_buf[16]` dans `dump_frame` n'est initialisé que sur 2 octets (`[0]` et `[1]`), mais le programme ne lit que `local_buf[0]` (`%c`) ; aucun accès à un octet non écrit, donc aucun signalement.

---

## 6. Vérification des explications d'IA

Les explications de la tâche 1 (`memory_maps.md`) avaient été produites avec l'aide d'une IA (Claude) à partir du code seul. Les sorties réelles de Valgrind permettent de les vérifier.

| # | Affirmation de l'IA | Verdict | Vérification |
|---|---|---|---|
| 1 | `aliasing_example` produit **deux** erreurs : lecture de `b[2]`, écriture de `b[3]` | **Incomplète** | Valgrind : `3 errors from 3 contexts`. Le `printf("wrote b[3]=%d", b[3])` (l. 45) relit l'élément écrit : troisième accès invalide |
| 2 | `crash_example` : « aucune fuite : rien n'a été alloué » | **Partiellement incorrecte** | Valgrind : `1 allocs, 0 frees`, `still reachable: 1,024 bytes`. Rien n'est alloué *par le programme*, mais la libc a alloué le tampon `stdout`. Ce n'est pas une fuite (`definitely lost: 0`), mais « rien alloué » était faux |
| 3 | `heap_example` : fuite de 6 octets sur `alice->name`, `bob` correctement libéré | **Correcte** | `definitely lost: 6 bytes in 1 blocks`, `5 allocs / 4 frees`, somme 1 066 = 1 024 + 16 + 6 + 16 + 4 |
| 4 | `stack_example` : `&local_int` identique à `enter` et `exit` à profondeur égale | **Correcte** | Identique aux quatre profondeurs |
| 5 | `b[2]` lu après `free` pourrait différer de 22 hors Valgrind (métadonnées glibc) | **Non vérifiée** | Sous Valgrind, `22` est bien affiché (blocs en quarantaine). L'affirmation concerne l'exécution sans Valgrind, non testée ici |

### Cas détaillé : l'erreur n°1 (IA incomplète)

- **Raisonnement erroné** : l'IA a compté les erreurs en comptant les **instructions décrites** dans le récit (« lecture de `b[2]` », « écriture de `b[3]` »), mais pas les **accès mémoire réels** : l'argument `b[3]` du `printf` est évalué avec une lecture supplémentaire.
- **Comment je l'ai détecté** : comparaison entre `ERROR SUMMARY: 3 errors from 3 contexts` et les deux erreurs annoncées, puis lecture de la troisième trace (`aliasing_example.c:45`, `12 bytes inside a block of size 20 free'd`, même adresse que l'écriture).
- **Correction** : `memory_maps.md` §4 a été mis à jour (trois accès invalides, explication de la relecture).
- **Leçon** : pour prédire Valgrind, énumérer chaque lecture et écriture d'un bloc libéré, y compris dans les arguments de `printf`, et non les « étapes » du récit.

### Cas détaillé : l'erreur n°2 (IA partiellement incorrecte)

- **Raisonnement erroné** : l'IA a confondu « le programme n'alloue rien » et « le tas est vide ». La libc alloue elle-même le tampon de `stdout` (1 024 o) au premier `printf` ; il apparaît dans tous les résumés (`aliasing`: 1 044 = 1 024 + 20 ; `heap`: 1 066 ; `stack`: 1 024).
- **Comment je l'ai détecté** : `1 allocs, 0 frees, 1,024 bytes allocated` alors que `allocate_numbers(0)` retourne avant `malloc`. Le comparatif avec `stack_example` (`1 allocs, 1 frees`) montre que le bloc est libéré en sortie normale et non en cas de `SIGSEGV`.
- **Correction** : `memory_maps.md` §5 mis à jour.
