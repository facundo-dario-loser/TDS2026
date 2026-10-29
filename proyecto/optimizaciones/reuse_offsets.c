#include "reuse_offsets.h"




void setOffsetsInAstWithReuse(AstNode *root) {
    int currentOffset = -8;
    setOffsetsInAstWithReuseAux(root, &currentOffset);
}




void setOffsetsInAstWithReuseAux(AstNode *node, int *currentOffset) {
    if (!node) return;

    switch (node->type) {
            case AST_NODE_TYPE_P:                  setOffsetsInAstWithReuseAux(node->children1, currentOffset); break;
            case AST_NODE_TYPE_GLOBAL_DECL_LIST:   setOffsetsInAstWithReuseAux(node->children2, currentOffset); break;
            case AST_NODE_TYPE_VAR_DECL:           setOffsetsNodeVarDecl(node, currentOffset);                  break;
            case AST_NODE_TYPE_METHOD_DECL_LIST:   setOffsetsNodeMethodDeclList(node, currentOffset);           break;
            case AST_NODE_TYPE_METHOD_DECL:        setOffsetsNodeMethodDecl(node, currentOffset);               break;
            case AST_NODE_TYPE_LIST_ID:                                                                         break;
            case AST_NODE_TYPE_ID:                                                                              break;
            case AST_NODE_TYPE_PARAMS:                                                                          break;
            case AST_NODE_TYPE_VOID:                                                                            break;
            case AST_NODE_TYPE_PARAM:                                                                           break;
            case AST_NODE_TYPE_BLOCK:              setOffsetsNodeBlock(node, currentOffset);                    break;
            case AST_NODE_TYPE_BLOCK_ELEMS:        setOffsetsNodeBlockElems(node, currentOffset);               break;
            case AST_NODE_TYPE_STATEMENTS:         setOffsetsNodeStatements(node, currentOffset);               break;
            case AST_NODE_TYPE_TYPE:                                                                            break;
            case AST_NODE_TYPE_ASSIGNMENT:         setOffsetsInAstWithReuseAux(node->children2, currentOffset); break;
            case AST_NODE_TYPE_METHOD_CALL:                                                                     break;
            case AST_NODE_TYPE_IF_ELSE:            setOffsetsNodeIfElse(node, currentOffset);                   break;
            case AST_NODE_TYPE_WHILE:              setOffsetsInAstWithReuseAux(node->children2, currentOffset); break;
            case AST_NODE_TYPE_RETURN:                                                                          break;
            case AST_NODE_TYPE_LIST_EXPR:                                                                       break;
            case AST_NODE_TYPE_INT_LITERAL:                                                                     break;
            case AST_NODE_TYPE_FLOAT_LITERAL:                                                                   break;
            case AST_NODE_TYPE_BOOL_LITERAL:                                                                    break;
            case AST_NODE_TYPE_ADDITION:           setOffsetsNodeBinaryOperator(node, currentOffset);           break;
            case AST_NODE_TYPE_SUBTRACTION:        setOffsetsNodeBinaryOperator(node, currentOffset);           break;
            case AST_NODE_TYPE_MULTIPLICATION:     setOffsetsNodeBinaryOperator(node, currentOffset);           break;
            case AST_NODE_TYPE_DIVISION:           setOffsetsNodeBinaryOperator(node, currentOffset);           break;
            case AST_NODE_TYPE_MOD:                setOffsetsNodeBinaryOperator(node, currentOffset);           break;
            case AST_NODE_TYPE_COMPARISON_SMALLER: setOffsetsNodeBinaryOperator(node, currentOffset);           break;
            case AST_NODE_TYPE_COMPARISON_GREATER: setOffsetsNodeBinaryOperator(node, currentOffset);           break;
            case AST_NODE_TYPE_EQUAL:              setOffsetsNodeBinaryOperator(node, currentOffset);           break;
            case AST_NODE_TYPE_AND:                setOffsetsNodeBinaryOperator(node, currentOffset);           break;
            case AST_NODE_TYPE_OR:                 setOffsetsNodeBinaryOperator(node, currentOffset);           break;
            case AST_NODE_TYPE_MINUS:              setOffsetsNodeUnaryOperator(node, currentOffset);            break;
            case AST_NODE_TYPE_NEGATION:           setOffsetsNodeUnaryOperator(node, currentOffset);            break;
            case AST_NODE_TYPE_EXTERN_METHOD_DECL:                                                              break;
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
                    printf("[LOG_REUSE_OFFSETS]: symbol %s, offset: %d\n", aux->children1->symbol->name, aux->children1->symbol->offset);
                }
                
                if (aux->children2) aux = aux->children2;
            } break;
            
            case AST_NODE_TYPE_ID: {
                aux->symbol->offset = (*currentOffset);
                (*currentOffset)    = (*currentOffset) - 8;
                printf("[LOG_REUSE_OFFSETS]: symbol %s, offset: %d\n", aux->symbol->name, aux->symbol->offset);
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




void setOffsetsNodeMethodDecl(AstNode *node, int *currentOffset) {
    int numberOfLocalVariablesAndTemporals = 0;

    if (node->children4) getNumberOfLocalVariablesAndTemporals(node->children4, &numberOfLocalVariablesAndTemporals);
    printf("getNumberOfLocalVariablesAndTemporals() ended\n");
    printf("numberOfLocalVariables: %d\n", numberOfLocalVariablesAndTemporals);
    node->children2->symbol->numberOfLocalVariables = numberOfLocalVariablesAndTemporals;
    setOffsetsInAstWithReuseAux(node->children4, currentOffset);
}




void setOffsetsNodeBinaryOperator(AstNode *node, int *currentOffset) {
    if (node->children1) setOffsetsInAstWithReuseAux(node->children1, currentOffset);
    if (node->children2) setOffsetsInAstWithReuseAux(node->children2, currentOffset);

    node->symbol->offset = *currentOffset;
    (*currentOffset) = (*currentOffset) - 8;

    printf("[LOG_REUSE_OFFSETS]: symbol %s, offset: %d\n", node->symbol->name, node->symbol->offset);
}




void setOffsetsNodeUnaryOperator(AstNode *node, int *currentOffset) {
    if (node->children1) setOffsetsInAstWithReuseAux(node->children1, currentOffset);

    node->symbol->offset = *currentOffset;
    (*currentOffset) = (*currentOffset) - 8;

    printf("[LOG_REUSE_OFFSETS]: symbol %s, offset: %d\n", node->symbol->name, node->symbol->offset);
}




void getNumberOfLocalVariablesAndTemporals(AstNode *node, int *numberOfVarsAndTemps) {
    if (!node) return;

    switch (node->type) {
        
        case AST_NODE_TYPE_BLOCK: {
            printf("node Block\n");
            if (node->children1) getNumberOfLocalVariablesAndTemporals(node->children1, numberOfVarsAndTemps);
        } break;
        
        case AST_NODE_TYPE_BLOCK_ELEMS: {
            printf("node BlockElems\n");
            AstNode *aux = node->children1->children2; // var decl -> list id
            int count    = 0;

            while (aux) {
                switch (aux->type) {

                    case AST_NODE_TYPE_LIST_ID: {
                        printf("node ListId\n");
                        count++;
                        aux->children1->symbol->marked = true;
                        aux = aux->children2;
                    } break;
                    
                    case AST_NODE_TYPE_ID: {
                        printf("node Id\n");
                        aux->symbol->marked = true;
                        count++;
                        aux = NULL;
                    } break;
                }
            }

            (*numberOfVarsAndTemps) += count;

            if (node->children2) getNumberOfLocalVariablesAndTemporals(node->children2, numberOfVarsAndTemps);
        } break;

        case AST_NODE_TYPE_STATEMENTS: {
            printf("node Statements\n");
            if (node->children1) getNumberOfLocalVariablesAndTemporals(node->children1, numberOfVarsAndTemps);
            if (node->children2) getNumberOfLocalVariablesAndTemporals(node->children2, numberOfVarsAndTemps);
        } break;
        
        case AST_NODE_TYPE_ASSIGNMENT: {
            printf("node Assignment\n");
            if (node->children2) getNumberOfLocalVariablesAndTemporals(node->children2, numberOfVarsAndTemps);
        } break;

        case AST_NODE_TYPE_METHOD_CALL: {
            printf("node MethodCall\n");
            if (node->children2) getNumberOfLocalVariablesAndTemporals(node->children2, numberOfVarsAndTemps); 

            if (!node->symbol->marked) {
                (*numberOfVarsAndTemps)++;
                node->symbol->marked = true;
            }
        } break;

        case AST_NODE_TYPE_IF_ELSE: {
            printf("node IfElse\n");
            if (node->children1) getNumberOfLocalVariablesAndTemporals(node->children1, numberOfVarsAndTemps);
            if (node->children2) getNumberOfLocalVariablesAndTemporals(node->children2, numberOfVarsAndTemps);
            if (node->children3) getNumberOfLocalVariablesAndTemporals(node->children3, numberOfVarsAndTemps);
        } break;

        case AST_NODE_TYPE_WHILE: {
            printf("node While\n");
            if (node->children1) getNumberOfLocalVariablesAndTemporals(node->children1, numberOfVarsAndTemps);
            if (node->children2) getNumberOfLocalVariablesAndTemporals(node->children2, numberOfVarsAndTemps);
        } break;

        case AST_NODE_TYPE_RETURN: {
            printf("node Return\n");
            if (node->children1) getNumberOfLocalVariablesAndTemporals(node->children1, numberOfVarsAndTemps);
        } break;

        case AST_NODE_TYPE_LIST_EXPR: {
            printf("node ListExpr\n");
            if (node->children1) getNumberOfLocalVariablesAndTemporals(node->children1, numberOfVarsAndTemps);
            if (node->children2) getNumberOfLocalVariablesAndTemporals(node->children2, numberOfVarsAndTemps);
        } break;

        case AST_NODE_TYPE_ID: printf("node Id\n"); break;
        
        case AST_NODE_TYPE_INT_LITERAL: printf("node IntLiteral\n"); break;

        case AST_NODE_TYPE_FLOAT_LITERAL: printf("node FloatLiteral\n"); break;
        
        case AST_NODE_TYPE_BOOL_LITERAL: printf("node BoolLiteral\n"); break;

        case AST_NODE_TYPE_ADDITION:
        case AST_NODE_TYPE_SUBTRACTION:
        case AST_NODE_TYPE_MULTIPLICATION:
        case AST_NODE_TYPE_DIVISION:
        case AST_NODE_TYPE_MOD:
        case AST_NODE_TYPE_COMPARISON_SMALLER:
        case AST_NODE_TYPE_COMPARISON_GREATER:
        case AST_NODE_TYPE_EQUAL:
        case AST_NODE_TYPE_AND:
        case AST_NODE_TYPE_OR: {
            printf("node BinaryOperator\n");
            if (node->children1) getNumberOfLocalVariablesAndTemporals(node->children1, numberOfVarsAndTemps);
            if (node->children2) getNumberOfLocalVariablesAndTemporals(node->children2, numberOfVarsAndTemps);
            
            if (!node->symbol->marked) {
                (*numberOfVarsAndTemps)++;
                node->symbol->marked = true;
            }
        } break;

        case AST_NODE_TYPE_MINUS:
        case AST_NODE_TYPE_NEGATION: {
            printf("node UnaryOperator\n");
            if (node->children1) getNumberOfLocalVariablesAndTemporals(node->children1, numberOfVarsAndTemps);
            
            if (!node->symbol->marked) {
                (*numberOfVarsAndTemps)++;
                node->symbol->marked = true;
            }
        } break;
    }
}
