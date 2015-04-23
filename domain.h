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

void addDomaine(Element* dom, int value) {
    Element *newElement = malloc(sizeof(Element) * gridSize + 1);

    if(newElement != NULL) {
        newElement->value = value;
        newElement->next = NULL;
    }

    if(dom == NULL) {
        printf("Je passe\t");
        dom = newElement;
        free(newElement);
        return;
    }

    Domaine list = dom;
    while(list->next != NULL) {
        list = list->next;
    }
    list->next = newElement;

    dom = list;

    free(newElement);
    free(list);
}

void removeDomaine(int pos) {
    (void) pos;
}

void initDomaine(Element* dom, int value) {
    if (value != 0) {
        addDomaine(dom, value);
        return;
    }

    for (int i = 1; i <= gridSize; ++i) {
    printf("\n");
    addDomaine(dom, i);
    }
}

void printDomaine(Element* dom) {

//    Domaine list = dom;

    //while(list->next != NULL) {
        printf("%d\t", dom->value);
        //list = list->next;
    //}

    printf("\n");
   // free(list);

    printf("OK\n");
}

#endif /* __DOMAIN_H__ */
