
#ifndef _LEX_H_
#define _LEX_H_


#include <stdio.h>
#include <f_annexe.h>

enum{INIT,INIT_DEBUT,DIR,DIR_TYPE1,DIR_TYPE2,NB_OPERANDE_DIR,TEMPO_DIR,CHARGE_DIR,SYM,SYM_PRESENT,SYM_PAS_PRESENT,SYM_AVANT,SYM_ARRIERE,INSTR,OPE_INSTR,ERROR};



instr_def* lecture_dico(int* p_nb_instr);
int test_nb_op_inst(LISTE p, int nb_op);
int is_in_dico(char* symbole,instr_def* dictionnaire, int nb_instr);
void analyse_gram(LISTE);
void ajout_etiq(char* name, int adresse, etiqLISTE tab_etiq);
int recherche_etiq(char* etiq, etiqLISTE tab_etiq);

#endif
