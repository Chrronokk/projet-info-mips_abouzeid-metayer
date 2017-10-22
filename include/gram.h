
#ifndef _LEX_H_
#define _LEX_H_


#include <stdio.h>
#include <f_annexe.h>

enum{INIT,INIT_DEBUT,DIR,DIR_TYPE1,DIR_TYPE2,SYM,INSTR,ETIQ,ERROR};

enum{text,data,bss};


void analyse_gram(LISTE);
instr_def* lecture_dico(int* p_nb_instr);
int is_in_dico(char* symbole,instr_def* dictionnaire, int nb_instr);
OPERANDE creer_op(char* name, char* ty, char* off);
instLISTE add_inst(instLISTE insts, LISTE p_lex, int nb_op, int adresse;);
int test_nb_op_inst(LISTE p, int nb_op);
int recherche_etiq(char* etiq, etiqLISTE tab_etiq);
etiqLISTE ajout_etiq(ETIQUETTE etiq, etiqLISTE tab_etiq);
ETIQUETTE creer_etiquette(char* nom, int adresse,	char* zone);
dirLISTE add_dir(LISTE p_lex,int decalage, dirLISTE col);
int decalage_asciiz(LISTE p);


#endif
