/* fichier main_plusieurs_exemplaires.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "biblioLC.h"
#include "entreeSortieLC.h"
#include "biblioH.h"
#include "entreeSortieH.h"

int main(int argc, char * argv[]){

    if(argc != 2){
        printf("Il faut 1 argument : nom_du_fichier.\n");
        return 0;
    }
	FILE * fichier = fopen("temps_plusieurs_exemplaires_LC_H.txt", "w");
	if (fichier == NULL){
		printf("Erreur lors de l'ouverture du fichier \n");
		return -1;
	}

    clock_t tpsInitLC;
	clock_t tpsFinLC;
	clock_t tpsInitH;
	clock_t tpsFinH;

    printf("Lance une boucle allant de 1000 a 50000 iterations : ...\n");

	for (int n = 1000; n < 50000; n++){
		Biblio * b_lc = charger_n_entrees(argv[1], n);
		BiblioH * b_h = charger_n_entrees_H(argv[1], n);


        /* Liste chainée */
		tpsInitLC = clock();
		ouvrages_multiples(b_lc);
		tpsFinLC = clock();

        /* Table de Hachage */
		tpsInitH = clock();
		plusieurs_exemplaires_H(b_h);
		tpsFinH = clock();

        double tpsCpuLC = ((double)(tpsFinLC - tpsInitLC)) / CLOCKS_PER_SEC;
	    double tpsCpuH = ((double)(tpsFinH - tpsInitH)) / CLOCKS_PER_SEC;

		fprintf(fichier, "%d %lf %lf\n", n, tpsCpuLC, tpsCpuH);
		liberer_biblio(b_lc);
		liberer_biblio_H(b_h);
	}

	printf("Boucle terminee\n");

	fclose(fichier);

	return 0;
}
	
/* Commandes pour le graphe 
    gnuplot
   >plot "temps_plusieurs_exemplaires_LC_H.txt" using 1:2 with lines title "ListeChainee"
    replot "temps_plusieurs_exemplaires_LC_H.txt" using 1:3 with lines title "TabledeHachage"
    set terminal png
    set output 'graph.png'
    replot
*/
