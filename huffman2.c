#include <stdlib.h>
#include<stdio.h>
#include<string.h>

#include"Arvore.h"
#include"Floresta.h"
#include"Tabela.h"

#define TFL 200

void montarTabela(Tabela **tab){
	FILE * ponteiro= fopen("registros.dat","rb");
	TpInfo info;
	fread(&info,sizeof(TpInfo),1,ponteiro);
	while(!feof(ponteiro)){
		inserirTabelaOrd(&*tab,info);
		fread(&info,sizeof(TpInfo),1,ponteiro);
	}
	exibirTabela(*tab,1,1);
	fclose(ponteiro);
}

void montarArvore(Tree **raiz,Tabela *tab){
	int i;
	Tree *aux;
	novoNo(&*raiz);
	while(tab!=NULL){
		aux=*raiz;
		for(i=0;i<strlen(tab->info.codigo);i++){
			if(tab->info.codigo[i]=='0'){
				if(aux->esq==NULL)
					novoNo(&(aux->esq));
				aux=aux->esq;
			}
			else{
				if(aux->dir==NULL)
					novoNo(&(aux->dir));
				aux=aux->dir;
			}
		}
		aux->simbolo=tab->info.simbolo;
		tab=tab->prox;
	}
}

void pegaCodigo(char cod[],Byte b){
	cod[0]=b.bit.b7+48;
	cod[1]=b.bit.b6+48;
	cod[2]=b.bit.b5+48;
	cod[3]=b.bit.b4+48;
	cod[4]=b.bit.b3+48;
	cod[5]=b.bit.b2+48;
	cod[6]=b.bit.b1+48;
	cod[7]=b.bit.b0+48;
}

void trim(char frase[]){
	int i;
	for(i=strlen(frase)-1;frase[i]==' ';i--);
	frase[i+1]='\0';
}

void decodificarHuffman(Tree *raiz,Tabela *tab){
	Tree *aux;
	Tabela *tabAux;
	char frase[TFL]="",codigo[TFC];
	int i;
	FILE *ponteiro=fopen("codigoHuffman.dat","rb");
	Byte byte;
	codigo[8]='\0';
	fread(&byte,sizeof(char),1,ponteiro);
	aux=raiz;
	while(!feof(ponteiro)){
		pegaCodigo(codigo,byte);
		printf("%s  ",codigo);
		for(i=0;i<8;i++){
			if(codigo[i]=='0')
				aux=aux->esq;
			else
				aux=aux->dir;
			if(aux->esq == NULL && aux->dir ==NULL){
				BuscarSimbolo(tab,aux->simbolo,&tabAux);
				strcat(frase,tabAux->info.palavra);
				aux=raiz;
			}
		}
		fread(&byte,sizeof(char),1,ponteiro);
	}
	trim(frase);
	printf("\n\n%s",frase);
}

void executar(){
	Tabela *tab;
	Tree *raiz;
	init(&tab);
	initTree(&raiz);
	montarTabela(&tab);
	montarArvore(&raiz,tab);
	exibeArvore(raiz,-1);
	decodificarHuffman(raiz,tab);
}


int main(){
	executar();
	return 0;
}
