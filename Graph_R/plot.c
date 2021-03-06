#include "plot.h"

node * creat_list_empty(){
        return NULL;
}

node * add_node(node * head,
                int item){
        node * new_node = (node*) malloc(sizeof(node));
        new_node->next  = NULL;
        new_node->item  = item;

        if(head == NULL){
                head = new_node;
        }else{
                new_node->next = head;
                head           = new_node;
        }
        return head;
}

void print_list(node * head){
        for (int i = 0; i < 50; ++i) {
                puts("");
        }
        while (head != NULL){
                printf("%d ", head->item);
                head = head->next;
        }
}

void search_list(node * head,
                 int item,
                 int * times){
        while(head != NULL){
                *times += 1;
                if(head->item == item){
                        return;
                }else if(head->next == NULL){
                        *times = 0;
                        return;
                }
                head = head->next;
        }
}

binary_tree * create_empty_binary_tree(){
        return NULL;
}

binary_tree * create_binary_tree(int item,
                                 binary_tree * left,
                                 binary_tree * right){
        binary_tree * new_binary_tree = (binary_tree*) malloc(sizeof(binary_tree));
        new_binary_tree->item = item;
        new_binary_tree->left = left;
        new_binary_tree->right = right;
        return new_binary_tree;
}

bool is_empty(binary_tree * bt){
        if(bt == NULL){
                return true;
        }else{
                return false;
        }
}

void print_in_order(binary_tree * bt){
        if(!is_empty(bt)){
                print_in_order(bt->left);
                printf(" %d ", bt->item);
                print_in_order(bt->right);
        }
}

void print_pre_order(binary_tree * bt){
        if(!is_empty(bt)){
                printf("%d", bt->item);
                print_pre_order(bt->left);
                print_pre_order(bt->right);
        }
}

void print_pos_order(binary_tree * bt){
        if(!is_empty(bt)){
                print_pos_order(bt->left);
                print_pos_order(bt->right);
                printf("%d", bt->item);
        }
}

void search(binary_tree **bt,
            int item,
            int * times){
        *times += 1;
        if(*bt == NULL || ((*bt)->item == item)){
                if(*bt == NULL){
                        *times = 0;
                }
                return;
        } else if ((*bt)->item > item){
                search(&(*bt)->left,
                       item,
                       times);
        }else{
                search(&(*bt)->right,
                       item,
                       times);
        }
}

void add_void(binary_tree * * bt,
              int item){
        if(*bt == NULL){
                *bt = create_binary_tree(item,
                                         NULL,
                                         NULL);
        } else if ((*bt)->item > item){
                add_void(&(*bt)->left,
                         item);
        }else{
                add_void(&(*bt)->right,
                         item);
        }
}

void find_element(binary_tree * bt,
                  node * head){

        int num = 0;
        for (int i = 0; i < 10000; ++i) {
                num  = rand() % 10000;
                int  times_search = 0;
                search(&bt,
                       num,
                       &times_search);

                if(times_search){
                        printf("%d %d", num, times_search);
                }else{
                        continue;
                }

                times_search = 0;
                search_list(head,
                            num,
                            &times_search);
                printf(" %d\n", times_search);
        }
}
