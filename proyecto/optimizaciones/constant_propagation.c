#include "constant_propagation.h"




void constantPropagation(AstNode *root) {
    if (!root) return;

    switch (root->type) {
        case AST_NODE_TYPE_P:                 constantPropagation(root->children1);            break;
        case AST_NODE_TYPE_GLOBAL_DECL_LIST:  constantPropagation(root->children2);            break;
        case AST_NODE_TYPE_VAR_DECL:                                                           break;
        case AST_NODE_TYPE_METHOD_DECL_LIST:  constantPropagationNodeMethodDeclList(root);     break;
        case AST_NODE_TYPE_METHOD_DECL:       constantPropagationNodeMethodDecl(root);         break;
        case AST_NODE_TYPE_LIST_ID:                                                            break;
        case AST_NODE_TYPE_PARAMS:                                                             break;
        case AST_NODE_TYPE_VOID:                                                               break;
        case AST_NODE_TYPE_BLOCK_ELEMS:        constantPropagation(root->children2);           break;
        case AST_NODE_TYPE_STATEMENTS:         constantPropagationNodeStatements(root);        break;
        case AST_NODE_TYPE_TYPE:                                                               break;
        case AST_NODE_TYPE_ASSIGNMENT:         constantPropagationNodeAssignment(root);        break;
        case AST_NODE_TYPE_METHOD_CALL:        constantPropagationNodeMethodCall(root);        break;
        case AST_NODE_TYPE_IF_ELSE:            constantPropagationNodeIfElse(root);            break;
        case AST_NODE_TYPE_WHILE:              constantPropagationNodeWhile(root);             break;
        case AST_NODE_TYPE_RETURN:             constantPropagationNodeReturn(root);            break;
        case AST_NODE_TYPE_LIST_EXPR:          constantPropagationNodeListExpr(root);          break;
        case AST_NODE_TYPE_INT_LITERAL:                                                        break;
        case AST_NODE_TYPE_FLOAT_LITERAL:                                                      break;
        case AST_NODE_TYPE_BOOL_LITERAL:                                                       break;
        case AST_NODE_TYPE_ADDITION:           constantPropagationNodeAddition(root);          break;
        case AST_NODE_TYPE_SUBTRACTION:        constantPropagationNodeSubtraction(root);       break;
        case AST_NODE_TYPE_MULTIPLICATION:     constantPropagationNodeMultiplication(root);    break;
        case AST_NODE_TYPE_DIVISION:           constantPropagationNodeDivision(root);          break;
        case AST_NODE_TYPE_MOD:                constantPropagationNodeMod(root);               break;
        case AST_NODE_TYPE_COMPARISON_SMALLER: constantPropagationNodeComparisonSmaller(root); break;
        case AST_NODE_TYPE_COMPARISON_GREATER: constantPropagationNodeComparisonGreater(root); break;
        case AST_NODE_TYPE_EQUAL:              constantPropagationNodeEqual(root);             break;
        case AST_NODE_TYPE_AND:                constantPropagationNodeAnd(root);               break;
        case AST_NODE_TYPE_OR:                 constantPropagationNodeOr(root);                break;
        case AST_NODE_TYPE_MINUS:              constantPropagationNodeMinus(root);             break;
        case AST_NODE_TYPE_NEGATION:           constantPropagationNodeNegation(root);          break;
        case AST_NODE_TYPE_EXTERN_METHOD_DECL:                                                 break;
    }
}




void constantPropagationNodeMethodDeclList(AstNode *node) {}




void constantPropagationNodeMethodDecl(AstNode *node) {}




void constantPropagationNodeStatements(AstNode *node) {}




void constantPropagationNodeAssignment(AstNode *node) {}




void constantPropagationNodeMethodCall(AstNode *node) {}




void constantPropagationNodeIfElse(AstNode *node) {}




void constantPropagationNodeWhile(AstNode *node) {}




void constantPropagationNodeReturn(AstNode *node) {}




void constantPropagationNodeListExpr(AstNode *node) {}




void constantPropagationNodeAddition(AstNode *node) {}




void constantPropagationNodeSubtraction(AstNode *node) {}




void constantPropagationNodeMultiplication(AstNode *node) {}




void constantPropagationNodeDivision(AstNode *node) {}




void constantPropagationNodeMod(AstNode *node) {}




void constantPropagationNodeComparisonSmaller(AstNode *node) {}




void constantPropagationNodeComparisonGreater(AstNode *node) {}




void constantPropagationNodeEqual(AstNode *node) {}




void constantPropagationNodeAnd(AstNode *node) {}




void constantPropagationNodeOr(AstNode *node) {}




void constantPropagationNodeMinus(AstNode *node) {}




void constantPropagationNodeNegation(AstNode *node) {}
