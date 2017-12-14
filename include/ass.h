#ifndef _ASS_H_
#define _ASS_H_


#include <stdlib.h>

void writeLineAssTxt(FILE* file,FILE* source,int line,int address,int code, int write);

void writeAss(FILE* source, etiqLISTE tab_etiq, int nblines, instLISTE ptext ,dirLISTE pdata, dirLISTE pbss, relocLISTE relocText, relocLISTE relocData);

void writeSymtab(FILE* file,etiqLISTE tab);

void copyLine(FILE* file,FILE* source,int line, int);

void writeReloc(FILE*, relocLISTE, relocLISTE);



#endif
