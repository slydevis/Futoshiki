// Rajout de l'option -O3 pour gcc pour la release avec gcc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "constraint.h"
#include "initTest.h"
#include "file.h"
#include "util.h"

/***********************************************************************************************************************
* FONCTION DE VERIFICATION
***********************************************************************************************************************/

/***********************************************************************************************************************
* Renvoie -1 si il y a pas de problème sinon il renvoi l'indice où une des contrainte est violée
* Par exemple si il y a deux fois le même chiffre dans la même colonne
***********************************************************************************************************************/
int checkFutoshiki(int indice) {
    // Line verification
    for(int i = indice - indice%gridSize; i < indice + gridSize; ++i) {
        if(grid[indice].value != 0 && i != indice && grid[i].value == grid[indice].value) {
            #ifdef DEBUG
                color(COLOR_BLUE);
                for (int j = 0; j < gridSize * gridSize; ++j) {
                    if(j == i || j == indice) color(COLOR_RED);
                    if (j % gridSize == 0) printf("\n");
                    printf("\t%d", grid[j].value);
                    if(j == i || j == indice) color(COLOR_BLUE);
                }
                color(COLOR_WHITE);
                printf("\n");
            #endif /* DEBUG */

            return i;
        }
    }

    // Column verification
    for(int i = indice%gridSize; i < gridSize*gridSize; i += gridSize) {
        if(grid[indice].value != 0 && i != indice && grid[i].value == grid[indice].value) {
            #ifdef DEBUG
                color(COLOR_BLUE);
                for (int j = 0; j < gridSize * gridSize; ++j) {
                    if(j == i || j == indice) color(COLOR_RED);
                    if (j % gridSize == 0) printf("\n");
                    printf("\t%d", grid[j].value);
                    if(j == i || j == indice) color(COLOR_BLUE);
                }
                color(COLOR_WHITE);
                printf("\n");
            #endif /* DEBUG */
            return i;
        }
    }

    #ifdef DEBUG
        color(COLOR_BLUE);
        for (int j = 0; j < gridSize * gridSize; ++j) {
            if (j % gridSize == 0) printf("\n");
            printf("\t%d", grid[j].value);
        }
        color(COLOR_WHITE);
        printf("\n");
    #endif /* DEBUG */

    return -1;
}

int backTrack() {
/*for(int i = 0; i <= gridSize*gridSize; ++i) {
    sleep(1);
    clearScreen();
    color(COLOR_BLUE);
    for(int j = 0; j < gridSize*gridSize; ++j) {
        if(j == i) {
            color(COLOR_RED);
        }

        if(j%gridSize == 0) printf("\n");
        printf("\t%d", grid[j].value);
    }
    color(COLOR_WHITE);
    printf("\n");

    grid[i].value = 5;
}*/

    return false;
}

// TODO : Faire le tableau de domaine (tableau de liste chainée surement sera le plus simple)
int forwardChecking() {
    return false;
}

/* Retourne -1 si aucune solution, dans le cas ou il existe une solution renvoie 1 */
int resolveFutoshiki(int (*f)()) {

    // En attendant que l'algorithme soit fait, afin d'afficher la grille à tous les coups
    return f();
}

int main(int argc, char* argv[]) {
    if((argc - 1) != 1) {
        color(COLOR_RED);
		printf("Erreur d'argument\n");
        color(COLOR_WHITE);
        return -1;
	}

    clearScreen();

    readGrid(argv[1]);

    printf("    ");

    for(int i = 0; i < ((gridSize*5)/2) - 6; ++i)
        printf("%c", '=');

    printf(" FUTOSHIKI ");

    for(int i = 0; i < ((gridSize*5)/2) - 6; ++i)
        printf("%c", '=');

    color(COLOR_GREEN); // Vert

    printGrid();

    color(COLOR_WHITE); // Blanc

    printf("\n    ");

    for(int i = 0; i < ((gridSize)*5) - 2; ++i)
    printf("%c", '=');

    printf("\n");

    int res = resolveFutoshiki(backTrack);

    if(res < 0) {
        printf("La grille n'a pas de solution\n");
        return 0;
    }

    /* Lancement de tous les tests unitaires (Avec l'option cmake DEBUG seulement) */
    #ifdef DEBUG
        printf("\n\n===> TEST UNIT\n\n");

        printf("==> TEST : checkFutoshiki()\n\n");
        // Test de la vérification de la grille
        runTestWithIntArg(checkFutoshiki, initTest1, -1, 0);
        runTestWithIntArg(checkFutoshiki, initTest2, 4, 3);
        runTestWithIntArg(checkFutoshiki, initTest3, 5, 0);
        runTestWithIntArg(checkFutoshiki, initTest4, -1, 0);
        runTestWithIntArg(checkFutoshiki, initTest5, 4*gridSize + 3, 3);
        runTestWithIntArg(checkFutoshiki, initTest6, gridSize*3 + 1, gridSize*3);
        runTestWithIntArg(checkFutoshiki, initTest7, gridSize*4 + gridSize - 2, gridSize*4 + gridSize - 1);
        runTestWithIntArg(checkFutoshiki, initTest8, gridSize*2, gridSize*4);
        printf("\n==> TEST : testContrainte()\n\n");
        // Test de la vérification des contraintes
        runTest(testContrainte, initContrainte1, false);
        runTest(testContrainte, initContrainte2, true);
        runTest(testContrainte, initContrainte3, true);
        runTest(testContrainte, initContrainte4, false);
    #endif /* DEBUG */

    return 0;
}
