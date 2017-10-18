#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gram.h>
#include <global.h>
#include <f_annexe.h>

/* Verifie que l'instruction pointée par p a bien nb_op opérandes */

int test_nb_op(LISTE p, int nb_op){
	int i=0;

	int att_vir=0;


	while (strcmp(p->val.type,"NL")*strcmp(p->val.type,"COM") != 0){
		
		p=p->suiv;
		char op[256];
		strcpy(op,p->val.type);
				
		if(att_vir==0){
			
			if (strcmp(op,"DEC")*strcmp(op,"HEX")*strcmp(op,"SYM")*strcmp(op,"REG")!=0){
				puts("ERREUR OPERANDE");
				return FALSE;
			}
			if(strcmp(op,"HEX")*strcmp(op,"DEC")==0){
				i++;
				if (strcmp(p->suiv->val.lex,"(") && strcmp(p->suiv->suiv->val.type,"REG") && strcmp(p->suiv->suiv->suiv->val.lex,")")){
					p=p->suiv->suiv->suiv;
				}
				att_vir=1;
			}	
		}
		
		else{ /* att_vir==1 */
			att_vir = 0;
			if (strcmp(op,"VIR") != 0) {
				puts("ERREUR OPERANDE");
			}
		}
	}
	if (i==nb_op) return TRUE;
	return FALSE;
}

/* Fonction qui recherche si une etiquette est dans la table des symboles 
   Renvoie la position de l'etiquette dans la table, renvoie -1 si l'etiquette n'existe pas encore*/

int recherche_etiq(char* etiq, etiqLISTE tab_etiq){
	int i=0;
	etiqLISTE p =tab_etiq;

	if (p==NULL){
		puts("Table des symboles vide");
		return -1;
	}
	while(p->suiv!=NULL){
		if(strcmp(etiq,p->pval->nom)==0){
			printf("Etiquette trouvée à la %d eme ligne de la table des symboles", i);
			return i;			
		}
		i++;
	}
	return -1;

}

/* Fonction qui ajoute l'etiquette "name", et son adresse à la table des symboles */
void ajout_etiq(char* name, int adresse, etiqLISTE tab_etiq){
	
	etiqLISTE p=tab_etiq;
	etiqLISTE p_etiq =calloc(1,sizeof(*p_etiq));
	
	int pos=recherche_etiq(name,tab_etiq);
	
	if (pos!=-1){
		printf("ERREUR: DEUX ETIQUETTES ONT LE MEME NOM");
		return;
	}
	while(p->suiv != NULL) p=p->suiv;

	p->suiv=p_etiq;
	strcpy(p_etiq->pval->nom,name);
	p_etiq->pval->arrivee=adresse;
	return;	
}





void analyse_gram(LISTE Col){
	puts("Entrée dans analyse_gram");
	int nb_instr;
	int* p_nb_instr=&nb_instr;
	instr_def* dictionnaire=lecture_dico(p_nb_instr);
	

	LISTE p=Col;
	int debut=0;
	
	int position;
	int nb_op;
	
	while (p->suiv!=NULL){
		/*puts("test1");*/
		int ETAT=INIT;
		int continu = TRUE;
		while (continu == TRUE){
			/*puts("test2");*/
			/*printf("ETAT=%d \n",ETAT);*/
			switch(ETAT){
				
				
				case INIT:
					printf("%s %s \n", p->val.lex, p->val.type);
					if(debut==0){
						ETAT=INIT_DEBUT;}
					else{
						if(strcmp(p->val.type,"DIR")==0){
							ETAT=DIR;}
						else if(strcmp(p->val.type,"SYM")==0){
							ETAT=SYM;}
						else if(strcmp(p->val.type,"NL")*strcmp(p->val.type,"COMMENT")==0){
							p=p->suiv;
							continu=FALSE;}
						else{
							ETAT=ERROR;}
					}
						
						
				break;
	
	
				case ERROR:
					printf("Erreur sur le mot %s à la ligne %d \n",p->val.lex,p->val.line);
					return;
				break;
	
				case INIT_DEBUT: /*ça marche*/
					if( (strcmp(p->val.type,"COMMENT"))*(strcmp(p->val.type,"NL"))==0){
						puts("allez");
						p=p->suiv;
						continu=FALSE;
						}
					else if(strcmp(p->val.type,"DIR")==0){
						puts("come on");
						if(strcmp(p->val.lex,".set")==0){
							puts("quasi success");
							p=p->suiv;
							printf("%s %s \n", p->val.lex, p->val.type);
							if(strcmp(p->val.lex,"noreorder")==0){
								puts("Succes");
								p=p->suiv;
								continu=FALSE;
								debut=1;
							}
							else{
								ETAT=ERROR;}
						}
						else{
							ETAT=ERROR;}
					}			
					else{
						ETAT=ERROR;}
				break;		
				
				
				case DIR: 
					if((strcmp(p->val.lex,".text"))*(strcmp(p->val.lex,".data"))*(strcmp(p->val.lex,".bss"))==0){
						ETAT=DIR_TYPE1;}
					else if((strcmp(p->val.lex,".word"))*(strcmp(p->val.lex,".byte"))*(strcmp(p->val.lex,".asciiz")==0)){
						ETAT=DIR_TYPE2;}
					else{
						ETAT=ERROR;}
				break;
				
				
				case DIR_TYPE1:/* ça marche*/
					if(strcmp(p->suiv->val.type,"COMMENT")||strcmp(p->suiv->val.type,"NL")){
						/* A COMPLETER*/
						
						p=p->suiv->suiv;
						continu=FALSE;
					}
					else{
						ETAT=ERROR;}
				break;
				
				
				case DIR_TYPE2:
					
					/* A COMPLETER */
					
				break;
				
				
				case SYM:
					position=is_in_dico(p->val.lex,dictionnaire,nb_instr);
					if(position>=0){
						ETAT=INSTR;}
					else{
						ETAT=ETIQ;}
				break;
				
				
				case INSTR:
					nb_op=dictionnaire[position+1].nb_op;
					if (test_nb_op(p,nb_op)){
						int i;
						for(i=0;i<nb_op+1;i++){
							p=p->suiv;}
						continu=FALSE;
					}
					else{
						ETAT=ERROR;}
				break;
					
				case ETIQ:
					
					
						
						
					
					
					



















































				
			}
		}
	}
}


instr_def * lecture_dico(int* p_nb_instr){
	/*puts("Lecture du dictionnaire");*/
	FILE* f1= fopen("dictionnaire.txt","r");
	int i;
	char s1[512];
	instr_def* tab;

	if (f1==NULL) return NULL;
	if (fscanf(f1, "%d", p_nb_instr) != 1) return NULL;
	/*printf("Il y a %d instructions dans le dictionnaire \n",*p_nb_instr);*/
	tab=calloc(*p_nb_instr,sizeof(instr_def));
	
	for(i=0;i<*p_nb_instr;i++){
		fscanf(f1,"%s %c %d",s1,&(tab[i].type),&(tab[i].nb_op));
		tab[i].symbole=calloc(1,strlen(s1));
		strcpy(tab[i].symbole,s1);
		/*printf("%s %c %d\n",tab[i].symbole,tab[i].type,tab[i].nb_op);*/
	}
	fclose(f1);
	return tab;
}

/*Retourne la position de l'instuction, ou -1 si l'instruction n'existe pas*/

int is_in_dico(char* symbole,instr_def* dictionnaire,int nb_instr){
	int i=0;
	for(i=0;i<nb_instr;i++){ 
		printf("Comparaison: %s avec %s \n", symbole, dictionnaire[i].symbole);
		if(strcmp(symbole,dictionnaire[i].symbole)==0){
			printf("Symbole ' %s ' trouvé à la ligne %d du dico\n",symbole,i);
			return i;
		}
	}
	puts("Instruction non trouvée");

	return -1;
}





		


















