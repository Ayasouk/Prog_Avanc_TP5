
#ifndef __MEO_AB_H__
#define __MEO_AB_H__

/* Mise en oeuvre par pointeurs d'un arbre binaire */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct noeud {
	int val;
	struct noeud *pere, *fg, *fd;
} t_noeud;


t_noeud* init_arbre(t_noeud* rac);
int arbre_vide(t_noeud* rac);
int filsg(t_noeud*);
int filsd(t_noeud*);

t_noeud* fg(t_noeud*);
t_noeud* fd(t_noeud*);
t_noeud* pere(t_noeud*);
t_noeud * racine(t_noeud*);

int feuille(t_noeud*);

void supprime_noeud(t_noeud* n);
//void modif_noeud(t_noeud*, char*);


int val_noeud(t_noeud*);
int get_id();
void oter_feuille(t_noeud* n);
t_noeud* ajout_filsg(t_noeud* n, int val);
t_noeud* ajout_filsd(t_noeud* n, int val);

t_noeud* creer_noeud(int val);


#endif 

