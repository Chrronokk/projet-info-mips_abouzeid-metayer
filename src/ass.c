#include <stdio.h>
#include <stdlib.h>
#include <f_annexe.h>
#include <global.h>
#include <string.h>
#include "ass.h"

void writeAss(FILE* source, etiqLISTE tab_etiq, int nblines, instLISTE p){
    FILE* file = NULL;
    file= fopen("list.l","w+");
    int i, write;
    affiche_liste_inst(p);

    if (file==NULL || source==NULL){
        puts("ERREUR PENDANT LA CREATION DE LA LISTE D'ASSEMBLAGE");
        return;
    }

    /* Ecriture du .text */

    for(i=0;i<nblines;i++){
        /*printf("On compare %d et %d\n",i,p->val.ligne);*/
        if (p->val.ligne==i+1){
            /*printf("Instruction trouvée ligne %d\n", i);*/
            write=TRUE;
            while (p->val.ligne==i+1){

                printf("Boucle while pour la ligne %d\n",p->val.ligne);
                writeLineAssTxt(file,source,i+1,p->val.adresse,456,write);
                write=FALSE;
                p=p->suiv;


            }
            if (p->suiv == NULL){
                writeLineAssTxt(file,source,i+1,p->val.adresse,456,write);
                write=FALSE;

            }
        }
        else {
            copyLine(file,source,i+1);
        }
    }
    writeSymtab(file,tab_etiq);
    /*
    writeReltext();
    writeRelData();
    */


    fclose(file);
    fclose(source);
    return;
}

void copyLine(FILE* file,FILE* source,int line){
    char l[255] ="";
    printf("line %d copied\n",line);
    fprintf(file,"%3d                   ",line);

    fgets(l,255,source);
    if (l[0]==(char)9){
        fprintf(file,"    %s",l+1);
    }
    else{
        fprintf(file,"%s",l);
    }
}

void writeLineAssTxt(FILE* file,FILE* source,int line,int address,int code, int write){
    printf("line %d written\n",line);
    char l[255] ="";

    /* Ecriture de la ligne et du code */

    fprintf(file,"%3d %08X %08X ",line, address, code);

    if (write==TRUE){
        puts("Writing");
        fgets(l,255,source);
        if (l[0]==(char)9){
            fprintf(file,"    %s",l+1);
        }
        else{
            fprintf(file,"%s",l);
        }
    }
    if (write==FALSE){
        puts("Not Writing");
        fprintf(file,"%s\n",l);
    }


    /*fprintf(file,"\n");*/

}










    /*char l[255] ="";

    fprintf(file,"%3d ",line);

    if (address<0){
        fprintf(file,"                  ");
    }
    else{
        Print l adresse et le code binaire
        fprintf(file,"%08x ",address);
        fprintf(file,"%08x ",code);
    }
    Ecriture de la ligne assembleur
    fgets(l,255,source);
    if (l[0]==(char)9){
        fprintf(file,"    %s",l+1);
    }
    else{
        fprintf(file,"%s",l);
    }
}
*/

void writeSymtab(FILE* file,etiqLISTE tab){
    puts("--------------------");
    fprintf(file,"\n.symtab\n");

    etiqLISTE p=tab;

    while (p->suiv !=NULL){
        fprintf(file,"%3d\t%-4s:%08X\t%s\n",p->val.decalage,p->val.zone,p->val.arrivee,p->val.nom);
        p=p->suiv;
    }
    fprintf(file,"%3d\t%-4s:%08X\t%s\n",p->val.decalage,p->val.zone,p->val.arrivee,p->val.nom);
}
