#ifndef DEBUG_H
#define DEBUG_H

// debug.h: modulo con macros y funciones para debugear e informar errores

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// enum para saber la fuente o de donde viene un mensaje/printf
typedef enum MessageSource {
    MESSAGE_SOURCE_GLOBAL,              // no proviene de ningun lugar en especifico (no sabia que nombre ponerle y deje GLOBAL)
    MESSAGE_SOURCE_ARGUMENT,            // proviene de los argumentos con los que se invoco al compilador
    MESSAGE_SOURCE_LEXICAL_ANALYSIS,    // proviene del analisis lexico
    MESSAGE_SOURCE_SINTAX_ANALYSIS,     // proviene del analisis sintactico
    MESSAGE_SOURCE_SEMANTIC_ANALYSIS,   // proviene del analisis semantico
    MESSAGE_SOURCE_IR_GENERATION,       // proviene de la generacion de codigo intermedio de bajo nivel
    MESSAGE_SOURCE_ASSEMBLY_GENERATION, // proviene de la generacion de assembly
    MESSAGE_SOURCE_AST,                 // proviene del arbol sintactico abstracto
    MESSAGE_SOURCE_SYMBOL_TABLE,        // proviene de la tabla de simbolos
} MessageSource;

extern bool debugFlag;

// retorna un 'MessageSource' como un string literal
char * getMessageSourceString(MessageSource msgSrc);

// macro para utilizar en funciones/secciones que aun no se hayan implementado.
// printea 'TODO' junto al mensaje (msg) y finalmente mata al proceso con exit.
#define TODO(msg) {                      \
                    printf("[TODO]: ");  \
                    printf("%s\n", msg); \
                    exit(EXIT_FAILURE);  \
                  }                      \

// macro para hacer logs y debuguear. Solo printea si se ejecuto el compilador con la opcion -debug.
// printea el prefijo 'LOG_' junto al el source de donde viene el mensaje y finalmente el mensaje en si.
#define LOG(msgSrc, ...) {                                                         \
                            if (debugFlag) {                                       \
                                char * msgSrcStr = getMessageSourceString(msgSrc); \
                                printf("[LOG_%s]: ", msgSrcStr);                   \
                                printf(__VA_ARGS__);                               \
                                printf("\n");                                      \
                            }                                                      \
                         }                                                         \

// macro para informar un error.
// printea el prefijo 'ERROR_' junto al el source de donde viene el mensaje y finalmente el mensaje en si.
// luego mata al proceso finalizando su ejecucion.
#define ERROR(msgSrc, ...) {                                                       \
                                char * msgSrcStr = getMessageSourceString(msgSrc); \
                                printf("[ERROR_%s]: ", msgSrcStr);                 \
                                printf(__VA_ARGS__);                               \
                                printf("\n");                                      \
                                exit(EXIT_FAILURE);                                \
                           }                                                       \

// macros que expanden en la macro LOG() invocando a la misma con el source correspondiente
// es para evitar poner el source cada vez que invoco a LOG()
#define DEBUG(...)            LOG(MESSAGE_SOURCE_GLOBAL, __VA_ARGS__)
#define DEBUG_ARGUMENT(...)   LOG(MESSAGE_SOURCE_ARGUMENT, __VA_ARGS__)
#define DEBUG_LEXER(...)      LOG(MESSAGE_SOURCE_LEXICAL_ANALYSIS, __VA_ARGS__)
#define DEBUG_PARSER(...)     LOG(MESSAGE_SOURCE_SINTAX_ANALYSIS, __VA_ARGS__)
#define DEBUG_SEMANTIC(...)   LOG(MESSAGE_SOURCE_SEMANTIC_ANALYSIS, __VA_ARGS__)
#define DEBUG_IR(...)         LOG(MESSAGE_SOURCE_IR_GENERATION, __VA_ARGS__)
#define DEBUG_ASSEMBLY(...)   LOG(MESSAGE_SOURCE_ASSEMBLY_GENERATION, __VA_ARGS__)
#define DEBUG_AST(...)        LOG(MESSAGE_SOURCE_AST, __VA_ARGS__)
#define DEBUG_ST(...)         LOG(MESSAGE_SOURCE_SYMBOL_TABLE, __VA_ARGS__)

// macros que expanden en la macro ERROR() invocando a la misma con el source correspondiente
// es para evitar poner el source cada vez que invoco a ERROR()
#define ERROR_GLOBAL(...)   ERROR(MESSAGE_SOURCE_GLOBAL, __VA_ARGS__) 
#define ERROR_ARGUMENT(...) ERROR(MESSAGE_SOURCE_ARGUMENT, __VA_ARGS__)
#define ERROR_LEXER(...)    ERROR(MESSAGE_SOURCE_LEXICAL_ANALYSIS, __VA_ARGS__)
#define ERROR_PARSER(...)   ERROR(MESSAGE_SOURCE_SINTAX_ANALYSIS, __VA_ARGS__)
#define ERROR_SEMANTIC(...) ERROR(MESSAGE_SOURCE_SEMANTIC_ANALYSIS, __VA_ARGS__)
#define ERROR_IR(...)       ERROR(MESSAGE_SOURCE_IR_GENERATION, __VA_ARGS__)
#define ERROR_ASSEMBLY(...) ERROR(MESSAGE_SOURCE_ASSEMBLY_GENERATION, __VA_ARGS__)
#define ERROR_AST(...)      ERROR(MESSAGE_SOURCE_AST, __VA_ARGS__)
#define ERROR_ST(...)       ERROR(MESSAGE_SOURCE_SYMBOL_TABLE, __VA_ARGS__)

#endif // DEBUG_H