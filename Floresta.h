

struct tpfloresta{
	Tree *no;
	struct tpfloresta *prox;
};

typedef struct tpfloresta Floresta;

void initFloresta(Floresta **f){
	*f=NULL;
}

void novaFloresta(Floresta **nova,Tree *no){
	*nova=(Floresta*)malloc(sizeof(Floresta));
	(*nova)->prox=NULL;
	(*nova)->no=no;
}

void enqueueFloresta(Floresta **f,Tree *no){
	Floresta *nova,*aux,*ant;
	novaFloresta(&nova,no);
	if(*f==NULL)
		*f=nova;
	else{
		if(no->frequencia<=(*f)->no->frequencia){
			nova->prox=*f;
			*f=nova;	
		}
		else{
			aux=ant=*f;
			while(aux!=NULL && no->frequencia>aux->no->frequencia){
				ant=aux;
				aux=aux->prox;
			}
			nova->prox=aux;
			ant->prox=nova;
		}
	}
}

void dequeueFloresta(Floresta **f,Tree **no){
	Floresta *aux=*f;
	*f=aux->prox;
	*no=aux->no;
	free(aux);
}

char isEmptyFloresta(Floresta *f){
	return f==NULL;
}

void mataFloresta(Floresta **floresta){
	Floresta *aux;
	while(*floresta!=NULL){
		aux=*floresta;
		*floresta=aux->prox;
		if(aux->no !=NULL)
			free (aux->no);
		free (aux);
	}
}

void exibeFloresta(Floresta *f){
	while(f!=NULL){
		printf("simb: %d freq: %d\n",f->no->simbolo,f->no->frequencia);
		f=f->prox;
	}
}
