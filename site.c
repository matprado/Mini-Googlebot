#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "site.h"

struct site{
	int code;  /*codigo*/
	char name[51]; /*nome*/
	int relevance; /*relevancia*/
	char link[101]; /*link*/
	AVL *keywords_tree; /*árvore de palavras-chave*/
	int n_key; /*quantidade de palavras chave*/
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
		new->keywords_tree = NULL;
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
	S->keywords_tree = avl_create();
	char keyword[51];
	while((c = fgetc(fp)) != '\n'){
		if(c != ',') fseek(fp, -1L, SEEK_CUR);
		fscanf(fp,"%[a-zA-Z]", keyword);
		keyword[strlen(keyword)] = '\0';
		/*printf("sdaas %s\n", keyword);*/
		avl_insert(S->keywords_tree, keyword);
		keyword[0] = '\0';
		S->n_key++;
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
	printf("Palavras-chave:\n");
	avl_print(S->keywords_tree);
	printf("------------------------------------------\n");
}

/*Função read_new_site:
 Lê dados digitados pelo usuário e os armazena em um novo site alocado, retornando o mesmo;
@Parâmetros:
-Dois inteiros, um é o código e o outro é a relevância do novo site;
@Retorno:
-Se bem sucedida, retorna o ponteiro do novo site. Caso contrário, retorna NULL;*/
SITE *read_new_site(int code, int relevance){
	SITE *new = create_site();
	new->code = code;
	new->relevance = relevance;
	/*Confere se a relevância está no intervalo permitido:*/
	if(new->relevance < 0 || new->relevance > 1000){
		printf("ERRO --> número inválido para relevancia(0-1000).\n");
		printf("Valor de relevância resetado para 0.\n");
		new->relevance = 0;
	}
	char c; /*OBS: essa variável c existe para pegar os '\n' que sobram do stdin*/
	printf("Nome(string) = ");
	scanf("%[^\n]%c", new->name, &c);
	printf("Link(string) = ");
	scanf("%[^\n]%c", new->link, &c);
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
	int i;
	char keyword[51];
	new->keywords_tree = avl_create();
	for(i=0; i<new->n_key; i++){
		printf("Palavra-chave(string) número %d = ", i+1);
		scanf("%s%c", keyword, &c);
		keyword[strlen(keyword)] = '\0';
		avl_insert(new->keywords_tree, keyword);
		keyword[0] = '\0';
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
	char keyword[51];
	scanf("%s", keyword);
	avl_insert(S->keywords_tree, keyword);
	S->n_key++;
	getchar();
	return 1;
}

/*Função change_relevance:
 Muda a relevância de um site dado;
@Parâmetros:
-Um ponteiro para site;
@Retorno:
-Se bem sucedida, retorna 1. Caso contrário, retorna 0;*/
int change_relevance(SITE *S, int relevance){
	if(S == NULL){
		printf("ERRO --> Site não encontrado.\n");
		return 0;
	}
	if(relevance < 0 || relevance > 1000){
		printf("ERRO --> número inválido para relevancia(0-1000).\n");
		return 0;
	}
	S->relevance = relevance;
	return 1;
}
/*Função save_site:
 Salva todas os dados em um arquivo;
@Parâmetros:
-Um ponteiro para arquivo e um para site;*/
void save_site(FILE *fp, SITE *S){
	fprintf(fp, "%d,%s,%d,%s,", S->code, S->name, S->relevance, S->link);
	avl_save(S->keywords_tree, fp);
	if(S->n_key != 0){
		fseek(fp, -1L, SEEK_CUR);
	}
	fprintf(fp, "\n");
}

/*Função delete_site:
 Deleta um site;
@Parâmetros:
-Um ponteiro para um site;*/
void delete_site(SITE *S){
	if(S != NULL){
		avl_delete(&(S->keywords_tree));
		free(S);
		S = NULL;
	}
}

/*Função keyword_found:
 Procura uma palavra-chave em um site;
@Parâmetros:
-Um ponteiro para o site;
-A palavra-chave;
@Retorno:
-Se bem sucedida, retorna 1. Caso contrário, retorna 0;*/
int keyword_found(SITE *S, char keyword[51]){
	if(S != NULL){
		if(avl_search(S->keywords_tree, keyword)) return 1;	
	}
	return 0;	
}

/*Função print_search:
 Imprime um site em forma de busca;
@Parâmetros:
-Um ponteiro para um site;*/
void print_search(SITE *S){
	printf("------------------------------------------\n");
	printf("---\t%s\t---\n", S->name);
	printf("%s\n", S->link);
	printf("------------------------------------------\n");
}

/*Função site_keywords:
 Retorna as palavras-chave de um site;
@Parâmetros:
-Um ponteiro para um site;
@Retorno:
-A palavra-chave;*/
char** site_keywords(SITE* S){
	if(S == NULL) return NULL;
	char** keywords;
	keywords = (char**) malloc(S->n_key * sizeof(char*));
	avl_copy_keywords(S->keywords_tree, keywords);
	return keywords;
}

/*Função site_nkey:
 Retorna o número de palavras-chave de um site;
@Parâmetros:
-Um ponteiro para um site;
@Retorno:
-O número de palavras-chave do site;*/
int site_nkey(SITE* S){
	if (S == NULL) return -404;
	return S->n_key;
}

/*Função site_relevance:
 Retorna a relevância de um site;
@Parâmetros:
-Um ponteiro para um site;
@Retorno:
-A relevância do site;*/
int site_relevance(SITE *S){
	if(S == NULL) return 0;		
	return S->relevance;
}
