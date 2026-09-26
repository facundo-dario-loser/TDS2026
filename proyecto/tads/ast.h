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
    AST_NODE_TYPE_VAR_DECL,            // declaracion de variable
    AST_NODE_TYPE_METHOD_DECL_LIST,    // declaracion de metodo/funcion
    AST_NODE_TYPE_METHOD_DECL,         // tipo de una variable o valor de retorno de una funcion
    AST_NODE_TYPE_LIST_ID,             // lista de identificadores (para declaracion de variables)
    AST_NODE_TYPE_ID,                  // identificador de variable o metodo/funcion
    AST_NODE_TYPE_PARAMS,              // lista de parametros para una funcion
    AST_NODE_TYPE_VOID,                // tipo void (porque estaba aparte de 'type' en la gramatica)
    AST_NODE_TYPE_PARAM,               // parametro de una funcion
    AST_NODE_TYPE_BLOCK,               // un bloque { }
    AST_NODE_TYPE_BLOCK_ELEMS,         // elementos de un bloque
    AST_NODE_TYPE_STATEMENTS,          // sentencias
    AST_NODE_TYPE_TYPE,                // quedo redundadnte/confuso pero es por el tipo de un var o retorno de funcion
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

// para declaraciones guardar temporalmente el tipo dentro del nodo del ast 'type'
// esta info luego se guarda en el simbolo
typedef enum AstNodeDeclarationType {
    AST_NODE_DECLARATION_TYPE_INT,
    AST_NODE_DECLARATION_TYPE_FLOAT,
    AST_NODE_DECLARATION_TYPE_BOOLEAN,
} AstNodeDeclarationType;

typedef struct AstNode {
    AstNodeType            type;
    AstNodeDeclarationType declarationType; // solo para nodos 'AST_NODE_TYPE_TYPE'
    AstNodeValue           value;           // guarda temporalmente valores para luego darselos a los simbolos
    Symbol                 *symbol;
    struct AstNode         *children1;
    struct AstNode         *children2;
    struct AstNode         *children3;
    struct AstNode         *children4;
    bool                   isFunctionBlock; // para saber si un BLock es el principal de una funcion (solo se usa en nodos de tipo Block)
                                            // function(...) { Block } (osea si es el bloque principal de la funcion)
    int                    line;            // linea donde se ubica en el archivo fuente
} AstNode;

typedef struct AstNodeConfig {
    AstNodeType            type;
    AstNodeDeclarationType declarationType;
    AstNodeValue           value;
    AstNode                *children1;
    AstNode                *children2;
    AstNode                *children3;
    AstNode                *children4;
    int                    line;
} AstNodeConfig;

AstNode * newAstNode(AstNodeConfig *config); // crea un nuevo nodo dada la configuracion
void      freeAst(AstNode *root);            // libera la memoria todos los nodos del arbol (y de los simbolos a los que apuntan) 

#endif // AST_H
