#ifndef __CONSTRAINT_H__
#define __CONSTRAINT_H__

#include "util.h"

struct Contrainte* tabContrainte = NULL;
int tailleTabContrainte = 0;
int posContrainte = 0;

typedef struct Contrainte{
    int v1, v2;
    char contrainte;
} Contrainte;


/* Met a jour la taille du tableau et ajoute la nouvelle contrainte */
void majContrainte (Contrainte contrainte) {

    if(tabContrainte == NULL) {
        tabContrainte = calloc(1, sizeof(Contrainte));
    }

    tailleTabContrainte += 1;
    
    /*
    void* res = realloc(tabContrainte, tailleTabContrainte * sizeof(Contrainte));

    if(res == NULL) {
        free(tabContrainte);
        color(COLOR_RED);
        perror("realloc() error");
        color(COLOR_WHITE);
        exit(1);
    } */

    tabContrainte[tailleTabContrainte - 1] = contrainte;
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
void addContrainte (int a, int b, char c)
{
    Contrainte contrainte;
    contrainte = initContrainte(a, b, c);
    majContrainte(contrainte);
}

/* Renvoie le résultat de la vérification de contrainte */
int checkContrainte(Contrainte* c)
{
    if(grid[c->v1].value == 0 || grid[c->v2].value == 0) return true;

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
