#include <stdlib.h>
#include <stdio.h>

# include "barbre.h"
# include "general.h"

p_Bnoeud creation_Barbre(int valeur)
{
	p_Bnoeud racine;
	racine = malloc(sizeof(Bnoeud));
	racine->cpt = 1;
            racine->cle = malloc((2 * N + 1) * sizeof(int));
	racine->cle[0] = valeur;
	racine->haut = 0;
	racine->fils = NULL;
	racine->pere = NULL;

	return racine;
}


void  affiche_noeud(p_Bnoeud x){
	int i;
	printf("(cpt=%d | niveau = %d ||", x->cpt, x->haut);
	for ( i = 0; i < x->cpt; i++)
		printf(" %d", x->cle[i]);
   printf(")\n");
}
void affiche_Barbre(p_Bnoeud x){
	int i;
	affiche_noeud(x);	
        if (x->fils != NULL)
	   	for ( i = 0; i < x->cpt + 1; i++)
			affiche_Barbre(x->fils[i]);
}

int recherche_dich(int *T, int n, int val){
	int i, g, d;
	if (n == 0) return n-1;
	if (val < T[0]) return 0;
	if (val > T[n-1]) return n;
	
	for(g = 0, d = n-1; (g <= d) && g < n && d >= 0;)
	{
		i = (g + d) / 2;
		if (T[i] == val) return i;
		if (T[i] < val) 
			g = i + 1;
		else
			d = i - 1;

	}	
	return g;
}

void  insertion_feuille(p_Bnoeud x, int val){
	int k, indice; 

	printf(" Insertion dans feuille valeur %d.\n", val);
	indice = recherche_dich(x->cle, x->cpt, val);
	for (k = x->cpt; k >= indice; k--)
		(x->cle)[k + 1] = (x->cle)[k];
	x->cle[indice] = val;
	x->cpt++;
}

void  insertion_interne(p_Bnoeud x, int val, p_Bnoeud a){
	int k, indice; 

	printf(" Insertion interne valeur %d dans le noeud : ", val);
	affiche_noeud(x);
	indice = recherche_dich(x->cle, x->cpt, val);
	for (k = x->cpt - 1; k >= indice; k--)
	{
		(x->cle)[k + 1] = (x->cle)[k];
		(x->fils)[k + 2] = (x->fils)[k+1];
	}
	x->cle[indice] = val;
	x->fils[indice+1] = a;
	a-> pere = x;
	x->cpt++;
}


void split_noeud(p_Bnoeud x, int *m, p_Bnoeud *aux){
	p_Bnoeud y;
	int i;
	
	*m = x->cle[N];

	y = malloc(sizeof(Bnoeud));
	y->cpt = N;
	y->cle = malloc((2 * N + 1) * sizeof(int));
	for ( i = 0; i < N; i++)
		y->cle[i] = x->cle[N + 1 + i];
	y->haut = x->haut;
	if (x->fils == NULL)
		y->fils = NULL;
	else
	{
		 y->fils = malloc((2 * N + 2) * sizeof(p_Bnoeud));
		 for ( i = 0; i <= N; i++)
			 y->fils[i] = x->fils[N + 1 + i];
	}
	y->pere = x->pere; 
	x->cpt = N;
	*aux = y;

	return;
}

void insertion_Barbre(p_Bnoeud *Bracine, int val){
	int i, med; 
	p_Bnoeud x, y, z;

	x = *Bracine;
	while (x->fils != NULL)
	{
		i = recherche_dich(x->cle, x->cpt, val);
		x = (x->fils)[i];
	}
	 // on sait que x->fils == NULL)
	 printf(" on traite une feuille.\n");
	 insertion_feuille(x, val);
	 
	 while (x->cpt > 2 * N)
	 {
		 printf(" --> on doit eclater le noeud.\n"); affiche_noeud(x);
		 split_noeud(x, &med, &y);
		 printf(" Apres split : "); affiche_noeud(x); affiche_noeud(y);
		 if (x->pere == NULL)
		 {
			 /* on traite la racine */
			 z =  creation_Barbre(med);
			 z->fils = malloc((2 * N + 2) * sizeof(p_Bnoeud));
			 z->fils[0] = x;
			 z->fils[1] = y;
			 z->haut = x->haut + 1;
			 x->pere = z;
			 y->pere = z;
			 *Bracine = z;
			 return;
		 }
		 else
		 {
			x = x-> pere;
			insertion_interne(x, med, y);
		 }
	 }
	 return;
}


int recherche_val_Bnoeud(p_Bnoeud x, int valeur)
{
	int i;
	if (x == NULL) return FAUX;
	i = recherche_dich(x->cle, x->cpt, valeur);
	if (x->cle[i] == valeur)
	   return VRAI;
	else 
		if (x->fils == NULL)
			return FAUX;
		else
			return 	recherche_val_Bnoeud(x->fils[i], valeur);
}

int recherche_val_Barbre(p_Bnoeud x, int valeur)
{
	return(recherche_val_Bnoeud(x, valeur));
}


