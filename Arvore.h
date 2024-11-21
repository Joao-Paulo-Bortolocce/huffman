struct tptree{
	int frequencia,simbolo;
	struct tptree *esq,*dir;
};

typedef struct tptree Tree;

void initTree(Tree **raiz){
	*raiz=NULL;
}

void novoNo(Tree **t){
	*t=(Tree*)malloc(sizeof(Tree));
	(*t)->esq=(*t)->dir=NULL;
	(*t)->frequencia=(*t)->simbolo=0;
}

void criaNo(Tree **t, int frequencia, int simbolo){
	novoNo(&*t);
	(*t)->frequencia=frequencia;
	(*t)->simbolo=simbolo;
}

void mataArvore(Tree **raiz){
	if(*raiz!=NULL){
		mataArvore(&(*raiz)->esq);
		mataArvore(&(*raiz)->dir);
		free(*raiz);
	}
}

void exibeArvore(Tree *raiz, int n){
	int i;
	if(raiz!=NULL){
		n++;
		exibeArvore(raiz->dir,n);
		for(i=0;i<5*n;i++)
			printf(" ");
		if(raiz->frequencia==0)
        	printf("(%d)\n", raiz->simbolo);
        else
			printf("(%d, %d)\n",raiz->simbolo,raiz->frequencia);
		exibeArvore(raiz->esq,n);
	}
}

int contaFilhos(Tree *raiz) {
    if (raiz == NULL)
        return 0;
    return 1 + contaFilhos(raiz->esq) + contaFilhos(raiz->dir);
}

void printaEmPe(Tree *raiz, int l, int ci) {
    if (raiz != NULL) {
        int c_esq = contaFilhos(raiz->esq);
        float posicao_atual = ci + 4.3 * c_esq;
        gotoxy((int)posicao_atual, l);
        if(raiz->frequencia==0)
        	printf("(%d)", raiz->simbolo);
        else
        	printf("(%d,%d)", raiz->simbolo, raiz->frequencia);
        printaEmPe(raiz->esq, l + 2, ci);              
        printaEmPe(raiz->dir, l + 2, posicao_atual + 7); 
    }
	
}


