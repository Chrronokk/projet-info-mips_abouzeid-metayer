#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <f_annexe.h>
#include <global.h>
#include <notify.h>
#include <gram.h>
#include <relocation.h>


relocLISTE reloc_etiq_text(instLISTE col,etiqLISTE tab_etiq,relocLISTE liste){
  if (col==NULL) return NULL;
  int nb_instr;
	int* p_nb_instr=&nb_instr;
	instr_def* dico=lecture_dico(p_nb_instr);
	instLISTE p=col;
  etiqLISTE e=tab_etiq;
  relocETIQ maillon;
	int j;
	while (p->suiv!=NULL){
    int i=0;
  	while(strcmp(p->val.symbole,dico[i].symbole)) i++;
		for(j=0;j<p->val.nb_op;j++){
			if((strcmp(p->val.op[j].type,"SYM")==0)){
        maillon.nom=calloc(strlen(p->val.op[j].nom),sizeof(char));
        strcpy(maillon.nom,p->val.op[j].nom);
        maillon.decalage=p->val.adresse;
        int pos=recherche_etiq(maillon.nom,tab_etiq);
        int k;
        for (k=0;k<pos;k++) e=e->suiv;
        maillon.depart=e->val.decalage;
        maillon.zone=calloc(strlen(e->val.zone),sizeof(char));
        strcpy(maillon.zone,e->val.zone);
        printf("%c\n",dico[i].type);
        printf("%s\n",dico[i].optype_tab[j]);
				if(dico[i].type=='J'){
          maillon.type="R_MIPS_26";
        }
        else if(strcmp(dico[i].optype_tab[j],"IMM")*strcmp(dico[i].optype_tab[j],"REGOFF")==0){
          if(strcmp(p->val.symbole,"LW")){
            maillon.type="R_MIPS_HI16 ";
          }
          else{
            maillon.type="R_MIPS_LO16 ";
          }
        }
        else{
          printf("L'étiquette %s est utilisé non initialisé\n", maillon.nom);
          /*return NULL;*/
        }
        ajout_queue_reloc(maillon,liste);
      }
		}

    p=p->suiv;
  }
  affiche_liste_reloc(liste);
  return(liste);
}


/*relocLISTE placement_etiq_data(dirLISTE col,etiqLISTE tab_etiq, relocLISTE liste){
  etiqLISTE e=tab_etiq;
  dirLISTE p=col;
  relocETIQ maillon;
  while (p->suiv!=NULL){
    if(strcmp(p->))
  */
