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
void movZeroRax(FILE *f); // para indicar que el programa termino correctamente
void newLine(FILE *f);
void add(FILE *f, Symbol *op1, Symbol *op2, Symbol *result);
void returnFromMethod(FILE *f, Symbol *symbolReturned);
void label(FILE *f, char *str);
void jmp(FILE *f, char *label);
void push(FILE *f, Symbol *src);
void call(FILE *f, char *methodName);
void movFromRaxToTemporal(FILE *f, Symbol *temp);
void cmp(FILE *f, Symbol *op1, Symbol *op2, Symbol *result, ComparisonType compType);
void jmpToLabelIfFalse(FILE *f, Symbol *cond, char *label);
void jmpToLabelIfTrue(FILE *f, Symbol *cond, char *label);
void imul(FILE *f, Symbol *op1, Symbol *op2, Symbol *result);
void neg(FILE *f, Symbol *op, Symbol *result);
void negationBoolean(FILE *f, Symbol *op, Symbol *result);
void idiv(FILE *f, Symbol *op1, Symbol *op2, Symbol *result);
void sub(FILE *f, Symbol *op1, Symbol *op2, Symbol *result);
void mod(FILE *f, Symbol *op1, Symbol *op2, Symbol *result);
void dataSegment(FILE *f);
void globalVarDecl(FILE *f, Symbol *globalVarSymbol);
void text(FILE *f);

// funciones auxiliares
void          saveAllArguments(Symbol *methodSymbol, FILE *f);                                       // salva todos los argumentos pasados dentro de un metodo
char        * getRegisterForArgument(int numberOfArgument);                                          // mapea un numero entre 1 y 6 a un registro (para pasar argumentos a metodos o salvarlos dentro del mismo)
void          passArgumentToMethodInRegister(FILE *f, Symbol *argumentSymbol, int numberOfArgument); // pasa el argumento dado al metodo a travez de un registro
Instruction * passArgumentsToMethodInStack(FILE *f, Instruction *argumentInstruction);               // pushea el resto de los argumentos (si hay mas de 6) en el stack
void          popArgumentsFromStackAfterMethodCall(FILE *f, Symbol *methodSymbol);                   // popea todos los argumentos pasados en el stack a un metodo

#endif // ASSEMBLY_INSTRUCTIONS_H
