#ifndef _BIN_H_
#define _BIN_H_


#include <stdio.h>
#include <f_annexe.h>

instr_def_bin* lecture_dico_bin(int* p_nbr_instr);
void affiche_dico_bin(instr_def_bin* dico_bin,int n);
int is_in_dico_bin(char* symbole,instr_def_bin* dictionnaire,int nb_instr);
int creation_binaire_inst(instruction inst,instr_def_bin* dico,int nb_instr,etiqLISTE tab_etiq);
int creation_binaire_dir(DIRECTIVE dir,int nb_instr,etiqLISTE tab_etiq);
int quel_op(char* reg);



#endif
