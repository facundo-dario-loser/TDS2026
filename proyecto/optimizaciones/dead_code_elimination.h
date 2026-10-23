#ifndef DEAD_CODE_ELIMINATION_H
#define DEAD_CODE_ELIMINATION_H

#include "../tads/ast.h"

void deadCodeElimination(AstNode **root);

void deadCodeEliminationNodeMethodDeclList(AstNode **node);
void deadCodeEliminationNodeStatements(AstNode **node);
bool deadCodeEliminationNodeIfElse(AstNode **node);
bool deadCodeEliminationNodeWhile(AstNode **node);

#endif // DEAD_CODE_ELIMINATION_H
