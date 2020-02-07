#ifndef DATA_STRUCT_HUFFMAN_PLOT_H
#define DATA_STRUCT_HUFFMAN_PLOT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "plot.h"

typedef struct binary_tree binary_tree;

struct binary_tree{
        int item;
        binary_tree * left;
        binary_tree * right;
};

typedef struct node node;

struct node {
        int    item;
        node * next;
};

node * creat_list_empty();

node * add_node(node * head,
                int item);

void print_list(node * head);

void search_list(node * head,
                 int item,
                 int * times);

binary_tree * create_empty_binary_tree();

binary_tree * create_binary_tree(int item,
                                 binary_tree * left,
                                 binary_tree * right);

bool is_empty(binary_tree * bt);

void print_in_order(binary_tree * bt);

void print_pre_order(binary_tree * bt);

void print_pos_order(binary_tree * bt);

void search(binary_tree ** bt,
            int item,
            int * times);

binary_tree * add(binary_tree * bt,
                  int item);

void add_void(binary_tree * * bt,
              int item);

void find_element(binary_tree * bt,
                  node * head);

#endif //DATA_STRUCT_HUFFMAN_PLOT_H
