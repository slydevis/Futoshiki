#ifndef __FILE_H__
#define __FILE_H__

/***********************************************************************************************************************
* LECTURE DU FICHIER SOURCE + INITIALISATION DES VARIABLES GLOBALES
***********************************************************************************************************************/

#include "util.h"

/* Initialise les données de la grille */
void gridLineManager(char* line, int nbLine) {
    for(int i = 0, pos = 0; pos < (int) strlen(line); ++pos, ++i)
    {
        if (line[pos] == '<' || line[pos] == '>') {
            addContrainte(nbLine * gridSize + i -1, nbLine * gridSize + i, line[pos]);
            i--;
        }
        else if (line[pos] == '^' ||line[pos] == 'v')
            addContrainte((nbLine - 1) * gridSize + pos, nbLine * gridSize + pos, line[pos]);
        else if(isdigit(line[pos])) {
            grid[nbLine * gridSize + i].value = line[pos] - '0';
            if(line[pos] == '0') {
                grid[nbLine * gridSize + i].canChange = true;
            }
            else {
                grid[nbLine * gridSize + i].canChange = false;
            }

            grid[nbLine * gridSize + i].dom = initDomaine(NULL, grid[nbLine * gridSize + i].value);
        }
        else
            i--;
    }
}

/* Lit le fichier en paramètre */
void readGrid(const char* path) {
    FILE* file = NULL;

    char buff[MAX_SIZE];

    file = fopen(path, "r");

    if (file != NULL) {

        fgets(buff, MAX_SIZE, file);
        gridSize = atoi(buff);

        int nbLigne = 0;
        int incr = 1;
        while(fgets(buff, MAX_SIZE, file) != NULL) {
            gridLineManager(buff, nbLigne);
            if(incr == 1) {
                incr = 0;
                nbLigne++;
            }
            else incr = 1;
        }

        fclose(file);
    }

    removeUselessDomain();
}

void writeGrid(char* buff) {
    char path[100];

    strcpy(path, buff);
    strcat(path, ".log");

    printf("Arrêt du programme -> Creation des logs : ");

    FILE* file = fopen(path, "w+");

    if(file == NULL) {
        color(COLOR_RED);
        printf("Erreur d'ouverture du fichier de sortie\n");        
    }

    int nbLigne = 0;
    for(int i = 0; i < gridSize; ++i) {
        fputs("\n", file);
        for(int j = 0; j < gridSize; ++j) {
            char* str = malloc(sizeof(char)* 100);
            sprintf(str, "%5d", grid[nbLigne * gridSize + j].value);
            fputs(str, file);
            free(str);
        }
        nbLigne++;
    }
    
    fputs("\n", file);

    fclose(file);
    
    color(COLOR_GREEN);
    printf("OK\n");
    color(COLOR_WHITE);

    printBeautifulGrid(COLOR_GREEN);
    exit(0);
}

#endif /* __FILE_H__ */
