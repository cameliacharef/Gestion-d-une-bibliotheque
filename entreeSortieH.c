// CHAREF CAMELIA 21202057
// RINCKWALD LISA 21203107
/* fichier entreeSortieH.c */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "entreeSortieH.h"
#include "biblioH.h"

// Lit le fichier nomfic et crée une bibliothèque à partir des n premières lignes
BiblioH * charger_n_entrees_H(char * nomfic, int n){
  	char buffer[256]; 
    int i = 0;
	char auteur[256];
	char titre[256]; 
    int num;

	// Création d'une nouvelle bibliothèque
	BiblioH * biblio_h = creer_biblio_H(100); 

	// Ouverture du fichier en mode lecture
	FILE * fichier = fopen(nomfic, "r"); 
	assert(fichier != NULL); // Vérification de l'ouverture du fichier 

	while ((fgets(buffer, 256, fichier) != NULL) && (i < n)){ // Lecture de n lignes ou jusqu'à la fin du fichier
		i = i + 1;
		sscanf(buffer, " %d %s %s\n", &num, titre, auteur); 
		inserer_livre_H(biblio_h, num, titre, auteur); 
	}

	fclose(fichier);  // Fermeture du fichier
	return biblio_h;
}

//Crée un fichier contenant tous les livres de la bibliothèque
void enregistrer_biblio_H(BiblioH * biblio_h, char * nomfic){

	// Ouverture du fichier en mode écriture
	FILE * fichier = fopen(nomfic, "w"); 
	assert(fichier != NULL); // Vérification de l'ouverture du fichier

  	for (int i = 0; i < biblio_h->m; i++){ // Parcours table de hachage
        LivreH * livre = biblio_h->T[i]; 
	    
        while(livre){ // Parcours de la liste chaînée de la case i
		    fprintf(fichier, "%d %s %s\n", livre->num, livre->titre, livre->auteur); //ecriture du LivreH
		    livre = livre->suivant;
	    }
    }

	fclose(fichier); // Fermeture du fichier
}


