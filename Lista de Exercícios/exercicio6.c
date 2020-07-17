/*
  	Lista 1 - Exercício 6
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct SITE{
	char nome[30];
	char link[50];
}SITE;

typedef struct aux{
	SITE site;
	struct aux* prox;
}ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct LISTA{
	PONT inicio;
}LISTA;

void adicionar(LISTA* lis1, SITE add){
	
	PONT novo;
	novo = (PONT) malloc(sizeof(ELEMENTO));
	novo->site = add;
	novo->prox = lis1->inicio;
	lis1->inicio = novo;
	
}

void printar(LISTA* lis1){		// printa os sites
	
	PONT endereco = lis1->inicio;
	
	if(endereco == NULL){
		return;
	}
	while(endereco != NULL){
		printf("\n%s\n", endereco->site.nome);
		printf("%s\n", endereco->site.link);
		endereco = endereco->prox;
	}
}

PONT busca_sequencialEXC(LISTA* l1, char procurado[], PONT* ant){	// busca o site anterior ao procurado
	
	*ant = NULL;
	PONT atual = l1->inicio;
	
	while((atual != NULL) && (strcmp(procurado, atual->site.nome))){
		*ant = atual;
		atual = atual->prox;
	}
	
	if((atual != NULL) && (!strcmp(procurado, atual->site.nome))){
		return atual;
	}
	return NULL;
}

bool excluir(LISTA* lis1, char del[], SITE guardar){	// exclui o site procurado na função abaixo e em seguida adiciona no inicio o conteudo da variavel Guardar
	
	PONT ant, i;
	i = busca_sequencialEXC(lis1, del, &ant);
	
	if(i == NULL){
		return false;
	}
	
	if(ant == NULL){
		lis1->inicio = i->prox;
	}
	
	else{
		ant->prox = i->prox;
	}
	free(i);
	adicionar(lis1, guardar);
	return true;
	
}

void procura(LISTA* lis1, char procurado[]){	// procura um site e o guarda na variável Guardar
	
	PONT posicao = lis1->inicio;
	SITE guardar;
	
	while(posicao != NULL){
		if(!strcmp(procurado, posicao->site.nome)){
			printf("%s\n", posicao->site.nome);
			printf("%s\n", posicao->site.link);
			printf("\n\n");
			guardar = posicao->site;
			break;
		}
		posicao = posicao->prox;
	}
	excluir(lis1, posicao->site.nome, guardar);
	
}

int main(){
	
	int i;
	char procurado[30];
	LISTA* lista1 = (LISTA*) malloc(sizeof(LISTA));
	lista1->inicio = NULL;
	SITE add;
	
	for(i=0; i<5; i++){
		system("cls");
		scanf("%s", add.nome);
		scanf("%s", add.link);
		adicionar(lista1, add);
	}
	
	system("cls");
	printar(lista1);
	printf("\n\n");
	scanf("%s", procurado);
	system("cls");
	procura(lista1, procurado);
	printf("\n\n");
	printar(lista1);
	
}
