#include "ast.h"

AstNode * newAstNode(AstNodeConfig *config) {
    AstNode *node = (AstNode*)malloc(sizeof(AstNode));

    if (!node) ERROR_AST("couldn't allocate memory for new node");

    node->type            = config->type;
    node->declarationType = config->declarationType;

    if (config->type == AST_NODE_TYPE_ID) {
        node->value.strValue = strdup(config->value.strValue);
    } else {
        node->value = config->value;
    }

    node->children1       = config->children1;
    node->children2       = config->children2;
    node->children3       = config->children3;
    node->children4       = config->children4;
    node->symbol          = NULL; // los simbolos los creo en el analisis semantico
    node->isFunctionBlock = false;
    node->line            = config->line;

    return node;
}

void freeAst(AstNode *root) {
    if (root) {
        AstNodeType nodeType = root->type;

        freeAst(root->children1);
        freeAst(root->children2);
        freeAst(root->children3);
        freeAst(root->children4);

        bool nodeIsNotLiteral = (root->type != AST_NODE_TYPE_INT_LITERAL)   &&
                                (root->type != AST_NODE_TYPE_FLOAT_LITERAL) &&
                                (root->type != AST_NODE_TYPE_BOOL_LITERAL);

        // el problema es que en un literal como el campo 'value' es una union entonces strValue no es NULL, pero tendria basura
        if (root->value.strValue && nodeIsNotLiteral) free(root->value.strValue);

        if (root->symbol) {
            root->symbol->referenceCount--;
            if (root->symbol->referenceCount == 0) freeSymbol(root->symbol);
        }

        free(root);
        DEBUG_AST("%s freed", getAstNodeTypeString(nodeType))
    }
}

char * getAstNodeTypeString(AstNodeType nodeType) {
    switch (nodeType) {
        case AST_NODE_TYPE_P:                  return "node P";
        case AST_NODE_TYPE_GLOBAL_DECL_LIST:   return "node GlobalDeclList";
        case AST_NODE_TYPE_VAR_DECL:           return "node varDecl";
        case AST_NODE_TYPE_METHOD_DECL_LIST:   return "node MethodDeclList";
        case AST_NODE_TYPE_METHOD_DECL:        return "node MethodDecl";
        case AST_NODE_TYPE_LIST_ID:            return "node ListId";
        case AST_NODE_TYPE_ID:                 return "node Id";
        case AST_NODE_TYPE_PARAMS:             return "node Params";
        case AST_NODE_TYPE_VOID:               return "node Void";
        case AST_NODE_TYPE_PARAM:              return "node Param";
        case AST_NODE_TYPE_BLOCK:              return "node Block";
        case AST_NODE_TYPE_BLOCK_ELEMS:        return "node BlockElems";
        case AST_NODE_TYPE_STATEMENTS:         return "node Statements";
        case AST_NODE_TYPE_TYPE:               return "node Type";
        case AST_NODE_TYPE_ASSIGNMENT:         return "node Assignment";
        case AST_NODE_TYPE_METHOD_CALL:        return "node MethodCall";
        case AST_NODE_TYPE_IF_ELSE:            return "node IfElse";
        case AST_NODE_TYPE_WHILE:              return "node While";
        case AST_NODE_TYPE_RETURN:             return "node Return";
        case AST_NODE_TYPE_LIST_EXPR:          return "node ListExpr";
        case AST_NODE_TYPE_INT_LITERAL:        return "node IntLiteral";
        case AST_NODE_TYPE_FLOAT_LITERAL:      return "node FloatLiteral";
        case AST_NODE_TYPE_BOOL_LITERAL:       return "node BoolLiteral";
        case AST_NODE_TYPE_ADDITION:           return "node Addition";
        case AST_NODE_TYPE_SUBTRACTION:        return "node Subtraction";
        case AST_NODE_TYPE_MULTIPLICATION:     return "node Multiplication"; 
        case AST_NODE_TYPE_DIVISION:           return "node Division";
        case AST_NODE_TYPE_MOD:                return "node Mod";
        case AST_NODE_TYPE_COMPARISON_SMALLER: return "node ComparisonSmaller";
        case AST_NODE_TYPE_COMPARISON_GREATER: return "node ComparisonGreater";
        case AST_NODE_TYPE_EQUAL:              return "node Equal";
        case AST_NODE_TYPE_AND:                return "node And";
        case AST_NODE_TYPE_OR:                 return "node Or";
        case AST_NODE_TYPE_MINUS:              return "node Minus";
        case AST_NODE_TYPE_NEGATION:           return "node Negation";
        default:                               return "node ?";
    }
}
