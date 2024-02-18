// CHAREF CAMELIA 21202057
// RINCKWALD LISA 21203107
/* fichier main.c */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "biblioLC.h"
#include "entreeSortieLC.h"
#include "biblioH.h"
#include "entreeSortieH.h"



void menu()
{
/*Affichage du menu*/
	printf("Actions possibles sur la bibliothèque : \n");
	printf(" - 0 : Quitter le programme\n");
	printf(" - 1 : Affichage\n");
	printf(" - 2 : Insertion d'ouvrage\n");
	printf(" - 3 : suppression d'ouvrage\n");
	printf(" - 4 : recherche par titre\n");
	printf(" - 5 : recherche par numero\n");
	printf(" - 6 : recherche par auteur\n");
	printf(" - 7 : recherche ouvrages à plusieurs exemplaires\n");
	printf(" - 8 : fusion de deux bibliotheques\n");
}

int main(int argc, char* argv[] )
{
    if(argc != 3){
        printf("Il faut 2 arguments : nom_du_fichier et nb_de_lignes.\n");
        return 0;
    }

	/* Création des deux bibliothèques */
    
	Biblio *b_lc = charger_n_entrees(argv[1], atoi(argv[2]));
	
	BiblioH *b_h = charger_n_entrees_H(argv[1], atoi(argv[2]));


	/*Instructions à l'utilisateur, choix des actions et structures et exécutions des actions choisies*/
	int stop = 1;
	char buffer[256];
	char nom_livre[256];
	char nom_auteur[256];
	int num;
	int type;
	
	while(stop)
	{
		printf("Choisir le type :\n 1 - Liste chainée\n 2 - Table de hachage\n");
		fgets(buffer, sizeof(int), stdin);
		type = atoi(buffer);
		switch(type){
			case 1:
				menu();
				printf("saisir l'action a effectuer.\n");
				fgets(buffer, sizeof(int), stdin);
				stop = atoi(buffer);

				switch(stop)
				{
				case 0:
					// Quitter le programme
					printf("Merci et au revoir\n");
					break;
				case 1:
					// Affichage biblo
					afficher_biblio(b_lc);
					break;
				case 2:
					// inserer en tete livre 
					printf("Entrez un nom de livre, un nom d'auteur et un numéro\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer, "%s %s %d", nom_livre, nom_auteur, &num);
					inserer_en_tete(b_lc, num, nom_livre, nom_auteur);
					printf("Ajout fait\n");
					break;
				case 3:
					// supprimer un livre 
					printf("Entrez un nom de livre, un nom d'auteur et un numéro\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer, "%s %s %d", nom_livre, nom_auteur, &num);
					supprimer_livre_biblio(b_lc, num, nom_livre, nom_auteur);
					printf("Suppression terminée\n");
					break;
				case 4:
					// Afficher livre recherché par son nom 
					printf("Entrez un nom de livre\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer, "%s", nom_livre);
					printf("Les livres sont:\n");
					afficher_livre(recherche_livre_titre(b_lc, nom_livre));
					break;

				case 5:
					// Afficher livre recherché par son numero
					printf("Entrez un numero de livre\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer, "%d", &num);
					printf("Les livres sont:\n");
					afficher_livre(recherche_livre_num(b_lc, num));
					break;

				case 6:
					// Afficher biblio des livres de meme auteur 
					printf("Entrez un nom d'auteur\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer, "%s", nom_auteur);
					printf("Les livres sont:\n");
					Biblio * blc_auteur=recherche_livre_auteur(b_lc, nom_auteur);
					afficher_biblio(blc_auteur);
					liberer_biblio(blc_auteur);
					break;
				case 7:
					afficher_biblio(ouvrages_multiples(b_lc));
					break;
				case 8:
					// Fusionner deux bibliothèques
					char f1[50]; char f2[50];
					printf("Entrez deux fichiers contenant chacun une bibliotheque.\n");
					scanf("%s %s", f1, f2);
					// Initialisation des biblios 
					Biblio * b1 = charger_n_entrees(f1, 50);
					Biblio * b2 = charger_n_entrees(f2, 50);

					fusion_biblio(b1,b2);
					afficher_biblio(b1);
					liberer_biblio(b1);
					break;
				}
				break;
				

			case 2:
				menu();
				printf("saisir l'action a effectuer.\n");
				fgets(buffer, sizeof(int), stdin);
				stop = atoi(buffer);
				switch(stop)
				{
				case 0:
					// Quitter le programme
					printf("Merci et au revoir\n");
					break;
				case 1:
					// Affichage biblo
					afficher_biblio_H(b_h);
					break;
				case 2:
					// inserer en tete livre
					printf("Entrez un nom de livre, un nom d'auteur et un numéro\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer, "%s %s %d", nom_livre, nom_auteur, &num);
					inserer_livre_H(b_h, num, nom_livre, nom_auteur);
					printf("Ajout fait\n");
					break;
				case 3:
					// supprimer un livre 
					printf("Entrez un nom de livre, un nom d'auteur et un numéro\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer, "%s %s %d", nom_livre, nom_auteur, &num);
					suppression_ouvrage_H(b_h,num, nom_livre, nom_auteur);
					printf("Suppression terminée\n");
					break; 
				case 4:
					// Afficher livre recherché par son nom 
					printf("Entrez un nom de livre\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer, "%s", nom_livre);
					printf("Les livres sont:\n");
					afficher_livre_H(recherche_livre_titre_H(b_h, nom_livre));
					
					break;
				case 5:
					// Afficher livre recherché par son numero
					printf("Entrez un numero de livre\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer, "%d", &num);
					printf("Les livres sont:\n");
					
					afficher_livre_H(recherche_livre_num_H(b_h, num));
					break;
				case 6:
					// Afficher biblio avec livres meme auteur
					printf("Entrez un nom d'auteur\n");
					fgets(buffer, 256, stdin);
					sscanf(buffer,"%s",nom_auteur);
					printf("Les livres sont:\n");
					BiblioH* bh_auteur = recherche_livre_auteur_H(b_h, nom_auteur);
					afficher_biblio_H(bh_auteur);
					liberer_biblio_H(bh_auteur);
					break;
				case 7:
					afficher_biblio_H(plusieurs_exemplaires_H(b_h));
					break;
				case 8:
					// Fusionner deux bibliothèques
					char f3[50]; char f4[50];
					printf("Entrez deux fichiers contenant chacun une bibliotheque.\n");
					scanf("%s %s", f3, f4);
					// Initialisation des biblios 
					BiblioH * b3 = charger_n_entrees_H(f3, 5);
					BiblioH * b4 = charger_n_entrees_H(f4, 5);

					fusion_biblio_H(b3,b4);
					afficher_biblio_H(b3);
					liberer_biblio_H(b3);
					break;
				}
			break;
		}
	}


	/*Désallocation de mémoire de toutes les structures créées*/

	liberer_biblio(b_lc);
	liberer_biblio_H(b_h);



	return 0;
}