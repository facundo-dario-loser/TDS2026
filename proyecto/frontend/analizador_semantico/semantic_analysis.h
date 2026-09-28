#ifndef SEMANTIC_ANALYSIS_H
#define SEMANTIC_ANALYSIS_H

#include "../../utils/debug.h"
#include "../../tads/ast.h"
#include "../../tads/st.h"

void semanticAnalysis(AstNode *root);
void semanticAnalysisAux(AstNode *root, SymbolTable *st);

// funciones para analizar semanticamente cada tipo de nodo:
void analysisNodeP(AstNode *node, SymbolTable *st);
void analysisNodeGlobalDeclList(AstNode *node, SymbolTable *st);
void analysisNodeVarDecl(AstNode *node, SymbolTable *st);
void analysisNodeMethodDeclList(AstNode *node, SymbolTable *st);
void analysisNodeMethodDecl(AstNode *node, SymbolTable *st);
void analysisNodeListId(AstNode *node, SymbolTable *st);
void analysisNodeId(AstNode *node, SymbolTable *st);
void analysisNodeParams(AstNode *node, SymbolTable *st);
void analysisNodeVoid(AstNode *node, SymbolTable *st);
void analysisNodeParam(AstNode *node, SymbolTable *st);
void analysisNodeBlock(AstNode *node, SymbolTable *st);
void analysisNodeBlockElems(AstNode *node, SymbolTable *st);
void analysisNodeStatements(AstNode *node, SymbolTable *st);
void analysisNodeType(AstNode *node, SymbolTable *st);
void analysisNodeAssignment(AstNode *node, SymbolTable *st);
void analysisNodeMethodCall(AstNode *node, SymbolTable *st);
void analysisNodeIfElse(AstNode *node, SymbolTable *st);
void analysisNodeWhile(AstNode *node, SymbolTable *st);
void analysisNodeReturn(AstNode *node, SymbolTable *st);
void analysisNodeListExpr(AstNode *node, SymbolTable *st);
void analysisNodeIntLiteral(AstNode *node, SymbolTable *st);
void analysisNodeFloatLiteral(AstNode *node, SymbolTable *st);
void analysisNodeBoolLiteral(AstNode *node, SymbolTable *st);
void analysisNodeAddition(AstNode *node, SymbolTable *st);
void analysisNodeSubtraction(AstNode *node, SymbolTable *st);
void analysisNodeMultiplication(AstNode *node, SymbolTable *st);
void analysisNodeDivision(AstNode *node, SymbolTable *st);
void analysisNodeMod(AstNode *node, SymbolTable *st);
void analysisNodeComparisionSmaller(AstNode *node, SymbolTable *st);
void analysisNodeComparisionGreater(AstNode *node, SymbolTable *st);
void analysisNodeEqual(AstNode *node, SymbolTable *st);
void analysisNodeAnd(AstNode *node, SymbolTable *st);
void analysisNodeOr(AstNode *node, SymbolTable *st);
void analysisNodeMinus(AstNode *node, SymbolTable *st);
void analysisNodeNegation(AstNode *node, SymbolTable *st);

// funciones auxiliares
bool checkIfFunctionHasReturn(AstNode *node);                     // chequea que una funcion tenga return's en todas sus ramas
void getSymbolParamList(AstNode *node, Symbol **symbolParamList); // retorna una lista enlazada de simbolso que son los parametros de un metodo/funcion
void printMethodParamList(Symbol *methodSymbol);                  // printea la lista parametros de un metodo/funcion 
void setLiteralSymbolInAstNode(AstNode *nodeLiteral);             // crea un simbolo para un nodo de un literal (int, float o bool) y se lo asigna al nodo

SymbolSemanticType getSymbolSemanticTypeFromAstNodeDeclarationType(AstNodeDeclarationType declType); // retorna el tipo semantico del simbolo a partir del campo nodeDeclaration del nodo del ast

// funciones para analizar diferentes tipos de operadores binarios
void analysisArithmeticBinaryOperator(AstNode *arithBinOpNode, SymbolTable *st); // + - * / %
void analysisLogicalBinaryOperator(AstNode *logicalBinOpNode, SymbolTable *st);  // and, or
void analysisComparisonOperator(AstNode *comparisonOpNode, SymbolTable *st);     // <, >

#endif // SEMANTIC_ANALYSIS_H
