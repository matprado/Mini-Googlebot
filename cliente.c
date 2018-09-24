#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "site.h"

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
	printf("Opção 1: Inserir um site;\n");
	printf("Opção 2: Remover um site;\n");
	printf("Opção 3: Inserir palavra-chave;\n");
	printf("Opção 4: Atualizar relevância;\n");
	printf("Opção 5: Sair;\n");
	printf("Opção 6: Mostrar sites;\n");
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
	int code;
	scanf("%d", &code);
	/*Se achar o código na lista, não insere um novo site;*/
	if(code_found(L, code)){
		printf("ERRO --> código digitado já existe\n");
	}	
	else{ 
		if(list_insertion(L, read_new_site(code))) printf("Site inserido com sucesso!\n");
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
	int code;
	scanf("%d", &code);
	/*Se não encontrar o código na lista, não remove;*/
	if(!code_found(L, code)){
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
	int code;
	scanf("%d", &code);
	if(new_keyword(list_search(L, code))) printf("Palavra-chave adicionada com sucesso!\n");;		
}

/*Função update_relevance:
 Atualiza a relevância de um sita na lista;
@Parâmetros:
-Um ponteiro para lista;*/
void update_relevance(LIST *L){
	printf("Você escolheu atualizar a relevância de um site.\n");	
	printf("Digite o código do site que vai ter a relevância atualizada: ");
	int code;
	scanf("%d", &code);
	if(change_relevance(list_search(L, code))) printf("Relevância atualizada com sucesso!\n"); 	
}

int main(void){
	FILE* fp; /*ponteiro para arquivo*/
	int n_lines; /*variavel que armazena o numero de linhas do arquivo*/
	LIST* L = NULL;
	if((fp = fopen("googlebot.csv", "r")) == NULL){ /*abre o arquivo googlebot.txt em modo leitura*/
		printf("ERRO AO ABRIR ARQUIVO DE LEITURA.\n");
		return 0;
	}
	printf("Arquivo de leitura aberto...\n");
	n_lines = count_lines(fp); /*conta as linhas*/
	rewind(fp); /*volta ao inicio do arquivo*/
	L = scan_file(fp, n_lines); /*le o arquivo*/
	printf("Arquivo de leitura lido com sucesso...\n");
	int opc = 0;
	print_intro();
	while(opc != 5){	
		print_menu();	
		scanf("%d", &opc);
		switch(opc){
			case 1: insert_site(L);
				break;	
			case 2:	remove_site(L);
				break;
			case 3:	insert_keyword(L);
				break;
			case 4:	update_relevance(L);	
				break;						
			case 5: printf("Encerrando execução...\n");
				break;
			case 6:	
				printf("Você escolheu ver todos os sites:\n");
				print_list(L);
				break;		
			default: printf("ERRO --> OPÇÃO INVÁLIDA.\nPor favor, digite uma das opções apresentadas:\n");
		}
	}

	/* PARTE DE GUARDAR NO ARQUIVO: FUNCIONA, PORÉM COM ALGUNS BUGS...*/
	fclose(fp);
	if((fp = fopen("googlebot.csv", "w+")) == NULL){ /*abre o arquivo googlebot.txt em modo escrita*/
		printf("ERRO AO ESCREVER NO ARQUIVO DE SAÍDA.\n");
		return 0;
	}
	printf("Armazenando dados no arquivo...\n");
	update_file(fp, L);
	printf("Dados armazenados com sucesso!\n");
	printf("Liberando dados e fechando arquivo...\n");
	delete_list(L);
	fclose(fp);
	printf("FIM DA EXECUÇÃO.\n");
	return 0;
}
