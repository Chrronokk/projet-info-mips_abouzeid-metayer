#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gram.h"

analyse_gram(Col){
	int nb_instr=NULL;
	int* p_nb_instr=&nb_instr;
	instr_def* dictionnaire;
	
	dictionnaire=lecture_dico(p_nb_instr);

	/*
	printf("\n\n%s , %s , %s , %s\n", dictionnaire[0].symbole, dictionnaire[1].symbole, dictionnaire[2].symbole, dictionnaire[3].symbole);
	printf("%c , %c , %c , %c\n", dictionnaire[0].type, dictionnaire[1].type, dictionnaire[2].type, dictionnaire[3].type);
	printf("%d , %d , %d , %d\n\n\n", dictionnaire[0].nb_op, dictionnaire[1].nb_op, dictionnaire[2].nb_op, dictionnaire[3].nb_op);
	*/

	is_in_dico("XXX",dictionnaire,*p_nb_instr);
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
