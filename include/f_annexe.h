#ifndef _annexe
#define _annexe


/*Liste des lexemes*/

typedef struct{
	char* type;
	char* lex;
	int line;
} LEXEME;

struct maillon{
	LEXEME val;
	struct maillon* suiv;
};

typedef struct maillon* LISTE;


/*Structure de définition d'instruction*/

typedef struct{
	char* symbole;
	char type;
	int nb_op;
} instr_def;


/*Liste des etiquettes de départs*/

struct intMAILLON{
	int nligne;
	struct intMAILLON* suiv;
};

typedef struct intMAILLON* intLISTE;


/*Definition de la liste des etiquettes d'arrivée*/

typedef struct{
	char* nom;
	int arrivee;
	intLISTE departs;
} ETIQUETTE;



struct etiqMAILLON{
	ETIQUETTE* pval;
	struct etiqMAILLON* suiv;
};

typedef struct etiqMAILLON* etiqLISTE;








LISTE creer_liste(void);
int est_vide(LISTE l);
LISTE supprimer_tete(LISTE l);
LISTE ajout_queue(LEXEME , LISTE );
LISTE ajout_tete (LEXEME, LISTE );
LISTE supprimen(int n, LISTE l);
LISTE copie(LISTE l);
void affiche_liste(LISTE l);
void nbmaillon(LISTE l);
LISTE concat(LISTE l1, LISTE l2);


#endif
