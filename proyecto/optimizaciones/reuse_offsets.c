#include "reuse_offsets.h"




void setOffsetsInAstWithReuse(AstNode *root) {
    int currentOffset = -8;
    setOffsetsInAstWithReuseAux(root, &currentOffset);
}




void setOffsetsInAstWithReuseAux(AstNode *node, int *currentOffset) {
    if (!node) return;

    switch (node->type) {
            case AST_NODE_TYPE_P:                setOffsetsInAstWithReuseAux(node->children1, currentOffset); break;
            case AST_NODE_TYPE_GLOBAL_DECL_LIST: setOffsetsInAstWithReuseAux(node->children2, currentOffset); break;
            case AST_NODE_TYPE_VAR_DECL:         setOffsetsNodeVarDecl(node, currentOffset);                  break;
            case AST_NODE_TYPE_METHOD_DECL_LIST: setOffsetsNodeMethodDeclList(node, currentOffset);           break;
            case AST_NODE_TYPE_METHOD_DECL:      setOffsetsInAstWithReuseAux(node->children4, currentOffset); break;
            case AST_NODE_TYPE_LIST_ID:                                                                       break;
            case AST_NODE_TYPE_ID:                                                                            break;
            case AST_NODE_TYPE_PARAMS:                                                                        break;
            case AST_NODE_TYPE_VOID:                                                                          break;
            case AST_NODE_TYPE_PARAM:                                                                         break;
            case AST_NODE_TYPE_BLOCK:            setOffsetsNodeBlock(node, currentOffset);                    break;
            case AST_NODE_TYPE_BLOCK_ELEMS:      setOffsetsNodeBlockElems(node, currentOffset);               break;
            case AST_NODE_TYPE_STATEMENTS:       setOffsetsNodeStatements(node, currentOffset);               break;
            case AST_NODE_TYPE_TYPE:                                                                          break;
            case AST_NODE_TYPE_ASSIGNMENT:                                                                    break;
            case AST_NODE_TYPE_METHOD_CALL:                                                                   break;
            case AST_NODE_TYPE_IF_ELSE:          setOffsetsNodeIfElse(node, currentOffset);                   break;
            case AST_NODE_TYPE_WHILE:            setOffsetsInAstWithReuseAux(node->children2, currentOffset); break;
            case AST_NODE_TYPE_RETURN:                                                                        break;
            case AST_NODE_TYPE_LIST_EXPR:                                                                     break;
            case AST_NODE_TYPE_INT_LITERAL:                                                                   break;
            case AST_NODE_TYPE_FLOAT_LITERAL:                                                                 break;
            case AST_NODE_TYPE_BOOL_LITERAL:                                                                  break;
            case AST_NODE_TYPE_ADDITION:                                                                      break;
            case AST_NODE_TYPE_SUBTRACTION:                                                                   break;
            case AST_NODE_TYPE_MULTIPLICATION:                                                                break;
            case AST_NODE_TYPE_DIVISION:                                                                      break;
            case AST_NODE_TYPE_MOD:                                                                           break;
            case AST_NODE_TYPE_COMPARISON_SMALLER:                                                            break;
            case AST_NODE_TYPE_COMPARISON_GREATER:                                                            break;
            case AST_NODE_TYPE_EQUAL:                                                                         break;
            case AST_NODE_TYPE_AND:                                                                           break;
            case AST_NODE_TYPE_OR:                                                                            break;
            case AST_NODE_TYPE_MINUS:                                                                         break;
            case AST_NODE_TYPE_NEGATION:                                                                      break;
            case AST_NODE_TYPE_EXTERN_METHOD_DECL:                                                            break;
    }
}




void setOffsetsNodeMethodDeclList(AstNode *node, int *currentOffset) {
    if (node->children1) setOffsetsInAstWithReuseAux(node->children1, currentOffset);
    if (node->children2) setOffsetsInAstWithReuseAux(node->children2, currentOffset);
}




void setOffsetsNodeVarDecl(AstNode *node, int *currentOffset) {
    AstNode *aux = node->children2; // listId

    while (aux) {

        switch (aux->type) {
            
            case AST_NODE_TYPE_LIST_ID: {
                if (aux->children1->type == AST_NODE_TYPE_ID) {
                    aux->children1->symbol->offset = (*currentOffset);
                    (*currentOffset)  = (*currentOffset) - 8;
                    printf("symbol %s, offset: %d\n", aux->children1->symbol->name, aux->children1->symbol->offset);
                }
                
                if (aux->children2) aux = aux->children2;
            } break;
            
            case AST_NODE_TYPE_ID: {
                aux->symbol->offset = (*currentOffset);
                (*currentOffset)    = (*currentOffset) - 8;
                printf("symbol %s, offset: %d\n", aux->symbol->name, aux->symbol->offset);
                aux = NULL;
            } break;
        }

    }
}




void setOffsetsNodeBlock(AstNode *node, int *currentOffset) {
    int oldCurrentOffset = (*currentOffset);

    if (node->children1) setOffsetsInAstWithReuseAux(node->children1, currentOffset);

    (*currentOffset) = oldCurrentOffset; // al terminar el bloque se reestablece el offset anterior
}




void setOffsetsNodeBlockElems(AstNode *node, int *currentOffset) {
    if (node->children1) setOffsetsInAstWithReuseAux(node->children1, currentOffset);
    if (node->children2) setOffsetsInAstWithReuseAux(node->children2, currentOffset);
}




void setOffsetsNodeStatements(AstNode *node, int *currentOffset) {
    if (node->children1) setOffsetsInAstWithReuseAux(node->children1, currentOffset);
    if (node->children2) setOffsetsInAstWithReuseAux(node->children2, currentOffset);
}




void setOffsetsNodeIfElse(AstNode *node, int *currentOffset) {
    if (node->children2) setOffsetsInAstWithReuseAux(node->children2, currentOffset);
    if (node->children3) setOffsetsInAstWithReuseAux(node->children3, currentOffset);
}
