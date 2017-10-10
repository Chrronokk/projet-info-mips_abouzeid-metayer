#include "f_annexe.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


LISTE creer_liste(void){
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
	

    printf("[%s]  %s \n", c->val.type, c->val.lex);                  

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


instr_def * lecture_dico(char* Fichier, int* p_nb_instr){
	puts("Lecture du dictionnaire");
	FILE* f1= fopen("dictionnaire.txt","r");
	int i;
	char s1[512];
	instr_def* tab;

	if (f1==NULL) return NULL;
	if (fscanf(f1, "%d", p_nb_instr) != 1) return NULL;
	printf("Il y a %d instructions dans le dictionnaire \n",*p_nb_instr);
	tab=calloc(*p_nb_instr,sizeof(instr_def));
	
	for(i=0;i<*p_nb_instr;i++){
		fscanf(f1,"%s %c %d",s1,&(tab[i].type),&(tab[i].nb_op));
		tab[i].symbole=calloc(1,strlen(s1));
		strcpy(tab[i].symbole,s1);
		printf("%s %c %d\n",tab[i].symbole,tab[i].type,tab[i].nb_op);
	}
	fclose(f1);
	return tab;
}

/*Retourne la position de l'instuction, ou NULL si l'instruction n'existe pas*/
int is_in_dico(char* symbole,instr_def* dictionnaire,int nb_instr){
	int i=0;
	for(i=0;i<nb_instr;i++){
		printf("Comparaison: %s avec %s \n", symbole, dictionnaire[i].symbole);
		if(strcmp(symbole,dictionnaire[i].symbole)==0){
			printf("Symbole ' %s ' trouvé à la ligne %d du dico\n",symbole,i);
			return i;
		}
	}
	puts("instruction non trouvée");

	return NULL;
}
		
	
	



















