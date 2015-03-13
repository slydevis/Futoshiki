#ifndef _UTIL_H
#define _UTIL_H

#include "constraint.h"

#define COLOR_BLACK "30"
#define COLOR_RED "31"
#define COLOR_GREEN "32"
#define COLOR_YELLOW "33"
#define COLOR_BLUE "34"
#define COLOR_WHITE "37"

#define color(param) printf("\033[%sm",param)

#define MAX_SIZE 500

#define true 1
#define false 0

/***********************************************************************************************************************
* VARIABLE GLOBAL DIVERS
***********************************************************************************************************************/

typedef struct {
    int value;
    int canChange;    
} int_t;

int_t grid[MAX_SIZE * MAX_SIZE];
int gridSize = 0;

/***********************************************************************************************************************
* TEST UNITAIRE
***********************************************************************************************************************/

/* Fonction de lancement des tests unitaires */
void runTest(int (*f)(), void (*init)(), int result) {
    (*init)();
    int r = (*f)();

    printf("Run Test : ");

    if(r == result) {
        color(COLOR_GREEN);
        printf("OK\n");
        color(COLOR_WHITE);
    }
    else {
        color(COLOR_RED);
        printf("Fail\n");
        color(COLOR_WHITE);
        exit(-1);
    }
}

/***********************************************************************************************************************
* FONCTION D'AFFICHAGE
***********************************************************************************************************************/

/* Affiche la grille */
void printGrid() {
    int nbLigne = 0;
    for(int i = 0; i < gridSize; ++i) {
        printf("\n");

        for(int j = 0; j < gridSize; ++j)
            printf("%5d", grid[nbLigne * gridSize + j].value);

        nbLigne++;
    }
}

/***********************************************************************************************************************
* FONCTION UTIL
***********************************************************************************************************************/

/*Efface la console sous linux */
void clearScreen() { printf("\033[H\033[2J"); }

#endif /* UTIL_H */