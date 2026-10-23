#include "constant_propagation.h"




void constantPropagation(AstNode **root) {
    if (!(*root)) return;

    switch ((*root)->type) {
        case AST_NODE_TYPE_P:                 constantPropagation(&(*root)->children1);        break;
        case AST_NODE_TYPE_GLOBAL_DECL_LIST:  constantPropagation(&(*root)->children2);        break;
        case AST_NODE_TYPE_VAR_DECL:                                                           break;
        case AST_NODE_TYPE_METHOD_DECL_LIST:  constantPropagationNodeMethodDeclList(root);     break;
        case AST_NODE_TYPE_METHOD_DECL:       constantPropagationNodeMethodDecl(root);         break;
        case AST_NODE_TYPE_LIST_ID:                                                            break;
        case AST_NODE_TYPE_PARAMS:                                                             break;
        case AST_NODE_TYPE_VOID:                                                               break;
        case AST_NODE_TYPE_BLOCK:              constantPropagation(&(*root)->children1);       break;
        case AST_NODE_TYPE_BLOCK_ELEMS:        constantPropagation(&(*root)->children2);       break;
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




void constantPropagationNodeMethodDeclList(AstNode **node) {
    printf("node methodDeclList visited\n");
    constantPropagation(&(*node)->children1);
    constantPropagation(&(*node)->children2);
}




void constantPropagationNodeMethodDecl(AstNode **node) {
    printf("node methodDecl visited\n");
    constantPropagation(&(*node)->children4);
}




void constantPropagationNodeStatements(AstNode **node) {
    printf("node NodeStatements visited\n");
    constantPropagation(&(*node)->children1);
    constantPropagation(&(*node)->children2);
}




void constantPropagationNodeAssignment(AstNode **node) {
    printf("node Assignment visited\n");
    constantPropagation(&(*node)->children2);
}




void constantPropagationNodeMethodCall(AstNode **node) {
    printf("node methodCall visited\n");
    if ((*node)->children2) constantPropagation(&(*node)->children2);
}




void constantPropagationNodeIfElse(AstNode **node) {
    printf("node IfElse visited\n");
    constantPropagation(&(*node)->children1);
    constantPropagation(&(*node)->children2);
    constantPropagation(&(*node)->children3);
}




void constantPropagationNodeWhile(AstNode **node) {
    printf("node While visited\n");
    constantPropagation(&(*node)->children1);
    constantPropagation(&(*node)->children2);
}




void constantPropagationNodeReturn(AstNode **node) {
    printf("node Return visited\n");
    if ((*node)->children1) constantPropagation(&(*node)->children1);
}




void constantPropagationNodeListExpr(AstNode **node) {
    printf("node ListExpr visited\n");
    constantPropagation(&(*node)->children1);
    constantPropagation(&(*node)->children2);
}




void constantPropagationNodeAddition(AstNode **node) {
    printf("node Addition visited\n");
    constantPropagationNodeArithmeticBinaryOperation(node);
}




void constantPropagationNodeSubtraction(AstNode **node) {
    printf("node Subtraction visited\n");
    constantPropagationNodeArithmeticBinaryOperation(node);
}




void constantPropagationNodeMultiplication(AstNode **node) {
    printf("node Multiplication visited\n");
    constantPropagationNodeArithmeticBinaryOperation(node);
}




void constantPropagationNodeDivision(AstNode **node) {
    printf("node Division visited\n");
    constantPropagationNodeArithmeticBinaryOperation(node);
}




void constantPropagationNodeMod(AstNode **node) {
    printf("node Mod visited\n");
    // warning: solo funciona con operandos ints (en c % solo opera con enteros)
    // TODO: ver como manejar el caso cuando alguno de los operandos es float
    constantPropagationNodeArithmeticBinaryOperation(node);
}




void constantPropagationNodeComparisonSmaller(AstNode **node) {
    printf("node ComparisonSmaller visited\n");
    constantPropagationNodeComparison(node);
}




void constantPropagationNodeComparisonGreater(AstNode **node) {
    printf("node ComparisonGreater visited\n");
    constantPropagationNodeComparison(node);
}




void constantPropagationNodeEqual(AstNode **node) {
    printf("node Equal visited\n");
    constantPropagationNodeComparison(node);
}




void constantPropagationNodeAnd(AstNode **node) {
    printf("node And visited\n");
    constantPropagationNodeBooleanBinaryOperation(node);
}




void constantPropagationNodeOr(AstNode **node) {
    printf("node Or visited\n");
    constantPropagationNodeBooleanBinaryOperation(node);
}




void constantPropagationNodeMinus(AstNode **node) {
    printf("node Minus visited\n");
    constantPropagation(&(*node)->children1);

    SymbolValue         constValue;
    SymbolSemanticType  constSymbolSemanticType;
    char                constSymbolName[16];
    AstNodeType         constNodeType;
    AstNodeValue        constNodeValue;

    if ((*node)->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
        constValue.intValue     = -(*node)->children1->symbol->value.intValue;
        constSymbolSemanticType = SYMBOL_SEMANTIC_TYPE_INT;
        constNodeType           = AST_NODE_TYPE_INT_LITERAL;
        constNodeValue.intValue = constValue.intValue;
        snprintf(constSymbolName, sizeof(constSymbolName), "%d", constValue.intValue);
    }

    if ((*node)->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
        constValue.floatValue     = -(*node)->children1->symbol->value.floatValue;
        constSymbolSemanticType   = SYMBOL_SEMANTIC_TYPE_FLOAT;
        constNodeType             = AST_NODE_TYPE_FLOAT_LITERAL,
        constNodeValue.floatValue = constValue.floatValue;
        snprintf(constSymbolName, sizeof(constSymbolName), "%f", constValue.floatValue);
    }

    freeAst((*node));

    SymbolConfig constSymbolConfig = {
        .type         = SYMBOL_TYPE_CONSTANT,
        .semanticType = constSymbolSemanticType,
        .value        = constValue,
        .name         = strdup(constSymbolName),
    };

    Symbol *constSymbol = newSymbol(&constSymbolConfig);

    AstNodeConfig constNodeConfig = {
        .type   = constNodeType,
        .symbol = constSymbol,
        .value  = constNodeValue,
    };

    (*node) = newAstNode(&constNodeConfig);
    constSymbol->referenceCount++;
}




void constantPropagationNodeNegation(AstNode **node) {
    printf("node Negation visited\n");
    constantPropagation(&(*node)->children1);

    // ...
}




void constantPropagationNodeArithmeticBinaryOperation(AstNode **node) {
    constantPropagation(&(*node)->children1);
    constantPropagation(&(*node)->children2);

    if (((*node)->children1->symbol->type == SYMBOL_TYPE_CONSTANT) &&
        ((*node)->children2->symbol->type == SYMBOL_TYPE_CONSTANT)) {
            SymbolValue        constValue;
            SymbolSemanticType constSemanticType;
            char               constName[16];
            AstNodeType        constNodeType;
            AstNodeValue       constNodeValue;

            if (((*node)->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) &&
                ((*node)->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                    
                    switch ((*node)->type) {
                        case AST_NODE_TYPE_ADDITION: {
                            constValue.intValue = (*node)->children1->symbol->value.intValue + (*node)->children2->symbol->value.intValue;
                        } break;

                        case AST_NODE_TYPE_SUBTRACTION: {
                            constValue.intValue = (*node)->children1->symbol->value.intValue - (*node)->children2->symbol->value.intValue;
                        } break;

                        case AST_NODE_TYPE_MULTIPLICATION: {
                            constValue.intValue = (*node)->children1->symbol->value.intValue * (*node)->children2->symbol->value.intValue;
                        } break;

                        case AST_NODE_TYPE_DIVISION: {
                            constValue.intValue = (*node)->children1->symbol->value.intValue / (*node)->children2->symbol->value.intValue;
                        } break;

                        case AST_NODE_TYPE_MOD: {
                            constValue.intValue = (*node)->children1->symbol->value.intValue % (*node)->children2->symbol->value.intValue;
                        } break;
                    }

                    constSemanticType       = SYMBOL_SEMANTIC_TYPE_INT;
                    constNodeType           = AST_NODE_TYPE_INT_LITERAL;
                    constNodeValue.intValue = constValue.intValue; // es solo para que se imprima bien en el archivo dot
                    snprintf(constName, sizeof(constName), "%d", constValue.intValue);
                }

            if (((*node)->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) &&
                ((*node)->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                    
                    switch ((*node)->type) {
                        case AST_NODE_TYPE_ADDITION: {
                            constValue.floatValue = (float)(*node)->children1->symbol->value.intValue + (*node)->children2->symbol->value.floatValue;
                        } break;
                        
                        case AST_NODE_TYPE_SUBTRACTION: {
                            constValue.floatValue = (float)(*node)->children1->symbol->value.intValue - (*node)->children2->symbol->value.floatValue;
                        } break;
                        
                        case AST_NODE_TYPE_MULTIPLICATION: {
                            constValue.floatValue = (float)(*node)->children1->symbol->value.intValue * (*node)->children2->symbol->value.floatValue;
                        } break;
                        
                        case AST_NODE_TYPE_DIVISION: {
                            constValue.floatValue = (float)(*node)->children1->symbol->value.intValue / (*node)->children2->symbol->value.floatValue;
                        } break;
                        
                        case AST_NODE_TYPE_MOD: {
                            TODO("const % const in C only works with ints in constantPropagationNodeArithmeticBinaryOperation()")
                        } break;
                    }

                    constSemanticType         = SYMBOL_SEMANTIC_TYPE_FLOAT;
                    constNodeType             = AST_NODE_TYPE_FLOAT_LITERAL;
                    constNodeValue.floatValue = constValue.floatValue;
                    snprintf(constName, sizeof(constName), "%f", constValue.floatValue);
                }

            if (((*node)->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) &&
                ((*node)->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                    
                    switch ((*node)->type) {
                        case AST_NODE_TYPE_ADDITION: {
                            constValue.floatValue = (*node)->children1->symbol->value.floatValue + (float)(*node)->children2->symbol->value.intValue;
                        } break;
                        
                        case AST_NODE_TYPE_SUBTRACTION: {
                            constValue.floatValue = (*node)->children1->symbol->value.floatValue - (float)(*node)->children2->symbol->value.intValue;
                        } break;
                        
                        case AST_NODE_TYPE_MULTIPLICATION: {
                            constValue.floatValue = (*node)->children1->symbol->value.floatValue * (float)(*node)->children2->symbol->value.intValue;
                        } break;
                        
                        case AST_NODE_TYPE_DIVISION: {
                            constValue.floatValue = (*node)->children1->symbol->value.floatValue / (float)(*node)->children2->symbol->value.intValue;
                        } break;
                        
                        case AST_NODE_TYPE_MOD: {
                            TODO("const % const in C only works with ints in constantPropagationNodeArithmeticBinaryOperation()")
                        } break;
                    }
        
                    constSemanticType         = SYMBOL_SEMANTIC_TYPE_FLOAT;
                    constNodeType             = AST_NODE_TYPE_FLOAT_LITERAL;
                    constNodeValue.floatValue = constValue.floatValue;
                    snprintf(constName, sizeof(constName), "%f", constValue.floatValue);
                }

            if (((*node)->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) &&
                ((*node)->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                    
                    switch ((*node)->type) {
                        case AST_NODE_TYPE_ADDITION: {
                            constValue.floatValue = (*node)->children1->symbol->value.floatValue + (*node)->children2->symbol->value.floatValue;
                        } break;
                        
                        case AST_NODE_TYPE_SUBTRACTION: {
                            constValue.floatValue = (*node)->children1->symbol->value.floatValue - (*node)->children2->symbol->value.floatValue;
                        } break;
                        
                        case AST_NODE_TYPE_MULTIPLICATION: {
                            constValue.floatValue = (*node)->children1->symbol->value.floatValue * (*node)->children2->symbol->value.floatValue;
                        } break;
                        
                        case AST_NODE_TYPE_DIVISION: {
                            constValue.floatValue = (*node)->children1->symbol->value.floatValue / (*node)->children2->symbol->value.floatValue;
                        } break;
                        
                        case AST_NODE_TYPE_MOD: {
                            TODO("const % const in C only works with ints in constantPropagationNodeArithmeticBinaryOperation()")
                        } break;
                    }

                    constSemanticType         = SYMBOL_SEMANTIC_TYPE_FLOAT;
                    constNodeType             = AST_NODE_TYPE_FLOAT_LITERAL;
                    constNodeValue.floatValue = constValue.floatValue;
                    snprintf(constName, sizeof(constName), "%f", constValue.floatValue);
                }

            freeAst((*node));

            SymbolConfig constSymbolConfig = {
                .type         = SYMBOL_TYPE_CONSTANT,
                .name         = strdup(constName),
                .semanticType = constSemanticType,
                .value        = constValue,
            };

            Symbol *constSymbol = newSymbol(&constSymbolConfig);
            
            AstNodeConfig constNodeConfig = {
                .type   = constNodeType,
                .symbol = constSymbol,
                .value  = constNodeValue,
            };

            (*node) = newAstNode(&constNodeConfig);
            constSymbol->referenceCount++;
    }
}




void constantPropagationNodeComparison(AstNode **node) {
    if (!(*node)) return;

    constantPropagation(&(*node)->children1);
    constantPropagation(&(*node)->children2);

    bool constValue;
    char constSymbolName[16];

    if (((*node)->children1->symbol->type == SYMBOL_TYPE_CONSTANT) &&
        ((*node)->children2->symbol->type == SYMBOL_TYPE_CONSTANT)) {
            
            if (((*node)->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) &&
                ((*node)->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
                    
                    switch ((*node)->type) {
                        case AST_NODE_TYPE_COMPARISON_SMALLER: {
                            constValue = (*node)->children1->symbol->value.intValue < (*node)->children2->symbol->value.intValue;
                        } break;
                        
                        case AST_NODE_TYPE_COMPARISON_GREATER: {
                            constValue = (*node)->children1->symbol->value.intValue > (*node)->children2->symbol->value.intValue;
                        } break;

                        case AST_NODE_TYPE_EQUAL: {
                            constValue = (*node)->children1->symbol->value.intValue == (*node)->children2->symbol->value.intValue;
                        } break;
                    }
                }

            if (((*node)->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) &&
                ((*node)->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                    
                    switch ((*node)->type) {
                        case AST_NODE_TYPE_COMPARISON_SMALLER: {
                            constValue = (*node)->children1->symbol->value.intValue < (*node)->children2->symbol->value.floatValue;
                        } break;
                        
                        case AST_NODE_TYPE_COMPARISON_GREATER: {
                            constValue = (*node)->children1->symbol->value.intValue > (*node)->children2->symbol->value.floatValue;
                        } break;
                    }
                }

            if (((*node)->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) &&
                ((*node)->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT)) {
        
                    switch ((*node)->type) {
                        case AST_NODE_TYPE_COMPARISON_SMALLER: {
                            constValue = (*node)->children1->symbol->value.floatValue < (*node)->children2->symbol->value.intValue;
                        } break;
                        
                        case AST_NODE_TYPE_COMPARISON_GREATER: {
                            constValue = (*node)->children1->symbol->value.floatValue > (*node)->children2->symbol->value.intValue;
                        } break;
                    }
                }

            if (((*node)->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) &&
                ((*node)->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
                
                    switch ((*node)->type) {
                        case AST_NODE_TYPE_COMPARISON_SMALLER: {
                            constValue = (*node)->children1->symbol->value.floatValue < (*node)->children2->symbol->value.floatValue;
                        } break;
                        
                        case AST_NODE_TYPE_COMPARISON_GREATER: {
                            constValue = (*node)->children1->symbol->value.floatValue > (*node)->children2->symbol->value.floatValue;
                        } break;

                        case AST_NODE_TYPE_EQUAL: {
                            constValue = (*node)->children1->symbol->value.floatValue == (*node)->children2->symbol->value.floatValue;
                        } break;
                    }
                }

            if (((*node)->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) &&
                ((*node)->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN)) {
                    if ((*node)->type == AST_NODE_TYPE_EQUAL) {
                        constValue = (*node)->children1->symbol->value.booleanValue == (*node)->children2->symbol->value.booleanValue; 
                    }
                }

            freeAst((*node));

            snprintf(constSymbolName, sizeof(constSymbolName), "%s", constValue ? "true" : "false");
            
            SymbolConfig constSymbolConfig = {
                .type         = SYMBOL_TYPE_CONSTANT,
                .semanticType = SYMBOL_SEMANTIC_TYPE_BOOLEAN,
                .name         = strdup(constSymbolName),
                .value        = constValue,
            };

            Symbol *constSymbol = newSymbol(&constSymbolConfig);

            AstNodeConfig constNodeConfig = {
                .type               = AST_NODE_TYPE_BOOL_LITERAL,
                .symbol             = constSymbol,
                .value.booleanValue = constValue,
            };

            (*node) = newAstNode(&constNodeConfig);
            constSymbol->referenceCount++;
        }
}




void constantPropagationNodeBooleanBinaryOperation(AstNode **node) {
    if (!(*node)) return;

    constantPropagation(&(*node)->children1);
    constantPropagation(&(*node)->children2);

    bool constValue;
    char constSymbolName[16];

    if (((*node)->children1->symbol->type == SYMBOL_TYPE_CONSTANT) &&
        ((*node)->children2->symbol->type == SYMBOL_TYPE_CONSTANT)) {
            if ((*node)->type == AST_NODE_TYPE_AND) {
                constValue = (*node)->children1->symbol->value.booleanValue && (*node)->children2->symbol->value.booleanValue; 
            }

            if ((*node)->type == AST_NODE_TYPE_OR) {
                constValue = (*node)->children1->symbol->value.booleanValue || (*node)->children2->symbol->value.booleanValue;
            }

            freeAst((*node));

            snprintf(constSymbolName, sizeof(constSymbolName), "%s", constValue ? "true" : "false");

            SymbolConfig constSymbolConfig = {
                .type               = SYMBOL_TYPE_CONSTANT,
                .semanticType       = SYMBOL_SEMANTIC_TYPE_BOOLEAN,
                .value.booleanValue = constValue,
                .name               = strdup(constSymbolName),
            };

            Symbol *constSymbol = newSymbol(&constSymbolConfig);

            AstNodeConfig constNodeConfig = {
                .type               = AST_NODE_TYPE_BOOL_LITERAL,
                .symbol             = constSymbol,
                .value.booleanValue = constValue,
            };

            (*node) = newAstNode(&constNodeConfig);
            constSymbol->referenceCount++;
        }
}
