#include "plot.h"

int main(){
        binary_tree * bt = create_empty_binary_tree();
        node * list      = creat_list_empty();

        int number = -1;

        srand(time(0));

        for (int i = 0; i < 10000; ++i) {
                number = rand() % 10000;
                add_void(&bt,
                         number);
                list = add_node(list,
                                number);
        }
        printf("element Bt List\n");

        find_element(bt,
                     list);

        puts("");

        return 0;
}