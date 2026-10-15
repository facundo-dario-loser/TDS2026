#ifndef ASSEMBLY_INSTRUCTIONS_H
#define ASSEMBLY_INSTRUCTIONS_H

#include <stdio.h>
#include "../../frontend/codigo_intermedio/intermediate_code.h"
#include "../../utils/debug.h"

typedef enum ComparisonType {
    COMPARISON_TYPE_GREATER, // op1 > op2?  in cmp
    COMPARISON_TYPE_SMALLER, // op1 < op2?  in cmp
    COMPARISON_TYPE_EQUAL,   // op1 == op2? in cmp
} ComparisonType;

void comment(FILE *f, char *string);
void globl(FILE *f, char *name);
void methodLabel(FILE *f, char *name);
void enter(FILE *f, int numberOfBytes);
void mov(FILE *f, Symbol *src, Symbol *dst);
void leave(FILE *f);
void ret(FILE *f);
void movZeroEax(FILE *f); // para indicar que el programa termino correctamente
void newLine(FILE *f);
void add(FILE *f, Symbol *op1, Symbol *op2, Symbol *result);
void returnFromMethod(FILE *f, Symbol *symbolReturned);
void label(FILE *f, char *str);
void jmp(FILE *f, char *label);
void push(FILE *f, Symbol *src);
void call(FILE *f, char *methodName);
void movFromRaxToTemporal(FILE *f, Symbol *temp);
void and(FILE *f, Symbol *op1, Symbol *op2, Symbol *result);
void or(FILE *f, Symbol *op1, Symbol *op2, Symbol *result);
void cmp(FILE *f, Symbol *op1, Symbol *op2, Symbol *result, ComparisonType compType);
void jmpToLabelIfFalse(FILE *f, Symbol *cond, char *label);
void imul(FILE *f, Symbol *op1, Symbol *op2, Symbol *result);
void neg(FILE *f, Symbol *op, Symbol *result);
void negationBoolean(FILE *f, Symbol *op, Symbol *result);
void idiv(FILE *f, Symbol *op1, Symbol *op2, Symbol *result);
void sub(FILE *f, Symbol *op1, Symbol *op2, Symbol *result);
void mod(FILE *f, Symbol *op1, Symbol *op2, Symbol *result);
void dataSegment(FILE *f);
void globalVarDecl(FILE *f, Symbol *globalVarSymbol);

// funciones auxiliares
void          saveAllArguments(Symbol *methodSymbol, FILE *f);
char        * getRegisterForArgument(int numberOfArgument); // dado el numero de argumento retorna el registro en el cual se debe guardar o que ay esta guardado
void          passArgumentToMethodInRegister(FILE *f, Symbol *argumentSymbol, int numberOfArgument);
Instruction * passArgumentsToMethodInStack(FILE *f, Instruction *argumentInstruction); // pushea el resto de los argumentos (si hay mas de 6) en el stack
void          popArgumentsFromStackAfterMethodCall(FILE *f, Symbol *methodSymbol);

#endif // ASSEMBLY_INSTRUCTIONS_H
