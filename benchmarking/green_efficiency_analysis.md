## Measurement Methodology
Pour mesurer, j'ai initialisé les valeurs de début et de fin avec clock_t grâce a la bibliothèque <time.h>. (qui permet d'avoir clock().)
Puis j'ai utilisé clock() pour commencer le compteur a "start" et le finir a "end". (Nom du fichier finissant ou commencant par end/start).
Entre ces deux derniers, une fonction se lançais selon les cas.
Le TOTAL cependant, commençait au debut mais se terminais à la fin de toutes les lignes clock()

Pour que printf affiches toutes ces valeurs, j'ai utilisé le format %.6f, suivi de (valeur du début du clock( - valeur de fin du clock()) / CLOCKS_PER_SEC
CLOCKS_PER_SEC permet d'afficher le résultat en secondes, grâce a une division.

## Observed Performance Differences
Voici les résultats obtenus pour chaque programmes :


Pour le programme baseline_loop.c :

Iterations: 100000000
Execution time: 0.109309 seconds

Pour le programme comparison_algorithms.c

Naive algorithm result: 625025000
Naive algorithm time: 0.558303 seconds
Single-pass algorithm result: 25000
Single-pass algorithm time: 0.000018 seconds

Pour le programme instrumentation_lab.c:

TOTAL seconds: 0.000296
BUILD_DATA seconds: 0.000140
PROCESS seconds: 0.000104
REDUCE seconds: 0.000049

Le programme le plus rapide est instrumentation_lab.c ~ 0.000296 secondes.
TOTAL est supérieur a toutes les sous-mesures car il est le total de toutes ces dernières : addition

## Relation Between Runtime and Energy Consumption
L'énergie consommmée correspond a la puissance * le temps. Donc un programme qui tourne moins longtemps consomme moins d’énergie.
Donc le programme le plus rapide est aussi celi qui consommera le moins.

## Limitations of the Experiment
Cependant cette méthode a des limites;

-clock() mesure le temps processeur, pas le temps réel donc si le programme attend ou est mis en pause par le système, ce temps n’est pas compté. Ce n’est donc pas forcément le temps vu par l’utilisateur.
-les résultats changent légèrement d’une exécution à l’autre
-d’autres programmes tournent en même temps sur notre machine donc ce n'est pas exact car le terminal, l’éditeur et le système utilisent aussi le processeur.
-Peu d’exécutions, en effet on n’as lancé le programme seulement 3 fois, ce n'est donc pas une mesure representative , pour que cette dernière le soit, il faudrait effectuer des centaines voir des milliers d'éxécutions.

## Practical Engineering Takeaway
Les mesures doivent guider l'optimisation.
Un ingenieur doit donc prioriser celle qui a le temps d'execution le plus long pour le réduire le plus possible.
Car energie = puissance * temps; donc moins de temps = moins d'énergie consommée, donc meilleure efficacitée.
Et selon moi, il faut plutôt choisir un algorithme dont le temps croît plus lentement par exemple O(n) plutôt que O(n**2) car cela devient plus important quand la taille des données augmentent.
