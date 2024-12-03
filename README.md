# Minishell

## Description
Le projet **Minishell** consiste à développer un shell minimaliste en utilisant le langage C. Ce shell doit être capable de recevoir des commandes de l'utilisateur, les exécuter, gérer l'historique des commandes, et prendre en charge un ensemble de fonctionnalités communes d'un shell. Ce projet vise à simuler les comportements d'un shell Unix, comme Bash, tout en implémentant des fonctionnalités spécifiques.

## Fonctionnalités de la partie obligatoire

### Affichage du prompt
- Le shell affiche un prompt lorsqu'il attend une nouvelle commande de l'utilisateur.
  
### Historique des commandes
- Le shell garde une trace de l'historique des commandes et peut y accéder via la fonction `readline()`.

### Exécution des commandes
- Le shell peut rechercher et exécuter des exécutables en utilisant la variable `PATH` ou en utilisant un chemin absolu/relatif.

### Gestion des signaux
- Le shell gère les signaux de manière appropriée, notamment les signaux comme `SIGINT` (ctrl-C), `SIGQUIT` (ctrl-\), et `SIGTSTP` (ctrl-D).

### Gestion des quotes
- Le shell gère les quotes simples `'` et doubles `"`:
  - **'** : Les caractères entre guillemets simples ne sont pas interprétés.
  - **"** : Les caractères entre guillemets doubles ne sont pas interprétés, à l'exception du `$` (pour les variables d'environnement).

### Redirections
- Le shell implémente les redirections suivantes :
  - **<** : Redirige l'entrée standard depuis un fichier.
  - **>** : Redirige la sortie standard vers un fichier.
  - **<<** : Lecture de l'entrée jusqu'à un délimiteur spécifique.
  - **>>** : Redirige la sortie standard en mode append (ajout).
  
### Pipes
- Le shell gère les pipes (`|`), connectant la sortie d'une commande à l'entrée d'une autre.

### Variables d'environnement
- Le shell gère l'expansion des variables d'environnement (ex : `$HOME`, `$PATH`).
- Il gère également la variable spéciale `$?`, qui affiche le code de sortie de la dernière commande exécutée.

### Gestion des touches spéciales
- **Ctrl-C** : Affiche un nouveau prompt sur une nouvelle ligne.
- **Ctrl-D** : Quitte le shell.
- **Ctrl-\** : Aucun effet sur le shell.

### Commandes internes (Builtins)
Le shell implémente les commandes internes suivantes :
- **echo** : Affiche un message. L'option `-n` empêche l'ajout d'un saut de ligne.
- **cd** : Change de répertoire (avec un chemin relatif ou absolu).
- **pwd** : Affiche le répertoire courant.
- **export** : Exporte des variables d'environnement.
- **unset** : Supprime des variables d'environnement.
- **env** : Affiche les variables d'environnement.
- **exit** : Quitte le shell.

## Installation

Clonez ce dépôt sur votre machine locale :
```bash
git clone https://github.com/your-username/minishell.git
cd minishell
