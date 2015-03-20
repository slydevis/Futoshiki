#ifndef __INITTEST_H__
#define __INITTEST_H__

#include "util.h"

/***********************************************************************************************************************
* TEST UNITAIRE : INITIALISATION
***********************************************************************************************************************/

void resetAll() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTabContrainte = 0;

    for(int i = 0; i < gridSize*gridSize; ++i) {
        grid[i].value = 0;
        grid[i].canChange = true;
    }
}
void initContrainte1() {
    resetAll();

    addContrainte(0, 1, '<');

    grid[0].value = 2;
    grid[1].value = 1;
}

void initContrainte2() {
    resetAll();

    addContrainte(0, 1, '>');

    grid[0].value = 2;
    grid[1].value = 1;
}

void initContrainte3() {
    resetAll();

    addContrainte(0, 1, 'v');

    grid[0].value = 2;
    grid[1].value = 1;
}

void initContrainte4() {
    resetAll();

    addContrainte(0, 1, '^');

    grid[0].value = 2;
    grid[1].value = 1;
}

void initCheckFutoTest1() {
    resetAll();
}

void initCheckFutoTest2() {
    resetAll();

    for(int i = 0; i < gridSize*gridSize; ++i)
        grid[i].value = i + 1;

    grid[3].value = 5;
}

void initCheckFutoTest3() {
    resetAll();

    for(int i = 0; i < gridSize*gridSize; ++i)
        grid[i].value = i + 1;

    grid[gridSize].value = 1;
}

void initCheckFutoTest4() {
    resetAll();

    for(int i = 0; i < gridSize*gridSize; ++i)
        grid[i].value =  i + 1;

    grid[3*gridSize + 1].value = 1;
}

void initCheckFutoTest5() {
    resetAll();

    for(int i = 0; i < gridSize*gridSize; ++i)
        grid[i].value = i;

    grid[4*gridSize + 3].value = 3;
}

void initCheckFutoTest6() {
    resetAll();

    for(int i = 0; i < gridSize*gridSize; ++i)
        grid[i].value = i + 1;

    grid[3*gridSize+1].value = 2;
    grid[3*gridSize].value = 2;
}

void initCheckFutoTest7() {
    resetAll();

    for(int i = 0; i < gridSize*gridSize; ++i)
        grid[i].value = i + 1;

    grid[4*gridSize + gridSize - 2].value = 2;
    grid[4*gridSize + gridSize - 1].value = 2;
}

void initCheckFutoTest8() {
    resetAll();

    for(int i = 0; i < gridSize*gridSize; ++i)
        grid[i].value = i + 1;

    grid[4*gridSize].value = 2;
    grid[2*gridSize].value = 2;
}

// TODO : Faire un test plus propre et valable pour toutes les tailles de grille
// Fonctionnel juste pour une grille de 6x6 pour l'instant
void initCheckFutoTest9() {

/*
    Error source :
    3    1    2    4    5    6
    1    3    4    6    2    5
    4    5    3    2    1    0
    0    2    0    0    0    0
    0    0    0    0    0    0
    2    0    0    0    0    0

*/

    resetAll();

    grid[0].value = 3;
    grid[1].value = 1;
    grid[2].value = 2;
    grid[3].value = 4;
    grid[4].value = 5;
    grid[5].value = 6;
    grid[6].value = 1;
    grid[7].value = 3;
    grid[8].value = 4;
    grid[9].value = 6;
    grid[10].value = 2;
    grid[11].value = 5;
    grid[12].value = 4;
    grid[13].value = 5;
    grid[14].value = 3;
    grid[15].value = 2;
    grid[16].value = 1;
    grid[17].value = 0;
    grid[18].value = 0;
    grid[19].value = 2;
}

void initBacktrackTest() {
    resetAll();
}

void initBacktrackTest2() {
    resetAll();

    grid[gridSize*gridSize - 3].value = 5;
    grid[gridSize*gridSize - 3].canChange = false;

    grid[2].value = 5;
    grid[2].canChange = false;
}
#endif /* __INITTEST_H__ */
