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

- Créer une fonction `redir_file` qui redirige la sortie standard et la sortie d'erreur vers un fichier.
	* Permet de simplifier encore plus l'utilisation de cette lib.
	* Possibilité de passer un flag `append` pour ajouter les données à la fin du fichier, plutôt que de remplacer le contenu.
	* Fermer le fichier à la fin de la fonction.
- Verifier que le binaire existe
	* Qu'il est bien executable
- Verifier que le fichier passé a `redir_file`
	* Que ce n'est pas un dossier
	* Que l'on peut lire et écrire dedans
- Gérer les pipes
- Afficher des erreurs explicites.
- Ajouter une fonction `get_path` pour obtenir le chemin d'accès vers un binaire.
- Refaire le moteur de tests unitaire, afin d'écrire les tests directement en C et provoquer des erreurs.
- Faire une fonction `generate_prompt` qui permet de générer le prompt du shell (raccourci si trop long).
- Utiliser les variables d'environnement pour décider si oui ou non on utilise des couleurs.
_(liste évidemment non exhaustive)_