//
//	File   : rules.c
//  Project: Sudoku Solver
//  Version: 3
//	Author : Younes CHEIKH 
//	e-mail : younes.cheikh@gmail.com 
//  Created on 10/23/11.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../headers/main.h"
#include "../headers/basicFunctions.h"
#include "../headers/mainFunctions.h"
#include "../headers/candidates.h"
#include "../headers/rules.h"


/*
 * 1ere regle
 *  Une seule occurrence de chaque chiffre dans chaque groupe : 
 * Un candidat a` une case ne peut ˆetre qu’un chiffre non encore place
 * dans un groupe (ligne, colonne et r ́egion) qui contient cette case.
*/
 
void firstRule ( T_Cell grid[][GRID_SIZE] ) {
	T_Region currentRegion; 
	int i,line,column, currentCandidate; 
	bool presentInLine, presentInColumn, presentInRegion; // Le nombre des presences dans la ligne, colonne, et region
	for (line=0; line<GRID_SIZE; line++ ) {
		for (column = 0; column<GRID_SIZE; column++ ) {
			currentRegion = initializeRegion(grid[line][column].region); // Initialiser la region de la case courante
			for (i=0; i<GRID_SIZE; i++ ) { // parcourir la liste des candidats
				if (grid[line][column].possibleValues[i]!=0) { // si candidat possible
					currentCandidate = grid[line][column].possibleValues[i];
					presentInLine = lineContains(line, currentCandidate, grid); // verifier la presence dans la ligne
					presentInColumn=columnContains(column, currentCandidate , grid); // verifier la presence dans la colonne
					presentInRegion=regionContains(currentRegion, currentCandidate, grid); // verifier la presence dans la region
					
					if ( presentInLine || presentInColumn || presentInRegion ) { // si le candidat est present dans le groupe
						removeCandidate(currentCandidate, &grid[line][column]); // supprimer le candidat
					} // End of if present
				} // end of if candidat != 0
			} // end of for i
		} // end of for column
	} // End of for line
}

void secondRule(T_Cell grid[][GRID_SIZE],bool stepByStep) {
	int i,nbrOfCandidates,currentCandidate,line,column;
	bool showLastModified; // Vrai si l'utilisateur a choisi de retourner en arrierre
	currentCandidate = 0;
	for(line=0;line<GRID_SIZE;line++)
		for(column=0;column<GRID_SIZE;column++) {
			if (grid[line][column].value==0 ) {
				nbrOfCandidates = 0;
				i=0;
				while (nbrOfCandidates<2 && i<GRID_SIZE) { //Tanque le nombre de candidats inferieur ou egale a 1 et i<9
					if(grid[line][column].possibleValues[i]!=0) { // si le candidat acctuel diff√©rent de 0
						nbrOfCandidates++; // incrementer le nombre du candidats
						if (nbrOfCandidates==1) { // Si le nombre du candidat egale a 1
							currentCandidate = grid[line][column].possibleValues[i]; 
							//currentIndex = i; // 
						}
					}
					i++;
				}
				if (nbrOfCandidates==1) {
					grid[line][column].value = currentCandidate;
					removeCandidateFromGroup(grid[line][column], currentCandidate, grid);
					removeAllCandidates(&grid[line][column]);
					//grid[line][column].possibleValues[currentIndex] = 0;
					if (stepByStep){ // Si le mode pas a pas
						addThisStep(grid[line][column]);  // Empiler
						showLastModified=showStepByStep( grid[line][column], grid); // afficher l'etape
						if (showLastModified) { // si l'utilisateur a choisi de retourner en arriere
							Steps *tmp;// une liste temporaire
							tmp = stepsListe; // coupier la liste des etapes
							do 
							{
								if(tmp!=NULL) { // si la liste n'est pas vide
									if (tmp->precedent!=NULL) tmp = tmp->precedent; 
									showLastModified=showStepByStep( grid[tmp->line][tmp->column], grid); 
								}
							}while (showLastModified);
							tmp = NULL;
							free(tmp); // vider la memoire
						}
					}
				} /* end of if */
			}
		} /* end of for */
}

void thirdRule (T_Cell grid[][GRID_SIZE], bool stepByStep) {
	int i, line, column, currentCandidate;
	bool showLastModified = false;
	//bool presentOneTime;
	//int l,j;
	for (line=0; line < GRID_SIZE; line++ ) { // parcours de les lignes
		for (column=0; column < GRID_SIZE; column++) { // parcours de les colonnes
			if (grid[line][column].value==0) { // si la valeur de la case actuelle egale a zero
				for (i=0; i<GRID_SIZE; i++) { // parcours la liste des candidats
					if (grid[line][column].possibleValues[i]!=0 ) { // si element actuel est different de zero
						currentCandidate = grid[line][column].possibleValues[i];
						if (presentOneTimeInGroup(grid[line][column], i, grid)) { // si ce candidat est present une fois dans un groupe
							grid[line][column].value = currentCandidate;
							removeCandidateFromGroup(grid[line][column], currentCandidate, grid);
							removeAllCandidates(&grid[line][column]);
							if (stepByStep){
								addThisStep(grid[line][column]);
								showLastModified=showStepByStep( grid[line][column], grid);
								if (showLastModified) {
									Steps *tmp;// = malloc(sizeof(*tmp));
									tmp = stepsListe;
									do 
									{
										if(tmp!=NULL) {
											if (tmp->precedent!=NULL) tmp = tmp->precedent;
											showLastModified=showStepByStep( grid[tmp->line][tmp->column], grid); 
										}
									}while (showLastModified);
									tmp = NULL;
									free(tmp);
								}
							}
						}
					}
				}
			}
		} // end of for column
	} // end of for line
}


void forthRule (T_Cell grid[][GRID_SIZE]) {
	
	int line,column,i;
	for (line=0 ; line<GRID_SIZE ; line++) 
		for (column=0 ; column<GRID_SIZE; column++) 
			if (grid[line][column].value == 0) 
				for (i=0; i<GRID_SIZE; i++) 
					if (grid[line][column].possibleValues[i] != 0) {
						// si un candidat d'une case n'est pas present dans les autre ligne de la meme region
						if (!presentInOtherLines(grid[line][column].possibleValues[i], grid[line][column], grid)) 
							// Supprimer la candidate de les cases sur la meme ligne et dans les autre region
							removeFromOtherLine (grid[line][column].possibleValues[i], grid[line][column], grid);
						if (!presentInOtherColumns(grid[line][column].possibleValues[i], grid[line][column], grid))
							removeFromOtherColum (grid[line][column].possibleValues[i], grid[line][column], grid);
					}
}



