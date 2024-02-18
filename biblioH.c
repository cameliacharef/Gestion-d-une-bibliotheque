/* fichier biblioH.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "biblioH.h"


// Retourne une clé à partir de la somme des valeurs ASCII des caractères du nom de l'auteur
int fonctionClef(char * auteur){
    int somme = 0;
    int i = 0;

    if (auteur != NULL){

        while(auteur[i] != '\0'){
            somme += (int)auteur[i];
            i++;
        }
        return somme;

    }

    return -1; //retourne -1 en cas de pointeur null 
}

// Crée un livre à partir d'un numéro, d'un titre et du nom d'un auteur
LivreH * creer_livre_H(int num, char * titre, char * auteur){
    LivreH * livre_h = (LivreH *)malloc(sizeof(LivreH));

    if (livre_h == NULL){
		return NULL;
	}

    livre_h->clef = fonctionClef(auteur);
    livre_h->num = num;
    livre_h->titre = strdup(titre);
    livre_h->auteur = strdup(auteur);
    livre_h->suivant = NULL;

    return livre_h;
}

// Désalloue l'espace mémoire dédié au livre
void liberer_livre_H(LivreH * livre_h){

    if(livre_h != NULL){
        free(livre_h->titre);
        free(livre_h->auteur);
        free(livre_h);
    }
}

// Crée une bibliothèque vide de taille m
BiblioH * creer_biblio_H(int m){

    BiblioH * biblio_h = (BiblioH *)malloc(sizeof(BiblioH));

    biblio_h->nE = 0; // Nombre d'éléments initialisé à 0
    biblio_h->m = m;
    biblio_h->T = NULL;

    biblio_h->T = (LivreH **)(malloc(sizeof(LivreH * ) * m));

	// Initialisation des pointeurs de chaque case du tableau à NULL
	for (int i = 0; i < biblio_h->m; i++){
        biblio_h->T[i] = NULL;
    }

    return biblio_h;
}

// Désalloue l'espace mémoire dédié à la bibliothèque
void liberer_biblio_H(BiblioH * biblio_h){
    if(biblio_h != NULL){

        for (int i = 0; i < biblio_h->m; i++){
            LivreH * ptr = biblio_h->T[i];

			// Parcours de la liste chainée pour la case i
            while(ptr){
                ptr = biblio_h->T[i]->suivant;
			    liberer_livre_H(biblio_h->T[i]);
			    biblio_h->T[i] = ptr;
            }

        }

        free(biblio_h->T);
        free(biblio_h);

    }
}

// Transforme la clé en un entier entre 0 et m inclus, utilisable par la table de hachage
int fonctionHachage(int cle, int m){
	double A = ( (sqrt(5) - 1.0) / (double)2.0 );
	int inf_kA = floor(cle * A);
	double kA = cle * A;
	double result = m * (kA - inf_kA);

	return floor(result);
}

// Crée un livre à partir du numéro, du titre et du nom de l'auteur puis l'ajoute dans la bibliothèque
void inserer_livre_H(BiblioH* biblio_h, int num, char * titre, char * auteur){
    if (biblio_h == NULL) {
        return;
    }
    // Créer le livre à insérer
    LivreH * livre = creer_livre_H(num, titre, auteur);

    if (livre == NULL) {
        return; // Échec de la création du livre
    }

    int position = fonctionHachage(livre->clef, biblio_h->m);
    
    // Insérer le livre en tête de la liste chaînée correspondante
    livre->suivant = (biblio_h->T)[position];
	(biblio_h->T)[position] = livre;
	biblio_h->nE = biblio_h->nE + 1;
}

// Affiche la clé, le numéro, le titre et le nom de l'auteur du livre
void afficher_livre_H(LivreH * livre_h){
	if (livre_h != NULL){
		printf("Clef : %d Numero : %d %s %s\n", livre_h->clef, livre_h->num, livre_h->titre, livre_h->auteur);
	}
}

// Affiche tous les livres constituant la bibliothèque
void afficher_biblio_H(BiblioH * biblio_h){

	for (int i = 0; i < biblio_h->m; i++){
		LivreH * livre = biblio_h->T[i];

		while (livre){
			afficher_livre_H(livre);
			livre = livre->suivant;
		}
	}
}

// Recherche un livre par son numéro et le retourne
LivreH * recherche_livre_num_H(BiblioH * biblio_h, int num){
	LivreH * livre = NULL;

	for (int i = 0; i < biblio_h->m ; i++){
		livre = biblio_h->T[i];

		while (livre != NULL){
			if (livre->num == num){	 // Si le numéro du livre correspond à celui recherché	
                return livre;
			}
		    livre = livre->suivant;
		}
	}
	return NULL;
}

// Recherche un livre par son titre et le retourne
LivreH * recherche_livre_titre_H(BiblioH * biblio_h, char * titre){
	LivreH * livre = NULL;

	for (int i = 0; i < biblio_h->m; i++){
		livre = biblio_h->T[i];
		while (livre != NULL){
			if (strcmp(livre->titre, titre) == 0){ // Si le titre du livre correspond à celui recherché
				return livre;
            }
			livre = livre->suivant;
      	}
	}
	return NULL;
}

// Recherche tous les livres d'un même auteur et retourne une nouvelle bibliothèque
BiblioH * recherche_livre_auteur_H(BiblioH * biblio_h, char * auteur){
	BiblioH * new_biblio_h = creer_biblio_H(biblio_h->m);

	int cle = fonctionClef(auteur);
	int position = fonctionHachage(cle, biblio_h->m);

	LivreH * livre = biblio_h->T[position];

	while (livre != NULL){
		if (strcmp(livre->auteur, auteur) == 0){ // Si l'auteur du livre correspond à celui recherché
			inserer_livre_H(new_biblio_h, livre->num, livre->titre, livre->auteur); // Inserer le livre dans nouvelle biblio
		}
		livre = livre->suivant;
	}

	return new_biblio_h;
}

// Supprime un livre de la bibliothèque
void suppression_ouvrage_H(BiblioH * biblio_h, int num, char * auteur, char * titre){
	int cle = fonctionClef(auteur);
	int position = fonctionHachage(cle, biblio_h->m);
	LivreH * livre = biblio_h->T[position];
	LivreH * predecesseur = NULL;

	//La fonction ne fait rien si la bibliothèque est vide
    if(biblio_h == NULL){
        return;
    }
	while ((livre != NULL) && ((livre->num != num) || (strcmp(livre->auteur, auteur) != 0) || (strcmp(livre->titre, titre) != 0))){
		predecesseur = livre;
		livre = livre->suivant;
	}

	if (livre != NULL){
		if (predecesseur != NULL){
			predecesseur->suivant = livre->suivant;
		}
        else {
			predecesseur = livre->suivant;
			biblio_h->T[position] = predecesseur;
		}
		biblio_h->nE = (biblio_h->nE)-1;
		liberer_livre_H(livre);

	}
}

// Fusionne deux bibliothèques
BiblioH * fusion_biblio_H(BiblioH * biblio_h1, BiblioH * biblio_h2){

	for (int i = 0; i < biblio_h2->m; i++){

		LivreH * livre = biblio_h2->T[i];

		while (livre != NULL){
			inserer_livre_H(biblio_h1, livre->num, livre->titre, livre->auteur);
			livre = livre->suivant;
		}
	}

	liberer_biblio_H(biblio_h2);
	return biblio_h1;
}

// Rechercher tous les libvres identiques et les mettre dans une bibliotheque 
BiblioH * plusieurs_exemplaires_H(BiblioH * biblio_h){
	int i;
	BiblioH * resultat = creer_biblio_H(biblio_h->m);
	for(i = 0; i < biblio_h->m; i++){
		plusieurs_exemplaires_i(biblio_h, resultat, i);
	}
	return resultat;
}

/* Retourne 1 si les deux livres sont identiques */
int livres_identiques_H(LivreH * livre_h1, LivreH * livre_h2)
{
	if((strcmp(livre_h1->auteur, livre_h2->auteur) == 0) && (strcmp(livre_h1->titre, livre_h2->titre) == 0)){
		return 1;
	}
	return 0;
}

/* Rechercher les livres identiques en position i de la bibliotehque */
void plusieurs_exemplaires_i(BiblioH * biblio_h, BiblioH * resultat, int i){
	LivreH * parc1 = (biblio_h->T)[i]; //parcours premiere boucle
	LivreH * parc2; //parcours de deuxième boucle
	LivreH * prec = parc1; //Element précédent 
	LivreH * tete = parc1;; //la tête de liste
	int doublon; //detection d'un doublon

	if( (parc1 == NULL) || (parc1->suivant == NULL) ){
		return;
	}

	(biblio_h->T)[i] = NULL;

	//premiere boucle
	while(parc1){
		inserer_livre_H(biblio_h, parc1->num, parc1->titre, parc1->auteur); //copie de l'élément en cours
		parc2 = tete;
		doublon = 0; //initialise a 0 a chaque nouvel élément testé
		
		//deuxieme boucle
		while(parc2){
			if((livres_identiques_H(parc1, parc2)) && (parc1 != parc2)){ //identiques mais pas la même instance
				//on a trouvé un livre identique a l'élément testé (parc1)
				doublon = 1;
				break;
			}
			parc2 = parc2->suivant;
		}
		
		if(!doublon){ //si pas de doublon on passe a la suppression de l'élément

			if(parc1 == tete){ //élément a supr en tête 
				tete = parc1->suivant; 
				liberer_livre_H(parc1);
				parc1 = tete; 
			}
			else
			{
				prec->suivant = parc1->suivant; //suppression élément pas en tête
				liberer_livre_H(parc1);
				parc1 = prec->suivant; 
			}
		}
		else
		{
			prec = parc1;
			parc1 = parc1->suivant; 
		}
		
	}
	resultat->T[i] = tete;
	return;	
}
