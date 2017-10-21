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

/*Definition de la liste des etiquettes d'arrivée*/

typedef struct{
	char* nom;
	int arrivee;
	char* zone;
} ETIQUETTE;



struct etiqMAILLON{
	ETIQUETTE val;
	struct etiqMAILLON* suiv;
};

typedef struct etiqMAILLON* etiqLISTE;


typedef struct{
	char* nom;
	char* type;
	char* offset;
} OPERANDE;


typedef struct{
	char* symbole;
	int adresse;
	OPERANDE* op[3];
} instruction;

struct instMAILLON{
	instruction val;
	struct instMAILLON* suiv;
};

typedef struct instMAILLON* instLISTE;



LISTE creer_liste(void);
instLISTE creer_liste_inst(void);
int est_vide(LISTE l);
LISTE supprimer_tete(LISTE l);
LISTE ajout_queue(LEXEME , LISTE );
LISTE ajout_tete (LEXEME, LISTE );
LISTE supprimen(int n, LISTE l);
LISTE copie(LISTE l);
void affiche_liste(LISTE l);
void affiche_liste_etiq(etiqLISTE l);
void affiche_liste_inst(instLISTE l);
void nbmaillon(LISTE l);
LISTE concat(LISTE l1, LISTE l2);
instLISTE ajout_queue_inst(instruction inst, instLISTE liste);



#endif
