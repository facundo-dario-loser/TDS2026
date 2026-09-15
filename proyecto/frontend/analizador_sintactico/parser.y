%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

extern int yylex(void);
void yyerror(const char *s);

extern FILE *yyin;
%}

// para hacer mejores logs cuando hay un error de sintaxis
%define parse.error detailed 

// valores/datos que pueden tener los tokens
%union {
    int     intValue;
    bool    boolValue;
    float   floatValue;
    char    *string;
}

%token VOID INT BOOLEAN FLOAT IF ELSE WHILE RETURN EQUAL AND OR BOOL_LITERAL INT_LITERAL FLOAT_LITERAL ID
// + - * / % < > 

// precendencia (de menor a mayor)
%left OR
%left AND
%left EQUAL
%left '<' '>'
%left '-' '+'
%left '*' '/' '%'

// quiero definir la precendencia pero no quiero definir la asociatividad
// porque no tiene sentido dado que son operadores unarios
// luego: '-' expr %prec UMINUS le dice a bison que en ese caso tome la
// precedencia del - (unario) y no del menos binario (resta)
%precedence UMINUS '!'

%%
p: decl_list {}
;

decl_list: var_decl decl_list           {}
         | method_decl method_decl_list {}
         | %empty                       {}
;

method_decl_list: method_decl method_decl_list {}
                | %empty                       {}
;

var_decl: type list_id ';' {} 
;

list_id: ID             {} 
       | ID ',' list_id {} 
;

method_decl: type ID '(' ')' block        {}
           | type ID '(' params ')' block {}
           | VOID ID '(' ')' block        {}
           | VOID ID '(' params ')' block {}
;

params: param ',' params {} 
      | param            {}
;

param: type ID {}
;

block: '{' block_elems '}' {}
;

block_elems: var_decl block_elems {}
           | statements           {}
;

type: INT     {}
    | BOOLEAN {}
    | FLOAT   {}
;

statements: statement statements {}
          | %empty
;

statement: ID '=' expr ';'                  {}
         | method_call ';'                  {}
         | IF '(' expr ')' block            {}
         | IF '(' expr ')' block ELSE block {}
         | WHILE expr block                 {}
         | RETURN expr ';'                  {}
         | RETURN ';'                       {}
         | ';'                              {}
         | block                            {}
;

method_call: ID '(' ')'           {}
           | ID '(' list_expr ')' {}
;

list_expr: expr ',' list_expr {}
         | expr               {}
;

expr: ID                    {}
    | method_call           {}
    | literal               {}
    | expr '+' expr         {}
    | expr '-' expr         {}
    | expr '*' expr         {}
    | expr '/' expr         {}
    | expr '%' expr         {}
    | expr '<' expr         {}
    | expr '>' expr         {}
    | expr EQUAL expr       {}
    | expr AND expr         {}
    | expr OR expr          {}
    | '-' expr %prec UMINUS {} 
    | '!' expr              {}
    | '(' expr ')'          {}
;

literal: INT_LITERAL   {}
       | BOOL_LITERAL  {}
       | FLOAT_LITERAL {}
;

%%

void yyerror(const char *s) {
    printf("[SINTAX ERROR]: %s\n", s);
    exit(EXIT_FAILURE);
}

