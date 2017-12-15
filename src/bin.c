#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "f_annexe.h"
#include "global.h"
#include "notify.h"
#include "lex.h"
#include "gram.h"
#include "pseudo_instr.h"
#include "relocation.h"
#include "bin.h"

instr_def_bin* lecture_dico_bin(int* p_nb_instr){
  FILE* f1= fopen("Dicos/dico_bin.txt","r");
  if (f1==NULL) return NULL;
  int i;
  char type;
  if (fscanf(f1, "%d", p_nb_instr) != 1) return NULL;
  instr_def_bin* dico_bin;
  dico_bin=calloc(*p_nb_instr,sizeof(instr_def_bin));
  int opcode,function;
  char* nom=calloc(4,sizeof(char));
  char* r1=calloc(4,sizeof(char));
  char* r2=calloc(4,sizeof(char));
  char* r3=calloc(4,sizeof(char));
  char* sa=calloc(4,sizeof(char));
  char * ind=calloc(4,sizeof(char));
  for(i=0;i<*p_nb_instr;i++){
    fscanf(f1,"%s %c %d", nom,&type,&opcode);
    dico_bin[i].nom=calloc(512,sizeof(char));
    strcpy(dico_bin[i].nom,nom);
    dico_bin[i].opcode=opcode;
    dico_bin[i].type=type;
    if(type=='R'){
      fscanf(f1,"%s %s %s %s %d",r1,r2,r3,sa,&function);
      /*printf("%s %s %s %s %d\n",r1,r2,r3,sa,function);*/
      dico_bin[i].arg.R.function=function;
      if(isdigit(r1[0])){
        if(r1[0]=='0'){
          dico_bin[i].arg.R.rr1.bin=0;
        }
        else{
          dico_bin[i].arg.R.rr1.bin=atoi(r1);
        }
      }
      else{
        dico_bin[i].arg.R.rr1.rg=calloc(strlen(r1),sizeof(char));
        strcpy(dico_bin[i].arg.R.rr1.rg,r1);
        dico_bin[i].arg.R.rr1.bin=-1;
      }
      if(isdigit(r2[0])){
        if(r2[1]=='0'){
          dico_bin[i].arg.R.rr2.bin=0;
        }
        else{
          dico_bin[i].arg.R.rr2.bin=atoi(r2);
        }
      }
      else{
        dico_bin[i].arg.R.rr2.rg=calloc(4,sizeof(char));
        strcpy(dico_bin[i].arg.R.rr2.rg,r2);
        dico_bin[i].arg.R.rr2.bin=-1;
      }
      if(isdigit(r3[0])){
        if(r3[1]=='0'){
          dico_bin[i].arg.R.rr3.bin=0;
        }
        else{
          dico_bin[i].arg.R.rr3.bin=atoi(r3);
        }
      }
      else{
        dico_bin[i].arg.R.rr3.rg=calloc(4,sizeof(char));
        strcpy(dico_bin[i].arg.R.rr3.rg,r3);
        dico_bin[i].arg.R.rr3.bin=-1;
      }
      if(isdigit(sa[0])){
        if(sa[0]=='0'){
          dico_bin[i].arg.R.rsa.bin=0;
      }
        else{
          dico_bin[i].arg.R.rsa.bin=atoi(sa);
        }
      }
      else{
        dico_bin[i].arg.R.rsa.rg=calloc(4,sizeof(char));
        strcpy(dico_bin[i].arg.R.rsa.rg,sa);
        dico_bin[i].arg.R.rsa.bin=-1;
      }
    }
    else if(type=='I'){
      fscanf(f1,"%s %s %s",r1,r2,r3);
      if(isdigit(r1[0])){
        if(r1[1]=='0'){
          dico_bin[i].arg.I.ir1.bin=0;
        }
        else{
          dico_bin[i].arg.I.ir1.bin=atoi(r1);
        }
      }
      else{
        dico_bin[i].arg.I.ir1.rg=calloc(4,sizeof(char));
        strcpy(dico_bin[i].arg.I.ir1.rg,r1);
        dico_bin[i].arg.I.ir1.bin=-1;
      }
      if(isdigit(r2[0])){
        if(r2[0]=='0'){
          dico_bin[i].arg.I.ir2.bin=0;
        }
        else{
          dico_bin[i].arg.I.ir2.bin=atoi(r2);
        }
      }
      else{
        dico_bin[i].arg.I.ir2.rg=calloc(4,sizeof(char));
        strcpy(dico_bin[i].arg.I.ir2.rg,r2);
        dico_bin[i].arg.I.ir2.bin=-1;
      }
      if(isdigit(r3[0])){
        if(r3[0]=='0'){
          dico_bin[i].arg.I.off.bin=0;
        }
        else{
          dico_bin[i].arg.I.off.bin=atoi(r3);
        }
      }
      else{
        dico_bin[i].arg.I.off.rg=calloc(4,sizeof(char));
        strcpy(dico_bin[i].arg.I.off.rg,r3);
        dico_bin[i].arg.I.off.bin=-1;
      }
    }
    else if(type=='J'){
      fscanf(f1,"%s",ind);
      if(isdigit(ind[0])){
        if(ind[0]=='0'){
          dico_bin[i].arg.J.ind.bin=0;
        }
        else{
          dico_bin[i].arg.J.ind.bin=atoi(ind);
        }
      }
      else{
        dico_bin[i].arg.J.ind.rg=calloc(4,sizeof(char));
        strcpy(dico_bin[i].arg.J.ind.rg,ind);
        dico_bin[i].arg.J.ind.bin=-1;
      }
    }

  }

  return dico_bin;
}


void affiche_dico_bin(instr_def_bin* dico,int n){
  int i;
  puts("Affichage du dictionnaire du binaire");
  for(i=0;i<n;i++){
    printf("%s %c %d ",dico[i].nom,dico[i].type,dico[i].opcode);
    if(dico[i].type=='R'){
      if(dico[i].arg.R.rr1.bin<0) printf("%s ",dico[i].arg.R.rr1.rg);
      else printf("%d ",dico[i].arg.R.rr1.bin);

      if(dico[i].arg.R.rr2.bin<0) printf("%s ",dico[i].arg.R.rr2.rg);
      else printf("%d ",dico[i].arg.R.rr2.bin);

      if(dico[i].arg.R.rr3.bin<0) printf("%s ",dico[i].arg.R.rr3.rg);
      else printf("%d ",dico[i].arg.R.rr3.bin);

      if(dico[i].arg.R.rsa.bin<0) printf("%s ",dico[i].arg.R.rsa.rg);
      else printf("%d ",dico[i].arg.R.rsa.bin);

      printf("%d\n",dico[i].arg.R.function);
    }
    if(dico[i].type=='I'){
      if(dico[i].arg.I.ir1.bin<0) printf("%s ",dico[i].arg.I.ir1.rg);
      else printf("%d ",dico[i].arg.I.ir1.bin);

      if(dico[i].arg.I.ir2.bin<0) printf("%s ",dico[i].arg.I.ir2.rg);
      else printf("%d ",dico[i].arg.I.ir2.bin);

      if(dico[i].arg.I.off.bin<0) printf("%s \n",dico[i].arg.I.off.rg);
      else printf("%d\n ",dico[i].arg.I.off.bin);
    }
    if(dico[i].type=='J'){
      if(dico[i].arg.J.ind.bin<0) printf("%s\n",dico[i].arg.J.ind.rg);
      else printf("%d \n",dico[i].arg.J.ind.bin);
    }
  }
  puts("Fin de l'affichage du ditionnaire binaire\n ");
}


int creation_binaire_inst(instruction inst,instr_def_bin* dico,int nb_instr){
  int i;
  i=is_in_dico_bin(inst.symbole,dico,nb_instr);
  if(i<0) return -1;
  int opcode;
  char type;
  opcode=dico[i].opcode;
  type=dico[i].type;
  int r1;
  int r2;
  int r3;
  int sa;
  int function;
  int off;
  int ind;
  int codeBinaire;
  int r;
  if(type=='R'){
    function=dico[i].arg.R.function;
    if(dico[i].arg.R.rr1.bin<0){
      r=quel_op(dico[i].arg.R.rr1.rg);
      if(strcmp(inst.op[r].type,"REG")==0){
        r1=check_reg(inst.op[r].nom);
      }
      else if(strcmp(inst.op[r].type,"SYM")==0){
        r1=0;
      }
      else{
        return -1;
      }
    }
    else{
      r1=dico[i].arg.R.rr1.bin;
    }
    if(dico[i].arg.R.rr2.bin<0){
      r=quel_op(dico[i].arg.R.rr2.rg);
      if(strcmp(inst.op[r].type,"REG")==0){
        r2=check_reg(inst.op[r].nom);
      }
      else if(strcmp(inst.op[r].type,"SYM")==0){
        r2=0;
      }
      else{
        return -1;
      }
    }
    else{
      r2=dico[i].arg.R.rr2.bin;
    }
    if(dico[i].arg.R.rr3.bin<0){
      r=quel_op(dico[i].arg.R.rr3.rg);
      if(strcmp(inst.op[r].type,"REG")==0){
        r3=check_reg(inst.op[r].nom);
      }
      else if(strcmp(inst.op[r].type,"SYM")==0){
        r3=0;
      }
      else{
        return -1;
      }
    }
    else{
      r3=dico[i].arg.R.rr3.bin;
    }
    if(dico[i].arg.R.rsa.bin<0){
      if(strcmp(inst.op[2].type,"DEC")==0){
        sa=strtol(inst.op[2].nom,NULL,10);
      }
      else if(strcmp(inst.op[2].type,"HEXA")==0){
        sa=strtol(inst.op[2].nom,NULL,16);
      }
      else if(strcmp(inst.op[r].type,"SYM")==0){
        sa=0;
      }
      else return -1;
    }
    else{
      sa=dico[i].arg.R.rsa.bin;
    }
    int neg=0xFFFFFFE0; /*recupération des 2 octets utiles*/
    if(sa<0){
      sa=sa-neg;
    }
    /*printf("%d %d %d %d %d %d\n",opcode,r1,r2,r3,sa,function);*/
    codeBinaire = 0;
    codeBinaire = codeBinaire | (opcode << 26);
    codeBinaire = codeBinaire | (r1 << 21);
    codeBinaire = codeBinaire | (r2 << 16);
    codeBinaire = codeBinaire | (r3 << 11);
    codeBinaire = codeBinaire | (sa << 6);
    codeBinaire = codeBinaire | (function << 0);
    return codeBinaire;
  }
  else if(type=='I'){
    if(dico[i].arg.I.ir1.bin<0){
      r=quel_op(dico[i].arg.I.ir1.rg);
      if(strcmp(inst.op[r].type,"REG")==0){
        r1=check_reg(inst.op[r].nom);
      }
      else if(strcmp(inst.op[r].type,"SYM")==0){
        r1=0;
      }
      else{
        return -1;
      }
    }
    else{
      r1=dico[i].arg.I.ir1.bin;
    }
    if(dico[i].arg.I.ir2.bin<0){
      r=quel_op(dico[i].arg.I.ir2.rg);
      if(strcmp(inst.op[r].type,"REG")==0){
        r2=check_reg(inst.op[r].nom);
      }
      else if(strcmp(inst.op[r].type,"SYM")==0){
        r2=0;
      }
      else{
        return -1;
      }
    }
    else{
      r2=dico[i].arg.I.ir2.bin;
    }

    if(dico[i].arg.I.off.bin<0){
      if(strcmp(dico[i].arg.I.off.rg,"imm")==0){
        if(strcmp(inst.op[r+1].type,"DEC")==0){
          off=strtol(inst.op[r+1].nom,NULL,10);
        }
        else if(strcmp(inst.op[r+1].type,"HEXA")==0){
          off=strtol(inst.op[r+1].nom,NULL,16);
        }
        else if(strcmp(inst.op[r+1].type,"SYM")==0){
          off=0;
        }
        else{
          return -1;
        }
      }
      else if(strcmp(dico[i].arg.I.off.rg,"off")==0){
        if(strcmp(inst.op[1].type_off,"DEC")==0){
          off=strtol(inst.op[1].offset,NULL,10);
        }
        else if(strcmp(inst.op[1].type_off,"HEXA")==0){
          off=strtol(inst.op[1].offset,NULL,16);
        }
        else if(strcmp(inst.op[1].type_off,"SYM")==0){
          off=0;
          puts("---------------------------------------------");
        }
        else{
          return -1;
        }
      }
    }
    else{
      off=dico[i].arg.I.off.bin;
    }

    int neg=0xFFFF0000; /*recupération des 2 octets utiles*/
    if(off<0){
      off=off-neg;
    }

    printf("%d %d %d %x\n",opcode,r1,r2,off);
    codeBinaire = 0;
    codeBinaire = codeBinaire | (opcode << 26);
    codeBinaire = codeBinaire | (r1 << 21);
    codeBinaire = codeBinaire | (r2 << 16);
    codeBinaire = codeBinaire | (off << 0);
    return codeBinaire;
  }
  else if(type=='J'){
    if(dico[i].arg.J.ind.bin<0){
      if(strcmp(inst.op[0].type,"DEC")==0){
        ind=strtol(inst.op[0].nom,NULL,10);
      }
      else if(strcmp(inst.op[0].type,"HEXA")==0){
        ind=strtol(inst.op[0].nom,NULL,16);
      }
      else if(strcmp(inst.op[0].type,"SYM")==0){
        ind=0;
      }
      else return -1;
    }
    else{
      off=dico[i].arg.J.ind.bin;
    }

    codeBinaire = 0;
    codeBinaire = codeBinaire | (opcode << 26);
    codeBinaire = codeBinaire | (ind << 0);
    return codeBinaire;
  }
  else return -1;
}


int quel_op(char* reg){
  if(strcmp(reg,"r1")==0) return 0;
  if(strcmp(reg,"r2")==0) return 1;
  if(strcmp(reg,"r3")==0) return 2;
  else return -1;
}

int is_in_dico_bin(char* symbole,instr_def_bin* dictionnaire,int nb_instr){
	int i=0;
	for(i=0;i<nb_instr;i++){
		/*printf("Comparaison: %s avec %s \n", symbole, dictionnaire[i].symbole);*/
		if(strcmp(symbole,dictionnaire[i].nom)==0){
			/*printf("Symbole ' %s ' trouvé à la ligne %d du dico\n",symbole,i);*/
			return i;
		}
	}
	/*puts("Instruction non trouvée");*/

	return -1;
}

int creation_binaire_dir(DIRECTIVE dir,int nb_instr){
  int modulo=pow(2,16);
  int op;
  int codeBinaire;
  int i;
  if(strcmp(dir.dir,".word")==0){
    if(strcmp(dir.type_op,"DEC")==0){
      op=strtol(dir.symb_op,NULL,10);
    }
    else if(strcmp(dir.type_op,"HEXA")==0){
      op=strtol(dir.symb_op,NULL,16);
    }
    else if(strcmp(dir.type_op,"SYM")==0){
      op=0;
    }
    else return -1;
    codeBinaire=0;
    codeBinaire=op;
  }
  else if(strcmp(dir.dir,".byte")==0){
    if(strcmp(dir.type_op,"DEC")==0){
      op=strtol(dir.symb_op,NULL,10);
    }
    else if(strcmp(dir.type_op,"HEXA")==0){
      op=strtol(dir.symb_op,NULL,16);
    }
    else if(strcmp(dir.type_op,"SYM")==0){
      op=0;
    }
    else return -1;
    codeBinaire=0;
    codeBinaire=(op<<16)%modulo;
  }
  /*else if(strcmmp(dir.dir,".asciiz")==0){
    if(strcmp(dir.type_op,"ASC_OP")==0){
      op=0;
      for(i=0;i<strlen(dir.symb_op);i++){
        op=(op<<8)+dir.symb_op[i]
      }
    }
  }*/
  else return -1;
  return codeBinaire;
}
