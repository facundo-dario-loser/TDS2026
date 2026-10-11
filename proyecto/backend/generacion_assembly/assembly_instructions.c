#include "assembly_instructions.h"

void globl(FILE *f, char *name) {
    if (!name)
        ERROR_ASSEMBLY("name is null in globl()")
    fprintf(f, ".globl %s\n", name);
}

void methodLabel(FILE *f, char *name) {
    if (!name)
        ERROR_ASSEMBLY("name is null in methodLabel()")
    fprintf(f, "%s:\n", name);
}

void enter(FILE *f, int numberOfBytes) {
    fprintf(f, "\tenter $(8*%d), $0\n", numberOfBytes);
}
