#ifndef _annexe
#define _annexe
#include <stdio.h>
#include "projet.h"


LISTE creer_liste(void);
int est_vide(LISTE l);
LISTE supprimer_tete(LISTE l);
LISTE ajout_queue(LEXEME* p_arc, LISTE l);
LISTE ajout_tete (LEXEME* p_arc, LISTE Liste);
LISTE supprimen(int n, LISTE l);
LISTE copie(LISTE l);
LISTE concat(LISTE l1, LISTE l2);



#endif
