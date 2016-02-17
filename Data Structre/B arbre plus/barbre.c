#include <stdlib.h>
#include <stdio.h>

# include "barbre.h"
# include "general.h"

p_Bnoeud creation_Barbre(int val1, int val2){
	p_Bnoeud racine;
        racine = malloc(sizeof(Bnoeud));
	racine->cpt = 1;
	racine->cle = malloc((2 * B + 1) * sizeof(int));
        racine->val = malloc((2 * B + 1) * sizeof(int));
	racine->cle[0] = val1;
        racine->val[0] = val2;
	racine->haut = 0;
        racine->frereR = NULL;
        racine->frereL = NULL;
	racine->fils = NULL;
	racine->pere = NULL;

	return racine;
}

void  affiche_noeud(p_Bnoeud x) {
	int i;
	printf("(cpt=%d | niveau = %d ||", x->cpt, x->haut);
        
        if(x->fils == NULL){
            for ( i = 0; i < x->cpt; i++)
		printf(" clé-val : %d | %d", x->cle[i], x->val[i]);
            printf(")\n");
        }else{
             for ( i = 0; i < x->cpt; i++)
		printf(" clé : %d", x->cle[i]);
             printf(")\n");
        }
	
}

void affiche_Barbre(p_Bnoeud x) {
	int i;
	affiche_noeud(x);	
   if (x->fils != NULL)
	   	for ( i = 0; i < x->cpt + 1; i++)
			affiche_Barbre(x->fils[i]);
}

int recherche_dich(int *T, int n, int val) {
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

int recherche_val_Bnoeud(p_Bnoeud x, int valeur) {
	affiche_Barbre(x);
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

int recherche_val_Barbre(p_Bnoeud x, int valeur) {
	return(recherche_val_Bnoeud(x, valeur));
}

void  insertion_feuille(p_Bnoeud x, int key, int value) {
	int k, indice; 

	printf(" Insertion dans feuille la cle %d | %d.\n", key, value);
	indice = recherche_dich(x->cle, x->cpt, key);
	for (k = x->cpt-1; k >= indice; k--)
		(x->cle)[k + 1] = (x->cle)[k];
                (x->val)[k + 1] = (x->val)[k];
	x->cle[indice] = key;
        x->val[indice] = value;
	x->cpt++;
}

void  insertion_interne(p_Bnoeud x, int key,int val, p_Bnoeud a) {
	int k, indice; 

	printf(" Insertion interne valeur %d dans le noeud : ", key);
	affiche_noeud(x);
	indice = recherche_dich(x->cle, x->cpt, key);
	for (k = x->cpt - 1; k >= indice; k--)
	{
		(x->cle)[k + 1] = (x->cle)[k];
//              (x->val)[k + 1] = (x->val)[k];
		(x->fils)[k + 2] = (x->fils)[k+1];
	}
	x->cle[indice] = key;
	x->fils[indice+1] = a;
	a->pere = x;
	x->cpt++;
}

void split_noeud(p_Bnoeud x, int *m, int *mv, p_Bnoeud *aux) {
	p_Bnoeud y;
        int i,j=0;
	y = malloc(sizeof(Bnoeud));
	y->haut = x->haut;
        
	if (x->fils == NULL) {
            y->cpt = B+1;
            *m = x->cle[B];
            *mv = x->val[B];
            y->cle = malloc((2 * B + 1) * sizeof(int));
            y->val = malloc((2 * B + 1) * sizeof(int));
            //Spécifité Barbre+
            y->cle[0] = x->cle[B];
            y->val[0] = x->val[B];
            
            for ( i = 1; i <= B ; i++) {
                
                y->cle[i] = x->cle[B + i ];
                printf("%d, %d \n",i,y->cle[i]);
                y->val[i] = x->val[B + i ];
            }
            
            y->fils = NULL;
            y->frereL = x ;
            y->frereR = NULL ;
            x->frereR = y ;
        }
	else {
            j=1;
            y->cpt = A;
            *m = x->cle[A];
            *mv = x->val[A];
            y->cle = malloc((2 * A + 1) * sizeof(int));
            
            //Spécifité Barbre+
            y->cle[0] = x->cle[A];
            
            for ( i = 1; i <= A + 1; i++)
            {
                        y->cle[i] = x->cle[A + i -1];
            }
            y->fils = malloc((2 * A + 2) * sizeof(p_Bnoeud));
            for ( i = 0; i <= A + 1; i++)
                    y->fils[i] = x->fils[A + i];
                    (y->fils[i])->pere = y; // correction de Grégoire Massot
            y->frereL = NULL ;
            y->frereR = NULL ;
	}
        y->pere = x->pere; 
        
        //Spécifité Barbre+
        if(j==0){
	x->cpt = B;
        }else{
           x->cpt = A; 
        }
	*aux = y;

	return;
}

void insertion_Barbre(p_Bnoeud *Bracine, int key, int value) {
	int i, med, medVal; 
	p_Bnoeud x, y, z;

	x = *Bracine;
	while (x->fils != NULL)
	{
		i = recherche_dich(x->cle, x->cpt, key);
		x = (x->fils)[i];
	}
	 // on sait que x->fils == NULL)
	 printf(" on traite une feuille.\n");
	 insertion_feuille(x, key, value);
	 
	 while (x->cpt > 2 * B)
	 {
		 printf(" --> on doit eclater le noeud.\n"); affiche_noeud(x);
		 split_noeud(x, &med, &medVal, &y);
		 printf(" Apres split : "); affiche_noeud(x); affiche_noeud(y);
		 if (x->pere == NULL)
		 {
			 /* on traite la racine */
			 z =  creation_Barbre(med,medVal);
			 z->fils = malloc((2 * A + 2) * sizeof(p_Bnoeud));
			 z->fils[0] = x;
			 z->fils[1] = y;
			 z->haut = x->haut + 1;
                         z->frereL = NULL ;
                         z->frereR = NULL ;
			 x->pere = z;
			 y->pere = z;
			 *Bracine = z;
			 return;
		 }
		 else
		 {
			x = x-> pere;
			insertion_interne(x, med,medVal, y);
		 }
	 }
	 return;
}

void successeur_predecesseur(p_Bnoeud x, int val){
	int i;
	int pred;
	int succ;
	
	while (x->fils != NULL)
	{
		i = recherche_dich(x->cle, x->cpt, val);
		x = (x->fils)[i];
	}
	
	i = recherche_dich(x->cle, x->cpt, val);
	if(i!=0)
	{
		pred=x->cle[i-1];
	}
	else
	{
		if (x->frereL==NULL)
		{
			pred=val;
                        printf("frere gauche null");
		}
		else
		{
			pred=x->frereL->cle[x->frereL->cpt];
		}
	}
			
	if(i!=x->cpt-1)
	{
		succ=x->cle[i+1];
	}
	else
	{
		if (x->frereR==NULL)
		{
			succ=val;
		}
		else
		{
			succ=x->frereR->cle[0];
		}
	}
	
	printf("pred : %d, succ : %d \n",pred,succ);
	
	return;
}

void interval(p_Bnoeud x, int inf, int sup){
	int i;
	while (x->fils != NULL)
	{
		i = recherche_dich(x->cle, x->cpt, inf);
		x = (x->fils)[i];
	}
	i = recherche_dich(x->cle, x->cpt, inf);
	
        printf("Interval = ");
	while(x->cle[i]<=sup)
	{
		printf("%d,",x->cle[i]);
		if (i==B)
		{
			if(x->frereR==NULL)
			{
				break;
			}
			else
			{
				x=x->frereR;
				i=0;
			}
		}
		i++;
	}
	printf("\n");
}
		
