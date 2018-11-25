#ifndef AVL_H
#define AVL_H

#define max(a, b) ((a > b) ? a : b)

typedef struct avl AVL;
typedef struct node NODE;

AVL *avl_create(void);
void avl_delete(AVL **tree);
void delete_avl_aux(NODE *root);
void delete_node_avl(NODE* a);
int avl_height_node(NODE* root);
NODE *avl_create_node(char keyword[51]);
NODE *rotate_right(NODE *a);
NODE *rotate_left(NODE *a);
NODE *rotate_left_right(NODE *a);
NODE *rotate_right_left(NODE *a);
NODE *avl_insert_node(NODE *root, char keyword[51]);
int avl_insert(AVL *tree, char keyword[51]);
void avl_print(AVL* tree);
void print_tree(NODE* root);
NODE* avl_root(AVL* tree);
void avl_save(AVL *tree, FILE *fp);
void tree_save(NODE *root, FILE *fp);
int avl_search(AVL *tree, char keyword[51]);
int avl_search_aux(NODE *root, char keyword[51]);
void avl_copy_keywords(AVL *tree, char **keywords);
void avl_copy_aux(NODE *root, char **keywords, int *i);
/*int avl_remove(NODE *root, NODE *rem, NODE *prev, int code);
void change_left_max(NODE *aux, NODE *rem, NODE *prev);*/


#endif
