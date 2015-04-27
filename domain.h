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

    // Ajout en fin de liste

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

int domaineAt(Domaine dom, int pos) {
    
    if(dom == NULL || pos < 0)
        return -1;

    Domaine list = dom;

    for(int i = 0; i < pos; ++i) {

        if(list->next == NULL)
            break;

        list = list->next;
    }

    return list->value;
}

Domaine removeDomaine(Domaine dom, int value) {
    if(dom == NULL)
        return NULL;
 
    if(dom->next == NULL) {
        if(dom->value != value)
            return dom;

        free(dom);
        return NULL;
    }
 
    Domaine previous = dom;
    Domaine current = dom;
    int i = 0;

    while(current->value != value) {

        if(current->next == NULL)
            break;
        previous = current;
        current = current->next;
        ++i;
    }

    if(i == 0) {
        free(previous);
        return dom->next;
    }

    previous->next = current->next;

    free(current);
    return dom;
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
