#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum MessageSource {
    MESSAGE_SOURCE_GLOBAL,
    MESSAGE_SOURCE_ARGUMENT,
    MESSAGE_SOURCE_LEXICAL_ANALYSIS,
    MESSAGE_SOURCE_SINTAX_ANALYSIS,
    MESSAGE_SOURCE_SEMANTIC_ANALYSIS,
    MESSAGE_SOURCE_IR_GENERATION,
    MESSAGE_SOURCE_ASSEMBLY_GENERATION,
    MESSAGE_SOURCE_AST,
    MESSAGE_SOURCE_SYMBOL_TABLE,
} MessageSource;

extern bool debugFlag;

// retorna un 'MessageSource' como un string literal
char * getMessageSourceString(MessageSource msgSrc);

#define TODO(msg) {                      \
                    printf("[TODO]: ");  \
                    printf("%s\n", msg); \
                    exit(EXIT_FAILURE);  \
                  }                      \

#define LOG(msgSrc, ...) {                                                         \
                            if (debugFlag) {                                       \
                                char * msgSrcStr = getMessageSourceString(msgSrc); \
                                printf("[LOG_%s]: ", msgSrcStr);                   \
                                printf(__VA_ARGS__);                               \
                                printf("\n");                                      \
                            }                                                      \
                         }                                                         \

#define ERROR(msgSrc, ...) {                                                       \
                                char * msgSrcStr = getMessageSourceString(msgSrc); \
                                printf("[ERROR_%s]: ", msgSrcStr);                 \
                                printf(__VA_ARGS__);                               \
                                printf("\n");                                      \
                                exit(EXIT_FAILURE);                                \
                           }                                                       \

#define DEBUG(...)            LOG(MESSAGE_SOURCE_GLOBAL, __VA_ARGS__)
#define DEBUG_ARGUMENT(...)   LOG(MESSAGE_SOURCE_ARGUMENT, __VA_ARGS__)
#define DEBUG_LEXER(...)      LOG(MESSAGE_SOURCE_LEXICAL_ANALYSIS, __VA_ARGS__)
#define DEBUG_PARSER(...)     LOG(MESSAGE_SOURCE_SINTAX_ANALYSIS, __VA_ARGS__)
#define DEBUG_SEMANTIC(...)   LOG(MESSAGE_SOURCE_SEMANTIC_ANALYSIS, __VA_ARGS__)
#define DEBUG_IR(...)         LOG(MESSAGE_SOURCE_IR_GENERATION, __VA_ARGS__)
#define DEBUG_ASSEMBLY(...)   LOG(MESSAGE_SOURCE_ASSEMBLY_GENERATION, __VA_ARGS__)
#define DEBUG_AST(...)        LOG(MESSAGE_SOURCE_AST, __VA_ARGS__)
#define DEBUG_ST(...)         LOG(MESSAGE_SOURCE_SYMBOL_TABLE, __VA_ARGS__)

#endif // DEBUG_H