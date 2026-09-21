#ifndef AST_H
#define AST_H

// ast.h: implementacion del TAD para el arbol abstracto sintactico

#include <stdbool.h>
#include <stdlib.h>
#include "../utils/debug.h"
#include "st.h"

typedef enum AstNodeType {
    AST_NODE_TYPE_P,                   // todo el programa
    AST_NODE_TYPE_GLOBAL_DECL_LIST,    // declaraciones de todo el programa
    AST_NODE_TYPE_VAR_DECL,            // declaracion de varaible
    AST_NODE_TYPE_METHOD_DECL_LIST,    // declaracion de metodo/funcion
    AST_NODE_TYPE_METHOD_DECL,         // tipo de una variable o valor de retorno de una funcion
    AST_NODE_TYPE_LIST_ID,             // lista de identificadores (para declaracion de variables)
    AST_NODE_TYPE_ID,                  // identificador de variable o metodo/funcion
    AST_NODE_TYPE_PARAMS,              // lista de parametros para una funcion
    AST_NODE_TYPE_BLOCK,               // bloque { }
    AST_NODE_TYPE_VOID,                // tipo void (porque estaba aparte de 'type' en la gramatica)
    AST_NODE_TYPE_PARAM,               // parametro de una funcion
    AST_NODE_TYPE_BLOCK_ELEMS,         // elementos de un bloque
    AST_NODE_TYPE_STATEMENTS,          // sentencias
    AST_NODE_TYPE_TYPE,                // quedo redundadnte/confuso pero es por el tipo de un var o retorno de funcion
    AST_NODE_TYPE_STATEMENT,           // una sentencia
    AST_NODE_TYPE_ASSIGNMENT,          // asignacion
    AST_NODE_TYPE_METHOD_CALL,         // llamada a metodo/funcion
    AST_NODE_TYPE_IF_ELSE,             // condicional if-else
    AST_NODE_TYPE_WHILE,               // ciclo while
    AST_NODE_TYPE_RETURN,              // return ; / return expr;
    AST_NODE_TYPE_LIST_EXPR,           // lista de expresiones (los argumentos que se pasan a una funcion)
    AST_NODE_TYPE_INT_LITERAL,         // literal/cosntante entera
    AST_NODE_TYPE_FLOAT_LITERAL,       // literal/cosntante real
    AST_NODE_TYPE_BOOL_LITERAL,        // literal/cosntante booleana
    AST_NODE_TYPE_ADDITION,            // +
    AST_NODE_TYPE_SUBTRACTION,         // -
    AST_NODE_TYPE_MULTIPLICATION,      // *
    AST_NODE_TYPE_DIVISION,            // /
    AST_NODE_TYPE_MOD,                 // %
    AST_NODE_TYPE_COMPARISION_SMALLER, // <
    AST_NODE_TYPE_COMPARISION_GREATER, // >
    AST_NODE_TYPE_EQUAL,               // ==
    AST_NODE_TYPE_AND,                 // &&
    AST_NODE_TYPE_OR,                  // ||
    AST_NODE_TYPE_MINUS,               // -expr
    AST_NODE_TYPE_NEGATION,            // !expr
} AstNodeType;

typedef union AstNodeValue {
    char  *strValue;    // para nombres de funciones y variables
    int   intValue;     // para constantes enteras
    float floatValue;   // para constantes booleanas
    bool  booleanValue; // para constantes booleanas
} AstNodeValue;

typedef struct AstNode {
    AstNodeType    type;
    AstNodeValue   value; // guarda temporalmente valores para luego darselos a los simbolos
    Symbol         *symbol;
    struct AstNode *left;
    struct AstNode *middle;
    struct AstNode *right;
    bool            hasReturn;
    int             line; // linea donde se ubica en el archivo
} AstNode;

typedef struct AstNodeConfig {
    AstNodeType  type;
    AstNodeValue value;
    AstNode      *left;
    AstNode      *middle;
    AstNode      *right;
    int          line;
} AstNodeConfig;

AstNode * newAstNode(AstNodeConfig *config);
void      freeAst(AstNode *root);

#endif // AST_H
