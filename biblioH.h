/* fichier biblioH.h */
#ifndef __BIBLIOH_H__
#define __BIBLIOH_H__

typedef struct livreh
{
	int clef;
	int num;
	char * titre;
	char * auteur;
	struct livreh * suivant;
} LivreH;

typedef struct table
{
	int nE ;		/*nombre d’elements contenus dans la table de hachage */
	int m ; 		/*taille de la table de hachage */
	LivreH ** T;	/*table de hachage avec resolution des collisions par chainage */
} BiblioH ;


//PROTOTYPES

int fonctionClef(char * auteur);
int fonctionHachage(int cle, int m);

/* Partie Livre */
LivreH * creer_livre_H(int num, char * titre, char * auteur);
void liberer_livre_H(LivreH * livre_h);

/* Partie biblio */
BiblioH * creer_biblio_H(int m);
void liberer_biblio_H(BiblioH * biblio_h);

/* Insertion de livre dans une biblio */
void inserer_livre_H(BiblioH* biblio_h, int num, char * titre, char * auteur);

/* Affichage */
void afficher_livre_H(LivreH * livre_h);
void afficher_biblio_H(BiblioH * biblio_h);

/* Recherche livre par ses attributs */
LivreH * recherche_livre_num_H(BiblioH * biblio_h, int num);
LivreH * recherche_livre_titre_H(BiblioH * biblio_h, char * titre);
BiblioH * recherche_livre_auteur_H(BiblioH * biblio_h, char * auteur);

/* Suppression d'un livre dans une biblio */
void  suppression_ouvrage_H(BiblioH * biblio_h, int num, char * auteur, char * titre);

/* Fusionner deux biblio */
BiblioH * fusion_biblio_H(BiblioH * biblio_h1, BiblioH * biblio_h2);

/* Recherche ouvrages avec plusieurs exemplaires*/
BiblioH * plusieurs_exemplaires_H(BiblioH * biblio_h);
int livres_identiques_H(LivreH * livre_h1, LivreH * livre_h2);
void plusieurs_exemplaires_i(BiblioH * biblio_h, BiblioH * resultat, int i);


#endif
