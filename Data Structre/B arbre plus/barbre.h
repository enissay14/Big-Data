/*
   Mihaela Juganaru-Mathieu : le 15 septembre 2015
*/

/* definitions de types pour le B-arbre et la collection des fonctions */
/* degré du B-arbre */
 
int A, B;

typedef struct Bnoeud {
		  int cpt; // nb valeurs gardées : entre 0 et 2N  
		  int *cle; // Liste des clés 
		  int *val;
		  int haut; // haut : la hauteur du noeud, 0 pour la racine
		  int des;
		  int color;
                  struct Bnoeud *frereR;
		  struct Bnoeud *frereL;
                  struct Bnoeud **fils;
		  struct Bnoeud *pere;
} Bnoeud,* p_Bnoeud; //le type Bnoeud est le type noeud même et p_BNoeud est le type pointeur de B

p_Bnoeud creation_Barbre(int val1, int val2);

int recherche_val_Barbre(p_Bnoeud x, int valeur);

void affiche_Barbre(p_Bnoeud x);

void affiche_noeud(p_Bnoeud x);

void  insertion_feuille(p_Bnoeud x, int key, int value);

void  insertion_interne(p_Bnoeud x, int key,int val, p_Bnoeud a);

void split_noeud(p_Bnoeud x,  int *m, int *mv, p_Bnoeud *aux);

void insertion_Barbre(p_Bnoeud *Bracine, int key, int value);

void successeur_predecesseur(p_Bnoeud x, int val);

void interval(p_Bnoeud x, int inf, int sup);

