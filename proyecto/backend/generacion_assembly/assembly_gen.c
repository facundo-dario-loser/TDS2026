#include "assembly_gen.h"




void setSymbolOffsets(Instruction *list) {
    if (!list) return;

    Instruction *i = list;
    int currentOffset;
    int numberOfLocalVariables;

    while (i) {
        switch (i->type) {
            case INSTRUCTION_TYPE_BEGIN_METHOD: {
                currentOffset          = -8;
                numberOfLocalVariables = 0;

                // setear el offset para todos los params del metodo (se tratan como variables locales)
                Symbol *param = i->result->parameters;

                while (param) {
                    if (!param->offsetSet) {
                        param->offset    = currentOffset;
                        currentOffset   -= 8;
                        param->offsetSet = true;
                        numberOfLocalVariables++;
                    }
                    param = param->next;
                }
                
                i = i->next;
            } break;

            case INSTRUCTION_TYPE_END_METHOD: {
                i->result->numberOfLocalVariables = numberOfLocalVariables;
                i = i->next;
            } break;

            case INSTRUCTION_TYPE_GLOBAL_VAR_DECL: {
                i = i->next; // no hace falta setear el offset
            } break;

            case INSTRUCTION_TYPE_LABEL: {
                i = i->next; // no hace falta setear el offset
            } break;

            case INSTRUCTION_TYPE_CALL_METHOD: {
                // solo hay que setear el offset del temporal donde se guarda el resultado de la invocacion
                if (i->result && !i->result->offsetSet) {
                    i->result->offset    = currentOffset;
                    currentOffset       -= 8;
                    i->result->offsetSet = true;
                    numberOfLocalVariables++;
                }

                i = i->next;
            } break;

            case INSTRUCTION_TYPE_JMP_FALSE: {
                // solo el temporal del op1 se le podria asignar un offset
                if (i->op1 && (i->op1->type != SYMBOL_TYPE_CONSTANT) && !i->op1->offsetSet) {
                    i->op1->offset    = currentOffset;
                    currentOffset    -= 8;
                    i->op1->offsetSet = true;
                    numberOfLocalVariables++;
                }

                i = i->next;
            } break;

            case INSTRUCTION_TYPE_JMP: {
                i = i->next; // no hace falta setear ningun offset
            } break;

            default: {
                if (i->op1 && (i->op1->type != SYMBOL_TYPE_CONSTANT) && !i->op1->offsetSet) {
                    i->op1->offset    = currentOffset;
                    currentOffset    -= 8;
                    i->op1->offsetSet = true;
                    numberOfLocalVariables++;
                }

                if (i->op2 && (i->op2->type != SYMBOL_TYPE_CONSTANT) && !i->op2->offsetSet) {
                    i->op2->offset    = currentOffset;
                    currentOffset    -= 8;
                    i->op2->offsetSet = true;
                    numberOfLocalVariables++;
                }

                if (i->result && (i->result->type != SYMBOL_TYPE_CONSTANT) && !i->result->offsetSet) {
                    i->result->offset    = currentOffset;
                    currentOffset       -= 8;
                    i->result->offsetSet = true;
                    numberOfLocalVariables++;
                }

                i = i->next;
            } break;
        }
    }
}




void printSymbolOffsets(Instruction *list) {
    if (!list) return;

    printf("\n****offsets info:****\n");

    Instruction *i = list;

    while (i) {
        switch (i->type) {
            case INSTRUCTION_TYPE_BEGIN_METHOD: {
                printf("\nmethod name: %s (number of local variables: %d)\n", i->result->name, i->result->numberOfLocalVariables);
                i = i->next;
            } break;

            case INSTRUCTION_TYPE_END_METHOD: {
                printf("\n");
                i = i->next;
            } break;

            case INSTRUCTION_TYPE_GLOBAL_VAR_DECL: {
                i = i->next;
            } break;

            case INSTRUCTION_TYPE_LABEL: {
                i = i->next;
            } break;

            case INSTRUCTION_TYPE_CALL_METHOD: {
                if (i->result)
                    printf("symbol variable: %s (offset: %d)\n", i->result->name, i->result->offset);
                i = i->next;
            } break;

            case INSTRUCTION_TYPE_JMP_FALSE: {
                if (i->op1->type != SYMBOL_TYPE_CONSTANT)
                    printf("symbol variable: %s (offset: %d)\n", i->op1->name, i->op1->offset);
                i = i->next;
            } break;
            
            case INSTRUCTION_TYPE_JMP: {
                i = i->next;
            } break;

            default: {
                if (i->op1 && (i->op1->type != SYMBOL_TYPE_CONSTANT))
                    printf("symbol variable: %s (offset: %d)\n", i->op1->name, i->op1->offset);
            
                if (i->op2 && (i->op2->type != SYMBOL_TYPE_CONSTANT))
                    printf("symbol variable: %s (offset: %d)\n", i->op2->name, i->op2->offset);
            
                if (i->result && (i->result->type != SYMBOL_TYPE_CONSTANT))
                    printf("symbol variable: %s (offset: %d)\n", i->result->name, i->result->offset);
                
                i = i->next;
            } break;
        }
    }
}




char * generateAssembly(Instruction *list, char *outputFileName) {
    if (!list)
        ERROR_ASSEMBLY("list is NULL in generateAssemby()")

    if (!outputFileName)
        ERROR_ASSEMBLY("outputFileName is NULL in generateAssembly()")

    // setear los offsets para todos los simbolos de variables locales, parametros y temporales
    setSymbolOffsets(list);
    PRINT_SYMBOL_OFFSETS(list)

    // obtener el nombre del archivo assembly
    char assemblyFileName[64] = "";
    strcat(assemblyFileName, outputFileName);
    strcat(assemblyFileName, ".s");

    FILE *f = fopen(assemblyFileName, "w");
    generateAssemblyAux(list, f);
    fclose(f);

    return strdup(assemblyFileName);
}




void generateAssemblyAux(Instruction *list, FILE *f) {
    if (!list || !f) return;

    switch (list->type) {
        case INSTRUCTION_TYPE_GLOBAL_VAR_DECL:                generateAssemblyInstructionGlobalVarDecl(list, f);               break;
        case INSTRUCTION_TYPE_BEGIN_METHOD:                   generateAssemblyInstructionBeginMethod(list, f);                 break;
        case INSTRUCTION_TYPE_END_METHOD:                     generateAssemblyInstructionEndMethod(list, f);                   break;
        case INSTRUCTION_TYPE_LABEL:                          generateAssemblyInstructionLabel(list, f);                       break;
        case INSTRUCTION_TYPE_ASSIGNMENT_INT_INT:             generateAssemblyInstructionAssignmentIntInt(list, f);            break;
        case INSTRUCTION_TYPE_ASSIGNMENT_INT_FLOAT:           generateAssemblyInstructionAssignmentIntFloat(list, f);          break;
        case INSTRUCTION_TYPE_ASSIGNMENT_FLOAT_INT:           generateAssemblyInstructionAssignmentFloatInt(list, f);          break;
        case INSTRUCTION_TYPE_ASSIGNMENT_FLOAT_FLOAT:         generateAssemblyInstructionAssignmentFloatFloat(list, f);        break;
        case INSTRUCTION_TYPE_ASSIGNMENT_BOOL_BOOL:           generateAssemblyInstructionAssignmentBoolBool(list, f);          break;
        case INSTRUCTION_TYPE_ADDITION_INT_INT:               generateAssemblyInstructionAdditionIntInt(list, f);              break;
        case INSTRUCTION_TYPE_ADDITION_INT_FLOAT:             generateAssemblyInstructionAdditionIntFloat(list, f);            break;
        case INSTRUCTION_TYPE_ADDITION_FLOAT_INT:             generateAssemblyInstructionAdditionFloatInt(list, f);            break;
        case INSTRUCTION_TYPE_ADDITION_FLOAT_FLOAT:           generateAssemblyInstructionAdditionFloatFloat(list, f);          break;
        case INSTRUCTION_TYPE_AND:                            generateAssemblyInstructionAnd(list, f);                         break;
        case INSTRUCTION_TYPE_OR:                             generateAssemblyInstructionOr(list, f);                          break;
        case INSTRUCTION_TYPE_ARGUMENT:                       generateAssemblyInstructionArgument(list, f);                    break;
        case INSTRUCTION_TYPE_CALL_METHOD:                    generateAssemblyInstructionCallMethod(list, f);                  break;           
        case INSTRUCTION_TYPE_RETURN:                         generateAssemblyInstructionReturn(list, f);                      break;
        case INSTRUCTION_TYPE_SUBTRACTION_INT_INT:            generateAssemblyInstructionSubtractionIntInt(list, f);           break;
        case INSTRUCTION_TYPE_SUBTRACTION_INT_FLOAT:          generateAssemblyInstructionSubtractionIntFloat(list, f);         break;
        case INSTRUCTION_TYPE_SUBTRACTION_FLOAT_INT:          generateAssemblyInstructionSubtractionFloatInt(list, f);         break;
        case INSTRUCTION_TYPE_SUBTRACTION_FLOAT_FLOAT:        generateAssemblyInstructionSubtractionFloatFloat(list, f);       break;
        case INSTRUCTION_TYPE_MULTIPLICATION_INT_INT:         generateAssemblyInstructionMultiplicationIntInt(list, f);        break;
        case INSTRUCTION_TYPE_MULTIPLICATION_INT_FLOAT:       generateAssemblyInstructionMultiplicationIntFloat(list, f);      break;
        case INSTRUCTION_TYPE_MULTIPLICATION_FLOAT_INT:       generateAssemblyInstructionMultiplicationFloatInt(list, f);      break;
        case INSTRUCTION_TYPE_MULTIPLICATION_FLOAT_FLOAT:     generateAssemblyInstructionMultiplicationFloatFloat(list, f);    break;
        case INSTRUCTION_TYPE_DIVISION_INT_INT:               generateAssemblyInstructionDivisionIntInt(list, f);              break;
        case INSTRUCTION_TYPE_DIVISION_INT_FLOAT:             generateAssemblyInstructionDivisionIntFloat(list, f);            break;
        case INSTRUCTION_TYPE_DIVISION_FLOAT_INT:             generateAssemblyInstructionDivisionFloatInt(list, f);            break;
        case INSTRUCTION_TYPE_DIVISION_FLOAT_FLOAT:           generateAssemblyInstructionDivisionFloatFloat(list, f);          break;
        case INSTRUCTION_TYPE_MOD_INT_INT:                    generateAssemblyInstructionModIntInt(list, f);                   break;
        case INSTRUCTION_TYPE_MOD_INT_FLOAT:                  generateAssemblyInstructionModIntFloat(list, f);                 break;
        case INSTRUCTION_TYPE_MOD_FLOAT_INT:                  generateAssemblyInstructionModFloatInt(list, f);                 break;
        case INSTRUCTION_TYPE_MOD_FLOAT_FLOAT:                generateAssemblyInstructionModFloatFloat(list, f);               break;
        case INSTRUCTION_TYPE_COMPARISON_SMALLER_INT_INT:     generateAssemblyInstructionComparisonSmallerIntInt(list, f);     break;
        case INSTRUCTION_TYPE_COMPARISON_SMALLER_INT_FLOAT:   generateAssemblyInstructionComparisonSmallerIntFloat(list, f);   break;
        case INSTRUCTION_TYPE_COMPARISON_SMALLER_FLOAT_INT:   generateAssemblyInstructionComparisonSmallerFloatInt(list, f);   break;
        case INSTRUCTION_TYPE_COMPARISON_SMALLER_FLOAT_FLOAT: generateAssemblyInstructionComparisonSmallerFloatFloat(list, f); break;
        case INSTRUCTION_TYPE_COMPARISON_GREATER_INT_INT:     generateAssemblyInstructionComparisonGreaterIntInt(list, f);     break;
        case INSTRUCTION_TYPE_COMPARISON_GREATER_INT_FLOAT:   generateAssemblyInstructionComparisonGreaterIntFloat(list, f);   break;
        case INSTRUCTION_TYPE_COMPARISON_GREATER_FLOAT_INT:   generateAssemblyInstructionComparisonGreaterFloatInt(list, f);   break;
        case INSTRUCTION_TYPE_COMPARISON_GREATER_FLOAT_FLOAT: generateAssemblyInstructionComparisonGreaterFloatFloat(list, f); break;
        case INSTRUCTION_TYPE_UNARY_MINUS_INT:                generateAssemblyInstructionUnaryMinusInt(list, f);               break;
        case INSTRUCTION_TYPE_UNARY_MINUS_FLOAT:              generateAssemblyInstructionUnaryMinusFloat(list, f);             break;
        case INSTRUCTION_TYPE_NEGATION:                       generateAssemblyInstructionNegation(list, f);                    break;
        case INSTRUCTION_TYPE_JMP_FALSE:                      generateAssemblyInstructionJmpFalse(list, f);                    break;
        case INSTRUCTION_TYPE_JMP:                            generateAssemblyInstructionJmp(list, f);                         break;
        case INSTRUCTION_TYPE_EQUAL:                          generateAssemblyInstructionEqual(list, f);                       break;
    }
}




void generateAssemblyInstructionGlobalVarDecl(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionGlobalVarDecl() not implemented yet")
}




void generateAssemblyInstructionBeginMethod(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionBeginMethod() not implemented yet")
}




void generateAssemblyInstructionEndMethod(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionEndMethod() not implemented yet")
}




void generateAssemblyInstructionLabel(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionLabel() not implemented yet")
}




void generateAssemblyInstructionAssignmentIntInt(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionAssignmentIntInt() not implemented yet")
}




void generateAssemblyInstructionAssignmentIntFloat(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionAssignmentIntFloat() not implemented yet")
}




void generateAssemblyInstructionAssignmentFloatInt(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionAssignmentFloatInt() not implemented yet")
}




void generateAssemblyInstructionAssignmentFloatFloat(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionAssignmentFloatFloat() not implemented yet")
}




void generateAssemblyInstructionAssignmentBoolBool(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionAssignmentBoolBool() not implemented yet")
}




void generateAssemblyInstructionAdditionIntInt(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionAdditionIntInt() not implemented yet")
}




void generateAssemblyInstructionAdditionIntFloat(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionAdditionIntFloat() not implemented yet")
}




void generateAssemblyInstructionAdditionFloatInt(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionAdditionFloatInt() not implemented yet")
}




void generateAssemblyInstructionAdditionFloatFloat(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionAdditionFloatFloat() not implemented yet")
}




void generateAssemblyInstructionAnd(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionAnd() not implemented yet")
}




void generateAssemblyInstructionOr(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionOr() not implemented yet")
}




void generateAssemblyInstructionArgument(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionArgument() not implemented yet")
}




void generateAssemblyInstructionCallMethod(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionCallMethod() not implemented yet")
}




void generateAssemblyInstructionReturn(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionReturn() not implemented yet")
}




void generateAssemblyInstructionSubtractionIntInt(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionSubtractionIntInt() not implemented yet")
}




void generateAssemblyInstructionSubtractionIntFloat(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionSubtractionIntFloat() not implemented yet")
}




void generateAssemblyInstructionSubtractionFloatInt(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionSubtractionFloatInt() not implemented yet")
}




void generateAssemblyInstructionSubtractionFloatFloat(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionSubtractionFloatFloat() not implemented yet")
}




void generateAssemblyInstructionMultiplicationIntInt(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionMutiplicationIntInt() not implemented yet")
}




void generateAssemblyInstructionMultiplicationIntFloat(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionMultiplicationIntFloat() not implemented yet")
}




void generateAssemblyInstructionMultiplicationFloatInt(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionMultiplicationFloatInt() not implemented yet")
}




void generateAssemblyInstructionMultiplicationFloatFloat(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionMultiplicationFloatFloat() not implemented yet")
}




void generateAssemblyInstructionDivisionIntInt(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionDivisionIntInt() not implemented yet")
}




void generateAssemblyInstructionDivisionIntFloat(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionDivisionIntFloat() not implemented yet")
}




void generateAssemblyInstructionDivisionFloatInt(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionDivisionFloatInt() not implemented yet")
}




void generateAssemblyInstructionDivisionFloatFloat(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionDivisionFloatFloat() not implemented yet")
}




void generateAssemblyInstructionModIntInt(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionModIntInt() not implemented yet")
}




void generateAssemblyInstructionModIntFloat(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionModIntFloat() not implemented yet")
}




void generateAssemblyInstructionModFloatInt(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionModFloatInt() not implemented yet")
}




void generateAssemblyInstructionModFloatFloat(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionModFloatFloat() not implemented yet")
}




void generateAssemblyInstructionComparisonSmallerIntInt(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionComparisonSmallerIntInt() not implemented yet")
}




void generateAssemblyInstructionComparisonSmallerIntFloat(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionComparisonSmallerIntFloat() not implemented yet")
}




void generateAssemblyInstructionComparisonSmallerFloatInt(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionComparisonSmallerFloatInt() not implemented yet")
}




void generateAssemblyInstructionComparisonSmallerFloatFloat(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionComparisonSmallerFloatFloat() not implemented yet")
}




void generateAssemblyInstructionComparisonGreaterIntInt(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionComparisonGreaterIntInt() not implemented yet")
}




void generateAssemblyInstructionComparisonGreaterIntFloat(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionComparisonGreaterIntFloat() not implemented yet")
}




void generateAssemblyInstructionComparisonGreaterFloatInt(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionComparisonGreaterFloatInt() not implemented yet")
}




void generateAssemblyInstructionComparisonGreaterFloatFloat(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionComparisonGreaterFloatFloat() not implemented yet")
}




void generateAssemblyInstructionUnaryMinusInt(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionUnaryMinusInt() not implemented yet")
}




void generateAssemblyInstructionUnaryMinusFloat(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionUnaryMinusFloat() not implemented yet")
}




void generateAssemblyInstructionNegation(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionNegation() not implemented yet")
}




void generateAssemblyInstructionJmpFalse(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionJmpFalse() not implemented yet")
}




void generateAssemblyInstructionJmp(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionJmp() not implemented yet")
}




void generateAssemblyInstructionEqual(Instruction *i, FILE *f) {
    TODO("generateAssemblyInstructionEqual() not implemented yet")
}
