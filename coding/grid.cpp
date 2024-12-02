#include "grid.hpp"
#include <iostream>

using namespace std;

// Constructeur : initialise la grille et le tampon temporaire
Grid::Grid(int sizeY, int sizeX) 
    : sizeX(sizeX), sizeY(sizeY), grid(sizeY, vector<Cell>(sizeX)), tmp(sizeY, vector<Cell>(sizeX)) {}

// Retourne la taille X de la grille
int Grid::getSizeX() const {
    return sizeX;
}

// Retourne la taille Y de la grille
int Grid::getSizeY() const {
    return sizeY;
}

// Initialise la grille avec des cellules mortes
void Grid::create() {
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            grid[i][j] = Cell(); // Toutes les cellules sont mortes au départ
        }
    }
}

// Vérifie les voisins d'une cellule et applique les règles du jeu
void Grid::surroundingCheck(int posY, int posX) {
    int nearby = 0; // Compteur de voisins vivants
    bool stateCell = grid[posY][posX].getState(); // État actuel de la cellule

    // Parcours des 8 voisins
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // Ignorer la cellule elle-même
            if (i == 0 && j == 0) continue;

            // Vérifier si le voisin est dans les limites
            int neighborY = posY + i;
            int neighborX = posX + j;

            if (neighborY >= 0 && neighborY < sizeY && neighborX >= 0 && neighborX < sizeX) {
                if (grid[neighborY][neighborX].getState()) {
                    nearby++; // Incrémenter si le voisin est vivant
                }
            }
        }
    }

    // Appliquer les règles du jeu
    if (stateCell && (nearby == 2 || nearby == 3)) {
        tmp[posY][posX].editState(true); // Cellule vivante reste vivante
    } else if (!stateCell && nearby == 3) {
        tmp[posY][posX].editState(true); // Cellule morte devient vivante
    } else {
        tmp[posY][posX].editState(false); // Sinon, la cellule meurt ou reste morte
    }
}

// Affiche la grille actuelle dans la console
void Grid::displayGrid() const {
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            cout << (grid[i][j].getState() ? "O" : "."); // Affiche 'O' pour vivant, '.' pour mort
        }
        cout << endl;
    }
    cout << endl;
}

// Change l'état d'une cellule (vivante <-> morte)
void Grid::stateChange(int posY, int posX) {
    grid[posY][posX].editState(!grid[posY][posX].getState()); // Inverse l'état
}


void Grid::updateGrid() {
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            surroundingCheck(i, j); // Calculer le nouvel état pour chaque cellule
        }
    }
    grid = tmp; // Remplacer la grille principale par le tampon
}