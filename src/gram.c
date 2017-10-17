#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gram.h>
#include <global.h>
#include <f_annexe.h>

/* Fonction qui  */
int recherche_etiq(char* etiq, ETIQUETTE* tab_etiq){

}

void ajout_etiq(char* etiq, ETIQUETTE* tab_etiq, int isdep){

	int i;
	LISTE p=Col;
	
	
	while (p->suiv != NULL){
		if (p->
	










}




analyse_gram(LISTE Col){
	int nb_instr=NULL;
	int* p_nb_instr=&nb_instr;
	instr_def* dictionnaire;
	
	dictionnaire=lecture_dico(p_nb_instr);
	
	LISTE p=Col;
	int debut=0;
	
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
						else if{strcmp(p->val.type,"	
	



























































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
