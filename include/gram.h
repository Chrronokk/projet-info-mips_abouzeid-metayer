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



instr_def * lecture_dico(int* p_nb_instr);
int is_in_dico(char* symbole,instr_def* dictionnaire, int nb_instr);
void analyse_gram(LISTE);
