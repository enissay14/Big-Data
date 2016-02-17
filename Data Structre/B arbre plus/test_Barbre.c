
/* on teste les fonction sur un B-arbre */

#include <stdlib.h>
#include <stdio.h>

# include "barbre.h"
# include "general.h"


int main(int argc, char *argv[])
{
	p_Bnoeud mon_Barbre;
	int i;
        int key;
        int value;
 
	int NN = 10;

	if (argc == 1)
	{
		printf(" On doit indiqué les degrés du B+-arbre en paramètre. Le troisième paramètre est le nombre de valeur qu'on insère, par défaut 10. \n");
		exit(2);
	}

	B = atoi(argv[2]);
        A = atoi(argv[1]);
	if (argc >= 4)
		NN =  atoi(argv[3]);

	printf(" L'ordre de B+-arbre est de %d - %d.\n", A, B);
	mon_Barbre = NULL;

	printf(" indiquez la cle et la valeur à insérer dans le B+-arbre : ");
	for (i = 0; i < NN; i++)
	{
		printf("\n");
                scanf("%d", &key);
// 		scanf("%d", &value);
                value = key;
                if (mon_Barbre == NULL)
		{
			mon_Barbre = creation_Barbre(key,value);
			printf("Le premier B-arbre : "); affiche_Barbre(mon_Barbre);
		}
		else
		{
			if (recherche_val_Barbre(mon_Barbre, key) == VRAI)
				printf(" La cle s'y trouve déja. \n");
			else
			{
				printf("On insère  la cle %d valeur %d.\n ", key , value);
                                insertion_Barbre(&mon_Barbre, key, value);
				printf("Etat actuel B-arbre : "); affiche_Barbre(mon_Barbre);
				printf("\n");
			}
		}
	}

        printf("\n **** Predecesseur et Successeur *****\n");
        int valeur;
        printf(" Entrez valeur: ");
        scanf("%d", &valeur);
        
        successeur_predecesseur(mon_Barbre, valeur);
        
        printf("\n **** Interval *****\n");
        int inf,sup;
        printf(" Entrez valeur inf: ");
        scanf("%d", &inf);
        printf(" Entrez valeur inf: ");
        scanf("%d", &sup);
        
        interval(mon_Barbre, inf,sup);
    
}
