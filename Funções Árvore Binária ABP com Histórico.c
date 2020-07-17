#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5

typedef int TIPOCHAVE;

typedef struct aux{
	TIPOCHAVE chave;
	struct aux *esq;
	struct aux *dir;
}NO;

typedef struct REGISTRO{
	TIPOCHAVE chave_hist;
}REGISTRO;

typedef struct BIN{
	REGISTRO A[MAX];
	int num_ele;
}BIN;

typedef NO* PONT;

PONT inicializar(){
	return(NULL);
}

void inicializacao(BIN* bi){
	bi->num_ele = 0;
}

void inserir_bin(BIN* bi, int insert){
	
	int k;
	
	for(k=bi->num_ele; k > 0; k--){
		bi->A[k].chave_hist = bi->A[k-1].chave_hist;
	}
	bi->A[k].chave_hist = insert;
	bi->num_ele++;
	
}

void barras(){
	
	int i;
	
	printf("\n  ");
	for(i=0; i<80; i++){
		printf("-");
	}
	printf("\n");
}

void barras2(){
	
	int i;
	
	printf("\n  ");
	for(i=0; i<60; i++){
		printf("_");
	}
	printf("\n");
}

void exibir_bin(BIN* bi){
	
	int i;
	
	barras2();
	for(i=0; i < bi->num_ele; i++){
		time_t agora;
		time(&agora);
		printf("\n\t| %d | ", bi->A[i].chave_hist);
		printf(" ~~ Item deletado em: ");
		printf("%s", ctime(&agora));
		barras2();
	}
	
	for(i=0; i < 5-bi->num_ele; i++){
		printf("\n\t| Vazio |\n");
		barras2();
	}
}

int busca_sequencial(BIN* bi, TIPOCHAVE ch){
	int i;
	
	for(i=0; i < bi->num_ele; i++){
		if(ch == bi->A[i].chave_hist){
			return i;
		}
	}
	return -1;
	
}

int excluir_elemento(BIN* bi, TIPOCHAVE ch){
	
	int posicao, j;
	
	posicao = busca_sequencial(bi, ch);
	
	if(posicao == -1){
		printf("\n");
		return -1;
	}
	
	for(j = posicao; j < bi->num_ele-1; j++){
		bi->A[j] = bi->A[j+1];
	}
	bi->num_ele--;
	return 1;
	
}

PONT criarNo(TIPOCHAVE ch){
	
	PONT novoNo = (PONT) malloc(sizeof(NO));
	novoNo->esq = NULL;
	novoNo->dir = NULL;
	novoNo->chave = ch;
	return(novoNo);
	
}

PONT inserir(PONT r, PONT no){
	
	if(r == NULL){
		return no;
	}
	
	if(no->chave < r->chave){
		r->esq = inserir(r->esq, no);
	}
	
	else{
		r->dir = inserir(r->dir, no);
	}
	return(r);
	
}

void impressao(PONT r){
	
	if(r != NULL){
		printf("%d", r->chave);
		printf(" [");
		impressao(r->esq);
		impressao(r->dir);
		printf("] ");
	}
}

PONT buscar_pai(PONT r, TIPOCHAVE ch, PONT *pai){
	
	PONT atual = r;
	*pai = NULL;
	
	while(atual){
		if(atual->chave == ch){
			return (atual);
		}
		
		*pai = atual;
		
		if(ch < atual->chave){
			atual = atual->esq;
		}
		
		else{
			atual = atual->dir;
		}
	}
	return (NULL);
}

PONT remover(PONT r, TIPOCHAVE ch){
	
	PONT pai, no, p, q;
	no = buscar_pai(r, ch, &pai);
	
	if(no == NULL){
		return(r);
	}
	
	if(!no->esq || !no->dir){
		if(!no->esq){
			q = no->dir;
		}
		else{
			q = no->esq;
		}
	}
	
	else{
		p = no;
		q = no->esq;
		
		while(q->dir){
			p = q;
			q = q->dir;
		}
		
		if(p != no){
			p->dir = q->esq;
			q->esq = no->esq;
		}
		q->dir = no->dir;
	}
	
	if(!pai){
		free(no);
		return(q);
	}
	
	if(ch < pai->chave){
		pai->esq = q;
	}
	
	else{
		pai->dir = q;
	}
	free(no);
	return(r);
}

int main(){
	
	int menu, menulixo, del;
	
	PONT raiz = inicializar();
	PONT no;
	NO aux;
	
	BIN* bin = (BIN*) malloc(sizeof(BIN));
	inicializacao(bin);
	
	time_t agora;
	time(&agora);
	
	do{
		system("cls");
		printf("\n  Elementos da arvore:\n");
		barras();
		printf("\n\t");
		
		if(raiz == NULL){
			printf("Nao ha elementos na Arvore.");
		}
		
		impressao(raiz);
		printf("\n");
		barras();
		printf("\n   O que deseja fazer?\n\n");
		printf("  [1] - Adicionar novo no.\n");
		printf("  [2] - Excluir um no.\n");
		printf("  [3] - Visualizar lixeira.\n");
		printf("  [4] - Reiniciar Arvore.\n");
		printf("  [5] - Sair.\n   ");
		
		scanf("%d", &menu);
		switch(menu){
			
			case 1:
				barras();
				printf("\n  Digite o No que deseja adicionar: ");
				scanf("%d", &aux.chave);
				no = criarNo(aux.chave);
				raiz = inserir(raiz, no);
				barras(); printf("\n");
				break;
				
			case 2:
				barras();
				printf("\n  Digite o No que deseja deletar: ");
				scanf("%d", &aux.chave);
				inserir_bin(bin, aux.chave);
				raiz = remover(raiz, aux.chave);
				barras(); printf("\n");
				break;
				
			case 3:
				do{
					system("cls");
					barras();
					printf("\n\t\t\tLIXEIRA\n");
					barras();
					exibir_bin(bin);
					printf("\n"); barras();
					printf("\n   O que deseja fazer?\n\n");
					printf("  [1] - Excluir um item da lixeira.\n");
					printf("  [2] - Esvaziar lixeira.\n");
					printf("  [3] - Restaurar um item de volta a arvore.\n");
					printf("  [4] - Voltar.\n   ");
					
					scanf("%d", &menulixo);
					
					switch(menulixo){
						
						case 1:
							printf("\n\n  Digite o item que deseja apagar da lixeira: ");
							scanf("%d", &aux.chave);
							if(excluir_elemento(bin, aux.chave) == 1){
								barras();
								printf("\n\tO item %d foi excluido da lixeira.\n", aux.chave);
								barras();
								printf("\n"); system("pause"); printf("\n");
								break;
							}
							else{
								barras();
								printf("\n\tO item %d nao foi encontrado.\n", aux.chave);
								barras();
								printf("\n"); system("pause"); printf("\n");
								break;
							}
							
						case 2:
							inicializacao(bin);
							barras();
							printf("\n\tA lixeira foi esvaziada.\n");
							barras();
							printf("\n"); system("pause"); printf("\n");
							break;
							
						case 3: //
							printf("\nvc restaurou");
							printf("\n"); system("pause"); printf("\n");
							break;
							
						case 4:
							barras();
							printf("\n\tVoltando para o menu principal.\n");
							barras();
							printf("\n"); system("pause"); printf("\n");
							break;
							
						default:
							barras();
							printf("\n\tDigite um numero de 1 a 4.\n");
							barras();
							printf("\n"); system("pause");
					}
					
				}while(menulixo != 4);
				break;
				
			case 4:
				
				
			case 5:
				barras();
				printf("\n\tSaindo do programa...\n");
				return 0;
				
			default:
				barras();
				printf("\n\tDigite um numero de 1 a 5.\n");
				barras();
				system("pause");
		}
		
	}while(menu != 5);
}
