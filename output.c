#include "output.h"

void print_tree(Node* root) {
    if (root == NULL) {
        printf("NULL\n");
        return;
    }
    char* res = to_string_general(root, 0);
    printf("%s\n", res);
    free(res);
    close_tree(root);
}

