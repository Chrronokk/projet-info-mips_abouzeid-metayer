enum {INIT,COMMENT,SYM,DIR,REG,NBR,DEC,HEXA,DP,VIR,PVIR,NL,PAR};

int com =0;
int ETAT=INIT;
switch(ETAT);

case INIT:
	if (token[0]=='#' || com ){
		ETAT=COMMENT;}
	else if (token[0]=='.'){
		ETAT=DIR;}
	else if (token[0]=='$'){
		ETAT=REG;}
	else if (isalpha(token)){
		ETAT=SYM;}
	else if (token[0] == ','){
		ETAT=VIR;}
	else if (token[0] == ':'){
		ETAT=DP;}
	else if (token[0] == ';'){
		ETAT=PVIR;}
	else if (isdigit(token[0]) || token[0]=='-')){
		ETAT=NBR;}
	else if (token[0]=='(' || token[0]==')' ){
		ETAT=PAR;
	else if (
		ETAT=NL;
	
	break;
	
case 	COMMENT:
		com=1
		if token == '\n'{
		
case DIR:
	maillon->type="DIR";
	maillon->token=token;
	ajout-queue(liste,maillon);
	break		
	
case REG:
	maillon->type="REG";
	maillon->token=token;
	ajout-queue(liste,maillon);
	break		
	
case SYM:
	maillon->type="SYM";
	maillon->token=token;
	ajout-queue(liste,maillon);
	break	
	
case VIR:
	maillon->type="VIR";
	maillon->token=token;
	ajout-queue(liste,maillon);
	break

case DP:
	maillon->type="DP";
	maillon->token=token;
	ajout-queue(liste,maillon);
	break

case PVIR:
	maillon->type="PVIR";
	maillon->token=token;
	ajout-queue(liste,maillon);
	break

case PAR:
	maillon->type="PAR";
	maillon->token=token;
	ajout-queue(liste,maillon);
	break

case NBR:
	int i=0;
	if (token[0]=='-'){
		i=1;
	}
	






		
		
