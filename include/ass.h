#ifndef _ASS_H_
#define _ASS_H_


#include <stdlib.h>

void writeLineAssTxt(FILE* file,FILE* source,int line,int address,int code, int write);

void writeAss(FILE* source, etiqLISTE tab_etiq, int nblines, instLISTE p);

void writeSymtab(FILE* file,etiqLISTE tab);

void copyLine(FILE* file,FILE* source,int line);



#endif
