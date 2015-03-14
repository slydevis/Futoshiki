#ifndef _CONSTRAINT_H
#define _CONSTRAINT_H

#include <term.h>
#include "util.h"

struct Contrainte* tabContrainte = NULL;
int tailleTabContrainte = 0;

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
    void* res = realloc(tabContrainte, tailleTabContrainte * sizeof(Contrainte));

    if(res == NULL) {
        free(tabContrainte);
        color(COLOR_RED);
        perror("realloc() error");
        color(COLOR_WHITE);
        exit(1);
    }

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

void getContrainte(struct Contrainte con[], int indice) {
    for(int i = 0, cpt = 0; i < tailleTabContrainte; ++i, cpt++) {
        if(tabContrainte[i].v1 == indice)
            con[cpt] = tabContrainte[i];
        if(tabContrainte[i].v2 == indice)
            con[cpt] = tabContrainte[i];
    }
}

#endif /* _CONSTRAINT_H */