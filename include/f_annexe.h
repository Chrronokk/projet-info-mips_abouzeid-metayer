#ifndef _annexe
#define _annexe

typedef struct{
	char* type;
	char* lex;
} LEXEME;

struct maillon{
	LEXEME* val;
	struct maillon* suiv;
};

typedef struct maillon* LISTE;

LISTE creer_liste(void);
int est_vide(LISTE l);
LISTE supprimer_tete(LISTE l);
LISTE ajout_queue(LEXEME* , LISTE );
LISTE ajout_tete (LEXEME, LISTE );
LISTE supprimen(int n, LISTE l);
LISTE copie(LISTE l);
void affiche_liste(LISTE l);
void nbmaillon(LISTE l);
LISTE concat(LISTE l1, LISTE l2);



#endif
