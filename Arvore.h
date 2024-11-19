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
		printf("(%d, %d)\n",raiz->simbolo,raiz->frequencia);
		exibeArvore(raiz->esq,n);
	}
}


