#include <stdlib.h>
#include "../include/string_utils.h"

enum Comparison switch_cmp_mode(enum Comparison val) {
    if (val < 3 || val > 5) return 8 - val;
    return val;
}

ast_node* new_name(const char* v_first, const char* v_second) {
    ast_node* new_node = malloc(sizeof(ast_node));
    new_node->type = NAME_NODE;
    if (v_first != NULL)
        new_node->fields_one.str = safe_strcpy(v_first);
    if (v_second != NULL)
        new_node->fields_two.str = safe_strcpy(v_second);
    new_node->first = NULL;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}

ast_node *new_string(ast_node *first, const char *v_second) {
    ast_node* new_node = malloc(sizeof(ast_node));
    new_node->type = STRING_NODE;
    if (first)
        new_node->fields_one.str = safe_strcpy(first->fields_one.str);
    if (v_second) {
        if (first)
            safe_strcat(&new_node->fields_one.str, " ");
        else new_node->fields_one.str = safe_strcpy("");
        safe_strcat(&new_node->fields_one.str, v_second);
    }
    new_node->first = NULL;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}

ast_node* new_number(int v_first) {
    ast_node* new_node = malloc(sizeof(ast_node));
    new_node->type = NUMBER_NODE;
    new_node->fields_one.integer = v_first;
    new_node->first = NULL;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}

ast_node* new_float_number(float v_first) {
    ast_node* new_node = malloc(sizeof(ast_node));
    new_node->type = FLOAT_NUMBER_NODE;
    new_node->fields_one.flt = v_first;
    new_node->first = NULL;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}

ast_node* new_bool(bool v_first) {
    ast_node* new_node = malloc(sizeof(ast_node));
    new_node->type = BOOLEAN_NODE;
    new_node->fields_one.boolean = v_first;
    new_node->first = NULL;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}

ast_node* new_type(enum DataType v_first) {
    ast_node* new_node = malloc(sizeof(ast_node));
    new_node->type = TYPE_NODE;
    new_node->fields_one.data_type = v_first;
    new_node->first = NULL;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}

ast_node* new_list(ast_node* first, ast_node* second) {
    ast_node* new_node = malloc(sizeof(ast_node));
    new_node->type = LIST_NODE;
    new_node->first = first;
    new_node->second = second;
    new_node->third = NULL;
    return new_node;
}

ast_node* new_pair(const char* v_first, ast_node* second) {
    ast_node* new_node = malloc(sizeof(ast_node));
    new_node->type = PAIR_NODE;
    new_node->fields_one.str = safe_strcpy(v_first);
    new_node->first = NULL;
    new_node->second = second;
    new_node->third = NULL;
    return new_node;
}
ast_node* new_select(const char* v_first, ast_node* first, const char* v_second, ast_node* second, ast_node* third) {
    ast_node* new_node = malloc(sizeof(ast_node));
    new_node->type = FOR_NODE;
    new_node->fields_one.str = safe_strcpy(v_first);
    if (v_second != NULL) new_node->fields_two.str = safe_strcpy(v_second);
    else new_node->fields_two.str = NULL;
    new_node->first = first;
    new_node->second = second;
    new_node->third = third;
    return new_node;
}
ast_node* new_delete(const char* v_first, ast_node* first) {
    ast_node* new_node = malloc(sizeof(ast_node));
    new_node->type = REMOVE_NODE;
    new_node->fields_one.str = safe_strcpy(v_first);
    new_node->first = first;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}
ast_node* new_insert(const char* v_first, ast_node* first) {
    ast_node* new_node = malloc(sizeof(ast_node));
    new_node->type = INSERT_NODE;
    new_node->fields_one.str = safe_strcpy(v_first);
    new_node->first = first;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}
ast_node* new_update(const char* v_first, ast_node* first, ast_node* second) {
    ast_node* new_node = malloc(sizeof(ast_node));
    new_node->type = UPDATE_NODE;
    new_node->fields_one.str = safe_strcpy(v_first);
    new_node->first = first;
    new_node->second = second;
    new_node->third = NULL;
    return new_node;
}
ast_node* new_create(const char* v_first, ast_node* first) {
    ast_node* new_node = malloc(sizeof(ast_node));
    new_node->type = CREATE_NODE;
    new_node->fields_one.str = safe_strcpy(v_first);
    new_node->first = first;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}
ast_node* new_drop(const char* v_first) {
    ast_node* new_node = malloc(sizeof(ast_node));
    new_node->type = DROP_NODE;
    new_node->fields_one.str = safe_strcpy(v_first);
    new_node->first = NULL;
    new_node->second = NULL;
    new_node->third = NULL;
    return new_node;
}
ast_node* new_where(enum LogicOperation v_first, ast_node* first, ast_node* second) {
    ast_node* new_node = malloc(sizeof(ast_node));
    new_node->type = FILTER_NODE;
    new_node->fields_one.log_op = v_first;
    new_node->first = first;
    new_node->second = second;
    new_node->third = NULL;
    return new_node;
}
ast_node* new_compare(enum Comparison v_first, ast_node* first, ast_node* second) {
    ast_node* new_node = malloc(sizeof(ast_node));
    new_node->type = COMPARE_NODE;
    new_node->fields_one.comp = v_first;
    new_node->first = first;
    new_node->second = second;
    new_node->third = NULL;
    return new_node;
}

void close_tree(ast_node* root) {
    if (root == NULL) return;
    close_tree(root->first);
    close_tree(root->second);
    close_tree(root->third);
    if (root->type == NAME_NODE ||
        root->type == STRING_NODE ||
        root->type == FOR_NODE ||
        root->type == REMOVE_NODE ||
        root->type == INSERT_NODE ||
        root->type == UPDATE_NODE ||
        root->type == CREATE_NODE ||
        root->type == DROP_NODE ||
        root->type == PAIR_NODE)
        free(root->fields_one.str);
    if (root->type == NAME_NODE ||
        root->type == FOR_NODE)
        free(root->fields_two.str);
    free(root);
}
