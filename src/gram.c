#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include <gram.h>
#include <pseudo_instr.h>
#include <global.h>
#include <f_annexe.h>
#include <relocation.h>
#include <bin.h>


Gram analyse_gram(LISTE Col){

	instLISTE col_text=creer_liste_inst();
	dirLISTE col_data=creer_liste_dir();
	dirLISTE col_bss=creer_liste_dir();
	etiqLISTE tab_etiq=creer_liste_etiq();
	relocLISTE reloc_text=creer_liste_reloc();
	relocLISTE reloc_data=creer_liste_reloc();

	Gram gram_error;

	gram_error.col_text=creer_liste_inst();
	gram_error.col_data=creer_liste_dir();
	gram_error.col_bss=creer_liste_dir();
	gram_error.tab_etiq=creer_liste_etiq();
	gram_error.reloc_text=creer_liste_reloc();
	gram_error.reloc_data=creer_liste_reloc();

	puts("Début de l'analyse grammaticale\n\n");

	int nb_instr;
	int* p_nb_instr=&nb_instr;
	instr_def* dictionnaire=lecture_dico(p_nb_instr);

	LISTE p=Col;
	int debut=0;

	int position;
	int nb_op;
	char* zone=calloc(6,sizeof(char));
	strcpy(zone,".text");
	int decalage_complet[3];
	decalage_complet[text]=0;
	decalage_complet[data]=0;
	decalage_complet[bss]=0;
	int decalage=decalage_complet[text];

	ETIQUETTE etiq;
	while (p->suiv!=NULL){
		/*printf("%s \n",p->val.lex);*/
		int ETAT=INIT;
		int continu = TRUE;
		while (continu == TRUE){
			/*printf("%s\n", zone);*/
			/*puts("test2");*/
			/*printf("ETAT=%d \n",ETAT);*/
			switch(ETAT){


				case INIT:
					if(debut==0){
						ETAT=INIT_DEBUT;}
					else{
						if(strcmp(p->val.type,"DIR")==0){
							ETAT=DIR2;}
						else if(strcmp(p->val.type,"SYM")==0){
							ETAT=SYM2;}
						else if(strcmp(p->val.type,"NL")*strcmp(p->val.type,"COMMENT")==0){
							p=p->suiv;
							continu=FALSE;}
						else{
							ETAT=ERROR2;}
					}
				break;


				case ERROR2:
					printf("Erreur sur le mot %s à la ligne %d \n",p->val.lex,p->val.line);
					return gram_error;
				break;


				case INIT_DEBUT: /*ça marche*/
					if( (strcmp(p->val.type,"COMMENT"))*(strcmp(p->val.type,"NL"))==0){
						/*puts("allez");*/
						p=p->suiv;
						continu=FALSE;
						}
					else if(strcmp(p->val.type,"DIR")==0){
						/*puts("come on");*/
						if(strcmp(p->val.lex,".set")==0){
							/*puts("quasi success");*/
							p=p->suiv;
							/*printf("%s %s \n", p->val.lex, p->val.type);*/
							if(strcmp(p->val.lex,"noreorder")==0){
								/*puts("Succes");*/
								p=p->suiv;
								continu=FALSE;
								debut=1;
							}
							else{
								ETAT=ERROR2;}
						}
						else{
							ETAT=ERROR2;}
					}
					else{
						ETAT=ERROR2;}
				break;


				case DIR2:
					if((strcmp(p->val.lex,".text"))*(strcmp(p->val.lex,".data"))*(strcmp(p->val.lex,".bss"))==0){
						ETAT=DIR_TYPE1;}
					else if((strcmp(p->val.lex,".word"))*(strcmp(p->val.lex,".byte"))*(strcmp(p->val.lex,".asciiz"))*(strcmp(p->val.lex,".space"))==0){
						ETAT=DIR_TYPE2;}
					else ETAT=ERROR2;

				break;


				case DIR_TYPE1:/* ça marche*/
					if(strcmp(zone,".text")==0) decalage_complet[text]=decalage;
					if(strcmp(zone,".data")==0) decalage_complet[data]=decalage;
					if(strcmp(zone,".bss ")==0) decalage_complet[bss]=decalage;


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
							ETAT=ERROR2;
						}
						p=p->suiv->suiv;
						continu=FALSE;
					}
					else{
						ETAT=ERROR2;}
				break;


				case DIR_TYPE2:
							if((strcmp(p->val.lex,".byte"))==0){
								col_data=add_dir(p,decalage,col_data);
								if(col_data==NULL) ETAT=ERROR2;
								decalage=decalage+decalage_byte(p);
								if(decalage_byte(p)==0) ETAT=ERROR2;
							}
							else if((strcmp(p->val.lex,".asciiz"))==0){
								col_data=add_dir(p,decalage,col_data);
								if(col_data==NULL) ETAT=ERROR2;
								decalage+=decalage_asciiz(p);
								if(decalage_asciiz(p)==0) ETAT=ERROR2;
							}
							else if((strcmp(p->val.lex,".space"))==0){
								col_bss=add_dir(p,decalage,col_bss);
								if(col_bss==NULL) ETAT=ERROR2;
								if(strcmp(p->suiv->val.type,"DEC")!=0) ETAT=ERROR2;
								decalage+=atoi(p->suiv->val.lex);
							}
							else if((strcmp(p->val.lex,".word"))==0){
								col_data=add_dir(p,decalage,col_data);
								if(col_data==NULL) ETAT=ERROR2;
								decalage=decalage+decalage_word(p);
								if(decalage_word(p)==0) ETAT=ERROR2;
							}
							else ETAT=ERROR2;
							while(strcmp(p->val.type,"NL")*strcmp(p->val.type,"COMMENT")!=0) p=p->suiv;
							if(ETAT!=ERROR2) continu=FALSE;

				break;


				case SYM2:
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
						while(strcmp(p->val.type,"NL")!=0){
							p=p->suiv;
						}
						p=p->suiv;
						continu=FALSE;
					}
					else ETAT=ERROR2;
				break;

				case ETIQ:
					if(strcmp(p->suiv->val.type,"DP")==0){
						if(recherche_etiq(p->val.lex,tab_etiq)<0){
							etiq=creer_etiquette(p->val.lex,decalage,zone,etiq,decalage);
							tab_etiq=ajout_etiq(etiq,tab_etiq);
							p=p->suiv->suiv;
							continu=FALSE;
						}
						else ETAT=ERROR2;
					}
					else ETAT=ERROR2;
				break;
			}
		}
	}

	instLISTE l=col_text;
	while (l->suiv!=NULL){
		if(test_type_op_inst(l->val,dictionnaire,tab_etiq)==0){
			return gram_error;
		}
		l=l->suiv;
	}
	if(test_type_op_inst(l->val,dictionnaire,tab_etiq)==0){
		return gram_error;
	}
	reloc_text=reloc_etiq_text(col_text,tab_etiq,reloc_text);
	reloc_data=reloc_etiq_data(col_data,tab_etiq,reloc_data);

	/*instr_def_bin* dico_bin;
	dico_bin=calloc(*p_nb_instr,sizeof(instr_def_bin));
  dico_bin=lecture_dico_bin(p_nb_instr);
  affiche_dico_bin(dico_bin,*p_nb_instr);
	int bin;
	bin=creation_binaire(col_text->val,dico_bin,*p_nb_instr);
	printf("%x\n",bin);
	*/
	Gram gram;

	gram.col_text=col_text;
	gram.col_data=col_data;
	gram.col_bss=col_bss;
	gram.tab_etiq=tab_etiq;
	gram.reloc_text=reloc_text;
	gram.reloc_data=reloc_data;

	/*affiche_liste_etiq(gram.tab_etiq);
	affiche_liste_inst(gram.col_text);
	affiche_liste_dir(gram.col_data);
	affiche_liste_dir(gram.col_bss);
	affiche_liste_reloc(gram.reloc_text);
	affiche_liste_reloc(gram.reloc_data);
	*/

	return gram;


}


/* Lit le fichier contenant le dictionnaire d'instructions et renvoi un tableau contenant le dictionnaire*/

instr_def* lecture_dico(int* p_nb_instr){
	puts("Lecture du dictionnaire");
	FILE* f1= fopen("Dicos/dictionnaire.txt","r");
	int i;
	instr_def* dico;
	char type_instr;
	char* symbole=calloc(512,sizeof(char));
	char* op0=calloc(512,sizeof(char));
	char* op1=calloc(512,sizeof(char));
	char* op2=calloc(512,sizeof(char));
	int nb_op;
	/*puts("Affichage du dictionnaire");*/
	if (f1==NULL) return NULL;
	if(fscanf(f1, "%d", p_nb_instr)!=1) return NULL;
	/*printf("Il y a %d instructions dans le dictionnaire \n",*p_nb_instr);*/
	dico=calloc(*p_nb_instr,sizeof(instr_def));

	for(i=0;i<*p_nb_instr;i++){
		fscanf(f1,"%s %c %d %s %s %s",symbole,&type_instr,&nb_op,op0,op1,op2);
		dico[i].symbole=calloc(strlen(symbole),sizeof(char));
		strcpy(dico[i].symbole,symbole);
		dico[i].nb_op=nb_op;
		dico[i].type=type_instr;
		dico[i].optype_tab[0]=calloc(strlen(op0),sizeof(char));
		strcpy(dico[i].optype_tab[0],op0);
		dico[i].optype_tab[1]=calloc(strlen(op1),sizeof(char));
		strcpy(dico[i].optype_tab[1],op1);
		dico[i].optype_tab[2]=calloc(strlen(op2),sizeof(char));
		strcpy(dico[i].optype_tab[2],op2);
		printf("%s %c %d %s %s %s\n",dico[i].symbole,dico[i].type,dico[i].nb_op,dico[i].optype_tab[0],dico[i].optype_tab[1],dico[i].optype_tab[2]);
	}
	fclose(f1);
	puts("ABCD");
	return dico;
}

/*Retourne la position de l'instuction, ou -1 si l'instruction n'existe pas*/

int is_in_dico(char* symbole,instr_def* dictionnaire,int nb_instr){
	int i=0;
	for(i=0;i<nb_instr;i++){
		/*printf("Comparaison: %s avec %s \n", symbole, dictionnaire[i].symbole);*/
		if(strcmp(symbole,dictionnaire[i].symbole)==0){
			/*printf("Symbole ' %s ' trouvé à la ligne %d du dico\n",symbole,i);*/
			return i;
		}
	}
	/*puts("Instruction non trouvée");*/

	return -1;
}


/*cree et renvoie une structure operande contenant les 3 string données*/
OPERANDE creer_op(char* name, char* ty, char* off,char* type_off){

	OPERANDE op;

	op.nom=calloc(strlen(name),sizeof(char));
	op.type=calloc(strlen(ty),sizeof(char));
	op.offset=calloc(strlen(off),sizeof(char));
	op.type_off=calloc(strlen(type_off),sizeof(char));

	strcpy(op.nom,name);
	strcpy(op.type,ty);
	strcpy(op.offset,off);
	strcpy(op.type_off,type_off);

	return op;
}



/* Ajoute l'instruction pointée, ainsi que ses opérandes à la liste des instructions */

instLISTE add_inst(instLISTE insts, LISTE p_lex, int nb_op, int adresse){
	instruction inst;
	inst.symbole=calloc(strlen(p_lex->val.lex),sizeof(char));
	strcpy(inst.symbole,p_lex->val.lex);
	inst.adresse=adresse;
	inst.nb_op=nb_op;
	inst.ligne=p_lex->val.line;
	int i=0;


	while (i<nb_op){
		p_lex=p_lex->suiv;
		/*printf("%s\n",p_lex->val.lex);*/

		OPERANDE op;
		if(strcmp(p_lex->val.type,"VIR")!=0){
			if (strcmp(p_lex->val.type,"HEXA")*strcmp(p_lex->val.type,"DEC")*strcmp(p_lex->val.type,"SYM")==0){
				if (strcmp(p_lex->suiv->val.lex,"(")==0){
					op=creer_op(p_lex->suiv->suiv->val.lex,"REG",p_lex->val.lex,p_lex->val.type);
					p_lex=p_lex->suiv->suiv->suiv;
				}
				else{
					op=creer_op(p_lex->val.lex,p_lex->val.type,"0","null");
				}
			}

			else if(strcmp(p_lex->val.type,"REG")*strcmp(p_lex->val.type,"SYM")==0){
				op=creer_op(p_lex->val.lex,p_lex->val.type,"0","null");
				/*printf("%s\n", op.nom);*/
			}
			/*printf("%s\n", op.nom);*/
			inst.op[i] = op;
			i++;
		}
	}
	/*Ajout de l'instruction à la liste des instructions:*/
	insts=ajout_queue_inst(inst, insts);
	/*affiche_liste_inst(insts);*/
	return insts;
}



/* Verifie que l'instruction pointée par p a bien nb_op opérandes */
int test_nb_op_inst(LISTE p, int nb_op){
	/*printf("Instruction %s : %d opérandes souhaitées\n",p->val.lex, nb_op);*/
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

			if(strcmp(op,"HEXA")*strcmp(op,"DEC")*strcmp(op,"SYM")==0){
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
	/*printf(" %d Opérandes trouvées\n", i);*/
	if (i==nb_op){
		/*puts("Bon nombre d'opérandes\n\n");*/
		return TRUE;
		}
	puts("Mauvais nombre d'opérandes\n\n");
	return FALSE;
}


/*Fonction qui vérifie le type des opérandes des instructions*/
/*Renvoie 1 si OK, 0 si erreur détectée*/
int test_type_op_inst(instruction inst, instr_def* dico, etiqLISTE tab_etiq){

	int i=0;

	while(strcmp(inst.symbole,dico[i].symbole)) i++;
	int err=0;
	int j;

	for (j=0;j<dico[i].nb_op;j++){ /* Parcourt chaque opérande de l'instruction*/
		if (strcmp(dico[i].optype_tab[j],"REG")==0){
			if (strcmp(inst.op[j].type,"REG")!=0 || strcmp(inst.op[j].offset,"0")!=0) err=1;
		}
		if (strcmp(dico[i].optype_tab[j],"IMM")==0){
			if ((strcmp(inst.op[j].type,"DEC")!=0 && strcmp(inst.op[j].type,"HEXA")!=0 )&& (strcmp(inst.op[j].type,"SYM")!=0)) err=1;
		}
		if (strcmp(dico[i].optype_tab[j],"REGOFF")==0){
			if (strcmp(inst.op[j].type,"REG")!=0) err=1;
		}

		if (err==1){
			printf("ERREUR LIGNE %d: OPERANDE NUMERO %d: %s NON SUPPORTEE",inst.ligne,j,inst.op[j].nom);
			return 0;
		}
	}
	return 1;
}



/* Fonction qui recherche si une etiquette est dans la table des symboles
   Renvoie la position de l'etiquette dans la table, renvoie -1 si l'etiquette n'existe pas encore*/
int recherche_etiq(char* etiq, etiqLISTE tab_etiq){
	int i=0;

	if (tab_etiq==NULL){
		/*puts("Table des symboles vide");*/
		return -1;
	}
	while(tab_etiq->suiv!=NULL){
		if(strcmp(etiq,tab_etiq->val.nom)==0){
			/*printf("Etiquette trouvée à la %d eme ligne de la table des symboles", i);*/
			return i;
		}
		tab_etiq=tab_etiq->suiv;
		i++;
	}
	if(strcmp(etiq,tab_etiq->val.nom)==0){
		/*printf("Etiquette trouvée à la %d eme ligne de la table des symboles", i);*/
		return i;
	}
	return -1;


}

/* Fonction qui ajoute l'etiquette "etiq" à la table des symboles */

etiqLISTE ajout_etiq(ETIQUETTE etiq, etiqLISTE tab_etiq){
	/*printf("%s,%s,%d\n",etiq.nom, etiq.zone, etiq.arrivee);*/
	etiqLISTE p_etiq =calloc(1,sizeof(*p_etiq));
	p_etiq->suiv=NULL;
	p_etiq->val=etiq;
	int pos=recherche_etiq(etiq.nom,tab_etiq);
	if (pos!=-1){
		printf("ERREUR: DEUX ETIQUETTES ONT LE MEME NOM");
		return NULL;
	}
	if(tab_etiq==NULL){ return p_etiq;}
	else{
		etiqLISTE q=tab_etiq;
		while(q->suiv != NULL) q=q->suiv;
		q->suiv=p_etiq;
	}
	return tab_etiq;
}


/* créer un aillon étiquette comprenant les informations nécessaires sur l'étiquette en entrée*/
ETIQUETTE creer_etiquette(char* nom, int adresse,	char* zone,ETIQUETTE etiq,int decalage){
	etiq.nom=calloc(strlen(nom),sizeof(*nom));
	strcpy(etiq.nom,nom);
	etiq.zone=calloc(strlen(zone),sizeof(*zone));
	strcpy(etiq.zone,zone);
	etiq.arrivee=adresse;
	etiq.decalage=decalage;
	return etiq;
}


/*Fonction qui va lire la liste p_lex afin d'ajouter à la colection data ou bss une directive et ses opérandes*/
dirLISTE add_dir(LISTE p_lex,int decalage, dirLISTE col){
	DIRECTIVE dir;
	dir.dir=calloc(strlen(p_lex->val.lex),sizeof(*p_lex->val.lex));
	strcpy(dir.dir,p_lex->val.lex);
	dir.decalage=decalage;
	dir.ligne=p_lex->val.line;
	int att_vir=0;
	p_lex=p_lex->suiv;

	while (strcmp(p_lex->val.type,"NL")*strcmp(p_lex->val.type,"COM") != 0){

		if (att_vir==0){
			att_vir=1;
			if (strcmp(p_lex->val.lex, ",")==0){
				printf("ERREUR LIGNE %d: MAUVAISE OPERANDE DE DIRECTIVE\n", p_lex->val.line);
				return NULL;
			}
			else if (strcmp(p_lex->val.type,"HEXA")*strcmp(p_lex->val.type,"DEC")*strcmp(p_lex->val.type,"SYM")*strcmp(p_lex->val.type,"ASC_OP")==0){
				dir.symb_op=calloc(strlen(p_lex->val.lex),sizeof(*p_lex->val.lex));
				dir.type_op=calloc(strlen(p_lex->val.type),sizeof(*p_lex->val.type));
				strcpy(dir.symb_op,p_lex->val.lex);
				strcpy(dir.type_op,p_lex->val.type);
				col=ajout_queue_dir(dir,col);
				p_lex=p_lex->suiv;
			}
		}
		else if (att_vir==1){
			att_vir=0;
			if (strcmp(p_lex->val.lex, ",")!=0){
				printf("ERREUR LIGNE %d: MAUVAISE OPERANDE DE DIRECTIVE\n", p_lex->val.line);
				p_lex=p_lex->suiv;
				return NULL;
			}
			p_lex=p_lex->suiv;
		}
	}
	if (att_vir==0){
		printf("ERREUR LIGNE %d: MAUVAISE OPERANDE DE DIRECTIVE\n", p_lex->val.line);
		return NULL;
	}
	return col;
}

/*Calcul le décalage généré par une directive asciiiz*/
int decalage_asciiz(LISTE p){
	int c=0;
	p=p->suiv;
	while (strcmp(p->val.type,"NL")*strcmp(p->val.type,"COM") != 0){

		if (strcmp(p->val.type, "VIR")==0){
			p=p->suiv;
		}
		else if (p->val.lex[0]=='"'){
			c+=strlen(p->val.lex)-1;
			p=p->suiv;
		}
		else{
			return 0;}
	}
	return c;
}

/*Calcul le décalage généré par une directive bytes*/
int decalage_byte(LISTE p){
	int c=0;
	p=p->suiv;
	while (strcmp(p->val.type,"NL")*strcmp(p->val.type,"COM") != 0){

		if (strcmp(p->val.type, "VIR")==0){
			p=p->suiv;
		}
		else if (strcmp(p->val.type,"HEXA")*strcmp(p->val.type,"DEC")==0){
			c+=1;
			p=p->suiv;
		}
		else{
			return 0;
		}
	}
	return c;
}

/*Calcul le décalage généré par une directive word*/
int decalage_word(LISTE p){
	int c=0;
	p=p->suiv;
	while (strcmp(p->val.type,"NL")*strcmp(p->val.type,"COM") != 0){

		if (strcmp(p->val.type, "VIR")==0){
			p=p->suiv;
		}
		else if (strcmp(p->val.type,"HEXA")*strcmp(p->val.type,"DEC")*strcmp(p->val.type,"SYM")==0){
			c+=4;
			p=p->suiv;
		}
		else{
			return 0;
		}
	}
	return c;
}


/*Prend le nom du registre en entrée et renvoie son numero, renvoie -1 si le registre n'existe pas*/
int check_reg(char* registre){
	char* reg=calloc(strlen(registre),sizeof(*registre));
	strcpy(reg,registre);
	int nreg,x;
	/*printf("%s: ", reg);*/
	if (reg[0]!='$'){
		puts("Erreur: pas un registre");
		return -1;
	}

	if (isalpha(reg[1])){
		puts("lettre");

		x=atoi(reg+2);

		if (strcmp(reg,"$zero")==0) nreg = 0;

		else if (strlen(reg)==3){

			if(strcmp(reg,"$at")==0) nreg =1;

			else if(strcmp(reg,"$gp")==0) nreg=28;

			else if(strcmp(reg,"$sp")==0) nreg=29;

			else if(strcmp(reg,"$fp")==0) nreg=30;

			else if(strcmp(reg,"$ra")==0) nreg=31;

			else if (reg[1]=='v') nreg=x+2;

			else if (reg[1]=='a') nreg=x+4;

			else if (reg[1]=='t'){
				if (x<8 && x>-1){
					nreg=x+8;
				}
				else if (atoi(reg+2)==8 || atoi(reg+2)==9){
					nreg=x+16;
				}
			}

			else if (reg[1]=='s') nreg=x+16;

			else if(reg[1]=='k'){
				nreg=x+26;
			}

			else{
				puts("ERREUR REGISTRE INVALIDE");
				return -1;
			}
		}
		else{
			puts("ERREUR REGISTRE INVALIDE");
			return -1;
		}
	}
	else{ /*if reg[1] is a number*/
		nreg=atoi(reg+1);
		if(nreg<0 || nreg >31){
			puts("ERREUR: REGISTRE INVALIDE");
			return -1;
		}
		printf("nombre: %d\n",nreg);
		return nreg;
	}
	printf("%d\n",nreg);
	return nreg;
}
