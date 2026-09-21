#include "st.h"

void newLevel(SymbolTable *st) {
    if (!st) ERROR_ST("cannot open a new level because st is NULL")

    Level *level = (Level*)malloc(sizeof(Level)); 
    level->head  = NULL;
    level->next  = st->top; 
    st->top      = level;
}

void closeLevel(SymbolTable *st) {
    if (!st)      ERROR_ST("cannot close the level because st is NULL")
    if (!st->top) ERROR_ST("the symbol table level stack is NULL");

    Level *oldTop = st->top;
    st->top       = st->top->next;

    // no borro los simbolos del nivel porque estan apuntados por nodos del ast
    free(oldTop);
}

bool insertSymbol(SymbolTable *st, SymbolConfig *config) {
    if (!st) ERROR_ST("the symbol table is null (insertSymbol)")

    // primero chequear que no exista el simbolo en el nivel corriente
    Symbol *aux = st->top->head;

    while (aux) {
        if (strcmp(aux->name, config->name) == 0) {
            return false; // la variable ya fue declarada
        }
        aux = aux->next;
    }

    Symbol *s         = (Symbol*)malloc(sizeof(Symbol));
    s->type           = config->type;
    s->name           = config->name;
    s->semanticType   = config->semanticType;
    s->value          = config->value;
    s->parameters     = config->parameters;
    s->next           = NULL;
    s->referenceCount = 0;

    s->next       = st->top->head;
    st->top->head = s;
    
    PRINT_SYMBOL_TABLE(st)
    
    return true;
}

Symbol * searchSymbol(SymbolTable *st, char *name) {
    if (!st) ERROR_ST("the symbol table is NULL (searchSymbol)")

    Level *currentLevel = st->top;

    while (currentLevel) {
        Symbol *aux = currentLevel->head;

        while (aux) {
            if (strcmp(aux->name, name) == 0) return aux;
            aux = aux->next;
        }

        currentLevel = currentLevel->next;
    }

    return NULL;
}

void printSymbolTable(SymbolTable *st) {
    printf("****TS****\n");
    Level *levelAux = st->top;
    Symbol *symbolAux;

    while (levelAux != NULL) {
        symbolAux = levelAux->head;

        while (symbolAux != NULL) {
            printf("[%s] -> ", symbolAux->name);
            symbolAux = symbolAux->next;
        }
        printf("NULL\n");
        printf("ʌ\n");
        printf("|\n");
        levelAux = levelAux->next;
    }
}

// creo que no es necesaria esta funcion
void freeSymbolTable(SymbolTable *st) {
    TODO("freeSymbolTable() not yet implemented")
}

void freeSymbol(Symbol *s) {
    if (!s) ERROR_ST("s is NULL (freeSymbol)")

    if (s->name) free(s->name);

    Symbol *paramAux = s->parameters;

    while (paramAux) {
        Symbol *nextParamAux = paramAux->next;
        freeSymbol(paramAux);
        paramAux = nextParamAux;
    }

    free(s);
}
