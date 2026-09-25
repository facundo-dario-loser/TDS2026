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

    node->children1 = config->children1;
    node->children2 = config->children2;
    node->children3 = config->children3;
    node->children4 = config->children4;
    node->symbol    = NULL; // los simbolos los creo en el analisis semantico
    node->line      = config->line;

    return node;
}

void freeAst(AstNode *root) {
        if (root) {
        freeAst(root->children1);
        freeAst(root->children2);
        freeAst(root->children3);
        freeAst(root->children4);

        if (root->value.strValue) free(root->value.strValue);

        if (root->symbol) {
            root->symbol->referenceCount--;
            if (root->symbol->referenceCount == 0) freeSymbol(root->symbol);
        }

        free(root);
    }
}
