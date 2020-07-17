#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <windows.h>
#include <locale.h>
#include <time.h>

#define MAX 50

typedef int TIPOCHAVE;

typedef struct REGISTRO{	// struct interna
	TIPOCHAVE chave;		// int chamado chave
}REGISTRO;

typedef struct LISTA{	// struct externa
	REGISTRO A[MAX];	// vetor da struct interna
	int num_ele;
}LISTA;

void inicializacao(LISTA* lis1){	// inicia a lista
	lis1->num_ele = 0;
}

void insercao(LISTA* lis1, int insert){		// insere valores no início da lista
	
	int k;
	
	for(k=lis1->num_ele; k > 0; k--){
		lis1->A[k].chave = lis1->A[k-1].chave;
	}
	lis1->A[k].chave = insert;
	lis1->num_ele++;
	
}

int retorno_quant(LISTA* lis1){		// retorna quantos numeros a lista tem
	return lis1->num_ele;
}

void exibir_ele(LISTA* lis1){		// exibe os elementos da lista
	
	int i;
	
	if(lis1->num_ele == 0){
		printf("\tA lista nao possui elementos.");
	}
	
	printf("\t");
	for(i=0; i < lis1->num_ele; i++){
		
		if(i < lis1->num_ele-1){
			printf("%d, ", lis1->A[i].chave);
		}
		
		else{
			printf("%d", lis1->A[i].chave);
		}
	}
	
}

int busca_sequencial(LISTA* lis1, TIPOCHAVE cha){	// busca um elemento da lista e devolve sua posição
	
	int i;
	
	for(i=0; i < lis1->num_ele; i++){
		if(cha == lis1->A[i].chave){
			printf("\n\tElemento encontrado no índice [%d]\n", i);
			return i;
		}
	}
	printf("\n\tElemento nao foi encontrado.\n");
	return -1;
	
}

bool adicionar_posicao_especifica(LISTA* lis1, TIPOCHAVE cha, int ind){	// adiciona um elemento à lista jogando os seguintes para a direita
	
	int i;
	
	if(lis1->num_ele == MAX){
		printf("\n\tERRO!\n\tLista cheia.\n");
		printf("\n");
		system("pause");
		return false;
	}
	
	else if(ind < 0){
		printf("\n\tERRO!\n\tIndice inexistente.\n");
		printf("\n");
		system("pause");
		return false;
	}
	
	else if(ind > lis1->num_ele){
		printf("\n\tERRO!\n\tIndice nao e o ultimo.\n");
		printf("\n");
		system("pause");
		return false;
	}
	
	for(i = lis1->num_ele; i > ind; i--){
		lis1->A[i] = lis1->A[i-1];
	}
	lis1->A[ind].chave = cha;
	lis1->num_ele++;
	printf("\n\tO elemento %d foi adicionado no indice %d da lista.\n", cha, ind);
	return true;
}

bool excluir_elemento(LISTA* lis1, TIPOCHAVE cha){	// exclui um elemento da lista trazendo os seguintes elementos para a esquerda
	
	int posicao, j;
	
	posicao = busca_sequencial(lis1, cha);
	
	if(posicao == -1){
		printf("\n");
		system("pause");
		return false;
	}
	
	for(j = posicao; j < lis1->num_ele-1; j++){
		lis1->A[j] = lis1->A[j+1];
	}
	lis1->num_ele--;
	printf("\n\tO elemento %d foi excluido da lista.\n", cha);
	return true;
	
}

void barras(){		// printa as divisórias entre as funções
	
	int i;
	
	printf("\n\t");
	for(i=0; i<80; i++){
		printf("-");
	}
	printf("\n");
}

int main(){
	
	int insert, i, menu_ini, quant, procurado, deletar, add, indice, continuar;
	LISTA* lista1;
	lista1 = (LISTA*) malloc(sizeof(LISTA));
	setlocale(LC_ALL, "Portuguese");
	
	inicializacao(lista1);
	
	do{		// laço que impede que o usuário digite um número negativo de elementos ou maior que o máximo
		system("cls");
		printf("\n\tDigite quantos termos ira adicionar ao inicio da lista: ");
		scanf("%d", &quant);
		
		if(quant > MAX || quant < 0){
			printf("\n\tErro, a lista deve ter entre 0 e 50 elementos.");
			Sleep(3000);
		}
	}while(quant > MAX || quant < 0);
	
	printf("\n\tDigite os elementos para serem adicionados: ");
	for(i=0; i < quant; i++){
		scanf("%d", &insert);
		insercao(lista1, insert);
	}
	
	do{
		system("cls");
		printf("\n\tElementos da lista do mais atual para o antigo:\n");
		exibir_ele(lista1);
		printf("\n\n\tQuantidade de elementos na lista: %d\n", retorno_quant(lista1));
		barras();
		printf("\n\t O que deseja fazer?\n");
		printf("\t[1] - Buscar um elemento na lista.\n");
		printf("\t[2] - Adicionar um elemento em uma posicao especifica.\n");
		printf("\t[3] - Excluir um elemento da lista.\n");
		printf("\t[4] - Reinicializar lista.\n");
		printf("\t[5] - Sair.\n\t ");
		
		scanf("%d", &menu_ini);
		switch (menu_ini){
			
			case 1:
				barras();
				printf("\n\tDigite o numero para procurar: ");
				scanf("%d", &procurado);
				busca_sequencial(lista1, procurado);
				barras();
				printf("\n");
				system("pause");
				break;
			
			case 2:
				if(lista1->num_ele == MAX){
					printf("\n\tLista cheia, nao e possivel adicionar nenhum elemento.\n");
					barras();
					printf("\n");
					system("pause");
					break;
				}
				
				else{
					barras();
					printf("\n\tDigite um elemento a ser adicionado: ");
					scanf("%d", &add);
					printf("\n\tDigite o indice do novo elemento: ");
					scanf("%d", &indice);
					adicionar_posicao_especifica(lista1, add, indice);
					barras();
					break;
				}
			
			case 3:
				barras();
				printf("\n\tDigite o numero que deseja excluir: ");
				scanf("%d", &deletar);
				excluir_elemento(lista1, deletar);
				barras();
				break;
			
			case 4:
				barras();
				inicializacao(lista1);
				printf("\n\tLista reiniciada!\n");
				barras();
				break;
			
			case 5:
				barras();
				printf("\n\tSaindo do programa...\n");
				return 0;
			
			default:
				printf("\n\tDigite um numero de 1 a 5.");
				Sleep(2000);
		}
		
	}while(menu_ini != 5);
	
	free(lista1);
}
