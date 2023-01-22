#ifndef STRING_UTILS_H
#define STRING_UTILS_H
#include "ast.h"

char* safe_strcpy (const char* from);
void safe_strcat(char** str, const char * str2);
void indent(int indentation, char** src);

char* to_string_general(ast_node* node, int indentation);

#endif
