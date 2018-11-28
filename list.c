#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#define ERROR -404

/*ESTRUTURA DE DADOS USADA: Lista Encadeada Ordenada*/
struct list{	
	NODE *start; /*Começo da lista*/
	int size; /*Tamanho da lista*/	
};

struct node{
	SITE *site;
	NODE *next;
};


/*Função create_list:
 Aloca e retorna um ponteiro para a nova lista;
@Retorno:
-Se bem sucedida, retorna o ponteiro da nova lista criada. Caso contrário, retorna NULL;*/
LIST *create_list(void){
	LIST *L; 
	L = (LIST *) malloc(sizeof(LIST)); 
	if(L != NULL){
		L->start = NULL; 
		L->size = 0; 
	}	
	return(L);	
}


/*Função delete_list:
 Libera todos os nós de uma lista e, por último, a própria lista;
@Parâmetros:
-Um ponteiro para a lista a ser removida;*/
void delete_list(LIST *L){
	if(L != NULL && !empty_list(L)){
   		NODE *N = L->start, *aux;
    	while(N != NULL){
       	 	aux = N;
       	 	N = N->next;
        	delete_node(aux);
        }
    	L->start = NULL;
    	free(L);
		L = NULL;
	}
}

/*Função delete_node:
 Libera o conteúdo de um nó e, posteriormente, o próprio nó;
@Parâmetros:
-Um nó;*/
void delete_node(NODE *N){
	if(N != NULL){
		delete_site(N->site);
		free(N);
		N = NULL;
	}
}

/*Função scan_file:
 Lê todas as informações de um arquivo e as armazena em uma lista;
@Parâmetros:
-Um ponteiro para o arquivo de leitura e a quantidade de linhas do arquivo;
@Retorno:
-Retorna um ponteiro para a nova lista;*/
LIST* scan_file(FILE* fp, int n_lines){
	LIST *L = create_list(); 
	SITE *S;
	while(L->size < n_lines){
		S = read_file_sites(fp);
		if(list_insertion(L, S)) printf("NOVO SITE INSERIDO COM SUCESSO...\n");
	}
	return L; 
}

/*Função list_insertion:
 Insere um novo śite em uma lista;
@Parâmetros:
-Ponteiros para a lista e para o site;
@Retorno:
-Se bem sucedida, retorna 1. Caso contrário, retorna 0;*/
int list_insertion(LIST *L, SITE *S){ 
 	if(L == NULL || S == NULL) return 0;
	NODE *new = (NODE *) malloc(sizeof(NODE)), *search = NULL, *previous = NULL;		/*
	search -> nó posicionado onde deveria estar o new;
	previous -> nó anterior à search		
	new -> novo nó a ser inserido entre o previous e o search; */
	if(new != NULL){
		new->site = S;
		new->next = NULL;
		if(empty_list(L)){ /*LISTA VAZIA*/
			L->start = new;
		}else{
			search = L->start;
			while((search != NULL) && (site_code(search->site) < site_code(new->site))){
				previous = search;
				search = search->next; /*previous recebe o nó anterior de search*/
			}
			if(search == L->start){ /*CASO PARTICULAR: inserir como primeiro elemento*/
				new->next = search;
				L->start = new;
			}
			else{
				new->next = previous->next;
				previous->next = new;
			}
		}
		L->size++;
		return 1;
	}
	return 0;
}

/*Função empty_list:
 Verifica se uma lista está vazia;
@Parâmetros:
-Um ponteiro para lista;
@Retorno:
-Se a lista estiver vazia, retorna 1. Caso contrário, retorna 0;*/
int empty_list(LIST *L){
	if(L != NULL && L->start == NULL) return 1;
 	return 0;
}

/*Função print_list:
 Imprime todos os elementos da lista;
@Parâmetros:
-Um ponteiro para a lista a ser imprimida;
*/
void print_list(LIST *L){
	NODE *aux = NULL;
	if(L != NULL && !empty_list(L)){
		aux = L->start;
		while(aux != NULL){			
			print_site(aux->site);
			aux = aux->next;
		}
	}		
}

/*Função list_remove:
 Remove um nó de uma lista que contém um site com o código dado;
@Parâmetros:
-Ponteiro para lista e um código;
@Retorno:
-Se bem sucedida, retorna 1. Caso contrário, retorna 0;*/
int list_remove(LIST *L, int code){
	NODE *p, *aux = NULL;
	if(L != NULL && !empty_list(L)){
		p = L->start;
		while((p != NULL) && (site_code(p->site) != code)){
			aux = p; /* aux_busca recebe o nó anterior de aux_remocao*/
			p = p->next;
		}
		if(p != NULL){
			if(p == L->start){ /*Exceção: chave no inicio*/
				L->start = p->next;
				p->next = NULL;
			}else{
				aux->next = p->next;
				p->next = NULL;
			}
			L->size--;
			delete_node(p);	
			return 1;
		}
	}
	return 0;
}

/*Função list_search:
 Procura e retorna um site de uma lista baseado em um código dado;
@Parâmetros:
-Um ponteiro para lista e um código;
@Retorno:
-Se bem sucedida, retorna o site encontrado. Caso contrário, retorna NULL;*/
SITE *list_search(LIST *L, int code){
	NODE *aux = L->start;
	if(L != NULL){
		while(aux != NULL){
			if(site_code(aux->site) > code) return NULL;
			if(site_code(aux->site) == code) return aux->site;
			aux = aux->next;
		}
	}
	return NULL; /*Erro de não achar um site com o código dado*/
}

/*Função code_found:
 Verifica se existe algum site na lista com o mesmo código que o dado;
@Parâmetros:
-Um ponteiro para lista e um código;
@Retorno:
-Se encontrar um site com o código dado, retorna 1. Caso contrário, retorna 0;*/
int code_found(LIST *L, int code){
	if(L == NULL) return 0;
	NODE *aux = L->start;
	while(aux != NULL){
		if(code == site_code(aux->site)){
			return 1;
		}			
		aux = aux->next;		
	}
	return 0;
}

/*Função update_file:
 Escreve em um arquivo todas os sites de uma lista;
@Parâmetros:
-Ponteiros para o arquivo e para o site;*/
void update_file(FILE *fp, LIST *L){
	NODE *aux = NULL;
	if(L != NULL && !empty_list(L)){
		aux = L->start;
		while(aux != NULL){			
			save_site(fp, aux->site);
			aux = aux->next;
		}
	}	
}

LIST *list_keyword_search(LIST* L, char keyword[51]){
	if(L == NULL) return NULL;
	LIST* search_list = create_list();
	NODE *aux = L->start;
	while(aux != NULL){
		if(keyword_found(aux->site, keyword)) list_relevance_insertion(search_list, aux->site);
		aux = aux->next;
	}
	if(!print_search_list(search_list)){
		printf("Não foram encontrados sites com essa palavra-chave\n");
		delete_aux_list(search_list);
		free(search_list);
		return NULL;
	}
	return search_list;
}

int print_search_list(LIST *L){
	if(empty_list(L)) return 0;
	NODE *aux = NULL;
	if(L != NULL && !empty_list(L)){
		aux = L->start;
		while(aux != NULL){			
			print_search(aux->site);
			aux = aux->next;
		}
	}
	return 1;
}

void list_suggestions(LIST *L, LIST *search_list){
	LIST *sug_list = create_list();
	char ***related_keywords = (char ***) malloc(search_list->size * sizeof(char **));
	int site_counter = 0, i = 0;
	NODE *aux = search_list->start, *sec;
	while(aux != NULL){
		related_keywords[site_counter] = site_keywords(aux->site);
		sec = L->start;
		while(sec != NULL){
			for(i = 0; i < site_nkey(aux->site); i++){
				/*SE NÃO QUISER REPETIR, MUDA AQUI*/
				if(keyword_found(sec->site, related_keywords[site_counter][i])) list_relevance_insertion(sug_list, sec->site);
			}	
			sec = sec->next;
		}	
		aux = aux->next;
		site_counter++;
	}
	if(!print_search_list(sug_list)) printf("Não há sites sugeridos.\n");
	int a, b;
	aux = search_list->start;
	for(a = 0; a < search_list->size; a++){
		for(b = 0; b < site_nkey(aux->site); b++){
			free(related_keywords[a][b]);
		}
		free(related_keywords[a]);
		aux = aux->next;
	}
	free(related_keywords);
	if(sug_list != NULL) delete_aux_list(sug_list);
	if(search_list != NULL) delete_aux_list(search_list);
}

int list_relevance_insertion(LIST *L, SITE *S){
	if(L == NULL || S == NULL) return 0;
	NODE *new = NULL, *search = NULL, *previous = NULL;
	/*CHECAR SE O SITE JÁ EXISTE NA LISTA*/
	NODE* aux = L->start;
	int check = 0;
	while(check < L->size){
		if(site_code(S) == site_code(aux->site))
			return 1;
		aux = aux->next;
		check++;
	}
	/*
	search -> nó posicionado onde deveria estar o new;
	previous -> nó anterior à search		
	new -> novo nó a ser inserido entre o previous e o search; */
	new = (NODE *) malloc(sizeof(NODE));
	if(new != NULL){
		new->site = S;
		new->next = NULL;
		if(empty_list(L)){ /*LISTA VAZIA*/
			L->start = new;
		}else{
			search = L->start;
			while((search != NULL) && (site_relevance(search->site) > site_relevance(new->site))){
				previous = search;
				search = search->next; /*previous recebe o nó anterior de search*/
			}
			if(search == L->start){ /*CASO PARTICULAR: inserir como primeiro elemento*/
				new->next = search;
				L->start = new;
			}
			else{
				new->next = previous->next;
				previous->next = new;
			}
		}
		L->size++;
		return 1;
	}
	return 0;
}

void delete_aux_list(LIST *L){
	if(L != NULL && !empty_list(L)){
   		NODE *N = L->start, *aux;
    	while(N != NULL){
       	 	aux = N;
       	 	N = N->next;
        	free(aux);
        	aux=NULL;
        }
    	L->start = NULL;
    	free(L);
		L = NULL;
	}
}