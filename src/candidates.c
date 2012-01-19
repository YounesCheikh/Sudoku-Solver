//
//	File   : candidatesFunctions.c
//  Project: Sudoku Solver
//  Version: 3
//	Author : Younes CHEIKH 
//	e-mail : younes.cheikh@gmail.com 
//  Created on 10/23/11.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../headers/main.h"
#include "../headers/candidates.h"
#include "../headers/basicFunctions.h"
#include "../headers/mainFunctions.h"



void removeCandidate(int candidate, T_Cell *cell ) {
	cell->possibleValues[candidate-1] = 0; // mis la valeur du candidat a zero
}


void removeCandidateFromLine(int line, int candidate, T_Cell grid[][GRID_SIZE]) {
	int column;
	for (column = 0 ; column <GRID_SIZE ; column++ ) { // supprimer le candidate de la ligne courante
		removeCandidate(candidate, &grid[line][column]);
	}
}

void removeCandidateFromColumn(int column, int candidate, T_Cell grid[][GRID_SIZE]) {
	int line;
	for (line = 0 ; line <GRID_SIZE ; line++ ) { // supprimer le candidat de la colonne courante
		removeCandidate(candidate, &grid[line][column]);
	}
}

void removeCandidateFromRegion(T_Region region, int candidate, T_Cell grid[][GRID_SIZE]) {
	int line,column;
	// supprimer le candidat de la region courante
	for (line = region.headLine; line<region.headLine+3; line++) 
		for (column = region.headColumn ; column <region.headColumn+3; column++ ) {
			removeCandidate(candidate, &grid[line][column]);
		}
}

void removeCandidateFromGroup(T_Cell cell, int candidate, T_Cell grid[][GRID_SIZE]) {
	// initialiser la region courante
	T_Region thisRegion= initializeRegion(cell.region);
	// supprimer le candidat de ligne et la colonne et la region courantes
	removeCandidateFromLine(cell.line, candidate, grid);
	removeCandidateFromColumn(cell.column, candidate, grid);
	removeCandidateFromRegion(thisRegion, candidate, grid);
}

void removeAllCandidates(T_Cell *cell) {
	int i;
	// supprimer tous les candidats d'une case
	for(i=0;i<GRID_SIZE;i++)
		cell->possibleValues[i]=0;
}

bool isCandidate (int candidate , T_Cell cell) {
	return (cell.possibleValues[candidate-1]==candidate);
}

int nbOfPresenceInLine (int line, int candidate, T_Cell grid[][GRID_SIZE]) {
	int column, nbOfPresence;
	nbOfPresence = 0; // initialiser le nombre de presence du candidat
	for (column=0; column<GRID_SIZE; column++) 
		if (grid[line][column].possibleValues[candidate-1] != 0) // candidate-1 c'est l'indice de la case ou se trouve le candidat 
			nbOfPresence++; // incrementer le nombre de presence
	return nbOfPresence; // renvoyer le nombre de presence
}

int nbOfPresenceInColumn (int column, int candidate, T_Cell grid[][GRID_SIZE]) {
	int line, nbOfPresence;
	nbOfPresence = 0;
	for (line=0; line<GRID_SIZE; line++)
		if (grid[line][column].possibleValues[candidate-1] != 0)
			nbOfPresence++;
	return nbOfPresence;
}

int nbOfPresenceInRegion (T_Region region, int candidate, T_Cell grid[][GRID_SIZE]) {
	int line, column, nbOFPresence; 
	nbOFPresence = 0;
	for (line=region.headLine; line<region.headLine+3; line++)
		for (column=region.headColumn; column<region.headColumn+3; column++) 
			if (grid[line][column].possibleValues[candidate-1] != 0) {
				nbOFPresence++;
			}
	return nbOFPresence;
}

bool presentOneTimeInGroup (T_Cell cell,int index, T_Cell grid[][GRID_SIZE]) {
	T_Region thisRegion = initializeRegion(cell.region) ;
	bool oneTimeInLine = (nbOfPresenceInLine(cell.line, cell.possibleValues[index], grid)==1) ;
	bool oneTimeInColumn = (nbOfPresenceInColumn(cell.column, cell.possibleValues[index], grid)==1);
	bool oneTimeInRegion = (nbOfPresenceInRegion(thisRegion, cell.possibleValues[index], grid)==1);
	
	return (oneTimeInLine || oneTimeInColumn || oneTimeInRegion);
}

bool lineContains(int line, int candidate, T_Cell grid[][GRID_SIZE]) {
	int column;
	for (column=0; column <GRID_SIZE; column++) { // parcourt la line
		if (grid[line][column].value==candidate) // Si la valeur existe dans la ligne
			return (true); // envoi vrai
	}
	return (false);  // Sinon renvoi faux
}

bool columnContains(int column, int candidate, T_Cell grid[][GRID_SIZE]) {
	int line;
	for (line=0; line <GRID_SIZE; line++) { // parcourt la colonne
		if (grid[line][column].value==candidate) // Si la valeur existe dans la ligne
			return (true); // envoi vrai
	}
	return (false);  // Sinon renvoi faux
}

bool regionContains(T_Region region, int candidate, T_Cell grid[][GRID_SIZE]) {
	int line,column;
	for ( line=region.headLine; line<region.headLine+3; line++ ) { // parcourt toute la region
		for (column = region.headColumn ; column < region.headColumn+3; column++ ) { 
			if (grid[line][column].value == candidate ) // si valeur existe dans la region
				return (true); // renvoi vrai
		}
	}
	
	return (false); // si la valeur n'existe pas dans la region renvoi faux
}

bool presentInOtherLines(int candidate, T_Cell cell, T_Cell grid[][GRID_SIZE]) {
	int line,column;
	T_Region thisRegion = initializeRegion(cell.region);
	
	for (line=thisRegion.headLine; line<thisRegion.headLine+3;line++) {
		for (column = thisRegion.headColumn ; column<thisRegion.headColumn+3; column++) {
			if (line != cell.line) {
				if (grid[line][column].possibleValues[candidate-1] == candidate )
					return (true);
			}
		}
	}
	
	return (false);
}

bool presentInOtherColumns(int candidate, T_Cell cell, T_Cell grid[][GRID_SIZE]) {
	int line,column;
	T_Region thisRegion = initializeRegion(cell.region);
	
	for (line=thisRegion.headLine; line<thisRegion.headLine+3;line++) {
		for (column = thisRegion.headColumn ; column<thisRegion.headColumn+3; column++) {
			if (column != cell.column) {
				if (grid[line][column].possibleValues[candidate-1] == candidate )
					return (true);
			}
		}
	}
	
	return (false);
}

void removeFromOtherLine (int candidate, T_Cell cell, T_Cell grid[][GRID_SIZE]) {
	int column;
	T_Region thisRegion = initializeRegion(cell.region);
	for (column = 0 ; column < GRID_SIZE ; column++ ) {
		if (grid[cell.line][column].region != thisRegion.number)
			removeCandidate(candidate,&grid[cell.line][column]);
	}
}

void removeFromOtherColum (int candidate, T_Cell cell, T_Cell grid[][GRID_SIZE]) {
	int line;
	T_Region thisRegion = initializeRegion(cell.region);
	for (line = 0 ; line < GRID_SIZE ; line++ ) {
		if (grid[line][cell.column].region != thisRegion.number)
			removeCandidate(candidate,&grid[line][cell.column]);
	}
}

bool addPossible(int candidate, T_Cell cell, T_Cell grid[][GRID_SIZE]) {
	
	int line,column;
	
	//T_Region thisRegion = initializeRegion(cell.region);
	int headLine = 3*(cell.region/3); 
	int headColumn =  3*(cell.region%3);
	// La recherche dans la ligne
	for(column=0; column<GRID_SIZE; column++) 
		if (grid[cell.line][column].value==candidate)
			return (false);
	
	// la recherche dans la colonne
	for(line=0; line<GRID_SIZE ; line++) 
		if(grid[line][cell.column].value== candidate)
			return (false);
	
	// La recherche dans la region
	for (line=headLine; line<headLine+3;line++) {
		for (column=headColumn; column<headColumn+3; column++) {
			if (grid[line][column].value == candidate)
				return (false);
		}
	}
	
	//si le candidat n'est pas present dans le groupe courant , la fonction renvoi vrai 
	return (true);
}




