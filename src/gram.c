#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gram.h>
#include <global.h>
#include <f_annexe.h>


void analyse_gram(LISTE Col){
	puts("Entrée dans analyse_gram");
	int nb_instr;
	int* p_nb_instr=&nb_instr;
	instr_def* dictionnaire=lecture_dico(p_nb_instr);


	LISTE p=Col;
	int debut=0;

	int position;
	int nb_op;
	char zone[5]=".text";
	int decalage_complet[3];
	int decalage=decalage_complet[text];
	etiqLISTE tab_etiq= NULL;

	ETIQUETTE etiq;

	instLISTE col_text=creer_liste_inst();
	dirLISTE col_data=creer_liste_dir();


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
						if (strcmp(p->val.lex,".text")==0){
							strcpy(zone,".text");
							decalage=decalage_complet[text];
						}
						else if(strcmp(p->val.lex,".data")==0){
							strcpy(zone,".data");
							decalage=decalage_complet[data];
						}
						else if(strcmp(p->val.lex,".bss")==0){
							strcpy(zone,".bss ");
							decalage=decalage_complet[bss];
						}
						else{
							ETAT=ERROR;
						}
						p=p->suiv->suiv;
						continu=FALSE;
					}
					else{
						ETAT=ERROR;}
				break;


				case DIR_TYPE2:
						if((strcmp(p->val.lex,".data"))==0){
							if((strcmp(p->val.lex,".word"))==0){
								col_data=add_dir(p,decalage,col_data);
								if(col_data==NULL) ETAT=ERROR;
								decalage+=4;
							}
							else if((strcmp(p->val.lex,".byte"))==0){
								col_data=add_dir(p,decalage,col_data);
								if(col_data==NULL) ETAT=ERROR;
								decalage+=1;
							}
							else if((strcmp(p->val.lex,".asciiz"))==0){
								col_data=add_dir(p,decalage,col_data);
<<<<<<< HEAD
								if(col==NULL) ETAT=ERROR;
=======
								if(col_data==NULL) ETAT=ERROR;								
>>>>>>> 0df4a58bf9ac921a67dff56870407b1164f73578
								decalage+=decalage_asciiz(p);
								if(decalage_asciiz(p)==0) ETAT=ERROR;
							}
							else if((strcmp(p->val.lex,".space"))==0){
								col_data=add_dir(p,decalage,col_data);
<<<<<<< HEAD
								if(col==NULL) ETAT=ERROR;


=======
								if(col_data==NULL) ETAT=ERROR;
							}
						}
						else ETAT=ERROR;
>>>>>>> 0df4a58bf9ac921a67dff56870407b1164f73578
				break;


				case SYM:
					position=is_in_dico(p->val.lex,dictionnaire,nb_instr);
					if(position>=0){
						ETAT=INSTR;}
					else{
						ETAT=ETIQ;}
				break;


				case INSTR:
					nb_op=dictionnaire[position].nb_op;

					if (test_nb_op_inst(p,nb_op)==TRUE){
						col_text=add_inst(col_text,p,nb_op,decalage);
						decalage+=4;
						while(p->val.line==p->suiv->val.line){
							p=p->suiv;}
						continu=FALSE;
					}
					else{
						ETAT=ERROR;}
				break;

				case ETIQ:

					if(strcmp(p->suiv->val.type,"DP")==0){
						if(recherche_etiq(p->val.lex,tab_etiq)<0){
							puts("test");
							etiq=creer_etiquette(p->val.lex,decalage,zone);
							printf("%s\n",etiq.nom);
							tab_etiq=ajout_etiq(etiq,tab_etiq);
							p=p->suiv->suiv;
							continu=FALSE;
						}
						else{
							ETAT=ERROR;}
					}
					else{
						ETAT=ERROR;}
				break;













			}
		}
	}
	affiche_liste_etiq(tab_etiq);
	affiche_liste_inst(col_text);
}


/* Lis le fichier contenant le dictionnaire d'instructions et renvoi un tableau contenant le dictionnaire*/

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
/*cree et renvoie une structure operande contenant les 3 string données*/
OPERANDE creer_op(char* name, char* ty, char* off){

	OPERANDE op;
	op.nom=calloc(strlen(name),sizeof(*name));
	op.type=calloc(strlen(ty),sizeof(*ty));
	op.offset=calloc(strlen(off),sizeof(*off));

	strcpy(op.nom,name);
	strcpy(op.type,ty);
	strcpy(op.offset,off);

	return op;
}



/* Ajoute l'instruction pointée, ainsi que ses opérandes à la liste des instructions */

instLISTE add_inst(instLISTE insts, LISTE p_lex, int nb_op, int adresse){
	instruction* p_inst=calloc(1,sizeof(p_inst));
	p_inst->symbole=calloc(strlen(p_lex->val.lex),sizeof(*p_lex->val.lex));
	strcpy(p_inst->symbole,p_lex->val.lex);
	p_inst->adresse=adresse;
	int i=0;

	p_lex=p_lex->suiv;

	while (i<nb_op){
		p_lex=p_lex->suiv;

		OPERANDE op;

		if (strcmp(p_lex->val.lex, "VIR")==0){
			continue;
		}
		else if (strcmp(p_lex->val.type,"HEXA")*strcmp(p_lex->val.type,"DEC")==0){
			if (strcmp(p_lex->suiv->val.lex,"(")==0){
				op=creer_op(p_lex->suiv->suiv->val.lex,"REG",p_lex->val.lex);
				p_lex=p_lex->suiv->suiv->suiv;
			}
			else{
				op=creer_op(p_lex->val.lex,p_lex->val.type,"0");
			}
		}

		else if(strcmp(p_lex->val.type,"REG")*strcmp(p_lex->val.type,"SYM")==0){
			op=creer_op(p_lex->val.type,p_lex->val.lex,"0");
		}

		p_inst->op[i] = &op;

		i++;
	}
	/*Ajout de l'instruction à la liste des instructions:*/
	insts=ajout_queue_inst(*p_inst, insts);
	return insts;
}



/* Verifie que l'instruction pointée par p a bien nb_op opérandes */
int test_nb_op_inst(LISTE p, int nb_op){
	printf("Instruction %s : %d opérandes souhaitées\n",p->val.lex, nb_op);
	int i=0;
	p=p->suiv;
	int att_vir=0;

	while (strcmp(p->val.type,"NL")*strcmp(p->val.type,"COM") != 0){
		char* op=calloc(strlen(p->val.type),sizeof(*p->val.type));
		strcpy(op,p->val.type);
		/*printf("Analyse du lexème %s de type %s\n", p->val.lex, p->val.type);*/
		if(att_vir==0){
			att_vir=1;
			/*puts("Recherche d'une operande");
			printf("opération: %s\n",op); */

			if(strcmp(op,"HEXA")*strcmp(op,"DEC")==0){
				i++;
				/*puts("Opérande trouvée");
				printf("Lexemes suivants:    %s   %s   %s\n",p->suiv->val.lex, p->suiv->suiv->val.type, p->suiv->suiv->suiv->val.lex);*/
				if (strcmp(p->suiv->val.lex,"(")==0 && strcmp(p->suiv->suiv->val.type,"REG")==0 && strcmp(p->suiv->suiv->suiv->val.lex,")")==0){
					p=p->suiv->suiv->suiv;
					/*puts("Adressage par offset détecté");*/
				}
			}
			else if(strcmp(op,"REG")*strcmp(op,"SYM")==0){
				i++;
			}
			else {
				puts("ERREUR: PAS UNE OPERANDE");
				return FALSE;
			}
		}
		else{ /* att_vir==1 */
			att_vir = 0;
			if (strcmp(op,"VIR") != 0) {
				puts("ERREUR: PAS UNE VIRGULE");
				return FALSE;
			}
		}
		p=p->suiv;
	}
	printf(" %d Opérandes trouvées\n", i);
	if (i==nb_op){
		/*puts("Bon nombre d'opérandes\n\n");*/
		return TRUE;
		}
	puts("Mauvais nombre d'opérandes\n\n");
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
		if(strcmp(etiq,p->val.nom)==0){
			printf("Etiquette trouvée à la %d eme ligne de la table des symboles", i);
			return i;
		}
		i++;
	}
	return -1;

}

/* Fonction qui ajoute l'etiquette "etiq" à la table des symboles */

etiqLISTE ajout_etiq(ETIQUETTE etiq, etiqLISTE tab_etiq){

	etiqLISTE p=tab_etiq;
	etiqLISTE p_etiq =calloc(1,sizeof(*p_etiq));
	p_etiq->suiv=NULL;
	p_etiq->val=etiq;

	int pos=recherche_etiq(etiq.nom,tab_etiq);

	if (pos!=-1){
		printf("ERREUR: DEUX ETIQUETTES ONT LE MEME NOM");
		return NULL;
	}
	if(p==NULL){ return p_etiq;}
	else{
		while(p->suiv != NULL) p=p->suiv;
		p->suiv=p_etiq;
	}
	return tab_etiq;
}



ETIQUETTE creer_etiquette(char* nom, int adresse,	char* zone){
	ETIQUETTE etiq;
	etiq.nom=calloc(strlen(nom),sizeof(*nom));
	strcpy(etiq.nom,nom);
	etiq.zone=calloc(strlen(zone),sizeof(*zone));
	strcpy(etiq.zone,zone);
	etiq.arrivee=adresse;
	return etiq;
}



dirLISTE add_dir(LISTE p_lex,int decalage, dirLISTE col){
	DIRECTIVE* p_dir=calloc(1,sizeof(p_dir));
	p_dir->dir=calloc(strlen(p_lex->val.lex),sizeof(*p_lex->val.lex));
	strcpy(p_dir->dir,p_lex->val.lex);
	p_dir->decalage=decalage;
	while (strcmp(p_lex->val.type,"NL")*strcmp(p_lex->val.type,"COM") != 0){
		p_lex=p_lex->suiv;
		if (strcmp(p_lex->val.lex, "VIR")==0){
			continue;
		}
		else if (strcmp(p_lex->val.type,"HEXA")*strcmp(p_lex->val.type,"DEC")*strcmp(p_lex->val.type,"SYM")==0){
			p_dir->symb_op=calloc(strlen(p_lex->val.lex),sizeof(*p_lex->val.lex));
			p_dir->type_op=calloc(strlen(p_lex->val.type),sizeof(*p_lex->val.type));
			strcpy(p_dir->symb_op,p_lex->val.lex);
			strcpy(p_dir->type_op,p_lex->val.type);
			col=ajout_queue_dir(*p_dir,col);
		}
		else return NULL;
	}
	return col;
}

int decalage_asciiz(LISTE p){
	int c=0;
	while (strcmp(p->val.type,"NL")*strcmp(p->val.type,"COM") != 0){
		p=p->suiv;
		if (strcmp(p->val.lex, "VIR")==0){
			continue;
		}
		else if (p->val.lex[0]=='"'){
			c+=strlen(p->val.lex)-1;
		}
		else return 0;
	}
	return c;
}


void affiche_col(instLISTE col){
	puts("Affichage de la ")
	while (col->suiv != NULL){
		printf(dir:%s\n %d %d %s %s)
	}
}
