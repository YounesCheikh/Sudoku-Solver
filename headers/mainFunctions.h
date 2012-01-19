//
//	File   : mainFunctions.h
//  Project: Sudoku Solver
//  Version: 3
//	Author : Younes CHEIKH 
//	e-mail : younes.cheikh@gmail.com 
//  Created on 10/23/11.
//


#ifndef MAINFUNCTIONS_H

#define MAINFUNCTIONS_H

/*
 objet : procedure applique les r√®gles de la resolution une par une 
 et demande l'utilisateur d'exporter la grille resolue
 Donn√©es: la grille grid et le bool√©en stepBystep qui vrai si
 l'utilisateur a choisi d'afficher chaque modification
 de la case
 resultat: les 4 r√®gles appliqu√©es
 */
void solve(T_Cell grid[][GRID_SIZE], bool stepByStep) ;

/*
 Objet: Proc√©dure affiche les options differentes 
 Donn√©es: la grille
 */
void startNow(T_Cell grid[][GRID_SIZE]) ;

/*
 Objet : Proc√©dure export la grille acctuelle vers un fichier
 Donn√©es: La grille modifi√©
 */
void exportCurrentGrid(T_Cell grid[][GRID_SIZE]) ;

/*
 Afficher le message de bienvenue
*/
void welcome(T_Cell grid[][GRID_SIZE] ) ;

/*
 objet : Fonction recurssive cherche les valeurs possible pour les cases non devoil√©s
 Donn√©es: ligne et la colonne de la case de l'etape courante, la grille a modifi√©, une grille temporaire 'oldGrid', 
 entier 'sense' si positif la recurssivit√© avance en avant (colonne+1 ou line+1) sinon recule en arriere 
 stepByStep Qui vrai si l'utilisateur a choisi le mode etape par etape
 */
void forceBrute (int line, int column, T_Cell grid[][GRID_SIZE], T_Cell oldGrid[][GRID_SIZE], int sense, bool stepByStep);

/*
 la meme procedure comme forceBrute sans utiliser la recursivite
*/
void exhaustive(T_Cell grid[][GRID_SIZE]);

/*
 * Procedure affiche les fichiers des grilles pour un sudoku
*/
void showAvailableGrids() ;

/*
 procdure pour empiler la pile stepsListe avec la ligne et la colonne de la case cell
 Donnees: une case
*/
void addThisStep(T_Cell cell)  ;


#endif

