/**
 * @file lex.h
 * @author François Portet <francois.portet@imag.fr>
 * @brief Lexem-related stuff.
 *
 * Contains lexem types definitions, some low-level syntax error codes,
 * the lexem structure definition and the associated prototypes.
 */

#ifndef _LEX_H_
#define _LEX_H_


#include <stdio.h>

enum {COMMENT,SYM,DIR,REG,NBR,DEC,HEXA,DP,VIR,PVIR,NL,PAR,ASC_OP,ERROR};

LISTE	lex_read_line( char *, int);
LISTE	lex_load_file( char *, unsigned int * );
void	lex_standardise( char*, char*  );

#endif /* _LEX_H_ */
