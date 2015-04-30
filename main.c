// Rajout de l'option -O3 pour gcc pour la release avec gcc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "constraint.h"
#include "util.h"
#include "initTest.h"
#include "file.h"

int indice = 0;
int ligne = 0;
unsigned long long noeud = 0;

/***********************************************************************************************************************
* FONCTION DE VERIFICATION
***********************************************************************************************************************/

int checkFutoshiki(int indice);

/* Change les valeurs et vérifie la résolution du futoshiki */
int changerValeur()
{
    // Cette case n'est pas initiliasée
    if (grid[indice].value == 0)  {
        grid[indice].value = 1;
        noeud++;
    }

    // Evite de lancer de lancer plusieur fois la vérification = Gain de temps
    int resultatCheck = checkFutoshiki(indice);

    // Si le futoshiki n'est a ce point pas correcte, il faut changer les valeurs placées
    if (resultatCheck >= 0 && grid[indice].canChange == true) {
        // la valeur maximale est atteinte pour cette case
        while (grid[indice].value == gridSize && grid[indice].canChange == true) {
            // place cette valeur de nouveau a 0
            grid[indice].value = 0;
            // si indice == 0, nous avons essayé toutes les valeurs
            if (indice != 0) {
                indice--;
                while (grid[indice].canChange == false) {
                    if (indice != 0)
                        indice--;
                    else {
                        color(COLOR_RED);
                        printf ("\nPas de solution : %f\n", getTimer());
                        printf("Nombre de noeuds parcouru %llu\n\n", noeud);
                        color(COLOR_WHITE);
                        return false;
                    }
                }
            }
            else {
                stopChrono();
                color(COLOR_RED);
                printf ("\nPas de solution en %f\n", getTimer());
                printf("Nombre de noeuds parcouru %llu\n\n", noeud);
                color(COLOR_WHITE);
                return false;
            }
        }

        // incrémente la valeur de la case
        grid[indice].value++;
        noeud++;
    }
    else if (resultatCheck < 0 && indice == gridSize*gridSize -1) {
        stopChrono();
        color(COLOR_GREEN);
        printf ("\tSolution trouvée en %f !\n", getTimer());
        printf("\tNombre de noeuds parcouru %llu\n\n", noeud);
        color(COLOR_WHITE);
        return true;
    }
    else // on avance d'une case
        indice++;

    return -1;
}

int changerNValeur()
{
    // Initialisation de la première ligne    
    if(ligne == 0) {
        for(int i = 0; i < gridSize; ++i) {
            if(grid[i].canChange == true) {
                grid[i].value = grid[i].value + 1;
                for(int j = 0; j < gridSize;) {
                    if(i != j && grid[j].value != 0 && grid[j].value == grid[i].value) {
                        grid[i].value = grid[i].value + 1;
                        j = 0;
                        continue;
                    }
                    ++j;
                }
            }
        }
    }

    int resultatCheck = checkFutoshiki(indice);

    if(resultatCheck) {

    }

    printBeautifulGrid(COLOR_BLUE);

    return false;
/*

    // Si le futoshiki n'est a ce point pas correcte, il faut changer les valeurs placées
    if (resultatCheck >= 0 && grid[indice].canChange == true) {
        // la valeur maximale est atteinte pour cette case
        while (grid[indice].value == gridSize && grid[indice].canChange == true) {
            // place cette valeur de nouveau a 0
            grid[indice].value = 0;
            // si indice == 0, nous avons essayé toutes les valeurs
            if (indice != 0) {
                indice--;
                while (grid[indice].canChange == false) {
                    if (indice != 0)
                        indice--;
                    else {
                        color(COLOR_RED);
                        printf ("\nPas de solution : %f\n", getTimer());
                        printf("Nombre de noeuds parcouru %llu\n\n", noeud);
                        color(COLOR_WHITE);
                        return false;
                    }
                }
            }
            else {
                stopChrono();
                color(COLOR_RED);
                printf ("\nPas de solution en %f\n", getTimer());
                printf("Nombre de noeuds parcouru %llu\n\n", noeud);
                color(COLOR_WHITE);
                return false;
            }
        }

        // incrémente la valeur de la case
        grid[indice].value++;
        noeud++;
    }
    else if (resultatCheck < 0 && indice == gridSize*gridSize -1) {
        stopChrono();
        color(COLOR_GREEN);
        printf ("\tSolution trouvée en %f !\n", getTimer());
        printf("\tNombre de noeuds parcouru %llu\n\n", noeud);
        color(COLOR_WHITE);
        return true;
    }
    else // on avance d'une case
        indice++;

    return -1;
*/
}
/***********************************************************************************************************************
* Renvoie -1 si il y a pas de problème sinon il renvoi l'indice où une des contrainte est violée
* Par exemple si il y a deux fois le même chiffre dans la même colonne
***********************************************************************************************************************/
int checkFutoshiki(int indice) {
    // Line verification
    for(int i = indice - indice%gridSize; i < indice - indice%gridSize + gridSize; ++i) {
        if(grid[indice].value != 0 && i != indice && grid[i].value == grid[indice].value) {
            #ifdef VERBOSE
                color(COLOR_BLUE);
                for (int j = 0; j < gridSize * gridSize; ++j) {
                    if(j == i || j == indice) color(COLOR_RED);
                    if (j % gridSize == 0) printf("\n");
                    printf("\t%d", grid[j].value);
                    if(j == i || j == indice) color(COLOR_BLUE);
                }
                color(COLOR_WHITE);
                printf("\n");
                sleep(1);
            #endif /* VERBOSE */

            return i;
        }
    }

    // Column verification
    for(int i = indice%gridSize; i < gridSize*gridSize; i += gridSize) {
        if(grid[indice].value != 0 && i != indice && grid[i].value == grid[indice].value) {
            #ifdef VERBOSE
                color(COLOR_BLUE);
                for (int j = 0; j < gridSize * gridSize; ++j) {
                    if(j == i || j == indice) color(COLOR_RED);
                    if (j % gridSize == 0) printf("\n");
                    printf("\t%d", grid[j].value);
                    if(j == i || j == indice) color(COLOR_BLUE);
                }
                color(COLOR_WHITE);
                printf("\n");
                sleep(1);
            #endif /* VERBOSE */
            return i;
        }
    }

    for(int i = 0; i < tailleTabContrainte; ++i) {
        if(checkContrainte(&tabContrainte[i]) == false)
            return i;
        else
            posContrainte++;
    }

    return -1;
}

int backTrack() {
    int res = -1;
    indice = 0;

    while(res < 0) {
        res = changerValeur();

        if(res == true) {
            #ifndef DEBUG
                //clearScreen();
                printBeautifulGrid(COLOR_BLUE);
            #endif
            #ifdef DEBUG
                printBeautifulGrid(COLOR_BLUE);
                sleep(SLEEP_TIME);
            #endif /* DEBUG */
            return true;
        }
    }

    return false;
}

int backTrackNaire() {
    int res = -1;
    indice = 0;

    while(res < 0) {
        res = changerNValeur();

        if(res == true) {
            #ifndef DEBUG
                //clearScreen();
                printBeautifulGrid(COLOR_BLUE);
            #endif
            #ifdef DEBUG
                printBeautifulGrid(COLOR_BLUE);
                sleep(SLEEP_TIME);
            #endif /* DEBUG */
            return true;
        }
    }

    return false;
}

int changerDomaine() {
    if (indice == gridSize*gridSize) {
        printf("hey mais c'est bon! \n");
        /* Nous avons trouvé une solution */
        stopChrono();
        color(COLOR_GREEN);
        printf ("\tSolution trouvée en %f !\n", getTimer());
        printf("\tNombre de noeuds parcouru %llu\n\n", noeud);
        color(COLOR_WHITE);
        return true;
    }   
    else if(grid[indice].dom != NULL) {       
    int k;
      if(indice == 8){
        for(k = 0; k < gridSize * gridSize -1; ++k)
        {
          printf("Domaine de %d\n", k);     
          printDomaine(grid[k].dom);
        }
      }     

      if(grid[indice].canChange == true)
          noeud++;
      else {
          indice++;
          return -1;
      }  

      grid[indice].value = grid[indice].dom->value;
      printf("Je suis %d\n", indice);
      printf("J'ai placé la valeur %d \n", grid[indice].value);
      
      /* Pas de solution pour le moment */
      if(removeLineAndColumnDomain(indice, grid[indice].value) == false) {
      printf("retrait valeur Echec\n\n");
          // removeDomaine(grid[indice].dom, grid[indice].value);
          addLineAndColumnDomain(indice);
      }
      else {
          printf("retrait valeur bon\n\n");
          indice++;
          return -1;
      }

      if(grid[indice].dom != NULL && grid[indice].canChange == true) {
          addLineAndColumnDomain(indice);
          grid[indice].value = grid[indice].dom->value;
      }
      else {
          /* La valeur est vide, on retourne 
             à la dernière valeur que l'on peut changer */
          while(grid[indice].canChange == false) {
              indice--;
              if(indice == 0) {
                stopChrono();
                color(COLOR_RED);
                printf ("\nPas de solution en %f\n", getTimer());
                printf("Nombre de noeuds parcouru %llu\n\n", noeud);
                color(COLOR_WHITE);
                return false;   
              }
          }
          removeDomaine(grid[indice].dom, grid[indice].value);
          grid[indice].value = grid[indice].dom->value;
          noeud++;
      }                     
      return -1;  
      /* to be continued */
  }
  else {
      stopChrono();
      color(COLOR_RED);
      printf ("\nPas de solution en %f\n", getTimer());
      printf("Nombre de noeuds parcouru %llu\n\n", noeud);
      color(COLOR_WHITE);
      return false;
  } 

  return -1;
}

int forwardChecking() {
    int res = -1;
    indice = 0;

    while(res < 0) {
        res = changerDomaine();

        if(res == true) {
            #ifndef DEBUG
                //clearScreen();
                printBeautifulGrid(COLOR_BLUE);
            #endif
            #ifdef DEBUG
                printBeautifulGrid(COLOR_BLUE);
                sleep(SLEEP_TIME);
            #endif /* DEBUG */
            return true;
        }
    }
    return false;
}



/* Retourne -1 si aucune solution, dans le cas ou il existe une solution renvoie 1 */
void resolveFutoshiki(int (*f)()) {
    startChrono();
    f();
}

int main(int argc, char* argv[]) {
    if((argc - 1) != 1) {
        color(COLOR_RED);
        printf("Erreur d'argument\n");
        color(COLOR_WHITE);
        return -1;
    }

    signal(SIGINT, logOnStop);

    clearScreen();

    readGrid(argv[1]);

    resolveFutoshiki(forwardChecking);
    printf("Et c'est terminé \n");

/*
    #ifndef DEBUG
        #ifndef VERBOSE
            writeGrid("backTrack");
        #endif
    #endif

    resolveFutoshiki(forwardChecking);

    #ifndef DEBUG
        #ifndef VERBOSE
            writeGrid("forwardChecking");
        #endif
    #endif
*/

    /* Lancement de tous les tests unitaires (Avec l'option cmake DEBUG seulement) */
    #ifdef DEBUG
        printf("\n\n===> TEST UNIT\n\n");

        printf("==> TEST : checkFutoshiki()\n\n");
        // Test de la vérification de la grille
        runTestWithIntArg(checkFutoshiki, initCheckFutoTest1, -1, 0);
        runTestWithIntArg(checkFutoshiki, initCheckFutoTest2, 4, 3);
        runTestWithIntArg(checkFutoshiki, initCheckFutoTest3, gridSize, 0);
        runTestWithIntArg(checkFutoshiki, initCheckFutoTest4, -1, 0);
        runTestWithIntArg(checkFutoshiki, initCheckFutoTest5, 4*gridSize + 3, 3);
        runTestWithIntArg(checkFutoshiki, initCheckFutoTest6, gridSize*3 + 1, gridSize*3);
        runTestWithIntArg(checkFutoshiki, initCheckFutoTest7, gridSize*4 + gridSize - 2, gridSize*4 + gridSize - 1);
        runTestWithIntArg(checkFutoshiki, initCheckFutoTest8, gridSize*2, gridSize*4);

        if(gridSize == 6)
            runTestWithIntArg(checkFutoshiki, initCheckFutoTest9, -1, 15);

        printf("\n==> TEST : testContrainte()\n\n");
        // Test de la vérification des contraintes
        runTest(testContrainte, initContrainte1, false);
        runTest(testContrainte, initContrainte2, true);
        runTest(testContrainte, initContrainte3, true);
        runTest(testContrainte, initContrainte4, false);

        printf("\n===> TEST : backTrack() \n\n");
        runTest(backTrack, initBacktrackTest, true);
        runTest(backTrack, initBacktrackTest2, false);

        printf("\n===> TEST : structure domaine \n\n");

        for(int i = 0; i < 2; ++i) {
            grid[i].dom = initDomaine(grid[i].dom, i);
            printDomaine(grid[i].dom);
        }

    #endif /* DEBUG */

    return 0;
}
