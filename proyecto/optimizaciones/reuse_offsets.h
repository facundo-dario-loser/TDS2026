#ifndef REUSE_OFFSETS_H
#define REUSE_OFFSETS_H

#include "../tads/ast.h"

void setOffsetsInAstWithReuse(AstNode *root);
void setOffsetsInAstWithReuseAux(AstNode *node, int *currentOffset);

void setOffsetsNodeMethodDeclList(AstNode *node, int *currentOffset);
void setOffsetsNodeVarDecl(AstNode *node, int *currentOffset);
void setOffsetsNodeBlock(AstNode *node, int *currentOffset);
void setOffsetsNodeBlockElems(AstNode *node, int *currentOffset);
void setOffsetsNodeStatements(AstNode *node, int *currentOffset);
void setOffsetsNodeIfElse(AstNode *node, int *currentOffset);

void setOffsetsNodeBinaryOperator(AstNode *node, int *currentOffset);
void setOffsetsNodeUnaryOperator(AstNode *node, int *currentOffset);

#endif // REUSE_OFFSETS_H
