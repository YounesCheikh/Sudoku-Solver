//
//	File   : candidatesFunctions.h
//  Project: Sudoku Solver
//  Version: 3
//	Author : Younes CHEIKH 
//	e-mail : younes.cheikh@gmail.com 
//  Created on 10/23/11.
//


#ifndef CANDIDATESFUNCTIONS_H

#define CANDIDATESFUNCTIONS_H


/*
 Objet: Supprime un candidat d'une liste du candidat d'une case selectionn√©
 Donn√©es:le candidat a supprimer et le pointeur de la case
 */
void removeCandidate(int candidate, T_Cell *cell ) ;

/*
 Objet: Supprime un candidat d'une ligne
 Donn√©es: le numero de la ligne d'ou on va supprimer le candidat
 le candidat qu'on veux supprimer
 la grille grid
 */
void removeCandidateFromLine(int line, int candidate, T_Cell grid[][GRID_SIZE]) ;

/*
 Objet: Supprime un candidat d'une colonne
 Donn√©es: le numero de la colonne d'ou on va supprimer le candidat
 le candidat qu'on veux supprimer
 la grille grid
 */
void removeCandidateFromColumn(int column, int candidate, T_Cell grid[][GRID_SIZE]) ;

/*
 Objet: Supprime un candidat d'une region
 Donn√©es: la region d'ou on va supprimer le candidat
 le candidat qu'on veux supprimer
 la grille grid
 */
void removeCandidateFromRegion(T_Region region, int candidate, T_Cell grid[][GRID_SIZE]) ;

/*
 Objet: Supprime un candidate d'un group (ligne, colonne, colonne) d'une case
 Donn√©es: la cellule ou se trouve ce candidat
 le candidat qu'on veux supprimer
 la grille 'grid'
 */
void removeCandidateFromGroup(T_Cell cell, int candidate, T_Cell grid[][GRID_SIZE]) ;

/*
 Objet: supprime touts les candidats d'une case 
 Donn√©es: la case cell
 */
void removeAllCandidates(T_Cell *cell) ;

/*
 Objet: Fonction renvoi le nombre de presence d'un candidat dans une ligne
 Donn√©es: la ligne ou on va chercher le candidat
 le candidat
 la grille
 resultat: le nombre de presence d'un candidat dans une ligne
 */
int nbOfPresenceInLine (int line, int candidate, T_Cell grid[][GRID_SIZE]) ;

/*
 Objet: Fonction renvoi le nombre de presence d'un candidat dans une colonne
 Donn√©es: le numero de la colonne ou on va chercher le candidat
 le candidat
 la grille
 Resultats: le nombre de presence d'un candidat dans une colonne
 */
int nbOfPresenceInColumn (int column, int candidate, T_Cell grid[][GRID_SIZE]);

/*
 Objet: Fonction renvoi le nombre de presence d'un candidat dans une region
 Donn√©es: la region ou on va chercher le candidat
 le candidat
 la grille
 Resultats: le nombre de presence d'un candidat dans une region
 */
int nbOfPresenceInRegion (T_Region region, int candidate, T_Cell grid[][GRID_SIZE]) ;

/*
 Objet: Fonction cherche si un candidat est present au moins une fois dans une ligne ou pas
 dans un groupe (ligne, colonne, region)
 Donn√©es: la region ou on va chercher le candidat
 le candidat
 la grille
 Resultats: renvoi vrai si un candidat est present aumoins une fois dans un groupe
 */
bool presentOneTimeInGroup (T_Cell cell,int index, T_Cell grid[][GRID_SIZE]) ;

/*
 Objet: fonction recherche si un candidat est present dans un ligne ou pas
 Donn√©es:   la ligne ou on va chercher
 le candidat
 la grille
 Resultats: renvoi si la ligne qu'a le numero line contient le candidat 'candidate'
 */
bool lineContains(int line, int candidate, T_Cell grid[][GRID_SIZE]) ;

/*
 Objet: fonction recherche si un candidat est present dans un colonne ou pas
 Donn√©es:   la colonne ou on va chercher
 le candidat
 la grille
 Resultats: renvoi si la colonne qu'a le numero line contient le candidat 'candidate'
 */
bool columnContains(int column, int candidate, T_Cell grid[][GRID_SIZE]);

/*
 Objet: fonction recherche si un candidat est present dans une region ou pas
 Donn√©es: ->la region ou on va chercher
 ->le candidat
 ->la grille
 Resultats:
 */
bool regionContains(T_Region region, int candidate, T_Cell grid[][GRID_SIZE]);

/*
 Objet: consulter si un candidat d'une case est present dans les autres 2 lignes de la meme region
 Donn√©es: candidat, la case, la grille
 Resultats: vrai s'il existe ce candidat dans les autres 2 lignes de la region
 */
bool presentInOtherLines(int candidate, T_Cell cell, T_Cell grid[][GRID_SIZE]);

/*
 Objet: consulter si un candidat d'une case est present dans les autres 2 colonne de la meme region
 Donn√©es: candidat, la case, la grille
 Resultats: vrai s'il existe ce candidat dans les autres 2 colonne de la region
 */
bool presentInOtherColumns(int candidate, T_Cell cell, T_Cell grid[][GRID_SIZE]);

/*
 Objet: supprimer un candidat d'une case de toute les cases de la meme ligne qui sont pas dans la region courante
 Donn√©es: candidat, la case, la grille
 */
void removeFromOtherLine (int candidate, T_Cell cell, T_Cell grid[][GRID_SIZE]) ;

/*
 Objet: supprimer un candidat d'une case de toute les cases de la meme colonne qui sont pas dans la region courante
 Donn√©es: candidat, la case, la grille
 */
void removeFromOtherColum (int candidate, T_Cell cell, T_Cell grid[][GRID_SIZE]);

/*
 Objet: fonction verife si un candidat est present dans un groupe ou pas
 Donn√©es: le candidat, la case ou on veux ajouter ce candidat,  la grille
 Resultats: vrai si le groupe de la case cell ne contient pas la valeur du candidat
 */
bool addPossible(int candidate, T_Cell cell, T_Cell grid[][GRID_SIZE]);

#endif
