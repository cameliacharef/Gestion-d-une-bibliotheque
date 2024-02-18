// CHAREF CAMELIA 21202057
// RINCKWALD LISA 21203107
/* fichier biblioLC.h */
#ifndef _BIBLIOLC_H_
#define _BIBLIOLC_H_

typedef struct livre {
    int num ;
    char * titre ;
    char * auteur ;
    struct livre * suiv ;
}Livre ;
    
typedef struct { /* Tete fictive */
    Livre * L ; /* Premier element */
}Biblio ;


//PROTOTYPES

/* Partie Livre */
Livre * creer_livre(int num, char * titre, char * auteur);
void liberer_livre(Livre * L);

/* Partie biblio */
Biblio * creer_biblio();
void liberer_biblio(Biblio * biblio);

/* Insertion de livre dans une biblio */
void inserer_en_tete(Biblio * biblio, int num, char * titre, char * auteur);

/* Affichage */
void afficher_livre(Livre * livre);
void afficher_biblio(Biblio * biblio);

/* Recherche livre par ses attributs */
Livre * recherche_livre_num(Biblio * biblio, int num);
Livre * recherche_livre_titre(Biblio * biblio, char * titre);
Biblio * recherche_livre_auteur(Biblio * biblio, char * auteur);

/* Suppression d'un livre dans une biblio */
void supprimer_livre_biblio(Biblio * biblio, int num, char * titre, char * auteur);

/* Fusionner deux biblio */
Biblio * fusion_biblio(Biblio * biblio1, Biblio * biblio2);

/* Recherche ouvrages avec plusieurs exemplaires*/
Biblio * ouvrages_multiples(Biblio * biblio);

#endif


