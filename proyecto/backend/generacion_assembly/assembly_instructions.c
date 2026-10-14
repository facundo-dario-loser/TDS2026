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
        fprintf(f, "\tmov %d(%%rbp), %%r10\n", src->offset);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", dst->offset);
    }

    if ((src->type == SYMBOL_TYPE_VARIABLE) && (src->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL)) {
        TODO("global variable case in mov() not implemented yet")
    }

    if (src->type == SYMBOL_TYPE_CONSTANT) {
        if (src->semanticType == SYMBOL_SEMANTIC_TYPE_INT)
            fprintf(f, "\tmov, $%d, %%r10\n", src->value.intValue);
            fprintf(f, "\tmov %%r10, %d(%%rbp)\n", dst->offset);

        if (src->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)
            TODO("mov float_const, dst not implemented yet in mov()")

        if (src->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN)
            TODO("mov boolean_const, dst not implemented yet in mov()")
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
    if (!op1) ERROR_ASSEMBLY("op1 is NULL in add()")
    if (!op2) ERROR_ASSEMBLY("op2 is NULL in add()")
    if (!result) ERROR_ASSEMBLY("result is NULL in add()")

    // var + var
    if ((op1->type == SYMBOL_TYPE_VARIABLE) && (op2->type == SYMBOL_TYPE_VARIABLE)) {
        // var(int) + var(int)
        if (op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT && op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            fprintf(f, "\tmov %d(%%rbp), %%r10\n", op1->offset);
            fprintf(f, "\tadd %d(%%rbp), %%r10\n", op2->offset);
            fprintf(f, "\tmov %%r10, %d(%%rbp)\n", result->offset);
        }

        // var(float) + var(float)
        if (op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT && op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            TODO("var(float) + var(float) in add() not implemented yet")
        }
    }
    
    // var + const
    if ((op1->type == SYMBOL_TYPE_VARIABLE) && (op2->type == SYMBOL_TYPE_CONSTANT)) {
        // var(int) + const(int)
        if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
            fprintf(f, "\tmov %d(%%rbp), %%r10\n", op1->offset);
            fprintf(f, "\tadd $%d, %%r10\n", op2->value.intValue);
            fprintf(f, "\tmov %%r10, %d(%%rbp)\n", result->offset);
        }

        // var(float) + const(float)
        if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
            TODO("var(float) + const(float) in add() not implemented yet")
        }
    }
    
    // const + var
    if ((op1->type == SYMBOL_TYPE_CONSTANT) && (op2->type == SYMBOL_TYPE_VARIABLE)) {
        if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
            TODO("cons(int) + var(int) in add() not implemented yet")
        }

        if ((op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (op2->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
            TODO("cons(float) + var(float) in add() not implemented yet")
        }
    }
    
    // const + const
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
    fprintf(f, "\tmov %d(%%rbp), %%rax\n", symbolReturned->offset);
}




void label(FILE *f, char *str) {
    if (!str) ERROR_ASSEMBLY("str is NULL in label()")
    fprintf(f, "%s:\n", str);
}




void jmp(FILE *f, char *label) {
    if (!label) ERROR_ASSEMBLY("label is NULL in jmp()")
    fprintf(f, "\tjmp %s\n", label);
}




void passArgumentToMethodInRegister(FILE *f, Symbol *argumentSymbol, int numberOfArgument) {
    if (!argumentSymbol)      ERROR_ASSEMBLY("argumentSymbol is NULL in passArgumentToMethod()")
    if (numberOfArgument > 6) ERROR_ASSEMBLY("numberOfArgument >= 6 in passArgumentToMethod()")

    char *reg = getRegisterForArgument(numberOfArgument);
    
    if (argumentSymbol->type == SYMBOL_TYPE_VARIABLE) {
        if (argumentSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            fprintf(f, "\tmov %d(%%rbp), %%%s\n", argumentSymbol->offset, reg);
        }

        if (argumentSymbol->type == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            TODO("argument symbol type variable float in passArgumentToMethodInRegister() not implemented yet")
        }

        if (argumentSymbol->type == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
            TODO("argument symbol type variable boolean in passArgumentToMethodInRegister() not implemented yet")
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
            TODO("argumentSymbol type constant boolean in passArgumentToMethodInRegister() not implemented yet")
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
        push(f, aux->result);
        aux = aux->prev;
    }

    return nextInstructionToProcess;
}




void push(FILE *f, Symbol *src) {
    if (!src) ERROR_ASSEMBLY("src is NULL in push()")
    
    if (src->type == SYMBOL_TYPE_VARIABLE) {
        if (src->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            // TODO: si es int, boolean, float
            fprintf(f, "\tmov %d(%%rbp), %%r10\n", src->offset);
            fprintf(f, "\tpush %%r10\n");
        } else {
            TODO("src is not int not implemented yet in push()")
        }
    } else {
        TODO("src is is constant not implemented yet in push()")
    }
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
//       y por ende en una llamda se puede llegar a usar mas de 6 registros para pasar los argumentos
void popArgumentsFromStackAfterMethodCall(FILE *f, Symbol *methodSymbol) {
    if (!methodSymbol) ERROR_ASSEMBLY("methodSymbol is NULL in popArgumentsFromStackAfterMethodCall()")

    if (methodSymbol->numberOfParameters > 6) {
        comment(f, "PopingArgumentsFromStack");
        int numberOfArgumentsInStack = methodSymbol->numberOfParameters - 6;

        while (numberOfArgumentsInStack > 0) {
            fprintf(f, "\tpop %%r10\n");
            numberOfArgumentsInStack--;
        }
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
            TODO("save numberOfArgument >= 7 in saveAllArguments() not implemented yet");
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
