#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "site.h"
#define DEBUG 1

//definindo a estrutura de um so site
struct site{
	int code; //codigo
	char name[51]; //nome
	int relevance; //relevancia
	char link[101]; //link
	char keywords[10][51]; //palavras-chave
	int n_key; //quantidade de palavras chave
};

//criando um site
SITE* create_site(void){
	SITE* create;//ponteiro opaco para um site
	create = (SITE*) malloc(sizeof(SITE)); //alocando na heap o site
	//se alocou, entra
	if (create != NULL){
		create->code = 0; //zerando o codigo
		create->relevance = 0; //zerando a relevancia
		create->n_key = 0;
	}
	//retornando o site criado
	return(create);
}

SITE *read_file_sites(FILE *fp){
	SITE *S = create_site();
	char c;
	fscanf(fp, "%d%c%[^,]%c%d%c%[^,]", &S->code, &c, S->name, &c, &S->relevance, &c,  S->link);
	c = fgetc(fp);
	while((c = fgetc(fp)) != '\n'){
		if(c != ',') fseek(fp, -1L, SEEK_CUR);
		fscanf(fp,"%[a-zA-Z]", S->keywords[S->n_key++]);
	}
	return S;
}

void print_site(SITE *S){
	printf("-----------------------------------------------------\n");
	printf("Código: %d\n", S->code);
	printf("Nome: %s\n", S->name);
	printf("Relevância: %d\n", S->relevance);
	printf("Link: %s\n", S->link);
	for(int i=0; i<S->n_key; i++){
		printf("Palavra-chave %d: %s\n", i+1,S->keywords[i]);
	}
	printf("-----------------------------------------------------\n");
	printf("\n");
}

SITE *read_new_site(){
	SITE *new = create_site();
	char c;
	printf("Digite os seguintes elementos do novo site:\n");
	printf("Código = ");
	scanf("%d", &new->code);
	c = getchar();
	printf("Nome = ");
	scanf("%[^\n]", new->name);
	c = getchar();
	printf("Relevância = ");
	scanf("%d", &new->relevance);
	c = getchar();
	printf("Link = ");
	scanf("%[^\n]", new->link);
	c = getchar();
	printf("Quantas palavras chave? ");
	scanf("%d", &new->n_key);
	c = getchar();	
	for(int i=0; i<new->n_key; i++){
		printf("Palavra-chave %d = ", i+1);
		scanf("%s", new->keywords[i]);
		c = getchar();
	}
	return new;
}

int site_code(SITE *S){
	if(S == NULL) return 0;		
	return S->code;
}

int new_keyword(SITE *S){
	if(S == NULL){
		printf("ERRO --> Site não encontrado.\n");
		return 0;
	}
	if(S->n_key == 10){
		printf("ERRO --> Número máximo de palavras-chave atingido.\n");
		return 0;
	}
	printf("Digite a palavra-chave = ");
	scanf("%s", S->keywords[S->n_key++]);
	return 1;
}

int change_relevance(SITE *S){
	if(S == NULL){
		printf("ERRO --> Site não encontrado.\n");
		return 0;
	}
	printf("Digite a nova relevancia = ");
	scanf("%d", &S->relevance);
	return 1;
}