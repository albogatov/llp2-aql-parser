#include <stdlib.h>
#include "string_utils.h"

enum Comparison reverse_Comparison(enum Comparison val) {
    if (val < 3 || val > 5) return 8 - val;
    return val;
}

Node* new_name(const char* v_first, const char* v_second) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = NAME_my;
    if (v_first != NULL)
        new_node->v_first.str = str_copy(v_first);
    if (v_second != NULL)
        new_node->v_second.str = str_copy(v_second);
    new_node->first = NULL;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}

//Node *new_string(const char *v_first, const char *v_second) {
//    Node* new_node = malloc(sizeof(Node));
//    new_node->type = STRING_my;
//    new_node->v_first.str = str_copy(v_first);
//    if (v_second) {
//        str_concat(&new_node->v_first.str, " ");
//        str_concat(&new_node->v_first.str, v_second);
//    }
//    new_node->first = NULL;
//    new_node->second = NULL;
//    new_node->third = NULL;
//    return new_node;
//}

Node *new_string(Node *first, const char *v_second) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = STRING_my;
    if (first)
        new_node->v_first.str = str_copy(first->v_first.str);
    if (v_second) {
        if (first)
            str_concat(&new_node->v_first.str, " ");
        else new_node->v_first.str = str_copy("");
        str_concat(&new_node->v_first.str, v_second);
    }
    new_node->first = NULL;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}

Node* new_integer(int v_first) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = INTEGER_my;
    new_node->v_first.integer = v_first;
    new_node->first = NULL;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}

Node* new_float(float v_first) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = FLOAT_my;
    new_node->v_first.flt = v_first;
    new_node->first = NULL;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}

Node* new_bool(bool v_first) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = BOOL_my;
    new_node->v_first.boolean = v_first;
    new_node->first = NULL;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}

Node* new_type(enum DataType v_first) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = TYPE_my;
    new_node->v_first.data_type = v_first;
    new_node->first = NULL;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}

Node* new_list(Node* first, Node* second) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = LIST_my;
    new_node->first = first;
    new_node->second = second;
    new_node->third = NULL;
    return new_node;
}

Node* new_pair(const char* v_first, Node* second) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = PAIR_my;
    new_node->v_first.str = str_copy(v_first);
    new_node->first = NULL;
    new_node->second = second;
    new_node->third = NULL;
    return new_node;
}
Node* new_select(const char* v_first, Node* first, const char* v_second, Node* second, Node* third) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = FOR_my;
    new_node->v_first.str = str_copy(v_first);
    if (v_second != NULL) new_node->v_second.str = str_copy(v_second);
    else new_node->v_second.str = NULL;
    new_node->first = first;
    new_node->second = second;
    new_node->third = third;
    return new_node;
}
Node* new_delete(const char* v_first, Node* first) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = REMOVE_my;
    new_node->v_first.str = str_copy(v_first);
    new_node->first = first;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}
Node* new_insert(const char* v_first, Node* first) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = INSERT_my;
    new_node->v_first.str = str_copy(v_first);
    new_node->first = first;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}
Node* new_update(const char* v_first, Node* first, Node* second) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = UPDATE_my;
    new_node->v_first.str = str_copy(v_first);
    new_node->first = first;
    new_node->second = second;
    new_node->third = NULL;
    return new_node;
}
Node* new_create(const char* v_first, Node* first) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = CREATE_my;
    new_node->v_first.str = str_copy(v_first);
    new_node->first = first;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}
Node* new_drop(const char* v_first) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = DROP_my;
    new_node->v_first.str = str_copy(v_first);
    new_node->first = NULL;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}
Node* new_where(enum LogicOperation v_first, Node* first, Node* second) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = FILTER_my;
    new_node->v_first.log_op = v_first;
    new_node->first = first;
    new_node->second = second;
    new_node->third = NULL;
    return new_node;
}
Node* new_compare(enum Comparison v_first, Node* first, Node* second) {
    Node* new_node = malloc(sizeof(Node));
    new_node->type = COMPARE_my;
    new_node->v_first.comp = v_first;
    new_node->first = first;
    new_node->second = second;
    new_node->third = NULL;
    return new_node;
}

void close_tree(Node* root) {
    if (root == NULL) return;
    close_tree(root->first);
    close_tree(root->second);
    close_tree(root->third);
    if (root->type == NAME_my ||
        root->type == STRING_my ||
        root->type == FOR_my ||
        root->type == REMOVE_my ||
        root->type == INSERT_my ||
        root->type == UPDATE_my ||
        root->type == CREATE_my ||
        root->type == DROP_my ||
        root->type == PAIR_my)
        free(root->v_first.str);
    if (root->type == NAME_my ||
        root->type == FOR_my)
        free(root->v_second.str);
    free(root);
}
