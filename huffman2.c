#include <stdlib.h>
#include<stdio.h>
#include<string.h>

#include"Layout.h"
#include"Arvore.h"
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
		printf("[A] - Exibir tabela de palavras");
		l+=3;
		gotoxy(c,l);
		printf("[B] - Exibir arvore");
		l+=3;
		gotoxy(c,l);
		printf("[C] - Ver frase decodificada");
		l+=3;
		gotoxy(c,l);
		printf("[D] - Ver frase codificada");
		l+=3;
		gotoxy(c,l);
		printf("[E] - Exibir arvore em pe");
		l+=3;
		gotoxy(c,l);
		printf("[ESC] - Encerrar programa");
		l=27;
		gotoxy(c,l);
		printf("OPCAO: ");
		fflush(stdin);
		op=toupper(getche());
	}while(op!='A' && op!='B' && op!='C' && op!='D'  && op!='E' && op!='F' && op!=27 );
	return op;
}

void montarTabela(Tabela **tab){
	FILE * ponteiro= fopen("registros.dat","rb");
	TpInfo info;
	fread(&info,sizeof(TpInfo),1,ponteiro);
	while(!feof(ponteiro)){
		inserirTabelaOrd(&*tab,info);
		fread(&info,sizeof(TpInfo),1,ponteiro);
	}
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

void decodificarHuffman(Tree *raiz,Tabela *tab,char  frase[TFL]){
	Tree *aux;
	Tabela *tabAux;
	char codigo[TFC];
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
	char op,frase[TFL];
	Tabela *tab;
	Tree *raiz;
	init(&tab);
	initTree(&raiz);
	montarTabela(&tab);
	montarArvore(&raiz,tab);
	strcpy(frase,"");
	decodificarHuffman(raiz,tab,frase);
	do{
		op=Menu();
		switch(op){
			case 'A':
				system("cls");
				exibirTabela(tab,1,1);
				gotoxy(1,1);
				fflush(stdin);
				getch();
				break;
			case 'B':
				system("cls");
				exibeArvore(raiz,-1);
				gotoxy(1,1);
				fflush(stdin);
				getch();
				break;
			case 'C':
				system("cls");
				printf("A frase decodificada foi:\n %s\n ",frase);
				teste();
				exibirTabela(tab,1,4);
				gotoxy(1,1);
				fflush(stdin);
				getch();
				break;
			case 'D':
				system("cls");
				teste();
				exibirTabela(tab,1,4);
				gotoxy(1,1);
				fflush(stdin);
				getch();
				break;
			case 'E':
				system("cls");
				printaEmPe(raiz,1,1);
				gotoxy(1,1);
				fflush(stdin);
				getch();
				break;
		}
			
	}while(op!=27);
	mataTabela(&tab);
	mataArvore(&raiz);
}


int main(){
	executar();
	
	return 0;
}
