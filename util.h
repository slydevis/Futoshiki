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

void writeGrid(char* path);

// Handler if SIGINT
void logOnStop(int signal) {
    if(signal == SIGINT)
        writeGrid("save");
}

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

clock_t debut;
clock_t fin;

struct Contrainte* tabContrainte = NULL;
int tailleTabContrainte = 0;

typedef struct Contrainte{
    int v1, v2;
    char contrainte;
} Contrainte;

/***********************************************************************************************************************
* CHRONO
***********************************************************************************************************************/

void startChrono() { debut = clock(); }

void stopChrono() { fin = clock(); }

float getTimer() { return (fin - debut)*1.0/CLOCKS_PER_SEC; }

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
        color(COLOR_RED);
        printf("Fail\n");
        color(COLOR_WHITE);
        exit(-1);
    }
}

void runTestStructDomain(void (*init)(), int tailleTest, int res) {
    (*init)();

    int r = true;

    for(int i = 0; i < tailleTest; ++i) {
        if(grid[i].dom == NULL) {
            printf("OK\n");
            r = false;
        }
    }

    printf("Run Test : ");

    if(r == res) {
        color(COLOR_GREEN);
        printf("OK\n\n");
        color(COLOR_WHITE);
    }
    else {
        color(COLOR_RED);
        printf("Fail\n\n");
        color(COLOR_WHITE);
        exit(-1);
    }
}

/***********************************************************************************************************************
* FONCTIONS D'AFFICHAGE
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

/* Efface la console sous linux */
void clearScreen() { printf("\033[H\033[2J"); }

/***********************************************************************************************************************
* FONCTIONS DE MANIPULATION DES STRUCTURES
***********************************************************************************************************************/

int removeDomain(int v1, int v2, char contrainte) {
    switch(contrainte) {
        case '<' :
        case '^' :
        if(grid[v1].value == 0 && grid[v2].value == 0) {
            grid[v1].dom = removeDomaine(grid[v1].dom, gridSize);
            grid[v2].dom = removeDomaine(grid[v2].dom, 1);
            #ifdef VERBOSE
                printf("Suppression de %d sur grid[%d] (ligne %d)", gridSize, v1, __LINE__);
                printf("Suppression de %d sur grid[%d] (ligne %d)", 1, v2, __LINE__);
            #endif /* VERBOSE */
            return true;
        }

        if(grid[v1].value != 0 && grid[v2].value != 0)
            return false;

        if(grid[v1].value == 0) {
            for(int i = grid[v2].value; i < gridSize + 1; ++i) {
                Domaine dom = grid[v1].dom;
                grid[v1].dom = removeDomaine(dom, i);

                #ifdef VERBOSE
                    printf("Suppression de %d sur grid[%d] (ligne %d)", i, v1, __LINE__);
                #endif /* VERBOSE */
            }            
        }

        if(grid[v2].value == 0) {
            for(int i = grid[v1].value; i > 0; --i) {
                Domaine dom = grid[v2].dom;
                grid[v2].dom = removeDomaine(dom, i);

                #ifdef VERBOSE
                    printf("Suppression de %d sur grid[%d] (ligne %d)", i, v2, __LINE__);
                #endif /* VERBOSE */
            }
        }

        return true;  
        case '>':
        case 'v':
        if(grid[v1].value == 0 && grid[v2].value == 0) {
            grid[v1].dom = removeDomaine(grid[v1].dom, 1);
            grid[v2].dom = removeDomaine(grid[v2].dom, gridSize);

            #ifdef VERBOSE
                printf("Suppression de %d sur grid[%d] (ligne %d)", 1, v1, __LINE__);
                printf("Suppression de %d sur grid[%d] (ligne %d)", gridSize, v2, __LINE__);
            #endif /* VERBOSE */

            return true;
        }
            
        if(grid[v1].value != 0 && grid[v2].value != 0)
            return false;

        if(grid[v1].value == 0) {
            for(int i = grid[v2].value; i > 0; --i) {
                Domaine dom = grid[v1].dom;
                grid[v1].dom = removeDomaine(dom, i);

                #ifdef VERBOSE
                    printf("Suppression de %d sur grid[%d] (ligne %d)", i, v1, __LINE__);
                #endif /* VERBOSE */
            }
        }

        if(grid[v2].value == 0) {
            for(int i = grid[v1].value; i < gridSize; ++i) {
                Domaine dom = grid[v2].dom;
                grid[v2].dom = removeDomaine(dom, i);

                #ifdef VERBOSE
                    printf("Suppression de %d sur grid[%d] (ligne %d)", i, v2, __LINE__);
                #endif /* VERBOSE */
            }
        }
        return true;
    }

    return false;
}

int removeLineAndColumnDomain(int indice, int value) {

    int res = true;

    // Line verification
    for(int i = indice - indice%gridSize; i < indice - indice%gridSize + gridSize; ++i) {
      if(i != indice) {
            grid[i].dom = removeDomaine(grid[i].dom, value);
            
            if(grid[i].dom == NULL)
                res = false;
      }
    }

    // Column verification
    for(int i = indice%gridSize; i < gridSize*gridSize; i += gridSize) {
        if(i != indice)
            grid[i].dom = removeDomaine(grid[i].dom, value);

        if(grid[i].dom == NULL)
            res = false;
    }

    return res;
}

void addLineAndColumnDomain(int indice) {
    // Line verification
    for(int i = indice - indice%gridSize; i < indice - indice%gridSize + gridSize; ++i)
        grid[i].dom = addDomaine(grid[i].dom, grid[indice].value);

    // Column verification
    for(int i = indice%gridSize; i < gridSize*gridSize; i += gridSize) {
        if(i != indice)
            grid[i].dom = addDomaine(grid[i].dom, grid[indice].value);
    }
}

void removeUselessDomain() {

    #ifdef VERBOSE
        printf("===> INITIALISATION DES DOMAINES\n\n");
    #endif /* VERBOSE */
    
    for(int i = 0; i < tailleTabContrainte; ++i) {
        removeDomain(tabContrainte[i].v1, tabContrainte[i].v2, tabContrainte[i].contrainte);

        #ifdef VERBOSE
           printf("grid[%d].dom ==>\n", tabContrainte[i].v1);
           printDomaine(grid[tabContrainte[i].v1].dom);
           printf("grid[%d].dom ==>\n", tabContrainte[i].v2);
           printDomaine(grid[tabContrainte[i].v2].dom);
           sleep(SLEEP_TIME);
        #endif
    }
    
    for(int i = 0; i < gridSize * gridSize; ++i) {
        Domaine dom = grid[i].dom;

        if(dom != NULL && dom->next == NULL)
            removeLineAndColumnDomain(i, dom->value);

    }
}

#endif /* __UTIL_H__ */