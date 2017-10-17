#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gram.h>
#include <global.h>
#include <f_annexe.h>

/* Fonction qui recherche si une etiquette est dans la table des symboles 
   Renvoie la position de l'etiquette dans la table, renvoie -1 si l'etiquette n'existe pas encore*/

int recherche_etiq(char* etiq, ETIQUETTE* tab_etiq){
	int i=0;
	ETIQUETTE* p =tab_etiq;

	if (p==NULL){
		puts("Table des symboles vide");
		return -1;
	
	while(p->suiv!=NULL){
		if(strcmp(etiq,p->nom)==0){
			printf("Etiquette trouvée à la %d eme ligne de la table des symboles", i);
			return i;			
		}
		i++;
	}
	return -1;
}


/* Fonction qui ajoute l'etiquette "name", et son adresse à la table des symboles */
void ajout_etiq(char* name, int adresse, ETIQUETTE* tab_etiq){
	
	int i;
	ETIQUETTE* p=tab_etiq;
	ETIQUETTE* p_etiq =calloc(1,sizeof(ETIQUETTE));
	
	int pos=recherche_etiq(name,tab_etiq);
	
	if (pos!=-1){
		printf("ERREUR: DEUX ETIQUETTES ONT LE MEME NOM");
		return;
	}
	while(p->suiv != NULL) p=p->suiv;

	p->suiv=p_etiq;
	p_etiq->nom=strcpy(name);
	p_etiq->arrivee=adresse;
	return;	
}





analyse_gram(LISTE Col){
	int nb_instr=NULL;
	int* p_nb_instr=&nb_instr;
	instr_def* dictionnaire;
	
	dictionnaire=lecture_dico(p_nb_instr);
	
	LISTE p=Col;
	int debut=0;
	char zone[
	
	while (p->val!=NULL){
		ETAT=INIT;
		int continu = TRUE:
		while (continu == TRUE){
			switch(ETAT){
				case INIT:
					if(debut==0){
						ETAT=INIT_DEBUT}
					else{
						if(strcmp(p->val.type,"DIR"){
							ETAT=DIR;}
						else if(strcmp(p->val.type,"SYM"){
							ETAT=SYM;}
						else if	(
						
						else{
				break;
	
	
				case INIT_DEBUT:
					if( (strcmp(p->val.type,"COMMENT") || (strcmp(p->val.type,"NL"){
						p=p->suiv;
						continu=FALSE
						}
					else if(strcmp(p->val.type,"DIR"){
						if(strcmp(p->vavl.lex,".set"){
							p=p->suiv;
							if(strcmp(p->val.type,"noreorder"){
								p=p->suiv;
								continu=FALSE;
							}
							else{
								ETAT=ERROR;}
						else{
							ETAT=ERROR;}			
					else{
						ETAT=ERROR;}
				break;		
				
				
				case DIR:
					if((strcmp(p->val.lex,".text")||(strcmp(p->val.lex,".data")||(strcmp(p->val.lex,".bss"){
						ETAT=DIR_TYPE1;}
					else if((strcmp(p->val.lex,".word"))||(strcmp(p->val.lex,".byte"))||(strcmp(p->val.lex,".asciiz"))){
						ETAT=DIR_TYPE2;}
					else{
						ETAT=ERROR;}
				break;
				
				
				case DIR_TYPE1:
					if(strcmp(p->suiv->val.type,"COMMENT")||strcmp(p->suiv->val.type,"NL")){
						if 
				
























































}


instr_def * lecture_dico(int* p_nb_instr){
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
