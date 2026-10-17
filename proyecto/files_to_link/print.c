#include <stdio.h>
#include <stdint.h>

// en el lenguaje ctds todas las variables ocupan 64 bits, por eso
// estas funciones toman un entero con signo de 64 bits

// para llamar a printInt en assembly:
// mov param %rdi
// mov $0, %rax   // hay que limpiar el rax si o si (para indicar que no se estan usando floats)
// call printInt

void printInt(int64_t n) {
    printf("%ld\n", (long)n);
}

void printBoolean(int64_t n) {
    printf("%s\n", n ? "true" : "false");
}
