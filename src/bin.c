#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "f_annexe.h"
#include "global.h"
#include "notify.h"
#include "lex.h"
#include "gram.h"
#include "pseudo_instr.h"
#include "relocation.h"
#include "bin.h"

instr_def_bin* lecture_dico_bin(int* p_nb_instr){
  FILE* f1= fopen("dico_bin.txt","r");
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
      fscanf(f1,"%s %s %s",r1,r2,r3);
      if(isdigit(r1[1])){
        if(r1[1]=='0'){
          dico_bin[i].arg.R.rr1.bin=0;
        }
        else{
          dico_bin[i].arg.R.rr1.bin=atoi(r1);
        }
      }
      else{
        dico_bin[i].arg.R.rr1.rg=calloc(4,sizeof(char));
        strcpy(dico_bin[i].arg.R.rr1.rg,r1);
      }
      if(isdigit(r2[1])){
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
      }
      if(isdigit(r3[1])){
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
      }
      if(isdigit(sa[1])){
        if(sa[1]=='0'){
          dico_bin[i].arg.R.rsa.bin=0;
        }
        else{
          dico_bin[i].arg.R.rsa.bin=atoi(sa);
        }
      }
      else{
        dico_bin[i].arg.R.rsa.rg=calloc(4,sizeof(char));
        strcpy(dico_bin[i].arg.R.rsa.rg,sa);
      }
      fscanf(f1,"%d",&function);
      dico_bin[i].arg.R.function=function;
    }
    else if(type=='I'){
      fscanf(f1,"%s %s %s",r1,r2,r3);
      if(isdigit(r1[1])){
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
      }
      if(isdigit(r2[1])){
        if(r2[1]=='0'){
          dico_bin[i].arg.I.ir2.bin=0;
        }
        else{
          dico_bin[i].arg.I.ir2.bin=atoi(r2);
        }
      }
      dico_bin[i].arg.I.imm=calloc(4,sizeof(char));
      strcpy(dico_bin[i].arg.I.imm,r3);
    }
    else if(type=='J'){
      fscanf(f1,"%s",ind);
      dico_bin[i].arg.J.ind=calloc(4,sizeof(char));
      strcpy(dico_bin[i].arg.J.ind,ind);
    }
  }
  return dico_bin;
}


void affiche_dico_bin(instr_def_bin* dico_bin,int n){
  int i;
  puts("Affichage du dictionnaire du binaire");
  for(i=0;i<n;i++){
    printf("%s %d %c ",dico_bin[i].nom,dico_bin[i].opcode,dico_bin[i].type);
    if(dico_bin[i].type=='R'){
      printf("%s %s %s %s %d \n",dico_bin[i].arg.R.rr1.rg,dico_bin[i].arg.R.rr2.rg,dico_bin[i].arg.R.rr3.rg,dico_bin[i].arg.R.rsa.rg,dico_bin[i].arg.R.function);
    }
    if(dico_bin[i].type=='I'){
      printf("%s %s %s \n",dico_bin[i].arg.I.ir1.rg,dico_bin[i].arg.I.ir2.rg,dico_bin[i].arg.I.imm);
    }
    if(dico_bin[i].type=='J'){
      printf("%s \n",dico_bin[i].arg.J.ind);
    }
  }
}
