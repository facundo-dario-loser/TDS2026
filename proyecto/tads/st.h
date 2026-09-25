#ifndef ST_H
#define ST_H

// st.h (symbol table): implementa el TAD para la tabla de simbolos

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../utils/debug.h"

typedef enum SymbolType {
    SYMBOL_TYPE_VARIABLE, // a los parametros tambien los trato como variables locales
    SYMBOL_TYPE_METHOD,
    SYMBOL_TYPE_CONSTANT,
} SymbolType;

typedef enum SymbolSemanticType {
    SYMBOL_SEMANTIC_TYPE_INT,
    SYMBOL_SEMANTIC_TYPE_BOOLEAN,
    SYMBOL_SEMANTIC_TYPE_FLOAT,
    SYMBOL_SEMANTIC_TYPE_VOID, // se usa en funciones que no retornan nada
} SymbolSemanticType;

typedef struct SymbolValue {
    int   intValue;
    float floatValue;
    bool  booleanValue;
} SymbolValue;

typedef struct Symbol {
    SymbolType         type;
    char               *name;
    SymbolSemanticType semanticType;
    SymbolValue        value;
    struct Symbol      *parameters;    // para funciones
    struct Symbol      *next;          // proximo de la lista enlazada (en la tabla de simbolos)
    int                referenceCount; // contador de referencias para liberar el simbolo
    int                offset;         // es para la generacion de asm (offset respecto de rbp) 
    bool               offsetSet;      // para saber si a una variable o temporal ya se le asigno un offset
} Symbol;

typedef struct SymbolConfig {
    SymbolType         type;
    char               *name;
    SymbolSemanticType semanticType;
    SymbolValue        value;
    struct Symbol      *parameters;
    struct Symbol      *functionWhichBelongs; // no es un campo del Symbol, pero sirve para saber si el simbolo esta dentro de una funcion (y tener el puntero al simbolo de la funcion)
} SymbolConfig;

// pila de niveles
typedef struct Level {
    Symbol       *head; // lista de simbolos del nivel
    struct Level *next; // proximo nivel (inferior)
} Level;

typedef struct SymbolTable {
    Level *top; // tope de la pila
} SymbolTable;

void     newLevel(SymbolTable *st);                           // crea un nuevo nivel y lo apila en el tope
void     closeLevel(SymbolTable *st);                         // elimina el nivel del tope
bool     insertSymbol(SymbolTable *st, SymbolConfig *config); // inserta un simbolo en el nivel actual
Symbol * searchSymbol(SymbolTable *st, char *name);           // busca un simbolo en toda la pila de niveles. Si lo encuentra retorna un puntero al mismo y si no retorna NULL
void     printSymbolTable(SymbolTable *st);                   // printea la tabla de simbolos en la terminal
void     freeSymbolTable(SymbolTable *st);                    // libera la memoria de la tabal de simbolos
void     freeSymbol(Symbol *s);                               // libera la memoria de un simbolo
char *   getSemanticTypeString(SymbolSemanticType semanticType);

#endif // ST_h