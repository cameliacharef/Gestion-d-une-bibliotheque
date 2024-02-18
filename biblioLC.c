// CHAREF CAMELIA 21202057
// RINCKWALD LISA 21203107
/* fichier biblioLC.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"

// Crée un livre à partir d'un numéro, d'un titre et du nom d'un auteur
Livre * creer_livre(int num, char * titre, char * auteur){
    Livre * livre = (Livre *) malloc(sizeof(Livre));
    livre->num = num;
    livre->titre = strdup(titre); // Allocation titre
    livre->auteur = strdup(auteur); // Allocation auteur 
    livre->suiv = NULL;

    return livre;
}

// Désalloue l'espace mémoire dédié au livre
void liberer_livre(Livre * L){
    if (L != NULL){
        free(L->titre);
        free(L->auteur);
        free(L);
    }
}   

// Crée une bibliothèque vide
Biblio * creer_biblio(){
    Biblio * biblio = (Biblio *) malloc(sizeof(Biblio));
    biblio->L = NULL;

    return biblio;
}

// Désalloue l'espace mémoire dédié à la bibliothèque
void liberer_biblio(Biblio * biblio) {
    if (biblio != NULL) {
        Livre * courant = biblio->L; // Pointeur pour parcourir la liste des livres
        Livre * suivant;

        // Parcours de la liste des livres
        while (courant != NULL) {
            suivant = courant->suiv; // Sauvegarde du pointeur vers le prochain livre
            liberer_livre(courant); // Libération du livre courant
            courant = suivant; // Passage au prochain livre
        }

        free(biblio); // Libération de la mémoire allouée pour la structure Biblio elle-même
    
    }
}


// Insère un livre en tête de la liste chaînée de la bibliothèque
void inserer_en_tete(Biblio * biblio, int num, char * titre, char * auteur){
    Livre * tete = creer_livre(num, titre, auteur);
    if(biblio->L == NULL){ // Si biblio vide 
        biblio->L = tete; // Nouveau livre est la tete 
    }
    else{
        tete->suiv = biblio->L; 
        biblio->L = tete;
    }
}


// Affiche le numéro, le titre et le nom de l'auteur du livre
void afficher_livre(Livre * livre){
    if(livre != NULL){
        printf("%d %s %s\n", livre->num, livre->titre, livre->auteur);
    }
}
    


// Affiche tous les livres constituant la bibliothèque
void afficher_biblio(Biblio * biblio){
    Livre * tmp = biblio->L;

    while (tmp){
        afficher_livre(tmp);
        tmp = tmp->suiv;
    }
}


// Recherche un livre par son numéro et le retourne
Livre * recherche_livre_num(Biblio * biblio, int num){
    Livre* tmp = biblio->L;
    while (tmp){
        if (tmp->num == num){ // Si le numéro du livre correspond à celui recherché
            return tmp; // Retourne livre trouvé
        }
        tmp = tmp->suiv;
    }
    return NULL; // Si pas trouvé 
}

// Recherche un livre par son titre et le retourne
Livre * recherche_livre_titre(Biblio * biblio, char * titre){
    Livre * tmp = biblio->L;
    while (tmp){
        if (strcmp(titre, tmp->titre) == 0){ // Si le titre correspond à celui recherché
            return tmp; // Retourne le livre
        }
        tmp = tmp->suiv;
    }
    return NULL; // Si pas trouvé
}

// Recherche tous les livres d'un même auteur et retourne une nouvelle bibliothèque
Biblio * recherche_livre_auteur(Biblio * biblio, char * auteur){
    Biblio * newBib = creer_biblio(); 
    Livre * tmp = biblio->L;
    while (tmp){
       if (strcmp(auteur, tmp->auteur) == 0){ // Si l'auteur du livre correspond à celui recherché
            inserer_en_tete(newBib, tmp->num, tmp->titre, tmp->auteur); // Insère le livre trouvé dans la nouvelle bibliothèque
        }
        tmp = tmp->suiv;
    }
    return newBib; // Retourne la nouvelle bibliothèque contenant les livres de l'auteur
}

// Supprime un livre de la bibliothèque
void supprimer_livre_biblio(Biblio * biblio, int num, char * titre, char * auteur) {
    //La fonction ne fait rien si la bibliothèque est vide
    if(biblio == NULL){
        return;
    }

    Livre* l = biblio->L;
    /*Si le livre recherché est en tête de la bibliothèque, la fonction le supprime.
    Sinon, elle le recherche de case en case.*/

    if(l->num == num && strcmp(auteur, l->auteur) == 0 && strcmp(titre, l->titre) == 0){
        biblio->L = l->suiv;
        liberer_livre(l);
    }
  

    while(l->suiv && (l->suiv->num != num || strcmp(auteur, l->suiv->auteur) != 0 || strcmp(titre, l->suiv->titre) != 0)){
        l = l->suiv;
    }
    

    //Au cas où la bibliothèque n'est pas vide, la fonction supprime le livre recherché. Sinon, elle s'arrête.
    if(l->suiv){
        Livre * tmp = l->suiv;
        l->suiv = tmp->suiv;
        liberer_livre(tmp);
    }

}

// Fusionne deux bibliothèques
Biblio * fusion_biblio(Biblio * biblio1, Biblio * biblio2){
    Livre * tmp2 = biblio2->L;
    while(tmp2){
        inserer_en_tete(biblio1, tmp2->num, tmp2->titre, tmp2->auteur);
        tmp2 = tmp2->suiv;
    }

    // Libérer la mémoire de biblio2
    liberer_biblio(biblio2);
    return biblio1;
}

/* Recherche de tous les ouvrages avec plusieurs exemplaires */
Biblio * ouvrages_multiples(Biblio * biblio) {
    Biblio * doublons = creer_biblio();
    Livre * livre = biblio->L;

    // Parcourir la bibliothèque
    while (livre != NULL) {
        int count = 0;
        Livre * tmp = biblio->L;

        // Compter le nombre d'exemplaires du livre courant
        while (tmp != NULL) {
            if (strcmp(tmp->titre, livre->titre) == 0 && strcmp(tmp->auteur, livre->auteur) == 0) {
                count = count + 1;
            }
            tmp = tmp->suiv;
        }

        // Si le livre a plus d'un exemplaire, l'ajouter aux doublons
        if (count > 1) {
            inserer_en_tete(doublons, livre->num, livre->titre, livre->auteur);
        }

        // Passer au livre suivant
        livre = livre->suiv;
    }

    return doublons;
}