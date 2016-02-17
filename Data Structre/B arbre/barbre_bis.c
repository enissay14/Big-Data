
#include <stdlib.h>
#include <stdio.h>


# include "barbre.h"
# include "general.h"

void affiche_Barbre_Trie(p_Bnoeud x)
{
    int i;
    if (x->fils == NULL) 
        for ( i = 0; i < x->cpt ; i++)
                    printf("%d ",x->cle[i]);
    else{
        
            for ( i = 0; i < x->cpt ; i++){
                affiche_Barbre_Trie(x->fils[i]);
                printf("%d ",x->cle[i]);
                
            }
            affiche_Barbre_Trie(x->fils[x->cpt]);
            printf("\n");
    }
}

int recherche_dichotomique(int *T, int n, int val)
{
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
void predec_mont(p_Bnoeud x, int valeur){
    int k;
    int found = 0;
    if(x->pere != NULL){
        for(k = x->pere->cpt - 1; k >= 0 ; k-- ) {
            if(x->pere->cle[k] < valeur) {
                printf("predec mont Le predecesseur de %d est %d. \n",valeur, x->pere->cle[k]);
                found = 1 ;
                break ;
            }
        }
        if(found == 0) 
            predec_mont(x->pere,valeur);
    }else {
        printf("%d est la plus petite valeur. \n",valeur);
    }
}

void predec_desc(p_Bnoeud x, int valeur){
     if (x->fils != NULL){
                predec_desc(x->fils[x->cpt],valeur);
        } else {
                printf("predec descLe predecesseur de %d est %d. \n",valeur, x->cle[x->cpt -1]);
        }
}

void predecesseur(int i, p_Bnoeud x,int valeur){
    
    
        if (x->fils != NULL){
                predec_desc(x->fils[i],valeur);
        } else {
            if(i != 0) {
                printf("Le predecesseur de %d est %d. \n",valeur, x->cle[i-1]);
            }else{
                 predec_mont(x,valeur);
            }
        }
    
    
}
void successeur(int i, p_Bnoeud x,int valeur){
    
    if (x->fils == NULL){
        if(i != x->cpt - 1){
            printf("Le successeur de %d est %d. \n",valeur,x->cle[i+1]);
        }
        else{
                for(i = 0; i < x->pere->cpt ; i++){
                    if(x->pere->cle[i] > valeur ) {
                        printf("Le successeur de %d est %d. \n",valeur, x->pere->cle[i]);
                        break;
                    }
                }
                if(x->pere->pere != NULL){
                    if(x->pere->pere->cle[0] > valeur )
                        printf("Le successeur de %d est %d. \n",valeur, x->pere->pere->cle[0]);
                    else
                            predecesseur(0 , x, x->pere->pere->cle[0]);
                }
                else{
                    printf(" %d est la plus grande valeur. \n",valeur); 
                }
        }
    }
    else{
        printf("Le successeur de %d est %d. \n",valeur, x->fils[i+1]->cle[0]);
    }
}
void predec_succ(p_Bnoeud x,int valeur)
{
    
    if (recherche_val_Barbre(x, valeur) == FAUX)
            printf(" La valeur n'existe pas. \n");
    else
    {
        int i;
	if (x == NULL) printf(" erreur X == NuLL. \n");
	i = recherche_dichotomique(x->cle, x->cpt, valeur);
	if (x->cle[i] == valeur){
            
            //predecesseur
            predecesseur(i, x, valeur);
            
            //successeur
            successeur(i, x, valeur);
            
        }
	else 
		if (x->fils == NULL)
			printf(" La valeur n'existe pas. \n");
		else
			predec_succ(x->fils[i], valeur);
    }
    
}

