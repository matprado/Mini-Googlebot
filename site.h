#ifndef SITE_H
#define SITE_H
#include "avl.h"

typedef struct site SITE;

SITE* create_site(void);
SITE *read_file_sites(FILE *fp);
void print_site(SITE *S);
SITE *read_new_site(int code, int relevance);
int site_code(SITE *S);
int new_keyword(SITE *S);
int change_relevance(SITE *S, int relevance);
void save_site(FILE *fp, SITE *S);
void delete_site(SITE *S);
int keyword_found(SITE *S, char keyword[51]);
void print_search(SITE *S);
char** site_keywords(SITE* S);
int site_nkey(SITE* S);
int site_relevance(SITE *S);

#endif
