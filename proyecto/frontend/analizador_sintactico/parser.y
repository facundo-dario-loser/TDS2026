%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../utils/debug.h"
#include "../../tads/ast.h"

extern int yylex(void);
void yyerror(const char *s);

extern FILE *yyin;
extern int  yylineno;

AstNode *root = NULL;
%}

// para que meta 'ast.h' en 'parser.tab.h'
%code requires { #include "../../tads/ast.h" }

// para hacer mejores logs cuando hay un error de sintaxis
%define parse.error detailed 

// valores/datos que pueden tener los tokens
%union {
    int     intValue;
    float   floatValue;
    bool    boolValue;
    char    *strValue;
    AstNode *node;
}

%token <strValue>   ID
%token <intValue>   INT_LITERAL
%token <floatValue> FLOAT_LITERAL
%token <boolValue>  BOOL_LITERAL
%type  <node>       p global_decl_list var_decl method_decl_list method_decl type list_id params block param block_elems statements statement expr method_call list_expr

// VOID en realidad tiene tipo AstNode pero como no se usa en ningun lado no hace falta
%token VOID INT BOOLEAN FLOAT IF ELSE WHILE RETURN EQUAL AND OR

// precendencia (de menor a mayor)
%left OR
%left AND
%nonassoc EQUAL
%nonassoc '<' '>'
%left '-' '+'
%left '*' '/' '%'
%precedence UMINUS '!' // quiero definir la precendencia pero no quiero definir la asociatividad
                       // porque no tiene sentido dado que son operadores unarios
                       // luego: '-' expr %prec UMINUS le dice a bison que en ese caso tome la
                       // precedencia del - (unario) y no del menos binario (resta)

%%
p: global_decl_list {
                        $$   = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_P, .children1 = $1, .line = yylineno});
                        root = $$;
                    }
 ;

global_decl_list: var_decl global_decl_list { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_GLOBAL_DECL_LIST, .children1 = $1, .children2 = $2, .line = yylineno}); }
                | method_decl_list          { $$ = $1; }
                ;

method_decl_list: method_decl method_decl_list { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_METHOD_DECL_LIST, .children1 = $1, .children2 = $2, .line = yylineno}); }
                | %empty                       { $$ = NULL; }
                ;

var_decl: type list_id ';' { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_VAR_DECL, .children1 = $1, .children2 = $2, .line = yylineno}); } 
        ;

list_id: ID             { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = $1, .line = yylineno}); }
       | ID ',' list_id {   
                            AstNode *aux = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = $1, .line = yylineno});
                            $$           = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_LIST_ID, .children1 = aux, .children2 = $3, .line = yylineno}); 
                        } 
       ;

method_decl: type ID '(' params ')' block { 
                                            AstNode *auxID = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = $2, .line = yylineno});
                                            $$             = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_METHOD_DECL, .children1 = $1, .children2 = auxID, .children3 = $4, .children4 = $6, .line = yylineno}); 
                                          }
           | type ID '(' ')' block        {
                                            AstNode *auxID = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = $2, .line = yylineno});
                                            $$             = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_METHOD_DECL, .children1 = $1, .children2 = auxID, .children4 = $5, .line = yylineno});
                                          }
           | VOID ID '(' params ')' block {
                                            AstNode *auxVoid = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_VOID, .line = yylineno});
                                            AstNode *auxID   = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = $2, .line = yylineno});
                                            $$               = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_METHOD_DECL, .children1 = auxVoid, .children2 = auxID, .children3 = $4, .children4 = $6, .line = yylineno}); 
                                          }
           | VOID ID '(' ')' block        {
                                            AstNode *auxVoid = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_VOID, .line = yylineno});
                                            AstNode *auxID   = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = $2, .line = yylineno});
                                            $$               = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_METHOD_DECL, .children1 = auxVoid, .children2 = auxID, .children4 = $5, .line = yylineno});
                                          }
           ;

params: param ',' params { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_PARAMS, .children1 = $1, .children2 = $3, .line = yylineno}); } 
      | param            { $$ = $1; }
      ;

param: type ID { 
                AstNode *auxID = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = $2, .line = yylineno});
                $$             = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_PARAM, .children1 = $1, .children2 = auxID, .line = yylineno}); 
               }
     ;

block: '{' block_elems '}' { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_BLOCK, .children1 = $2, .line = yylineno}); }
     ;

block_elems: var_decl block_elems { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_BLOCK_ELEMS, .children1 = $1, .children2 = $2, .line = yylineno}); }
           | statements           { $$ = $1; }
           ;

type: INT     { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_TYPE, .declarationType = AST_NODE_DECLARATION_TYPE_INT, .line = yylineno}); }
    | BOOLEAN { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_TYPE, .declarationType = AST_NODE_DECLARATION_TYPE_BOOLEAN, .line = yylineno}); }
    | FLOAT   { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_TYPE, .declarationType = AST_NODE_DECLARATION_TYPE_FLOAT, .line = yylineno}); }
    ;

statements: statement statements { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_STATEMENTS, .children1 = $1, .children2 = $2, .line = yylineno}); }
          | %empty               { $$ = NULL; }
          ;

statement: ID '=' expr ';'                  {
                                                AstNode *auxID = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = $1, .line = yylineno});
                                                $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ASSIGNMENT, .children1 = auxID, .children2 = $3, .line = yylineno});
                                            }
         | method_call ';'                  { $$ = $1; }
         | IF '(' expr ')' block            { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_IF_ELSE, .children1 = $3, .children2 = $5, .line = $3->line}); }
         | IF '(' expr ')' block ELSE block { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_IF_ELSE, .children1 = $3, .children2 = $5, .children3 = $7, .line = $3->line}); }
         | WHILE '(' expr ')' block         { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_WHILE, .children1 = $3, .children2 = $5, .line = $3->line}); }
         | RETURN expr ';'                  { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_RETURN, .children1 = $2, .line = yylineno}); }
         | RETURN ';'                       { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_RETURN, .line = yylineno}); }
         | ';'                              { $$ = NULL; }
         | block                            { $$ = $1; } 
         ;

method_call: ID '(' ')'           { 
                                    AstNode *auxID = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = $1, .line = yylineno});
                                    $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_METHOD_CALL, .children1 = auxID, .line = yylineno}); 
                                  }
           | ID '(' list_expr ')' {
                                    AstNode *auxID = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = $1, .line = yylineno});
                                    $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_METHOD_CALL, .children1 = auxID, .children2 = $3, .line = yylineno}); 
                                  }
           ;

list_expr: expr ',' list_expr { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_LIST_EXPR, .children1 = $1, .children2 = $3, .line = yylineno}); }
         | expr               { $$ = $1; }
         ;

expr: ID                    { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = $1, .line = yylineno}); }
    | method_call           { $$ = $1; }
    | INT_LITERAL           { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_INT_LITERAL, .value.intValue = $1, .line = yylineno}); }
    | FLOAT_LITERAL         { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_FLOAT_LITERAL, .value.floatValue = $1, .line = yylineno}); }
    | BOOL_LITERAL          { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_BOOL_LITERAL, .value.booleanValue = $1, .line = yylineno}); }
    | expr '+' expr         { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ADDITION, .children1 = $1, .children2 = $3, .line = yylineno}); }
    | expr '-' expr         { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_SUBTRACTION, .children1 = $1, .children2 = $3, .line = yylineno}); }
    | expr '*' expr         { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_MULTIPLICATION, .children1 = $1, .children2 = $3, .line = yylineno}); }
    | expr '/' expr         { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_DIVISION, .children1 = $1, .children2 = $3, .line = yylineno}); }
    | expr '%' expr         { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_MOD, .children1 = $1, .children2 = $3, .line = yylineno}); }
    | expr '<' expr         { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_COMPARISION_SMALLER, .children1 = $1, .children2 = $3, .line = yylineno}); }
    | expr '>' expr         { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_COMPARISION_GREATER, .children1 = $1, .children2 = $3, .line = yylineno}); }
    | expr EQUAL expr       { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_EQUAL, .children1 = $1, .children2 = $3, .line = yylineno}); }
    | expr AND expr         { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_AND, .children1 = $1, .children2 = $3, .line = yylineno}); }
    | expr OR expr          { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_OR, .children1 = $1, .children2 = $3, .line = yylineno}); }
    | '-' expr %prec UMINUS { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_MINUS, .children1 = $2, .line = yylineno}); }
    | '!' expr              { $$ = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_NEGATION, .children1 = $2, .line = yylineno}); }
    | '(' expr ')'          { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    ERROR_PARSER("%s (line %d)\n", s, yylineno)
}

