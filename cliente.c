#include <stdlib.h>
#include <string.h>
#include "list.h"

//funcao para contar o numero de linhas do arquivo (conta as quebras de linha '\n's)
int count_lines(FILE* file){	
	int count = 0;
	char h;
  	//enquanto nao chega no final
    while((fscanf(file, "%c", &h)) != EOF){
		if(h == '\n') //se for uma quebra de linha
			count++; //conta
	}	
	return count; //retorna o numero de linha
}

void print_intro(){
	printf("------------------------------------------\n");	
	printf("Olá, Seja bem vindo ao Mini Googlebot!\n");
	printf("Verifique abaixo o menu de escolhas e \ndigite a opção correspondente com a ação desejada:\n");	
	printf("------------------------------------------\n");	
}

void print_menu(){
	printf("------------------------------------------\n");	
	printf("Opção 1: Inserir um site;\n");
	printf("Opção 2: Remover um site;\n");
	printf("Opção 3: Inserir palavra-chave;\n");
	printf("Opção 4: Atualizar relevância;\n");
	printf("Opção 5: Sair;\n");
	printf("------------------------------------------\n");		
}

void insert_site(LIST *L){
	printf("Você escolheu inserir um site.\n");
	printf("Digite os seguintes elementos do novo site:\n");
	printf("Código(int) = ");
	int code;
	scanf("%d", &code);
	if(code_found(L, code)){
		printf("ERRO --> código digitado já existe\n");
	}	
	else if(list_insertion(L, read_new_site(code))) printf("Site inserido com sucesso!\n");
}

void remove_site(LIST *L){
	printf("Você escolheu remover um site.\n");	
	printf("Digite o código do site a ser removido: ");
	int code;
	scanf("%d", &code);
	if(!code_found(L, code)){
		printf("ERRO --> site com este código não exite.\n");
	}
	else if(list_remove(L, code)) printf("Site removido com sucesso!\n");
}

void insert_keyword(LIST *L){
	printf("Você escolheu inserir uma nova palavra-chave.\n");	
	printf("Digite o código do site que vai receber a nova palavra-chave: ");
	int code;
	scanf("%d", &code);
	if(new_keyword(list_search(L, code))) printf("Palavra-chave adicionada com sucesso!\n");;		
}

void update_relevance(LIST *L){
	printf("Você escolheu atualizar a relevância de um site.\n");	
	printf("Digite o código do site que vai ter a relevância atualizada: ");
	int code;
	scanf("%d", &code);
	if(change_relevance(list_search(L, code))) printf("Relevância atualizada com sucesso!\n"); 	
}

int main(void){
	FILE* fp; //ponteiro para arquivo
	int n_lines; //variavel que armazena o numero de linhas
	LIST* L = NULL;
	if((fp = fopen("googlebot.txt", "r")) == NULL){ //abre o arquivo googlebot.txt em modo leitura
		printf("ERRO AO ABRIR ARQUIVO DE LEITURA.\n");
		return 0;
	}
	printf("Arquivo de leitura aberto...\n");
	n_lines = count_lines(fp); //conta as linhas
	rewind(fp); //volta ao inicio do arquivo
	L = scan_file(fp, n_lines); //le o arquivo
	printf("Arquivo de leitura lido com sucesso...\n");
	//print_list(l);
	int opc = 0;
	print_intro();
	while(opc != 5){
		print_list(L);	
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
			default: printf("ERRO --> OPÇÃO INVÁLIDA.\nPor favor, digite uma das opções apresentadas:\n");
		}
	}
	printf("Liberando dados e fechando arquivo...\n");
	delete_list(L);
	fclose(fp);
	printf("FIM DA EXECUÇÃO.\n");
	return 0;
}
