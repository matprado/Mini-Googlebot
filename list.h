#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include "site.h"

typedef struct list LIST;
typedef struct node NODE;

LIST* create_list(void);
void delete_list(LIST *L);
void delete_node(NODE *N);
LIST* scan_file(FILE* fp, int n_lines);
int list_insertion_relevance(LIST *L, SITE *S);
int list_insertion(LIST *L, SITE *S);
int empty_list(LIST *L);
int list_size(LIST *L);
void print_list(LIST *L);
int list_remove(LIST *L, int code);
SITE *list_search(LIST *L, int code);
int code_found(LIST *L, int code);
void update_file(FILE *fp, LIST *L);
SITE* list_search_keyword(LIST* L, int place);

#endif
