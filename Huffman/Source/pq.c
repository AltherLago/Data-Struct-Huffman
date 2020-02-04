#include "../Headers/pq.h"
#include "../Headers/huff_tree.h"

//CRIA A FILA DE PRIORIDADE
pq* create_pq() {
        pq* new_queue   = (pq*) malloc(sizeof(pq));
        new_queue->head = NULL;
        new_queue->size = 0;
        return new_queue;
}

//PROCURA OS CARACTERES E SUAS FREQUENCIAS E MANDA PARA COLOCA-LOS EM FILA
pq* enqueue_amount(int amount[]) {
        pq *pq_new   = (pq*) malloc(sizeof(pq));
        pq_new->head = NULL;
        node* new_node;

        //Quando achar algo diferente de 0, i será o caracter e amount[i] será sua frequência
        //Já cria em formato de árvore com os ponteiros para esquerda e direita
        //Coloca na fila
        for(int i = 0; i < 256; i++) {
                if(amount[i]) {
                        new_node = c_tree(i, amount[i], NULL, NULL);
                        enqueue(pq_new, new_node);
                }
        }

        return pq_new;
}

//CRIA E RETORNA O NÓ DA "PRÉ" ÁRVORE
node* c_tree(unsigned char charac, int amount, node *left, node *right) {
        node *tree     = (node*) malloc(sizeof(node));
        tree->charac   = charac;
        tree->priority = amount;
        tree->next     = NULL;
        tree->left     = left;
        tree->right    = right;

        return tree;
}

//CRIA A FILA EM ORDEM CRESCENTE
void enqueue(pq *pq, node *tree) {
        node *aux = tree;

        if(pq->size == 0) { //Primeiro elemento da fila vazia
                pq->size += 1;
                aux->next = pq->head;
                pq->head  = aux;
        }
        else {
                pq->size      += 1;
                node *current  = pq->head;
                node *previous = NULL;

                while((current != NULL) && (current->priority < aux->priority)){
                        // Depois de feita a soma dos
                        // dois menores, se forem maior
                        // do que o next da fila aqui
                        // será feita a troca de posição
                        previous = current;
                        current  = current->next;
                }
                if(previous == NULL) { //Quando o elemento a ser adicionado é menor que a head
                        aux->next = pq->head;
                        pq->head  = aux;
                        return;
                }
                previous->next = aux;
                aux->next      = current;
        }
}

//REMOVE O PRIMEIRO ELEMENTO DA FILA
node *dequeue(pq *pq) {
        node *aux = pq->head;
        pq->head  = pq->head->next;
        pq->size -= 1;
        return aux;
}

//IMPRIME A FILA DE PRIORIDADE
void print_pq(pq *pq) {
        node *node = pq->head;

        while(node != NULL) {
                printf("%d -> %d\n", node->charac, node->priority);
                node = node->next;
        }
}
