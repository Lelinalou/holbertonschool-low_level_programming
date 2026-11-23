# Cartes mémoire : pile, tas, aliasing, crash

Analyse de quatre programmes C : `stack_example`, `heap_example`, `aliasing_example`, `crash_example`.
Les sorties Valgrind citées sont celles **attendues d'après le code** ; remplacez-les par vos sorties réelles (`valgrind --leak-check=full --track-origins=yes ./prog`) avant de rendre.

## 1. Rappel : pile vs tas

| Critère | Pile (stack) | Tas (heap) |
|---|---|---|
| Contenu | variables locales, paramètres, adresses de retour | blocs obtenus par `malloc` |
| Allocation | automatique à l'entrée de la fonction | explicite (`malloc`) |
| Libération | automatique au `return` | explicite (`free`) |
| Durée de vie | celle de la fonction (de son frame) | de `malloc` jusqu'à `free` |
| Croissance (x86-64) | vers les adresses basses | vers les adresses hautes (en général) |
| Erreurs typiques | retour d'un pointeur vers un local, débordement | fuite, use-after-free, double free |

Point clé : **un pointeur est une variable de pile (ou globale) ; le bloc qu'il désigne est sur le tas.** Le pointeur et sa cible n'ont pas la même durée de vie.

---

## 2. `stack_example` : récursion et frames

Appels : `main` → `walk_stack(0,3)` → `walk_stack(1,3)` → `walk_stack(2,3)` → `walk_stack(3,3)`. Chaque `walk_stack` appelle `dump_frame("enter", d)` puis, au retour de la récursion, `dump_frame("exit", d)`.

### Variables et durées de vie

| Variable | Zone | Naît | Meurt |
|---|---|---|---|
| `marker` (de `walk_stack(d)`) | pile, frame de `walk_stack(d)` | entrée de `walk_stack(d)` | `return` de `walk_stack(d)` |
| `local_int`, `local_buf[16]`, `p_local` (de `dump_frame`) | pile, frame de `dump_frame` | entrée de `dump_frame` | `return` de `dump_frame` |

### Schéma de la pile (adresses décroissantes vers le bas)

```
adresses hautes
┌──────────────────────────┐
│ main                      │
├──────────────────────────┤
│ walk_stack(0)  marker=0   │
├──────────────────────────┤
│ walk_stack(1)  marker=10  │
├──────────────────────────┤
│ walk_stack(2)  marker=20  │
├──────────────────────────┤
│ walk_stack(3)  marker=30  │
├──────────────────────────┤
│ dump_frame (éphémère)     │  ← local_int, local_buf, p_local
└──────────────────────────┘
adresses basses
```

### Observations

- `&marker` diminue quand `depth` augmente : chaque appel empile un nouveau frame plus bas.
- `p_local` est un **alias** de `&local_int`, dans le même frame : les deux adresses affichées sont identiques. Aucun risque, car les deux vivent aussi longtemps.
- `dump_frame("enter", d)` et `dump_frame("exit", d)` affichent **les mêmes adresses** pour `&local_int` : à profondeur d'appel identique, le frame de `dump_frame` est recréé au même endroit. Ce sont deux variables différentes (la première est morte) qui réutilisent le même emplacement.
- `&marker` est identique à l'entrée et à la sortie d'un même `walk_stack(d)` : c'est la même variable, vivante pendant tout l'appel, valeur inchangée.
- Au retour de `walk_stack(3)`, son frame est libéré ; les `dump_frame("exit", 2)` suivants réutilisent cette zone.

---

## 3. `heap_example` : allocations et fuite délibérée

### Schéma (64 bits)

```
PILE (main)                 TAS
alice ─────────────────▶ [Person#1 : name ─▶ "Alice\0" (6 o) | age=30]   (16 o avec padding)
bob   ─────────────────▶ [Person#2 : name ─▶ "Bob\0"   (4 o) | age=41]
```

Quatre `malloc` : deux `Person`, deux chaînes.

### Séquence de libération

| Étape | Effet |
|---|---|
| `free(bob->name)` | libère `"Bob"` |
| `free(bob)` | libère `Person#2` (l'ordre est correct : le champ avant la structure) |
| `person_free_partial(alice)` | libère **seulement** `Person#1` |

### Bug : fuite de `alice->name`

`person_free_partial` fait `free(p)` sans `free(p->name)`. Après cet appel, la seule référence vers `"Alice\0"` était le champ `name` de la structure qui vient d'être libérée : plus aucun pointeur valide ne désigne ce bloc de 6 octets, il est donc **définitivement perdu**.

Sortie Valgrind attendue :

```
6 bytes in 1 blocks are definitely lost in loss record 1 of 1
   at malloc
   by person_new (heap_example.c)
   by main
LEAK SUMMARY: definitely lost: 6 bytes in 1 blocks
```

Correction : dans `person_free_partial`, faire `free(p->name); free(p);`.

---

## 4. `aliasing_example` : alias et use-after-free

### Chronologie

| Moment | État |
|---|---|
| `make_numbers(5)` | `arr` (pile, frame de `make_numbers`) reçoit l'adresse d'un bloc de 20 octets sur le tas (5 × 4) |
| `return arr` | la **valeur** de `arr` est copiée dans `a` (pile, frame de `main`). `arr` meurt ; le bloc, lui, survit |
| `b = a` | `a` et `b` contiennent la même adresse : **alias** du même bloc |
| `free(a)` | le bloc est libéré. `a` **et** `b` deviennent pendants (`a` n'est pas mis à `NULL`) |
| `b[2]` | lecture dans un bloc libéré : comportement indéfini |
| `b[3] = 1234` | écriture dans un bloc libéré : comportement indéfini |

### Schéma

```
Avant free                          Après free(a)
PILE (main)        TAS              PILE (main)        TAS
a ──┐                               a ──┐
    ├──▶ [0|11|22|33|44]  (20 o)        ├──▶ [bloc LIBÉRÉ]  (20 o)
b ──┘                               b ──┘
```

### Durées de vie

- `n`, `a`, `b` : pile de `main`, jusqu'au `return` de `main`.
- `i`, `arr` : pile de `make_numbers`, jusqu'à son `return`.
- Bloc de 20 octets : de `malloc` (dans `make_numbers`) à `free(a)` (dans `main`). Il a survécu à `make_numbers` précisément parce qu'il est sur le tas.

### Sortie Valgrind attendue

```
Invalid read of size 4
   at main (aliasing_example.c)       ← b[2]
 Address 0x... is 8 bytes inside a block of size 20 free'd
   at free ... by main
 Block was alloc'd at malloc ... by make_numbers ... by main

Invalid write of size 4
   at main (aliasing_example.c)       ← b[3] = 1234
 Address 0x... is 12 bytes inside a block of size 20 free'd
```

Décalages : `b[2]` = 2 × 4 = octet 8 ; `b[3]` = 3 × 4 = octet 12. Aucune fuite : le bloc a bien été libéré, une seule fois.

---

## 5. `crash_example` : déréférencement de NULL

### Chronologie

| Moment | État |
|---|---|
| `n = 0` | variable de pile de `main` |
| `allocate_numbers(0)` | le test `n <= 0` retourne `NULL` **avant tout `malloc`** : aucun bloc sur le tas |
| `nums = NULL` | `nums` (pile) ne désigne rien |
| `nums[0] = 42` | écriture à l'adresse `0x0` → `SIGSEGV` |
| `free(nums)` | **jamais atteint** |

Le `NULL` ne vient donc pas d'un échec de `malloc` : c'est la garde `n <= 0` qui l'a produit. L'erreur est l'absence de test `if (!nums)` dans `main`.

Sortie Valgrind attendue :

```
Invalid write of size 4
   at main (crash_example.c)
 Address 0x0 is not stack'd, malloc'd or (recently) free'd
Process terminating with default action of signal 11 (SIGSEGV)
```

Aucune fuite : rien n'a été alloué.

---

## 6. Cas documenté : explication d'IA incorrecte

> **À compléter avec votre cas réel.** La consigne demande un exemple vécu ; recopiez ci-dessous la réponse exacte de l'IA que vous avez obtenue. Le cas suivant est le plus probable sur ces programmes ; ne le conservez que s'il correspond à ce que l'IA vous a réellement dit.

### Affirmation de l'IA (à remplacer par la citation exacte)

« Dans `aliasing_example`, après `free(a)`, `b[2]` vaut toujours 22 puisque `free` n'efface pas la mémoire ; le seul problème est que Valgrind le signale. Le programme est donc "correct en pratique". »

### Pourquoi c'est faux ou trompeur

1. **Comportement indéfini, pas « correct en pratique ».** Lire ou écrire un bloc libéré n'a aucune garantie, quelle que soit la valeur observée.
2. **La valeur 22 n'est pas garantie.** Avec glibc, un bloc de 20 octets libéré va dans le tcache et ses 16 premiers octets sont réutilisés comme métadonnées (pointeur `next` à l'octet 0, clé à l'octet 8). `b[2]` (octets 8 à 11) se trouve précisément sur cette clé : la valeur lue peut donc différer de 22 hors Valgrind. Sous Valgrind, `malloc` est remplacé, donc la valeur reste souvent 22 : les deux exécutions ne sont pas comparables.
3. **L'écriture est plus grave que la lecture.** `b[3] = 1234` écrit sur la zone de métadonnées (octets 12 à 15) : elle peut corrompre la liste libre de l'allocateur et provoquer un plantage bien plus tard, loin de la cause.
4. **L'explication omettait `a`.** `a` est aussi pendant après `free(a)`. Le message « b dangling » du programme est trompeur par omission.

### Correction

- Vérifier : exécuter hors Valgrind, comparer la valeur de `b[2]` avant et après `free`, puis relancer sous Valgrind.
- Rectifier le modèle mental : `free` ne détruit pas les pointeurs, il rend le bloc à l'allocateur ; **tous les alias** deviennent invalides en même temps.
- Bonne pratique : `a = NULL; b = NULL;` après `free`, et ne conserver qu'un seul propriétaire du bloc.

### Variante si l'IA s'est trompée ailleurs

| Programme | Erreur fréquente | Réalité |
|---|---|---|
| `crash_example` | « `malloc` a échoué et retourné `NULL` » | `malloc` n'est jamais appelé ; c'est la garde `n <= 0` |
| `heap_example` | « `bob` est fuité » | `bob` et `bob->name` sont libérés ; la fuite est `alice->name` |
| `stack_example` | « les adresses de `dump_frame` diffèrent à l'entrée et à la sortie » | elles sont identiques à profondeur égale (frame recréé au même endroit) |

---

## 7. Récapitulatif

| Programme | Zone en cause | Défaut | Détection Valgrind |
|---|---|---|---|
| `stack_example` | pile | aucun (démonstration) | propre |
| `heap_example` | tas | fuite de 6 octets (`alice->name`) | `definitely lost` |
| `aliasing_example` | tas + alias | use-after-free (lecture + écriture) | `Invalid read/write` sur bloc `free'd` |
| `crash_example` | tas (jamais alloué) | déréférencement de `NULL` | `Invalid write`, `SIGSEGV` |