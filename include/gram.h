
#ifndef _LEX_H_
#define _LEX_H_


#include <stdio.h>
#include <f_annexe.h>

enum{INIT,INIT_DEBUT,DIR,DIR_TYPE1,DIR_TYPE2,SYM,INSTR,ETIQ,ERROR};

enum{text,data,bss};



instr_def* lecture_dico(int* p_nb_instr);
int test_nb_op_inst(LISTE p, int nb_op);
int is_in_dico(char* symbole,instr_def* dictionnaire, int nb_instr);
void analyse_gram(LISTE);
etiqLISTE ajout_etiq(char* name,char* zone, int adresse, etiqLISTE tab_etiq);
int recherche_etiq(char* etiq, etiqLISTE tab_etiq);

#endif
