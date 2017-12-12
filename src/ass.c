#include <stdio.h>
#include <stdlib.h>
#include "ass.h"



void* writeAss(){
    FILE* file = NULL;
    FILE* source = NULL;
    file= fopen("list.l","w+");
    source= fopen("tests/miam.s","r");
    int i;
    
    if (file==NULL || source==NULL){
        puts("ERREUR PENDANT LA CREATION DE LA LISTE D'ASSEMBLAGE");
        return NULL;
    }


    /*while (du text){*/

    for(i=0;i<33;i++){
        writeLineAssText(file,source,i,123,456);
    }

    /*while (du data){
        writeLineAssData();
    }

    while (du bss){
        writeLineAssBss();
    }

    writeSymtab();
    writeReltext();
    writeRelData();


    */

    fclose(file);
    fclose(source);
    return NULL;
}



void writeLineAssText(FILE* file,FILE* source,int line,int address,int code){
    char l[255] ="";

    /* Print le numero de ligne*/
    if (line<10) fprintf(file,"   ");
    else if (line<100) fprintf(file,"  ");
    else if (line<1000) fprintf(file," ");
    fprintf(file,"%d ",line);

    if (address==-1){
        fprintf(file,"                  ");
    }
    else{
        /*Print l'adresse et le code binaire*/
        fprintf(file,"%08x ",address);
        fprintf(file,"%08x ",code);
    }
    /*Ecriture de la ligne assembleur*/
    fgets(l,255,source);
    fprintf(file,"%s",l);
}
