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
|-----> childproc (API pour manipuler les sous-processus)
|
|-----> misc (d'autres fonctions optionnelles pour le projet)
|
|-----> neo_libft (ma propre libft)
|
|-----> tests (unit-tests pour chaque fonctions)
|     |
|     ---> utils (fonctions pour les tests unitaires)
|
|-----> includes (Header files pour les API de cette branche)
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

- [ ] Gérer les pipes
- [ ] Ajouter une fonction `get_path` pour obtenir le chemin d'accès vers un binaire.
- [ ] Utiliser les variables d'environnement pour décider si oui ou non on utilise des couleurs.
- [x] Créer une fonction `redir_file` qui redirige la sortie standard et la sortie d'erreur vers un fichier.
	* [x] Permet de simplifier encore plus l'utilisation de cette lib.
	* [x] Possibilité de passer un flag `append` pour ajouter les données à la fin du fichier, plutôt que de remplacer le contenu.
	* [x] Fermer le fichier à la fin de la fonction.
- [x] Verifier que le binaire existe
	* [x] Qu'il est bien executable
- [x] Verifier que le fichier passé a `redir_file`
	* [x] Que ce n'est pas un dossier
	* [x] Que l'on peut lire et écrire dedans
- [x] Afficher des erreurs explicites.
- [x] Refaire le moteur de tests unitaire, afin d'écrire les tests directement en C et provoquer des erreurs.
- [x] Faire une fonction `generate_prompt` qui permet de générer le prompt du shell (raccourci si trop long).
_(liste évidemment non exhaustive)_