# Rapport de crash

Programmes couverts : `crash_example` (le seul qui plante), puis `aliasing_example`, `heap_example` et `stack_example`, pour établir pour chacun s'il peut ou non planter, et pourquoi.

Références : `analysis/memory_maps.md` (tâche 1), `analysis/valgrind_analysis.md` (tâche 2).


## 0. Vue d'ensemble

| Programme | Plante ? | Accès invalide ? | Catégorie de comportement | Zone mémoire |
|---|---|---|---|---|
| `crash_example` | **Oui**, `SIGSEGV` | écriture via un pointeur nul (l. 32) | comportement indéfini : déréférencement de pointeur nul | ni pile ni tas pour la cible (aucun objet) ; le pointeur `nums` est sur la pile |
| `aliasing_example` | Non (crash **latent**) | lecture et écriture après `free` (l. 42, 44, 45) | comportement indéfini : accès à un objet hors de sa durée de vie | tas (cible) ; pile (pointeurs `a`, `b`) |
| `heap_example` | Non | aucun | comportement défini : fuite de ressource | tas |
| `stack_example` | Non | aucun | comportement défini | pile |

---

## 1. `crash_example`

### 1.1 Description du crash

Le programme se termine sur le signal `SIGSEGV` pendant l'exécution de l'instruction correspondant à `nums[0] = 42;` (ligne 32). Les deux lignes suivantes (`printf` de `nums[0]`, `free(nums)`) ne sont jamais exécutées.

Confirmation : Valgrind rapporte `Invalid write of size 4 ... Address 0x0 is not stack'd, malloc'd or (recently) free'd` puis `Process terminating with default action of signal 11 (SIGSEGV)`, et le shell affiche « Erreur de segmentation ». Ces sorties ne font que corroborer la déduction suivante.

### 1.2 Chaîne causale complète

| Étape | Ligne | Ce qui se passe | Zone mémoire |
|---|---|---|---|
| 1 | 25 | `n` est initialisé à `0` | pile (frame de `main`) |
| 2 | 30 | `main` appelle `allocate_numbers(0)` | |
| 3 | 9–10 | la garde `if (n <= 0) return NULL;` est vraie (0 ≤ 0) : la fonction retourne `NULL` **avant** l'appel à `malloc` (l. 12) | aucun bloc n'est créé sur le tas |
| 4 | 30 | la valeur de retour `NULL` est copiée dans `nums` | pile (frame de `main`) |
| 5 | 32 | `nums[0] = 42;` équivaut à `*(nums + 0) = 42;` : le programme déréférence `NULL` pour y écrire | accès à l'adresse virtuelle 0 |
| 6 | — | l'adresse 0 n'est pas mappée : le processeur lève un défaut de page, le noyau envoie `SIGSEGV`, l'action par défaut termine le processus | |

### 1.3 Cause racine

**Le code appelant (`main`) ne vérifie pas la valeur de retour de `allocate_numbers`** avant de l'utiliser comme adresse d'un objet.

Facteur aggravant dans la conception : `allocate_numbers` retourne `NULL` dans **deux situations indiscernables** pour l'appelant : paramètre invalide (`n <= 0`) et échec de `malloc`. Aucun code d'erreur ne distingue ces cas, ce qui rend la vérification d'autant plus indispensable et le diagnostic plus difficile.

Cause immédiate (distincte de la cause racine) : l'écriture à travers un pointeur nul, ligne 32.

### 1.4 Pourquoi l'accès est invalide

- **Au niveau du langage.** `NULL` est par définition un pointeur qui ne désigne aucun objet. La norme C11 (§6.5.3.2, al. 4) précise que le comportement de l'opérateur unaire `*` est **indéfini** lorsque l'opérande est une valeur de pointeur invalide, ce qui inclut le pointeur nul. Or `nums[0]` est défini comme `*(nums + 0)`. L'écriture est donc un **comportement indéfini (UB) de la catégorie « déréférencement de pointeur nul »**.
- **Au niveau de la mémoire.** Aucun objet n'existe à l'adresse visée : `malloc` n'a jamais été appelé (étape 3), donc ni tas ni pile n'est impliqué comme **cible**. Seule la variable `nums` (le pointeur lui-même) est sur la pile, et sa valeur est correctement lue et écrite. Ce n'est pas la pile qui est mal utilisée, c'est la valeur qu'elle contient.
- **Au niveau du système.** Sur Linux, la page contenant l'adresse 0 est volontairement laissée non mappée (c'est ce qui permet de détecter ce type d'erreur). L'écriture déclenche le défaut de page, et c'est cette configuration du système qui transforme l'UB en `SIGSEGV`.

### 1.5 Précision sur la notion de « crash déterministe »

Le message du programme (« deterministic NULL dereference ») est vrai **sur cette plate-forme**, mais ce n'est pas une garantie du langage. L'UB signifie que la norme n'impose aucun comportement : sur un système où l'adresse 0 est mappée (certains microcontrôleurs), l'écriture réussirait silencieusement ; un compilateur peut aussi, en présence d'un UB, supprimer ou réordonner du code. Le plantage observé est une **conséquence possible** de l'UB, non sa définition.

### 1.6 Pile ou tas ?

| Élément | Zone | Rôle dans le crash |
|---|---|---|
| `n`, `nums` | pile (`main`) | variables saines ; `nums` contient `NULL` |
| `arr`, `i` | pile (`allocate_numbers`) | morts au `return` ; `arr` jamais assigné à un bloc |
| bloc de `malloc` | **inexistant** | cause indirecte : son absence est la raison du `NULL` |
| adresse `0x0` | aucune | cible de l'accès invalide |

Verdict : **ni pile ni tas n'est corrompu ; le pointeur sur la pile ne désigne aucun objet du tas.**

### 1.7 Correction suggérée (optionnelle, à titre indicatif)

Non appliquée au code. Vérifier le retour avant tout accès :

```c
nums = allocate_numbers(n);
if (!nums)
{
    fprintf(stderr, "allocation failed or invalid n\n");
    return 1;
}
```

Option de conception : faire retourner un code d'erreur distinct (ou une valeur de sortie par paramètre) pour séparer « `n` invalide » de « mémoire insuffisante ». Ne pas remplacer `n = 0` par une autre valeur est une rustine, pas une correction : la vérification de `NULL` reste nécessaire dans tous les cas.

---

## 2. `aliasing_example` (crash latent)

### 2.1 Description

Le programme **ne plante pas** dans l'exécution observée (il affiche `wrote b[3]=1234` et se termine). Il contient pourtant trois accès invalides (l. 42, 44, 45) qui ne planteront pas toujours de la même façon.

### 2.2 Chaîne causale

| Étape | Ligne | Ce qui se passe |
|---|---|---|
| 1 | 12, 30 | `make_numbers(5)` alloue un bloc de 20 octets sur le tas ; son adresse est copiée dans `a` (pile de `main`) |
| 2 | 34 | `b = a` : `a` et `b` désignent le même bloc (alias) |
| 3 | 38 | `free(a)` met fin à la durée de vie du bloc |
| 4 | 42 | `b[2]` : lecture hors durée de vie |
| 5 | 44 | `b[3] = 1234` : écriture hors durée de vie |
| 6 | 45 | `b[3]` relu hors durée de vie |

### 2.3 Cause racine

Après `free(a)`, **tous les alias** (`a` et `b`) désignent un objet dont la durée de vie est terminée. Le programme continue pourtant d'utiliser `b`. La propriété du bloc n'est pas clairement attribuée : un pointeur libère, l'autre ignore l'événement.

### 2.4 Pourquoi c'est invalide (catégorie d'UB)

C11 §6.2.4, al. 2 : la valeur d'un pointeur devient **indéterminée** lorsque l'objet qu'il désigne atteint la fin de sa durée de vie. L'annexe J.2 range parmi les comportements indéfinis le fait de référencer un objet hors de sa durée de vie et d'utiliser la valeur d'un pointeur vers un tel objet.

Catégorie : **accès à un objet hors de sa durée de vie (use-after-free)**.

Remarque : au sens strict de la norme, même `printf("%p", (void *)b)` après `free` (l. 40) utilise une valeur de pointeur indéterminée. En pratique cette lecture ne cause aucun dommage, mais le message « b=... (dangling) » du programme décrit déjà un usage non défini.

### 2.5 Pourquoi l'absence de crash ne prouve rien

Le crash est **possible mais non garanti** : tout dépend de ce que l'allocateur fait de ce bloc ensuite.

- Lecture (l. 42, 45) : renvoie des octets qui peuvent avoir été modifiés par l'allocateur ou par une nouvelle allocation du même espace.
- Écriture (l. 44) : si ce bloc est réattribué plus tard par `malloc`, l'écriture a modifié des données d'un autre objet, et le plantage ou la corruption survient loin de la cause. Les allocateurs courants stockent leurs métadonnées dans les premiers octets d'un bloc libéré (détail dépendant de l'implémentation) ; une écriture à l'intérieur peut donc corrompre la gestion du tas.

La valeur `22` relue sous Valgrind est un artefact de l'outil (blocs libérés mis en quarantaine), pas un comportement défini.

### 2.6 Correction suggérée (optionnelle)

Avoir un seul propriétaire du bloc ; après `free`, mettre `a = NULL; b = NULL;` ; ne plus déréférencer l'alias.

---

## 3. `heap_example` (pas de crash)

### 3.1 Description

Le programme se termine normalement. Aucun accès invalide n'a lieu : tous les accès à `alice`, `alice->name`, `bob`, `bob->name` (l. 63–64) précèdent les `free` (l. 66–69).

### 3.2 Défaut et chaîne causale

| Étape | Ligne | Ce qui se passe |
|---|---|---|
| 1 | 14, 21 | `person_new` alloue deux blocs : la structure `Person` et la chaîne `name` |
| 2 | 41, 69 | `person_free_partial(alice)` fait `free(p)` mais pas `free(p->name)` |
| 3 | — | le seul pointeur vers `"Alice\0"` était dans la structure libérée : le bloc de 6 octets n'est plus atteignable |

### 3.3 Catégorie

**Ce n'est pas un comportement indéfini.** Ne pas libérer un bloc est défini par la norme (la mémoire est rendue au système à la fin du processus) : c'est une **fuite de ressource par perte de propriété**, sans accès invalide, donc **sans crash**. Elle pénalise un programme qui tourne longtemps ou alloue en boucle, jusqu'à l'épuisement de la mémoire.

### 3.4 Note de latence

La même fonction est appelée dans la branche d'erreur de `main` (l. 56–59) : le défaut s'y reproduirait. Là encore, il n'en résulterait qu'une fuite, pas un crash.

### 3.5 Correction suggérée (optionnelle)

Dans `person_free_partial`, libérer `p->name` avant `p`. L'ordre est important : `free(p)` d'abord rendrait `p->name` illisible.

---

## 4. `stack_example` (pas de crash)

Aucun accès invalide, aucun UB, pas de crash. Ce programme sert de contrôle :

- Chaque accès concerne une variable automatique **pendant sa durée de vie** (`marker` pendant `walk_stack(d)`, `local_int` / `local_buf` / `p_local` pendant `dump_frame`).
- `p_local` est un alias de `&local_int` dans le même frame : les deux vivent exactement aussi longtemps.
- `local_buf[16]` n'est que partiellement initialisé (deux octets), mais seul `local_buf[0]` est lu.
- La profondeur de récursion est de 4 niveaux (0 à 3), très loin d'un dépassement de pile.

**Ce qui le ferait planter (non présent dans le code).** Retourner un pointeur vers `local_int` depuis `dump_frame` (pointeur vers un objet automatique dont la durée de vie est terminée, UB selon C11 §6.2.4) ou récurser sans condition d'arrêt (dépassement de pile). Ce contraste montre que la pile est elle aussi sujette aux erreurs de durée de vie.

---

## 5. Critique des explications d'IA

Les explications suivantes ont été produites par un assistant IA (Claude) lors des tâches 1 et 2, ou sont des affirmations typiques qu'un assistant propose pour un `SIGSEGV`. Chacune est confrontée au code et à la norme.

| # | Explication d'IA | Statut | Vérification et raison |
|---|---|---|---|
| 1 | « `crash_example` : aucune allocation, donc aucune fuite » | **Incorrecte** | Le programme n'alloue rien, mais la libc alloue le tampon de `stdout` (1 024 o) au premier `printf` : c'est ce que montre `still reachable: 1,024 bytes`. Ce n'est pas une fuite, mais « rien alloué » était faux. Déjà corrigé dans `valgrind_analysis.md` |
| 2 | « `aliasing_example` produit deux erreurs » | **Incomplète** | Il y en a trois : l'argument `b[3]` du `printf` (l. 45) est une lecture supplémentaire. Raisonnement par « étapes du récit » au lieu d'énumérer chaque accès |
| 3 | « Le `NULL` vient d'un échec de `malloc` » (hypothèse fréquente) | **Incorrecte** | `malloc` n'est pas appelé : la garde `n <= 0` retourne avant. L'indice décisif est `n = 0`, visible dans le code |
| 4 | « Le crash vient de `free(nums)` » (hypothèse fréquente) | **Incorrecte** | `free(NULL)` est défini et sans effet (C11 §7.22.3.3). De plus la ligne 36 n'est jamais atteinte : le crash a lieu ligne 32 |
| 5 | « Le crash est un dépassement de pile » (suggéré par le message générique de Valgrind sur `--main-stacksize`) | **Incorrecte / hors sujet** | L'adresse fautive est `0x0`, pas une adresse proche de la pile ; le message est conditionnel (« if you believe… ») et générique |
| 6 | « Le crash est causé par une corruption du tas » | **Spéculative** | Aucun bloc du tas n'est impliqué ; le tas est vide côté utilisateur |
| 7 | « `NULL` est un échec d'allocation, donc le programme manque de mémoire » | **Incorrecte** | `n = 0` suffit à produire `NULL` ; aucune hypothèse sur la mémoire disponible n'est nécessaire |
| 8 | « Le programme plante toujours » / « le crash est garanti » | **Trompeuse** | Le plantage dépend du système (adresse 0 non mappée). La norme ne l'exige pas, c'est un UB (§1.5) |
| 9 | « Correction : initialiser `n` à une valeur positive » | **Rustine** | Cache le symptôme ; la vérification de `NULL` reste nécessaire pour `malloc` (§1.7) |
| 10 | « Une correction correcte : tester `nums` avant l'utilisation » | **Correcte** | Supprime la cause racine et est couverte par la norme |
| 11 | « Après `free`, `b[2]` peut valoir autre chose que 22 hors Valgrind » | **Plausible, non vérifiée** | Cohérent avec le comportement des allocateurs, mais dépend de l'implémentation et n'a pas été testé ; la conclusion de ce rapport n'en dépend pas |

### Lecture critique générale

Les erreurs d'IA relevées suivent trois schémas :

1. **Raisonner sur le récit, pas sur chaque accès** (#2) : on compte les « étapes » au lieu des lectures/écritures réelles.
2. **Confondre « pas de mon fait » avec « inexistant »** (#1) : la libc alloue elle aussi.
3. **Proposer une cause plausible par défaut** (#3, #5, #6, #7) au lieu de la déduire du code. Ces hypothèses sont réfutables par une lecture attentive : `n = 0` et le `return NULL` ligne 10 écartent à eux seuls l'échec de `malloc`, le dépassement de pile et la corruption du tas.

### Méthode de vérification utilisée

Pour chaque affirmation : (1) la rattacher à une ligne précise du code, (2) vérifier la durée de vie de l'objet concerné dans `memory_maps.md`, (3) citer la règle de la norme qui rend l'accès défini ou indéfini, (4) n'utiliser Valgrind que pour corroborer.


