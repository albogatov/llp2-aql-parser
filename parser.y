
%{
    #include "ast.h"
    #include "output.h"

    #define YYERROR_VERBOSE 1

    extern int yylex();
    extern int yylineno;
    void yyerror(const char*);
%}

%define parse.error verbose

%token FOR REMOVE IN FILTER WITH RETURN INSERT UPDATE CREATE DROP JOIN OTHER

%token
    END 0       "end of file"

    OPEN_CIRCLE_BRACKET         "("
    OPEN_FIGURE_BRACKET         "{"
    CLOSE_CIRCLE_BRACKET        ")"
    CLOSE_FIGURE_BRACKET        "}"
    ENDLINE     ";"
    COLON     ":"
    COMMA       ","
    DOT         "."
    AND         "&&"
    OR          "||"
;
%token TYPE QUOTE

%token CMP BOOL INT FLOAT STR QSTR

%type <intval> CMP
%type <intval> TYPE
%type <boolval> BOOL
%type <intval> INT
%type <floatval> FLOAT
%type <str> STR
%type <intval> AND
%type <intval> OR

// You declare the types of nonterminals using %type.
%type <nonterminal> root
%type <nonterminal> query

%type <nonterminal> select_query
%type <nonterminal> empty_select
%type <nonterminal> filter_select
%type <nonterminal> join_empty_select
%type <nonterminal> join_filter_select

%type <nonterminal> delete_query
%type <nonterminal> empty_delete
%type <nonterminal> filter_delete

%type <nonterminal> update_query
%type <nonterminal> empty_update
%type <nonterminal> filter_update

%type <nonterminal> create_query
%type <nonterminal> drop_query

%type <nonterminal> filter_statement
%type <nonterminal> logic_statement
%type <nonterminal> column
%type <nonterminal> column_name
%type <nonterminal> terminal

%type <nonterminal> insert_query
%type <nonterminal> values_list
%type <nonterminal> values_pair
%type <nonterminal> string_list


%union {
    char str[50];
    int intval;
    bool boolval;
    Node* nonterminal;
    float floatval;

    int cmp_type;
    int logic_op;
    int type;
}

%%

root:
|   root query ENDLINE { print_tree($2); printf("$> "); }
;

query:
|   select_query
|   insert_query
|   delete_query
|   drop_query
|   update_query
|   create_query
;

select_query:
|   empty_select
|   filter_select
|   join_empty_select
|   join_filter_select
;
empty_select:
|   FOR column_name IN STR RETURN STR { $$ = new_select($4, NULL, NULL, NULL, NULL); }
;
filter_select:
|   FOR column_name IN STR FILTER filter_statement RETURN STR { $$ = new_select($4, $6, NULL, NULL, NULL); }
;

// FOR u IN users FOR f IN friends RETURN u, f;
join_empty_select:
|   FOR column_name IN STR FOR column_name IN STR RETURN STR "," STR { $$ = new_select($4, NULL, $8, $6, $2); }
;

// FOR u IN users FOR f IN friends FILTER u.id == f.userId RETURN u, f;
// FOR u IN users FOR f IN friends FILTER u.id == f.userId && f.active == true && (u.status == "active" || f.age > 15) RETURN u, f;
join_filter_select:
|   FOR column_name IN STR FOR column_name IN STR FILTER filter_statement RETURN STR "," STR { $$ = new_select($4, $10, $8, $6, $2); }
;

update_query:
|   empty_update
|   filter_update
;
empty_update:
|   FOR column_name IN STR UPDATE STR WITH "{" values_list "}" IN STR { $$ = new_update($4, NULL, $9); }
;
filter_update:
|   FOR column_name IN STR FILTER filter_statement UPDATE STR WITH "{" values_list "}" IN STR { $$ = new_update($4, $6, $11); }
;

delete_query:
|   empty_delete
|   filter_delete
;
empty_delete:
|   FOR column_name IN STR REMOVE STR IN STR { $$ = new_delete($4, NULL); }
;
filter_delete:
|   FOR column_name IN STR FILTER filter_statement REMOVE STR IN STR { $$ = new_delete($4, $6); }
;

insert_query:
|   INSERT "{" values_list "}" IN STR { $$ = new_insert($6, $3); }
;

create_query:
|   CREATE STR "{" values_list "}" { $$ = new_create($2, $4); }
;

drop_query:
|   DROP STR { $$ = new_drop($2); }
;

values_list:
|   values_list "," values_pair { $$ = new_list($3, $1); }
|   values_pair { $$ = new_list($1, NULL); }
;

values_pair:
|   STR ":" terminal { $$ = new_pair($1, $3); }
;

filter_statement:
|   filter_statement "&&" filter_statement { $$ = new_where($2, $1, $3); }
|   filter_statement "||" filter_statement { $$ = new_where($2, $1, $3); }
|   "(" filter_statement ")" { $$ = $2; }
|   logic_statement
;

logic_statement:
|   column CMP terminal { $$ = new_compare($2, $1, $3); }
|   terminal CMP column { $$ = new_compare(reverse_Comparison($2), $1, $3); }
|   column CMP column { $$ = new_compare($2, $1, $3); }
;

column:
|   STR DOT STR { $$ = new_name($1, $3); }
;

column_name:
|   STR { $$ = new_name(NULL, $1); }
;

string_list:
|   string_list STR { $$ = new_string($1, $2); }
|   STR { $$ = new_string(NULL, $1); }
;

terminal:
|   TYPE { $$ = new_type($1); }
|   INT { $$ = new_integer($1); }
|   FLOAT { $$ = new_float($1); }
|   BOOL { $$ = new_bool($1); }
|   QUOTE string_list QUOTE { $$ = new_string($2, NULL); }
;

%left "+" "-";
%left "*" "/" "%";

%left OR;
%left AND;

%%

void yyerror (const char *s) {
   fprintf (stderr, "%s on line number %d", s, yylineno);
}

int main() {
	printf("$> ");
	yyparse();
	return 0;
}



