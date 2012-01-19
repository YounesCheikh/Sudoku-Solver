//
//	File   : main.h
//  Project: Sudoku Solver
//  Version: 3
//	Author : Younes CHEIKH 
//	e-mail : younes.cheikh@gmail.com 
//  Created on 10/23/11.
//

#ifndef MAIN_H

#define MAIN_H

#define GRID_SIZE 9 // La taille de la grille

// Type personalis√© de chaque case
typedef struct t_Cell 
{
	/* La valeur de la case */
	int value; 
	/* les cordonn√©es de la case dans la grille */
	int line;
	int column;
	/* Numero de la case dans la grille */
	int number;
	/* La region ou √ßa situe la case */
	int region;
	/* La liste des valeurs possibles pour la case courante */
	int possibleValues[9];
}T_Cell;

// Type pour chaque region dans la grille
typedef struct
{
	int number; // numero de la region
	int headLine; // Le numero de la ligne haut gauche de la region
	int headColumn; // Le numero de la colonne haut gauche de la region
}T_Region;

typedef struct steps {
	int line,column;
	struct steps *precedent;
}Steps;

Steps *stepsListe; // la pile des etapes ( utilisé pour le mode pas à pas )

//FILE * logFILE; // fichier pour les differntes sorite du programme

#endif


