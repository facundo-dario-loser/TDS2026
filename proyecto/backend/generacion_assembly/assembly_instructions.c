#include "assembly_instructions.h"




void comment(FILE *f, char *string) {
    if (!comment) ERROR_ASSEMBLY("string in NULL in comment()")
    fprintf(f, "\t# %s\n", string);
}




void globl(FILE *f, char *name) {
    if (!name) ERROR_ASSEMBLY("name is null in globl()")
    fprintf(f, ".globl %s\n", name);
}




void methodLabel(FILE *f, char *name) {
    if (!name) ERROR_ASSEMBLY("name is null in methodLabel()")
    fprintf(f, "%s:\n", name);
}




void enter(FILE *f, int numberOfBytes) {
    fprintf(f, "\tenter $(8*%d), $0\n", numberOfBytes);
}




void mov(FILE *f, Symbol *src, Symbol *dst) {
    if (!src) ERROR_ASSEMBLY("src is NULL in mov()")
    if (!dst) ERROR_ASSEMBLY("dst is NULL in mov()")

    if ((src->type == SYMBOL_TYPE_VARIABLE) && (src->variableType == SYMBOL_VARIABLE_TYPE_LOCAL)) {
        if (dst->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", src->offset);
                fprintf(f, "\tmov %%r10, %d(%%rbp)\n", dst->offset);
            }

            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("dst(local float variable) = src(local float variable) in mov() not implemented yet")
            }

            // hago los mismo que en mov IntInt
            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN)) { 
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", src->offset);
                fprintf(f, "\tmov %%r10, %d(%%rbp)\n", dst->offset);
            }
        }

        if (dst->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", src->offset);
                fprintf(f, "\tmov %%r10, %s(%%rip)\n", dst->name);
            }

            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("dst(global float variable) = src(local float variable) in mov() not implemented yet")
            }

            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN)) {
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", src->offset);
                fprintf(f, "\tmov %%r10, %s(%%rip)\n", dst->name);
            }
        }
    }

    if ((src->type == SYMBOL_TYPE_VARIABLE) && (src->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL)) {
        if (dst->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%r10\n", src->name);
                fprintf(f, "\tmov %%r10, %d(%%rbp)\n", dst->offset);
            }

            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("dst(local float variable) = dst(global float variable) in mov() not implemented yet")
            }

            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN)) {
                fprintf(f, "\tmov %s(%%rip), %%r10\n", src->name);
                fprintf(f, "\tmov %%r10, %d(%%rbp)\n", dst->offset);
            }
        }

        if (dst->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%r10\n", src->name);
                fprintf(f, "\tmov %%r10, %s(%%rip)\n", dst->name);
            }

            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("dst(global float variable) = dst(global float variable) in mov() not implemented yet")
            }

            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN)) {
                fprintf(f, "\tmov %s(%%rip), %%r10\n", src->name);
                fprintf(f, "\tmov %%r10, %s(%%rip)\n", dst->name);
            }
        }
    }

    if (src->type == SYMBOL_TYPE_CONSTANT) {
        if (dst->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov $%d, %%r10\n", src->value.intValue);
                fprintf(f, "\tmov %%r10, %d(%%rbp)\n", dst->offset);
            }

            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("mov float_const, dst not implemented yet in mov()")
            }

            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN)) {
                int booleanConstantValue = src->value.booleanValue ? 1 : 0;
                fprintf(f, "\tmov $%d, %%r10\n", booleanConstantValue);
                fprintf(f, "\tmov %%r10, %d(%%rbp)\n", dst->offset);
            }
        }

        if (dst->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov $%d, %%r10\n", src->value.intValue);
                fprintf(f, "\tmov %%r10, %s(%%rip)\n", dst->name);
            }

            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("mov float_const, dst not implemented yet in mov()")
            }

            if ((src->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) && (dst->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN)) {
                int booleanConstantValue = src->value.booleanValue ? 1 : 0;
                fprintf(f, "\tmov $%d, %%r10\n", booleanConstantValue);
                fprintf(f, "\tmov %%r10, %s(%%rip)\n", dst->name);
            }
        }
    }
}




void leave(FILE *f) {
    fprintf(f, "\tleave\n");
}




void ret(FILE *f) {
    fprintf(f, "\tret\n");
}




void movZeroEax(FILE *f) {
    fprintf(f, "\tmov $0, %%rax\n");
}




void newLine(FILE *f) {
    fprintf(f, "\n");
}




void add(FILE *f, Symbol *op1, Symbol *op2, Symbol *result) {
    if (!op1)    ERROR_ASSEMBLY("op1 is NULL in add()")
    if (!op2)    ERROR_ASSEMBLY("op2 is NULL in add()")
    if (!result) ERROR_ASSEMBLY("result is NULL in add()")

    if ((op1->type == SYMBOL_TYPE_VARIABLE) && (op2->type == SYMBOL_TYPE_VARIABLE)) {
        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL)) {
            if (op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT && op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op1->offset);
                fprintf(f, "\tadd %d(%%rbp), %%r10\n", op2->offset);
                fprintf(f, "\tmov %%r10, %d(%%rbp)\n", result->offset);
            }

            if (op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT && op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
                TODO("local var(float) + local var(float) in add() not implemented yet")
            }
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op1->offset);
                fprintf(f, "\tadd %s(%%rip), %%r10\n", op2->name);
                fprintf(f, "\tmov %%r10, %d(%%rbp)\n", result->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("local var(float) + global var(float) in add() not implemented yet")
            }
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%r10\n", op1->name);
                fprintf(f, "\tadd %d(%%rbp), %%r10\n", op2->offset);
                fprintf(f, "\tmov %%r10, %d(%%rbp)\n", result->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("global var(float) + local var(float) in add() not implemented yet")
            }
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%r10\n", op1->name);
                fprintf(f, "\tadd %s(%%rip), %%r10\n", op2->name);
                fprintf(f, "\tmov %%r10, %d(%%rbp)\n", result->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("global var(float) + global var(float) in add() not implemented yet")
            }
        }
    }
    
    if ((op1->type == SYMBOL_TYPE_VARIABLE) && (op2->type == SYMBOL_TYPE_CONSTANT)) {
        if (op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op1->offset);
                fprintf(f, "\tadd $%d, %%r10\n", op2->value.intValue);
                fprintf(f, "\tmov %%r10, %d(%%rbp)\n", result->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("local var(float) + const(float) in add() not implemented yet")
            }
        }

        if (op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%r10\n", op1->name);
                fprintf(f, "\tadd $%d, %%r10\n", op2->value.intValue);
                fprintf(f, "\tmov %%r10, %d(%%rbp)\n", result->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("global var(float) + const(float) in add() not implemented yet")
            }
        }
    }
    
    if ((op1->type == SYMBOL_TYPE_CONSTANT) && (op2->type == SYMBOL_TYPE_VARIABLE)) {
        if (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov $%d, %%r10\n", op1->value.intValue);
                fprintf(f, "\tadd %d(%%rbp), %%r10\n", op2->offset);
                fprintf(f, "\tmov %%r10, %d(%%rbp)\n", result->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("cons(float) + local var(float) in add() not implemented yet")
            }
        }

        if (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov $%d, %%r10\n", op1->value.intValue);
                fprintf(f, "\tadd %s(%%rip), %%r10\n", op2->name);
                fprintf(f, "\tmov %%r10, %d(%%rbp)\n", result->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("const(float) + global var(float) in add() not implemented yet")
            }
        }
    }
    
    if ((op1->type == SYMBOL_TYPE_CONSTANT) && (op2->type == SYMBOL_TYPE_CONSTANT)) {
        if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
            fprintf(f, "\tmov $%d, %%r10\n", op1->value.intValue);
            fprintf(f, "\tadd $%d, %%r10\n", op2->value.intValue);
            fprintf(f, "\tmov %%r10, %d(%%rbp)\n", result->offset);
        }

        if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
            TODO("const(float) + const(float) in add() not implemented yet")
        }
    }
}




void returnFromMethod(FILE *f, Symbol *symbolReturned) {
    if (!symbolReturned) ERROR_ASSEMBLY("symbolReturned is NULL in returnFromMethod()")

    if (symbolReturned->type == SYMBOL_TYPE_VARIABLE) {
        if (symbolReturned->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if (symbolReturned->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
                fprintf(f, "\tmov %d(%%rbp), %%rax\n", symbolReturned->offset);
            }

            if (symbolReturned->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
                TODO("return float local variable in returnFromMethod() not implemented yet")
            }

            if (symbolReturned->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
                fprintf(f, "\tmov %d(%%rbp), %%rax\n", symbolReturned->offset);
            }
        }

        if (symbolReturned->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if (symbolReturned->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
                fprintf(f, "\tmov %s(%%rip), %%rax\n", symbolReturned->name);
            }

            if (symbolReturned->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
                TODO("return float global variable in returnFromMethod() not implemented yet")
            }

            if (symbolReturned->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
                fprintf(f, "\tmov %s(%%rip), %%rax\n", symbolReturned->name);
            }
        }
    }

    if (symbolReturned->type == SYMBOL_TYPE_CONSTANT) {
        if (symbolReturned->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            fprintf(f, "\tmov $%d, %%rax\n", symbolReturned->value.intValue);
        }

        if (symbolReturned->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            TODO("return float constant in returnFromMethod() not implemented yet")
        }

        if (symbolReturned->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
            int booleanValue = symbolReturned->value.booleanValue ? 1 : 0;
            fprintf(f, "\tmov $%d, %%rax\n", booleanValue);
        }
    }
}




void label(FILE *f, char *str) {
    if (!str) ERROR_ASSEMBLY("str is NULL in label()")
    fprintf(f, ".%s:\n", str);
}




void jmp(FILE *f, char *label) {
    if (!label) ERROR_ASSEMBLY("label is NULL in jmp()")
    fprintf(f, "\tjmp .%s\n", label);
}




void passArgumentToMethodInRegister(FILE *f, Symbol *argumentSymbol, int numberOfArgument) {
    if (!argumentSymbol)      ERROR_ASSEMBLY("argumentSymbol is NULL in passArgumentToMethod()")
    if (numberOfArgument > 6) ERROR_ASSEMBLY("numberOfArgument >= 6 in passArgumentToMethod()")

    char *reg = getRegisterForArgument(numberOfArgument);
    
    if (argumentSymbol->type == SYMBOL_TYPE_VARIABLE) {
        if (argumentSymbol->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if (argumentSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
                fprintf(f, "\tmov %d(%%rbp), %%%s\n", argumentSymbol->offset, reg);
            }

            if (argumentSymbol->type == SYMBOL_SEMANTIC_TYPE_FLOAT) {
                TODO("argument symbol type local variable float in passArgumentToMethodInRegister() not implemented yet")
            }

            if (argumentSymbol->type == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
                fprintf(f, "\tmov %d(%%rbp), %%%s\n", argumentSymbol->offset, reg);
            }
        }

        if (argumentSymbol->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if (argumentSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
                fprintf(f, "\tmov %s(%%rip), %%%s\n", argumentSymbol->name, reg);
            }

            if (argumentSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
                TODO("argument symbol type global variable float in passArgumentToMethodInRegister() not implemented yet")
            }

            if (argumentSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
                fprintf(f, "\tmov %s(%%rip), %%%s\n", argumentSymbol->name, reg);
            }
        }
    }

    if (argumentSymbol->type == SYMBOL_TYPE_CONSTANT) {
        if (argumentSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            fprintf(f, "\tmov $%d, %%%s\n", argumentSymbol->value.intValue, reg);
        }

        if (argumentSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            TODO("argumentSymbol type constant float in passArgumentToMethodInRegister() not implemented yet")
        }

        if (argumentSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
            int booleanValue = argumentSymbol->value.booleanValue ? 1 : 0;
            fprintf(f, "\tmov $%d, %%%s\n", booleanValue, reg);
        }
    }
}




Instruction * passArgumentsToMethodInStack(FILE *f, Instruction *argumentInstruction) {
    if (!argumentInstruction) ERROR_ASSEMBLY("argumentInstruction is NULL in passArgumentsToMethodInStack()")

    Instruction *aux = argumentInstruction;
    
    while (aux->next->type == INSTRUCTION_TYPE_ARGUMENT) aux = aux->next;

    // guarda la proxima instruccion que se deberia procesar luego pushear todos los argumentos
    Instruction *nextInstructionToProcess = aux->next;

    // se pushean los argumentos en orden inverso
    while ((aux->prev->type == INSTRUCTION_TYPE_ARGUMENT) && (aux->prev->op1->value.intValue >= 6)) {
        newLine(f);
        comment(f, "PassingArgumentForMethodCall");
        push(f, aux->result);
        aux = aux->prev;
    }

    return nextInstructionToProcess;
}




void push(FILE *f, Symbol *src) {
    if (!src) ERROR_ASSEMBLY("src is NULL in push()")
    
    if (src->type == SYMBOL_TYPE_VARIABLE) {
        if (src->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if (src->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", src->offset);
            } 

            if (src->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
                TODO("push float local variable in push() not implemented yet")
            }

            if (src->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", src->offset);
            }
        }

        if (src->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if (src->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
                fprintf(f, "\tmov %s(%%rip), %%r10\n", src->name);
            }

            if (src->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
                TODO("push float global variable in push() not implemented yet")
            }

            if (src->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
                fprintf(f, "\tmov %s(%%rip), %%r10\n", src->name);
            }
        }
    }

    if (src->type == SYMBOL_TYPE_CONSTANT) {
        if (src->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            fprintf(f, "\tmov $%d, %%r10\n", src->value.intValue);
        }

        if (src->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            TODO("push float constant in push() not implemented yet")
        }

        if (src->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
            int booleanValue = src->value.booleanValue ? 1 : 0;
            fprintf(f, "\tmov $%d, %%r10\n", booleanValue);
        }
    }

    fprintf(f, "\tpush %%r10\n");
}




void call(FILE *f, char *methodName) {
    if (!methodName) ERROR_ASSEMBLY("methodName is NULL in call()")
    fprintf(f, "\tcall %s\n", methodName);
}




void movFromRaxToTemporal(FILE *f, Symbol *temp) {
    if (!temp) ERROR_ASSEMBLY("temp is NULL in movFromRaxToTemporal()")
    fprintf(f, "\tmov %%rax, %d(%%rbp)\n", temp->offset);
}




// Nota: esto solo funciona teniendo en cuenta que no estoy manipulando floats (que usan otros registros llamados xmm...)
//       y por ende en una llamada se puede llegar a usar mas de 6 registros para pasar los argumentos
void popArgumentsFromStackAfterMethodCall(FILE *f, Symbol *methodSymbol) {
    if (!methodSymbol) ERROR_ASSEMBLY("methodSymbol is NULL in popArgumentsFromStackAfterMethodCall()")

    if (methodSymbol->numberOfParameters > 6) {
        newLine(f);
        comment(f, "PopingArgumentsFromStack");
        int numberOfArgumentsInStack = methodSymbol->numberOfParameters - 6;

        while (numberOfArgumentsInStack > 0) {
            fprintf(f, "\tpop %%r10\n");
            numberOfArgumentsInStack--;
        }
    }
}




// calcula: op1 - op2. Luego se chequea de acuerdo al resultado: es op1, mayor, menor o igual que op2
void cmp(FILE *f, Symbol *op1, Symbol *op2, Symbol *result, ComparisonType compType) {
    if (!op1)    ERROR_ASSEMBLY("op1 is NULL in cmp()")
    if (!op2)    ERROR_ASSEMBLY("op2 is NULL in cmp()")
    if (!result) ERROR_ASSEMBLY("result is NULL in cmp()")

    if ((op1->type == SYMBOL_TYPE_VARIABLE) && (op2->type == SYMBOL_TYPE_VARIABLE)) {
        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op1->offset);
                fprintf(f, "\tmov %d(%%rbp), %%r11\n", op2->offset);
            }   

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("comparison between float(local variable) and float(local variable) in cmp() not implemented yet")
            }
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL)) {
            fprintf(f, "\tmov %d(%%rbp), %%r10\n", op1->offset);
            fprintf(f, "\tmov %s(%%rip), %%r11\n", op2->name);
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL)) {
            fprintf(f, "\tmov %s(%%rip), %%r10\n", op1->name);
            fprintf(f, "\tmov %d(%%rbp), %%r11\n", op2->offset);
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL)) {
            fprintf(f, "\tmov %s(%%rip), %%r10\n", op1->name);
            fprintf(f, "\tmov %s(%%rip), %%r11\n", op2->name);
        }
    }
    
    if ((op1->type == SYMBOL_TYPE_VARIABLE) && (op2->type == SYMBOL_TYPE_CONSTANT)) {
        if (op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op1->offset);
                fprintf(f, "\tmov $%d, %%r11\n", op2->value.intValue);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("comparison between float(local variable) and float(constant) in cmp() not implemented yet")
            }
        }

        if (op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%r10\n", op1->name);
                fprintf(f, "\tmov $%d, %%r11\n", op2->value.intValue);
            }

            if ((op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("comparison between float(global variable) and float(constant) in cmp() not implemented yet")
            }
        }
    }

    if ((op1->type == SYMBOL_TYPE_CONSTANT) && (op2->type == SYMBOL_TYPE_VARIABLE)) {
        if (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov $%d, %%r10\n", op1->value.intValue);
                fprintf(f, "\tmov %d(%%rbp), %%r11\n", op2->offset);       
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("comparison between float(constant) and float(local variable) in cmp() not implemented yet")
            }
        }

        if (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov $%d, %%r10\n", op1->value.intValue);
                fprintf(f, "\tmov %s(%%rip), %%r11\n", op2->name);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("comparison between float(constant) and float(global variable) in cmp() not implemented yet")
            }
        }
    }

    if ((op1->type == SYMBOL_TYPE_CONSTANT) && (op2->type == SYMBOL_TYPE_CONSTANT)) {
        if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
            fprintf(f, "\tmov $%d, %%r10\n", op1->value.intValue);
            fprintf(f, "\tmov $%d, %%r11\n", op2->value.intValue);
        }   

        if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
            TODO("comparison between float(constant) and float(constant) in cmp() not implemented yet")
        }
    }

    fprintf(f, "\tcmp %%r11, %%r10\n");
    fprintf(f, "\tmov $0, %%r11\n");
    fprintf(f, "\tmov $1, %%r10\n");
    
    switch (compType) {
        case COMPARISON_TYPE_GREATER: {
            fprintf(f, "\tcmovg %%r10, %%r11\n"); // r10 > r11?
        } break;
        
        case COMPARISON_TYPE_SMALLER: {
            fprintf(f, "\tcmovl %%r10, %%r11\n"); // r10 < r11?
        } break;
        
        case COMPARISON_TYPE_EQUAL: {
            fprintf(f, "\tcmove %%r10, %%r11\n"); // r10 == r11?
        }
    }

    fprintf(f, "\tmov %%r11, %d(%%rbp)\n", result->offset);
}




void jmpToLabelIfFalse(FILE *f, Symbol *cond, char *label) {
    if (!label) ERROR_ASSEMBLY("label is NULL in jmpToLabelIfFalse()")

    if (cond->type == SYMBOL_TYPE_VARIABLE) {
        if (cond->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            fprintf(f, "\tmov %d(%%rbp), %%r10\n", cond->offset);
        }
        
        if (cond->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            fprintf(f, "\tmov %s(%%rip), %%r10\n", cond->name);
        }
    }

    if (cond->type == SYMBOL_TYPE_CONSTANT) {
        int booleanValue = cond->value.booleanValue ? 1 : 0;
        fprintf(f, "\tmov $%d, %%r10\n", booleanValue);
    }

    fprintf(f, "\tmov $0, %%r11\n");
    fprintf(f, "\tcmp %%r10, %%r11\n");
    fprintf(f, "\tje .%s\n", label);
}




void jmpToLabelIfTrue(FILE *f, Symbol *cond, char *label) {
    if (!label) ERROR_ASSEMBLY("label is NULL in jmpToLabelIfTrue()")

    if (cond->type == SYMBOL_TYPE_VARIABLE) {
        if (cond->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            fprintf(f, "\tmov %d(%%rbp), %%r10\n", cond->offset);
        }
        
        if (cond->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            fprintf(f, "\tmov %s(%%rip), %%r10\n", cond->name);
        }
    }

    if (cond->type == SYMBOL_TYPE_CONSTANT) {
        int booleanValue = cond->value.booleanValue ? 1 : 0;
        fprintf(f, "\tmov $%d, %%r10\n", booleanValue);
    }

    fprintf(f, "\tmov $1, %%r11\n");
    fprintf(f, "\tcmp %%r10, %%r11\n");
    fprintf(f, "\tje .%s\n", label);
}




void imul(FILE *f, Symbol *op1, Symbol *op2, Symbol *result) {
    if (!op1)    ERROR_ASSEMBLY("op1 is NULL in imul()")
    if (!op2)    ERROR_ASSEMBLY("op2 is NULL in imul()")
    if (!result) ERROR_ASSEMBLY("result is NULL in imul()")

    if ((op1->type == SYMBOL_TYPE_VARIABLE) && (op2->type == SYMBOL_TYPE_VARIABLE)) {
        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op1->offset);
                fprintf(f, "\tmov %d(%%rbp), %%r11\n", op2->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float local variable) * op2(float local variable) in imul() not implemented yet")
            }
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op1->offset);
                fprintf(f, "\tmov %s(%%rip), %%r11\n", op2->name);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float local variable) * op2(float global variable) in imul() not implemented yet")
            }
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%r10\n", op1->name);
                fprintf(f, "\tmov %d(%%rbp), %%r11\n", op2->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float global variable) * op2(float local variable) in imul() not implemented yet")
            }
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%r10\n", op1->name);
                fprintf(f, "\tmov %s(%%rip), %%r11\n", op2->name);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float global variable) * op2(float global variable) in imul() not implemented yet")
            }
        }
    }

    if ((op1->type == SYMBOL_TYPE_VARIABLE) && (op2->type == SYMBOL_TYPE_CONSTANT)) {
        if (op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op1->offset);
                fprintf(f, "\tmov $%d, %%r11\n", op2->value.intValue);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float local variable) * op2(float constant) in imul() not implemented yet")
            }
        }

        if (op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%r10\n", op1->name);
                fprintf(f, "\tmov $%d, %%r11\n", op2->value.intValue);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float global variable) * op2(constant) in imul() not implemented yet")
            }
        }
    }

    if ((op1->type == SYMBOL_TYPE_CONSTANT) && (op2->type == SYMBOL_TYPE_VARIABLE)) {
        if (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov $%d, %%r10\n", op1->value.intValue);
                fprintf(f, "\tmov %d(%%rbp), %%r11\n", op2->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float constant) * op2(float local variable) in imul() not implemented yet")
            }
        }

        if (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov $%d, %%r10\n", op1->value.intValue);
                fprintf(f, "\tmov %s(%%rip), %%r11\n", op2->name);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(constant) * op2(float global variable) in imul() not implemented yet")
            }
        }
    }

    if ((op1->type == SYMBOL_TYPE_CONSTANT) && (op2->type == SYMBOL_TYPE_CONSTANT)) {
        if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
            fprintf(f, "\tmov $%d, %%r10\n", op1->value.intValue);
            fprintf(f, "\tmov $%d, %%r11\n", op2->value.intValue);
        }

        if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
            TODO("op1(float constant) * op2(float constant) in imul() not implemented yet")
        }
    }

    fprintf(f, "\timul %%r10, %%r11\n");
    fprintf(f, "\tmov %%r11, %d(%%rbp)\n", result->offset);
}




void neg(FILE *f, Symbol *op, Symbol *result) {
    if (!op)     ERROR_ASSEMBLY("op is NULL in neg()")
    if (!result) ERROR_ASSEMBLY("result is NULL in neg()")

    if (op->type == SYMBOL_TYPE_VARIABLE) {
        if (op->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if (op->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op->offset);
            }

            if (op->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
                TODO("-op(float local variable) in neg() not implemented yet")
            }
        }

        if (op->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if (op->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
                fprintf(f, "\tmov %s(%%rip), %%r10\n", op->name);
            }

            if (op->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
                TODO("-op(float global variable) in neg() not implemented yet")
            }
        }
    }

    if (op->type == SYMBOL_TYPE_CONSTANT) {
        if (op->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            fprintf(f, "\tmov $%d, %%r10\n", op->value.intValue);
        }

        if (op->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            TODO("-op(float constant) in neg() not implemented yet")
        }
    }

    fprintf(f, "\tneg %%r10\n");
    fprintf(f, "\tmov %%r10, %d(%%rbp)\n", result->offset);
}




void negationBoolean(FILE *f, Symbol *op, Symbol *result) {
    if (!op)     ERROR_ASSEMBLY("op1 is NULL in xor()")
    if (!result) ERROR_ASSEMBLY("result is NULL in xor()")

    if (op->type == SYMBOL_TYPE_VARIABLE) {
        if (op->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            fprintf(f, "\tmov %d(%%rbp), %%r10\n", op->offset);
        }

        if (op->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            fprintf(f, "\tmov %s(%%rip), %%r10\n", op->name);
        }
    }

    if (op->type == SYMBOL_TYPE_CONSTANT) {
        int opBooleanValue = op->value.booleanValue ? 1 : 0;
        fprintf(f, "\tmov $%d, %%r10\n", opBooleanValue);
    }

    fprintf(f, "\txor $1, %%r10\n");
    fprintf(f, "\tmov %%r10, %d(%%rbp)\n", result->offset);
}



// result = op1 / op2
void idiv(FILE *f, Symbol *op1, Symbol *op2, Symbol *result) {
    if (!op1)    ERROR_ASSEMBLY("op1 is NULL in idiv()")
    if (!op2)    ERROR_ASSEMBLY("op2 is NULL in idiv()")
    if (!result) ERROR_ASSEMBLY("result is NULL in idiv()")

    if ((op1->type == SYMBOL_TYPE_VARIABLE) && (op2->type == SYMBOL_TYPE_VARIABLE)) {
        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%rax\n", op1->offset);
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op2->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float local variable) / op2(float local variable) in idiv() not implemented yet")
            }
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%rax\n", op1->offset);
                fprintf(f, "\tmov %s(%%rip), %%r10\n", op2->name);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float local variable) / op2(float global variable) in idiv() not implemented yet")
            }
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%rax\n", op1->name);
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op2->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float global variable) / op2(float local variable) in idiv() not implemented yet")
            }
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%rax\n", op1->name);
                fprintf(f, "\tmov %s(%%rip), %%r10\n", op2->name);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float global variable) / op2(float global variable) in idiv() not implemented yet")
            }
        }
    }

    if ((op1->type == SYMBOL_TYPE_VARIABLE) && (op2->type == SYMBOL_TYPE_CONSTANT)) {
        if (op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%rax\n", op1->offset);
                fprintf(f, "\tmov $%d, %%r10\n", op2->value.intValue);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float local variable) / op2(float constant) in idiv() not implemented yet")
            }
        }

        if (op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%rax\n", op1->name);
                fprintf(f, "\tmov $%d, %%r10\n", op2->value.intValue);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float global variable) / op2(constant) in idiv() not implemented yet")
            }
        }
    }

    if ((op1->type == SYMBOL_TYPE_CONSTANT) && (op2->type == SYMBOL_TYPE_VARIABLE)) {
        if (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov $%d, %%r10\n", op1->value.intValue);
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op2->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float constant) / op2(float local variable) in idiv() not implemented yet")
            }
        }

        if (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov $%d, %%rax\n", op1->value.intValue);
                fprintf(f, "\tmov %s(%%rip), %%r10\n", op2->name);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(constant) / op2(float global variable) in idiv() not implemented yet")
            }
        }
    }

    if ((op1->type == SYMBOL_TYPE_CONSTANT) && (op2->type == SYMBOL_TYPE_CONSTANT)) {
        if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
            fprintf(f, "\tmov $%d, %%r10\n", op1->value.intValue);
            fprintf(f, "\tmov $%d, %%r10\n", op2->value.intValue);
        }

        if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
            TODO("op1(float constant) / op2(float constant) in idiv() not implemented yet")
        }
    }

    fprintf(f, "\tcqto # extend rax sign to rdx\n");
    fprintf(f, "\tidiv %%r10\n");
    fprintf(f, "\tmov %%rax, %d(%%rbp) # save the quotient\n", result->offset);
}




void sub(FILE *f, Symbol *op1, Symbol *op2, Symbol *result) {
    if (!op1)    ERROR_ASSEMBLY("op1 is NULL in sub()")
    if (!op2)    ERROR_ASSEMBLY("op2 is NULL in sub()")
    if (!result) ERROR_ASSEMBLY("result is NULL in sub()")

    if ((op1->type == SYMBOL_TYPE_VARIABLE) && (op2->type == SYMBOL_TYPE_VARIABLE)) {
        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op1->offset);
                fprintf(f, "\tsub %d(%%rbp), %%r10\n", op2->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float local variable) - op2(float local variable) in sub() not implemented yet")
            }
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op1->offset);
                fprintf(f, "\tsub %s(%%rip), %%r10\n", op2->name);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float local variable) - op2(float global variable) in sub() not implemented yet")
            }
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%r10\n", op1->name);
                fprintf(f, "\tsub %d(%%rbp), %%r10\n", op2->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float global variable) - op2(float local variable) in sub() not implemented yet")
            }
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%r10\n", op1->name);
                fprintf(f, "\tsub %s(%%rip), %%r10\n", op2->name);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float global variable) - op2(float global variable) in sub() not implemented yet")
            }
        }
    }

    if ((op1->type == SYMBOL_TYPE_VARIABLE) && (op2->type == SYMBOL_TYPE_CONSTANT)) {
        if (op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op1->offset);
                fprintf(f, "\tsub $%d, %%r10\n", op2->value.intValue);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float variable) - op2(float constant) in sub() not implemented yet")
            }
        }

        if (op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%r10\n", op1->name);
                fprintf(f, "\tsub $%d, %%r10\n", op2->value.intValue);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float global variable) - op2(float constant) in sub() not implemented yet")
            }
        }
    }

    if ((op1->type == SYMBOL_TYPE_CONSTANT) && (op2->type == SYMBOL_TYPE_VARIABLE)) {
        if (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov $%d, %%r10\n", op1->value.intValue);
                fprintf(f, "\tsub %d(%%rbp), %%r10\n", op2->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float constant) - op2(float local variable) in sub() not implemented yet")
            }
        }

        if (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov $%d, %%r10\n", op1->value.intValue);
                fprintf(f, "\tsub %s(%%rip), %%r10\n", op2->name);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(constant) - op2(float global variable) in sub() not implemented yet")
            }
        }
    }

    if ((op1->type == SYMBOL_TYPE_CONSTANT) && (op2->type == SYMBOL_TYPE_CONSTANT)) {
        if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
            fprintf(f, "\tmov $%d, %%r10\n", op1->value.intValue);
            fprintf(f, "\tsub $%d, %%r10\n", op2->value.intValue);
        }

        if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
            TODO("op1(float constant) - op2(float constant) in sub() not implemented yet")
        }
    }

    fprintf(f, "\tmov %%r10, %d(%%rbp)\n", result->offset);
}




// igual a la division pero en lugar de quedarme con lo que tiene el rax(cociente),
// me quedo con lo que tiene el rdx(resto)
void mod(FILE *f, Symbol *op1, Symbol *op2, Symbol *result) {
    if (!op1)    ERROR_ASSEMBLY("op1 is NULL in mod()")
    if (!op2)    ERROR_ASSEMBLY("op2 is NULL in mod()")
    if (!result) ERROR_ASSEMBLY("result is NULL in mod()")

    if ((op1->type == SYMBOL_TYPE_VARIABLE) && (op2->type == SYMBOL_TYPE_VARIABLE)) {
        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%rax\n", op1->offset);
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op2->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float local variable) / op2(float local variable) in mod() not implemented yet")
            }
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%rax\n", op1->offset);
                fprintf(f, "\tmov %s(%%rip), %%r10\n", op2->name);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float local variable) / op2(float global variable) in mod() not implemented yet")
            }
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%rax\n", op1->name);
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op2->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float global variable) / op2(float local variable) in mod() not implemented yet")
            }
        }

        if ((op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) && (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL)) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%rax\n", op1->name);
                fprintf(f, "\tmov %s(%%rip), %%r10\n", op2->name);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float global variable) / op2(float global variable) in mod() not implemented yet")
            }
        }
    }

    if ((op1->type == SYMBOL_TYPE_VARIABLE) && (op2->type == SYMBOL_TYPE_CONSTANT)) {
        if (op1->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %d(%%rbp), %%rax\n", op1->offset);
                fprintf(f, "\tmov $%d, %%r10\n", op2->value.intValue);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float local variable) / op2(float constant) in mod() not implemented yet")
            }
        }

        if (op1->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov %s(%%rip), %%rax\n", op1->name);
                fprintf(f, "\tmov $%d, %%r10\n", op2->value.intValue);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float global variable) / op2(constant) in mod() not implemented yet")
            }
        }
    }

    if ((op1->type == SYMBOL_TYPE_CONSTANT) && (op2->type == SYMBOL_TYPE_VARIABLE)) {
        if (op2->variableType == SYMBOL_VARIABLE_TYPE_LOCAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov $%d, %%r10\n", op1->value.intValue);
                fprintf(f, "\tmov %d(%%rbp), %%r10\n", op2->offset);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(float constant) / op2(float local variable) in mod() not implemented yet")
            }
        }

        if (op2->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL) {
            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                fprintf(f, "\tmov $%d, %%rax\n", op1->value.intValue);
                fprintf(f, "\tmov %s(%%rip), %%r10\n", op2->name);
            }

            if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                TODO("op1(constant) / op2(float global variable) in mod() not implemented yet")
            }
        }
    }

    if ((op1->type == SYMBOL_TYPE_CONSTANT) && (op2->type == SYMBOL_TYPE_CONSTANT)) {
        if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
            fprintf(f, "\tmov $%d, %%r10\n", op1->value.intValue);
            fprintf(f, "\tmov $%d, %%r10\n", op2->value.intValue);
        }

        if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
            TODO("op1(float constant) / op2(float constant) in mod() not implemented yet")
        }
    }

    fprintf(f, "\tcqto # extend rax sign to rdx\n");
    fprintf(f, "\tidiv %%r10\n");
    fprintf(f, "\tmov %%rdx, %d(%%rbp) # save the remainder\n", result->offset);
}




void dataSegment(FILE *f) {
    fprintf(f, ".data\n");
}




void globalVarDecl(FILE *f, Symbol *globalVarSymbol) {
    if (!globalVarSymbol) ERROR_ASSEMBLY("globalVarSymbol is NULL in globalVarDecl()")
    
    if ((globalVarSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) || (globalVarSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN)) {
        fprintf(f, ".globl %s\n", globalVarSymbol->name);
        fprintf(f, "%s: .quad 0\n", globalVarSymbol->name);
    } else {
        TODO("global float variables in globalVarDecl() not implemented yet")
    }
}




void saveAllArguments(Symbol *methodSymbol, FILE *f) {
    if (!methodSymbol) ERROR_ASSEMBLY("method symbol is NULL in saveAllArguments()")
    
    // si no tiene parametros, entonces no se le paso ningun argumento
    if (!methodSymbol->parameters) return;
    
    comment(f, "SaveAllArguments");

    Symbol *param        = methodSymbol->parameters;
    int numberOfArgument = 1;

    while (param) {
        if (numberOfArgument <= 6) {
            char *reg = getRegisterForArgument(numberOfArgument);
            fprintf(f, "\tmov %%%s, %d(%%rbp)\n", reg, param->offset);
        } else {
            int numberOfStackArgument = numberOfArgument - 6;
            int argumentOffset = 8*numberOfStackArgument + 8;
            fprintf(f, "\tmov %d(%%rbp), %%r10\n", argumentOffset);
            fprintf(f, "\tmov %%r10, %d(%%rbp)\n", param->offset);
        }

        numberOfArgument++;
        param = param->next;
    }
}




char * getRegisterForArgument(int numberOfArgument) {
    switch (numberOfArgument) {
        case 1:  return "rdi";
        case 2:  return "rsi";
        case 3:  return "rdx";
        case 4:  return "rcx";
        case 5:  return "r8";
        case 6:  return "r9";
        default: ERROR_ASSEMBLY("numberOfArgument cannot be mapped to a register in getRegisterForArgument()");
    }
}
