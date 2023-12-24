#include "bataille_navale.h"

int main() {
    // Création du jeu
    Game* jeu = creerGame();

    // Appel de la fonction pour jouer
    jouer(jeu);

    return 0;
}
