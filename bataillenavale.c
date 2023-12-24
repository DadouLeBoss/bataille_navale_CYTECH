#include "bataille_navale.h"

// Enumération pour les différents types de cases
enum casetype {
    WATER,
    WATER_SHOT,
    BOAT,
    WRECK
};

// Structure pour représenter un bateau
typedef struct {
    int length;
    int pos_x;
    int pos_y;
    int horiz;
} Boat;

// Structure pour représenter le plateau de jeu
typedef struct {
    enum casetype** matrix;
    int side;
} Plate;

// Structure pour représenter le jeu complet
typedef struct {
    Plate* board[2];
    Boat ships[2][5];
} Game;

#define NUMBER_BOAT 5
#define BOARD_SIDE 10

// Fonction pour créer un bateau
Boat createBoat(int size, int posx, int posy, int horiz) {
    Boat newBoat;
    newBoat.length = size;
    newBoat.pos_x = posx;
    newBoat.pos_y = posy;
    newBoat.horiz = horiz;
    return newBoat;
}

// Fonction pour vérifier si un bateau est encore en vie
int boatAlive(Boat boat) {
    return (boat.length > 0);
}

// Fonction pour créer le jeu
Game* createGame() {
    Game* game = malloc(sizeof(Game));
    if (game == NULL) {
        exit(1);
    }

    for (int i = 0; i < 2; i++) {
        game->board[i] = malloc(sizeof(Plate));
        if (game->board[i] == NULL) {
            exit(2);
        }

        game->board[i]->matrix = malloc(BOARD_SIDE * sizeof(enum casetype*));
        if (game->board[i]->matrix == NULL) {
            exit(3);
        }

        for (int j = 0; j < BOARD_SIDE; j++) {
            game->board[i]->matrix[j] = malloc(BOARD_SIDE * sizeof(enum casetype));
            if (game->board[i]->matrix[j] == NULL) {
                exit(4);
            }
        }

        for (int j = 0; j < BOARD_SIDE; j++) {
            for (int k = 0; k < BOARD_SIDE; k++) {
                game->board[i]->matrix[j][k] = WATER;
            }
        }

        game->board[i]->side = BOARD_SIDE;

        for (int j = 0; j < NUMBER_BOAT; j++) {
            int size = rand() % 3 + 3;
            int posx = rand() % BOARD_SIDE;
            int posy = rand() % BOARD_SIDE;
            int horiz = rand() % 2;

            game->ships[i][j] = createBoat(size, posx, posy, horiz);
        }
    }

    return game;
}

// Fonction pour vérifier si le placement d'un bateau est valide
int isValidPlacement(Plate* plate, int posx, int posy, int size, int horiz) {
    for (int i = posx; i < posx + ((1 - horiz) * size); i++) {
        for (int j = posy; j < posy + (horiz * size); j++) {
            if (plate->matrix[i][j] != WATER) {
                return 0; // La case n'est pas de l'eau
            }
        }
    }
    return 1; // Le placement est valide
}

// Fonction pour placer aléatoirement les bateaux sur le plateau
void placeRandomBoats(Game* game) {
    for (int player = 0; player < 2; player++) {
        for (int boat = 0; boat < NUMBER_BOAT; boat++) {
            int size = game->ships[player][boat].length;
            int posx, posy, horiz;

            do {
                horiz = rand() % 2;
                posx = rand() % (BOARD_SIDE - (1 - horiz) * size);
                posy = rand() % (BOARD_SIDE - horiz * size);
            } while (!isValidPlacement(game->board[player], posx, posy, size, horiz));
        }
    }
}
// Fonction pour obtenir le symbole correspondant à un type de case
char symboleCase(enum casetype cas, int joueur) {
    if (cas == WATER) {
        if (joueur == 1) {
            return '.';
        } else {
            return ' ';
        }
    } else if (cas == WATER_SHOT) {
        return 'O';
    } else if (cas == WRECK) {
        return 'X';
    } else if (cas == BOAT) {
        if (joueur == 1) {
            return 'B';
        } else {
            return ' ';
        }
    } else {
        return ' ';
    }
}

// Fonction pour afficher le plateau
void displayBoard(Plate* board, int player) {
    printf("Plateau du joueur %d :\n", player);

    for (int i = 0; i < BOARD_SIDE; i++) {
        for (int j = 0; j < BOARD_SIDE; j++) {
            printf("%c", symboleCase(board->matrix[i][j], player));
        }
        printf("\n");
    }
}

// Fonction pour effectuer un tir sur une case
enum casetype performShot(Plate* board, int posx, int posy) {
    if (board->matrix[posx][posy] == WATER) {
        board->matrix[posx][posy] = WATER_SHOT;
        return WATER;
    }
    if (board->matrix[posx][posy] == BOAT) {
        board->matrix[posx][posy] = WRECK;
        return BOAT;
    }
    if (board->matrix[posx][posy] == WRECK) {
        return WATER; // Tir déjà effectué sur cette case
    }
    if (board->matrix[posx][posy] == WATER_SHOT) {
        return WATER; // Tir déjà effectué sur cette case
    } else {
        return WATER;
    }
}

// Fonction pour le tour de jeu
void playTurn(Game* game, int player) {
    if (player == 1) {
        int posx, posy;
        do {
            printf("Entrer les coordonnees x et y de l'endroit où tirer : ");
            scanf("%d %d", &posx, &posy);

            if (posx < 0 || posx >= BOARD_SIDE || posy < 0 || posy >= BOARD_SIDE) {
                printf("Erreur, veuillez réessayer\n");
            }
        } while (posx < 0 || posx >= BOARD_SIDE || posy < 0 || posy >= BOARD_SIDE);

        enum casetype shotResult = performShot(game->board[1], posx, posy);

        if (shotResult == WATER) {
            printf("Dans l'eau !\n");
        } else if (shotResult == BOAT) {
            printf("Touché !\n");
        }
        displayBoard(game->board[0], 1);
    } else {
        int posx, posy;

        posx = rand() % BOARD_SIDE;
        posy = rand() % BOARD_SIDE;

        enum casetype shotResult = performShot(game->board[0], posx, posy);

        if (shotResult == WATER) {
            printf("L'ordinateur a tiré dans l'eau\n");
        } else if (shotResult == BOAT) {
            printf("L'ordinateur a touché un bateau\n");
        }
        displayBoard(game->board[1], 2);
    }
}

// Fonction pour libérer la mémoire allouée pour le jeu
void freeGame(Game* game) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < BOARD_SIDE; j++) {
            free(game->board[i]->matrix[j]);
        }
        free(game->board[i]->matrix);
        free(game->board[i]);
    }
    free(game);
}

// Fonction pour jouer le jeu complet
void playGame(Game* game) {
    placeRandomBoats(game);

    // Boucle principale du jeu
    int currentPlayer = 1;
    while (1) {
        // Affichage des plateaux des deux joueurs
        displayBoard(game->board[0], 1);
        printf("\n");
        displayBoard(game->board[1], 2);

        // Tour du joueur en cours
        printf("\nTour du joueur %d :\n", currentPlayer);
        playTurn(game, currentPlayer);

        // Vérifier s'il y a un gagnant
        int winner = 0;
        for (int i = 0; i < NUMBER_BOAT; i++) {
            if (boatAlive(game->ships[1][i])) {
                winner = 2;  // Le joueur 2 (ordinateur) a encore des bateaux
                break;
            }
            if (boatAlive(game->ships[0][i])) {
                winner = 1;  // Le joueur 1 (humain) a encore des bateaux
                break;
            }
        }

        if (winner != 0) {
            printf("Le joueur %d a gagné !\n", winner);
            break;  // Sortir de la boucle du jeu
        }

        // Changer de joueur
        currentPlayer++;
        if (currentPlayer == 3){
			currentPlayer = 1;
		}
    }

    // Libérer la mémoire allouée
    freeGame(game);
}

int main() {
    // Création du jeu
    Game* game = createGame();

    // Appel de la fonction pour jouer
    playGame(game);

    return 0;
}
