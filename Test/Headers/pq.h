#ifndef priority_queue
#define priority_queue

typedef struct node node;
typedef struct pq pq;

struct pq {
	int size;			//Armazena o tamanho da lista de prioridade
	node *head;			//Guarda o nó da cabeça da lista de prioridade
};

pq* create_pq();
node* c_tree(unsigned char charac, int amount, node *left, node *right);
void enqueue(pq *pq, node *tree);
pq* enqueue_amount(int amount[]);
node* dequeue(pq *pq);
void print_pq(pq *pq);

#endif