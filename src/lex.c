
/**
 * @file lex.c
 * @author François Portet <francois.portet@imag.fr>
 * @brief Lexical analysis routines for MIPS assembly syntax.
 *
 * These routines perform the analysis of the lexeme of an assembly source code file.
 */

#define _POSIX_C_SOURCE 200112L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include <f_annexe.h>
#include <global.h>
#include <notify.h>
#include "lex.h"





/**
 * @param file Assembly source code file name.
 * @param nlines Pointer to the number of lines in the file.
 * @return should return the collection of lexemes
 * @brief This function loads an assembly code from a file into memory.
 *
 */
LISTE lex_load_file( char *file, unsigned int *nlines) {
	puts("Chargement du fichier");

    FILE        *fp   = NULL;
    char         line[STRLEN]; /* original source line */
    char         res[2*STRLEN]; /* standardised source line, can be longer due to some possible added spaces*/
	LISTE col_general=creer_liste();
	LISTE col_line=creer_liste();


    fp = fopen( file, "r" );
    if ( NULL == fp ) {
        /*macro ERROR_MSG : message d'erreur puis fin de programme ! */
        ERROR_MSG("Error while trying to open %s file --- Aborts",file);
    }

    *nlines = 0;

    while(!feof(fp)) {

        /*read source code line-by-line */
        if (fgets( line, STRLEN-1, fp ) != NULL ) {
            (*nlines)++;
            if ( 0 != strlen(line) ) {
            	/*printf("%s",line);*/
                lex_standardise( line, res);
                /*printf("%s",res);*/
                col_line=lex_read_line(res,*nlines);
                if(col_general==NULL){
                	col_general=col_line;
                }
                else{
                	col_general=concat(col_general,col_line);
									}
            }
						LEXEME maillon;
						maillon.type="NL";
						maillon.lex=calloc(1,sizeof(char*));
						strcpy(maillon.lex,"\n");
						maillon.line=*nlines+1;
						col_general=ajout_queue(maillon,col_general);
        }
    }
	/*puts("Affichage de la liste des tokens:");*/
	affiche_liste(col_general);
	/*puts("Fin de la liste des tokens");*/
    fclose(fp);
    return col_general;
}











/**
 * @param line String of the line of source code to be analysed.
 * @param nline the line number in the source code.
 * @return return the collection of lexemes that represent the input line of source code.
 * @brief This function performs lexical analysis of one standardized line.
 *
 */
LISTE lex_read_line( char *line, int nline) {

	/*puts("entrée dans lex_read_line");*/
	LISTE col=creer_liste();
	char *seps = " \t";
	char *token = NULL;
	char save[STRLEN];
	int com=0;
	int asc=0;
	int g=0;


	/*nbmaillon(col);*/

    /* copy the input line so that we can do anything with it without impacting outside world*/

	memcpy( save, line, STRLEN );

    /* get each token*/


	for( token = strtok( line, seps ); token!=NULL ; token = strtok( NULL, seps )) {

		int length= strlen(token);
		int ETAT;
		int i;
		LEXEME maillon;
		char* commentaire;
		char* op_asc;
		size_t len=STRLEN;


		/*printf("%s\n", token);*/
		/*printf("%d\n", com);*/

		if ((token[0]=='#') || (com==1 )){
			/*puts("comment");*/
			ETAT=COMMENT;}
		else if (token[0]=='.'){
			ETAT=DIR;}
		else if (token[0]=='$'){
			ETAT=REG;}
		else if (token[0]=='"'||asc==1){
			ETAT=ASC_OP;}
		else if (isalpha(token[0])){
			ETAT=SYM;}
		else if (token[0] == ','){
			ETAT=VIR;}
		else if (token[0] == ':'){
			ETAT=DP;}
		else if (token[0] == ';'){
			ETAT=PVIR;}
		else if (isdigit(token[0]) || token[0]=='-'){
			ETAT=NBR;}
		else if (token[0]=='(' || token[0]==')' ){
			ETAT=PAR;}
		else if (strcmp(token,"\n")==0){
			ETAT=NL;}
		else{
			ETAT=ERROR;}

		switch(ETAT){

		case COMMENT:
				/*printf("passage\n");*/
				if (com==0){
					commentaire=calloc(len,sizeof(char));
				}
				com=1;
				if(token[0]!='\n'){
					commentaire=strcat(commentaire,token);
					commentaire=strcat(commentaire," ");
				}
				else{
					commentaire=strcat(commentaire,"\0");
					com=0;
					maillon.type="COMMENT";
					maillon.lex=calloc(length,sizeof(*commentaire));
					strcpy(maillon.lex,commentaire);
					maillon.line=nline;
					col=ajout_queue(maillon,col);
				}
			break;

		case DIR:
			maillon.type="DIR";
			maillon.lex=calloc(length,sizeof(*token));
			strcpy(maillon.lex,token);
			maillon.line=nline;
			/*puts("dir");*/
			col=ajout_queue(maillon,col);
			/*printf("%s , %s \n", col->val.type, col->val.lex);*/
			break;

		case REG:
			maillon.type="REG";
			maillon.lex=calloc(length,sizeof(*token));
			strcpy(maillon.lex,token);
			maillon.line=nline;
			/*puts("reg");*/
			col=ajout_queue(maillon,col);
			/*printf("%s , %s \n", col->val.type, col->val.lex);*/
			break;

		case SYM:
			maillon.type="SYM";
			maillon.lex=calloc(length,sizeof(*token));
			strcpy(maillon.lex,token);
			maillon.line=nline;
			col=ajout_queue(maillon,col);
		break;

		case VIR:
			maillon.type="VIR";
			maillon.lex=calloc(length,sizeof(*token));
			strcpy(maillon.lex,token);
			maillon.line=nline;
			col=ajout_queue(maillon,col);
			/*printf("%s , %s \n", col->val.type, col->val.lex);*/
			break;

		case DP:
			maillon.type="DP";
			maillon.lex=calloc(length,sizeof(*token));
			strcpy(maillon.lex,token);
			maillon.line=nline;
			col=ajout_queue(maillon,col);
			/*printf("%s , %s \n", col->val.type, col->val.lex);*/
			break;

		case PVIR:
			maillon.type="PVIR";
			maillon.lex=calloc(length,sizeof(*token));
			strcpy(maillon.lex,token);
			maillon.line=nline;
			col=ajout_queue(maillon,col);
			/*printf("%s , %s \n", col->val.type, col->val.lex);*/
			break;

		case PAR:
			maillon.type="PAR";
			maillon.lex=calloc(length,sizeof(*token));
			strcpy(maillon.lex,token);
			maillon.line=nline;
			col=ajout_queue(maillon,col);
			/*printf("%s , %s \n", col->val.type, col->val.lex);*/
			break;

		case NL:
			maillon.type="NL";
			maillon.lex=calloc(length,sizeof(char*));
			strcpy(maillon.lex,"\n");
			maillon.line=nline;
			col=ajout_queue(maillon,col);
			break;

		case NBR:
			i=0;
			if (token[0]=='-'){
				i=1;
			}
			if(token[i]=='0'){
				if (token[i+1]=='x'){
					maillon.type="HEXA";
					maillon.lex=calloc(length,sizeof(*token));
					strcpy(maillon.lex,token);
					maillon.line=nline;
					col=ajout_queue(maillon,col);
					/*printf("%s , %s \n", col->val.type, col->val.lex);*/
				}
				else{
					maillon.type="DEC";
					maillon.lex=calloc(length,sizeof(*token));
					strcpy(maillon.lex,token);
					maillon.line=nline;
					col=ajout_queue(maillon,col);
					/*printf("%s , %s \n", col->val.type, col->val.lex);*/
				}
			}
			else{
				maillon.type="DEC";
				maillon.lex=calloc(length,sizeof(*token));
				strcpy(maillon.lex,token);
				maillon.line=nline;
				col=ajout_queue(maillon,col);
				/*printf("%s , %s \n", col->val.type, col->val.lex);*/
				}

			break;

		case ASC_OP:
			if(token[0]=='"') g+=1;
			if (g%2!=0){
				if (asc==0){
				 op_asc=calloc(512,sizeof(char));
			 	}
				asc=1;
					op_asc=strcat(op_asc,token);
					op_asc=strcat(op_asc," ");
					/*printf("%s\n",op_asc);*/
			}
			else{
				op_asc=strcat(op_asc,token);
				asc=0;
				maillon.type="ASC_OP";
				maillon.lex=calloc(length,sizeof(*op_asc));
				strcpy(maillon.lex,op_asc);
				maillon.line=nline;
				col=ajout_queue(maillon,col);
			}
		break;

		case ERROR:
			maillon.type="ERROR";
			maillon.lex=calloc(length,sizeof(*token));
			strcpy(maillon.lex,token);
			maillon.line=nline;
			col=ajout_queue(maillon,col);
		break;

			}
    /*puts("Affichage de la ligne:");
	affiche_liste(col);
	*/
	}

    return(col);
}





/**
 * @param in Input line of source code (possibly very badly written).
 * @param out Line of source code in a suitable form for further analysis.
 * @return nothing
 * @brief This function will prepare a line of source code for further analysis.
*/

/* note that MIPS assembly supports distinctions between lower and upper case*/
void lex_standardise( char* in, char* out ) {
    unsigned int i, j;

    for ( i= 0, j= 0; i< strlen(in); i++ ) {
        /* rajoute des espaces autour des symboles de ponctuation*/
		if ( in[i] == ',' || in[i] == ';' || in[i] == '(' || in[i] == ')' || in[i] == ':' || in[i] == '#'){
			out[j++]=' ';
			out[j++]=in[i];
			out[j++]=' ';
		}
		/* rajoute un espace avant le - */
		else if (in[i]=='-'){
			out[j++]=' ';
			out[j++]=in[i];
		}

		else if(i>0 && in[i]=='"'){
			if(in[i-1]!='\\'){
				out[j++]=' ';
				out[j++]=in[i];
				out[j++]=' ';
			}
		}

    else if(in[i]=='\n'){
    	out[j++]=' ';
			out[j++]='\n';
			out[j]='\0';
		}


        /* translate all spaces (i.e., tab) into simple spaces*/
    else if (isblank((int) in[i])) out[j++]=' ';
    else out[j++]=in[i];
    }
		/*out[j]='\0';*/
		printf("%s",out );
}
