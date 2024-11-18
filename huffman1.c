
#include <stdlib.h>
#include<stdio.h>
#include<string.h>

#include"Layout.h"
#include"Arvore.h"
#include"Floresta.h"
#include"Tabela.h"

#define TFL 200



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

void recebeFrase(Tabela **tab){
	char linha[TFL];
	FILE *ponteiro=fopen("fraseOriginal.txt","r");
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

void codificarFrase(Tabela *tab){
	Byte b;
	FILE * ponteiro = fopen("codigoHuffman.dat","wb");
	int i,tl,j=0,k;
	Tabela *aux;
	char flag=0,frase[TFL] = "O sol brilhava no ceu azul",palavra[TFL],codigo[TFC];
	codigo[8]='\0';
	for(i=0;i<strlen(frase);i++){
		for(tl=0;i<strlen(frase) && frase[i]!=' ';i++,tl++)
			palavra[tl]=frase[i];
		palavra[tl]='\0';
		BuscarPalavra(tab,palavra,&aux);
		k=0;
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
	
}

void teste(){// Teste para mostrar os bytes armazenados
	FILE * ponteiro=fopen("codigoHuffman.dat","rb");
	Byte b;
	fread(&b.cod,sizeof(char),1,ponteiro);
	while(!feof(ponteiro)){
		printf("%d",b.bit.b0);
		printf("%d",b.bit.b1);
		printf("%d",b.bit.b2);
		printf("%d",b.bit.b3);
		printf("%d",b.bit.b4);
		printf("%d",b.bit.b5);
		printf("%d",b.bit.b6);
		printf("%d\n",b.bit.b7);
		fread(&b.cod,sizeof(char),1,ponteiro);
	}
	fclose(ponteiro);
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
	recebeFrase(&tab);
	ordenarFrequencia(&tab);//Exclui os nós e insere de forma ordenada 
	CriaFloresta(&floresta,tab);
	CriarArvoreHuffman(&floresta);
	raiz=floresta->no;
	free(floresta);
	system("cls");
	exibeArvore(raiz,-1);
	printf("\n\n");
	gerarCodigoHuffman(tab,raiz);
	system("cls");
	exibirTabela(tab,1,1);
	codificarFrase(tab);
	teste();
	gravarRegistros(&tab);
}

int main(){
	executar();
	return 0;
}
