#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#define ERROR 505
#define DEBUG 0

//lista de sites, contem um site no inicio e um no final e o tamanho
struct list{	
	NODE *start; //primeiro
	NODE *end; //ultimo
	int size; //tamanho da lista	
};

struct node{
	SITE *site;
	NODE *next;
};

//funcao que cria uma lista e retorna essa
LIST *create_list(void){
	LIST *L; //declarado um ponteiro para lista
	L = (LIST *) malloc(sizeof(LIST)); //alocando a lista na heap
	//se alocou, entra
	if(L != NULL){
		L->start = NULL; //nenhum item no comeco da lista
		L->end = NULL; //nenhum item no final da lista
		L->size = 0; //portanto, lista vazia
	}	
	return(L);//retorna a lista vazia	
}

void delete_list(LIST *L){
	if(L != NULL && !empty_list(L)){
   		NODE *N = L->start, *aux;
    	while(N != L->end){
       	 	aux = N;
       	 	N = N->next;
        	delete_node(aux);
        }
    	delete_node(N); //Deleta o último nó
    	L->start = NULL;
    	L->end = NULL;
		free(L);
		L = NULL;
	}
}

void delete_node(NODE *N){
	if(N != NULL){
		free(N->site);
		free(N);
		N = NULL;
	}
}

LIST* scan_file(FILE* fp, int n_lines){
	LIST *L = create_list(); 
	SITE *S;
	//printf("linhas = %d\n", n_lines);
	while(L->size < n_lines){
		S = read_file_sites(fp);
		if(list_insertion(L, S)) printf("NOVO SITE INSERIDO COM SUCESSO...\n");
	}
	return L; //retorna a lista
}

int list_insertion(LIST *L, SITE *S){ 
 	if(L == NULL || S == NULL) return 0;
	NODE *new = (NODE *) malloc(sizeof(NODE)), *search = NULL, *previous = NULL;	
	/*
	search -> nó posicionado onde deveria estar o new;
	previous -> nó anterior à search		
	new -> novo nó a ser inserido entre o previous e o search; 
	*/
	if(new != NULL){
		new->site = S;
		new->next = NULL;
		if(empty_list(L)){ /*LISTA VAZIA*/
			L->start = new;
			L->end = new;
		}else{
			search = L->start;
			while((search != NULL) && (site_code(search->site) < site_code(new->site))){
				previous = search;
				search = search->next; /* previous recebe o nó anterior de search*/
			}
			if(search == L->start){ //CASO PARTICULAR: inserir como primeiro elemento
				new->next = search;
				L->start = new;
			}else if(search == NULL){ //CASO PARTICULAR: inserir como último elemento
				previous->next = new;
				L->end = new;
			}else{
				new->next = previous->next;
				previous->next = new;
			}
		}
		L->size++;
		return 1;
	}
	return 0;

}

int empty_list(LIST *L){
	if(L != NULL && L->start == NULL) return 1;
 	return 0;
}

int list_size(LIST *L){
	return (L != NULL ? L->size : ERROR);
}

void print_list(LIST *L){
	NODE *aux = NULL;
	if(L != NULL && !empty_list(L)){
		aux = L->start;
		while(aux != L->end){			
			print_site(aux->site);
			aux = aux->next;
		}
		print_site(aux->site); /*Imprime o último site da lista*/
	}		
}

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
			if(p == L->end){ /* Se a chave está no último nó*/
				L->end = aux;
			}
			L->size--;
			delete_node(p);	
			return 1;
		}
	}
	return 0;
}

SITE *list_search(LIST *L, int code){
	NODE *aux = L->start;
	if(L != NULL){
		while(aux != NULL){
			if(site_code(aux->site) == code) return aux->site;
			aux = aux->next;
		}
	}
	return NULL; //Erro de não achar um site com o código dado
}

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