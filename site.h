#ifndef SITE_H
#define SITE_H
#include <stdio.h>

typedef struct site SITE;

SITE* create_site(void);
SITE *read_file_sites(FILE *fp);
void print_site(SITE *S);
SITE *read_new_site(int code, int relevance);
int site_code(SITE *S);
int site_relevance(SITE *S);
int site_key(SITE *S);
int new_keyword(SITE *S);
int change_relevance(SITE *S, int relevance);
void save_site(FILE *fp, SITE *S);
SITE* keyword_found(SITE* root, char search[51]);
char* keyword_to_search(char** keywords, int word);
int site_nkey(SITE* s);
char** site_keywords(SITE* s);

#endif
