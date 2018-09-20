#ifndef SITE_H
#define SITE_H

typedef struct site SITE; //struct de um site

SITE* create_site(void); //funcao que cria o site
SITE *read_file_sites(FILE *fp);
void print_site(SITE *S);
SITE *read_new_site(int code);
int site_code(SITE *S);
int new_keyword(SITE *S);
int change_relevance(SITE *S);

#endif