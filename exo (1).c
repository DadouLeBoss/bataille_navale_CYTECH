
/*
    //------------------------------------
    // creation d'un dépot GIT (github.com ou gitlab.com)
    // vous envoyez l'url du dépot (url publique)
    
    // Doxygen generation doc (cela implique de commenter toutes vos fonctions et structures et constantes à minima.... et tout en anglais)
    // makefile pour tout compiler
    // generer une lib (dyn ou static) de tous vos fichiers sauf le main
    // votre executable = main.c + lib
    // code robuste !!!!!!!!
    // code separé en modules !!
    //------------------------------------


    //------------------------------------
    // Bataille navale contre l'ordinateur
    //------------------------------------

    // enumeration avec le type de case du plateau
    // WATER
    // WATER_SHOT
    // BOAT
    // WRECK
    
    // structure pour chaque bateau
    // - taille bateau
    // - position de référence (coordonnées, soit du milieu, soit du pt en haut à gauche)
    // - orientation

    // Structure plateau de jeu (1 plateau par joueur)
    // double pointeur pour la matrice
    // taille du cote de la matrice
    // initialisé à vide

    // structure "JEU"
    // qui contient 2 plateaux alloués dynamiquement
    // et qui contient 2 tableaux de bateaux (1 pour chaque joueur)

    // Une constante pour le nombre de bateaux par joueur (5 ? 6 ?)
    // Une constante pour la taille d'un plateau (ex 10 pour un plateau de 10x10)

    // fonction pour créer un bateau qui prend les paramètres necessaires
    // et qui va allouer une structure bateau décrite précédemment
    
    // fonction pour vérifier si un bateau est encore en vie ou pas ?
    // en paramètre l'adresse d'une structure bateau, retour booléen
       
    // fonction pour créer un "jeu" (2 plateaux, 2 tableaux de bateaux initialisés)
    // cette fonction place les bateaux de maniere aleatoire (pseudo-aleatoire)
    // et fait en sorte que 2 bateaux ne se touchent pas 
    
    // fonction qui affiche un plateau avec l'etat des bateaux (vue joueur) ou bien (booleen paramètre) affiche un plateau avec juste le résultat des tirs (vue du terrain de l'ordi)    

    // fonction qui sequence un tour de jeu (joueur) 
    // demande case X / Y
    // effectue le tir et modifie en conséquence
    // affiche un message en fonction

    // fonction qui sequence un tour de jeu (ordi)
    // qui effectue un tir aleatoire là ou on a pas deja tiré (au mieux !!)
    
    // fonction principale pour sequencer l'ensemble et afficher le gagnant

    // A la fin du jeu, toutes les données allouées sont libérées explicitement par le programme.

    // gcc ..... -fsanitize=address pour avoir un affichage des allocations non libérées à la fin du programme

*/


