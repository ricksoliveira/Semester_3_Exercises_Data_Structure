/*
  	Lista 1 - Exercício 1
*/

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct REGISTRO{
	char nome[15];
	int RG;
	int CPF;
}REGISTRO;

typedef struct aux{
	REGISTRO reg;
	struct aux* proximo;
}ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct LISTA{
	PONT inicio;
}LISTA;

void barras(){
	
	int i;
	
	printf("\n\t");
	for(i=0; i<50; i++){
		printf("-");
	}
	printf("\n");
}

void inicializacao(LISTA* lis1){
	lis1->inicio = NULL;
}

void reinicializar(LISTA* lis1){
	
	PONT atual = lis1->inicio;
	
	while(atual != NULL){
		PONT apagar = atual;
		atual = atual->proximo;
		free(apagar);
	}
	lis1->inicio = NULL;
	
}

void adicionar_dado(LISTA* lis1, REGISTRO add){
	
	PONT novo, anterior;
	novo = (PONT) malloc(sizeof(ELEMENTO));
	novo->reg = add;
	novo->proximo = lis1->inicio;
	lis1->inicio = novo;
	
}

void exibir_lista(LISTA* lis1){
	
	PONT endereco = lis1->inicio;
	
	if(endereco == NULL){
		printf("\n\tNao tem registro nessa lista.");
		barras();
	}
	
	else{
		printf("\n\tLista dos dados\n");
		barras();
		while(endereco != NULL){
			printf("\n\tNome: %s\n", endereco->reg.nome);
			printf("\n\tRG: %d", endereco->reg.RG);
			printf("\n\tCPF: %d", endereco->reg.CPF);
			barras();
			endereco = endereco->proximo;
		}
	}
	
}

int retornar_tamanho(LISTA* lis1){
	
	PONT endereco = lis1->inicio;
	int tam = 0;
	
	while(endereco != NULL){
		tam++;
		endereco = endereco->proximo;
	}
	return tam;
	
}

void buscar(LISTA* lis1, char procurado[]){
	
	PONT endereco = lis1->inicio;
	
	while(endereco != NULL){
		if(!strcmp(procurado, endereco->reg.nome)){
			barras();
			printf("\n\tDados de \"%s\"\n", endereco->reg.nome);
			printf("\n\tRG: %d", endereco->reg.RG);
			printf("\n\tCPF: %d", endereco->reg.CPF);
			barras(); system("pause"); printf("\n");
			return;
		}
		endereco = endereco->proximo;
	}
	
}

PONT busca_deletar(LISTA* l1, char procurado[], PONT* ant){
	
	*ant = NULL;
	PONT atual = l1->inicio;
	
	while((atual != NULL) && (strcmp(procurado, atual->reg.nome))){
		*ant = atual;
		atual = atual->proximo;
	}
	
	if((atual != NULL) && (!strcmp(procurado, atual->reg.nome))){
		return atual;
	}
	return NULL;
}

bool deletar(LISTA* lis1, char del[]){
	
	PONT ant, i;
	
	i = busca_deletar(lis1, del, &ant);
	
	if(i == NULL){
		barras();
		printf("\n\t\tERRO!\n\t\tA pessoa \"%s\" não foi encontrada.\n", del);
		return false;
	}
	
	if(ant == NULL){
		lis1->inicio = i->proximo;
	}
	
	else{
		ant->proximo = i->proximo;
	}
	
	free(i);
	barras();
	printf("\n\t\tA pessoa \"%s\" foi deletada!\n", del);
	return true;
	
}

int main(){
	
	int menu;
	char procurado[15];
	LISTA* lista1;
	REGISTRO inserir;
	
	lista1 = (LISTA*) malloc(sizeof(LISTA));
	
	do{
		system("cls");
		printf("\n\t O que deseja fazer?\n");
		barras();
		printf("\n\t[1] - Inicializar sistema.\n");
		printf("\t[2] - Inserir novos dados.\n");
		printf("\t[3] - Buscar um registro.\n");
		printf("\t[4] - Exibir dados.\n");
		printf("\t[5] - Remover um registro\n");
		printf("\t[6] - Finalizar sistema.\n");
		printf("\t[7] - Sair.\n\t ");
		scanf("%d", &menu);
		
		switch(menu){
			
			case 1:
				inicializacao(lista1);
				barras();
				printf("\n\tSistema inicializado!\n");
				printf("\n\tPronto para receber dados.\n");
				barras(); printf("\n"); system("pause");
				break;
				
			case 2:
				barras();
				printf("\n\tDigite o nome da pessoa: ");
				scanf("%s", inserir.nome);
				printf("\n\tDigite o RG de \"%s\": ", inserir.nome);
				scanf("%d", &inserir.RG);
				printf("\n\tDigite o CPF de \"%s\": ", inserir.nome);
				scanf("%d", &inserir.CPF);
				adicionar_dado(lista1, inserir);
				break;
				
			case 3:
				barras();
				printf("\n\tDigite o nome que deseja procurar: ");
				scanf("%s", procurado);
				buscar(lista1, procurado);
				break;
				
			case 4:
				system("cls");
				exibir_lista(lista1);
				printf("\n\t\tQuantidade de membros: %d\n", retornar_tamanho(lista1));
				barras(); printf("\n"); system("pause");
				break;
				
			case 5:
				barras();
				printf("\n\tDigite o nome da pessoa para deletar: ");
				scanf("%s", procurado);
				deletar(lista1, procurado);
				barras(); printf("\n"); system("pause");
				break;
				
			case 6:
				reinicializar(lista1);
				barras();
				printf("\n\tSistema reinicializado!\n");
				printf("\n\tPronto para receber novos dados.\n");
				barras(); printf("\n"); system("pause");
				break;
				
			case 7:
				barras();
				printf("\n\t\tSaindo do programa...\n");
				barras();
				return 0;
				
			default:
				barras();
				printf("\n\tDigite um numero de 1 a 7.\n");
				barras();
				printf("\n");
				system("pause");
		}
		
	}while(menu != 7);
	
}
