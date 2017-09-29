#include "f_annexe.h"

LISTE creer_liste(void){
     return NULL;                       
}



int est_vide(LISTE l){                       
    return !l;                         
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


LISTE ajout_queue(LEXEME* p_arc, LISTE l){
     
    LISTE p = calloc(1, sizeof(*p));    
    p->val = p_arc;                           
     
    p->suiv = NULL;                     
     
    if(est_vide(l)){ return p;}         
     
    else{                               
        LISTE q = l;                    
        while(q->suiv != NULL){         
            q = q->suiv;                
        }
        q->suiv = p;                    
        return l;                       
    }
                                        
}  

LISTE ajout_tete (LEXEME* p_arc, LISTE Liste){
	LISTE p;
	p = calloc(1, sizeof(p));
	p->suiv = Liste; 
	p->val = p_arc;
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
     
    LISTE p = l;                            
    LISTE copie = NULL;                    
     
    if(est_vide(l)){ return NULL;}         
     
    while(p->suiv != NULL){                 
        
        copie = ajout_queue(p->val,copie);    
        p = p->suiv;                        
    }
    copie = ajout_queue(p->val,copie);        
     
    return copie;                          
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



