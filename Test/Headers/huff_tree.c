#include "huff_tree.h"

node* create_node() {
	node* new_node = (node*) malloc(sizeof(node));
	new_node->priority = 0;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->next = NULL ;
	return new_node;
}

//CONSTRÓI A ÁRVORE COM A SOMA DOS CARACTERES DE MENOR FREQUÊNCIA E OS COLOCA COMO FOLHAS
node *create_huff_node(node *left, node *right) {
	node *huff = (node*) malloc(sizeof(node));
	huff->priority = left->priority + right->priority;//Soma dos dois de menor frequência
	huff->left = left;
	huff->right = right;
	huff->charac = '*';
	huff->next = NULL;

	return huff;
}

//PEGA OS 2 CARACTERES DE MENOR FREQUÊNCIA E COLOCA A SOMA DELES NOVAMENTE NA FILA
node *create_huff(pq *pq) {
	node *huff = create_node();
	while (pq->size > 1) {
		node *left = dequeue(pq);		    //Pega o primeiro elemento da fila que é de menor frequência
		node *right = dequeue(pq);		    //						||
		huff = create_huff_node(left, right);//Manda os dois menores para formar um novo nó pai e eles
		enqueue(pq, huff);			    // serão folhas
	}                                                   //Coloca em fila a cada parte da árvore até que sobre
	return pq->head;                                    // somente a raiz
}

//VERIFICA SE A ÁRVORE ESTÁ VAZIA
int isEmpty(node *tree) {
	return (tree == NULL);
}

//VERIFICA SE O NÓ É UMA FOLHA
int isLeaf(node *tree) {
	return ((tree->left == NULL) && (tree->right == NULL));
}

//SALVA O TAMANHO DA ÁRVORE PERCORRENDO EM PRÉ-ORDEM
void size_tree(node *tree, long long int *size) {
	if(isEmpty(tree)) {
		return;
	}
	if(isLeaf(tree)) {
		if(tree->charac == '*' || tree->charac == '\\') {
			*size += 1;
		}
	}
	*size += 1;
	size_tree(tree->left, size);
	size_tree(tree->right, size);
}

void print_huff_tree(node *node) {
	if(isEmpty(node)) {
		printf("()");
		return;
	}
	else {
		printf("(%u", node->charac);
		print_huff_tree(node->left);
		print_huff_tree(node->right);
		printf(")");
	}
}