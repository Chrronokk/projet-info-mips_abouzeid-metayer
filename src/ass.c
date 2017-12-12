#include <stdio.h>
#include <stdlib.h>
#include <f_annexe.h>
#include "ass.h"

/*TODO
gestion du nombre de lignes
Placer des lignes vides en mettant des adresses négatives

*/

void* writeAss(etiqLISTE tab_etiq){
    FILE* file = NULL;
    FILE* source = NULL;
    file= fopen("list.l","w+");
    source= fopen("tests/miam.s","r");
    int i;

    if (file==NULL || source==NULL){
        puts("ERREUR PENDANT LA CREATION DE LA LISTE D'ASSEMBLAGE");
        return NULL;
    }




    for(i=0;i<33;i++){
        writeLineAss(file,source,i,123,456);
    }

    writeSymtab(file,tab_etiq);

    /*
    writeReltext();
    writeRelData();
    */


    fclose(file);
    fclose(source);
    return NULL;
}



void writeLineAss(FILE* file,FILE* source,int line,int address,int code){
    char l[255] ="";

    /* Print le numero de ligne*/
    if (line<10) fprintf(file,"  ");
    else if (line<100) fprintf(file," ");
    fprintf(file,"%d ",line);

    if (address<0){
        fprintf(file,"                  ");
    }
    else{
        /*Print l'adresse et le code binaire*/
        fprintf(file,"%08x ",address);
        fprintf(file,"%08x ",code);
    }
    /*Ecriture de la ligne assembleur*/
    fgets(l,255,source);
    if (l[0]==(char)9){
        fprintf(file,"    %s",l+1);
    }
    else{
        fprintf(file,"%s",l);
    }
}

void writeSymtab(FILE* file,etiqLISTE tab){

    fprintf(file,"\n\n.symtab\n");

    etiqLISTE p=tab;

    while (p->suiv !=NULL){
        fprintf(file,"%4d\t%-4s:%08X\t%s\n",p->val.decalage,p->val.zone,p->val.arrivee,p->val.nom);
	p=p->suiv;
    }
    fprintf(file,"%4d\t%-4s:%08X\t%s\n",p->val.decalage,p->val.zone,p->val.arrivee,p->val.nom);
}
