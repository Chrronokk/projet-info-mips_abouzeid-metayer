
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




/**
 * @param file Assembly source code file name.
 * @param nlines Pointer to the number of lines in the file.
 * @return should return the collection of lexemes
 * @brief This function loads an assembly code from a file into memory.
 *
 */
void lex_load_file( char *file, unsigned int *nlines) {

    FILE        *fp   = NULL;
    char         line[STRLEN]; /* original source line */
    char         res[2*STRLEN]; /* standardised source line, can be longer due to some possible added spaces*/
	LISTE col=creer_liste();


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
            	/*printf("%s",line);*/
                lex_standardise( line, res);
                printf("%s",res);
                /*lex_read_line(res,*nlines,col);*/
            }
        }
    }
	affiche_liste(col);
    fclose(fp);
    return;
}







enum {COMMENT,SYM,DIR,REG,NBR,DEC,HEXA,DP,VIR,PVIR,NL,PAR};



/**
 * @param line String of the line of source code to be analysed.
 * @param nline the line number in the source code.
 * @return should return the collection of lexemes that represent the input line of source code.
 * @brief This function performs lexical analysis of one standardized line.
 *
 */
void lex_read_line( char *line, int nline,LISTE col) {
	
	char *seps = " \t";
	char *token = NULL;
	char save[STRLEN];

    /* copy the input line so that we can do anything with it without impacting outside world*/
	
	memcpy( save, line, STRLEN );

    /* get each token*/
    
	for( token = strtok( line, seps ); token!=NULL ; token = strtok( NULL, seps )) {	

		int length= strlen(token);
		int com =0;
		int ETAT;
		int t;
		int c;
		int i;
		LEXEME maillon;
		char commentaire[STRLEN];

		if (token[0]=='#' || com ){
			/*printf("comment \n");*/
			ETAT=COMMENT;}
		else if (token[0]=='.'){
			/*printf("dir\n");*/
			ETAT=DIR;}
		else if (token[0]=='$'){
			/*printf("reg\n");*/
			ETAT=REG;}
		else if (isalpha(token[0])){
			/*printf("sym\n");*/
			ETAT=SYM;}
		else if (token[0] == ','){
			/*printf("vir\n");*/
			ETAT=VIR;}
		else if (token[0] == ':'){
			/*printf("dp\n");*/
			ETAT=DP;}
		else if (token[0] == ';'){
			/*printf("pvir\n");*/
			ETAT=PVIR;}
		else if (isdigit(token[0]) || token[0]=='-'){
			ETAT=NBR;}
		else if (token[0]=='(' || token[0]==')' ){
			ETAT=PAR;}
		else if (token[0]=='\0'){
			/*printf("nl\n");*/
			ETAT=NL;}
	
		switch(ETAT){	

		case COMMENT: 
				/*printf("passage\n");*/
				if (com==0){
					c=-1;
				}
				com=1;
				if(token[0]!='\0'){
					for(t=0;t<length;t++){
						commentaire[c++]=token[t];
						}
					commentaire[c++]='\t';	
				}
				else{
					while(c<STRLEN){
						commentaire[c++]='\t';
					}
					com=0;	
					maillon.type="COMMENT";
					maillon.lex=commentaire;
					printf("%s \n", maillon.lex);
					col=ajout_queue(maillon,col);
					printf("passage2\n");
					printf("%s , %s \n", col->val->type, col->val->lex);
				}	
			break;		
				
		case DIR:
			maillon.type="DIR";
			maillon.lex=token;
			col=ajout_queue(maillon,col);
			break;		
			
		case REG: 
			maillon.type="REG";
			maillon.lex=token;
			col=ajout_queue(maillon,col);
			break;		
			
		case SYM:
			maillon.type="SYM";
			maillon.lex=token;
			col=ajout_queue(maillon,col);
			break;	
			
		case VIR:
			maillon.type="VIR";
			maillon.lex=token;
			col=ajout_queue(maillon,col);
			break;
		
		case DP:
			maillon.type="DP";
			maillon.lex=token;
			col=ajout_queue(maillon,col);
			break;
		
		case PVIR:
			maillon.type="PVIR";
			maillon.lex=token;
			col=ajout_queue(maillon,col);
			break;
		
		case PAR:
			maillon.type="PAR";
			maillon.lex=token;
			col=ajout_queue(maillon,col);
			break;
		
		case NL:
			com=0;
			maillon.type="NL";
			maillon.lex=token;
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
					maillon.lex=token;		
					col=ajout_queue(maillon,col);
				}
				else{	
					maillon.type="DEC";
					maillon.lex=token;		
					col=ajout_queue(maillon,col);
				}
			}
			else{
				maillon.type="DEC";
				maillon.lex=token;		
				col=ajout_queue(maillon,col);
				}
			
			break;
		}		
    }
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
		else if (in[i]=='-'){
			out[j++]=' ';
			out[j++]=in[i];
		}
		

			
        /* translate all spaces (i.e., tab) into simple spaces*/
        else if (isblank((int) in[i])) out[j++]=' ';
        

        else out[j++]=in[i];
        
   
    }
    out[j++]=' ';
    out[j++]='\0';
}




