#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <f_annexe.h>
#include <global.h>
#include <notify.h>
#include <lex.h>
#include <gram.h>
#include <pseudo_instr.h>



LISTE pseudo_instr(LISTE col){
	LISTE c=creer_liste();
	LISTE p=col;
	LEXEME maillon;
	while(p->suiv!=NULL){
		if(strcmp(p->val.lex,"NOP")==0){
			maillon.type="SYM";
			maillon.lex="SLL";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type="REG";
			maillon.lex="$0";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type="VIR";
			maillon.lex=",";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type="REG";
			maillon.lex="$0";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type="VIR";
			maillon.lex=",";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type="DEC";
			maillon.lex="0";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			p=p->suiv;

		}
		else if(strcmp(p->val.lex,"MOVE")==0){
			maillon.type="SYM";
			maillon.lex="ADD";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			p=p->suiv;
			while(strcmp(p->val.type,"NL")!=0){
				maillon.type=calloc(strlen(p->val.type),sizeof(char));
				strcpy(maillon.type,p->val.type);
				maillon.lex=calloc(strlen(p->val.lex),sizeof(char));
				strcpy(maillon.lex,p->val.lex);
				maillon.line=p->val.line;
				c=ajout_queue(maillon,c);
				p=p->suiv;
			}
			maillon.type="VIR";
			maillon.lex=",";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type="REG";
			maillon.lex="$0";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			p=p->suiv;
		}

		else if(strcmp(p->val.lex,"NEG")==0){
			maillon.type="SYM";
			maillon.lex="SUB";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			p=p->suiv;
			maillon.type=calloc(strlen(p->val.type),sizeof(char));
			strcpy(maillon.type,p->val.type);
			maillon.lex=calloc(strlen(p->val.lex),sizeof(char));
			strcpy(maillon.lex,p->val.lex);
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type="VIR";
			maillon.lex=",";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			p=p->suiv;
			maillon.type="REG";
			maillon.lex="$0";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type="VIR";
			maillon.lex=",";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			p=p->suiv;
			maillon.type=calloc(strlen(p->val.type),sizeof(char));
			strcpy(maillon.type,p->val.type);
			maillon.lex=calloc(strlen(p->val.lex),sizeof(char));
			strcpy(maillon.lex,p->val.lex);
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			p=p->suiv;
		}
		else if(strcmp(p->val.lex,"LI")==0){
			maillon.type="SYM";
			maillon.lex="ADDI";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			p=p->suiv;
			maillon.type=calloc(strlen(p->val.type),sizeof(char));
			strcpy(maillon.type,p->val.type);
			maillon.lex=calloc(strlen(p->val.lex),sizeof(char));
			strcpy(maillon.lex,p->val.lex);
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type="VIR";
			maillon.lex=",";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type="REG";
			maillon.lex="$0";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			p=p->suiv;
			maillon.type="VIR";
			maillon.lex=",";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			p=p->suiv;
			maillon.type=calloc(strlen(p->val.type),sizeof(char));
			strcpy(maillon.type,p->val.type);
			maillon.lex=calloc(strlen(p->val.lex),sizeof(char));
			strcpy(maillon.lex,p->val.lex);
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			p=p->suiv;

		}
		else if(strcmp(p->val.lex,"BLT")==0){
			maillon.type="SYM";
			maillon.lex="SLT";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			p=p->suiv;
			maillon.type="REG";
			maillon.lex="$1";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type="VIR";
			maillon.lex=",";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type=calloc(strlen(p->val.type),sizeof(char));
			strcpy(maillon.type,p->val.type);
			maillon.lex=calloc(strlen(p->val.lex),sizeof(char));
			strcpy(maillon.lex,p->val.lex);
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type="VIR";
			maillon.lex=",";
			p=p->suiv;
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			p=p->suiv;
			maillon.type=calloc(strlen(p->val.type),sizeof(char));
			strcpy(maillon.type,p->val.type);
			maillon.lex=calloc(strlen(p->val.lex),sizeof(char));
			strcpy(maillon.lex,p->val.lex);
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type="NL";
			maillon.lex="\n";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type="SYM";
			maillon.lex="BNE";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type="REG";
			maillon.lex="$1";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type="VIR";
			maillon.lex=",";
			maillon.line=p->val.line;
			p=p->suiv;
			c=ajout_queue(maillon,c);
			maillon.type="REG";
			maillon.lex="$0";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			maillon.type="VIR";
			maillon.lex=",";
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			p=p->suiv;
			maillon.type=calloc(strlen(p->val.type),sizeof(char));
			strcpy(maillon.type,p->val.type);
			maillon.lex=calloc(strlen(p->val.lex),sizeof(char));
			strcpy(maillon.lex,p->val.lex);
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
			p=p->suiv;
		}

		else{
			maillon.type=calloc(strlen(p->val.type),sizeof(char));
			strcpy(maillon.type,p->val.type);
			maillon.lex=calloc(strlen(p->val.lex),sizeof(char));
			strcpy(maillon.lex,p->val.lex);
			maillon.line=p->val.line;
			c=ajout_queue(maillon,c);
      p=p->suiv;
		}
	}
  affiche_liste(c);
	return c;
}
