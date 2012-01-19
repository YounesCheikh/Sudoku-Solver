//
//	File   : basicFunctions.h
//  Project: Sudoku Solver
//  Version: 3
//	Author : Younes CHEIKH 
//	e-mail : younes.cheikh@gmail.com 
//  Created on 10/23/11.
//


#ifndef BASICFUNCTIONS_H

#define BASICFUNCTIONS_H

/*
 procedure permet d'effacer l'ecran sans utiliser system("clear")
*/
void clearConsole();

/*
 fonction renvoi le code ascii d'une touche tapee au clavier
 l'objective de cette fonction et de permet l'utilisateur d'entrer son choix sans besoin de taper entrer 
 et sans besoin d'afficher le caractere de la touche tapee
*/
int getch(void);

/*
 fonction permet de gerer les touche de dircetion tapee par l'utilisateur
 renvoi 300 pour la touche directionnel haut
		301								bas
		302								droite
		303								gauche
 sinon le code ascii de la touche tapee
*/
int getTouch (void) ;

/*
 Objet: procédure initialise la grille et remploi les champs de chaque case avec des valeurs associes
 Données: la grille 'grid'
 */
void initializeGrid(T_Cell grid[][GRID_SIZE]) ;

/*
 Objet: fonction renvoi le numero de la region d'une case
 Données: la case 'cell'
 Resultats: numero de la region
 */
int regionOfCell(T_Cell cell) ;

/*
 Objet: fonction renvoi un entier soit le numero de la case dans la grille
 Données: la case 'cell'
 Resultats: numero de la case donnée
 */
int numberOfCell(T_Cell cell) ;

/*
 Objet: renvoi le numero de la ligne d'une case donnée
 Données: la case 'cell'
 Resultats: le numero de la ligne
 */
int lineOfCell(T_Cell cell) ;

/*
 Objet: renvoi le numero de la colonne d'une case donnée
 Données: la case 'cell'
 Resultats: le numero de la colonne
 */
int columnOfCell(T_Cell cell) ;

/*
 Objet: fonction renvoi une region initialisé avec son numero et le numero de la ligne et de la colonne de la premiere case de la region
 Données: le numero de la region (cell.number)
 Resultats: une region initialisée
 */
T_Region initializeRegion(int number) ;

/*
 Objet: procédure affiche la grille complete avec la case modifiée avec une autre couleur
 Données: la case modifée , la grille 'grid'
 */
void printGrid(T_Cell *editedCell ,T_Cell grid[][GRID_SIZE]) ;

/*
 Objet: fonction permet l'utilisateur de charger une grille apartir d'un fichier au par la saisie au clavier
 Données: la grille, et le booléen importFromFile qui s'il est vrai, le programme demande l'utilisateur de saisir le nom du fichier
 qui contient la grille, si non , il le demande le de saisir les valeur de la grille une apres l'autre
 Resultats: les valeurs données par l'utilisateur stoké dans la grille
 */
void scanGridValues(T_Cell grid[][GRID_SIZE], bool importFromFile) ;


/*
 procedure demande a l'utilisateur de taper le nom du fichier qui contient la grille non resolue de sudoku
 et place les valeurs importees dans la grille grid
 Donnees: une grille 'grid'
*/
void importGrid(T_Cell grid[][GRID_SIZE]) ;

/*
 Objet: Procédure affiche les champs d'une case (numero, ligne, colonne, region et les candidats possibles)
 Données: la case 'cell'
 */
void getInfo(T_Cell cell) ;

/*
 Objet: fonction verife si la grille est resolue ou pas
 Données: la grille
 Resultats: vrai si toutes les case sont rempli sinon renvoi faux
 */
bool isSolved(T_Cell grid[][GRID_SIZE]) ;

/*
 Objet: Procédure affiche l'etape actuelle (la case modifiée)
 Données: la grille et la case modifée
 Resultats: affiche la grille et colorier la case modifiée et attendre l'utilisateur de taper une touche pour passer
 a l'etape suivante
 */
bool showStepByStep( T_Cell cell, T_Cell grid[][GRID_SIZE] ) ;

/*
 Objet: fonction renvoi le numero des cases non devoilées
 Données: la grille
 Resultats: si toutes les cases sont dévoilées, ça renvoi 0
 */
int unveiledCells(T_Cell grid[][GRID_SIZE]);

#endif
