#pragma once
#include <stdbool.h>

enum NodeType {
    NAME_my,
    STRING_my,
    INTEGER_my,
    FLOAT_my,
    BOOL_my,
    LIST_my,
    PAIR_my,
    FOR_my,
    INSERT_my,
    REMOVE_my,
    UPDATE_my,
    CREATE_my,
    DROP_my,
    FILTER_my,
    COMPARE_my,
    TYPE_my
};

enum DataType {
    STR_my,
    INT_my,
    FLT_my,
    BOOLEAN_my
};

static const char* DataType_strings[] = {
        "STR",
        "INT",
        "FLT",
        "BOOLEAN"
};

enum LogicOperation {
    AND_my,
    OR_my
};

static const char* LogicOperation_strings[] = {
        "&&",
        "||"
};

enum Comparison {
    GREATER = 1, GREATER_OR_EQUAL = 2, LESS = 3, LESS_OR_EQUAL = 4, EQUAL = 5, NOT_EQUAL = 6, NO_COMPARE = 7,
};

enum Comparison reverse_Comparison(enum Comparison val);

static const char* Comparison_strings[] = {
        "GREATER",
        "GREATER_OR_EQUAL",
        "LESS",
        "LESS_OR_EQUAL",
        "NO_COMPARE",
        "EQUAL",
        "NOT_EQUAL",
        "NO_COMPARE"
};

union Value {
    char* str;
    enum LogicOperation log_op;
    enum Comparison comp;
    int integer;
    float flt;
    bool boolean;
    enum DataType data_type;
};

typedef struct Node Node;
typedef union Value Value;
typedef enum NodeType NodeType;

struct Node {
    NodeType type;
    Value v_first;
    Value v_second;
    Node* first;
    Node* second;
    Node* third;
};

Node* new_name(const char* v_first, const char* v_second);
Node* new_string(Node *first, const char *v_second);
Node* new_integer(int v_first);
Node* new_float(float v_first);
Node* new_bool(bool v_first);
Node* new_type(enum DataType v_first);
Node* new_list(Node* first, Node* second);
Node* new_pair(const char* v_first, Node* second);
Node* new_select(const char* v_first, Node* first, const char* v_second, Node* second, Node* third);
Node* new_delete(const char* v_first, Node* first);
Node* new_insert(const char* v_first, Node* first);
Node* new_update(const char* v_first, Node* first, Node* second);
Node* new_create(const char* v_first, Node* first);
Node* new_drop(const char* v_first);
Node* new_where(enum LogicOperation v_first, Node* first, Node* second);
Node* new_compare(enum Comparison v_first, Node* first, Node* second);

void close_tree(Node* root);

