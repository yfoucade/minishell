# minishell

## Fonctions utiles au projet

Cette branche n'a comme but de contenir des fonctions utiles au projet.
Elles ne sont pas intégrables directement via un merge (pour l'instant).

## Contenu de la branche

Cette branche est structurée de cette façon :

```
|
|
|-----> builtins
|     |
|     ---> *.c (code de chaque builtins du projet)
|
|-----> tests (unit-tests pour chaque fonctions)
|     |
|     ---> utils (fonctions pour les tests unitaires)
|
|
|
|-----> childproc (API pour manipuler les sous-processus)
|
|
|
|-----> includes (Header files pour les API de cette branche)
|
|
|-----> checks.py (script pour exécuter les tests, verifier la norme et les fonctions externes)
```

## Objectif

Les sources de cette branche sont des fonctions, avec programmes compilables utilisés
pour tester et patcher rapidement les bugs.

Une fois que l'algorithme de parsing sera terminé, les sources de cette branche
seront traduites en fonctions, qui utiliseront l'algorithme de parsing.

### Signaler un bug / un problème

- Trouver un moyen de reproduire le bug de façon constante.
- Créer une issue GitHub pour signaler le bug, avec :
	1) Le cas qui cause le bug (la commande par exemple).
	2) Le comportement attendu.
	3) Le comportement défectueux.

### Liste de choses à faire

- Reproduire les bases de l'API Subprocess de [python](https://docs.python.org/3/library/subprocess.html)
  1) `subprocess.call` avec pipes vers STDOUT, STDERR et n'importe quel `fd`.

_(liste évidemment non exhaustive)_