#include <stdio.h>
#include <stdint.h>

// en el lenguaje ctds todas las variables ocupan 64 bits

void printInt(int64_t n) {
    printf("%ld\n", (long)n);
}

void printBoolean(int64_t n) {
    printf("%s\n", n ? "true" : "false");
}
