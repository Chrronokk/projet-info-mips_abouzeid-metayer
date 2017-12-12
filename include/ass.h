#ifndef _ASS_H_
#define _ASS_H_


#include <stdlib.h>

void writeLineAss(FILE* file, FILE* source, int line, int address, int code);


void* writeAss(etiqLISTE tab_etiq, int nlines);



#endif
