
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
#include <lex.h>
#include <f_annexe.h>

enum {INIT,COMMENT,SYM,DIR,REG,NBR,DEC,HEXA,DP,VIR,PVIR,NL,PAR,ERROR};



/**
 * @param line String of the line of source code to be analysed.
 * @param nline the line number in the source code.
 * @return should return the collection of lexemes that represent the input line of source code.
 * @brief This function performs lexical analysis of one standardized line.
 *
 */
void lex_read_line( char *line, int nline) {
	char *seps = " \t";
	char *token = NULL;
	char save[STRLEN];
	LISTE col=creer_liste();

    /* copy the input line so that we can do anything with it without impacting outside world*/
	memcpy( save, line, STRLEN );

    /* get each token*/
    
    

	for( token = strtok( line, seps ); token!=NULL ; token = strtok( NULL, seps )) {	
		int length= strlen(token);
		int com =0;
		int ETAT=INIT;
		int t;
		int c;
		LEXEME maillon;
		LEXEME* pmaillon= &maillon;
		char commentaire[STRLEN];
		
		
		switch(ETAT){
		
		case INIT:
			if (token[0]=='#' || com ){
				ETAT=COMMENT;}
			else if (token[0]=='.'){
				ETAT=DIR;}
			else if (token[0]=='$'){
				ETAT=REG;}
			else if (isalpha(token)){
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
			else if (token[0]=='\n'){
				ETAT=NL;}
			else{
				ETAT=ERROR;}
			break;
			
		case COMMENT: 
				if (com==0){
					c=-1;
				}
				com=1;
				if(token[0]!='\n'){
					for(t=0;t<length;t++){
						if (c>STRLEN-1){
							ETAT=ERROR;
						}
						commentaire[c++]=token[t];
						}
					commentaire[c++]='\t';	
				}
				else{
					while(c<STRLEN){
						commentaire[c++]='\t';
					}	
					maillon.type="COMMENT";
					maillon.lex=commentaire;
					ajout_queue(maillon,col);
				}	
			break;		
				
		case DIR:
			for(t=1;t<length;t++){
				if(!isalpha(token[t])){
					ETAT=ERROR;
				}
			}		
			maillon.type="DIR";
			maillon.lex=token;
			ajout_queue(maillon,col);
			break;		
			
		case REG:
			if(length>3) 
			maillon.type="REG";
			maillon.lex=token;
			ajout_queue(maillon,col);
			break;		
			
		case SYM:
			maillon.type="SYM";
			maillon.lex=token;
			ajout_queue(maillon,col);
			break;	
			
		case VIR:
			if (token[0] != ','){
				ETAT=ERROR;}
			maillon.type="VIR";
			maillon.lex=token;
			ajout_queue(maillon,col);
			break;
		
		case DP:
			if (token[0] != ':'){
				ETAT=ERROR;}
			maillon.type="DP";
			maillon.lex=token;
			ajout_queue(maillon,col);
			break;
		
		case PVIR:
			if (token[0] != ';'){
				ETAT=ERROR;}
			maillon.type="PVIR";
			maillon.lex=token;
			ajout_queue(maillon,col);
			break;
		
		case PAR:
			if (token[0]!='(' || token[0]!=')' ){
				ETAT=ERROR;}
			maillon.type="PAR";
			maillon.lex=token;
			ajout_queue(maillon,col);
			break;
		
		case NL:
			if (token[0] != '\n'){
				ETAT=ERROR;}
			com=0;
			maillon.type="NL";
			maillon.lex=token;
			ajout_queue(maillon,col);
			break;
			
		case NBR:
			;
			int i=0;
			if (token[0]=='-'){
				i=1;
			}
			if(token[i]=='0'){
				if (token[i+1]=='x'){
					ETAT=HEXA;
				}
				else{
					ETAT=DEC;
				}
			}
			
		case HEXA:
			for(t=i+1;t<length;t++){
				if(!isxdigit(token[t])){
					ETAT=ERROR;
				}
			}
			maillon.type="HEXA";
			maillon.lex=token;		
			ajout_queue(maillon,col);
			break;
			
		case DEC:
			for(t=i;t<length;t++){
				if(!isdigit(token[t])){
					ETAT=ERROR;
				}
			}
			maillon.type="DEC";
			maillon.lex=token;		
			ajout_queue(maillon,col);
			break;	
			
		case ERROR:
				printf("Erreur dans la determination du token : %s \n",token);
			break;
    }
	}
    return;
}

/**
 * @param file Assembly source code file name.
 * @param nlines Pointer to the number of lines in the file.
 * @return should return the collection of lexemes
 * @brief This function loads an assembly code from a file into memory.
 *
 */
void lex_load_file( char *file, unsigned int *nlines ) {

    FILE        *fp   = NULL;
    char         line[STRLEN]; /* original source line */
    char         res[2*STRLEN]; /* standardised source line, can be longer due to some possible added spaces*/



    fp = fopen( file, "r" );
    if ( NULL == fp ) {
        /*macro ERROR_MSG : message d'erreur puis fin de programme ! */
        ERROR_MSG("Error while trying to open %s file --- Aborts",file);
    }

    *nlines = 0;

    while(!feof(fp)) {

        /*read source code line-by-line */
        if (fgets( line, STRLEN-1, fp ) != NULL ) {
            line[strlen(line)-1] = '\0';  /* eat final '\n' */
            (*nlines)++;

            if ( 0 != strlen(line) ) {
                lex_standardise( line, res );
                lex_read_line(res,*nlines);
            }
        }
    }

    fclose(fp);
    return;
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
        /*TODO : ajouter les autres transformations*/
        
        /* rajoute des espaces autour des symboles de ponctuation*/
		if ( in[i] == ',' || in[i] == ';' || in[i] == '(' || in[i] == ')' || in[i] == ':' || in[i] == '#'){
			out[j++]=' ';
			out[j++]=in[i];
			out[j++]=' ';
		}
		
		/* rajoute un espace avant le - */
		if (in[i]=='-'){
			out[j++]=' ';
			out[j++]=in[i];
		}
		
		
			
        /* translate all spaces (i.e., tab) into simple spaces*/
        if (isblank((int) in[i])) out[j++]=' ';
        else out[j++]=in[i];
    
    }
    out[j++]='\0';
}




