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
            case AST_NODE_TYPE_METHOD_CALL:        setOffsetsNodeMethodCall(node, currentOffset);               break;
            case AST_NODE_TYPE_IF_ELSE:            setOffsetsNodeIfElse(node, currentOffset);                   break;
            case AST_NODE_TYPE_WHILE:              setOffsetsNodeWhile(node, currentOffset);                    break;
            case AST_NODE_TYPE_RETURN:             setOffsetsNodeReturn(node, currentOffset);                   break;
            case AST_NODE_TYPE_LIST_EXPR:          setOffsetsNodeListExpr(node, currentOffset);                 break;
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
    if (node->children1) setOffsetsInAstWithReuseAux(node->children1, currentOffset);
    if (node->children2) setOffsetsInAstWithReuseAux(node->children2, currentOffset);
    if (node->children3) setOffsetsInAstWithReuseAux(node->children3, currentOffset);
}




void setOffsetsNodeMethodDecl(AstNode *node, int *currentOffset) {
    int numberOfLocalVariablesAndTemporals = 0;

    // setear el offset para todos los parametros del metodo
    Symbol *param = node->children2->symbol->parameters;

    while (param) {
        param->offset = (*currentOffset);
        (*currentOffset) -= 8;
        numberOfLocalVariablesAndTemporals++;
        printf("[LOG_REUSE_OFFSETS]: symbol %s, offset: %d\n", param->name, param->offset);
        param = param->next;
    }

    if (node->children4) getNumberOfLocalVariablesAndTemporals(node->children4, &numberOfLocalVariablesAndTemporals);
    DEBUG_REUSE_OFFSETS("getNumberOfLocalVariablesAndTemporals() ended")
    DEBUG_REUSE_OFFSETS("numberOfLocalVariables: %d", numberOfLocalVariablesAndTemporals)
    node->children2->symbol->numberOfLocalVariables = numberOfLocalVariablesAndTemporals;
    setOffsetsInAstWithReuseAux(node->children4, currentOffset);

    // restarurar el offset de los parametros
    int numberOfParams = node->children2->symbol->numberOfParameters;

    while (numberOfParams > 0) {
        (*currentOffset) += 8;
        numberOfParams--;
    }
}




void setOffsetsNodeMethodCall(AstNode *node, int *currentOffset) {
    if (node->symbol) {
        node->symbol->offset = (*currentOffset);
        (*currentOffset) -= 8;
        printf("[LOG_REUSE_OFFSETS]: symbol %s, offset: %d\n", node->symbol->name, node->symbol->offset);
    }

    // setear offsets para los temporales de las expresiones de los argumentos
    if (node->children2) setOffsetsInAstWithReuseAux(node->children2, currentOffset);
}




void setOffsetsNodeListExpr(AstNode *node, int *currentOffset) {
    if (node->children1) setOffsetsInAstWithReuseAux(node->children1, currentOffset);
    if (node->children2) setOffsetsInAstWithReuseAux(node->children2, currentOffset);
}




void setOffsetsNodeWhile(AstNode *node, int *currentOffset) {
    if (node->children1) setOffsetsInAstWithReuseAux(node->children1, currentOffset);
    if (node->children2) setOffsetsInAstWithReuseAux(node->children2, currentOffset);
}




void setOffsetsNodeReturn(AstNode *node, int *currentOffset) {
    if (node->children1) setOffsetsInAstWithReuseAux(node->children1, currentOffset);
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
            DEBUG_REUSE_OFFSETS("node Block")
            if (node->children1) getNumberOfLocalVariablesAndTemporals(node->children1, numberOfVarsAndTemps);
        } break;
        
        case AST_NODE_TYPE_BLOCK_ELEMS: {
            DEBUG_REUSE_OFFSETS("node BlockElems")
            AstNode *aux = node->children1->children2; // var decl -> list id
            int count    = 0;

            while (aux) {
                switch (aux->type) {

                    case AST_NODE_TYPE_LIST_ID: {
                        DEBUG_REUSE_OFFSETS("node ListId")
                        count++;
                        aux->children1->symbol->marked = true;
                        aux = aux->children2;
                    } break;
                    
                    case AST_NODE_TYPE_ID: {
                        DEBUG_REUSE_OFFSETS("node Id")
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
            DEBUG_REUSE_OFFSETS("node Statements")
            if (node->children1) getNumberOfLocalVariablesAndTemporals(node->children1, numberOfVarsAndTemps);
            if (node->children2) getNumberOfLocalVariablesAndTemporals(node->children2, numberOfVarsAndTemps);
        } break;
        
        case AST_NODE_TYPE_ASSIGNMENT: {
            DEBUG_REUSE_OFFSETS("node Assignment")
            if (node->children2) getNumberOfLocalVariablesAndTemporals(node->children2, numberOfVarsAndTemps);
        } break;

        case AST_NODE_TYPE_METHOD_CALL: {
            DEBUG_REUSE_OFFSETS("node MethodCall")
            if (node->children2) getNumberOfLocalVariablesAndTemporals(node->children2, numberOfVarsAndTemps); 

            if (!node->symbol->marked) {
                (*numberOfVarsAndTemps)++;
                node->symbol->marked = true;
            }
        } break;

        case AST_NODE_TYPE_IF_ELSE: {
            DEBUG_REUSE_OFFSETS("node IfElse")
            if (node->children1) getNumberOfLocalVariablesAndTemporals(node->children1, numberOfVarsAndTemps);
            if (node->children2) getNumberOfLocalVariablesAndTemporals(node->children2, numberOfVarsAndTemps);
            if (node->children3) getNumberOfLocalVariablesAndTemporals(node->children3, numberOfVarsAndTemps);
        } break;

        case AST_NODE_TYPE_WHILE: {
            DEBUG_REUSE_OFFSETS("node While")
            if (node->children1) getNumberOfLocalVariablesAndTemporals(node->children1, numberOfVarsAndTemps);
            if (node->children2) getNumberOfLocalVariablesAndTemporals(node->children2, numberOfVarsAndTemps);
        } break;

        case AST_NODE_TYPE_RETURN: {
            DEBUG_REUSE_OFFSETS("node Return")
            if (node->children1) getNumberOfLocalVariablesAndTemporals(node->children1, numberOfVarsAndTemps);
        } break;

        case AST_NODE_TYPE_LIST_EXPR: {
            DEBUG_REUSE_OFFSETS("node ListExpr")
            if (node->children1) getNumberOfLocalVariablesAndTemporals(node->children1, numberOfVarsAndTemps);
            if (node->children2) getNumberOfLocalVariablesAndTemporals(node->children2, numberOfVarsAndTemps);
        } break;

        case AST_NODE_TYPE_ID: DEBUG_REUSE_OFFSETS("node Id") break;
        
        case AST_NODE_TYPE_INT_LITERAL: DEBUG_REUSE_OFFSETS("node IntLiteral") break;

        case AST_NODE_TYPE_FLOAT_LITERAL: DEBUG_REUSE_OFFSETS("node FloatLiteral") break;
        
        case AST_NODE_TYPE_BOOL_LITERAL: DEBUG_REUSE_OFFSETS("node BoolLiteral") break;

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
            DEBUG_REUSE_OFFSETS("node BinaryOperator")
            if (node->children1) getNumberOfLocalVariablesAndTemporals(node->children1, numberOfVarsAndTemps);
            if (node->children2) getNumberOfLocalVariablesAndTemporals(node->children2, numberOfVarsAndTemps);
            
            if (!node->symbol->marked) {
                (*numberOfVarsAndTemps)++;
                node->symbol->marked = true;
            }
        } break;

        case AST_NODE_TYPE_MINUS:
        case AST_NODE_TYPE_NEGATION: {
            DEBUG_REUSE_OFFSETS("node UnaryOperator")
            if (node->children1) getNumberOfLocalVariablesAndTemporals(node->children1, numberOfVarsAndTemps);
            
            if (!node->symbol->marked) {
                (*numberOfVarsAndTemps)++;
                node->symbol->marked = true;
            }
        } break;
    }
}
