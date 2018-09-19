#ifndef LIST_H
#define LIST_H
#include <stdio.h> //tive que colocar a stdio aqui por causa do parametro "FILE*"
#include "site.h"

typedef struct list LIST; //struct da lista de sites
typedef struct node NODE;

LIST* create_list(void); //funcao que cria a lista para armazenar os sites
void delete_list(LIST *L);
void delete_node(NODE *N);
LIST* scan_file(FILE* fp, int n_lines); //funcao que escaneia o arquivo, recebe o arquivo e o numero de linhas dele
int list_insertion(LIST *L, SITE *S);
int empty_list(LIST *L);
int list_size(LIST *L);
void print_list(LIST *L);
int list_remove(LIST *L, int code);
SITE *list_search(LIST *L, int code);

#endif