//
//	File   : mainFunctions.c
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
#include <sys/time.h>

#include "../headers/main.h"
#include "../headers/mainFunctions.h"
#include "../headers/candidates.h"
#include "../headers/basicFunctions.h"
#include "../headers/rules.h"


/* Return 1 if the difference is negative, otherwise 0.  */
int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = (int)diff % 1000000;
	
    return (diff<0);
}

void solve(T_Cell grid[][GRID_SIZE], bool stepByStep) {  
	
	int unveiled=0; // Le nombre des cases non devoilés
	int oldUnveiled, counter; // un compteur
	counter=0; // initialiser le compteur a zero
	
	struct timeval tvBegin, tvEnd, tvDiff;
	
	gettimeofday(&tvBegin, NULL);
	
	while (!isSolved(grid) && counter<2) { // tanque la grille n'est pas resolue
		unveiled = unveiledCells(grid);
		oldUnveiled = unveiled; //La variable temporaire oldUnveiled prends la valeur du nombre des cases non devoilés
		
		firstRule(grid); // Appliquer la premiere regle
		
		secondRule(grid, stepByStep); // Appliquer la 2eme regle
		
		thirdRule(grid, stepByStep); // Appliquer la 3eme regle
		
		forthRule(grid); // Appliquer la 4eme regle
		
		unveiled = unveiledCells(grid); // Calculer le nombre des cases non devoilés
		
		if (unveiled==oldUnveiled) // si le nombre des cases non devoilés reste le meme
			counter++; // incrementer le compteur
		else
			counter=0; // sinon re-initialiser le compteur a zero
	}
	
	gettimeofday(&tvEnd, NULL);
	
	unveiled = unveiledCells(grid); // calculer a nouveau le nombre des cases non devoilés
	if (unveiled==0) // si le nombre des cases non devoilés egale a zero
		printf("\n\033[36mGood Work!! :\033[0mThe Grid has been solved!\n\n\n"); // Message confirme que la grille est resolue
	else { // sinon
		T_Cell oldGrid[GRID_SIZE][GRID_SIZE]; // Déclaration d'une nouvlle grille temporaire
		
		memcpy(oldGrid, grid, sizeof(T_Cell)*GRID_SIZE*GRID_SIZE); //Coupier les valeurs de la grille grid dans la grille temporaire
		printGrid(NULL,oldGrid);
		if (stepByStep==true) { // si le mode pas à pas
			char repUser; // la reponse d'utilisateur
			bool outOf = false; // pour sortir de la boucle
			// Demander l'utilisateur s'il veut continuer en mode pas à pas
			printf("Le programme doit commencer la recherche exhaustive!\n"); 
			printf("Continuer l'affichage etape par etape? [o/n]: ");
			do {
				repUser=getch();
				if (repUser=='o' || repUser=='n' || repUser=='O' || repUser=='N') { 
					outOf=true;
				}
			}while (!outOf); // tanque la reponse n'est oui n'est non
			
			if (repUser == 'o' || repUser=='O')
				forceBrute(0, 0, grid, oldGrid, 1, stepByStep); // Commencer la recherche exhaustive
				//exhaustive(grid);
			else {
				forceBrute(0, 0, grid, oldGrid, 1, false); // Commencer la recherche exhaustive
				//exhaustive(grid);
			}
		}
		else forceBrute(0, 0, grid, oldGrid, 1, stepByStep); // Commencer la recherche exhaustive
		//else exhaustive(grid);
		
		gettimeofday(&tvEnd, NULL);
		
		if (unveiledCells(grid)==0) { // si toutes les cases sont devoilés 
			clearConsole();
			printf("\n\033[36mGood Work!! :\033[0mThe Grid has been solved!\n\n\n"); // Message confirme que la grille est resolue
			if (stepByStep) printGrid(NULL, grid);
		}
		else
			printf("\n\033[36mSorry!! :\033[0mI'm not able to solve this sudoku!\n\n\n"); // Message confirme que la grille n'est pas resolue
	}
	
	if (!stepByStep) { // si l'utilisateur n'a pas choisi mode etape par etape
		printGrid(NULL, grid); // on affiche la grille apres la fin de la resolution
		// on affiche le temp du calcul
		timeval_subtract(&tvDiff, &tvEnd, &tvBegin);
		printf("Sudoku resolu en \033[41m%ld.%06ld\033[0m seconds!\n", tvDiff.tv_sec,(long int) tvDiff.tv_usec);  // l'affichage le temps du calcul
		
	}
	
	// Demander l'utilisateur s'il veux exporter les resultats dans un fichier
	printf("\nVoulez vous exporter les resultats vers un fichier ?: [o/N] ");
	char userEntry; 
	do {
		userEntry= getch();
		if (userEntry=='o' || userEntry=='O') { // l'utilisateur a choisi la reponse oui
			exportCurrentGrid(grid); // exporter la grille 'grid'
			printf("\n"); 
			exit (EXIT_SUCCESS); // sortie du programme
		}
		else if (userEntry=='n' || userEntry=='N'){ // l'utilisateur a choisi la repinse non
			printf("\n");
			exit (EXIT_SUCCESS); //sortie du programme
		}
	}while (userEntry!='n' && userEntry!='N'); // tanque la reponse different de oui et deffirent de non
}

void startNow(T_Cell grid[][GRID_SIZE]) {
	clearConsole(); // effacer l'ecran
	printf("\n\n\n\t\t\t \033[36m# Bienvenue #\033[0m\n\n\n");
	char userEntry;
	printf("Voulez vous afficher la resolution etape par etape? \033[36m[o/N]\033[0m : ");
	userEntry=getTouch();
	bool stepByStep = (userEntry=='o' || userEntry=='O'); 
	clearConsole();
	int currentChoice=1; // le choix du menu par defaut
	int userChoise; // le choix d'utilisateur
	bool outOf=false; // pour sortir de la boucle
	do {
		clearConsole(); // effacer le contenu du terminal
		if (currentChoice==1) // pour selectionner le choix courant
			printf("\n[#] \033[41mSAISIR LA GRILLE\033[0m\n");
		else
			printf("\n[ ] Saisir la grille\n");
		if (currentChoice==2)
			printf("\n[#] \033[41mCHARGER UNE GRILLE D'UN FICHIER\033[0m\n");
		else
			printf("\n[ ] Charger une grille d'un fichier\n");
		userChoise=getTouch();
		switch(userChoise) {
			case 300: { // la fonction renvoi 300 pour la touche dicretionnel haut
				if (currentChoice>1)
					currentChoice--;
				break;
			}
			case 301: { // la fonction renvoi 300 pour la touche dicretionnel bas
				if (currentChoice<2)
					currentChoice++;
				break;
			}
			default: { // l'utilisateur a choisi un choix parmi les 2 choix
				if (userChoise=='\n' || userChoise=='\r') {
					outOf=true;
				}
				break; // sortie de 'switch'
			}
		}
	} while(!outOf); // sortie de la boucle
	
	bool importFromFile = (currentChoice==2); // si le choix = 2 , importer une grille
	scanGridValues(grid,importFromFile); // scanner les valuers de la grille
	printGrid(NULL, grid); // afficher la grille avant de commencer la resolution
	solve(grid, stepByStep); // Resolue le sudoku
	
}

void exportCurrentGrid(T_Cell grid[][GRID_SIZE]) {
	printf("\nEntrer le nom du fichier ou vous voulez sauvgarder la grille: ");
	char fileName[30]; // Le nom du fichier	
	scanf("%s",fileName);
	strcat(fileName, ".sgf"); // sgf: 'Sudoku Grid File' c'est l'extension des fichiers qui contiens les grille du sudoku
	FILE * exportDestination = fopen(fileName,"w"); // ouvre le fichier en mode d'ecriture
	int line,column; // ligne et colonne pour parcourir la grille
	// Ecrire les valeurs dans le fichier
	for (line=0; line <GRID_SIZE; line++) {
		for (column=0; column<GRID_SIZE; column++ ) {
			fprintf(exportDestination, "%d ",grid[line][column].value);
		}
		fprintf(exportDestination, "\n");
	}
	fclose(exportDestination); // Fermer le fichier
	printf("Exportation success!\n"); // Afficher un message
	exit(0); // sortie de programme
	
}

void welcome(T_Cell grid[][GRID_SIZE] ) {
	
	int userChoice;
	int currentChoice=1;
	do {
		printf("\n");
		clearConsole();
		// AFFICHAGE
		printf("\n\n###########################################################\n");
		printf("###################### \033[36mSudoku-Solver\033[0m ######################\n");
		printf("###########################################################\n");
		printf("###                                                    ####\n");
		if (currentChoice==1)
			printf("### \033[41m[#] AFFICHER LES FICHIERS DISPONIBLES\033[0m              ####\n");
		else
			printf("### [ ] Afficher les fichiers disponibles              ####\n");
		printf("###                                                    ####\n");
		if (currentChoice==2)
			printf("### \033[41m[#] RESOUDRE UN SUDOKU\033[0m                             ####\n");
		else
			printf("### [ ] Resodre un Sudoku                              ####\n");
		printf("###                                                    ####\n");
		if (currentChoice==3)
			printf("### \033[41m[#] QUITTER\033[0m                                        ####\n");
		else
			printf("### [ ] Quitter                                        ####\n");
		printf("###                                                    ####\n");
		printf("###########################################################\n");
		printf("###########################################################\n");
		
		userChoice=getTouch();
		switch (userChoice) {
			case 300: {
				if (currentChoice>1)
					currentChoice--;
				break;
			}
			case 301: {
				if (currentChoice<3) 
					currentChoice++;
				break;
			}
			default: {
				if (userChoice=='\n' || userChoice=='\r') {
					switch (currentChoice) {
						case 1: { showAvailableGrids(); break; };
						case 2: startNow(grid); break;
						case 3: {
							printf("\n");
							clearConsole();
							exit(EXIT_SUCCESS);
						}
						default: break;
					}
				}
			}
		}
		
	} while (true) ;
	
}


void forceBrute (int line, int column, T_Cell grid[][GRID_SIZE], T_Cell oldGrid[][GRID_SIZE], int sense, bool stepByStep) {
	if (column>=0 && column<GRID_SIZE && line>=0 && line<GRID_SIZE) { // si le numero de la colonne inferieur a la taille de la grille
		//printf("L:%d C:%d S:%d\n",line,column,sense);
		if (oldGrid[line][column].value!=0) { // si la case courante est devoilé
			forceBrute(line, column+sense, grid, oldGrid, sense, stepByStep); //Passer a la case suivante ou la precedente
		} // end of if
		else {
			int currentCandidate = grid[line][column].value; //variable prends la valeur de la case courante 
			bool outOf = false; // Booleen permet de sortir du programme s'il = true
			do {
				if (currentCandidate<GRID_SIZE) { // Si la valeur de la case courante inferieur a 9 
					currentCandidate++; // incrementer la valeur de la variable currentCandidate
					if (addPossible(currentCandidate, grid[line][column], grid)) { // si l'ajout possible de ce candidat
						grid[line][column].value = currentCandidate ; // la valeur de la case courante prends la valeur de ce candidat
						if (stepByStep) // si l'utilisateur a choisi le mode etape par etape
							showStepByStep(grid[line][column], grid); // afficher etape par etape
						forceBrute(line, column+1, grid, oldGrid,1,stepByStep); //appliquer la recherche exhaustive pour la case suivante non devoilé
						outOf = true; // sortie de la boucle
					} // end of addPossible 
				} // end of currentCandidate<GRID_SIZE
				else { //SINON
					grid[line][column].value=0; // met la valeur de la case actuelle a zero
					forceBrute(line,column-1,grid,oldGrid,-1,stepByStep); // et appliquer la rechercher exhaustive sur la case precedente
					outOf = true; // sortie de la boucle
				}
			}while (!outOf);
		} // end of else 
	} // end of if
	else if (column < 0) { // si la colonne est negative , 
		if (line>0)
			forceBrute(line-1, GRID_SIZE-1, grid, oldGrid, -1, stepByStep); // passer a derniere case de la ligne precedente
		else
			forceBrute(0, 0, grid, oldGrid, 1, stepByStep);
	}
	else if (column>=GRID_SIZE) { // si la ligne est negative
		if (line<GRID_SIZE-1)
			forceBrute(line+1, 0, grid, oldGrid, 1, stepByStep); // passer a ligne suivante et la colonne suivante
	}
}


void exhaustive(T_Cell grid[][GRID_SIZE])
{
	int line = 0,column = 0,sense = 1,oldGrid[9][9];
	int i,j;
	for(i=0;i<GRID_SIZE;i++)
		for(j=0;j<GRID_SIZE;j++)
			oldGrid[i][j]=grid[line][column].value;
	while(true)
	{	
		if(column>=0 && column<9 && line>=0 && line<9)
		{
			if(oldGrid[line][column] !=0)
				column=column+sense;
			else
			{
				bool outOf =false;
				int currentCandidate;
				currentCandidate = grid[line][column].value;
				do
				{
					if(currentCandidate<9)
					{
						currentCandidate++;
						if(addPossible(currentCandidate, grid[line][column], grid))
						{
							grid[line][column].value = currentCandidate;
							column = column+1;
							sense = 1;
	 						outOf = true;
						}
						
					}
					else
					{
						grid[line][column].value = 0;
						column--;
						sense = -1;
						outOf = true;
					}
				}while(!outOf);
				
			}
		}
		else if(column<0 )
		{
			if(line>0)
			{
				line--;
				column = 8;
				sense = -1;
			}
			else
			{
				line = 0;
				column = 0;
				sense = 1;
			}
			
		}
		else if(column >=9)
		{
			if(line<8)	
			{
				line++;
				column = 0;
				sense = 1;
			}
			else
				break;
		}
		else
			break;			
	}
}



void showAvailableGrids(void) {

	printf("\nLes fichiers disponible: \n\n");
	system("ls -m *.sgf"); // afficher tous les fichier ont l'extension 'sgf' dans le repertoire courant
	printf("\nPress any key to continue...");
	getch();
	printf("\n");
}

// empiler
void addThisStep(T_Cell cell) {
	Steps *new = malloc(sizeof *new);
	if (new != NULL)
	{
		//memcpy(new->currentGrid, grid, sizeof(T_Cell)*GRID_SIZE*GRID_SIZE);
		new->line = cell.line;
		new->column = cell.column;
		new->precedent = stepsListe;
		stepsListe = new;
	}
}




