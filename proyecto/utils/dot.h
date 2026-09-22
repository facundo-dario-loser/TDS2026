#ifndef DOT_H
#define DOT_H

// dot.h: provee funciones para generar archivos .dot a partir de un ast para poder graficarlo

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../tads/ast.h"

void getNodeLabel(AstNode *node, char label[256]);
void astToDotAux(AstNode *root, FILE *f);
void astToDot(AstNode *root);

#endif // DOT_H