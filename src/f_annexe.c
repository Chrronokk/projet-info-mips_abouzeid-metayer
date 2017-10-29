#include "f_annexe.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


LISTE creer_liste(void){
     return NULL;
}

instLISTE creer_liste_inst(void){
     return NULL;
}

dirLISTE creer_liste_dir(void){
     return NULL;
}

etiqLISTE creer_liste_etiq(void){
     return NULL;
}

int est_vide(LISTE l){
    if (l==NULL) return 1;
	return 0;
}


LISTE supprimer_tete(LISTE l){

    if(est_vide(l)) {return NULL;}

    else{
        LISTE p;
        p = l->suiv;
        free(l);
        return p;
    }

}


LISTE ajout_queue(LEXEME lexeme, LISTE liste){
	/*puts("Entrée dans ajout_queue");*/
	LISTE p = calloc(1, sizeof(*p));
    p->suiv = NULL;
	p->val=lexeme;
    if(liste == NULL){ return p;}

    else{
        LISTE q = liste;
        while(q->suiv != NULL){
            q = q->suiv;
        }
        q->suiv = p;
        return liste;
    }

}

instLISTE ajout_queue_inst(instruction inst, instLISTE liste){
  /*puts("Entrée dans ajout_queue");*/
	instLISTE p = calloc(1, sizeof(*p));
  	p->suiv = NULL;
 	 p->val=inst;
  	if(liste == NULL){ return p;}

  	else{
		instLISTE q = liste;
    	while(q->suiv != NULL){
      		q = q->suiv;
    	}
    q->suiv = p;
    return liste;
    }
}

dirLISTE ajout_queue_dir(DIRECTIVE dir, dirLISTE liste){
  /*puts("Entrée dans ajout_queue");*/
	dirLISTE p = calloc(1, sizeof(*p));
  	p->suiv = NULL;
 	p->val=dir;
  	if(liste == NULL){ return p;}

  	else{
		dirLISTE q = liste;
    	while(q->suiv != NULL){
      		q = q->suiv;
    	}
    q->suiv = p;
    return liste;
    }
}

/*
LISTE ajout(void* p_e,LISTE l){
	LISTE p=calloc(1,sizeof(*p));
	p->pval=p_e;

	LISTE q=l;
	while (q->suiv != NULL) q=q->suiv;


	p->suiv=l;
	return l;
}
*/

LISTE ajout_tete (LEXEME lexeme, LISTE Liste){
	LISTE p;
	p = calloc(1, sizeof(p));
	p->suiv = Liste;
	p->val = lexeme;
	Liste = p;
	return Liste;
}


LISTE supprimen(int n, LISTE l){

    int i;
    LISTE p = l;
    LISTE temp = NULL;

    if(est_vide(l)){ return l;}

    if(n==1){ return supprimer_tete(l);}

    for(i=0; i<n-2 && p->suiv != NULL; i++){
        p = p->suiv;
    }

    if(p->suiv == NULL){
        printf("Cet element n'existe pas\n");
        return l;}

    else{
        temp = p->suiv;
        p->suiv = temp->suiv;}

    free(temp);
    return l;
}


LISTE copie(LISTE l){
    /*puts("Entrée dans copie"); */
    LISTE p = l;
    LISTE copie = NULL;

    if(est_vide(l)){ puts("CCCC");return NULL;}

    while(p->suiv != NULL){

        copie = ajout_queue(p->val,copie);
        p = p->suiv;
    }
    copie = ajout_queue(p->val,copie);
    /*puts("Sortie de copie"); */
    return copie;
}


void affiche_liste(LISTE l){
	/*puts("Entrée dans affiche_liste");*/
	LISTE c = l	;

	if(est_vide(l)==1){
		printf("Vide \n");
		return;
		}

	while(c->suiv != NULL){
		/*puts("Bouclage");*/
    	printf("[%s]  %s \n", c->val.type,c->val.lex);
		c=c->suiv;
    }
   }

void affiche_liste_etiq(etiqLISTE l){
	puts("Entrée dans affiche_liste_etiq");
	etiqLISTE c = l	;

	if(l==NULL){
		printf("Vide \n");
		return;
		}

	while(c->suiv != NULL){
		/*puts("Bouclage");*/
    	printf("%s,%s,%d\n",c->val.nom, c->val.zone, c->val.arrivee);
		c=c->suiv;
    }
    printf("%s,%s,%d\n",c->val.nom, c->val.zone, c->val.arrivee);
    puts(" ");
    return;


}

void nbmaillon(LISTE l){
	int c=0;
	if(est_vide(l)){ puts("Vide");}
	else{
		LISTE q=l;
		while(q->suiv != NULL){
				c++;
    	        q = q->suiv;
    	    }
		c++;
		printf("il y a %d d'éléments\n", c);
	}
}


void affiche_liste_inst(instLISTE l){
	puts("Affichage de la liste des instructions");
	instLISTE c = l	;
  int nb_op;
  int i;


	if(l==NULL){
		printf("Vide \n");
	}

	while(c->suiv != NULL){
    nb_op=c->val.nb_op;
		printf("[Instruction %s] adresse: %d, nombre d'op: %d, ligne: %d\n",c->val.symbole,c->val.adresse,c->val.nb_op,c->val.ligne);
    for(i=0;i<nb_op;i++){
      printf("[Operande %d] nom:%s, type:%s, offset:%s\n",i,c->val.op[i].nom,c->val.op[i].type,c->val.op[i].offset );
    	}
    puts("\n");
		c=c->suiv;
  }
}

void affiche_liste_dir(dirLISTE l){
	puts("Affichage de la liste des directives");
	dirLISTE c = l	;

	if(l==NULL){
		printf("Vide \n");
		return;
		}

	while(c->suiv != NULL){
		/*puts("Bouclage");*/
    	printf("%s,%d,%d,%s,%s\n",c->val.dir, c->val.ligne, c->val.decalage,c->val.symb_op,c->val.type_op);
		c=c->suiv;
    }
	printf("%s,%d,%d,%s,%s\n",c->val.dir, c->val.ligne, c->val.decalage,c->val.symb_op,c->val.type_op);
   	puts(" ");
    return;


}

LISTE concat(LISTE l1, LISTE l2){
    LISTE copie1 = copie(l1);
    LISTE copie2 = copie(l2);
    LISTE p = copie1;
    while(p->suiv != NULL){
        p = p->suiv;
    }
    p->suiv = copie2;
    return copie1;

}

char* concatener_string(char* dest,char* src){
    int l=strlen(dest)+strlen(src);
    char* c;
    c=calloc(strlen(dest),sizeof(*c));
    strcpy(c,dest);
    dest=calloc(l,sizeof(*c));
    dest=strcat(dest,src);
    return dest;
}
