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




void checkFileName(int argcIndex, char *argv[]) {
    char *fileName;  // nombre del archivo
    char *extension; // nombre de la extension

    // si es un path busca la ultima ocurrencia '/'
    fileName = strrchr(argv[argcIndex], '/');

    if (fileName) {
        fileName++; // avanza una posicion porque el primer caracter es '/'
    } else {
        fileName = argv[argcIndex];
    }

    if (fileName[0] == '-') ERROR_ARGUMENT("the name of the file provided starts with '-' (%s)", fileName)

    // busca la ultima ocurrencia de '.'
    extension = strrchr(fileName, '.');

    if (!extension) ERROR_ARGUMENT("the file has no extension (the extension must be '.ctds')")
    if (!stringEquals(extension, ".ctds")) ERROR_ARGUMENT("the file extension must be '.ctds' (%s)", fileName)
}




void processOptionO(int argc, char *argv[]) {
    if (argc < 3) ERROR_ARGUMENT("the name of the executable file was not specified")
    char *outputFileName = argv[2];

    if (argc < 4) ERROR_ARGUMENT("the path to the source file was not provided")
    checkFileName(3, argv);
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

    semanticAnalysis(root);
    DEBUG("semantic analysis done")

    Instruction *instructionList = generateIntermediateCode(root);

    if (!instructionList)
        ERROR_GLOBAL("instructionList is NULL")
    
    DEBUG("intermediate code generated")

    // ya no es necesario el ast
    freeAst(root);

    // setear los offsets para todos los simbolos de variables locales, parametros y temporales
    setSymbolOffsets(instructionList);

    // generacion asm (se debe borrar el archivo .s)
    char *assemblyFileName = generateAssembly(instructionList, outputFileName);

    freeInstructionLinkedList(instructionList);
    
    char command[256];
    snprintf(command, sizeof(command), "gcc %s files_to_link/print.c -o %s", assemblyFileName, outputFileName);
    system(command);

    remove(assemblyFileName);
}




void processOptionTarget(int argc, char *argv[]) {
    Stage stage = getArgumentStage(argc, argv);

    char *outputFileName = getFileNameFromPath(argv[3]);

    if (argc < 4) ERROR_ARGUMENT("the path to the source file was not provided")
    checkFileName(3, argv);
    yyin = fopen(argv[3], "r");

    if (!yyin) {
        ERROR_GLOBAL("couldn't open file '%s'\n", argv[3])
    }

    switch (stage) {
        case STAGE_SCAN: { 
                            while (yylex() != 0) {} 
                            DEBUG("lexical analysis done\n")
                         } break;
        
        case STAGE_PARSE: {
                            int parseResult = yyparse();
    
                            if (parseResult == 0) {
                                DEBUG("sintax analysis done\n")
                            } else {
                                ERROR_GLOBAL("[ERROR]: parseResult is '%d'\n", parseResult)
                            }

                          } break;

        case STAGE_CODINTER: {
                                int parseResult = yyparse();
    
                                if (parseResult == 0) {
                                    DEBUG("sintax analysis done\n")
                                } else {
                                    ERROR_GLOBAL("[ERROR]: parseResult is '%d'\n", parseResult)
                                }
                             
                                semanticAnalysis(root);
                                DEBUG("semantic analysis done")
        
                                Instruction *instructionList = generateIntermediateCode(root);

                                if (!instructionList)
                                    ERROR_GLOBAL("instructionList is NULL")
    
                                DEBUG("intermediate code generated")
                                
                                // aca podria liberar el ast, pero no hace falta en realidad
                                
                                printf("\n****Intermediate Code****\n");
                                printInstructions(instructionList);
                             } break;

        case STAGE_ASSEMBLY: {
                                int parseResult = yyparse();
    
                                if (parseResult == 0) {
                                    DEBUG("sintax analysis done\n")
                                } else {
                                    ERROR_GLOBAL("[ERROR]: parseResult is '%d'\n", parseResult)
                                }
                             
                                semanticAnalysis(root);
                                DEBUG("semantic analysis done")
        
                                Instruction *instructionList = generateIntermediateCode(root);

                                if (!instructionList)
                                    ERROR_GLOBAL("instructionList is NULL")
    
                                DEBUG("intermediate code generated")
                                
                                // ya no es necesario el ast
                                freeAst(root);

                                // setear los offsets para todos los simbolos de variables locales, parametros y temporales
                                setSymbolOffsets(instructionList);

                                // generacion asm (no se borra el archivo generado)
                                generateAssembly(instructionList, outputFileName);

                                freeInstructionLinkedList(instructionList);
                             } break;
    }
}




void processOptionOpt(int argc, char *argv[]) {
    char *outputFileName = getFileNameFromPath(argv[2]);

    if (argc < 3) ERROR_ARGUMENT("the path to the source file was not provided")
    checkFileName(2, argv);
    yyin = fopen(argv[2], "r");

    if (!yyin) {
        ERROR_GLOBAL("couldn't open file '%s'\n", argv[3])
    }

    int parseResult = yyparse();
    
    if (!(parseResult == 0)) ERROR_GLOBAL("[ERROR]: parseResult is '%d'\n", parseResult)

    // obtener el nombre 
    char *aux = strrchr(argv[2], '/');
    if (aux) aux++;
    if (!aux) aux = argv[2];

    // cambiar la extension .ctds por .dot
    char fileName[256];
    int i = 0;

    while (aux[i] != '.') {
        fileName[i] = aux[i]; 
        i++;
    }
    
    strcat(fileName, ".dot");

    semanticAnalysis(root);

    // optimizacion de propagacion de constantes
    constantPropagation(&root);

    // optimizacion de eliminacion de codigo muerto
    deadCodeElimination(&root);

    astToDot(root, fileName);
    printf("[LOG_GLOBAL]: '%s' file generated in folder /dot_files\n", fileName);

    // optimizacion de reuso de offsets
    setOffsetsInAstWithReuse(root);

    Instruction *instructionList = generateIntermediateCode(root);

    if (!instructionList)
        ERROR_GLOBAL("instructionList is NULL")

    // ya no es necesario el ast
    freeAst(root);

    // generacion asm
    char *assemblyFileName = generateAssembly(instructionList, outputFileName);

    freeInstructionLinkedList(instructionList);

    char command[256];
    snprintf(command, sizeof(command), "gcc %s files_to_link/print.c -o %s", assemblyFileName, outputFileName);
    system(command);
}




void processOptionDebug(int argc, char *argv[]) {
    debugFlag            = true;
    char *outputFileName = getFileNameFromPath(argv[2]);

    if (argc < 3) ERROR_ARGUMENT("the path to the source file was not provided")
    checkFileName(2, argv);
    yyin = fopen(argv[2], "r");

    if (!yyin) {
        ERROR_GLOBAL("couldn't open file '%s'\n", argv[3])
    }

    int parseResult = yyparse();
    
    if (parseResult == 0) {
        DEBUG("sintax analysis done")
    } else {
        ERROR_GLOBAL("[ERROR]: parseResult is '%d'\n", parseResult)
    }

    // obtener el nombre 
    char *aux = strrchr(argv[2], '/');
    if (aux) aux++;
    if (!aux) aux = argv[2];

    // cambiar la extension .ctds por .dot
    char fileName[256];
    int i = 0;

    while (aux[i] != '.') {
        fileName[i] = aux[i]; 
        i++;
    }
    
    strcat(fileName, ".dot");

    astToDot(root, fileName);
    DEBUG("'%s' file generated in folder /dot_files", fileName)

    semanticAnalysis(root);
    DEBUG("semantic analysis done")

    Instruction *instructionList = generateIntermediateCode(root);

    if (!instructionList)
        ERROR_GLOBAL("instructionList is NULL")
    
    DEBUG("intermediate code generated")

    printf("\n****Intermediate Code****\n");
    printInstructions(instructionList);

    // ya no es necesario el ast
    freeAst(root);

    // setear los offsets para todos los simbolos de variables locales, parametros y temporales
    setSymbolOffsets(instructionList);
    //PRINT_SYMBOL_OFFSETS(instructionList)

    // generacion asm (no se borra el archivo generado)
    char *assemblyFileName = generateAssembly(instructionList, outputFileName);

    freeInstructionLinkedList(instructionList);

    char command[256];
    snprintf(command, sizeof(command), "gcc %s files_to_link/print.c -o %s", assemblyFileName, outputFileName);
    system(command);
}




char * getFileNameFromPath(char *pathToFile) {
    if (!pathToFile) ERROR_ARGUMENT("pathToFile is NULL in getFileNameFromPath()")

    char *lastSlash = strrchr(pathToFile, '/');
    char *fileName = pathToFile;

    if (lastSlash) fileName = lastSlash + 1;

    char *dot = strrchr(fileName, '.');

    char fileNameWithoutExtension[256];

    if (dot) {
        size_t lengthWithoutExtension = dot - fileName;
        snprintf(fileNameWithoutExtension, lengthWithoutExtension + 1, "%s", fileName);
    } else {
        snprintf(fileNameWithoutExtension, sizeof(fileNameWithoutExtension), "%s", fileName);
    }

    // check: free the memory later
    return strdup(fileNameWithoutExtension);
}
