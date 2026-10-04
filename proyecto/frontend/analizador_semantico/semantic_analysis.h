#ifndef SEMANTIC_ANALYSIS_H
#define SEMANTIC_ANALYSIS_H

#include "../../utils/debug.h"
#include "../../tads/ast.h"
#include "../../tads/st.h"

void semanticAnalysis(AstNode *root);
void semanticAnalysisAux(AstNode *root, SymbolTable *st, int *tempCount);

// funciones para analizar semanticamente cada tipo de nodo:
void analysisNodeP(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeGlobalDeclList(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeVarDecl(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeMethodDeclList(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeMethodDecl(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeListId(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeId(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeParams(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeVoid(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeParam(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeBlock(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeBlockElems(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeStatements(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeType(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeAssignment(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeMethodCall(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeIfElse(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeWhile(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeReturn(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeListExpr(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeIntLiteral(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeFloatLiteral(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeBoolLiteral(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeAddition(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeSubtraction(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeMultiplication(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeDivision(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeMod(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeComparisonSmaller(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeComparisonGreater(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeEqual(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeAnd(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeOr(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeMinus(AstNode *node, SymbolTable *st, int *tempCount);
void analysisNodeNegation(AstNode *node, SymbolTable *st, int *tempCount);

// funciones auxiliares
bool checkIfFunctionHasReturn(AstNode *node);                                                        // chequea que una funcion tenga return's en todas sus ramas
void getSymbolParamList(AstNode *node, Symbol **symbolParamList);                                    // retorna una lista enlazada de simbolso que son los parametros de un metodo/funcion
void getSymbolParamListAux(AstNode *node, Symbol **symbolParamList, Symbol **tail);                  // funcion auxiliar que guarda el puntero a la cola de la lista de params
void setLiteralSymbolInAstNode(AstNode *nodeLiteral);                                                // crea un simbolo para un nodo de un literal (int, float o bool) y se lo asigna al nodo
SymbolSemanticType getSymbolSemanticTypeFromAstNodeDeclarationType(AstNodeDeclarationType declType); // retorna el tipo semantico del simbolo a partir del campo nodeDeclaration del nodo del ast

// funciones para analizar diferentes tipos de operadores binarios
void analysisArithmeticBinaryOperator(AstNode *arithBinOpNode, SymbolTable *st, int *tempCount); // + - * / %
void analysisLogicalBinaryOperator(AstNode *logicalBinOpNode, SymbolTable *st, int *tempCount);  // and, or
void analysisComparisonOperator(AstNode *comparisonOpNode, SymbolTable *st, int *tempCount);     // <, >

#endif // SEMANTIC_ANALYSIS_H
