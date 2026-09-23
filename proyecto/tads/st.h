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
} SymbolConfig;

typedef struct Level {
    Symbol       *head;
    struct Level *next;
} Level;

// pila de niveles (implementada usando una lista enlazada)
typedef struct SymbolTable {
    Level *top;
} SymbolTable;

void     newLevel(SymbolTable *st);
void     closeLevel(SymbolTable *st);
bool     insertSymbol(SymbolTable *st, SymbolConfig *config);
Symbol * searchSymbol(SymbolTable *st, char *name);
void     printSymbolTable(SymbolTable *st);
void     freeSymbolTable(SymbolTable *st);
void     freeSymbol(Symbol *s);

#endif // ST_h