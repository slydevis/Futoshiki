#ifndef __UTIL_H__
#define __UTIL_H__

#include <signal.h>     /* sigaction */
#include <time.h> /* clock */

#include "constraint.h"
#include "domain.h"

#define COLOR_BLACK "30"
#define COLOR_RED "31"
#define COLOR_GREEN "32"
#define COLOR_YELLOW "33"
#define COLOR_BLUE "34"
#define COLOR_WHITE "37"

#define color(param) printf("\033[%sm",param)

#define MAX_SIZE 500
#define SLEEP_TIME 1

#define true 1
#define false 0

clock_t debut;
clock_t fin;

void writeGrid(char* path);

// Handler if SIGINT
void logOnStop(int signal) {
    if(signal == SIGINT)
        writeGrid("save");
}

/***********************************************************************************************************************
* CHRONO
***********************************************************************************************************************/

void startChrono() { debut = clock(); }

void stopChrono() { fin = clock(); }

float getTimer() { return (fin - debut)*1.0/CLOCKS_PER_SEC; }

/***********************************************************************************************************************
* VARIABLE GLOBAL DIVERS
***********************************************************************************************************************/

typedef struct {
    int value;
    int canChange;
    Domaine dom;
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

void runTestWithIntArg(int (*f)(int), void (*init)(), int result, int arg) {
    (*init)();
    int r = (*f)(arg);

    printf("Run Test : ");

    if(r == result) {
        color(COLOR_GREEN);
        printf("OK\n");
        color(COLOR_WHITE);
    }
    else {
        printf("\n");
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

        for(int j = 0; j < gridSize; ++j) {
            printf("%5d", grid[nbLigne * gridSize + j].value);
        }

        nbLigne++;
    }
}

void printBeautifulGrid(char* gridColor) {
    printf("    ");

    for(int i = 0; i < ((gridSize*5)/2) - 6; ++i)
        printf("%c", '=');

    printf(" FUTOSHIKI ");

    for(int i = 0; i < ((gridSize*5)/2) - 6; ++i)
        printf("%c", '=');

    color(gridColor); // Vert

    printGrid();

    color(COLOR_WHITE); // Blanc

    printf("\n    ");

    for(int i = 0; i < ((gridSize)*5) - 2; ++i)
        printf("%c", '=');

    printf("\n");

    printf("    ");

    printf("\n");
}

/***********************************************************************************************************************
* FONCTION UTIL
***********************************************************************************************************************/

/*Efface la console sous linux */
void clearScreen() { printf("\033[H\033[2J"); }

#endif /* __UTIL_H__ */