//
//	File   : main.c
//  Project: Sudoku Solver
//  Version: 3
//	Author : Younes CHEIKH 
//	e-mail : younes.cheikh@gmail.com 
//  Created on 10/23/11.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../headers/main.h"
#include "../headers/basicFunctions.h"
#include "../headers/mainFunctions.h"


int main (int argc, const char * argv[])
{
	system("clear");
	printf("\033[s"); // stocker la position acctuelle du curseur
	stepsListe = NULL; // initialiser la liste des etapes
	
	T_Cell myGrid[GRID_SIZE][GRID_SIZE];
	
	// L'initialisation de la grille
	initializeGrid(myGrid);
	
	if (argc==1) welcome(myGrid); // demarrer l'affichage du menu
	else 
	{
		FILE* gridFile;
		gridFile=fopen(argv[1], "r");
		if (gridFile==NULL) {
			printf("\nErreur %d: Le fichier '%s' est introuvable!\n",errno, argv[1]);
			exit(EXIT_FAILURE);
		}
		
		int line,column;
		for(line=0;line<GRID_SIZE;line++){
			fscanf(gridFile, "%d %d %d %d %d %d %d %d %d",&myGrid[line][0].value,&myGrid[line][1].value,&myGrid[line][2].value,&myGrid[line][3].value,&myGrid[line][4].value,&myGrid[line][5].value,&myGrid[line][6].value,&myGrid[line][7].value,&myGrid[line][8].value);
			for (column=0; column<GRID_SIZE;column++)
				if (myGrid[line][column].value != 0 ) { // Si la valeur de la case differente de zero
					int i;
					for (i=0; i<GRID_SIZE; i++)
						myGrid[line][column].possibleValues[i]=0; // il ya pas des candidats pour cette case
				} // End of if
		} // End of for
		fclose(gridFile);
		solve(myGrid, false);
	}
	
    return 0;
}

