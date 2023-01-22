#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "string_utils.h"

char* safe_strcpy (const char* from) {
    int count = strlen(from);
    char* ret = malloc(sizeof(char) * (count + 1));
    strcpy(ret, from);
    return ret;
}

void safe_strcat (char** str, const char * str2) {
    char* str1 = *str;
    int first_len = strlen(str1), second_len = strlen(str2);
    char * new_str = malloc(sizeof(char) * (first_len + second_len + 1));
    strcat(new_str, str1);
    strcat(new_str, str2);
    free(str1);
    *str = new_str;
}

void indent(int indentation, char** src) {
    for (int i = 0; i < indentation; i++) {
        safe_strcat(src, "   ");
    }
}


char* print_string_node(Node* node, int indentation) {
    char* output = malloc(sizeof(char));
    indent(indentation, &output);
    safe_strcat(&output, "String { ");
    safe_strcat(&output, node->v_first.str);
    safe_strcat(&output, " }");
    return output;
}

char* print_column_node(Node* node, int indentation) {
    char* output = malloc(sizeof(char));
    indent(indentation, &output);
    safe_strcat(&output, "Column {\n");
    indent(indentation + 1, &output);
    if (node->v_first.str) {
        safe_strcat(&output, "table: ");
        safe_strcat(&output, node->v_first.str);
        safe_strcat(&output, "\n");
        indent(indentation + 1, &output);
    }
    if (node->v_second.str) {
        safe_strcat(&output, "column_name: ");
        safe_strcat(&output, node->v_second.str);
        safe_strcat(&output, "\n");
        indent(indentation, &output);
    }
    safe_strcat(&output, "}");
    return output;
}

char* print_integer_node(Node* node, int indentation) {
    char* output = malloc(sizeof(char));
    indent(indentation, &output);
    safe_strcat(&output, "Number { ");
    int length = snprintf(NULL, 0, "%d", node->v_first.integer);
    char* str = malloc( length + 1 );
    snprintf(str, length + 1, "%d", node->v_first.integer);
    safe_strcat(&output, str);
    free(str);
    safe_strcat(&output, " }");
    return output;
}

char* print_float_node(Node* node, int indentation) {
    char* output = malloc(sizeof(char));
    indent(indentation, &output);
    safe_strcat(&output, "Float Number { ");
    int length = snprintf(NULL, 0, "%f", node->v_first.flt);
    char* str = malloc( length + 1 );
    snprintf(str, length + 1, "%f", node->v_first.flt);
    safe_strcat(&output, str);
    free(str);
    safe_strcat(&output, " }");
    return output;
}

char* print_boolean_node(Node* node, int indentation) {
    char* output = malloc(sizeof(char));
    indent(indentation, &output);
    safe_strcat(&output, "Boolean { ");
    safe_strcat(&output, node->v_first.boolean ? "TRUE" : "FALSE");
    safe_strcat(&output, " }");
    return output;
}

char* print_type_node(Node* node, int indentation) {
    char* output = malloc(sizeof(char));
    indent(indentation, &output);
    safe_strcat(&output, "Type { ");
    safe_strcat(&output, DataType_strings[node->v_first.data_type]);
    safe_strcat(&output, " }");
    return output;
}

char* print_list_node(Node* node, int indentation) {
    char* output = malloc(sizeof(char));
    indent(indentation, &output);
    safe_strcat(&output, "List {\n");
    Node* next = node;
    char* ptr;
    while (next != NULL) {
        ptr = to_string_general(next->first, indentation + 1);
        safe_strcat(&output, ptr);
        free(ptr);
        safe_strcat(&output, ";\n");
        next = next->second;
    }
    indent(indentation, &output);
    safe_strcat(&output, "}");
    return output;
}

char* print_pair_node(Node* node, int indentation) {
    char* output = malloc(sizeof(char));
    indent(indentation, &output);
    safe_strcat(&output, "Pair {\n");
    indent(indentation + 1, &output);
    safe_strcat(&output, "column_name: ");
    safe_strcat(&output, node->v_first.str);
    safe_strcat(&output, "\n");
    char* pair = to_string_general(node->second, indentation + 1);
    safe_strcat(&output, pair);
    free(pair);
    safe_strcat(&output, "\n");
    indent(indentation, &output);
    safe_strcat(&output, "}");
    return output;
}

char* Select_to_string(Node* node, int indentation) {
    char* output = malloc(sizeof(char));
    indent(indentation, &output);
    safe_strcat(&output, "Select {\n");
    char* ptr;
    indent(indentation + 1, &output);
    safe_strcat(&output, "columns: ");
    if (node->third != NULL) {
        safe_strcat(&output, "\n");
        ptr = to_string_general(node->third, indentation + 2);
        safe_strcat(&output, ptr);
        free(ptr);
    }
    else {
        safe_strcat(&output, "*");
    }
    safe_strcat(&output, "\n");
    indent(indentation + 1, &output);
    safe_strcat(&output, "table: ");
    safe_strcat(&output, node->v_first.str);
    safe_strcat(&output, "\n");
    indent(indentation + 1, &output);
    safe_strcat(&output, "join: ");
    if (node->v_second.str != NULL) {
        safe_strcat(&output, node->v_second.str);
    } else {
        safe_strcat(&output, "NULL");
    }
    safe_strcat(&output, "\n");
    indent(indentation + 1, &output);
    safe_strcat(&output, "on: ");
    if (node->second != NULL) {
        safe_strcat(&output, "\n");
        ptr = to_string_general(node->second, indentation + 2);
        safe_strcat(&output, ptr);
        free(ptr);
    } else {
        safe_strcat(&output, "NULL");
    }
    safe_strcat(&output, "\n");
    indent(indentation + 1, &output);
    safe_strcat(&output, "condition: ");
    if (node->first != NULL) {
        safe_strcat(&output, "\n");
        ptr = to_string_general(node->first, indentation + 2);
        safe_strcat(&output, ptr);
        free(ptr);
    } else {
        safe_strcat(&output, "NULL");
    }
    safe_strcat(&output, "\n");
    indent(indentation, &output);
    safe_strcat(&output, "}");
    return output;
}

char* print_delete_node(Node* node, int indentation) {
    char* output = malloc(sizeof(char));
    indent(indentation, &output);
    safe_strcat(&output, "Delete {\n");
    indent(indentation + 1, &output);
    safe_strcat(&output, "table: ");
    safe_strcat(&output, node->v_first.str);
    safe_strcat(&output, "\n");
    indent(indentation + 1, &output);
    safe_strcat(&output, "condition: ");
    char* ptr;
    if (node->first != NULL) {
        safe_strcat(&output, "\n");
        ptr = to_string_general(node->first, indentation + 2);
        safe_strcat(&output, ptr);
        free(ptr);
    } else {
        safe_strcat(&output, "NULL");
    }
    safe_strcat(&output, "\n");
    indent(indentation, &output);
    safe_strcat(&output, "}");
    return output;
}

char* print_insert_node(Node* node, int indentation) {
    char* output = malloc(sizeof(char));
    indent(indentation, &output);
    safe_strcat(&output, "Insert {\n");
    indent(indentation + 1, &output);
    safe_strcat(&output, "name: ");
    safe_strcat(&output, node->v_first.str);
    safe_strcat(&output, "\n");
    char* ptr = to_string_general(node->first, indentation + 1);
    safe_strcat(&output, ptr);
    free(ptr);
    safe_strcat(&output, "\n");
    indent(indentation, &output);
    safe_strcat(&output, "}");
    return output;
}

char* print_update_node(Node* node, int indentation) {
    char* output = malloc(sizeof(char));
    indent(indentation, &output);
    safe_strcat(&output, "Update {\n");
    indent(indentation + 1, &output);
    safe_strcat(&output, "table: ");
    safe_strcat(&output, node->v_first.str);
    safe_strcat(&output, "\n");
    indent(indentation + 1, &output);
    char* ptr;
    safe_strcat(&output, "list_values:");
    if (node->second != NULL) {
        safe_strcat(&output, "\n");
        ptr = to_string_general(node->second, indentation + 2);
        safe_strcat(&output, ptr);
        free(ptr);
    } else {
        safe_strcat(&output, "NULL");
    }
    safe_strcat(&output, "\n");
    indent(indentation + 1, &output);
    safe_strcat(&output, "condition: ");

    if (node->first != NULL) {
        safe_strcat(&output, "\n");
        ptr = to_string_general(node->first, indentation + 2);
        safe_strcat(&output, ptr);
        free(ptr);
    } else {
        safe_strcat(&output, "NULL");
    }
    safe_strcat(&output, "\n");
    indent(indentation, &output);
    safe_strcat(&output, "}");
    return output;
}

char* print_create_node(Node* node, int indentation) {
    char* output = malloc(sizeof(char));
    indent(indentation, &output);
    safe_strcat(&output, "Create {\n");
    indent(indentation + 1, &output);
    safe_strcat(&output, "name: ");
    safe_strcat(&output, node->v_first.str);
    safe_strcat(&output, "\n");
    char* ptr = to_string_general(node->first, indentation + 1);
    safe_strcat(&output, ptr);
    free(ptr);
    safe_strcat(&output, "\n");
    indent(indentation, &output);
    safe_strcat(&output, "}");
    return output;
}

char* print_drop_node(Node* node, int indentation) {
    char* output = malloc(sizeof(char));
    indent(indentation, &output);
    safe_strcat(&output, "Drop { ");
    safe_strcat(&output, node->v_first.str);
    safe_strcat(&output, " }");
    return output;
}

char* print_where_node(Node* node, int indentation) {
    char* output = malloc(sizeof(char));
    indent(indentation, &output);
    safe_strcat(&output, "Where {\n");
    char* ptr = to_string_general(node->first, indentation + 1);
    safe_strcat(&output, ptr);
    free(ptr);
    safe_strcat(&output, "\n");
    indent(indentation + 1, &output);
    safe_strcat(&output, LogicOperation_strings[node->v_first.log_op]);
    safe_strcat(&output, "\n");
    ptr = to_string_general(node->second, indentation + 1);
    safe_strcat(&output, ptr);
    free(ptr);
    safe_strcat(&output, "\n");
    indent(indentation, &output);
    safe_strcat(&output, "}");
    return output;
}

char* print_compare_node(Node* node, int indentation) {
    char* output = malloc(sizeof(char));
    indent(indentation, &output);
    safe_strcat(&output, "Compare {\n");
    char* ptr = to_string_general(node->first, indentation + 1);
    safe_strcat(&output, ptr);
    free(ptr);
    safe_strcat(&output, "\n");
    indent(indentation + 1, &output);
    safe_strcat(&output, Comparison_strings[node->v_first.comp]);
    safe_strcat(&output, "\n");
    ptr = to_string_general(node->second, indentation + 1);
    safe_strcat(&output, ptr);
    free(ptr);
    safe_strcat(&output, "\n");
    indent(indentation, &output);
    safe_strcat(&output, "}");
    return output;
}

typedef char*(*node_to_string)(Node*, int);

node_to_string node_to_string_functions[] = {
        print_column_node,
        print_string_node,
        print_integer_node,
        print_float_node,
        print_boolean_node,
        print_list_node,
        print_pair_node,
        Select_to_string,
        print_insert_node,
        print_delete_node,
        print_update_node,
        print_create_node,
        print_drop_node,
        print_where_node,
        print_compare_node,
        print_type_node
};

char* to_string_general(Node* node, int indentation) {
    return node_to_string_functions[node->type](node, indentation);
}
