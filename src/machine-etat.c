

for( token = strtok( line, seps ); token!=NULL ; token = strtok( NULL, seps )) {	
	int length= strlength(token)
	int com =0;
	int ETAT=INIT;
	int t;
	int c;
	LEXEME maillon;
	LEXEME* pmaillon= &maillon;
	char commentaire[STRLEN];
	
	
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
			ETAT=NBR;}oken
		else if (token[0]=='(' || token[0]==')' ){
			ETAT=PAR;}
		else if (token[0]='\n'){
			ETAT=NL;}
		else{
			ETAT=ERROR;}
		break;
		
	case COMMENT: 
			if (com==0){
				c=-1
			}
			com=1
			if(token[0]!='\n'){
				for(t=0;t<length;t++){
					if (c>STRLEN-1){
						ETAT=ERROR
					}
					comentaire[c++]=token[t];
					}
				commentaire[c++]='\t';	
			}
			else{
				while(c<STRLEN){
					commentaire[c++]='\t';
				}	
				maillon->type="COMMENT";
				maillon->lex=commentaire;
				ajout-queue(col,maillon);
			}	
		break;		
			
	case DIR:
		for(t=1;t<length;t++){
			if(!isalpha(token[t])){
				ETAT=ERROR;}	
		maillon->type="DIR";
		maillon->lex=token;
		ajout-queue(col,maillon);
		break;		
		
	case REG:
		if(length>3) 
		maillon->type="REG";
		maillon->lex=token;
		ajout-queue(col,maillon);
		break;		
		
	case SYM:
		maillon->type="SYM";
		maillon->lex=token;
		ajout-queue(col,maillon);
		break;	
		
	case VIR:
		if (token[0] != ','){
			ETAT=ERROR;}
		maillon->type="VIR";
		maillon->lex=token;
		ajout-queue(col,maillon);
		break;
	
	case DP:
		if (token[0] != ':'){
			ETAT=ERROR;}
		maillon->type="DP";
		maillon->lex=token;
		ajout-queue(col,maillon);
		break;
	
	case PVIR:
		if (token[0] != ';'){
			ETAT=ERROR;}
		maillon->type="PVIR";
		maillon->lex=token;
		ajout-queue(col,maillon);
		break;
	
	case PAR:
		if (token[0]!='(' || token[0]!=')' ){
			ETAT=ERROR;}
		maillon->type="PAR";
		maillon->lex=token;
		ajout-queue(col,maillon);
		break;
	
	case NL:
		if (token[0] != '\n'){
			ETAT=ERROR;}
		maillon->type="NL";
		maillon->lex=token;
		ajout-queue(col,maillon);
		break;
		
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
		
	case HEXA:
		for(t=i+1;t<length;t++){
			if(!isxdigit(token[t])){
				ETAT=ERROR;}
		maillon->type="HEXA";
		maillon->lex=token;		
		ajout-queue(col,maillon);
		break;
		
	case DEC:
		for(t=i;t<length;t++){
			if(!isdigit(token[t])){
				ETAT=ERROR;}
		maillon->type="DEC";
		maillon->lex=token;		
		ajout-queue(col,maillon);
		break;	
		
	case ERROR;
			printf("Erreur dans la determination du token : %s \n",token)
		break;
		
	
	
	




























