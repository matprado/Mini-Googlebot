#ifndef SITE_H
#define SITE_H

typedef struct site SITE;

SITE* create_site(void);
SITE *read_file_sites(FILE *fp);
void print_site(SITE *S);
SITE *read_new_site(int code);
int site_code(SITE *S);
int new_keyword(SITE *S);
int change_relevance(SITE *S);
void save_site(FILE *fp, SITE *S);

#endif