#include <stdio.h>

int escolha(){
	
	int n;
	
	printf("digite um numero: ");
	scanf("%d", &n);
	return n;
	
}

int sortei(){
	
	int i, sorteado;
	
	sorteado = rand()%10+1;
	printf("%d  ", sorteado);
	return sorteado;
	
}

int comparacao(int numero[], int sortei[]){
	
	int i, j, cont = 0;
	
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			if(numero[i] == sortei[j]){
				cont++;
			}
		}
	}
	return cont;
	
}

int main(){
	
	int i, num[3], sorteio[3], cont;
	srand(time(NULL));
	
	for(i=0; i<3; i++){
		num[i] = escolha();
	}
	
	printf("\n");
	printf("numeros sorteados: \n");
	
	for(i=0; i<3; i++){
		sorteio[i] = sortei();
	}
	
	cont = comparacao(num, sorteio);
	
	printf("\n\nvoce acertou %d numero(s)", cont);
	
}
