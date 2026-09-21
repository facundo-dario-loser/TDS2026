#ifndef ARGUMENT_H
#define ARGUMENT_H

// argument.h: modulo para obtener los argumentos de la linea 
// de comandos con los que se invoca al compilador

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "debug.h"

// opciones del compilador
typedef enum Option {
    OPTION_O,
    OPTION_TARGET,
    OPTION_OPT,
    OPTION_DEBUG,
} Option;

// etapas del compilador
typedef enum Stage {
    STAGE_SCAN,     // para ejecutar solamente el lexer
    STAGE_PARSE,    // para frenar luego del analisis sintactico
    STAGE_CODINTER, // para frenar en la generacion de codigo intermedio
    STAGE_ASSEMBLY, // para frenar en la generacion de assembly 
} Stage;

extern FILE *yyin;
extern bool debugFlag;
extern int  yyparse();
extern int  yylex(void);

bool stringEquals(char *str1, char *str2); // retorna true sii str1 == str2 y false en otro caso

Option getArgumentOption(int argc, char *argv[]); // dada una opcion en los argumentos de invocacion, retorna un valor del enumerado 'Option'
Stage  getArgumentStage(int argc, char *argv[]);  // dada la opcion '-target' en los argumentos de invocacion, retorna un valor del enumerado 'Stage'

void processOptionO(int argc, char *argv[]);      // ejecuta el compilador con la opcion '-o <nombre_ejecutable>'
void processOptionTarget(int argc, char *argv[]); // ejecuta el compilador con la opcion '-target <etapa>'
void processOptionOpt(int argc, char *argv[]);    // ejecuta el compilador con la opcion '-opt'
void processOptionDebug(int argc, char *argv[]);  // ejecuta el compilador con la opcion '-debug'

#endif // ARGUMENT_H