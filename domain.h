#ifndef __DOMAIN_H__
#define __DOMAIN_H__

#include <stdlib.h>
#include "util.h"
#include "constraint.h"

int gridSize;

typedef struct element {
    int value;
    struct element *next;
} Element;

typedef Element* Domaine;

Domaine addDomaine(Domaine dom, int value) {
    Domaine newElement = malloc(sizeof(Domaine));

    // Ajout un fin de liste

    if(newElement != NULL) {
        newElement->value = value;
        newElement->next = NULL;
    }

    if(dom == NULL) {
        return newElement;
    }

    Domaine list = dom;
    while(list->next != NULL) {
        list = list->next;
    }

    list->next = newElement;

    return dom;
}

void removeDomaine(int pos) {
    (void) pos;
}

Domaine initDomaine(Domaine dom, int value) {
    if (value != 0) {
        dom = addDomaine(dom, value);
        return dom;
    }

    for (int i = 1; i <= gridSize; ++i) {
        dom = addDomaine(dom, i);
    }

    return dom;
}

void printDomaine(Domaine dom) {

    if(dom == NULL)
        return;

    Domaine list = dom;

    printf("==============>\n");

    while(list != NULL) {
        printf("%d\t", list->value);
        list = list->next;
    }

    printf("\n");

    printf("==============>\n");
}

#endif /* __DOMAIN_H__ */
