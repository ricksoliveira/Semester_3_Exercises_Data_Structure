#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <windows.h>
#include <locale.h>
#include <time.h>

typedef struct REGISTRO{
	char nome[15];
	int level;
	int item_lvl;
}REGISTRO;

typedef struct aux{
	REGISTRO reg;
	struct aux* proximo;
}ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct LISTA{
	PONT inicio;
}LISTA;

void barras(){		// printa as divisórias entre as funções
	
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
	
	PONT endereco = lis1->inicio;
	
	while (endereco != NULL) {
		PONT apagar = endereco;
		endereco = endereco->proximo;
		free(apagar);
	}
	lis1->inicio = NULL;
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

void exibir_lista(LISTA* lis1){
	
	PONT endereco = lis1->inicio;
	
	if(endereco == NULL){
		printf("\n\t A lista não possui jogadores.\n");
		barras();
	}
	else{
		printf("\n\tJogadores da lista\n");
		barras();
		while(endereco != NULL){
			printf("\tNome: %s\n", endereco->reg.nome);
			printf("\n\tLevel: %d", endereco->reg.level);
			printf("\n\tItem Level: %d", endereco->reg.item_lvl);
			barras();
			endereco = endereco->proximo;
		}
	}
}

PONT busca_sequencial(LISTA* lis1, char procurado[]){
	
	PONT posicao = lis1->inicio;
	
	while(posicao != NULL){
		if(!strcmp(procurado, posicao->reg.nome)){
			return posicao;
		}
		posicao = posicao->proximo;
	}
	return NULL;
}

PONT busca_sequencialEXC(LISTA* l1, char procurado[], PONT* ant){
	
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

bool adicionar_jogador(LISTA* lis1, REGISTRO add){
	
	PONT novo, anterior;
	novo = (PONT) malloc(sizeof(ELEMENTO));
	novo->reg = add;
	novo->proximo = lis1->inicio;
	lis1->inicio = novo;
	return true;
	
}

bool excluir_jogador(LISTA* lis1, char del[]){
	
	PONT ant, i;
	
	i = busca_sequencialEXC(lis1, del, &ant);
	
	if(i == NULL){
		barras();
		printf("\n\t\tERRO!\n\t\tJogador \"%s\" não encontrado.\n", del);
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
	printf("\n\t\tO jogador \"%s\" foi deletado!\n", del);
	return true;
	
}

int main(){
	
	int menu;
	char deletar[15];
	LISTA* lista1;
	REGISTRO inserir;
	
	lista1 = (LISTA*) malloc(sizeof(LISTA));
	setlocale(LC_ALL, "Portuguese");
	
	inicializacao(lista1);
	time_t agora;
	time(&agora);
	
	do{	
		system("cls");
		printf("\n\tLista gerada pela primeira vez em:\n");
		printf("\t%s", ctime(&agora));
		barras();
		printf("\n\t O que deseja fazer?\n\n");
		printf("\t[1] - Adicionar um jogador no início da lista.\n");
		printf("\t[2] - Exibir lista e quantidade de jogadores.\n");
		printf("\t[3] - Excluir um jogador da lista.\n");
		printf("\t[4] - Reinicializar a lista.\n");
		printf("\t[5] - Sair.\n\t ");
		scanf("%d", &menu);
		
		switch(menu){
			
			case 1:
				barras();
				printf("\n\tDigite o nome do(a) jogador(a) a ser adicionado(a): ");
				scanf("%s", inserir.nome);
				printf("\n\tDigite o Level de %s: ", inserir.nome);
				scanf("%d", &inserir.level);
				printf("\n\tDigite o item Level de %s: ", inserir.nome);
				scanf("%d", &inserir.item_lvl);
				adicionar_jogador(lista1, inserir);
				break;
				
			case 2:
				system("cls");
				exibir_lista(lista1);
				printf("\n\t\tQuantidade de membros: %d\n", retornar_tamanho(lista1));
				barras();
				printf("\n");
				system("pause");
				break;
				
			case 3:
				barras();
				printf("\n\tDigite o nome do(a) jogador(a) a ser excluído: ");
				scanf("%s", deletar);
				excluir_jogador(lista1, deletar);
				barras();
				printf("\n");
				system("pause");
				break;
				
			case 4:
				barras();
				reinicializar(lista1);
				printf("\n\t\tLista reiniciada!\n");
				barras();
				printf("\n");
				system("pause");
				break;
				
			case 5:
				barras();
				printf("\n\t\tSaindo do programa...\n");
				barras();
				return 0;
				
			default:
				barras();
				printf("\n\t\tDigite um número de 1 a 5.\n");
				barras();
				printf("\n");
				system("pause");
		}
		
	}while(menu != 5);
	
}


















