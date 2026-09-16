#include "argument.h"

Option getArgumentOption(int argc, char *argv[]) {
    if (argc == 1) {
        ERROR(MESSAGE_SOURCE_ARGUMENT, "no arguments were given\n\t\t  Usage: ./c-tds [option] nombreArchivo.ctds\n")
    }

    if (strcmp(argv[1], "-o") == 0)      return OPTION_O;
    if (strcmp(argv[1], "-target") == 0) return OPTION_TARGET;
    if (strcmp(argv[1], "-opt") == 0)    return OPTION_OPT;
    if (strcmp(argv[1], "-debug") == 0)  return OPTION_DEBUG;

    ERROR(MESSAGE_SOURCE_ARGUMENT, "invalid option '%s'\n", argv[1])
}

Stage getArgumentStage(int argc, char *argv[]) {
    if (argc < 3) {
        ERROR(MESSAGE_SOURCE_ARGUMENT, "no stage was provided\nUsage: c-tds -target <etapa> nombreArchivo.ctds\n")
    }

    if (strcmp(argv[2], "scan") == 0)     return STAGE_SCAN;
    if (strcmp(argv[2], "parse") == 0)    return STAGE_PARSE;
    if (strcmp(argv[2], "codinter") == 0) return STAGE_CODINTER;
    if (strcmp(argv[2], "assembly") == 0) return STAGE_ASSEMBLY;

    ERROR(MESSAGE_SOURCE_ARGUMENT, "invalid stage '%s'\n", argv[2])
}

void processOptionO(int argc, char *argv[]) {
    if (argc < 3) ERROR(MESSAGE_SOURCE_ARGUMENT, "the name of the executable file was not specified")
    char *outputFileName = argv[2];

    if (argc < 4) ERROR(MESSAGE_SOURCE_ARGUMENT, "the path to the source file was not provided")
    yyin = fopen(argv[3], "r");

    if (!yyin) {
        ERROR(MESSAGE_SOURCE_GLOBAL, "couldn't open file '%s'\n", argv[3])
    }

    int parseResult = yyparse();
    
    if (parseResult == 0) {
        DEBUG("sintax analysis done\n")
    } else {
        ERROR(MESSAGE_SOURCE_GLOBAL, "[ERROR]: parseResult is '%d'\n", parseResult)
    }
}

void processOptionTarget(int argc, char *argv[]) {
    Stage stage = getArgumentStage(argc, argv);

    char *outputFileName = "a"; // por default

    if (argc < 4) ERROR(MESSAGE_SOURCE_ARGUMENT, "the path to the source file was not provided")
    yyin = fopen(argv[3], "r");

    if (!yyin) {
        ERROR(MESSAGE_SOURCE_GLOBAL, "couldn't open file '%s'\n", argv[3])
    }

    switch (stage) {
        case STAGE_SCAN: while (yylex() != 0) {} 
                         DEBUG("lexical analysis done\n")
                         break;
        
        case STAGE_PARSE: int parseResult = yyparse();
    
                          if (parseResult == 0) {
                            DEBUG("sintax analysis done\n")
                          } else {
                            ERROR(MESSAGE_SOURCE_GLOBAL, "[ERROR]: parseResult is '%d'\n", parseResult)
                          }

                          break;
        
        case STAGE_CODINTER: TODO("processOptionTarget (STAGE_CODINTER) not implemented yet")
        case STAGE_ASSEMBLY: TODO("processOptionTarget (STAGE_ASSEMBLY) not implemented yet")
    }
}

void processOptionOpt(int argc, char *argv[]) {
    TODO("OPTION_OPT 'processOptionOpt()' not implemented yet")
}

void processOptionDebug(int argc, char *argv[]) {
    debugFlag = true;
    char *outputFileName = "a"; // default executable name

    if (argc < 3) ERROR(MESSAGE_SOURCE_ARGUMENT, "the path to the source file was not provided")
    yyin = fopen(argv[2], "r");

    if (!yyin) {
        ERROR(MESSAGE_SOURCE_GLOBAL, "couldn't open file '%s'\n", argv[3])
    }

    int parseResult = yyparse();
    
    if (parseResult == 0) {
        DEBUG("sintax analysis done\n")
    } else {
        ERROR(MESSAGE_SOURCE_GLOBAL, "[ERROR]: parseResult is '%d'\n", parseResult)
    }
}
