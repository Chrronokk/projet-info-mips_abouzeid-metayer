enum {INIT,COMMENT,SYM,DIR,REG,NBR,DEC,HEXA,DP,VIR,PVIR,NL,PAR,ERROR};
int length= strlength(token)
int com =0;
int ETAT=INIT;
int t;
LEXEME maillon;
LEXEME* pmaillon=
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
		ETAT=PAR;}
	else if (token[0]='\n'){
		ETAT=NL;}
	else{
		ETAT=ERROR;}
	
	break;
	
case 	COMMENT: /* A COMPLETER */
		com=1
		if token == '\n'{
		
case DIR:
	for(t=1;t<length;t++){
		
	maillon->type="DIR";
	maillon->lex=token;
	ajout-queue(liste,maillon);
	break		
	
case REG:
	maillon->type="REG";
	maillon->lex=token;
	ajout-queue(liste,maillon);
	break		
	
case SYM:
	maillon->type="SYM";
	maillon->lex=token;
	ajout-queue(liste,maillon);
	break	
	
case VIR:
	maillon->type="VIR";
	maillon->lex=token;
	ajout-queue(liste,maillon);
	break

case DP:
	maillon->type="DP";
	maillon->lex=token;
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
	if(token[i]=='0'){
		if (token[i+1]=='x'){
			ETAT=HEXA;
		}
		else{
			ETAT=DEC;
		}
	}

case DEC




		
		
