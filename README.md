# Rogue-like — Jeu d'exploration en C++

Projet pédagogique de jeu en terminal : explorer un labyrinthe, collecter des équipements, affronter des monstres et atteindre la sortie. La carte est chargée depuis un fichier texte, et les déplacements des monstres comportent une composante aléatoire.

## Fonctionnalités

- Affichage coloré de la carte, des statistiques et des messages avec curses/ncurses.
- Déplacement du joueur au clavier avec contrôle des collisions.
- Combat basé sur la force du joueur et du monstre, avec réapparition en cas de défaite.
- Inventaire, bonus d'équipements et ouverture des portes à l'aide des objets correspondants.
- Détection de monstres dangereux par distance de Manhattan.
- Détection de la sortie et possibilité de recommencer une partie.

## Installation (Linux / Windows avec WSL Ubuntu)

Dans Ubuntu ou un terminal Linux, installer les dépendances :

```bash
sudo apt update
sudo apt install g++ make libncurses-dev
```

Ouvrir un terminal dans le dossier contenant `main.cpp` et `level.txt`, puis :

```bash
make
./roguelike
```

Sans Make, la commande de compilation équivalente est `g++ -std=c++17 main.cpp -lncurses -o roguelike`.

Sous Windows, WSL permet d'utiliser ces mêmes commandes sans remplacer Windows. Dans le terminal VS Code ouvert dans le dossier du jeu, taper `wsl` pour entrer dans Linux, puis les commandes ci-dessus (une distribution Ubuntu doit être installée). Agrandir la fenêtre du terminal, idéalement au moins 140 colonnes × 30 lignes pour afficher tous les messages.

## Commandes du jeu

| Touche | Action |
| --- | --- |
| Flèches | Se déplacer ; interagir avec les cases |
| Q / q | Quitter |
| R / r | Rejouer après la victoire |

| Symbole | Signification |
| --- | --- |
| `@` | Joueur |
| `#` | Mur |
| `A-Z` | Monstres |
| `a-z` | Objets |
| `1-9` | Portes |
| `$` | Sortie |

## Organisation du code

| Fichier | Rôle |
| --- | --- |
| `main.cpp` | Initialisation, boucle principale, victoire |
| `carte.cpp`, `level.txt` | Lecture et affichage du niveau |
| `enregistrement.hpp` | Structures de données du jeu |
| `joueur.cpp` | Déplacement et interactions |
| `monstres.cpp` | Déplacements aléatoires |
| `combat.cpp` | Combat et détection de danger |
| `equipement.cpp`, `portes.cpp` | Inventaire, bonus, portes |
| `lib_ncurses.cpp`, `lib_projet_ncurses.hpp`, `couleurs.hpp` | Affichage et saisie |

Le projet conserve l'organisation pédagogique d'origine : `main.cpp` inclut les autres fichiers d'implémentation. Compiler uniquement `main.cpp`, pas tous les `.cpp` séparément.

## Version portfolio et limites

Le dépôt contient la version finale du projet scolaire, nettoyée pour GitHub. Les brouillons, exécutables et bibliothèques précompilées ont été retirés. La préparation avec assistance IA a apporté un Makefile, ce README et des corrections ciblées de lecture de carte, d'initialisation et de limite d'inventaire. Le niveau reste fixe ; il ne s'agit pas d'un générateur procédural. La compilation et les tests interactifs sont à vérifier dans un environnement disposant de ncurses. Les fichiers pédagogiques d'origine sont à publier uniquement si leurs droits de redistribution le permettent.
