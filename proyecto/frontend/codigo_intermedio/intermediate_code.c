#include "intermediate_code.h"

Instruction * newInstruction(InstructionConfig *config) {
    Instruction *i = (Instruction*)malloc(sizeof(Instruction));

    if (!i)
        ERROR_IR("couldn't allocate memory for 'i' in newInstruction()")

    i->type   = config->type;
    i->op1    = config->op1;
    i->op2    = config->op2;
    i->result = config->result;
    i->next   = NULL;
    i->prev   = NULL;

    return i;
}




void insertInstruction(Instruction **tail, Instruction *i) {
    if (!i) return;

    if (!(*tail)) {
        *tail = i;
    } else {
        (*tail)->next = i;
        i->prev = *tail;
        *tail = i;
    }
}




Instruction * generateIntermediateCode(AstNode *root) {
    Instruction *head;
    Instruction *tail;
    head = NULL;
    tail = NULL;

    int labelCount = 0;

    generateIntermediateCodeAux(root, &tail, &labelCount);

    if (!tail)
        ERROR_IR("tail is NULL in generateIntermediateCodeAux()")

    head = tail;

    while (head->prev != NULL) {
        head = head->prev;
    }

    return head;
}




void generateIntermediateCodeAux(AstNode *root, Instruction **tail, int *labelCount) {
    if (!root) return;

    switch (root->type) {
       case AST_NODE_TYPE_P:                  generateIntermediateCodeNodeP(root, tail, labelCount);                 break;
       case AST_NODE_TYPE_GLOBAL_DECL_LIST:   generateIntermediateCodeNodeGlobalDeclList(root, tail, labelCount);    break;
       case AST_NODE_TYPE_VAR_DECL:           generateIntermediateCodeNodeVarDecl(root, tail, labelCount);           break;
       case AST_NODE_TYPE_METHOD_DECL_LIST:   generateIntermediateCodeNodeMethodDeclList(root, tail, labelCount);    break;
       case AST_NODE_TYPE_METHOD_DECL:        generateIntermediateCodeNodeMethodDecl(root, tail, labelCount);        break;
       case AST_NODE_TYPE_LIST_ID:            generateIntermediateCodeNodeListId(root, tail, labelCount);            break;
       case AST_NODE_TYPE_ID:                 generateIntermediateCodeNodeId(root, tail, labelCount);                break;
       case AST_NODE_TYPE_PARAMS:             generateIntermediateCodeNodeParams(root, tail, labelCount);            break;
       case AST_NODE_TYPE_VOID:               generateIntermediateCodeNodeVoid(root, tail, labelCount);              break;
       case AST_NODE_TYPE_PARAM:              generateIntermediateCodeNodeParam(root, tail, labelCount);             break;
       case AST_NODE_TYPE_BLOCK:              generateIntermediateCodeNodeBlock(root, tail, labelCount);             break;
       case AST_NODE_TYPE_BLOCK_ELEMS:        generateIntermediateCodeNodeBlockElems(root, tail, labelCount);        break;
       case AST_NODE_TYPE_STATEMENTS:         generateIntermediateCodeNodeStatements(root, tail, labelCount);        break;
       case AST_NODE_TYPE_TYPE:               generateIntermediateCodeNodeType(root, tail, labelCount);              break;
       case AST_NODE_TYPE_ASSIGNMENT:         generateIntermediateCodeNodeAssignment(root, tail, labelCount);        break;
       case AST_NODE_TYPE_METHOD_CALL:        generateIntermediateCodeNodeMethodCall(root, tail, labelCount);        break;
       case AST_NODE_TYPE_IF_ELSE:            generateIntermediateCodeNodeIfElse(root, tail, labelCount);            break;
       case AST_NODE_TYPE_WHILE:              generateIntermediateCodeNodeWhile(root, tail, labelCount);             break;
       case AST_NODE_TYPE_RETURN:             generateIntermediateCodeNodeReturn(root, tail, labelCount);            break;
       case AST_NODE_TYPE_LIST_EXPR:          generateIntermediateCodeNodeListExpr(root, tail, labelCount);          break;
       case AST_NODE_TYPE_INT_LITERAL:        generateIntermediateCodeNodeIntLiteral(root, tail, labelCount);        break;
       case AST_NODE_TYPE_FLOAT_LITERAL:      generateIntermediateCodeNodeFloatLiteral(root, tail, labelCount);      break;
       case AST_NODE_TYPE_BOOL_LITERAL:       generateIntermediateCodeNodeBoolLiteral(root, tail, labelCount);       break;
       case AST_NODE_TYPE_ADDITION:           generateIntermediateCodeNodeAddition(root, tail, labelCount);          break;
       case AST_NODE_TYPE_SUBTRACTION:        generateIntermediateCodeNodeSubtraction(root, tail, labelCount);       break;
       case AST_NODE_TYPE_MULTIPLICATION:     generateIntermediateCodeNodeMultiplication(root, tail, labelCount);    break;
       case AST_NODE_TYPE_DIVISION:           generateIntermediateCodeNodeDivision(root, tail, labelCount);          break;
       case AST_NODE_TYPE_MOD:                generateIntermediateCodeNodeMod(root, tail, labelCount);               break;
       case AST_NODE_TYPE_COMPARISON_SMALLER: generateIntermediateCodeNodeComparisonSmaller(root, tail, labelCount); break;
       case AST_NODE_TYPE_COMPARISON_GREATER: generateIntermediateCodeNodeComparisonGreater(root, tail, labelCount); break;
       case AST_NODE_TYPE_EQUAL:              generateIntermediateCodeNodeEqual(root, tail, labelCount);             break;
       case AST_NODE_TYPE_AND:                generateIntermediateCodeNodeAnd(root, tail, labelCount);               break;
       case AST_NODE_TYPE_OR:                 generateIntermediateCodeNodeOr(root, tail, labelCount);                break;
       case AST_NODE_TYPE_MINUS:              generateIntermediateCodeNodeMinus(root, tail, labelCount);             break;
       case AST_NODE_TYPE_NEGATION:           generateIntermediateCodeNodeNegation(root, tail, labelCount);          break;
    }
}




char * getInstructionTypeString(InstructionType instType) {
    switch(instType) {
        case INSTRUCTION_TYPE_BEGIN_METHOD:                   return "BEGIN_METHOD";
        case INSTRUCTION_TYPE_END_METHOD:                     return "END_METHOD";
        case INSTRUCTION_GLOBAL_VAR_DECL:                     return "GLOBAL_VAR_DECL";
        case INSTRUCTION_TYPE_LABEL:                          return "LABEL"; 
        case INSTRUCTION_TYPE_JMP:                            return "JMP";
        case INSTRUCTION_TYPE_JMP_ZERO:                       return "JMP_ZERO";
        case INSTRUCTION_TYPE_ASSIGNMENT_INT_INT:             return "ASSIGNMENT_INT_INT";
        case INSTRUCTION_TYPE_ASSIGNMENT_INT_FLOAT:           return "ASSIGNMENT_INT_FLOAT";
        case INSTRUCTION_TYPE_ASSIGNMENT_FLOAT_INT:           return "ASSIGNMENT_FLOAT_INT";
        case INSTRUCTION_TYPE_ASSIGNMENT_FLOAT_FLOAT:         return "ASSIGNMENT_FLOAT_FLOAT";
        case INSTRUCTION_TYPE_ASSIGNMENT_BOOL_BOOL:           return "ASSIGNMENT_BOOL_BOOL";   
        case INSTRUCTION_TYPE_ADDITION_INT_INT:               return "ADDITION_INT_INT";
        case INSTRUCTION_TYPE_ADDITION_INT_FLOAT:             return "ADDITION_INT_FLOAT";
        case INSTRUCTION_TYPE_ADDITION_FLOAT_INT:             return "ADDITION_FLOAT_INT";
        case INSTRUCTION_TYPE_ADDITION_FLOAT_FLOAT:           return "ADDITION_FLOAT_FLOAT";
        case INSTRUCTION_TYPE_AND:                            return "AND";
        case INSTRUCTION_TYPE_OR:                             return "OR";
        case INSTRUCTION_TYPE_PUSH_ARGUMENT:                  return "PUSH_ARGUMENT";
        case INSTRUCTION_TYPE_CALL_METHOD:                    return "CALL_METHOD";
        case INSTRUCTION_TYPE_RETURN:                         return "RETURN";
        case INSTRUCTION_TYPE_SUBTRACTION_INT_INT:            return "SUBTRACTION_INT_INT";
        case INSTRUCTION_TYPE_SUBTRACTION_INT_FLOAT:          return "SUBTRACTION_INT_FLOAT";
        case INSTRUCTION_TYPE_SUBTRACTION_FLOAT_INT:          return "SUBTRACTION_FLOAT_INT";
        case INSTRUCTION_TYPE_SUBTRACTION_FLOAT_FLOAT:        return "SUBTRACTION_FLOAT_FLOAT";
        case INSTRUCTION_TYPE_MULTIPLICATION_INT_INT:         return "MULTIPLICATION_INT_INT";
        case INSTRUCTION_TYPE_MULTIPLICATION_INT_FLOAT:       return "MULTIPLICATION_INT_FLOAT";
        case INSTRUCTION_TYPE_MULTIPLICATION_FLOAT_INT:       return "MULTIPLICATION_FLOAT_INT";
        case INSTRUCTION_TYPE_MULTIPLICATION_FLOAT_FLOAT:     return "MULTIPLICATION_FLOAT_FLOAT";
        case INSTRUCTION_TYPE_DIVISION_INT_INT:               return "DIVISION_INT_INT";
        case INSTRUCTION_TYPE_DIVISION_INT_FLOAT:             return "DIVISION_INT_FLOAT";
        case INSTRUCTION_TYPE_DIVISION_FLOAT_INT:             return "DIVISION_FLOAT_INT";
        case INSTRUCTION_TYPE_DIVISION_FLOAT_FLOAT:           return "DIVISION_FLOAT_FLOAT";
        case INSTRUCTION_TYPE_MOD_INT_INT:                    return "MOD_INT_INT";
        case INSTRUCTION_TYPE_MOD_INT_FLOAT:                  return "MOD_INT_FLOAT";
        case INSTRUCTION_TYPE_MOD_FLOAT_INT:                  return "MOD_FLOAT_INT";
        case INSTRUCTION_TYPE_MOD_FLOAT_FLOAT:                return "MOD_FLOAT_FLOAT";
        case INSTRUCTION_TYPE_COMPARISON_SMALLER_INT_INT:     return "COMPARISON_SMALLER_INT_INT";
        case INSTRUCTION_TYPE_COMPARISON_SMALLER_INT_FLOAT:   return "COMPARISON_SMALLER_INT_FLOAT";
        case INSTRUCTION_TYPE_COMPARISON_SMALLER_FLOAT_INT:   return "COMPARISON_SMALLER_FLOAT_INT";
        case INSTRUCTION_TYPE_COMPARISON_SMALLER_FLOAT_FLOAT: return "COMPARISON_SMALLER_FLOAT_FLOAT";
        case INSTRUCTION_TYPE_COMPARISON_GREATER_INT_INT:     return "COMPARISON_GREATER_INT_INT";
        case INSTRUCTION_TYPE_COMPARISON_GREATER_INT_FLOAT:   return "COMPARISON_GREATER_INT_FLOAT";
        case INSTRUCTION_TYPE_COMPARISON_GREATER_FLOAT_INT:   return "COMPARISON_GREATER_FLOAT_INT";
        case INSTRUCTION_TYPE_COMPARISON_GREATER_FLOAT_FLOAT: return "COMPARISON_GREATER_FLOAT_FLOAT"; 
        case INSTRUCTION_TYPE_UNARY_MINUS_INT:                return "UNARY_MINUS_INT";
        case INSTRUCTION_TYPE_UNARY_MINUS_FLOAT:              return "UNARY_MINUS_FLOAT";
        case INSTRUCTION_TYPE_NEGATION:                       return "NEGATION";
        case INSTRUCTION_TYPE_EQUAL:                          return "EQUAL";
        default:                                              return "?";
    }
}




void printInstructions(Instruction *head) {
    if (!head) return;

    Instruction *aux = head;   

    while (aux) {
        char op1Str[64];
        char op2Str[64];
        char resultStr[64];

        aux->op1    ? strcpy(op1Str, aux->op1->name)       : strcpy(op1Str, "NULL");
        aux->op2    ? strcpy(op2Str, aux->op2->name)       : strcpy(op2Str, "NULL");
        aux->result ? strcpy(resultStr, aux->result->name) : strcpy(resultStr, "NULL");

        if (aux->op1 && (aux->op1->type == SYMBOL_TYPE_CONSTANT)) {
            switch (aux->op1->semanticType) {
                case SYMBOL_SEMANTIC_TYPE_INT:     snprintf(op1Str, 64, "%d", aux->op1->value.intValue);                          break;
                case SYMBOL_SEMANTIC_TYPE_FLOAT:   snprintf(op1Str, 64, "%f", aux->op1->value.floatValue);                        break;
                case SYMBOL_SEMANTIC_TYPE_BOOLEAN: snprintf(op1Str, 64, "%s", (aux->op1->value.booleanValue ? "true" : "false")); break;
            }
        }

        if (aux->op2 && (aux->op2->type == SYMBOL_TYPE_CONSTANT)) {
            switch (aux->op2->semanticType) {
                case SYMBOL_SEMANTIC_TYPE_INT:     snprintf(op2Str, 64, "%d", aux->op2->value.intValue);                          break;
                case SYMBOL_SEMANTIC_TYPE_FLOAT:   snprintf(op2Str, 64, "%f", aux->op2->value.floatValue);                        break;
                case SYMBOL_SEMANTIC_TYPE_BOOLEAN: snprintf(op2Str, 64, "%s", (aux->op2->value.booleanValue ? "true" : "false")); break;
            }
        }

        if (aux->result && (aux->result->type == SYMBOL_TYPE_CONSTANT)) {
            switch (aux->result->semanticType) {
                case SYMBOL_SEMANTIC_TYPE_INT:     snprintf(resultStr, 64, "%d", aux->result->value.intValue);                          break;
                case SYMBOL_SEMANTIC_TYPE_FLOAT:   snprintf(resultStr, 64, "%f", aux->result->value.floatValue);                        break;
                case SYMBOL_SEMANTIC_TYPE_BOOLEAN: snprintf(resultStr, 64, "%s", (aux->result->value.booleanValue ? "true" : "false")); break;
            }
        }

        if ((aux->type == INSTRUCTION_TYPE_BEGIN_METHOD) && 
            (aux->prev && (aux->prev->type == INSTRUCTION_GLOBAL_VAR_DECL))) printf("\n");

        printf("%s %s, %s, %s\n", getInstructionTypeString(aux->type), op1Str, op2Str, resultStr);
        
        if (aux->type == INSTRUCTION_TYPE_END_METHOD) printf("\n");
        aux = aux->next;
    }
}




void freeInstructionLinkedList(Instruction *head) {
    if (!head) return;

    while (head) {
        Instruction *next = head->next;

        if (head->op1)    freeSymbol(head->op1);
        if (head->op2)    freeSymbol(head->op2);
        if (head->result) freeSymbol(head->result);
        free(head);

        head = next;
    }
}




void generateIntermediateCodeNodeP(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node P visited")
    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);
}




void generateIntermediateCodeNodeGlobalDeclList(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node GlobalDeclList visited")

    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);
    if (node->children2) generateIntermediateCodeAux(node->children2, tail, labelCount);
}




void generateIntermediateCodeNodeVarDecl(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node VarDecl visited")
    // children1 (type) no hace falta analizarlo

    if (node->children2->type == AST_NODE_TYPE_ID) {

        if (!node->children2->symbol) printf("symbol is NULL\n");
        bool varIsGlobal = node->children2->symbol->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL;

        if (varIsGlobal) {
            InstructionConfig config = {
                .type   = INSTRUCTION_GLOBAL_VAR_DECL,
                .result = node->children2->symbol, 
            };

            Instruction *i = newInstruction(&config);
            insertInstruction(tail, i);
        }

        // sino, no generamos instrucciones (no hace falta para variables locales)
    }
    
    if (node->children2->type == AST_NODE_TYPE_LIST_ID) {
        generateIntermediateCodeAux(node->children2, tail, labelCount);
    }
}




void generateIntermediateCodeNodeMethodDeclList(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node MethodDeclList visited")
    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);
    if (node->children2) generateIntermediateCodeAux(node->children2, tail, labelCount);
}




void generateIntermediateCodeNodeMethodDecl(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node methodDecl visited")
    // obtener el simbolo del metodo
    Symbol *methodSymbol = NULL;
    
    if (node->children2) {
        methodSymbol = node->children2->symbol;
    }
    
    InstructionConfig configBeginMethod = {
        .type    = INSTRUCTION_TYPE_BEGIN_METHOD,
        .result  = methodSymbol,
    };

    Instruction *beginMethodInstruction = newInstruction(&configBeginMethod);

    insertInstruction(tail, beginMethodInstruction);

    //if (node->children1) generateIntermediateCodeAux(node->children1, tail);
    //if (node->children2) generateIntermediateCodeAux(node->children2, tail);
    
    // TODO: que hago al final con los params??
    //if (node->children2) generateIntermediateCodeAux(node->children3, tail); // no hace falta creo
    if (node->children4) generateIntermediateCodeAux(node->children4, tail, labelCount);

    InstructionConfig configEndMethod = {
        .type    = INSTRUCTION_TYPE_END_METHOD,
        .result  = methodSymbol,
    };

    Instruction *endMethodInstruction = newInstruction(&configEndMethod);

    insertInstruction(tail, endMethodInstruction);
}




void generateIntermediateCodeNodeListId(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node LisId visited")

    if (node->children1->symbol && (node->children1->symbol->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL)) {
        InstructionConfig config = {
            .type    = INSTRUCTION_GLOBAL_VAR_DECL,
            .result  = node->children1->symbol, 
        };

        Instruction *i = newInstruction(&config);
        insertInstruction(tail, i);
    }

    if ((node->children2->type == AST_NODE_TYPE_ID) && (node->children2->symbol->variableType == SYMBOL_VARIABLE_TYPE_GLOBAL)) {
        InstructionConfig config = {
            .type    = INSTRUCTION_GLOBAL_VAR_DECL,
            .result  = node->children2->symbol, 
        };

        Instruction *i = newInstruction(&config);
        insertInstruction(tail, i);
    }

    if (node->children2->type == AST_NODE_TYPE_LIST_ID) generateIntermediateCodeAux(node->children2, tail, labelCount);
}




void generateIntermediateCodeNodeId(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node Id visited")
    // no hace falta hacer nada
}




void generateIntermediateCodeNodeParams(AstNode *node, Instruction **tail, int *labelCount) {
    TODO("generateIntermediateCodeNodeParams() not implemented yet")
}




void generateIntermediateCodeNodeVoid(AstNode *node, Instruction **tail, int *labelCount) {
    TODO("generateIntermediateCodeNodeVoid() not implemented yet")
}




void generateIntermediateCodeNodeParam(AstNode *node, Instruction **tail, int *labelCount) {
    TODO("generateIntermediateCodeNodeParam() not implemented yet")
}




void generateIntermediateCodeNodeBlock(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node Block visited")
    // genero instruccion para abrir bloque?
    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);
}




void generateIntermediateCodeNodeBlockElems(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node BlockElems visited")
    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);
    if (node->children2) generateIntermediateCodeAux(node->children2, tail, labelCount);
}




void generateIntermediateCodeNodeStatements(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node Statements visited")
    
    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);
    if (node->children2) generateIntermediateCodeAux(node->children2, tail, labelCount);
}




void generateIntermediateCodeNodeType(AstNode *node, Instruction **tail, int *labelCount) {
    TODO("generateIntermediateCodeNodeType() not implemented yet")
}




void generateIntermediateCodeNodeAssignment(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node Assignment visited")
    
    // generar codigo para la expresion que asigno
    if (node->children2) generateIntermediateCodeAux(node->children2, tail, labelCount);

    InstructionType assignmentType;

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            assignmentType = INSTRUCTION_TYPE_ASSIGNMENT_INT_INT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            assignmentType = INSTRUCTION_TYPE_ASSIGNMENT_INT_FLOAT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            assignmentType = INSTRUCTION_TYPE_ASSIGNMENT_FLOAT_INT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            assignmentType = INSTRUCTION_TYPE_ASSIGNMENT_FLOAT_FLOAT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
            assignmentType = INSTRUCTION_TYPE_ASSIGNMENT_BOOL_BOOL;
        }

    InstructionConfig config = {
        .type   = assignmentType,
        .op1    = node->children2->symbol,
        .result = node->children1->symbol,
    };

    Instruction *i = newInstruction(&config);
    insertInstruction(tail, i);
}




void generateIntermediateCodeNodeMethodCall(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node MethodCallVisited")

    // primero generamos instrucciones de pusheo de los argumentos
    if (node->children2) {
        AstNode *aux = node->children2;

        while (aux) {
            if (aux->type == AST_NODE_TYPE_LIST_EXPR) {
                // push hijo izq
                generateIntermediateCodeAux(aux->children1, tail, labelCount);

                InstructionConfig config = {
                    .type   = INSTRUCTION_TYPE_PUSH_ARGUMENT,
                    .result = aux->children1->symbol,
                };

                Instruction *i = newInstruction(&config);
                insertInstruction(tail, i);

                // push los otros args si hay
                aux = aux->children2;
            } else {
                generateIntermediateCodeAux(aux->children2, tail, labelCount);

                InstructionConfig config = {
                    .type   = INSTRUCTION_TYPE_PUSH_ARGUMENT,
                    .result = aux->symbol,
                };

                Instruction *i = newInstruction(&config);
                insertInstruction(tail, i);

                aux = NULL; // ya no hay mas argumentos
            }
        }
    }

    InstructionConfig config = {
        .type   = INSTRUCTION_TYPE_CALL_METHOD,
        .result = node->children1->symbol,
    };

    Instruction *i = newInstruction(&config);
    insertInstruction(tail, i);
}




void generateIntermediateCodeNodeIfElse(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node IfElse visited")

    // instrucciones para evaluar la condicion
    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);

    // labels
    char labelCountStr[16];
    Symbol *elseBlockLabelSymbol = NULL;
    Symbol *endIfLabelSymbol     = NULL;
    Symbol *jumpZeroLabel        = NULL; // para saber a que etiqueta apuntar
                                         // depende de si el if tiene un else o no

    // label para el cuerpo del else
    if (node->children3) {
        char elseBlockName[64] = "label_";

        snprintf(labelCountStr, sizeof(labelCountStr), "%d", *labelCount);
        strcat(elseBlockName, labelCountStr);

        SymbolConfig elseBlockLabelConfig = {
            .type           = SYMBOL_TYPE_LABEL,
            .name           = strdup(elseBlockName),
            .value.intValue = (*labelCount),
        };

        elseBlockLabelSymbol = newSymbol(&elseBlockLabelConfig);

        (*labelCount)++;
    }

    // label para el fin del if (el cuerpo del if debe estar si o si)
    char endIfName[64] = "label_";

    snprintf(labelCountStr, sizeof(labelCountStr), "%d", *labelCount);
    strcat(endIfName, labelCountStr);

    SymbolConfig endIfLabelConfig = {
        .type           = SYMBOL_TYPE_LABEL,
        .name           = strdup(endIfName),
        .value.intValue = *labelCount,
    };

    endIfLabelSymbol = newSymbol(&endIfLabelConfig);

    (*labelCount)++;

    // instruccion del jump condicional
    jumpZeroLabel = endIfLabelSymbol;
    if (node->children3) jumpZeroLabel = elseBlockLabelSymbol;

    InstructionConfig jmpZeroConfig = {
        .type   = INSTRUCTION_TYPE_JMP_ZERO,
        .op1    = node->children1->symbol, // expresion de la condicion
        .result = jumpZeroLabel,
    };

    Instruction *jmpZeroInst = newInstruction(&jmpZeroConfig);
    insertInstruction(tail, jmpZeroInst);

    // instrucciones del bloque del if
    generateIntermediateCodeAux(node->children2, tail, labelCount);

    // instrucciones del else (si es que existe)
    if (node->children3) {
        InstructionConfig jmpEndIfConfig = {
            .type   = INSTRUCTION_TYPE_JMP,
            .result = endIfLabelSymbol,
        };

        Instruction *jmpEndIfInst = newInstruction(&jmpEndIfConfig);
        insertInstruction(tail, jmpEndIfInst);

        InstructionConfig elseBlockLabelInstConfig = {
            .type   = INSTRUCTION_TYPE_LABEL,
            .result = elseBlockLabelSymbol,
        };

        Instruction *elseBlockLabelInst = newInstruction(&elseBlockLabelInstConfig);
        insertInstruction(tail, elseBlockLabelInst);

        // instrucciones del cuerpo del else
        generateIntermediateCodeAux(node->children3, tail, labelCount);
    }

     InstructionConfig endIfLabelInstConfig = {
            .type   = INSTRUCTION_TYPE_LABEL,
            .result = endIfLabelSymbol,
        };

    Instruction *endIfLabelInst = newInstruction(&endIfLabelInstConfig);
    insertInstruction(tail, endIfLabelInst);
}




void generateIntermediateCodeNodeWhile(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node While visited")

    // etiqueta de inicio del while
    char beginWhileLabelName[64] = "label_";
    char labelCountStr[16];

    snprintf(labelCountStr, sizeof(labelCountStr), "%d", *labelCount);
    strcat(beginWhileLabelName, labelCountStr);

    SymbolConfig beginWhileLabelSymbolConfig = {
        .type           = SYMBOL_TYPE_LABEL,
        .name           = strdup(beginWhileLabelName),
        .value.intValue = (*labelCount),
    };

    Symbol *beginWhileLabelSymbol = newSymbol(&beginWhileLabelSymbolConfig);

    InstructionConfig beginWhileLabelInstConfig = {
        .type   = INSTRUCTION_TYPE_LABEL,
        .result = beginWhileLabelSymbol,
    };

    Instruction *beginWhileLabelInst = newInstruction(&beginWhileLabelInstConfig);
    insertInstruction(tail, beginWhileLabelInst);

    (*labelCount)++;

    // evaluar la expr de la condicion
    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);

    // etiqueta de fin del while
    char endWhileLabelName[64] = "label_";
    
    snprintf(labelCountStr, sizeof(labelCountStr), "%d", *labelCount);
    strcat(endWhileLabelName, labelCountStr);

    SymbolConfig endWhileLabelSymbolConfig = {
        .type           = SYMBOL_TYPE_LABEL,
        .name           = strdup(endWhileLabelName),
        .value.intValue = (*labelCount),
    };

    Symbol *endWhileLabelSymbol = newSymbol(&endWhileLabelSymbolConfig);

    InstructionConfig endWhileLabelInstConfig = {
        .type   = INSTRUCTION_TYPE_LABEL,
        .result = endWhileLabelSymbol,
    };

    // instruccion jmp condicional para saber si termina la iteracion o no
    InstructionConfig jmpZeroInstConfig = {
        .type   = INSTRUCTION_TYPE_JMP_ZERO,
        .op1    = node->children1->symbol,
        .result = endWhileLabelSymbol,
    };

    Instruction *jmpZeroInst = newInstruction(&jmpZeroInstConfig);
    insertInstruction(tail, jmpZeroInst);

    // instrucciones del cuerpo del while
    if (node->children2) generateIntermediateCodeAux(node->children2, tail, labelCount);

    // instruccion de jmp para volver al inicio del while
    InstructionConfig jmpWhileInstConfig = {
        .type   = INSTRUCTION_TYPE_JMP,
        .result = beginWhileLabelSymbol,
    };

    Instruction *jmpWhileInst = newInstruction(&jmpWhileInstConfig);
    insertInstruction(tail, jmpWhileInst);

    // inserto el label del fin del while
    Instruction *endWhileLabelInst = newInstruction(&endWhileLabelInstConfig);
    insertInstruction(tail, endWhileLabelInst);

    (*labelCount)++;
}




void generateIntermediateCodeNodeReturn(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node Return visited")

    Symbol *returnExprSymbol = NULL;

    if (node->children1) {
        generateIntermediateCodeAux(node->children1, tail, labelCount);
        returnExprSymbol = node->children1->symbol;
    }

    InstructionConfig config = {
        .type   = INSTRUCTION_TYPE_RETURN,
        .result = returnExprSymbol,
    };

    Instruction *i = newInstruction(&config);
    insertInstruction(tail, i);
}




void generateIntermediateCodeNodeListExpr(AstNode *node, Instruction **tail, int *labelCount) {
    TODO("generateIntermediateCodeNodeListExpr() not implemented yet")
}




void generateIntermediateCodeNodeIntLiteral(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node IntLiteral visited")
    // no habria que hacer nada
}




void generateIntermediateCodeNodeFloatLiteral(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node FloatLiteral visited")
    // no hace falta hacer nada
}




void generateIntermediateCodeNodeBoolLiteral(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node BoolLiteral visited")
    // no hace falta hacer nada
}




void generateIntermediateCodeNodeAddition(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node Addition visited")

    // analizar la expr del operando izquierdo
    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);

    // analizar la expr del operando derecho
    if (node->children2) generateIntermediateCodeAux(node->children2, tail, labelCount);

    // ver el tipo de suma (los casteos los haria en la generacion de assembly)
    InstructionType instructionAdditionType;

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            instructionAdditionType = INSTRUCTION_TYPE_ADDITION_INT_INT;
        }
    
    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            instructionAdditionType = INSTRUCTION_TYPE_ADDITION_INT_FLOAT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            instructionAdditionType = INSTRUCTION_TYPE_ADDITION_FLOAT_INT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            instructionAdditionType = INSTRUCTION_TYPE_ADDITION_FLOAT_FLOAT;
        }

    InstructionConfig config = {
        .type   = instructionAdditionType,
        .op1    = node->children1->symbol,
        .op2    = node->children2->symbol,
        .result = node->symbol,
    };

    Instruction *i = newInstruction(&config);
    insertInstruction(tail, i);
}




void generateIntermediateCodeNodeSubtraction(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node Subtraction visited")

    // analizar la expr del operando izquierdo
    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);

    // analizar la expr del operando derecho
    if (node->children2) generateIntermediateCodeAux(node->children2, tail, labelCount);

    // ver el tipo de suma (los casteos los haria en la generacion de assembly)
    InstructionType instructionSubtractionType;

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            instructionSubtractionType = INSTRUCTION_TYPE_SUBTRACTION_INT_INT;
        }
    
    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            instructionSubtractionType = INSTRUCTION_TYPE_SUBTRACTION_INT_FLOAT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            instructionSubtractionType = INSTRUCTION_TYPE_SUBTRACTION_FLOAT_INT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            instructionSubtractionType = INSTRUCTION_TYPE_SUBTRACTION_FLOAT_FLOAT;
        }

    InstructionConfig config = {
        .type   = instructionSubtractionType,
        .op1    = node->children1->symbol,
        .op2    = node->children2->symbol,
        .result = node->symbol,
    };

    Instruction *i = newInstruction(&config);
    insertInstruction(tail, i);
}




void generateIntermediateCodeNodeMultiplication(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node Multiplication visited")

    // analizar la expr del operando izquierdo
    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);

    // analizar la expr del operando derecho
    if (node->children2) generateIntermediateCodeAux(node->children2, tail, labelCount);

    // ver el tipo de suma (los casteos los haria en la generacion de assembly)
    InstructionType instructionMultiplicationType;

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            instructionMultiplicationType = INSTRUCTION_TYPE_MULTIPLICATION_INT_INT;
        }
    
    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            instructionMultiplicationType = INSTRUCTION_TYPE_MULTIPLICATION_INT_FLOAT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            instructionMultiplicationType = INSTRUCTION_TYPE_MULTIPLICATION_FLOAT_INT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            instructionMultiplicationType = INSTRUCTION_TYPE_MULTIPLICATION_FLOAT_FLOAT;
        }

    InstructionConfig config = {
        .type   = instructionMultiplicationType,
        .op1    = node->children1->symbol,
        .op2    = node->children2->symbol,
        .result = node->symbol,
    };

    Instruction *i = newInstruction(&config);
    insertInstruction(tail, i);
}




void generateIntermediateCodeNodeDivision(AstNode *node, Instruction **tail, int *labelCount) {
        DEBUG_IR("node Division visited")

    // analizar la expr del operando izquierdo
    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);

    // analizar la expr del operando derecho
    if (node->children2) generateIntermediateCodeAux(node->children2, tail, labelCount);

    // ver el tipo de suma (los casteos los haria en la generacion de assembly)
    InstructionType instructionDivisionType;

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            instructionDivisionType = INSTRUCTION_TYPE_DIVISION_INT_INT;
        }
    
    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            instructionDivisionType = INSTRUCTION_TYPE_DIVISION_INT_FLOAT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            instructionDivisionType = INSTRUCTION_TYPE_DIVISION_FLOAT_INT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            instructionDivisionType = INSTRUCTION_TYPE_DIVISION_FLOAT_FLOAT;
        }

    InstructionConfig config = {
        .type   = instructionDivisionType,
        .op1    = node->children1->symbol,
        .op2    = node->children2->symbol,
        .result = node->symbol,
    };

    Instruction *i = newInstruction(&config);
    insertInstruction(tail, i);
}




void generateIntermediateCodeNodeMod(AstNode *node, Instruction **tail, int *labelCount) {
        DEBUG_IR("node Mod visited")

    // analizar la expr del operando izquierdo
    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);

    // analizar la expr del operando derecho
    if (node->children2) generateIntermediateCodeAux(node->children2, tail, labelCount);

    // ver el tipo de suma (los casteos los haria en la generacion de assembly)
    InstructionType instructionModType;

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            instructionModType = INSTRUCTION_TYPE_MOD_INT_INT;
        }
    
    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            instructionModType = INSTRUCTION_TYPE_MOD_INT_FLOAT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            instructionModType = INSTRUCTION_TYPE_MOD_FLOAT_INT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            instructionModType = INSTRUCTION_TYPE_MOD_FLOAT_FLOAT;
        }

    InstructionConfig config = {
        .type   = instructionModType,
        .op1    = node->children1->symbol,
        .op2    = node->children2->symbol,
        .result = node->symbol,
    };

    Instruction *i = newInstruction(&config);
    insertInstruction(tail, i);
}




void generateIntermediateCodeNodeComparisonSmaller(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node ComparisonSmaller visited")

    // los operandos son expresiones aritmeticas
    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);
    if (node->children2) generateIntermediateCodeAux(node->children2, tail, labelCount);

    InstructionType comparisonSmallerType;

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            comparisonSmallerType = INSTRUCTION_TYPE_COMPARISON_SMALLER_INT_INT;
        }
    
    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            comparisonSmallerType = INSTRUCTION_TYPE_COMPARISON_SMALLER_INT_FLOAT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            comparisonSmallerType = INSTRUCTION_TYPE_COMPARISON_SMALLER_FLOAT_INT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            comparisonSmallerType = INSTRUCTION_TYPE_COMPARISON_SMALLER_FLOAT_FLOAT;
        }

    InstructionConfig config = {
        .type   = comparisonSmallerType,
        .op1    = node->children1->symbol,
        .op2    = node->children2->symbol,
        .result = node->symbol,
    };

    Instruction *i = newInstruction(&config);
    insertInstruction(tail, i);
}




void generateIntermediateCodeNodeComparisonGreater(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node ComparisonGreater visited")

    // los operandos son expresiones aritmeticas
    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);
    if (node->children2) generateIntermediateCodeAux(node->children2, tail, labelCount);

    InstructionType comparisonGreaterType;

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            comparisonGreaterType = INSTRUCTION_TYPE_COMPARISON_GREATER_INT_INT;
        }
    
    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            comparisonGreaterType = INSTRUCTION_TYPE_COMPARISON_GREATER_INT_FLOAT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT) {
            comparisonGreaterType = INSTRUCTION_TYPE_COMPARISON_GREATER_FLOAT_INT;
        }

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT &&
        node->children2->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) {
            comparisonGreaterType = INSTRUCTION_TYPE_COMPARISON_GREATER_FLOAT_FLOAT;
        }

    InstructionConfig config = {
        .type   = comparisonGreaterType,
        .op1    = node->children1->symbol,
        .op2    = node->children2->symbol,
        .result = node->symbol,
    };

    Instruction *i = newInstruction(&config);
    insertInstruction(tail, i);
}




void generateIntermediateCodeNodeEqual(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node Equal visited")

    // primero generar instrucciones para evaluar la expr de cada operando
    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);
    if (node->children2) generateIntermediateCodeAux(node->children2, tail, labelCount);

    InstructionConfig equalInstConfig = {
        .type   = INSTRUCTION_TYPE_EQUAL,
        .op1    = node->children1->symbol,
        .op2    = node->children2->symbol,
        .result = node->symbol,
    };
    
    Instruction *equalInst = newInstruction(&equalInstConfig);
    insertInstruction(tail, equalInst);
}




void generateIntermediateCodeNodeAnd(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node And visited")

    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);
    if (node->children2) generateIntermediateCodeAux(node->children2, tail, labelCount);

    InstructionConfig config = {
        .type   = INSTRUCTION_TYPE_AND,
        .op1    = node->children1->symbol,
        .op2    = node->children2->symbol,
        .result = node->symbol,
    };

    Instruction *i = newInstruction(&config);
    insertInstruction(tail, i);
}




void generateIntermediateCodeNodeOr(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node Or visited")

    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);
    if (node->children2) generateIntermediateCodeAux(node->children2, tail, labelCount);

    InstructionConfig config = {
        .type   = INSTRUCTION_TYPE_OR,
        .op1    = node->children1->symbol,
        .op2    = node->children2->symbol,
        .result = node->symbol,
    };

    Instruction *i = newInstruction(&config);
    insertInstruction(tail, i);
}




void generateIntermediateCodeNodeMinus(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node Minus visited")

    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);

    InstructionType unaryMinusType;

    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT)   unaryMinusType = INSTRUCTION_TYPE_UNARY_MINUS_INT;
    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_FLOAT) unaryMinusType = INSTRUCTION_TYPE_UNARY_MINUS_FLOAT;

    InstructionConfig config = {
        .type   = unaryMinusType,
        .op1    = node->children1->symbol,
        .result = node->symbol,
    };

    Instruction *i = newInstruction(&config);
    insertInstruction(tail, i);
}




void generateIntermediateCodeNodeNegation(AstNode *node, Instruction **tail, int *labelCount) {
    DEBUG_IR("node Negation visited")

    if (node->children1) generateIntermediateCodeAux(node->children1, tail, labelCount);

    InstructionConfig config = {
        .type   = INSTRUCTION_TYPE_NEGATION,
        .op1    = node->children1->symbol,
        .result = node->symbol,
    };

    Instruction *i = newInstruction(&config);
    insertInstruction(tail, i);
}
