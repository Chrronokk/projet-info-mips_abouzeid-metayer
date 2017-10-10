
/**
 * @file main.c
 * @author François Portet <francois.portet@imag.fr> from François Cayre
 * @brief Main entry point for MIPS assembler.
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <f_annexe.h>
#include <global.h>
#include <notify.h>
#include <lex.h>

/**
 * @param exec Name of executable.
 * @return Nothing.
 * @brief Print usage.
 *
 */
void print_usage( char *exec ) {
    fprintf(stderr, "Usage: %s file.s\n",exec);
}



/**
 * @param argc Number of arguments on the command line.
 * @param argv Value of arguments on the command line.
 * @return Whether this was a success or not.
 * @brief Main entry point for MIPS assembler.
 *
 */
int main ( int argc, char *argv[] ) {

    unsigned int 	nlines 	= 0;
    char         	 *file 	= NULL;

    /* exemples d'utilisation des macros du fichier notify.h */
    /* WARNING_MSG : sera toujours affiche */
    WARNING_MSG("Un message WARNING_MSG !");

    /* macro INFO_MSG : uniquement si compilé avec -DVERBOSE. Cf. Makefile*/
    INFO_MSG("Un message INFO_MSG : Debut du programme %s", argv[0]);

    /* macro DEBUG_MSG : uniquement si compilé avec -DDEBUG (ie : compilation avec make debug). Cf. Makefile */
    DEBUG_MSG("Un message DEBUG_MSG !");

    /* La macro suivante provoquerait l'affichage du message
       puis la sortie du programme avec un code erreur non nul (EXIT_FAILURE) */
    /* ERROR_MSG("Erreur. Arret du programme"); */
	int nb_instr=NULL;
	int* p_nb_instr=&nb_instr;
	instr_def* dictionnaire;
	
	dictionnaire=lecture_dico("dictionnaire.txt", p_nb_instr);

	/*
	printf("\n\n%s , %s , %s , %s\n", dictionnaire[0].symbole, dictionnaire[1].symbole, dictionnaire[2].symbole, dictionnaire[3].symbole);
	printf("%c , %c , %c , %c\n", dictionnaire[0].type, dictionnaire[1].type, dictionnaire[2].type, dictionnaire[3].type);
	printf("%d , %d , %d , %d\n\n\n", dictionnaire[0].nb_op, dictionnaire[1].nb_op, dictionnaire[2].nb_op, dictionnaire[3].nb_op);
	*/

	/*is_in_dico("LW",dictionnaire,*p_nb_instr);*/


    if ( argc <2 ) {
        print_usage(argv[0]);
        exit( EXIT_FAILURE );
    }


    file  	= argv[argc-1];


    if ( NULL == file ) {
        fprintf( stderr, "Missing ASM source file, aborting.\n" );
        exit( EXIT_FAILURE );
    }



    /* -------------- do the lexical analysis -------------------*/
	LISTE Col;
    Col=lex_load_file( file, &nlines);
	/*TODO Utiliser la fonction is_in_dico sur les symboles contenus dans Col*/ 

    DEBUG_MSG("source code got %d lines",nlines);

    /* --------------- Free memory and terminate ----------------*/

    /* TODO free everything properly*/
	free(dictionnaire);
    exit( EXIT_SUCCESS );
}

