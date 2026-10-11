#ifndef ASSEMBLY_INSTRUCTIONS_H
#define ASSEMBLY_INSTRUCTIONS_H

#include <stdio.h>
#include "../../utils/debug.h"

void globl(FILE *f, char *name);
void methodLabel(FILE *f, char *name);
void enter(FILE *f, int numberOfBytes);

#endif // ASSEMBLY_INSTRUCTIONS_H