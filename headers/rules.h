//
//	File   : rules.h
//  Project: Sudoku Solver
//  Version: 3
//	Author : Younes CHEIKH 
//	e-mail : younes.cheikh@gmail.com 
//  Created on 10/23/11.
//


#ifndef RULES_H

#define RULES_H

/*
 Objet: precédure applique la premiere regle : Une seule occurrence de chaque chiffre dans chaque groupe
 Données:  la grille 'grid' 
 Resultats: la liste des candidats de chaque case de la grille modifié.
 */
void firstRule ( T_Cell grid[][GRID_SIZE] ) ;

/*
 Objet: Preocédude applique la 2eme regle: : S’il n’y a qu’un candidat a une case, alors c’est cette valeur qu’il
 faut placer dans la case.
 Données: la grille 'grid', le booleen stepByStep qui vrai si l'utilisateur a choisi d'afficher la resolution etape par etape
 */
void secondRule(T_Cell grid[][GRID_SIZE],bool stepByStep) ;

/*
 Objet: Procédure applique la 3eme regle: Un candidat n’apparaissant que pour une seule case d’un groupe peut ˆetre plac ́e dans la case			correspondante.
 Données: la grille 'grid', le booleen stepByStep qui vrai si l'utilisateur a choisi d'afficher la resolution etape par etape
 */
void thirdRule (T_Cell grid[][GRID_SIZE], bool stepByStep) ;

/*
 Objet: procédure applique la 4eme regle: dans une r ́egion donn ́ee, lorsqu’un candidat n’est pr ́esent que dans des cases d’une seule					ligne, on peut supprimer ce candidat des autres cases de cette ligne (c’est a` dire des cases de la mˆeme ligne					appartenant aux 2 autres r ́egions)
 Données: la grille 'grid'
 */
void forthRule (T_Cell grid[][GRID_SIZE]);

#endif

