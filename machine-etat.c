enum {INIT,COMMENT,SYM,DIR,REG,NBR,DEC,HEXA,DP,VIR,P-VIR,NL,PAR};

int com =0
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
		ETAT=VIR;}
	else if (isdigit(token[0]) || token[0]=='-')){
		ETAT=PAR;}
	else if (token[0]=='(' || token[0]==')' ){
		ETAT=VIR;
	
	break;
	
case 	COMMENT:
		com=1
		if token == '\n'{
		
