#define TFP 50
#define TFC 20

struct bits{
	unsigned char b7:1; 
	unsigned char b6:1; 
	unsigned char b5:1; 
	unsigned char b4:1; 
	unsigned char b3:1; 
	unsigned char b2:1; 
	unsigned char b1:1; 
	unsigned char b0:1;
};

union byte{
	unsigned char cod;
	struct bits bit;
};

typedef union byte Byte;

struct tpinfo{
	int simbolo, frequencia;
	char palavra[TFP],codigo[TFC];
};

typedef struct tpinfo TpInfo;

struct tptabela{
	TpInfo info;
	struct tptabela *prox;
};

typedef struct tptabela Tabela;

void init(Tabela **t){
	*t=NULL;
}

void NovaInfo(char palavra[],int simbolo, Tabela **nova){
	*nova = (Tabela*)malloc(sizeof(Tabela));
	(*nova)->prox = NULL;
	(*nova)->info.simbolo=simbolo;
	strcpy((*nova)->info.palavra,palavra);
	(*nova)->info.frequencia=0;
}

char BuscarSimbolo(Tabela *t,int simb,Tabela **aux){
	*aux=t;
	while(*aux!=NULL && (*aux)->info.simbolo!=simb)
		*aux=(*aux)->prox;
	if(*aux!=NULL)
		return 1;
	return 0;
}

char BuscarPalavra(Tabela *t,char palavra[],Tabela **aux){
	*aux=t;
	while(*aux!=NULL && stricmp((*aux)->info.palavra,palavra))
		*aux=(*aux)->prox;
	if(*aux!=NULL)
		return 1;
	return 0;
}

void inserirTabela(Tabela **t, char palavra[]){ //Se a palavra ja estiver na lista ele apenas acidiona frequencia, caso contrário adiciona na lista
	Tabela *aux,*nova;
	if(!BuscarPalavra(*t,palavra,&aux)){
		NovaInfo(palavra,0,&nova);

		aux=*t;
		if(aux==NULL)
			*t=nova;
		else{
			while(aux->prox!=NULL)
				aux=aux->prox;
			aux->prox=nova;
		}
		aux=nova;
	}
	aux->info.frequencia++;
	
}


void inserirTabelaOrd(Tabela **t, TpInfo info){ //Insere de acordo com frequencia decrescente
	Tabela *aux,*ant,*nova;
	nova=(Tabela*)malloc(sizeof(Tabela));
	nova->prox=NULL;
	nova->info=info;
	if(*t==NULL)
		*t=nova;
	else{
		if(info.frequencia>(*t)->info.frequencia){
			nova->prox=*t;
			*t=nova;
		}
		else{
			ant=aux=*t;
			while(aux!=NULL && info.frequencia<=aux->info.frequencia){
				ant=aux;
				aux=aux->prox;
			}
			ant->prox=nova;
			nova->prox=aux;	
		}
	}	
}


void removeTabela(Tabela **t,TpInfo *info){
	Tabela *aux=*t;
	*t=aux->prox;
	*info=aux->info;
	free (aux);
}

void exibirTabela(Tabela *t, int colunaInicial, int linhaInicial){

	int i, j, vet[4],aux;
    vet[0] = colunaInicial+20;
    for(i=1;i<4;i++)
    	vet[i]=vet[i-1]+20;
    if(t->info.frequencia==0)
    	vet[3]=vet[2];

    // Topo da caixa
    gotoxy(colunaInicial, linhaInicial);
    printf("%c", 201); // Canto superior esquerdo

    for (i = colunaInicial + 1; i < vet[3]; i++) {
        gotoxy(i, linhaInicial);
        if (i == vet[0] || i == vet[1] || i == vet[2] || i == vet[3])
            printf("%c", 203); // Divisões de colunas
        else
            printf("%c", 205); // Linha horizontal
    }

    gotoxy(vet[3], linhaInicial); 
    printf("%c", 187); // Canto superior direito


    i = linhaInicial+1;
   
    gotoxy(colunaInicial, i);
    printf("%c", 186); // Borda esquerda
    gotoxy(vet[0], i);
    printf("%c", 186); // Divisória
    gotoxy(vet[1], i);
    printf("%c", 186);
	gotoxy(vet[2], i);
    printf("%c", 186); // Divisória
    gotoxy(vet[3], i);
    printf("%c", 186); // Borda direita

    aux=strlen("Palavra")/2;
   	gotoxy((colunaInicial+vet[0])/2 -aux, i);
    printf("PALAVRA");

    aux=strlen("Simbolo")/2;
    gotoxy((vet[0]+vet[1])/2 -aux, i);
    printf("SIMBOLO");
    
    aux=strlen("Codigo")/2;
    gotoxy((vet[1]+vet[2])/2 - aux, i);
   	printf("CODIGO");
    
    if(vet[2]!=vet[3]){
    	aux=strlen("Frequencia")/2;
		gotoxy((vet[2]+vet[3])/2 -aux, i);
   		printf("FREQUENCIA");
    }
    
   	
   	

    // Linha divisória inferior
    i++;
    gotoxy(colunaInicial, i);
    printf("%c", 204); // Divisão esquerda

    for (j = colunaInicial + 1; j < vet[3]; j++) {
        gotoxy(j, i);
        if (j == vet[0] || j == vet[1] || j == vet[2] || j == vet[3])
            printf("%c", 206); // Divisões de colunas
        else
            printf("%c", 205); // Linha horizontal
    }

    gotoxy(vet[3], i);
    printf("%c", 185); // Divisão direita
    
    while (t != NULL) {
        i++;
        gotoxy(colunaInicial, i);
        printf("%c", 186); // Borda esquerda
        gotoxy(vet[0], i);
        printf("%c", 186); // Divisória
        gotoxy(vet[1], i);
        printf("%c", 186);
		gotoxy(vet[2], i);
        printf("%c", 186); // Divisória
        gotoxy(vet[3], i);
        printf("%c", 186); // Borda direita

		if(t->info.palavra[0]==' '){
			aux=strlen("'Espaco'")/2;
       		gotoxy((colunaInicial+vet[0])/2 -aux, i);
        	printf("'Espaco'");
		}
		else{
			aux=strlen(t->info.palavra)/2;
       		gotoxy((colunaInicial+vet[0])/2 -aux, i);
        	printf("%s", t->info.palavra);
		}
        

        
        gotoxy((vet[0]+vet[1])/2 -1, i);
        printf("%d", t->info.simbolo);
        aux=strlen(t->info.codigo)/2;
		gotoxy((vet[1]+vet[2])/2 -aux, i);
		printf("%s", t->info.codigo);
       	
       	if(vet[2]!=vet[3]){
		    gotoxy((vet[2]+vet[3])/2 - 1, i);
	       	printf("%d", t->info.frequencia);	
    	}
        

        // Linha divisória inferior
        i++;
        gotoxy(colunaInicial, i);
        printf("%c", 204); // Divisão esquerda

        for (j = colunaInicial + 1; j < vet[3]; j++) {
            gotoxy(j, i);
            if (j == vet[0] || j == vet[1] || j == vet[2] || j == vet[3])
                printf("%c", 206); // Divisões de colunas
            else
                printf("%c", 205); // Linha horizontal
        }

        gotoxy(vet[3], i);
        printf("%c", 185); // Divisão direita

        // Próximo elemento da pilha
        t = t->prox; 
    }

    // Base da caixa
    gotoxy(colunaInicial, i);
    printf("%c", 200); // Canto inferior esquerdo

    for (j = colunaInicial + 1; j < vet[3]; j++) {
        gotoxy(j, i);
        if (j == vet[0] || j == vet[1] || j == vet[2] || j == vet[3])
            printf("%c", 202); // Divisões de colunas
        else
            printf("%c", 205); // Linha horizontal
    }

    gotoxy(vet[3], i);
    printf("%c", 188); // Canto inferior direito
}

