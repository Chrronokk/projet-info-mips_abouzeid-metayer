#include <stdio.h>
#include <stdlib.h>
#include <f_annexe.h>
#include <global.h>
#include <string.h>
#include "ass.h"

void writeAss(FILE* source, etiqLISTE tab_etiq, int nblines, instLISTE ptext ,dirLISTE pdata, dirLISTE pbss, relocLISTE relocText, relocLISTE relocData){
    FILE* file = NULL;


    file= fopen("list.l","w+");
    int i, write;
    int fintext=0;
    int findata=0;
    int finbss=FALSE;

    if (file==NULL || source==NULL){
        puts("ERREUR PENDANT LA CREATION DE LA LISTE D'ASSEMBLAGE");
        return;
    }



    for(i=0;i<nblines;i++){
        printf("On compare %d et %d\n",i+1,ptext->val.ligne);

        if (ptext->val.ligne==i+1 && fintext<2){
            puts("ecriture de l'instruction");
            if (fintext==1) fintext++;
            /*printf("Instruction trouvée ligne %d\n", i);*/
            write=TRUE;
            while (ptext->val.ligne==i+1){

                printf("Boucle while pour la ligne %d\n",ptext->val.ligne);
                writeLineAssTxt(file,source,i+1,ptext->val.adresse,456,write);
                write=FALSE;
                if (fintext<2) ptext=ptext->suiv;
                if (fintext==2) break;
            }
            if (ptext->suiv == NULL && fintext ==0){
                write=FALSE;
                fintext ++;
            }


        }
        else if(findata == 0 && pdata->val.ligne==i+1){
            if (pdata->val.ligne==i+1){
                puts("Ecriture data");
                fprintf(file,"%3d %08X %08X ",pdata->val.ligne,pdata->val.decalage,999);
                copyLine(file, source,i+1,FALSE);
                if (pdata->suiv==NULL){
                    findata =1;
                    puts("Fin du data");
                }
                if (findata==0) pdata=pdata->suiv;
            }
        }
        else if(pbss->val.ligne==i+1 && finbss ==FALSE){
            puts("ecriture bss");
            fprintf(file,"%3d %08X %08X ",pbss->val.ligne,pbss->val.decalage,999);
            copyLine(file, source,i+1,FALSE);
            if (pbss->suiv==NULL){
                finbss = TRUE;
            }
            if (finbss==FALSE) pbss=pbss->suiv;
        }
        else {
            puts("Copie de la ligne");
            copyLine(file,source,i+1,TRUE);
        }
    }
    writeSymtab(file,tab_etiq);

    writeReloc(file, relocText, relocData);



    fclose(file);
    fclose(source);
    return;
}

void copyLine(FILE* file,FILE* source,int line,int full){
    char l[255] ="";

    if (full==TRUE){
        printf("line %d copied\n",line);
        fprintf(file,"%3d                   ",line);
    }

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
    fprintf(file,"\n.symtab\n");

    etiqLISTE p=tab;

    while (p->suiv !=NULL){
        fprintf(file,"%3d\t%-4s:%08X\t%s\n",p->val.ligne,p->val.zone,p->val.arrivee,p->val.nom);
        p=p->suiv;
    }
    puts("Ecriture d'un symbole");
    fprintf(file,"%3d\t%-4s:%08X\t%s\n",p->val.ligne,p->val.zone,p->val.arrivee,p->val.nom);
}





void writeReloc(FILE* file,relocLISTE relocText, relocLISTE relocData){

    relocLISTE ptext = relocText;
    relocLISTE pdata = relocData;

    if(relocText !=NULL){
        fprintf(file,"\nrel.text\n");
        while(ptext->suiv !=NULL){
            fprintf(file,"%08x    %-11s  %-4s:%08x  %s\n",ptext->val.decalage,ptext->val.type,ptext->val.zone,1234,ptext->val.nom);
            ptext=ptext->suiv;
        }
        fprintf(file,"%08x    %-11s  %-4s:%08x  %s\n",ptext->val.decalage,ptext->val.type,ptext->val.zone,1234,ptext->val.nom);
    }

    if(relocData !=NULL){
        fprintf(file,"\nrel.data\n");
        while(pdata->suiv !=NULL){
            fprintf(file,"%08x    %-11s  %-4s:%08x  %s\n",pdata->val.decalage,pdata->val.type,pdata->val.zone,1234,pdata->val.nom);
            pdata=pdata->suiv;
        }
        fprintf(file,"%08x    %-11s  %-4s:%08x  %s\n",pdata->val.decalage,pdata->val.type,pdata->val.zone,1234,pdata->val.nom);
    }

}
