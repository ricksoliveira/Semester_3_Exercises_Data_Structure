#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <windows.h>
#include <locale.h>
#include <string.h>

#define MAX 10

typedef struct PLAYER{
	char nome[15];
	int ataque;
	int defesa;
}PLAYER;

typedef struct PARTY{
	PLAYER A[MAX];
	int num_ele;
}PARTY;

void inicializacao(PARTY* pt1){
	pt1->num_ele = 0;
}

void insercao(PARTY* pt1, PLAYER novo){
	
	int k;
	
	for(k = pt1->num_ele; k > 0; k--){
		pt1->A[k] = pt1->A[k-1];
	}
	pt1->A[k] = novo;
	pt1->num_ele++;
}

void barras(){
	
	int i;
	
	printf("\n    ");
	for(i=0; i<25; i++){
		printf("-");
	}
	printf("\n");
}

void exibir_party(PARTY* pt1){
	
	int i;
	
	printf("\n\tStatus da Party\n");
	barras();
	
	if(pt1->num_ele == 0){
		printf("\n\tNão há membros na party.\n");
		barras();
	}
	
	for(i=0; i < pt1->num_ele; i++){
		printf("\tNome: %s\n\n\tAtaque: %d\n\tDefesa: %d", pt1->A[i].nome, pt1->A[i].ataque, pt1->A[i].defesa);
		barras();
	}
}

int retorno_quant(PARTY* pt1){
	return pt1->num_ele;
}


void buscar_role(PARTY* pt1, char procurado[]){
	
	int i;
	
	for(i=0; i < pt1->num_ele; i++){
		
		if(!strcmp(procurado, pt1->A[i].nome)){
			
			if(pt1->A[i].ataque > pt1->A[i].defesa){
				printf("\n\tO ataque do jogador é maior que sua defesa.");
				printf("\n\tA função do jogador é Dano.\n");
				return;
				
			}else if(pt1->A[i].ataque == pt1->A[i].defesa){
				printf("\n\tO ataque do jogador é igual a sua defesa.");
				printf("\n\tA função do jogador é Híbrido.\n");
				return;
				
			}else{
				printf("\n\tA defesa do jogador é maior que seu ataque.");
				printf("\n\tA função do jogador é Tank.\n");
				return;
			}
		}
	}
	barras();
	printf("\n\tJogador não se encontra na party\n");
}

bool adicionar_jogador(PARTY* pt1, PLAYER novo){
	
	int i;
	
	if(pt1->num_ele == MAX){
		printf("\n\tERRO!\n\tA party está lotada.\n");
		printf("\n");
		system("pause");
		return false;
	}
	
	for(i = pt1->num_ele; i > 0; i--){
		pt1->A[i] = pt1->A[i-1];
	}
	pt1->A[i] = novo;
	pt1->num_ele++;
	return true;
}

int posicao_membro(PARTY* pt1, char nom[]){
	
	int i;
	
	for(i=0; i < pt1->num_ele; i++){
		if(!strcmp(nom, pt1->A[i].nome)){
			return i;
		}
	}
	return -1;
}

bool excluir_membro(PARTY* pt1, char nom[]){
	
	int posicao, j;
	
	posicao = posicao_membro(pt1, nom);
	
	if(posicao == -1){
		barras();
		printf("\n\tJogador não encontrado\n");
		barras();
		system("pause");
		return false;
	}
	
	for(j = posicao; j < pt1->num_ele-1; j++){
		pt1->A[j] = pt1->A[j+1];
	}
	pt1->num_ele--;
	return true;
}

bool nome_existente(PARTY* pt1, char nom[]){
	
	int i;
	
	for(i=0; i < pt1->num_ele; i++){
		if(!strcmp(nom, pt1->A[i].nome)){
			return false;
		}
	}
	return true;
}

void ord_crescenteA(PARTY* pt1){
	
	int i, j;
	PLAYER aux;
	
	for(i=0; i < pt1->num_ele; i++){
		for(j=i+1; j < pt1->num_ele; j++){
			if(pt1->A[i].ataque > pt1->A[j].ataque){
				aux = pt1->A[i];
				pt1->A[i] = pt1->A[j];
				pt1->A[j] = aux;
			}
		}
	}
}

void ord_decrescenteA(PARTY* pt1){
	
	int i, j;
	PLAYER aux;
	
	for(i=0; i < pt1->num_ele; i++){
		for(j=i+1; j < pt1->num_ele; j++){
			if(pt1->A[i].ataque < pt1->A[j].ataque){
				aux = pt1->A[i];
				pt1->A[i] = pt1->A[j];
				pt1->A[j] = aux;
			}
		}
	}
}

void ord_crescenteD(PARTY* pt1){
	
	int i, j;
	PLAYER aux;
	
	for(i=0; i < pt1->num_ele; i++){
		for(j=i+1; j < pt1->num_ele; j++){
			if(pt1->A[i].defesa > pt1->A[j].defesa){
				aux = pt1->A[i];
				pt1->A[i] = pt1->A[j];
				pt1->A[j] = aux;
			}
		}
	}
}

void ord_decrescenteD(PARTY* pt1){
	
	int i, j;
	PLAYER aux;
	
	for(i=0; i < pt1->num_ele; i++){
		for(j=i+1; j < pt1->num_ele; j++){
			if(pt1->A[i].defesa < pt1->A[j].defesa){
				aux = pt1->A[i];
				pt1->A[i] = pt1->A[j];
				pt1->A[j] = aux;
			}
		}
	}
}

void batalha_boss(PARTY* pt1, PLAYER boss, int num_ele){		//
	
	int i, morte = 0;
	PARTY* luta = pt1;
	
	for(i=0; i < pt1->num_ele; i++){
		
		if(pt1->A[i].ataque == boss.defesa){
		}
		
		else if((pt1->A[i].ataque < boss.defesa) || (boss.ataque > pt1->A[i].defesa)){
			excluir_membro(luta, luta->A[i].nome);
		}
		
		else if((pt1->A[i].ataque > boss.defesa) || (boss.ataque < pt1->A[i].defesa)){
			morte = 1;
		}
	}
	system("cls");
	if(morte == 1){
		printf("\n\n\tPARABENS VC VENCEU O BOSS\n\n");
	}else{
		printf("\n\n\tO BOSS MATOU TODO MUNDO\n\n");
	}
	printf("\n\tA PARTY DEPOIS DA BATALHA:\n\n");
	exibir_party(luta);
}

int main(){
	
	int i, menu_ini, quant, cre_decre;
	char procurado[15], deletar[15];
	PARTY* party1;
	PLAYER adicionar, boss;
	party1 = (PARTY*) malloc(sizeof(PARTY));
	setlocale(LC_ALL, "Portuguese");
	
	inicializacao(party1);
	
	do{
		system("cls");
		printf("\n\tDigite quantos jogadores terá sua Party: ");
		scanf("%d", &quant);
		
		if(quant > MAX || quant < 1){
			printf("\n\tErro, a party deve ter entre 1 e 10 jogadores.");
			Sleep(3000);
		}
	}while(quant > MAX || quant < 1);
	
	printf("\n\tPreencha os dados dos jogadores:");
	
	for(i=0; i < quant; i++){
		printf("\n\n\tQual será o nome do jogador %d: ", i+1);
		scanf("%s", adicionar.nome);
		
		if(strlen(adicionar.nome) > 15){
			printf("\n\tNome deve ter entre 3 e 15 caracteres");
			return 0;
		}
		
		printf("\tDigite o Ataque do(a) jogador(a) %s: ", adicionar.nome);
		scanf("%d", &adicionar.ataque);
		printf("\tDigite a Defesa do(a) jogador(a) %s: ", adicionar.nome);
		scanf("%d", &adicionar.defesa);
		insercao(party1, adicionar);
	}
	
	do{
		system("cls");
		exibir_party(party1);
		printf("\n\tQuantidade de membros: %d\n", retorno_quant(party1));
		barras();
		printf("\n\t O que deseja fazer?\n");
		printf("\t[1] - Buscar a função de um jogador.\n");
		printf("\t[2] - Adicionar um jogador à party.\n");
		printf("\t[3] - Excluir um jogador da party.\n");
		printf("\t[4] - Ordenar por Ataque.\n");
		printf("\t[5] - Ordenar por Defesa.\n");
		printf("\t[6] - Simular batalha contra um boss.\n"); //
		printf("\t[7] - Reinicializar a party.\n");
		printf("\t[8] - Sair.\n\t ");
		
		scanf("%d", &menu_ini);
		switch (menu_ini){
			
			case 1:
				barras();
				printf("\n\tDigite o nome do jogador: ");
				scanf("%s", procurado);
				buscar_role(party1, procurado);
				barras();
				printf("\n");
				system("pause");
				break;
				
			case 2:
				if(party1->num_ele == MAX){
					barras();
					printf("\n\tA party está cheia, impossível adicionar um jogador.\n");
					barras();
					printf("\n");
					system("pause");
					break;
				}
				
				else{
					barras();
					printf("\n\tDigite o nome do jogador(a) a ser adicionado(a): ");
					scanf("%s", adicionar.nome);
					
					if(strlen(adicionar.nome) > 15){
						printf("\n\tNome deve ter entre 3 e 15 caracteres");
						return 0;
					}
					
					printf("\tDigite o Ataque do(a) novo(a) jogador(a): ");
					scanf("%d", &adicionar.ataque);
					printf("\tDigite a Defesa do(a) novo(a) jogador(a): ");
					scanf("%d", &adicionar.defesa);
					adicionar_jogador(party1, adicionar);
					barras();
					break;
				}
				
			case 3:
				if(party1->num_ele == 0){
					barras();
					printf("\n\tNão há ninguém na party para ser excluído.\n");
					barras();
					system("pause");
					break;
				}
				
				barras();
				printf("\n\tDigite o nome do jogador que deseja excluir: ");
				scanf("%s", deletar);
				excluir_membro(party1, deletar);
				barras();
				break;
				
			case 4:
				barras();
				printf("\n\tDeseja ordenar por ordem crescente ou decrescente?\n");
				printf("\t[1] - Crescente.\n");
				printf("\t[2] - Decrescente.\n\t ");
				scanf("%d", &cre_decre);
				
				switch(cre_decre){
					case 1:
						barras();
						ord_crescenteA(party1);
						barras();
						break;
						
					case 2:
						barras();
						ord_decrescenteA(party1);
						barras();
						break;
						
					default:
						barras();
						printf("\n\tDigite 1 ou 2.\n");
						barras();
						system("pause");
				}
				break;
			
			case 5:
				barras();
				printf("\n\tDeseja ordenar por ordem crescente ou decrescente?\n");
				printf("\t[1] - Crescente.\n");
				printf("\t[2] - Decrescente.\n\t ");
				scanf("%d", &cre_decre);
				
				switch(cre_decre){
					case 1:
						barras();
						ord_crescenteD(party1);
						barras();
						break;
						
					case 2:
						barras();
						ord_decrescenteD(party1);
						barras();
						break;
						
					default:
						barras();
						printf("\n\tDigite 1 ou 2.\n");
						barras();
						system("pause");
				}
				break;
				
			case 6:
				barras();
				printf("\tDigite o Ataque do Boss: ");
				scanf("%d", &boss.ataque);
				printf("\tDigite a Defesa do Boss: ");
				scanf("%d", &boss.defesa);
				batalha_boss(party1, boss, party1->num_ele);
				system("pause");
				barras();
				break;
				
			case 7:
				barras();
				inicializacao(party1);
				printf("\n\tLista reiniciada!\n");
				barras();
				break;
			
			case 8:
				barras();
				printf("\n\tSaindo do programa...\n");
				return 0;
		}
		
	}while(menu_ini != 8);
	
	free(party1);
}

/*
	Implementar:
	- Verificar se o usuario digita letra em lugar de nome e vice versa
	- Verificar se novos nome adicionados já existem
	- Adicionar   || strlen(ins_nom) < 3)
	- Confirmação de certeza ao deletar um personagem
	- Retirar uma das funções de inserção
	- Criar um arquivo com a party
	- Loadar uma party existente de um arquivo
*/
