#ifndef __CONSTRAINT_H__
#define __CONSTRAINT_H__

#include "util.h"

int posContrainte = 0;

/* Met a jour la taille du tableau et ajoute la nouvelle contrainte */
void majContrainte (Contrainte contrainte) {

    if(tabContrainte == NULL)
        tabContrainte = calloc(1, sizeof(Contrainte));

    Contrainte* tabContrainteSave = NULL;
    tabContrainteSave = malloc(sizeof(struct Contrainte) * tailleTabContrainte);

    for(int i = 0; i < tailleTabContrainte; ++i) {
        Contrainte saveBuff = tabContrainte[i];
        tabContrainteSave[i] = saveBuff;
    }
    
    tailleTabContrainte += 1;

    free(tabContrainte);

    tabContrainte = malloc(sizeof(struct Contrainte) * tailleTabContrainte);

    for(int i = 0; i < tailleTabContrainte - 1; ++i) {
        Contrainte buff = tabContrainteSave[i];
        tabContrainte[i] = buff;
    }

    tabContrainte[tailleTabContrainte - 1] = contrainte;

    free(tabContrainteSave);
    tabContrainteSave = NULL;
}

/* Initialise la contrainte */
Contrainte initContrainte(int a, int b, char c) {
    Contrainte contrainte;
    contrainte.v1 = a;
    contrainte.v2 = b;
    contrainte.contrainte = c;

    return contrainte;
}

/* Adapte la taille du tableau a l'ajout d'une nouvelle contrainte */
void addContrainte (int a, int b, char c) {
    Contrainte contrainte;
    contrainte = initContrainte(a, b, c);
    majContrainte(contrainte);
}

/* Renvoie le résultat de la vérification de contrainte */
int checkContrainte(Contrainte* c) {

    if(grid[c->v1].value == 0 || grid[c->v2].value == 0)
        return true;

    nbTestContrainte++;
    
    switch (c->contrainte)
    {
        case '<':
            return grid[c->v1].value < grid[c->v2].value;
        case '>':
            return grid[c->v1].value > grid[c->v2].value;
        case '^':
            return grid[c->v1].value < grid[c->v2].value;
        case 'v':
            return grid[c->v1].value > grid[c->v2].value;
    }

    return false;
}

int testContrainte() {

    int res = false;
    for(int i = 0; i < tailleTabContrainte; ++i) {
        Contrainte c = tabContrainte[i];
        res = checkContrainte(&c);
    }

    return res;
}

#endif /* __CONSTRAINT_H__ */
