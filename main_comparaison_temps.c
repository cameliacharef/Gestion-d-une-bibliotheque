// CHAREF CAMELIA 21202057
// RINCKWALD LISA 21203107
/* fichier main_comparaison_temps.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "biblioLC.h"
#include "entreeSortieLC.h"
#include "biblioH.h"
#include "entreeSortieH.h"

int main(int argc, char* argv[]){

    if(argc != 3){
        printf("Il faut 2 arguments : nom_du_fichier et nb_de_lignes.\n");
        return 0;
    }
    /*Création des deux bibliothèques et comparaison de calcul*/
    printf("Calcul du temps d'exécution du chargement d'entrées entre les deux structures :\n");

    clock_t tpsInitLC;
	clock_t tpsFinLC;
	clock_t tpsInitH;
	clock_t tpsFinH;

	tpsInitLC = clock();
	Biblio *b_lc = charger_n_entrees(argv[1], atoi(argv[2]));
	tpsFinLC = clock();

	tpsInitH = clock();
	BiblioH *b_h = charger_n_entrees_H(argv[1], atoi(argv[2]));
	tpsFinH = clock();

	double tpsCpuLC1 = ((double)(tpsFinLC - tpsInitLC)) / CLOCKS_PER_SEC;
	double tpsCpuH1 = ((double)(tpsFinH - tpsInitH)) / CLOCKS_PER_SEC;
	if(tpsCpuH1 < tpsCpuLC1){
		printf("Le chargement d'entrees est plus efficace avec les tables de hachage.\n\n");
	}else{
		if (tpsCpuH1 == tpsCpuLC1 ) printf ("Le temps de chargement d'entrees est le meme .\n\n");
		else{
			printf("Le chargement d'entrees est plus efficace avec les listes simplement chainees.\n\n");
		}
		
	}


    /*Comparaison de calcul pour les recherches d'ouvrages.*/

	/*Recherche d'ouvrage par numéro existant dans la bibliotheque*/
	printf("Calcul du temps d'execution de la recherche d'ouvrage par son numero existant entre les deux structures :\n");

	tpsInitLC = clock();
	recherche_livre_num(b_lc, 2);
	tpsFinLC = clock();

	tpsInitH = clock();
	recherche_livre_num_H(b_h, 2);
	tpsFinH = clock();

	double tpsCpuLC2 = ((double)(tpsFinLC - tpsInitLC)) / CLOCKS_PER_SEC;
	double tpsCpuH2 = ((double)(tpsFinH - tpsInitH)) / CLOCKS_PER_SEC;
	if(tpsCpuH2 < tpsCpuLC2){
		printf("La recherche d'ouvrage par son numero existant est plus efficace avec les tables de hachage.\n\n");
	}else{
		if (tpsCpuH2 == tpsCpuLC2 ) printf ("Le temps de recherche d'ouvrage par son numero existant est le meme .\n\n");
		else{
			printf("La recherche d'ouvrage par son numero existant est plus efficace avec les listes simplement chainees.\n\n");
		}
		
	}

	/*Recherche d'ouvrage par numéro n'existant pas dans la bibliotheque*/
	printf("Calcul du temps d'execution de la recherche d'ouvrage par son numero n'existant pas entre les deux structures :\n");

	tpsInitLC = clock();
	recherche_livre_num(b_lc, 63969429);
	tpsFinLC = clock();

	tpsInitH = clock();
	recherche_livre_num_H(b_h, 63969429);
	tpsFinH = clock();

	double tpsCpuLC3 = ((double)(tpsFinLC - tpsInitLC)) / CLOCKS_PER_SEC;
	double tpsCpuH3 = ((double)(tpsFinH - tpsInitH)) / CLOCKS_PER_SEC;
	if(tpsCpuH3 < tpsCpuLC3){
		printf("La recherche d'ouvrage par son numero n'existant pas est plus efficace avec les tables de hachage.\n\n");
	}else{
		if (tpsCpuH3 == tpsCpuLC3 ) printf ("Le temps de recherche d'ouvrage par son numero n'existant pas est le meme .\n\n");
		else{
			printf("La recherche d'ouvrage par son numero n'existant pas est plus efficace avec les listes simplement chainees.\n\n");
		}
	}


	/*Recherche d'un ouvrage par le titre du livre existant dans la bibliothèque.*/
	printf("Calcul du temps d'execution de la recherche d'ouvrage par son titre existant entre les deux structures :\n");

	tpsInitLC = clock();
	recherche_livre_titre(b_lc, "OVHOGQ");
	tpsFinLC = clock();

	tpsInitH = clock();
	recherche_livre_titre_H(b_h, "OVHOGQ");
	tpsFinH = clock();

	double tpsCpuLC4 = ((double)(tpsFinLC - tpsInitLC)) / CLOCKS_PER_SEC;
	double tpsCpuH4 = ((double)(tpsFinH - tpsInitH)) / CLOCKS_PER_SEC;

	if(tpsCpuH4 < tpsCpuLC4){
		printf("La recherche d'ouvrage par son titre existant est plus efficace avec les tables de hachage.\n\n");
	}else{
		if (tpsCpuH4 == tpsCpuLC4 ) printf ("Le temps de recherche d'ouvrage par son titre existant est le meme .\n\n");
		else{ 
			printf("La recherche d'ouvrage par son titre existant est plus efficace avec les listes simplement chainees.\n\n");
		}
	}

	/*Recherche d'un ouvrage par le titre du livre n'existant pas dans la bibliothèque.*/
	printf("Calcul du temps d'execution de la recherche d'ouvrage par son titre n'existant pas entre les deux structures :\n");

	tpsInitLC = clock();
	recherche_livre_titre(b_lc, "Dune");
	tpsFinLC = clock();

	tpsInitH = clock();
	recherche_livre_titre_H(b_h, "Dune");
	tpsFinH = clock();

	double tpsCpuLC5 = ((double)(tpsFinLC-tpsInitLC)) / CLOCKS_PER_SEC;
	double tpsCpuH5 = ((double)(tpsFinH-tpsInitH)) / CLOCKS_PER_SEC;

	if(tpsCpuH5 < tpsCpuLC5){
		printf("La recherche d'ouvrage par son titre n'existant pas est plus efficace avec les tables de hachage.\n\n");
	}else{
		if (tpsCpuH5 == tpsCpuLC5 ) printf ("Le temps de recherche d'ouvrage par son titre n'existant pas est le meme .\n\n");
		else{ 
			printf("La recherche d'ouvrage par son titre n'existant pas est plus efficace avec les listes simplement chainees.\n\n");
		}
	}

	/*Recherche d'ouvrages par le nom d'auteur ; ces ouvrages existent */
	printf("Calcul du temps d'execution de la recherche d'ouvrages par le nom d'auteur existant entre les deux structures :\n");

	tpsInitLC = clock();
	Biblio* biblio1 = recherche_livre_auteur(b_lc, "wjndzawc");
	tpsFinLC = clock();

	tpsInitH = clock();
	BiblioH* biblio2 = recherche_livre_auteur_H(b_h, "wjndzawc");
	tpsFinH = clock();

	double tpsCpuLC6 = ((double)(tpsFinLC - tpsInitLC)) / CLOCKS_PER_SEC;
	double tpsCpuH6 = ((double)(tpsFinH - tpsInitH)) / CLOCKS_PER_SEC;

	if(tpsCpuH6 < tpsCpuLC6){
		printf("La recherche d'ouvrages par le nom d'auteur existant est plus efficace avec les tables de hachage.\n\n");
	}else{
		if (tpsCpuH6 == tpsCpuLC6 ) printf ("Le temps de recherche d'ouvrage par le nom d'auteur existant est le meme .\n\n");
		else{ 
			printf("La recherche d'ouvrages par le nom d'auteur existant est plus efficace avec les listes simplement chainees.\n\n");
		}
	}


	/*Recherche d'ouvrages par le nom d'auteur ; ces ouvrages n'existent pas dans la bibliothèque.*/
	printf("Calcul du temps d'execution de la recherche d'ouvrages par le nom d'auteur n'existant pas entre les deux structures :\n");

	tpsInitLC = clock();
	Biblio* biblio3 = recherche_livre_auteur(b_lc, "Tolkien");
	tpsFinLC = clock();

	tpsInitH = clock();
	BiblioH* biblio4 = recherche_livre_auteur_H(b_h, "Tolkien");
	tpsFinH = clock();

	double tpsCpuLC7 = ((double)(tpsFinLC - tpsInitLC)) / CLOCKS_PER_SEC;
	double tpsCpuH7 = ((double)(tpsFinH - tpsInitH)) / CLOCKS_PER_SEC;

	if(tpsCpuH7 < tpsCpuLC7){
		printf("La recherche d'ouvrages par le nom d'auteur n'existant pas est plus efficace avec les tables de hachage.\n\n");
	}else{
		if (tpsCpuH7 == tpsCpuLC7 ) printf ("Le temps de recherche d'ouvrage par le nom d'auteur n'existant pas est le meme .\n\n");
		else{
			printf("La recherche d'ouvrages par le nom d'auteur n'existant pas est plus efficace avec les listes simplement chainees.\n\n");
		}
	}

	/* Affichage des statistiques */
	printf("\n\nAffichage des statistiques:\n");

	/*Pour le chargement des bibliotheques*/
	printf("\nChargement d'une bibliotheque:\n\n");

	if ((tpsCpuLC1 != 0) && (tpsCpuH1 != 0)){
		printf("TEMPS pour ListeChainée:\n\t Chargement bibliotheque : %.10f \n",tpsCpuLC1);
		printf("TEMPS pour TableDeHachage:\n\t Chargement bibliotheque : %.10f \n",tpsCpuH1);
	}

	/* Pour une valeure presente */

	printf("\n\nPour une valeure presente dans la bibliotheque:\n\n");
	if ((tpsCpuLC4 != 0) && (tpsCpuH4 != 0) && (tpsCpuLC2 != 0) && (tpsCpuH2 != 0) && (tpsCpuLC6 != 0) && (tpsCpuH6 != 0)){
		printf("TEMPS pour ListeChainée:\n\t Recherche par titre : %.10f \n\t Recherche par numero : %.10f \n\t Recherche par auteur : %.10f \n", tpsCpuLC4, tpsCpuLC2, tpsCpuLC6);
		printf("TEMPS pour TableDeHachage:\n\t Recherche par titre : %.10f \n\t Recherche par numero : %.10f \n\t Recherche par auteur : %.10f", tpsCpuH4, tpsCpuH2, tpsCpuH6);
	}

	/*Pour une valeur absente */

	printf("\n\nPour une valeure absente de la bibliotheque:\n\n");
	if ((tpsCpuLC5 != 0) && (tpsCpuH5 != 0) && (tpsCpuLC3 != 0) && (tpsCpuH3 != 0) && (tpsCpuLC7 != 0) && (tpsCpuH7 != 0)){
		printf("TEMPS pour ListeChainée:\n\t Recherche par titre : %.10f \n\t Recherche par numero : %.10f \n\t Recherche par auteur : %.10f \n", tpsCpuLC5, tpsCpuLC3, tpsCpuLC7);
		printf("TEMPS pour TableDeHachage:\n\t Recherche par titre : %.10f \n\t Recherche par numero : %.10f \n\t Recherche par auteur : %.10f\n\n", tpsCpuH5, tpsCpuH3, tpsCpuH7);
	}



    /*Désallocation de mémoire de toutes les structures créées*/

    liberer_biblio(biblio1);
    liberer_biblio_H(biblio2);
	liberer_biblio(biblio3);
    liberer_biblio_H(biblio4);
    liberer_biblio(b_lc);
    liberer_biblio_H(b_h);
    
	
    return 0;
}

/* Taille n = 10 
Chargement d'une bibliotheque:

TEMPS pour ListeChainée:
         Chargement bibliotheque : 0.0000530000 
TEMPS pour TableDeHachage: 
         Chargement bibliotheque : 0.0000290000  x

Pour une valeure presente dans la bibliotheque:
TEMPS pour ListeChainée:
         Recherche par titre : 0.0000020000 x
         Recherche par numero : 0.0000010000 x
         Recherche par auteur : 0.0000020000 
TEMPS pour TableDeHachage:
         Recherche par titre : 0.0000030000 
         Recherche par numero : 0.0000020000 
         Recherche par auteur : 0.0000020000 x

Pour une valeure absente de la bibliotheque:
TEMPS pour ListeChainée:
         Recherche par titre : 0.0000010000 x
         Recherche par numero : 0.0000010000 x
         Recherche par auteur : 0.0000010000 
TEMPS pour TableDeHachage:
         Recherche par titre : 0.0000030000 
         Recherche par numero : 0.0000020000 
         Recherche par auteur : 0.0000010000 x

*/

/* Taille n = 100 
Chargement d'une bibliotheque:

TEMPS pour ListeChainée:
         Chargement bibliotheque : 0.0001140000 
TEMPS pour TableDeHachage:
         Chargement bibliotheque : 0.0001100000 x

Pour une valeure presente dans la bibliotheque:
TEMPS pour ListeChainée:
         Recherche par titre : 0.0000030000 x
         Recherche par numero : 0.0000020000 x
         Recherche par auteur : 0.0000020000 
TEMPS pour TableDeHachage:
         Recherche par titre : 0.0000050000 
         Recherche par numero : 0.0000040000 
         Recherche par auteur : 0.0000010000 x

Pour une valeure absente de la bibliotheque:
TEMPS pour ListeChainée:
         Recherche par titre : 0.0000010000 x
         Recherche par numero : 0.0000010000 x
         Recherche par auteur : 0.0000010000 
TEMPS pour TableDeHachage:
         Recherche par titre : 0.0000030000 
         Recherche par numero : 0.0000030000 
         Recherche par auteur : 0.0000010000 x
*/

/* Taille n = 300
Chargement d'une bibliotheque:

TEMPS pour ListeChainée:
         Chargement bibliotheque : 0.0002550000 x
TEMPS pour TableDeHachage:
         Chargement bibliotheque : 0.0003210000 

Pour une valeure presente dans la bibliotheque:
TEMPS pour ListeChainée:
         Recherche par titre : 0.0000080000 x
         Recherche par numero : 0.0000050000 x
         Recherche par auteur : 0.0000070000 
TEMPS pour TableDeHachage:
         Recherche par titre : 0.0000110000 
         Recherche par numero : 0.0000080000 
         Recherche par auteur : 0.0000020000 x

Pour une valeure absente de la bibliotheque:
TEMPS pour ListeChainée:
         Recherche par titre : 0.0000070000 x
         Recherche par numero : 0.0000050000 x
         Recherche par auteur : 0.0000060000 
TEMPS pour TableDeHachage:
         Recherche par titre : 0.0000110000 
         Recherche par numero : 0.0000090000 
         Recherche par auteur : 0.0000020000 x
*/

/* Taille n = 1000
Chargement d'une bibliotheque:

TEMPS pour ListeChainée:
         Chargement bibliotheque : 0.0007890000 x
TEMPS pour TableDeHachage:
         Chargement bibliotheque : 0.0009350000 

Pour une valeure presente dans la bibliotheque:
TEMPS pour ListeChainée:
         Recherche par titre : 0.0000190000 x
         Recherche par numero : 0.0000140000 x
         Recherche par auteur : 0.0000160000 
TEMPS pour TableDeHachage:
         Recherche par titre : 0.0000200000 
         Recherche par numero : 0.0000140000 
         Recherche par auteur : 0.0000020000 x

Pour une valeure absente de la bibliotheque:
TEMPS pour ListeChainée:
         Recherche par titre : 0.0000150000 x
         Recherche par numero : 0.0000100000 x
         Recherche par auteur : 0.0000150000 
TEMPS pour TableDeHachage:
         Recherche par titre : 0.0000210000 
         Recherche par numero : 0.0000180000 
         Recherche par auteur : 0.0000020000 x
*/


/* Taille n = 10000
Chargement d'une bibliotheque:

TEMPS pour ListeChainée:
         Chargement bibliotheque : 0.0125020000 
TEMPS pour TableDeHachage:
         Chargement bibliotheque : 0.0069590000 x


Pour une valeure presente dans la bibliotheque:

TEMPS pour ListeChainée:
         Recherche par titre : 0.0000700000 x
         Recherche par numero : 0.0001740000 x
         Recherche par auteur : 0.0000470000 
TEMPS pour TableDeHachage:
         Recherche par titre : 0.0001200000 
         Recherche par numero : 0.0006520000 
         Recherche par auteur : 0.0000020000 x

Pour une valeure absente de la bibliotheque:

TEMPS pour ListeChainée:
         Recherche par titre : 0.0000530000 x
         Recherche par numero : 0.0000930000 x
         Recherche par auteur : 0.0000380000 
TEMPS pour TableDeHachage:
         Recherche par titre : 0.0001270000 
         Recherche par numero : 0.0002080000 
         Recherche par auteur : 0.0000020000 x
*/

/* Taille = 99000
Chargement d'une bibliotheque:

TEMPS pour ListeChainée:
         Chargement bibliotheque : 0.0340750000 
TEMPS pour TableDeHachage:
         Chargement bibliotheque : 0.0271130000 x


Pour une valeure presente dans la bibliotheque:

TEMPS pour ListeChainée:
         Recherche par titre : 0.0010330000 x
         Recherche par numero : 0.0014720000 x
         Recherche par auteur : 0.0011490000 
TEMPS pour TableDeHachage:
         Recherche par titre : 0.0042130000 
         Recherche par numero : 0.0068250000 
         Recherche par auteur : 0.0000320000 x

Pour une valeure absente de la bibliotheque:

TEMPS pour ListeChainée:
         Recherche par titre : 0.0010780000 x
         Recherche par numero : 0.0012770000 x
         Recherche par auteur : 0.0009600000 
TEMPS pour TableDeHachage:
         Recherche par titre : 0.0073430000 
         Recherche par numero : 0.0091200000 
         Recherche par auteur : 0.0000910000 x
*/