#include "Headers/compress.h"
#include "Headers/descompress.h"
#include "Headers/hash.h"
#include "Headers/pq.h"
#include "Headers/huff_tree.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

int init_suite(void) {
	return 0;
}

int clear_suite(void) {
	return 0;
}

void hash_tests() {
	hash *new_hash = NULL;
	CU_ASSERT(new_hash == NULL);
	new_hash = create_hash(10);
	CU_ASSERT(new_hash != NULL);
}

void generate_tree_test_string(node *tree, char *string, int *size) {
	if(tree == NULL) {
		string[*size] = '\0';
		return;
	} 
	else {
		if(isLeaf(tree)) {
			string[*size] = tree->charac;
			*size += 1;
		}
		generate_tree_test_string(tree->left, string, size);		
		generate_tree_test_string(tree->right, string, size);
	}
}

node *build_tree_test(pq *pq) {
  node *first_dequeued;
  node *second_dequeued;
  int frequency;

  while(pq->head->next != NULL) {
    first_dequeued = dequeue(pq);
    second_dequeued = dequeue(pq);

    node *enqueued = create_huff_node(first_dequeued, second_dequeued);

    enqueued->left = first_dequeued;
    enqueued->right = second_dequeued;

    enqueue(pq, enqueued);
  }

  return (node*)(pq->head);
}

void  huff_tree_tests () {
	pq *pq = create_pq();
	char string_test[10], string_compare[10];
	int i, size = 0;
	node *tree;
	node *auxiliar;

	auxiliar = c_tree('a', 5, NULL, NULL);
	enqueue(pq, auxiliar);
	auxiliar = c_tree('b', 2, NULL, NULL);
	enqueue(pq, auxiliar);
	auxiliar = c_tree('c', 1, NULL, NULL);
	enqueue(pq, auxiliar);
	auxiliar = c_tree('d', 3, NULL, NULL);
	enqueue(pq, auxiliar);

	for(i = 0; i < 10; i++)	{
		string_test[i] = '0';
		string_compare[i] = '0';
	}
	
	tree = build_tree_test(pq);

	string_compare[0] = 'a';
	string_compare[1] = 'c';
	string_compare[2] = 'b';
	string_compare[3] = 'd';
	string_compare[4] = '\0';

	generate_tree_test_string(tree, string_test, &size);
	CU_ASSERT(strcmp(string_test, string_compare) == 0);
}

void p_queue_tests() {
	pq *pq = create_pq();
	node *auxiliar = NULL;

	//testando create_p_queue
	CU_ASSERT(pq != NULL);
	CU_ASSERT(pq->head == NULL);

	//testando enqueue
	auxiliar = c_tree('a', 5, NULL, NULL);
	enqueue(pq, auxiliar);
	auxiliar = c_tree('b', 2, NULL, NULL);
	enqueue(pq, auxiliar);
	auxiliar = c_tree('c', 1, NULL, NULL);
	enqueue(pq, auxiliar);
	auxiliar = c_tree('d', 3, NULL, NULL);
	enqueue(pq, auxiliar);
	auxiliar = c_tree('e', 1, NULL, NULL);
	enqueue(pq, auxiliar);
	
	
	CU_ASSERT(pq->head->charac == 'e'); 
	CU_ASSERT(pq->head->priority == (int *) 1);
	CU_ASSERT(pq->head->next->charac == 'c');
	CU_ASSERT(pq->head->next->priority == (int *) 1); 
	

	//testando dequeue
	node *node_test = dequeue(pq);
	CU_ASSERT(node_test->charac == 'e');
	CU_ASSERT(node_test->priority == (int *) 1);
	node_test = dequeue(pq);
	CU_ASSERT(node_test->charac == 'c');
	CU_ASSERT(node_test->priority == (int *) 1);
	CU_ASSERT(pq->head->charac == 'b');
}

int run_tests(){
	p_queue_tests();
	huff_tree_tests();
	hash_tests();
}

int main(){

	CU_pSuite pSuite = NULL;

	if(CUE_SUCCESS != CU_initialize_registry()) {
		return CU_get_error();
	}

	pSuite = CU_add_suite("Basic_Test_Suite", init_suite, clear_suite);
	if(pSuite == NULL){
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "p_queue_tests", p_queue_tests)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "huff_tree_tests", huff_tree_tests)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "hash_tests", hash_tests)) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
	return CU_get_error();
}
