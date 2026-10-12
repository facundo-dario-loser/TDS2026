#ifndef ASSEMBLY_INSTRUCTIONS_H
#define ASSEMBLY_INSTRUCTIONS_H

#include <stdio.h>
#include "../../utils/debug.h"

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

#endif // ASSEMBLY_INSTRUCTIONS_H
