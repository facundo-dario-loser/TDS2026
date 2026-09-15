#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "debug.h"

// opciones del compilador
typedef enum Option {
    OPTION_O,      // para renombrar el ejecutable
    OPTION_TARGET, // indicar hasta que etapa ejecutar el compilador
    OPTION_OPT,    // indicar optimizaciones
    OPTION_DEBUG,  // debugear al compilar
} Option;

// etapas del compilador
typedef enum Stage {
    STAGE_SCAN,     // para ejecutar solamente el lexer
    STAGE_PARSE,    // para frenar luego del analisis sintactico
    STAGE_CODINTER, // para frenar en la generacion de codigo intermedio
    STAGE_ASSEMBLY, // para frenar en la generacion de assembly 
} Stage;

extern FILE *yyin;
extern int  yyparse();
extern bool debugFlag;

Option getArgumentOption(int argc, char *argv[]);
Stage  getArgumentStage(int argc, char *argv[]);

void processOptionO(int argc, char *argv[]);
void processOptionTarget(int argc, char *argv[]);
void processOptionOpt(int argc, char *argv[]);
void processOptionDebug(int argc, char *argv[]);

#endif // ARGUMENT_H