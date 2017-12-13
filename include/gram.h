
#ifndef _GRAM_H_
#define _GRAM_H_


#include <stdio.h>
#include <f_annexe.h>

enum{INIT,INIT_DEBUT,DIR2,DIR_TYPE1,DIR_TYPE2,SYM2,INSTR,ETIQ,ERROR2};

enum{text,data,bss};


Gram analyse_gram(LISTE Col);
instr_def* lecture_dico(int* p_nb_instr);
int is_in_dico(char* symbole,instr_def* dictionnaire, int nb_instr);
OPERANDE creer_op(char* name, char* ty, char* off,char* type_off){
instLISTE add_inst(instLISTE insts, LISTE p_lex, int nb_op, int adresse;);
int test_nb_op_inst(LISTE p, int nb_op);
int test_type_op_inst(instruction inst, instr_def* dico, etiqLISTE tab_etiq);
int recherche_etiq(char* etiq, etiqLISTE tab_etiq);
etiqLISTE ajout_etiq(ETIQUETTE etiq, etiqLISTE tab_etiq);
ETIQUETTE creer_etiquette(char* nom, int adresse,	char* zone,ETIQUETTE etiq,int decalage);
dirLISTE add_dir(LISTE p_lex,int decalage, dirLISTE col);
int decalage_asciiz(LISTE p);
int decalage_byte(LISTE p);
int decalage_word(LISTE p);
int check_reg(char*);


#endif
