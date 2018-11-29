#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "site.h"

int count_lines(FILE* file);
int read_number();
void print_intro();
void print_menu();
void insert_site(LIST *L);
void remove_site(LIST *L);
void insert_keyword(LIST *L);
void update_relevance(LIST *L);
void keyword_search(LIST *L);
void site_suggestions(LIST *L);
int load_sites(LIST **L, FILE **fp);
int save_sites(LIST *L, FILE *fp);

int main(void){
	FILE* fp = NULL;
	LIST *L = NULL;
	if(!load_sites(&L, &fp)) return 0;
	int opc = 0;
	print_intro();
	while(opc != 4){	
		print_menu();
		opc = read_number();
		switch(opc){
			case 1: site_suggestions(L);
				break;	
			case 2:	keyword_search(L);
				break;
			case 3:	
				printf("Você escolheu ver todos os sites:\n");	
				print_list(L);
				break;
			case 4:	printf("Encerrando execução...\n");
				break;						
			case 5: insert_site(L);
				break;	
			case 6:	remove_site(L);
				break;		
			case 7: insert_keyword(L);
				break;
			case 8: update_relevance(L);	
				break;
			default: printf("ERRO --> OPÇÃO INVÁLIDA.\nPor favor, digite uma das opções apresentadas:\n");
		}
	}
	if(!save_sites(L, fp)) return 0;
	printf("FIM DA EXECUÇÃO.\n");
	return 0;
}

/*Função count_lines:
 Conta o numero de linhas de um arquivo;
@Parâmetros:
-Um ponteiro para o arquivo;
@Retorno:
-O número de linhas do arquivo;*/
int count_lines(FILE* file){	
	int count = 0;
	char h;
    while((fscanf(file, "%c", &h)) != EOF){
		if(h == '\n')
			count++; 
	}	
	return count; 
}

/*Função read_number:
 Lê um número conferindo se realmente é um número digitado pelo usuário;
 @Retorno:
 -O número inteiro lido*/
int read_number(){
	char input[1000], c;
	input[0] = '\0';
	int i, repeat, size, num=0;
	do{
		scanf("%[^\n]", input);
		if(input[0] != '\n'){
			scanf("%c", &c);
		}
		size = strlen(input);
		i=0;
		repeat=0;
		while(i<size){
			if(!isdigit(input[i++])){
				repeat=1;
			}	
		}
		if(repeat){
			printf("ERRO --> ENTRADA INVÁLIDA!\n");
			printf("Por favor, digite um número inteiro = ");
		}
	}while(repeat);
	num = atoi(input);
	if(input[0] == '\n'){
		return -1;
	}
	return num;	
}

/*Função print_intro:
 Imprime uma mensagem de boas-vindas ao usuário;*/
void print_intro(){
	printf("------------------------------------------\n");	
	printf("Olá, Seja bem vindo ao Mini Googlebot!\n");
	printf("Verifique abaixo o menu de escolhas e \ndigite a opção correspondente com a ação desejada:\n");	
	printf("------------------------------------------\n");	
}

/*Função print_menu:
 Imprime um menu de escolhas;*/
void print_menu(){
	printf("------------------------------------------\n");	
	printf("Opção 1: Sugestão de sites;\n");
	printf("Opção 2: Buscar por palavra-chave;\n");
	printf("Opção 3: Mostrar todos os sites;\n");
	printf("Opção 4: Sair;\n");
	printf("Opção 5: Inserir um site;\n");
	printf("Opção 6: Remover um site;\n");
	printf("Opção 7: Inserir palavra-chave;\n");
	printf("Opção 8: Atualizar relevância;\n");
	/*printf("Opção 9: Remover palavra-chave;\n");*/	
	printf("------------------------------------------\n");		
}

/*Função insert_site:
 Insere um novo site em uma lista;
@Parâmetros:
-Um ponteiro para a lista;*/
void insert_site(LIST *L){
	printf("Você escolheu inserir um site.\n");
	printf("Digite os seguintes elementos do novo site:\n");
	printf("Código(int) = ");
	int code = read_number(), relevance;
	if(code < 0 || code > 9999){
		printf("ERRO --> código inválido(intervalo aceito = 0-9999)\n");
	}
	/*Se achar o código na lista, não insere um novo site;*/
	else if(code_found(L, code)){
		printf("ERRO --> código digitado já existe\n");
	}	
	else{
		printf("Relevância(int) = ");
		relevance = read_number(); 
		if(list_insertion(L, read_new_site(code, relevance))) printf("Site inserido com sucesso!\n");
		else printf("ERRO --> Limite de memória atingido\n");
	}	
}

/*Função remove_site:
 Remove um site de uma lista;
@Parâmetros:
-Um ponteiro para lista;*/
void remove_site(LIST *L){
	printf("Você escolheu remover um site.\n");	
	printf("Digite o código do site a ser removido: ");
	int code = read_number();
	if(code < 0 || code > 9999){
		printf("ERRO --> código inválido(intervalo aceito = 0-9999)\n");
	}
	/*Se não encontrar o código na lista, não remove;*/
	else if(!code_found(L, code)){
		printf("ERRO --> site com este código não exite.\n");
	}
	else if(list_remove(L, code)) printf("Site removido com sucesso!\n");
}

/*Função insert_keyword:
 Insere uma palavra-chave em um site na lista;
@Parâmetros:
-Um ponteiro para lista;*/
void insert_keyword(LIST *L){
	printf("Você escolheu inserir uma nova palavra-chave.\n");	
	printf("Digite o código do site que vai receber a nova palavra-chave: ");
	int code = read_number();
	if(code < 0 || code > 9999){
		printf("ERRO --> código inválido(intervalo aceito = 0-9999)\n");
	}
	else if(new_keyword(list_search(L, code))) printf("Palavra-chave adicionada com sucesso!\n");;		
}

/*Função update_relevance:
 Atualiza a relevância de um sita na lista;
@Parâmetros:
-Um ponteiro para lista;*/
void update_relevance(LIST *L){
	printf("Você escolheu atualizar a relevância de um site.\n");	
	printf("Digite o código do site que vai ter a relevância atualizada: ");
	int code = read_number();
	if(code < 0 || code > 9999){
		printf("ERRO --> código inválido(intervalo aceito = 0-9999)\n");
	}else{
		printf("Digite a nova relevancia = ");
		int relevance = read_number();
		if(change_relevance(list_search(L, code), relevance)) printf("Relevância atualizada com sucesso!\n"); 	
	}	
}

/*Função keyword_search():
 Faz uma busca por uma palavra-chave;
@Parâmetros:
-Um ponteiro para lista;*/
void keyword_search(LIST *L){
	printf("Você escolheu buscar por palavra-chave.\n");
	printf("Digite a palavra-chave a ser buscada: ");
	char keyword[51];
	char c;
	scanf("%[^\n]%c", keyword, &c);
	keyword[strlen(keyword)] = '\0';
	LIST *search_list = list_keyword_search(L, keyword);
	if(!print_search_list(search_list)){
		printf("Não foram encontrados sites com essa palavra-chave\n");
	}
	delete_aux_list(search_list);
}

/*Função site_suggestions:
 Faz uma sugestão de site a partir de uma palavra-chave;
@Parâmetros:
-Um ponteiro para lista;*/
void site_suggestions(LIST *L){
	printf("Você escolheu uma sugestão de sites relacionados a uma palavra-chave.\n");
	printf("Digite a palavra-chave: ");
	char keyword[51];
	char c;
	scanf("%[^\n]%c", keyword, &c);
	keyword[strlen(keyword)] = '\0';
	list_suggestions(L, keyword);	
}

/*Função load_sites:
 Lê o arquivo inicializando a lista com os sites;
@Parâmetros:
-Um ponteiro para lista;
-Um ponteiro para arquivo;*/
int load_sites(LIST **L, FILE **fp){
	int n_lines; /*variavel que armazena o numero de linhas do arquivo*/
	if(((*fp) = fopen("googlebot.txt", "r")) == NULL){ /*abre o arquivo googlebot.txt em modo leitura*/
		printf("ERRO AO ABRIR ARQUIVO DE LEITURA.\n");
		return 0;
	}
	printf("Arquivo de leitura aberto...\n");
	n_lines = count_lines(*fp); /*conta as linhas*/
	rewind(*fp); /*volta ao inicio do arquivo*/
	(*L) = scan_file(*fp, n_lines); /*le o arquivo*/
	printf("Arquivo de leitura lido com sucesso...\n");
	return 1;
}

/*Função save_sites:
 Salva em um arquivo todos os sites armazenados e depois libera a lista da memória heap;
@Parâmetros:
-Um ponteiro para lista;
-Um ponteiro para arquivo;*/
int save_sites(LIST *L, FILE *fp){
	/*Guarda os dados de volta no arquivo:*/
	fclose(fp);
	if((fp = fopen("googlebot.txt", "w+")) == NULL){ /*abre o arquivo googlebot.txt em modo escrita*/
		printf("ERRO AO ESCREVER NO ARQUIVO DE SAÍDA.\n");
		return 0;
	}
	printf("Armazenando dados no arquivo...\n");
	update_file(fp, L);
	printf("Dados armazenados com sucesso!\n");
	printf("Liberando dados e fechando arquivo...\n");
	delete_list(L);
	fclose(fp);
	return 1;
}