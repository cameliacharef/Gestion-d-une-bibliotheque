// CHAREF CAMELIA 21202057
// RINCKWALD LISA 21203107
/* fichier entreeSortieLC.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "biblioLC.h"
#include "entreeSortieLC.h"

// Lit le fichier nomfic et crée une bibliothèque à partir des n premières lignes
Biblio * charger_n_entrees(char * nomfic, int n){

    // Création d'une nouvelle bibliothèque
    Biblio * biblio = creer_biblio();

    // Ouverture du fichier en mode lecture
    FILE * fichier = fopen(nomfic, "r");
    assert(fichier != NULL); // Vérification de l'ouverture du fichier 

    char buffer[256];
    int num;
    char titre[256];
    char auteur[256];

    int cpt = 0;
    
    // Lecture du fichier ligne par ligne
    while (fgets(buffer, 256, fichier)){
        if (cpt >= n) // Arrêt de la lecture lorsque n lignes ont été lues
            break;
            
        sscanf(buffer, "%d %s %s", &num, titre, auteur);
        inserer_en_tete(biblio, num, titre, auteur);

        cpt++;
    }

    fclose(fichier); // Fermeture du fichier
    return biblio;
}


// Crée un fichier contenant tous les livres de la bibliothèque
void enregistrer_biblio(Biblio * biblio, char * nomfic) {
    
    // Ouverture du fichier en mode écriture
    FILE * fichier = fopen(nomfic, "w"); 
    assert(fichier != NULL); // Vérification de l'ouverture du fichier
    
    Livre * tmp = biblio->L;

    // Parcours de la bibliothèque et écriture des données dans le fichier
    while (tmp){
        fprintf(fichier, "%d %s %s", tmp->num, tmp->titre, tmp->auteur);
        tmp = tmp->suiv;
    }
    fclose(fichier); // Fermeture du fichier
}

