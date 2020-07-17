#include <stdio.h>

typedef struct aluno{
	char nome[20];
	float p1, p2, trab, cr;
}aluno;

int main(){
	
	aluno media;
	
	printf("Digite o nome do aluno: ");
	scanf("%s", media.nome);
	printf("Digite a nota P1 do aluno %s: ", media.nome);
	scanf("%f", &media.p1);
	printf("Digite a nota P2 do aluno %s: ", media.nome);
	scanf("%f", &media.p2);
	printf("Digite a nota do trabalho do aluno %s: ", media.nome);
	scanf("%f", &media.trab);
	
	media.cr = (media.p1 + media.p2 + media.trab) / 3;
	
	printf("A media de %s eh %.2f", media.nome, media.cr);
	
}
