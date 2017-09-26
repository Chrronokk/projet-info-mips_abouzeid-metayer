#include <stdio.h>
#include "projet.h"
#include "f_annexe.h"



Liste creer_liste(void){
     
    return NULL;                       
                                        
     
}

Liste_proba creer_liste_proba(void){
     
    return NULL;                       
                                        
     
}


int est_vide(Liste l){
                                        
    return !l;                          
                                        
}


Liste supprimer_tete(Liste l){
     
    if(est_vide(l)) {return NULL;}      
     
    else{                               
        Liste p;                        
        p = l->suiv;                    
        free(l);                        
        return p;                       
    }
                                        
}                    


Liste ajout_queue(ARC* p_arc, Liste l){
     
    Liste p = calloc(1, sizeof(*p));    
    p->val = p_arc;                           
     
    p->suiv = NULL;                     
     
    if(est_vide(l)){ return p;}         
     
    else{                               
        Liste q = l;                    
        while(q->suiv != NULL){         
            q = q->suiv;                
        }
        q->suiv = p;                    
        return l;                       
    }
                                        
}  

Liste ajout_tete (ARC* p_arc, Liste liste){
	Liste p;
	p = calloc(1, sizeof(p));
	p->suiv = liste; 
	p->val = p_arc;
	liste = p;
	return liste;
}

Liste_proba ajout_queue_proba(Proba proba,Liste_proba l){
	Liste_proba p = calloc(1, sizeof(*p));    
	p->val = proba;                             
	p->suiv = NULL;                     
	Liste_proba q = l;                    
	while(q->suiv != NULL){         
		q = q->suiv;                
	}
	q->suiv = p;                    
	return l;                       
}

Liste supprimen(int n, Liste l){
     
    int i;
    Liste p = l;                                
    Liste temp = NULL;                          
     
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


Liste copie(Liste l){                      
     
    Liste p = l;                            
    Liste copie = NULL;                    
     
    if(est_vide(l)){ return NULL;}         
     
    while(p->suiv != NULL){                 
        
        copie = ajout_queue(p->val,copie);    
        p = p->suiv;                        
    }
    copie = ajout_queue(p->val,copie);        
     
    return copie;                          
}
 
 
Liste concat(Liste l1, Liste l2){  
    Liste copie1 = copie(l1);               
    Liste copie2 = copie(l2);               
    Liste p = copie1;                        
    while(p->suiv != NULL){                 
        p = p->suiv;                        
    } 
    p->suiv = copie2;                       
    return copie1;                           
}

File creer_file(void)
{	return NULL;}


int file_vide(File f)
{	return !f;}

File enfiler(ARC* p_arc, File f){
	File q = calloc(1, sizeof(*q));
	q->val = p_arc;
	if (file_vide(f)) q->suiv = q;
	else{
		q->suiv = f->suiv;
		f->suiv = q;
	}
	return q;
}

ARC* defiler(File* f){
	File h = (*f)->suiv;
	ARC* p_arc = ((*f)->suiv)->val;
	(*f)-> suiv = ((*f)->suiv)->suiv;
	free(h);
	return p_arc;

}



