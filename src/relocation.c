#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <f_annexe.h>
#include <global.h>
#include <notify.h>
#include <gram.h>
#include <relocation.h>


/*Fonction qui va générer une liste de relocation des étiquettes présents dans les oérandes des instructions
  présentes dans la liste col à l"aide du tableau des symboles tab_etiq*/

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
			if((strcmp(p->val.op[j].type,"SYM")*strcmp(p->val.op[j].offset,"SYM")==0)){
        if(strcmp(p->val.op[j].type,"SYM")==0){
          maillon.nom=calloc(strlen(p->val.op[j].nom),sizeof(char));
          strcpy(maillon.nom,p->val.op[j].nom);
        }
        else {
          maillon.nom=calloc(strlen(p->val.op[j].offset),sizeof(char));
          strcpy(maillon.nom,p->val.op[j].offset);
        }
        maillon.decalage=p->val.adresse;
        int pos=recherche_etiq(maillon.nom,tab_etiq);
        if(pos<0){
          maillon.depart=-1;
          maillon.zone="unknown";
          /*return NULL*/
        }
        else {
          int k;
          for (k=0;k<pos-1;k++) e=e->suiv;
          maillon.depart=e->val.decalage;
          maillon.zone=calloc(strlen(e->val.zone),sizeof(char));
          strcpy(maillon.zone,e->val.zone);
          /*printf("%c\n",dico[i].type);
          printf("%s\n",dico[i].optype_tab[j]);*/
        }
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
          printf("Erreur sur le mot %s à la ligne %d\n", maillon.nom,p->val.ligne);
          /*return NULL;*/
        }
        liste=ajout_queue_reloc(maillon,liste);

      }
		}

    p=p->suiv;
  }
  return(liste);
}


relocLISTE reloc_etiq_data(dirLISTE col,etiqLISTE tab_etiq, relocLISTE liste){
  etiqLISTE e=tab_etiq;
  dirLISTE p=col;
  relocETIQ maillon;
  while (p->suiv!=NULL){
    if(strcmp(p->val.type_op,"SYM")==0){
      maillon.nom=calloc(strlen(p->val.symb_op),sizeof(char));
      strcpy(maillon.nom,p->val.symb_op);
      maillon.decalage=p->val.decalage;
      int pos=recherche_etiq(maillon.nom,tab_etiq);
      if(pos<0){
        maillon.depart=-1;
        maillon.zone="unknown";
        /*return NULL*/
      }
      else {
        int k;
        for (k=0;k<pos-1;k++) e=e->suiv;
        maillon.depart=e->val.decalage;
        maillon.zone=calloc(strlen(e->val.zone),sizeof(char));
        strcpy(maillon.zone,e->val.zone);
      }
      maillon.type="R_MIPS_32 ";
      liste=ajout_queue_reloc(maillon,liste);
    }
    p=p->suiv;
  }
  return(liste);
}
