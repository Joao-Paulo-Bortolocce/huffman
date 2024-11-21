
#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio2.h>

#include"Layout.h"
#include"Arvore.h"
#include"Floresta.h"
#include"Tabela.h"

#define TFL 200

char Menu()
{
	int c,l;
	char op;
	do
	{
		LayoutMenu();
		gotoxy(25,3);
		printf("############ MENU ############");
		c=3;
		l=7;
		gotoxy(c,l);
		printf("[A] - Escolher texto");
		l+=3;
		gotoxy(c,l);
		printf("[B] - Codificar frase");
		l+=3;
		gotoxy(c,l);
		printf("[C] - Exibir tabela de palavras");
		l+=3;
		gotoxy(c,l);
		printf("[D] - Exibir arvore");
		l+=3;
		gotoxy(c,l);
		printf("[E] - Exibir tabela e arvore ");
		l+=3;
		gotoxy(c,l);
		printf("[F] - Ver frase codificada ");
		l+=3;
		gotoxy(c,l);
		printf("[G] - Exibir arvore em pe");
		l+=3;
		gotoxy(c,l);
		printf("[ESC] - Encerrar programa e");
		l++;
		gotoxy(c+8,l);
		printf("Gravar registros");
		l=29;
		gotoxy(40,l);
		printf("OPCAO: ");
		fflush(stdin);
		op=toupper(getche());
	}while(op!='A' && op!='B' && op!='C' && op!='D'  && op!='E' && op!='F' && op!='G' && op!=27 );
	return op;
}

void exibeTexto(char selecionado[], int col, int lin){
	char arq[50]="fraseOriginal", linha[TFL];
	strcat(arq,selecionado);
	strcat(arq,".txt");
	FILE * ponteiro= fopen(arq,"r");
	fgets(linha,TFL,ponteiro);
	while(!feof(ponteiro)){
		gotoxy(col,lin);
		printf("%s",linha);
		fgets(linha,TFL,ponteiro);
		
		lin++;
	}
	fclose(ponteiro);
	
	strcpy(arq,"frase");
	strcat(arq,selecionado);
	strcat(arq,".txt");
	ponteiro= fopen(arq,"r");
	fgets(linha,TFL,ponteiro);
	gotoxy(col,29);
	printf("FRASE QUE SERA CODIFICADA: %s",linha);
	fclose(ponteiro);
	
}

void escolherArquivo(char arq[],char selecionado[]){
	
	
	int c,l;
	char op;
	do
	{
		system("cls");
		Moldura();
		c=55;
		l=7;
		gotoxy(c,l);
		printf("O texto selecionado eh %s",selecionado);
		exibeTexto(selecionado,40,10);
		c=5;
		l=12;
		gotoxy(c,l);
		printf("[1] - Primeiro texto");
		l+=3;
		gotoxy(c,l);
		printf("[2] - Segundo texto");
		l+=3;
		gotoxy(c,l);
		printf("[3] - Terceiro texto");
		l+=3;
		gotoxy(c,l);
		printf("[ENTER] Confirmar texto atual ");
		l=27;
		gotoxy(c,l);
		printf("OPCAO: ");
		fflush(stdin);
		op=toupper(getche());
		if(op=='1')
			strcpy(selecionado,"1");
		else{
			if(op=='2')
				strcpy(selecionado,"2");
			else
				if(op=='3')
					strcpy(selecionado,"3");
		}
	}while(op!=13 );
	strcat(arq,selecionado);
}

void recebePalavras(Tabela **tab,char linha[]){
	int tl,i=0;
	char palavra[TFL];
	while(i<strlen(linha) && linha[i]!='\n'){
		for(tl=0;i<strlen(linha) && linha[i]!='\n' && linha[i]!=' ';i++,tl++)
			palavra[tl]=linha[i];
		palavra[tl]='\0';
		inserirTabela(&*tab,palavra);
		if(linha[i]==' '){
			palavra[0]=' ';
			palavra[1]='\0';
			inserirTabela(&*tab,palavra);
		}
		i++;
	}
}

void recebeFrase(Tabela **tab,char arq[]){
	char linha[TFL];
	FILE *ponteiro=fopen(arq,"r");
	fgets(linha,TFL,ponteiro);
	while(!feof(ponteiro)){
		recebePalavras(&*tab,linha);
		fgets(linha,TFL,ponteiro);
	}
	fclose(ponteiro);
}

void colocaSimbolos(Tabela *tab){
	int simb;
	for(simb=1;tab!=NULL;simb++){
		tab->info.simbolo=simb;
		tab=tab->prox;
	}
		
}

void ordenarFrequencia(Tabela **tab){
	int simbolo=1;
	Tabela *aux=*tab,*ant;
	*tab=NULL;
	if(aux!=NULL){ //Caso não seja informada nenhuma frase
		while(aux!=NULL){
			inserirTabelaOrd(&*tab,aux->info);
			simbolo++;
			ant=aux;
			aux=aux->prox;
			free (ant);
		}
	}
	colocaSimbolos(*tab);
}

void CriaFloresta(Floresta **floresta,Tabela *tab){
	initFloresta(&*floresta);
	Tree *no;
	while(tab!=NULL){
		criaNo(&no,tab->info.frequencia, tab->info.simbolo);
		enqueueFloresta(&*floresta,no);
		tab=tab->prox;
	}
}

void CriarArvoreHuffman(Floresta **floresta){
	Tree *no, *aux1,*aux2;
	/*system("cls");
	exibeFloresta(*floresta);
	fflush(stdin);
	getch();*/
	if(!isEmptyFloresta(*floresta)){
		dequeueFloresta(&*floresta,&aux1);
		if(!isEmptyFloresta(*floresta)){
			dequeueFloresta(&*floresta,&aux2);
			while(!isEmptyFloresta(*floresta)){
				criaNo(&no, aux1->frequencia+aux2->frequencia, 0);
				no->esq=aux1;
				no->dir=aux2;
				enqueueFloresta(&*floresta,no);
				/*system("cls");
				exibeFloresta(*floresta);
				fflush(stdin);
				getch();*/
				dequeueFloresta(&*floresta,&aux1);
				dequeueFloresta(&*floresta,&aux2);
				
			}
			criaNo(&no, aux1->frequencia+aux2->frequencia, 0);
			no->esq=aux1;
			no->dir=aux2;
			enqueueFloresta(&*floresta,no);
		}
		else
			enqueueFloresta(&*floresta,aux1);
		/*system("cls");
		exibeFloresta(*floresta);
		fflush(stdin);
		getch();*/
	}
}

void colocaCodHuffman(Tabela *tab,int simb,char codigo[TFC]){
	while(tab!=NULL && tab->info.simbolo!=simb){
		tab=tab->prox;
	}
	strcpy(tab->info.codigo,codigo);
}

void codigoHuffman(Tabela *tab,Tree *raiz,char codigo[TFC],int tl){
	if(raiz!=NULL){
		if(raiz->esq==NULL && raiz->dir==NULL)
			colocaCodHuffman(tab,raiz->simbolo,codigo);
		else{
			codigo[tl+1]='\0';
			codigo[tl]='0';
			codigoHuffman(tab,raiz->esq,codigo,tl+1);
			codigo[tl+1]='\0';
			codigo[tl]='1';
			codigoHuffman(tab,raiz->dir,codigo,tl+1);
		}
	}
}

void gerarCodigoHuffman(Tabela *tab,Tree *raiz){
	char codigo[TFC];
	codigo[0]='\0';
	codigoHuffman(tab,raiz,codigo,0);
}

char pegaBits(char cod[TFC]){
	Byte b;
	b.bit.b7=cod[0]-48;
	b.bit.b6=cod[1]-48;
	b.bit.b5=cod[2]-48;
	b.bit.b4=cod[3]-48;
	b.bit.b3=cod[4]-48;
	b.bit.b2=cod[5]-48;
	b.bit.b1=cod[6]-48;
	b.bit.b0=cod[7]-48;
	return b.cod;
}

void codificarFrase(Tabela *tab,char selecionado[]){
	Byte b;
	char frase[TFL],arq[50]="frase";
	strcat(arq,selecionado);
	strcat(arq,".txt");
	FILE * ponteiro = fopen("codigoHuffman.dat","wb");
	FILE * ptrLer = fopen(arq,"r");
	fgets(frase,TFL,ptrLer);
	fclose(ptrLer);
	int i,tl,j=0,k;
	Tabela *aux;
	char flag=0,palavra[TFL],codigo[TFC];
	codigo[8]='\0';
	for(i=0;i<strlen(frase);i++){
		for(tl=0;i<strlen(frase) && frase[i]!=' ' &&  frase[i]!='\n';i++,tl++)
			palavra[tl]=frase[i];
		palavra[tl]='\0';
		BuscarPalavra(tab,palavra,&aux);
		k=0;
		printf("%s - ",palavra);
		printf("%s\n",aux->info.codigo);
		while(k<strlen(aux->info.codigo)){
			codigo[j]=aux->info.codigo[k];
			k++;
			j=(j+1)%8;
			if(j==0){
				b.cod=pegaBits(codigo);
				fwrite(&b.cod,sizeof(char),1,ponteiro);
				//fwrite('a',sizeof(char),1,ponteiro);
				flag=0;
			}
		}
		if(frase[i]==' '){
			palavra[0]=' ';
			palavra[1]='\0';
			BuscarPalavra(tab,palavra,&aux);
			k=0;
			printf("'Espaco' - ",palavra);
			printf("%s\n",aux->info.codigo);
			while(k<strlen(aux->info.codigo)){
				codigo[j]=aux->info.codigo[k];
				k++;
				j=(j+1)%8;
				if(j==0){
					b.cod=pegaBits(codigo);
					fwrite(&b.cod,sizeof(char),1,ponteiro);
					flag=0;
				}
			}
		}
		
	}
	if(j>0){
		for(;j<8;j++)
			codigo[j]='0';
		b.cod=pegaBits(codigo);
		fwrite(&b.cod,sizeof(char),1,ponteiro);
	}
	fclose(ponteiro);
	printf("\n\tCodificado com sucesso!!");
}


void gravarRegistros(Tabela **tab){
	FILE * ponteiro=fopen("registros.dat","wb");
	TpInfo info;
	while(*tab!=NULL){
		removeTabela(&*tab,&info);
		info.frequencia=0;
		fwrite(&info,sizeof(TpInfo),1,ponteiro);
	}
	fclose(ponteiro);
}

void executar(){
	Tabela *tab;
	Floresta *floresta;
	Tree *raiz;
	init(&tab);
	initTree(&raiz);
	initFloresta(&floresta);
	char op,arq[50],selecionado[2]="1";
	do{
		op=Menu();
		switch(op){
			case 'A':
				mataArvore(&raiz);
				mataTabela(&tab);
				init(&tab);
				initTree(&raiz);
				initFloresta(&floresta);
				strcpy(arq,"fraseOriginal");
				escolherArquivo(arq,selecionado);
				strcat(arq,".txt");
				recebeFrase(&tab,arq);
				ordenarFrequencia(&tab);//Exclui os nós e insere de forma ordenada 
				CriaFloresta(&floresta,tab);
				CriarArvoreHuffman(&floresta);
				raiz=floresta->no;
				free(floresta);
				initFloresta(&floresta);
				gerarCodigoHuffman(tab,raiz);
				break;
			case 'B':
				system("cls");
				codificarFrase(tab,selecionado);
				fflush(stdin);
				getch();
				break;
			case 'C':
				system("cls");
				exibirTabela(tab,1,1);
				fflush(stdin);
				getch();
				break;
			case 'D':
				system("cls");
				exibeArvore(raiz,-1);
				fflush(stdin);
				getch();
				break;
			case 'E':
				system("cls");
				exibirTabela(tab,1,1);
				printf("\n\n");
				exibeArvore(raiz,-1);
				fflush(stdin);
				getch();
				break;
			case 'F':
				system("cls");
				teste();
				exibirTabela(tab,1,4);
				gotoxy(1,1);
				fflush(stdin);
				getch();
				break;
			case 'G':
				system("cls");
				printaEmPe(raiz,1,1);
				fflush(stdin);
				getch();
				break;
		}
		
	}while(op!=27);
	

	gravarRegistros(&tab);
	mataArvore(&raiz);
}

int main(){
	executar();
	return 0;
}
