
/* on teste les fonction sur un B-arbre */

#include <stdlib.h>
#include <stdio.h>

# include "barbre.h"
# include "general.h"


int main(int argc, char *argv[])
{
	p_Bnoeud mon_Barbre;
	int i, valeur; 
 
	int NN = 10;

	if (argc == 1)
	{
		printf(" On doit indiqué le degré du B-arbre en paramètre. Le second paramètre est le nombre de valeur qu'on insère, par défaut 10. \n");
		exit(2);
	}

	N = atoi(argv[1]);
	if (argc >= 3)
		NN =  atoi(argv[2]);

	printf(" L'ordre de B-arbre est de %d.\n", N);
	mon_Barbre = NULL;

	printf(" indiquez les %d premières valeurs à insérer dans le B-arbre :", NN);
	for (i = 0; i < NN; i++)
	{
// 		scanf("%d", &valeur);
                valeur = i+1;
		if (mon_Barbre == NULL)
		{
			mon_Barbre = creation_Barbre(valeur);
			printf("Le premier B-arbre : "); affiche_Barbre(mon_Barbre);
		}
		else
		{
			if (recherche_val_Barbre(mon_Barbre, valeur) == VRAI)
				printf(" La valeur s'y trouve déja. \n");
			else
			{
				printf("On insère  la valeur %d.\n ", valeur );
				insertion_Barbre(&mon_Barbre, valeur);
				printf("Etat actuel B-arbre : "); affiche_Barbre(mon_Barbre);
				printf("\n");
			}
		}
	}

	printf("\n **** ARBRE final *****\n");
	affiche_Barbre(mon_Barbre);

        printf("\n **** Arbre Trie *****\n");
        affiche_Barbre_Trie(mon_Barbre);
        
        printf("\n **** Predecesseur et Successeur *****\n");
        printf(" Entrez valeur: ");
        scanf("%d", &valeur);
        
        predec_succ(mon_Barbre, valeur);
}
