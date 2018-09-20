#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "site.h"
#define DEBUG 1


struct site{
	int code; //codigo
	char name[51]; //nome
	int relevance; //relevancia
	char link[101]; //link
	char keywords[10][51]; //palavras-chave
	int n_key; //quantidade de palavras chave
};

/*Função create_site:
 Aloca e retorna um novo site;
@Retorno:
-Um ponteiro para o novo site;*/
SITE* create_site(void){
	SITE* new;
	new = (SITE*) malloc(sizeof(SITE)); 
	if (new != NULL){
		new->code = 0; 
		new->relevance = 0;
		new->n_key = 0;
	}
	return new;
}

/*Função read_file_sites:
 Lê dados de uma linha de arquivo e os armazena em um novo site alocado, retornando o mesmo;
@Parâmetros:
-Ponteiro para o arquivo de leitura;
@Retorno:
-Um ponteiro para o novo site;*/
SITE *read_file_sites(FILE *fp){
	SITE *S = create_site();
	char c;
	/*Obs, o c existe para pegar as vírgulas que ficam entre os dados;*/
	fscanf(fp, "%d%c%[^,]%c%d%c%[^,]", &S->code, &c, S->name, &c, &S->relevance, &c,  S->link);
	c = fgetc(fp);
	/*Lê todas as palavras-chave até que chegue em um \n. Ao mesmo tempo, incrementa a quantidade de palavras-chave*/
	while((c = fgetc(fp)) != '\n'){
		if(c != ',') fseek(fp, -1L, SEEK_CUR);
		fscanf(fp,"%[a-zA-Z]", S->keywords[S->n_key++]);
	}
	return S;
}

/*Função print_site:
 Imprime todos os campos de um site;
@Parâmetros:
-O site a ser imprimido;
*/
void print_site(SITE *S){
	printf("-----------------------------------------\n");
	printf("Código: %d\n", S->code);
	printf("Nome: %s\n", S->name);
	printf("Relevância: %d\n", S->relevance);
	printf("Link: %s\n", S->link);
	for(int i=0; i<S->n_key; i++){
		printf("Palavra-chave %d: %s\n", i+1,S->keywords[i]);
	}
	printf("------------------------------------------\n");
}

/*Função read_new_site:
 Lê dados digitados pelo usuário e os armazena em um novo site alocado, retornando o mesmo;
@Parâmetros:
-Um inteiro representando o código do novo site;
@Retorno:
-Se bem sucedida, retorna o ponteiro do novo site. Caso contrário, retorna NULL;*/
SITE *read_new_site(int code){
	SITE *new = create_site();
	new->code = code;
	char c;
	c = getchar(); /*OBS: o c existe para pegar os '\n' que sobram do stdin*/
	printf("Nome(string) = ");
	scanf("%[^\n]", new->name);
	c = getchar();
	printf("Relevância(int) = ");
	scanf("%d", &new->relevance);
	/*Confere se a relevância está no intervalo permitido:*/
	if(new->relevance < 0 || new->relevance > 1000){
		printf("ERRO --> número inválido para relevancia(0-1000).\n");
		printf("Valor de relevância resetado para 0.\n");
		new->relevance = 0;
	}
	c = getchar();
	printf("Link(string) = ");
	scanf("%[^\n]", new->link);
	c = getchar();
	printf("Quantas palavras chave?(int) ");
	scanf("%d", &new->n_key);
	/*Confere se a quantidade de palavras-chave está no intervalo permitido:*/
	if(new->n_key < 0 || new->n_key > 10){
		printf("ERRO --> número inválido de palavras-chave(0-10).\n");
		printf("Quantidade de palavras-chave resetada para 0.\n");
		new->n_key = 0;
		return new;
	}
	c = getchar();
	/*Lê cada palavra chave:*/
	for(int i=0; i<new->n_key; i++){
		printf("Palavra-chave(string) número %d = ", i+1);
		scanf("%s", new->keywords[i]);
		// POSSÍVEL SOLUÇÃO PARA PALAVRAS CHAVE IGUAIS:
		/*for(int j=0; j<i; j++){
			if(strcmp(new->keywords[i], new->keywords[j]) == 0){
				printf("ERRO --> Palavra-chave já existe\n");
				new->n_key = i;
				printf("Quantidade de palavras-chave ficou em %d.\n", i);
				return new;
			}	
		}*/
		c = getchar();
	}
	return new;
}

/*Função site_code:
 Retorna o código de um site;
@Parâmetros:
-Um ponteiro do site que terá seu código retornado;
@Retorno:
-Se bem sucedida, retorna o código do site dado. Caso contrário, retorna 0;*/
int site_code(SITE *S){
	if(S == NULL) return 0;		
	return S->code;
}

/*Função new_keyword:
 Adiciona uma palavra-chave no site dado;
@Parâmetros:
-Um ponteiro para site;
@Retorno:
-Se bem sucedida, retorna 1. Caso contrário, retorna 0;*/
int new_keyword(SITE *S){
	if(S == NULL){
		printf("ERRO --> Site não encontrado.\n");
		return 0;
	}
	if(S->n_key >= 10){
		printf("ERRO --> Número máximo de palavras-chave atingido.\n");
		return 0;
	}
	printf("Digite a palavra-chave = ");
	scanf("%s", S->keywords[S->n_key++]);
	return 1;
}

/*Função change_relevance:
 Muda a relevância de um site dado;
@Parâmetros:
-Um ponteiro para site;
@Retorno:
-Se bem sucedida, retorna 1. Caso contrário, retorna 0;*/
int change_relevance(SITE *S){
	if(S == NULL){
		printf("ERRO --> Site não encontrado.\n");
		return 0;
	}
	printf("Digite a nova relevancia = ");
	int r;
	scanf("%d", &r);
	if(r < 0 || r > 1000){
		printf("ERRO --> número inválido para relevancia(0-1000).\n");
		return 0;
	}
	S->relevance = r;
	return 1;
}

void save_site(FILE *fp, SITE *S){
	fprintf(fp, "%d,%s,%d,%s", S->code, S->name, S->relevance, S->link);
	for(int i=0; i<S->n_key; i++){
		fprintf(fp, ",%s", S->keywords[i]);
	}
	fprintf(fp, "\n");
}