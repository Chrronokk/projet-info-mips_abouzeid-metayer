
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
#include <gram.h>
#include <pseudo_instr.h>
#include <relocation.h>
#include <bin.h>
#include <ass.h>



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


    if ( argc <2 ) {
        print_usage(argv[0]);
        exit( EXIT_FAILURE );
    }


    file  	= argv[argc-1];


    if ( NULL == file ) {
        fprintf( stderr, "Missing ASM source file,00000024 aborting.\n" );
        exit( EXIT_FAILURE );
    }



  /* -------------- do the lexical analysis -------------------*/

  LISTE Col;
  Col=lex_load_file( file, &nlines);
  DEBUG_MSG("source code got %d lines",nlines);

  LISTE Col_mod;
  Col_mod=pseudo_instr(Col);


	/* --------------- Analyse grammaticale ---------------------*/

  Gram gram;

	gram.col_text=creer_liste_inst();
	gram.col_data=creer_liste_dir();
	gram.col_bss=creer_liste_dir();
	gram.tab_etiq=creer_liste_etiq();
  gram.reloc_text=creer_liste_reloc();
  gram.reloc_data=creer_liste_reloc();

  gram=analyse_gram(Col_mod);
  puts("Fin de l'analyse_gram");
  affiche_liste_etiq(gram.tab_etiq);
	affiche_liste_inst(gram.col_text);
	affiche_liste_dir(gram.col_data);
	affiche_liste_dir(gram.col_bss);
	affiche_liste_reloc(gram.reloc_text);
	affiche_liste_reloc(gram.reloc_data);

    /*FILE *fichier = NULL;
    fichier=fopen(file,"r");*/


  /*  writeAss(fichier,gram.tab_etiq,nlines,gram.col_text);*/

    /* --------------- Free memory and terminate ----------------*/



    /* TODO free everything properly*/
    exit( EXIT_SUCCESS );
}
