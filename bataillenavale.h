#ifndef BATAILLE_NAVALE_H
#define BATAILLE_NAVALE_H

#include <stdio.h>
#include <stdlib.h>

enum casetype {
    WATER,
    WATER_SHOT,
    BOAT,
    WRECK
};

typedef struct {
    int length;
    int pos_x;
    int pos_y;
    int horiz;
} Bateau;

typedef struct {
    enum casetype** matrice;
    int Cote;
} Plate;

typedef struct {
    Plate* plateau[2];
    Bateau boat[2][5];
} Game;

#define NUMBER_BOAT 5
#define LENGHT_PLATE 10

Bateau creerBateau(int taille, int posx, int posy, int hori);
int boatAlive(Bateau boat);
Game* creerGame();
int placement_valide(Plate *plat, int posx, int posy, int taille, int hori);
void placerBateauAleatoire(Game* game);
char symboleCase(enum casetype ici, int player);
void afficherPlateau(Plate* plateau, int player);
enum casetype effectuerTir(Plate* plateau, int posx, int posy);
void TourDeJeu(Game* jeu, int player);
void libererJeu(Game* jeu);
void jouer(Game* jeu);

#endif /* BATAILLE_NAVALE_H */

