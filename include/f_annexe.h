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
	char* optype_tab[3];
} instr_def;

/*Definition de la liste des etiquettes d'arrivée*/

typedef struct{
	char* nom;
	int arrivee;
	int decalage;
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
	int nb_op;
	OPERANDE op[3];
	int ligne;
	int bin;
	int hidden; 
} instruction;

struct instMAILLON{
	instruction val;
	struct instMAILLON* suiv;
};

typedef struct instMAILLON* instLISTE;

typedef struct{
	char* dir;
	int ligne;
	int decalage;
	char* symb_op;
	char* type_op;
} DIRECTIVE;


struct dirMAILLON{
	DIRECTIVE val;
	struct dirMAILLON* suiv;
};

typedef struct dirMAILLON* dirLISTE;

typedef struct{
	char* nom;
	char* zone;
	int decalage;
	int depart;
	char* type;
} relocETIQ;

struct relocMAILLON{
	relocETIQ val;
	struct relocMAILLON* suiv;
};

typedef struct relocMAILLON* relocLISTE;

typedef struct {
	instLISTE col_text;
	dirLISTE col_data;
	dirLISTE col_bss;
	etiqLISTE tab_etiq;
	relocLISTE reloc_text;
	relocLISTE reloc_data;
} Gram;

union element{
	char* rg;
	int bin;
};

typedef struct{
	union element rr1;
	union element rr2;
	union element rr3;
	union element rsa;
	int function;
} instr_bin_R;

typedef struct{
	union element ir1;
	union element ir2;
	char* imm;
} instr_bin_I;

typedef struct{
	char* ind;
} instr_bin_J;



union arg{
	instr_bin_R R;
	instr_bin_I I;
	instr_bin_J J;
};

typedef struct{
		char* nom;
		int opcode;
		char type;
		union arg arg;
} instr_def_bin;





LISTE creer_liste(void);
instLISTE creer_liste_inst(void);
dirLISTE creer_liste_dir(void);
etiqLISTE creer_liste_etiq(void);
relocLISTE creer_liste_reloc(void);
int est_vide(LISTE l);
LISTE supprimer_tete(LISTE l);
void supprimer_liste(LISTE l);
LISTE ajout_queue(LEXEME , LISTE );
LISTE ajout_tete (LEXEME, LISTE );
LISTE supprimen(int n, LISTE l);
LISTE copie(LISTE l);
void affiche_liste(LISTE l);
void affiche_liste_etiq(etiqLISTE l);
void affiche_liste_inst(instLISTE l);
void affiche_liste_dir(dirLISTE l);
void affiche_liste_reloc(relocLISTE l);
void nbmaillon(LISTE l);
LISTE concat(LISTE l1, LISTE l2);
instLISTE ajout_queue_inst(instruction inst, instLISTE liste);
dirLISTE ajout_queue_dir(DIRECTIVE dir, dirLISTE liste);
relocLISTE ajout_queue_reloc(relocETIQ etiq, relocLISTE liste);



#endif
