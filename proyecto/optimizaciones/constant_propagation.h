#ifndef CONSTANT_PROPAGATION_H
#define CONSTANT_PROPAGATION_H

#include "../tads/ast.h"

void constantPropagation(AstNode *root);

void constantPropagationNodeMethodDeclList(AstNode *node);
void constantPropagationNodeMethodDecl(AstNode *node);
void constantPropagationNodeStatements(AstNode *node);
void constantPropagationNodeAssignment(AstNode *node);
void constantPropagationNodeMethodCall(AstNode *node);
void constantPropagationNodeIfElse(AstNode *node);
void constantPropagationNodeWhile(AstNode *node);
void constantPropagationNodeReturn(AstNode *node);
void constantPropagationNodeListExpr(AstNode *node);
void constantPropagationNodeAddition(AstNode *node);
void constantPropagationNodeSubtraction(AstNode *node);
void constantPropagationNodeMultiplication(AstNode *node);
void constantPropagationNodeDivision(AstNode *node);
void constantPropagationNodeMod(AstNode *node);
void constantPropagationNodeComparisonSmaller(AstNode *node);
void constantPropagationNodeComparisonGreater(AstNode *node);
void constantPropagationNodeEqual(AstNode *node);
void constantPropagationNodeAnd(AstNode *node);
void constantPropagationNodeOr(AstNode *node);
void constantPropagationNodeMinus(AstNode *node);
void constantPropagationNodeNegation(AstNode *node);

// void constantPropagationNode(AstNode *node);

#endif // CONSTANT_PROPAGATION_H