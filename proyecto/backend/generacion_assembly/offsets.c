#include "offsets.h"




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
                        PRINT_SYMBOL_OFFSET("symbol %s, offset: %d", param->name, param->offset)
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
                    PRINT_SYMBOL_OFFSET("symbol %s, offset: %d", i->result->name, i->result->offset)
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
                    PRINT_SYMBOL_OFFSET("symbol %s, offset: %d", i->op1->name, i->op1->offset)
                }

                i = i->next;
            } break;

            case INSTRUCTION_TYPE_JMP_TRUE: {
                // solo el temporal del op1 se le podria asignar un offset
                if (i->op1 && (i->op1->type != SYMBOL_TYPE_CONSTANT) && !i->op1->offsetSet) {
                    i->op1->offset    = currentOffset;
                    currentOffset    -= 8;
                    i->op1->offsetSet = true;
                    numberOfLocalVariables++;
                    PRINT_SYMBOL_OFFSET("symbol %s, offset: %d", i->op1->name, i->op1->offset)
                }

                i = i->next;
            } break;

            case INSTRUCTION_TYPE_JMP: {
                i = i->next; // no hace falta setear ningun offset
            } break;

            default: {
                if (i->op1 && (i->op1->type == SYMBOL_TYPE_VARIABLE) && (i->op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) && !i->op1->offsetSet) {
                    i->op1->offset    = currentOffset;
                    currentOffset    -= 8;
                    i->op1->offsetSet = true;
                    numberOfLocalVariables++;
                    PRINT_SYMBOL_OFFSET("symbol %s, offset: %d", i->op1->name, i->op1->offset)
                }

                if (i->op2 && (i->op2->type == SYMBOL_TYPE_VARIABLE) && (i->op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) && !i->op2->offsetSet) {
                    i->op2->offset    = currentOffset;
                    currentOffset    -= 8;
                    i->op2->offsetSet = true;
                    numberOfLocalVariables++;
                    PRINT_SYMBOL_OFFSET("symbol %s, offset: %d", i->op2->name, i->op2->offset)
                }

                if (i->result && (i->result->type == SYMBOL_TYPE_VARIABLE) && (i->result->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) && !i->result->offsetSet) {
                    i->result->offset    = currentOffset;
                    currentOffset       -= 8;
                    i->result->offsetSet = true;
                    numberOfLocalVariables++;
                    PRINT_SYMBOL_OFFSET("symbol %s, offset: %d", i->result->name, i->result->offset)
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

            case INSTRUCTION_TYPE_JMP_TRUE: {
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
