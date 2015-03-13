// Rajout de l'option -O3 pour gcc pour la release avec gcc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "constraint.h"

#define DEBUG true

/***********************************************************************************************************************
* TEST UNITAIRE : INITIALISATION
***********************************************************************************************************************/

void initContrainte1() {

    free(tabContrainte);
    tabContrainte = NULL;
    tailleTab = 0;

    addContrainte(0, 1, '<');

    grid[0].value = 2;
    grid[1].value = 1;
    grid[0].canChange = true;
    grid[1].canChange = true;

}

void initContrainte2() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTab = 0;

    addContrainte(0, 1, '>');

    grid[0].value = 2;
    grid[1].value = 1;
    grid[0].canChange = true;
    grid[1].canChange = true;
}

void initContrainte3() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTab = 0;

    addContrainte(0, 1, 'v');

    grid[0].value = 2;
    grid[1].value = 1;
    grid[0].canChange = true;
    grid[1].canChange = true;
}

void initContrainte4() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTab = 0;

    addContrainte(0, 1, '^');

    grid[0].value = 2;
    grid[1].value = 1;
    grid[0].canChange = true;
    grid[1].canChange = true;
}

void initTest1() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTab = 0;

    for(int i = 0; i < gridSize*gridSize; ++i) {
        grid[i].value = i;
        grid[i].canChange = true;
    }
}

void initTest2() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTab = 0;

    for(int i = 0; i < gridSize*gridSize; ++i) {
        grid[i].value = i;
        grid[i].canChange = true;
    }

    grid[3].value = 4;
}

void initTest3() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTab = 0;

    for(int i = 0; i < gridSize*gridSize; ++i) {
        grid[i].value = i;
        grid[i].canChange = true;
    }

    grid[gridSize+3].value = 4;
}

void initTest4() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTab = 0;

    for(int i = 0; i < gridSize*gridSize; ++i) {
        grid[i].value =  i;
        grid[i].canChange = true;
    }

    grid[3*gridSize + 2].value = 2;
}

void initTest5() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTab = 0;

    for(int i = 0; i < gridSize*gridSize; ++i) {
        grid[i].value = i;
        grid[i].canChange = true;
    }

    grid[3*gridSize + 1].value = 2;
}

void initTest6() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTab = 0;

    for(int i = 0; i < gridSize*gridSize; ++i) {
        grid[i].value = i;
        grid[i].canChange = true;
    }

    grid[3*gridSize+1].value = 2;
    grid[3*gridSize].value = 2;
}

/***********************************************************************************************************************
* LECTURE DU FICHIER SOURCE + INITIALISATION DES VARIABLES GLOBALES
***********************************************************************************************************************/

/* Initialise les données de la grille */
void gridLineManager(char* line, int nbLine) {
    for(int i = 0; i < (int) strlen(line); ++i)
    {
        if (line[i] == '<' || line[i] == '>')
            addContrainte(nbLine * gridSize + i, nbLine * gridSize + i + 1, line[i]);
        else if (line[i] == '^' ||line[i] == 'v') {
            addContrainte((nbLine - 1) * gridSize + i, nbLine * gridSize + i, line[i]);
        }
        else if(isdigit(line[i])) {
            grid[nbLine * gridSize + i].value = line[i] - '0';
            if(line[i] == '0')
                grid[nbLine * gridSize + i].canChange = true;
            else
                grid[nbLine * gridSize + i].canChange = false;
        }
    }
}

/* Lit le fichier en paramètre */
void readGrid(const char* path) {
    FILE* file = NULL;

    char buff[MAX_SIZE];

    file = fopen(path, "r");

    if (file != NULL) {
        fgets(buff, MAX_SIZE, file);
        gridSize = atoi(buff);


        int nbLigne = 0;
        int incr = 1;
        while(fgets(buff, MAX_SIZE, file) != NULL) {
            gridLineManager(buff, nbLigne);
            if(incr == 1) {
                incr = 0;
                nbLigne++;
            }
            else incr = 1;
        }

        fclose(file);
    }
}

/***********************************************************************************************************************
* FONCTION DE VERIFICATION
***********************************************************************************************************************/

int checkFutoshiki() {
    int nbColCheck = 1;
    for(int i = 0; i < gridSize*4 - 1; ++i) {
        for(int j = nbColCheck * gridSize - 1; j > 0; --j) {
            if (i != j && (j - 1)%(gridSize - 1) == i%(gridSize - 1) && grid[i].value == grid[j].value) {
                return false;
            }

            if(i == j%nbColCheck && grid[i].value == grid[j + gridSize * nbColCheck].value)
                return false;

        }
        nbColCheck++;
    }

    if(tabContrainte != NULL && !testContrainte())
        return false;

    return true;
}

int backTrack() {
    for(int i = 0; i <= gridSize*gridSize; ++i) {
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
    }

    return false;
}

int forwardChecking() {
    return -1;
}

/* Retourne -1 si aucune solution, dans le cas ou il existe une solution renvoie 1 */
int resolveFutoshiki(int (*f)()) {

    // En attendant que l'algorithme soit fait, afin d'afficher la grille à tous les coups
    if(DEBUG)
        return f();

    return -1;
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
/*
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

    for(int i = 0; i < tailleTab; ++i) {
        printf("\n%d %c %d", tabContrainte[i].v1, tabContrainte[i].contrainte, tabContrainte[i].v2);
    }

    printf("\n\n");
*/
    int res = resolveFutoshiki(backTrack);

    if(res < 0) {
        printf("La grille n'a pas de solution\n");
        return 0;
    }

    printf("\n\n===> TEST UNIT\n\n");

    printf("==> TEST : checkFutoshiki()\n\n");

    // Test de la vérification de la grille
    runTest(checkFutoshiki, initTest1, true);
    runTest(checkFutoshiki, initTest2, false);
    runTest(checkFutoshiki, initTest3, true);
    runTest(checkFutoshiki, initTest4, false);
    runTest(checkFutoshiki, initTest5, true);
    runTest(checkFutoshiki, initTest6, false);

    printf("\n==> TEST : testContrainte()\n\n");
    // Test de la vérification des contraintes
    runTest(testContrainte, initContrainte1, false);
    runTest(testContrainte, initContrainte2, true);
    runTest(testContrainte, initContrainte3, true);
    runTest(testContrainte, initContrainte4, false);

    return 0;
}
