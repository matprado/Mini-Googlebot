#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

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

/*Função avl_create:
 Cria uma nova árvore AVL;
@Retorno:
-A árvore criada;*/
AVL *avl_create(void){
	AVL *tree = (AVL *) malloc(sizeof (AVL));
	if(tree != NULL){
		tree->root = NULL;
		tree->depth = -1;
	}
	return tree;
}

/*Função avl_delete:
 Desaloca uma árvore AVL;
@Parâmetros:
-Um ponteiro para o árvore AVL;*/
void avl_delete(AVL **tree){
	delete_avl_aux((*tree)->root);
	free(*tree);
	*tree = NULL;
}

/*Função delete_avl_aux:
 Desaloca os nós de uma árvore AVL recursivamente;
@Parâmetros:
-Um ponteiro para o nó raiz da árvore AVL;*/
void delete_avl_aux(NODE *root){
	if(root != NULL){
		delete_avl_aux(root->left);
		delete_avl_aux(root->right);
		delete_node_avl(root);
	}
}

/*Função delete_node_avl:
 Desaloca um nó de uma árvore;
@Parâmetros:
-Um ponteiro para um nó;*/
void delete_node_avl(NODE* a){
	if(a != NULL){
		free(a->keyword);
		free(a);
		a = NULL;
	}
}

/*Função avl_height_node:
 Retorna a altura de uma árvore AVL;
@Parâmetros:
-Um ponteiro para o nó raiz da árvore AVL;
@Retorno:
-A altura da árvore AVL;*/
int avl_height_node(NODE* root){
	if(root == NULL){
		return -1;
	}else{
		return root->height;
	}
}

/*Função avl_create_node:
 Aloca um novo nó em uma árvore AVL;
@Parâmetros:
-A palavra-chave do novo nó;
@Retorno:
-O nó criado;*/
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

/*Função rotate_right:
 Rotaciona a árvore AVL para a direita;
@Parâmetros:
-Um ponteiro para o nó da árvore AVL que se deseja rotacionar;
@Retorno:
-O filho esquerdo do nó problemático*/
NODE *rotate_right(NODE *a){
	NODE *b = a->left;
	a->left = b->right;
	b->right = a;
	a->height = max(avl_height_node(a->left),avl_height_node(a->right)) + 1;
	b->height = max(avl_height_node(b->left), a->height) + 1;
	return b;
}

/*Função rotate_left:
 Rotaciona a árvore AVL para a esquerda;
@Parâmetros:
-Um ponteiro para o nó da árvore AVL que se deseja rotacionar;
@Retorno:
-O filho direito do nó problemático*/
NODE *rotate_left(NODE *a){
	NODE *b = a->right;
	a->right = b->left;
	b->left = a;
	a->height = max(avl_height_node(a->left),avl_height_node(a->right)) + 1;
	b->height = max(avl_height_node(b->right),	a->height) + 1;
	return b;
}

/*Função rotate_left_right:
 Rotaciona a árvore AVL para a esquerda e para a direita;
@Parâmetros:
-Um ponteiro para o nó da árvore AVL que se deseja rotacionar;
@Retorno:
-O filho esquerdo do nó problemático*/
NODE *rotate_left_right(NODE *a){
	a->left = rotate_left(a->left);
	return rotate_right(a);
}

/*Função rotate_right_left:
 Rotaciona a árvore AVL para a direita e para a esquerda;
@Parâmetros:
-Um ponteiro para o nó da árvore AVL onde se deseja rotacionar;
@Retorno:
-O filho direito do nó problemático*/
NODE *rotate_right_left(NODE *a){
	a->right = rotate_right(a->right);
	return rotate_left(a);
}

/*Função avl_insert_node:
 Insere um novo nó na árvore AVL;
@Parâmetros:
-Um ponteiro para o nó raiz da árvore AVL;
-A palavra-chave que se deseja inserir na árvore AVL;
@Retorno:
-O nó raiz;*/
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

/*Função avl_insert:
 Chama a função avl_insert para inserir um novo nó na árvore AVL, passando como parâmetro a raiz da árvore AVL e o nome de um nó;
@Parâmetros:
-Um ponteiro para a árvore AVL;
-A palavra-chave que se deseja inserir na árvore AVL;
@Retorno:
-1 se a inserção foi bem sucessida, ou 0 caso contrário;*/
int avl_insert(AVL *tree, char keyword[51]){
	return ((tree->root = avl_insert_node(tree->root, keyword)) != NULL);
}

/*Função avl_print:
 Chama a função print_tree, que imprime todos os itens da árvore AVL, passando como parâmetro a raiz da árvore AVL;
@Parâmetros:
-Um ponteiro para a árvore AVL;*/
void avl_print(AVL* tree){
	print_tree(tree->root);
}

/*Função print_tree:
 Imprime todos os itens da árvore AVL;
@Parâmetros:
-Um ponteiro para o nó da árvore AVL onde se deseja imprimir;*/
void print_tree(NODE* root){
	if(root == NULL) return;
	print_tree(root->left);
	printf("%s\n", root->keyword);
	print_tree(root->right);
}

/*Função avl_root:
 Retorna o nó raiz da árvore AVL;
@Parâmetros:
-Um ponteiro para a árvore AVL;
@Retorno:
-O nó raiz da árvore AVL*/
NODE* avl_root(AVL* tree){
	if(tree == NULL) return NULL;
	return tree->root;
}

/*Função avl_save:
 Chama a função avl_save, que passa o conteúdo da árvore AVL para um arquivo;
@Parâmetros:
-Um ponteiro para a árvore AVL;
-Um ponteiro para um arquivo;*/
void avl_save(AVL *tree, FILE *fp){
	tree_save(tree->root, fp);
}

/*Função tree_save:
 Salva o conteúdo da árvore AVL para um arquivo;
@Parâmetros:
-Um ponteiro para o nó raiz da árvore AVL;
-O arquivo onde se deseja salvar o conteúdo da árvore;*/
void tree_save(NODE *root, FILE *fp){
	if(root == NULL) return;
	tree_save(root->right, fp);
	tree_save(root->left, fp);	/*Note que a ordem de salvamento está "embaralhada" para não haver muitas rotações na proxima vez que carregar o arquivo*/
	fprintf(fp, "%s,", root->keyword);
}

/*Função avl_search:
 Chama a função avl_search, que faz a busca por uma palavra-chave, passando como parâmetro a raiz da árvore AVL;
@Parâmetros:
-Um ponteiro para a árvore AVL;
-A string palavra-chave;*/
int avl_search(AVL *tree, char keyword[51]){
	return avl_search_aux(tree->root, keyword);
}

/*Função avl_search_aux:
 Procura um nó em uma árvore AVL através de sua palavra-chave;
@Parâmetros:
-Um ponteiro para o nó raiz da árvore AVL;
-A palavra-chave do nó que se deseja encontrar;
@Retorno:
-1 se o nó foi encontrado, ou 0 caso contrário */
int avl_search_aux(NODE *root, char keyword[51]){
	if(root == NULL) return 0;
	if(!strcmp(root->keyword, keyword)) return 1;
	if(strcmp(root->keyword, keyword) < 0) return avl_search_aux(root->right, keyword);
	return avl_search_aux(root->left, keyword);
}

/*Função avl_copy_keywords:
 Chama a função avl_copy_aux, que copia as palavras-chave de uma árvore AVL para um vetor;
@Parâmetros:
-Um ponteiro para a árvore AVL;
-Um ponteiro para um vetor de palavras-chave;*/
void avl_copy_keywords(AVL *tree, char **keywords){
	int i=0;
	avl_copy_aux(tree->root, keywords, &i);
}

/*Função avl_copy_aux:
 Percorre a árvore AVL e copia as palavras-chave para um vetor de strings;
@Parâmetros:
-Um ponteiro para o nó raiz da árvore AVL;
-Um ponteiro para um vetor de palavras-chave;
-Um ponteiro auxiliar;*/
void avl_copy_aux(NODE *root, char **keywords, int *i){
	if(root == NULL) return;
	keywords[*i] = (char *) malloc(51 * sizeof(char));
	strcpy(keywords[*i], root->keyword);
	(*i)++;
	avl_copy_aux(root->left, keywords, i);
	avl_copy_aux(root->right, keywords, i);
}
