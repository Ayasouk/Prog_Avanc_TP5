/* Menu du TP 5 - Arbre AVL / équilibrage */
#include<stdio.h>
#include<stdlib.h>
#include "ab.h"

void purge(){
	char c;
	do{
		scanf("%c", &c);
	}while(c!='\n');
}

/* affiche l'arbre dans l'ordre croissant */
void afficher(t_noeud* n)
{
	if(!arbre_vide(n)){
		printf("%d ", val_noeud(n));
		//printf("addr: %p\tpere : %p filsg : %p filsd: %p\n", n, n->pere, n->fg, n->fd);
		if(filsg(n))
			afficher(fg(n));
		if(filsd(n))
			afficher(fd(n));
	}
}

int max(int a, int b){
	return (a>b)?a:b;
}

int hauteur(t_noeud* n){
	if(arbre_vide(n)){
		return -1;
	}
	else return 1+max(hauteur(fg(n)), hauteur(fd(n)));
}

int est_equilibre(t_noeud* n){
	if(feuille(n))
		return 1;
	else 
		return ( est_equilibre(fg(n)) && est_equilibre(fd(n)) && abs(hauteur(fg(n)) - hauteur(fd(n))) <= 1 ); 
}

/* fonction ok */
t_noeud* rotation_gauche(t_noeud* n)
{
		t_noeud* rac = fd(n);
		if(n && rac){
			n->fd = fg(rac);
			if(n->pere != NULL){
				if(n->pere->fd == n)
					n->pere->fd = rac;
				else n->pere->fg = rac;
			}
			rac->pere = n->pere;
			rac->fg = n;
			n->pere = rac;
			
			return rac;
		}
		else return n;
}

/* fonction ok */
t_noeud* rotation_droite(t_noeud* n)
{

	t_noeud* rac = fg(n);

	if( n && rac ){
		n->fg = fd(rac);
		if(n->pere != NULL){
			if(n->pere->fd == n)
				n->pere->fd = rac;
			else n->pere->fg = rac;
		}
		rac->pere = n->pere;
		rac->fd = n;
		n->pere = rac;
		
		return rac;
	}
	else return n;
}


void equilibrer(t_noeud* n)
{	
	if(arbre_vide(n))
		return;
	int hd, hg, diff; /* hauteur droit, gauche et difference */
	
	if(filsg(n)){
		equilibrer(fg(n));
		hg = hauteur(fg(n));
	}else hg = -1;
	
	if(filsd(n)){
		equilibrer(fd(n));
		hd = hauteur(fd(n));
	}else hd = -1;
	
	diff = hd - hg;
	if(diff >1){
		equilibrer(rotation_droite(n));
	}else if(diff < -1){
		equilibrer(rotation_gauche(n));
	}

}

/* fonction ok */
t_noeud* ajouter(t_noeud* r, int val)
{	
	if(arbre_vide(r))
		return creer_noeud(val);
	
	else if(val < val_noeud(r)){
			if(!filsg(r))
				return ajout_filsg(r, val);
			else if(filsg(r))
				return ajouter(fg(r), val);
			
	}
		
	else if(val_noeud(r)==val){
		printf("valeur deja presente dans l'arbre\n");
		return r;
	}
	
	else { // si val_noeud(r) < val
		if(!filsd(r))
			return ajout_filsd(r, val);
		else if(filsd(r))
			return ajouter(fd(r), val);
		
	}
	return NULL;
}
t_noeud* sousArb_desequilibre(t_noeud* n){
	if(arbre_vide(n))
		return NULL;
	if(abs(hauteur(fg(n)) - hauteur(fd(n))) > 1)
		return n;
	return (sousArb_desequilibre(fg(n)))? sousArb_desequilibre(fg(n)): sousArb_desequilibre(fd(n)) ;
}
/*
void ajouter_equilibre(t_noeud* n, int val)
{
	if(n = ajouter(n, val)){
		if(!est_equilibre(n)){
			n = sousArb_desequilibre(n);
			if(hauteur(fg(n)) - hauteur(fd(n)) == 2){
				
			}
		}
	}
	printf("Ce traitement n'est pas encore disponible\n");
}*/


/* Programme principal */
int main(void)
{	
	int choix;	/* Choix de l'utilisateur */
	int val;
	t_noeud* r = NULL;

	do
	{	/* Affichage du menu */
		printf("\nMenu :\n");
		printf(" 1 - Ajouter une valeur sans rééquilibrage\n");
		printf(" 2 - Ajouter une valeur\n");
		printf(" 3 - Rotation gauche\n");
		printf(" 4 - Rotation droite\n");
		printf(" 5 - Equilibrer l'arbre\n");
        printf(" 6 - Afficher l'arbre dans l'ordre croissant\n");
        printf(" 7 - Afficher la hauteur de l'arbre\n");
		printf(" 8 - Verifier si l'arbre est equilibré \n");
		printf(" 9 - Quitter\n");
		printf("Votre choix : ");
		scanf("%i",&choix);

		/* Traitement du choix de l'utilisateur */
		switch(choix)
		{	
			case 1:   
					printf("Quelle entier voulez vous ajouter ?\n");
					purge();
					scanf("%i", &val);
					r = ajouter(r, val);
					break;
			
			case 2: ajouter_equilibre(); break;
			
			case 3: printf("avant rotation\n");
					afficher(r);
					r = rotation_gauche(r); 
					printf("aprés rotation\n");
					r=racine(r);
					afficher(r);
					break;
					
			case 4: printf("avant rotation\n");
					afficher(r);
					r = rotation_droite(r); 
					printf("apres rotation\n");
					r= racine(r);
					afficher(r);
					break;
			
			case 5: equilibrer(r); break;
			
			case 6: afficher(r); break;
			
			case 7: printf("la hauteur est de %d\n", hauteur(r)); break;
			
			case 8: printf("l'arbre est %s\n", (est_equilibre(r))? "equilibre" : "pas equilibre");
			case 9: break;
			
			default: printf("Erreur: votre choix doit être compris entre 1 et 7\n");
		}
		r = racine(r);
	}
	while( choix != 9 );
	
	printf("Au revoir !\n");
	
	return 0;
}
