//
//	File   : basicFunctions.c
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
// Les deux headers suivants sont utilisé pour la fonction getch()
#include <termios.h>
#include <unistd.h>
// cette bibliotheque importé pour savoir la taille du terminal
#include <sys/ioctl.h>

#include "../headers/main.h"
#include "../headers/basicFunctions.h"
#include "../headers/mainFunctions.h"
#include "../headers/candidates.h"
#include "../headers/rules.h"


void clearConsole() {
	struct winsize w; // la taille de la fenetre
	printf("\033[u"); // poser le curseur dans la position par defaut
	ioctl(0, TIOCGWINSZ, &w); // initialiser la taille de la fenetre
	int line, column;
	for (line=0;line<w.ws_row;line++) {
		for (column=0;column<w.ws_col;column++) {
			printf(" "); // effacer l'affichage
		}
	}
	printf("\033[u"); // revenire a la position par default
}

int getch(void) {
	
	struct termios to, t;
	
    tcgetattr (1, &t);
    to = t;
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr (1, 0, &t);
    char c;
    c=getchar () ;
    tcsetattr (1, 0, &to);
	
	return c;
}

int getTouch (void) {
	int keyUp = 300;
	int keyDown = 301;
	int keyRight = 302;
	int keyLeft = 303;
	int retVal;
	int code1,code2,code3;
	
	code1 = getch(); if (code1!=27) return code1; // si la touche differente de les 4 touches de direction
	code2 = getch(); if (code2!=91) return code2;
	code3 = getch(); 
	switch (code3) {
		case 65: {
			retVal = keyUp;
			break;
		}
		case 66: {
			retVal = keyDown;
			break;
		}
		case 67: {
			retVal = keyRight;
			break;
		}
		case 68: {
			retVal = keyLeft;
			break;
		}
		default: {
			retVal = code3;
			break;
		}	
	}
	
	return retVal;
}


void initializeGrid(T_Cell grid[][GRID_SIZE]) {
	
	int line,column;
	
	/* Rempli toutes les cases avec des zeros */
	for(line=0;line<GRID_SIZE;line++)
		for(column=0;column<GRID_SIZE;column++)
			grid[line][column].value=0;
	
	/* 
	 Stock les numeros des lignes et des colonnes dans les valeurs
	 de line et column de la chaque case
	 */
	for(line=0;line<GRID_SIZE;line++)
		for(column=0;column<GRID_SIZE;column++)
		{
			grid[line][column].line=line;
			grid[line][column].column=column;
		}
	
	/* on stock la valeur 'number' de chaque case */
	for(line=0;line<GRID_SIZE;line++)
		for(column=0;column<GRID_SIZE;column++)
			grid[line][column].number=numberOfCell(grid[line][column]);
	
	/* on stock le numero de region dans la valeur 'region' de chaque case */
	for(line=0;line<GRID_SIZE;line++)
		for(column=0;column<GRID_SIZE;column++)
			grid[line][column].region=regionOfCell(grid[line][column]);
	
	/* initialise la liste des valeurs possibles de chaque case */
	int i;
	for(line=0;line<GRID_SIZE;line++) {
		for(column=0;column<GRID_SIZE;column++) {
			for(i=0;i<GRID_SIZE;i++) {
				grid[line][column].possibleValues[i]=i+1; // la case numero 0 prends la valeur 1 ainsi de suite
			}
		}
	}
	//addThisStep(grid[0][0]); // ajouter la grille par default dans la pile
}

int regionOfCell(T_Cell cell) {
	return (3*(cell.line/3)+(cell.column/3));
}

int numberOfCell(T_Cell cell) {
	return (GRID_SIZE * cell.line + cell.column);
}

int lineOfCell(T_Cell cell) {
	return (cell.number/GRID_SIZE);
}

int columnOfCell(T_Cell cell) {
	return (cell.number%GRID_SIZE);
}

T_Region initializeRegion(int nbRegion) {
	T_Region thisRegion; // Decalaration d'une region temporaire
	thisRegion.number=nbRegion; // Numero de la region
	thisRegion.headLine = 3*(nbRegion/3); 
	thisRegion.headColumn =  3*(nbRegion%3);
	
	return (thisRegion);
}

void printGrid(T_Cell *editedCell ,T_Cell grid[][GRID_SIZE]) {
	
	int line,column;
	
	printf("\n");
	for(line=0;line<GRID_SIZE;line++)
	{
		if (line%3==0)
			printf("\n+-----------------------+\n");
		else 
			printf("\n");
		// End of if
		for(column=0;column<GRID_SIZE;column++)
		{
			if (column%3==0)
				printf("| ");
			if (editedCell  == NULL) {
				if (grid[line][column].value != 0) // si la case est devoilée
					printf("%d ",grid[line][column].value);
				else // sinon on affiche un X colorié
					printf("\033[30mX\033[0m ");
			}
			else {
				if (editedCell->line == line && editedCell->column == column ) {// si la case actuel est la case modifée
					if (grid[line][column].value != 0)
						printf("\033[41m%d\033[0m ",grid[line][column].value);
					else 
						printf("\033[41m#\033[0m ");
				}
				else {
					if (grid[line][column].value != 0)
						printf("%d ",grid[line][column].value);
					else 
						printf("\033[30mX\033[0m ");
				}
			}
			// end of if
			if (column==GRID_SIZE-1)
				printf("|");
		}
	}
	printf("\n+-----------------------+\n");
		
}


void scanGridValues(T_Cell grid[][GRID_SIZE], bool importFromFile) {
	bool outOf=false;
	int line, column;
	line = 0; column=0;
	int userChoise;
	if (!importFromFile) {
		//printf("\nSaisie les %d valeurs de la grille: ",GRID_SIZE*GRID_SIZE);
		do 
		{
			//system("clear"); // initialiser le terminal
			//printf("\033[u");
			clearConsole();
			printGrid(&grid[line][column], grid); // Afficher la grille
			printf("Entrer la valeur de la case [%d][%d]: ",line,column);
			userChoise = getTouch(); // scan la valeur
			switch (userChoise) { // pour deplacer entre les case de la grille
				case 300: { // touche UP
					if (line>0)
						line--;
					break;
				}
				case 301: { // Touche DOWN
					if (line<GRID_SIZE-1)
						line++;
					break;
				}
				case 302: { // touche RIGHT
					if (column<GRID_SIZE-1)
						column++;
					break;
				}
				case 303: { // touche LEFT
					if (column>0) 
						column--;
					break;
				}
				case '0': { // Effacer la valeur de la case acctuelle
					grid[line][column].value = userChoise-48;
					break;
				}
				default: { // les 9 valeurs possible de la case
					if (userChoise>'0' && userChoise<='9') {
						if (addPossible(userChoise-48, grid[line][column], grid))
							grid[line][column].value = userChoise-48;
						break;
					}
					else if (userChoise=='\n' || userChoise=='\r') { // resoudre la grille
						outOf = true;
						break;
					}
					else {
						outOf=false;
						break;
					}
				}
			}
		} while (!outOf);
	} // end of if no importFromFile
	else importGrid(grid);
	firstRule(grid); // Appliquer la regle 1
}

void importGrid(T_Cell grid[][GRID_SIZE]) {
	int line,column;
	char gridFileName[255];//="/Users/yc/Documents/Studies/projet_C/fini/v3/niveau4.sgf";
	FILE *gridFile;
	do {
		printf("\nLes fichiers disponible: \n\n");
		system("ls -m *.sgf");
		printf("\nSaisie le nom du fichier: ");
		scanf("%s",gridFileName);
		gridFile = fopen (gridFileName,"r");
		//gridFile = fopen ("escargot.sgf","r");
		if (gridFile==NULL) {
			strcat(gridFileName,".sgf");
			gridFile = fopen (gridFileName,"r");
			if (gridFile==NULL)
				printf("\nle fichier \033[33m%s\033[0m est introuvable!!\n",gridFileName);
			//exit(-1);
		}
	}while (gridFile==NULL);
	for(line=0;line<GRID_SIZE;line++) {
		fscanf(gridFile, "%d %d %d %d %d %d %d %d %d",&grid[line][0].value,&grid[line][1].value,&grid[line][2].value,&grid[line][3].value,&grid[line][4].value,&grid[line][5].value,&grid[line][6].value,&grid[line][7].value,&grid[line][8].value);
		for(column=0;column<GRID_SIZE;column++) 
			if (grid[line][column].value != 0 ) { // Si la valeur de la case differente de zero
				int i;
				for (i=0; i<GRID_SIZE; i++)
					grid[line][column].possibleValues[i]=0; // il ya pas des candidats pour cette case
			} // End of if
	} // End of for
	fclose(gridFile);
}

bool isSolved(T_Cell grid[][GRID_SIZE]) {
	int line,column;
	for (line = 0 ; line<GRID_SIZE; line++) {
		for (column = 0 ; column<GRID_SIZE ; column++) {
			if (grid[line][column].value==0) // si la valeur d'une case egale a zero
				return (false); // Renvoi faux
			// Sinon continue
		}
	}
	return (true);
}


bool showStepByStep( T_Cell cell, T_Cell grid[][GRID_SIZE] ) {
	bool retval; // La valeur de retour, vrai si l'utilisateur a choisi de revenir en arriere
	int currentChoice = 1; // Chaque choix dans le menu a un numero
	int userChoice; // Le choix de l'uilisateur
	bool outOf=false; // booleen permet de sortir de la boucle
	do {
		printf("\n");
		//printf("\033[u");
		clearConsole();
		//system("clear"); // Initialiser le terminal
		retval = false; // Valeur faux par default
		printGrid(&cell, grid); // Afficher la grille
		
		if (currentChoice==1) // Si le choix courant egale au numero de menu 
			printf("\033[36m[*] CONTINUER\033[0m\n"); // afficher le menu coloré
		else
			printf("[ ] Continuer\n"); // sinon affichage normal
		if (currentChoice==2)
			printf("\033[36m[*] SAUVGARDER LA GRILLE DANS UN FICHIER\033[0m\n");
		else 
			printf("[ ] Sauvgarder la grille dans un fichier\n");
		if (currentChoice==3)
			printf("\033[36m[*] REVENIRE A L'ETAPE PRECEDENTE\033[0m\n");
		else 
			printf("[ ] Revenir a l'etape precedente\n");
		if (currentChoice==4)
			printf("\033[36m[*] APPLIQUER UNE REGLE\033[0m\n");
		else
			printf("[ ] Appliquer une regle\n");
		if (currentChoice==5)
			printf("\033[36m[#] QUITTER\033[0m \n");
		else
			printf("[ ] Quiter\n");
		
		
		userChoice=getTouch(); // prend le numero de la touche qui l'utilisateur a choisi
		switch (userChoice) { //faire un switch pour le code de la touche
			case 300: { // 300 si la valeur renvoyer par la fonction getTouch() ou cas ou l'utilisateur choisi la fleche haut
				if (currentChoice>1) 
					currentChoice--;
				else
					currentChoice=5;
				break;
			}
			case 301: {
				if (currentChoice<5) 
					currentChoice++;
				else 
					currentChoice=1;
				break;
			}
			default: {
				if (userChoice=='\n' || userChoice=='\r') { // si l'utilisateur a choisi un choix
					switch (currentChoice) {
						case 1: { outOf=true; break;} // continuer
						case 2: { exportCurrentGrid(grid); break; }; // exporter la grille courante
						case 3: {outOf=true; retval=true; break;} // revenir en arriere
						case 4: { // le choix d'application une regle
							bool secondOutOf=false; // booleen permet de sortir de la boucle suivante
							printf("\n  [ Entrer le numero de la regle] : ");
							do {
								int ruleNumber; // le numero de la regle
								ruleNumber=getch(); 
								switch (ruleNumber) {
									case '1': { // regle 1
										secondOutOf = true; // sortire de boucle apres l'application de la regle
										firstRule(grid); // appliquer la regle 2
										printf("\nregle 1 applique avec succes!\ntaper une touche pour continuer... ");
										getTouch(); // attender un signal pour continue
										break;
									} // end of case '1'
									case '2': { // regle 2
										secondOutOf = true;
										secondRule(grid, false);
										printf("\nregle 2 applique avec succes!\ntaper une touche pour continuer... ");
										getTouch();
										break;
									} // end of case '2'
									case '3': { // regle 3
										secondOutOf = true;
										thirdRule(grid, false);
										printf("\nregle 3 applique avec succes!\ntaper une touche pour continuer... ");
										getTouch();
										break;
									} // end of case '3'
									case '4': { // regle 4
										secondOutOf = true;
										forthRule(grid);
										printf("\nregle 4 applique avec succes!\ntaper une touche pour continuer... ");
										getTouch();
										break;
									} // end of case '4'
									default: break;
								} // end of switch ruleNumber
							}while (!secondOutOf);
							break;} // end of case 4
						case 5: {
							printf("\n");
							exit(EXIT_SUCCESS);
						} // end of case 5
						default: break;
					} // end of currentChoice
				} // end of default
			}
		} // end of switchuserchoice
		
	} while (!outOf);
	return  retval;
}


int unveiledCells(T_Cell grid[][GRID_SIZE]) {
	int line, column;
	int counter = 0;
	for (line= 0 ; line<GRID_SIZE ; line++) 
		for(column= 0 ; column<GRID_SIZE ; column++)
			if (grid[line][column].value == 0)
				counter++;
	return counter;
}




