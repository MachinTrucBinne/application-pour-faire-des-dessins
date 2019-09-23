2019-09-21

		✎ DESSIN ✐

######################################################################
######################################################################

		DESCRIPTION

C'est une application en C++ / SDL2 pour dessiner.

Fonctionne aussi en plein écran.

Codé en juin 2017.
Déposé sur GitHub en septembre 2019.

######################################################################
######################################################################

		COMMANDES

• Cliquer et déplacer le curseur : dessiner

• c : effacer tout
• s : garder une capture d'écran sur le bureau

• CMD+Q : quitter
• Arrière : remonter soit du dossier des tounes au dossier des albums, soit du dossier des albums au dossier des artistes
• Entrer : entrer dans le dossier, jouer la toune sélectionnée
• Escape : quitter
• Espace : jouer / pause

• ABC...Z : va à l'artiste qui commence par la lettre

• CMD+L : aller au dossier de l'album où la toune joue (comme dans iTunes)
• CMD+Q : quitter

• Gauche : recommence la toune, ou joue la toune qui précède
• Droite : joue la toune suivante
• Haut/Bas : pour se déplacer dans les dossiers

• Cliquer : entrer dans le dossier, jouer la toune sélectionnée
• Scroller : scroller

######################################################################
######################################################################

		PRÉREQUIS

Le code est pour macOS, mais ça devrait pouvoir se porter à d'autres OS assez aisément.

Le code est en C++.
Il utilise SDL2 pour l'interface graphique.

Après avoir installé Brew et les Command Line Tools, il faut installer SDL2 :
	brew install SDL2

######################################################################
######################################################################

		COMPILATION

Le code devrait compiler avec :

g++ $(sdl2-config --cflags) -Wall -o main  main.cpp $(sdl2-config --libs)

######################################################################
######################################################################

Noé Aubin-Cadot, 2019.