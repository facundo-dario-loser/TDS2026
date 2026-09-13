#ifndef ASM_H
#define ASM_H

#include "../pseudo_asm/ir_asm.h"

// setea el offset a todas las var locales y temporales y retorna la cant de var locales + temporales
// TODO: intentar hacerlo en otra etapa para evitar volver a recorrer la lista
int setOffsetsAndCountVars(Instruction *list);

// solo tenemos la seccion de texto por que esta todo adentro de main

// crea un archivo llamado main.asm con el codigo assembly (para ensamblar con gcc)
void generarAsm(Instruction *list);

#endif
