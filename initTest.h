#ifndef __INITTEST_H__
#define __INITTEST_H__

/***********************************************************************************************************************
* TEST UNITAIRE : INITIALISATION
***********************************************************************************************************************/

void initContrainte1() {

    free(tabContrainte);
    tabContrainte = NULL;
    tailleTabContrainte = 0;

    addContrainte(0, 1, '<');

    grid[0].value = 2;
    grid[1].value = 1;
    grid[0].canChange = true;
    grid[1].canChange = true;

}

void initContrainte2() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTabContrainte = 0;

    addContrainte(0, 1, '>');

    grid[0].value = 2;
    grid[1].value = 1;
    grid[0].canChange = true;
    grid[1].canChange = true;
}

void initContrainte3() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTabContrainte = 0;

    addContrainte(0, 1, 'v');

    grid[0].value = 2;
    grid[1].value = 1;
    grid[0].canChange = true;
    grid[1].canChange = true;
}

void initContrainte4() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTabContrainte = 0;

    addContrainte(0, 1, '^');

    grid[0].value = 2;
    grid[1].value = 1;
    grid[0].canChange = true;
    grid[1].canChange = true;
}

void initTest1() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTabContrainte = 0;

    for(int i = 0; i < gridSize*gridSize; ++i) {
        grid[i].value = 0;
        grid[i].canChange = true;
    }
}

void initTest2() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTabContrainte = 0;

    for(int i = 0; i < gridSize*gridSize; ++i) {
        grid[i].value = i + 1;
        grid[i].canChange = true;
    }

    grid[3].value = 5;
}

void initTest3() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTabContrainte = 0;

    for(int i = 0; i < gridSize*gridSize; ++i) {
        grid[i].value = i + 1;
        grid[i].canChange = true;
    }

    grid[gridSize].value = 1;
}

void initTest4() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTabContrainte = 0;

    for(int i = 0; i < gridSize*gridSize; ++i) {
        grid[i].value =  i + 1;
        grid[i].canChange = true;
    }

    grid[3*gridSize + 1].value = 1;
}

void initTest5() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTabContrainte = 0;

    for(int i = 0; i < gridSize*gridSize; ++i) {
        grid[i].value = i;
        grid[i].canChange = true;
    }

    grid[4*gridSize + 3].value = 3;
}

void initTest6() {
    free(tabContrainte);
    tabContrainte = NULL;
    tailleTabContrainte = 0;

    for(int i = 0; i < gridSize*gridSize; ++i) {
        grid[i].value = i + 1;
        grid[i].canChange = true;
    }

    grid[3*gridSize+1].value = 2;
    grid[3*gridSize].value = 2;
}

#endif /* __INITTEST_H__ */
