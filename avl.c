#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#define ERROR -404

/*ESTRUTURA DE DADOS USADA: Lista Encadeada Ordenada*/
struct node{
	char *keyword;
	NODE* left;
	NODE* right;
	int height;
};

struct avl{
	NODE* root;
	int depth;
};

AVL *avl_create(void){
	AVL *tree = (AVL *) malloc(sizeof (AVL));
	if(tree != NULL){
		tree->root = NULL;
		tree->depth = -1;
	}
	return tree;
}

void avl_delete(AVL **tree){
	delete_avl_aux((*tree)->root);
	free(*tree);
	*tree = NULL;
}

void delete_avl_aux(NODE *root){
	if(root != NULL){
		delete_avl_aux(root->left);
		delete_avl_aux(root->right);
		delete_node_avl(root);
	}
}

void delete_node_avl(NODE* a){
	if(a != NULL){
		free(a->keyword);
		free(a);
		a = NULL;
	}
}

int avl_height_node(NODE* root){
	if(root == NULL){
		return -1;
	}else{
		return root->height;
	}
}

NODE *avl_create_node(char keyword[51]){
	NODE *node = (NODE *) malloc(sizeof (NODE));
	if(node != NULL){
		node->height = 0;
		node->right = NULL;
		node->left = NULL;
		node->keyword = (char *) malloc(51 * sizeof(char));
		strcpy(node->keyword, keyword);
	}
	return node;
}

NODE *rotate_right(NODE *a){
	NODE *b = a->left;
	a->left = b->right;
	b->right = a;
	a->height = max(avl_height_node(a->left),avl_height_node(a->right)) + 1;
	b->height = max(avl_height_node(b->left),	a->height) + 1;
	return b;
}

NODE *rotate_left(NODE *a){
	NODE *b = a->right;
	a->right = b->left;
	b->left = a;
	a->height = max(avl_height_node(a->left),avl_height_node(a->right)) + 1;
	b->height = max(avl_height_node(b->right),	a->height) + 1;
	return b;
}

NODE *rotate_left_right(NODE *a){
	a->left = rotate_left(a->left);
	return rotate_right(a);
}

NODE *rotate_right_left(NODE *a){
	a->right = rotate_right(a->right);
	return rotate_left(a);
}

NODE *avl_insert_node(NODE *root, char keyword[51]){
	if(root == NULL){
		root = avl_create_node(keyword);
	}
	else if(strcmp(keyword, root->keyword) > 0){
		root->right = avl_insert_node(root->right, keyword);
		if(avl_height_node(root->left) - avl_height_node(root->right) == -2){
			if(strcmp(keyword, root->right->keyword) > 0){
				root = rotate_left(root);
			}else{
				root = rotate_right_left(root);
			}
		}
	}
	else if(strcmp(keyword, root->keyword) < 0){
		root->left = avl_insert_node(root->left, keyword);
		if(avl_height_node(root->left) - avl_height_node(root->right) == 2){
			if(strcmp(keyword, root->left->keyword) < 0){
				root = rotate_right(root);
			}else{
				root = rotate_left_right(root);
			}
		}
	}
	root->height = max(avl_height_node(root->left),avl_height_node(root->right)) + 1;
	return root;
}

int avl_insert(AVL *tree, char keyword[51]){
	return ((tree->root = avl_insert_node(tree->root, keyword)) != NULL);
}

void avl_print(AVL* tree){
	print_tree(tree->root);
}

void print_tree(NODE* root){
	if(root == NULL) return;
	print_tree(root->left);
	printf("%s\n", root->keyword);
	print_tree(root->right);
}

NODE* avl_root(AVL* tree){
	if(tree == NULL) return NULL;
	return tree->root;
}

void avl_save(AVL *tree, FILE *fp){
	tree_save(tree->root, fp);
}

void tree_save(NODE *root, FILE *fp){
	if(root == NULL) return;
	tree_save(root->left, fp);
	fprintf(fp, "%s,", root->keyword);
	tree_save(root->right, fp);
}

int avl_search(AVL *tree, char keyword[51]){
	return avl_search_aux(tree->root, keyword);
}

int avl_search_aux(NODE *root, char keyword[51]){
	if(root == NULL) return 0;
	if(!strcmp(root->keyword, keyword)) return 1;
	if(strcmp(root->keyword, keyword) < 0) return avl_search_aux(root->right, keyword);
	return avl_search_aux(root->left, keyword);
}

void avl_copy_keywords(AVL *tree, char **keywords){
	int i=0;
	avl_copy_aux(tree->root, keywords, &i);
}

void avl_copy_aux(NODE *root, char **keywords, int *i){
	if(root == NULL) return;
	keywords[*i] = (char *) malloc(51 * sizeof(char));
	strcpy(keywords[*i], root->keyword);
	(*i)++;
	avl_copy_aux(root->left, keywords, i);
	avl_copy_aux(root->right, keywords, i);
}
