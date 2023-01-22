%option noyywrap
%option caseless
%option yylineno

%{
    #include <stdio.h>
    #include <string.h>

    #include "include/ast.h"
    #include "parser.tab.h"
    void print_error(char*);
%}

%option noyywrap nounput noinput batch debug

alpha   [A-Za-z_0-9 \t\r]
id    [a-zA-Z][a-zA-Z_0-9]*
int   ([-+]?[0-9])+
float   [+-]?([0-9]*[.])?[0-9]+
blank [ \t\r]
word ([a-zA-Z_][a-zA-Z0-9_]*)
quoted_string \"{word}*\"

%%

"for"       {return FOR;}
"insert"    {return INSERT;}
"update"    {return UPDATE;}
"create"    {return CREATE;}
"remove"    {return REMOVE;}
"drop"      {return DROP;}
"in"        {return IN;}
"filter"    {return FILTER;}
"with"      {return WITH;}
"return"    {return RETURN;}
"join"      {return JOIN;}

"&&"        {yylval.logic_op = 1; return AND;}
"||"        {yylval.logic_op = 2; return OR;}

">"         {yylval.cmp_type = 1; return CMP;}
">="        {yylval.cmp_type = 2; return CMP;}
"<"         {yylval.cmp_type = 3; return CMP;}
"<="        {yylval.cmp_type = 4; return CMP;}
"=="        {yylval.cmp_type = 5; return CMP;}
"!="        {yylval.cmp_type = 6; return CMP;}

"str"       {yylval.type = 1; return TYPE;}
"int"       {yylval.type = 2; return TYPE;}
"float"     {yylval.type = 3; return TYPE;}
"bool"      {yylval.type = 4; return TYPE;}
"true"      {yylval.boolval = 1; return BOOL;}
"false"     {yylval.boolval = 0; return BOOL;}

"("         {return OPEN_CIRCLE_BRACKET;}
")"         {return CLOSE_CIRCLE_BRACKET;}
"{"         {return OPEN_FIGURE_BRACKET;}
"}"         {return CLOSE_FIGURE_BRACKET;}
";"         {return ENDLINE;}
":"         {return COLON;}
"."         {return DOT;}
","         {return COMMA;}
"\""        {return QUOTE;}

{word}     {
    sscanf(yytext, "%s", yylval.str);
    return (STR);
}
{int}   {
    yylval.intval = atoi(yytext);
    return (INT);
}
{float}     {
    yylval.floatval = atof(yytext);
    return (FLOAT);
}

[ \t]   { /* ignore */ }
[\n]    {}
.           {
    print_error(yytext);
    return (OTHER);
}

%%

void print_error(char* token) {
    printf("Error in tokenizer token = %s \n", token);
}


