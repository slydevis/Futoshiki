#ifndef __FILE_H__
#define __FILE_H__

/***********************************************************************************************************************
* LECTURE DU FICHIER SOURCE + INITIALISATION DES VARIABLES GLOBALES
***********************************************************************************************************************/

/* Initialise les données de la grille */
void gridLineManager(char* line, int nbLine) {
    for(int i = 0; i < (int) strlen(line); ++i)
    {
        if (line[i] == '<' || line[i] == '>')
            addContrainte(nbLine * gridSize + i, nbLine * gridSize + i + 1, line[i]);
        else if (line[i] == '^' ||line[i] == 'v') {
            addContrainte((nbLine - 1) * gridSize + i, nbLine * gridSize + i, line[i]);
        }
        else if(isdigit(line[i])) {
            grid[nbLine * gridSize + i].value = line[i] - '0';
            if(line[i] == '0')
                grid[nbLine * gridSize + i].canChange = true;
            else
                grid[nbLine * gridSize + i].canChange = false;
        }
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
}

#endif /* __FILE_H__ */
