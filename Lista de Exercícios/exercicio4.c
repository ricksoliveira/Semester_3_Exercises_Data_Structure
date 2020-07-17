/*
  	Lista 1 - Exercício 4
*/

typedef struct PESSOA{
	char nome[30];
	char RH[10];
	char tipo_sangue;
	int idade;
	int nascimento;
	int peso;
	float altura;
}PESSOA;

typedef struct DOCUMENTO{
	int RG;
	int registro;
	int ultima_doacao;
}DOCUMENTO;

typedef struct LOCAL{
	char logradouro[30];
	char cidade[20];
	char estado[10];
	int numero;
}LOCAL;

typedef struct aux{
	PESSOA individuo;
	DOCUMENTO docs;
	LOCAL place;
	struct aux* proximo;
}ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct LISTA{
	PONT inicio;
}LISTA;
