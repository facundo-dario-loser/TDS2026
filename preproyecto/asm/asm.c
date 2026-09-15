#include "asm.h"

// solo tenemos la funcion main y dentro var locales y temporales

void generarAsmADD(Instruction *list, FILE *f);
void generarAsmMultiplication(Instruction *list, FILE *f);
void generarAsmAnd(Instruction *list, FILE *f);
void generarAsmOr(Instruction *list, FILE *f);
void generarAsmAssigment(Instruction *list, FILE *f);
void generarAsmRet(Instruction *list, FILE *f);
void generarAsmBeginFunction(Instruction *list, FILE *f);
void generarAsmEndFunction(Instruction *list, FILE *f);

int getNumberOfParams(Symbol *funcSymbol);

int setOffsetsAndCountVars(Instruction *list) {
    // por ahora funciona bien asi porque tenemos 1 sola funcion
    Instruction *aux = list;

    int varCount = 0;
    int offsetCount = -8;

    while (aux) {
        if (aux->op1 && (aux->op1->flag == FLAG_VARIABLE) && !aux->op1->offsetSet) {
            aux->op1->offset    = offsetCount;
            offsetCount        -= 8;
            aux->op1->offsetSet = true;
            varCount++;
        }

        if (aux->op2 && (aux->op2->flag == FLAG_VARIABLE) && !aux->op2->offsetSet) {
            aux->op2->offset    = offsetCount;
            offsetCount        -= 8;
            aux->op2->offsetSet = true;
            varCount++;
        }

        if (aux->result && (aux->result->flag == FLAG_VARIABLE) && !aux->result->offsetSet) {
            aux->result->offset    = offsetCount;
            offsetCount           -= 8;
            aux->result->offsetSet = true;
            varCount++;
        }

        // porque la lista esta al revez
        aux = aux->prev;
    }

    return varCount;
}

void generarAsm(Instruction *list) {
    FILE *f = fopen("main.s", "w");
    fprintf(f, ".text\n");

    Instruction *aux = list;

    // la lista esta dada vuelta (seteamos aux para arrancar al final)
    while (aux->next) {
        aux = aux->next;
    }

    while (aux) {
        switch (aux->type) {
            case INSTRUCTION_ADD:            generarAsmADD(aux, f);            break;
            case INSTRUCTION_MULTIPLICATION: generarAsmMultiplication(aux, f); break;
            case INSTRUCTION_AND:            generarAsmAnd(aux, f);            break;
            case INSTRUCTION_OR:             generarAsmOr(aux, f);             break;
            case INSTRUCTION_ASSIGNMENT:     generarAsmAssigment(aux, f);      break;
            case INSTRUCTION_RET:            generarAsmRet(aux, f);            break;
            case INSTRUCTION_BEGIN_FUNCTION: generarAsmBeginFunction(aux, f);  break;
            case INSTRUCTION_END_FUNCTION:   generarAsmEndFunction(aux, f);    break;
        }

        // como tenemos solo a main, al encontrar el fin de la funcion termina el prog
        if (aux->type == INSTRUCTION_END_FUNCTION) break;
        aux = aux->prev;
    }

    fclose(f);
}

int getNumberOfParams(Symbol *funcSymbol) {
    int numberOfParams = 0;
    Symbol *aux        = funcSymbol->parametros;

    while (aux) {
        numberOfParams++;
        aux = aux->next;
    }

    return numberOfParams;
}

void generarAsmADD(Instruction *list, FILE *f) {
    // add (para sumar enteros de 64 bits)
    fprintf(f, "\t# ADD\n");

    if (list->op1->flag == FLAG_CONSTANTE && list->op2->flag == FLAG_CONSTANTE) {
        fprintf(f, "\tmov $%d, %%r10\n", list->op1->valor);
        fprintf(f, "\tadd $%d, %%r10\n", list->op2->valor);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", list->result->offset);
    }

    if (list->op1->flag == FLAG_CONSTANTE && list->op2->flag == FLAG_VARIABLE) {
        fprintf(f, "\tmov $%d, %%r10\n", list->op1->valor);
        fprintf(f, "\tadd %d(%%rbp), %%r10\n", list->op2->offset);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", list->result->offset);
    }
    
    if (list->op1->flag == FLAG_VARIABLE && list->op2->flag == FLAG_CONSTANTE) {
        fprintf(f, "\tmov $%d, %%r10\n", list->op2->valor);
        fprintf(f, "\tadd %d(%%rbp), %%r10\n", list->op1->offset);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", list->result->offset);
    }
    
    if (list->op1->flag == FLAG_VARIABLE && list->op2->flag == FLAG_VARIABLE) {
        fprintf(f, "\tmov %d(%%rbp), %%r10\n", list->op1->offset);
        fprintf(f, "\tadd %d(%%rbp), %%r10\n", list->op2->offset);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", list->result->offset);
    }

    fprintf(f, "\n");
}

void generarAsmMultiplication(Instruction *list, FILE *f) {
    // mull (para sumar enteros de 32 bits)
    fprintf(f, "\t# MULTIPLICATION\n");

    if (list->op1->flag == FLAG_CONSTANTE && list->op2->flag == FLAG_CONSTANTE) {
        fprintf(f, "\tmov $%d, %%r10\n", list->op1->valor);
        fprintf(f, "\tmul $%d, %%r10\n", list->op2->valor);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", list->result->offset);
    }

    if (list->op1->flag == FLAG_CONSTANTE && list->op2->flag == FLAG_VARIABLE) {
        fprintf(f, "\tmov $%d, %%r10\n", list->op1->valor);
        fprintf(f, "\tmul %d(%%rbp), %%r10\n", list->op2->offset);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", list->result->offset);
    }
    
    if (list->op1->flag == FLAG_VARIABLE && list->op2->flag == FLAG_CONSTANTE) {
        fprintf(f, "\tmov $%d, %%r10\n", list->op2->valor);
        fprintf(f, "\tmul %d(%%rbp), %%r10\n", list->op1->offset);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", list->result->offset);
    }
    
    if (list->op1->flag == FLAG_VARIABLE && list->op2->flag == FLAG_VARIABLE) {
        fprintf(f, "\tmov %d(%%rbp), %%r10\n", list->op1->offset);
        fprintf(f, "\tmul %d(%%rbp), %%r10\n", list->op2->offset);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", list->result->offset);
    }

    fprintf(f, "\n");
}

void generarAsmAnd(Instruction *list, FILE *f) {
    // andl (para sumar enteros de 32 bits)
    fprintf(f, "\t# AND\n");

    if (list->op1->flag == FLAG_CONSTANTE && list->op2->flag == FLAG_CONSTANTE) {
        fprintf(f, "\tmov $%d, %%r10\n", list->op1->valor);
        fprintf(f, "\tand $%d, %%r10\n", list->op2->valor);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", list->result->offset);
    }

    if (list->op1->flag == FLAG_CONSTANTE && list->op2->flag == FLAG_VARIABLE) {
        fprintf(f, "\tmov $%d, %%r10\n", list->op1->valor);
        fprintf(f, "\tand %d(%%rbp), %%r10\n", list->op2->offset);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", list->result->offset);
    }
    
    if (list->op1->flag == FLAG_VARIABLE && list->op2->flag == FLAG_CONSTANTE) {
        fprintf(f, "\tmov $%d, %%r10\n", list->op2->valor);
        fprintf(f, "\tand %d(%%rbp), %%r10\n", list->op1->offset);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", list->result->offset);
    }
    
    if (list->op1->flag == FLAG_VARIABLE && list->op2->flag == FLAG_VARIABLE) {
        fprintf(f, "\tmov %d(%%rbp), %%r10\n", list->op1->offset);
        fprintf(f, "\tand %d(%%rbp), %%r10\n", list->op2->offset);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", list->result->offset);
    }

    fprintf(f, "\n");
}

void generarAsmOr(Instruction *list, FILE *f) {
    // orl (para sumar enteros de 32 bits)
    fprintf(f, "\t# OR\n");

    if (list->op1->flag == FLAG_CONSTANTE && list->op2->flag == FLAG_CONSTANTE) {
        fprintf(f, "\tmov $%d, %%r10\n", list->op1->valor);
        fprintf(f, "\tor $%d, %%r10\n", list->op2->valor);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", list->result->offset);
    }

    if (list->op1->flag == FLAG_CONSTANTE && list->op2->flag == FLAG_VARIABLE) {
        fprintf(f, "\tmov $%d, %%r10\n", list->op1->valor);
        fprintf(f, "\tor %d(%%rbp), %%r10\n", list->op2->offset);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", list->result->offset);
    }
    
    if (list->op1->flag == FLAG_VARIABLE && list->op2->flag == FLAG_CONSTANTE) {
        fprintf(f, "\tmov $%d, %%r10\n", list->op2->valor);
        fprintf(f, "\tor %d(%%rbp), %%r10\n", list->op1->offset);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", list->result->offset);
    }
    
    if (list->op1->flag == FLAG_VARIABLE && list->op2->flag == FLAG_VARIABLE) {
        fprintf(f, "\tmov %d(%%rbp), %%r10\n", list->op1->offset);
        fprintf(f, "\tor %d(%%rbp), %%r10\n", list->op2->offset);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", list->result->offset);
    }

    fprintf(f, "\n");
}

void generarAsmAssigment(Instruction *list, FILE *f) {
    fprintf(f, "\t# ASSIGMENT\n");

    if (list->op1->flag == FLAG_VARIABLE) {
        fprintf(f, "\tmov %d(%%rbp), %%r10\n", list->op1->offset);
        fprintf(f, "\tmov %%r10, %d(%%rbp)\n", list->result->offset);
    } else if (list->op1->flag == FLAG_CONSTANTE) {
        // movq para enteros de 64 bits
        // sino el ensamblador no sabe con que tamano trabajar
        fprintf(f, "\tmovq $%d, %d(%%rbp)\n", list->op1->valor, list->result->offset);
    }

    fprintf(f, "\n");
}

void generarAsmRet(Instruction *list, FILE *f) {
    fprintf(f, "\t# RETURN\n");

    if (list->op1->flag == FLAG_CONSTANTE) {
        fprintf(f, "\tmov $%d, %%eax\n", list->op1->valor);
    } else if (list->op1->flag == FLAG_VARIABLE) {
        fprintf(f, "\tmov %d(%%rbp), %%eax\n", list->op1->offset);
    } else {
        // un return sin nada 'return ;' por las dudas
        fprintf(f, "\tmov $0, %%eax\n");
    }

    fprintf(f, "\n");
}

void generarAsmBeginFunction(Instruction *list, FILE *f) {
    // TODO: deberia guardar tanto lugar para: args + var locales + var temporales
    // 8 * cant (cada entrada del stack frame ocupa 8 bytes)
    // 1 quadword = 8 bytes
    // los params se pasan en registros y luego se guardan como variables locales
    int numberOfParams = getNumberOfParams(list->result);
    int numberOfVars   = setOffsetsAndCountVars(list);
    int total          = numberOfParams + numberOfVars;

    if (strcmp(list->result->nombre, "main") == 0) fprintf(f, ".globl main\n\n");
    
    fprintf(f, "%s:\n", list->result->nombre);
    fprintf(f, "\tenter $(8*%d), $0\n", total);

    fprintf(f, "\n");
}

void generarAsmEndFunction(Instruction *list, FILE *f) {
    // ???
    // aca deberia terminar la generacion de assembly
    // en main hay que setear el rax en 0 aunque no tenga tipo de retorno para indicar que termino todo ok
    fprintf(f, "\tleave\n");
    fprintf(f, "\tret\n\n");
}
