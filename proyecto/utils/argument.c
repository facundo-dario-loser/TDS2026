#include "argument.h"

bool stringEquals(char *str1, char *str2) {
    return strcmp(str1, str2) == 0;
}

Option getArgumentOption(int argc, char *argv[]) {
    if (argc == 1) {
        ERROR_ARGUMENT("no arguments were given\n\t\t  Usage: ./c-tds [option] nombreArchivo.ctds\n")
    }

    if (stringEquals(argv[1], "-o"))      return OPTION_O;
    if (stringEquals(argv[1], "-target")) return OPTION_TARGET;
    if (stringEquals(argv[1], "-opt"))    return OPTION_OPT;
    if (stringEquals(argv[1], "-debug"))  return OPTION_DEBUG;

    ERROR_ARGUMENT("invalid option '%s'\n", argv[1])
}

Stage getArgumentStage(int argc, char *argv[]) {
    if (argc < 3) {
        ERROR_ARGUMENT("no stage was provided\nUsage: c-tds -target <etapa> nombreArchivo.ctds\n")
    }

    if (stringEquals(argv[2], "scan"))     return STAGE_SCAN;
    if (stringEquals(argv[2], "parse"))    return STAGE_PARSE;
    if (stringEquals(argv[2], "codinter")) return STAGE_CODINTER;
    if (stringEquals(argv[2], "assembly")) return STAGE_ASSEMBLY;

    ERROR_ARGUMENT("invalid stage '%s'\n", argv[2])
}

void processOptionO(int argc, char *argv[]) {
    if (argc < 3) ERROR_ARGUMENT("the name of the executable file was not specified")
    char *outputFileName = argv[2];

    if (argc < 4) ERROR_ARGUMENT("the path to the source file was not provided")
    yyin = fopen(argv[3], "r");

    if (!yyin) {
        ERROR_GLOBAL("couldn't open file '%s'\n", argv[3])
    }

    int parseResult = yyparse();
    
    if (parseResult == 0) {
        DEBUG("sintax analysis done\n")
    } else {
        ERROR_GLOBAL("[ERROR]: parseResult is '%d'\n", parseResult)
    }
}

void processOptionTarget(int argc, char *argv[]) {
    Stage stage = getArgumentStage(argc, argv);

    char *outputFileName = "a"; // por default

    if (argc < 4) ERROR_ARGUMENT("the path to the source file was not provided")
    yyin = fopen(argv[3], "r");

    if (!yyin) {
        ERROR_GLOBAL("couldn't open file '%s'\n", argv[3])
    }

    switch (stage) {
        case STAGE_SCAN: while (yylex() != 0) {} 
                         DEBUG("lexical analysis done\n")
                         break;
        
        case STAGE_PARSE: int parseResult = yyparse();
    
                          if (parseResult == 0) {
                            DEBUG("sintax analysis done\n")
                          } else {
                            ERROR_GLOBAL("[ERROR]: parseResult is '%d'\n", parseResult)
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

    if (argc < 3) ERROR_ARGUMENT("the path to the source file was not provided")
    yyin = fopen(argv[2], "r");

    if (!yyin) {
        ERROR_GLOBAL("couldn't open file '%s'\n", argv[3])
    }

    int parseResult = yyparse();
    
    if (parseResult == 0) {
        DEBUG("sintax analysis done\n")
    } else {
        ERROR_GLOBAL("[ERROR]: parseResult is '%d'\n", parseResult)
    }
}
