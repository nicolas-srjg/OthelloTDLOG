# Intelligence artificielle pour le jeu Othello

Le but de ce projet est de créer un outil capable de nous aider à nous améliorer au jeu d'Othello à différents stades de notre progression.

## Présentation du jeu

Les règles sont simples. La partie se déroule sur un plateau carré comportant
64 cases. Deux joueurs, représentés respectivement par la couleur
blanche ou noire, s’affrontent sur cette grille pour qu’à la fin de la partie
les jetons de sa couleur soient majoritaires sur le plateau. Les jetons sont
des pièces bicolores, noire sur une face et blanche sur l’autre. Le but pour
un joueur est donc de retourner les pièces de son adversaire pour augmenter
la proportion de sa couleur. Le mécanisme pour retourner une pièce est le
suivant : le joueur qui place un jeton permettant d’encadrer avec sa couleur
des pièces ennemies sur une ligne ou une diagonale peut retourner toutes les
pièces ennemies qui ont été retournées et donc les mettre à sa couleur.
De ces règles simples émergent pourtant des stratégies plus complexes.
L’ancien champion du monde d’Othello Brian Rose a d’ailleurs choisi pour
titre de son livre cette phrase révélatrice "A minute to learn, a lifetime to
master"

## Objectif

L’idée du projet est d’élaborer un outil permettant
de progresser au jeu. Non seulement il devrait permettre de jouer au jeu
en local avec un ami, mais aussi de jouer contre plusieurs niveaux d’intelligence
artificielle dont un serait capable de nous pousser dans nos retranchements.
Nous voulions également nous inspirer de ce que propose certains
sites d’échecs comme Lichess qui permet de jouer en local contre l’ordinateur
et de revenir en arrière dans les parties avec un échiquier d’analyse pour les
analyser et apprendre de nos erreurs.

## Résultat

Le jeu est fonctionne contre un humain ou contre une IA. Trois niveaux d'IA sont proposés.
Le niveau facile est aléatoire. Le niveau difficile a une bonne heuristique est parcours les coups possibles sur une profondeur 7.
Le niveau moyen parcours moins de coups (profondeur 7)

![alt-text](link)

Ici, on peut voir un début de partie se dérouler avec un retour en arrière avec l'éditeur de partie

## Installation

- Cloner le dépôt github pybind11 https://github.com/pybind/pybind11.git
- Exécuter le CMakeLists.txt avec un compilateur 64bits en mode release (celui de Microsoft visiual marche mieux)
- Aller chercher dans le build un fichier dont le nom commence par bindOthello et finit par l'extension .pyd
- Installer la librairie Pygame
- Exécuter main.py



