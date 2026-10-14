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
        if (op1->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            fprintf(f, "\tmov %d(%%rbp), %%r10\n", op1->offset);
            fprintf(f, "\tadd $%d, %%r10\n", op2->value.intValue);
            fprintf(f, "\tmov %%r10, %d(%%rbp)\n", result->offset);
        }

        // var(float) + const(float)
        if (op1->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            TODO("var(float) + const(float) in add() not implemented yet")
        }
    }
    
    // const + var
    if ((op1->type == SYMBOL_TYPE_CONSTANT) && (op2->type == SYMBOL_TYPE_VARIABLE)) {
        TODO("const + var in add() not implemented yet")
    }
    
    // const + const
    if ((op1->type == SYMBOL_TYPE_CONSTANT) && (op2->type == SYMBOL_TYPE_CONSTANT)) {
        TODO("const + const in add() not implemented yet")
    }
}




void returnFromMethod(FILE *f, Symbol *symbolReturned) {
    fprintf(f, "\tmov %d(%%rbp), rax\n", symbolReturned->offset);
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
