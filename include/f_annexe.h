#ifndef _annexe
#define _annexe
#include <stdio.h>
#include "projet.h"


Liste creer_liste(void);
Liste_proba creer_liste_proba(void);
int est_vide(Liste l);
Liste supprimer_tete(Liste l);
Liste ajout_queue(ARC* p_arc, Liste l);
Liste ajout_tete (ARC* p_arc, Liste liste);
Liste supprimen(int n, Liste l);
Liste copie(Liste l);
Liste concat(Liste l1, Liste l2);
File creer_file(void);
int file_vide(File f);
File enfiler(ARC* p_arc, File f);
ARC* defiler(File* f);



#endif
