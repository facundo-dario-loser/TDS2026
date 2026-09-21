#include "ast.h"

AstNode * newAstNode(AstNodeConfig *config) {
    AstNode *node = (AstNode*)malloc(sizeof(AstNode));

    if (!node) ERROR_AST("couldn't allocate memory for new node");

    node->type = config->type;

    if (config->type == AST_NODE_TYPE_ID) {
        node->value.strValue = strdup(config->value.strValue);
    } else {
        node->value = config->value;
    }

    node->left      = config->left;
    node->middle    = config->middle;
    node->right     = config->right;
    node->symbol    = NULL;           // los simbolos los creo en el analisis semantico
    node->hasReturn = false;
    node->line      = config->line;

    return node;
}

void freeAst(AstNode *root) {
        if (root) {
        freeAst(root->left);
        freeAst(root->middle);
        freeAst(root->right);

        if (root->value.strValue) free(root->value.strValue);

        if (root->symbol) {
            root->symbol->referenceCount--;
            if (root->symbol->referenceCount == 0) freeSymbol(root->symbol);
        }

        free(root);
    }
}
