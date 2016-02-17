/*
   Mihaela Juganaru-Mathieu : le 15 septembre 2015
*/

/* definitions de types pour le B-arbre et la collection des fonctions */
/* degré du B-arbre */
 
int N;

typedef struct Bnoeud
{
		  int cpt; // nb valeurs gardées : entre 0 et 2N  
		  int *cle; // Liste des clés 
		  int haut; // haut : la hauteur du noeud, 0 pour la racine
		  int des;
		  int color;
		  struct Bnoeud **fils;
		  struct Bnoeud *pere;
} Bnoeud,* p_Bnoeud; //le type Bnoeud est le type noeud même et p_BNoeud est le type pointeur de B

p_Bnoeud creation_Barbre(int valeur);

int recherche_val_Barbre(p_Bnoeud x, int valeur);

void insertion_Barbre(p_Bnoeud *x, int val);

void split_noeud(p_Bnoeud x, int *m, p_Bnoeud *aux);

void affiche_Barbre(p_Bnoeud x);

void affiche_noeud(p_Bnoeud x);

