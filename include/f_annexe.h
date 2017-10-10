#ifndef _annexe
#define _annexe

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


typedef struct{
	char* symbole;
	char type;
	int nb_op;
} instr_def;



enum {COMMENT,SYM,DIR,REG,NBR,DEC,HEXA,DP,VIR,PVIR,NL,PAR,ERROR};


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
instr_def * lecture_dico(char* Fichier, int* p_nb_instr);
int is_in_dico(char* symbole,instr_def* dictionnaire, int nb_instr);

#endif
