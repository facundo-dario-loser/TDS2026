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

    generateIntermediateCodeAux(root, &tail);

    if (!tail)
        ERROR_IR("tail is NULL in generateIntermediateCodeAux()")

    head = tail;

    while (head->prev != NULL) {
        head = head->prev;
    }

    return head;
}




void generateIntermediateCodeAux(AstNode *root, Instruction **tail) {
    if (!root) return;

    switch (root->type) {
       case AST_NODE_TYPE_P:                  generateIntermediateCodeNodeP(root, tail);                 break;
       case AST_NODE_TYPE_GLOBAL_DECL_LIST:   generateIntermediateCodeNodeGlobalDeclList(root, tail);    break;
       case AST_NODE_TYPE_VAR_DECL:           generateIntermediateCodeNodeVarDecl(root, tail);           break;
       case AST_NODE_TYPE_METHOD_DECL_LIST:   generateIntermediateCodeNodeMethodDeclList(root, tail);    break;
       case AST_NODE_TYPE_METHOD_DECL:        generateIntermediateCodeNodeMethodDecl(root, tail);        break;
       case AST_NODE_TYPE_LIST_ID:            generateIntermediateCodeNodeListId(root, tail);            break;
       case AST_NODE_TYPE_ID:                 generateIntermediateCodeNodeId(root, tail);                break;
       case AST_NODE_TYPE_PARAMS:             generateIntermediateCodeNodeParams(root, tail);            break;
       case AST_NODE_TYPE_VOID:               generateIntermediateCodeNodeVoid(root, tail);              break;
       case AST_NODE_TYPE_PARAM:              generateIntermediateCodeNodeParam(root, tail);             break;
       case AST_NODE_TYPE_BLOCK:              generateIntermediateCodeNodeBlock(root, tail);             break;
       case AST_NODE_TYPE_BLOCK_ELEMS:        generateIntermediateCodeNodeBlockElems(root, tail);                  break;
       case AST_NODE_TYPE_STATEMENTS:         generateIntermediateCodeNodeStatements(root, tail);        break;
       case AST_NODE_TYPE_TYPE:               generateIntermediateCodeNodeType(root, tail);              break;
       case AST_NODE_TYPE_ASSIGNMENT:         generateIntermediateCodeNodeAssignment(root, tail);        break;
       case AST_NODE_TYPE_METHOD_CALL:        generateIntermediateCodeNodeMethodCall(root, tail);        break;
       case AST_NODE_TYPE_IF_ELSE:            generateIntermediateCodeNodeIfElse(root, tail);            break;
       case AST_NODE_TYPE_WHILE:              generateIntermediateCodeNodeWhile(root, tail);             break;
       case AST_NODE_TYPE_RETURN:             generateIntermediateCodeNodeReturn(root, tail);            break;
       case AST_NODE_TYPE_LIST_EXPR:          generateIntermediateCodeNodeListExpr(root, tail);          break;
       case AST_NODE_TYPE_INT_LITERAL:        generateIntermediateCodeNodeIntLiteral(root, tail);        break;
       case AST_NODE_TYPE_FLOAT_LITERAL:      generateIntermediateCodeNodeFloatLiteral(root, tail);      break;
       case AST_NODE_TYPE_BOOL_LITERAL:       generateIntermediateCodeNodeBoolLiteral(root, tail);       break;
       case AST_NODE_TYPE_ADDITION:           generateIntermediateCodeNodeAddition(root, tail);          break;
       case AST_NODE_TYPE_SUBTRACTION:        generateIntermediateCodeNodeSubtraction(root, tail);       break;
       case AST_NODE_TYPE_MULTIPLICATION:     generateIntermediateCodeNodeMultiplication(root, tail);    break;
       case AST_NODE_TYPE_DIVISION:           generateIntermediateCodeNodeDivision(root, tail);          break;
       case AST_NODE_TYPE_MOD:                generateIntermediateCodeNodeMod(root, tail);               break;
       case AST_NODE_TYPE_COMPARISON_SMALLER: generateIntermediateCodeNodeComparisonSmaller(root, tail); break;
       case AST_NODE_TYPE_COMPARISON_GREATER: generateIntermediateCodeNodeComparisonGreater(root, tail); break;
       case AST_NODE_TYPE_EQUAL:              generateIntermediateCodeNodeEqual(root, tail);             break;
       case AST_NODE_TYPE_AND:                generateIntermediateCodeNodeAnd(root, tail);               break;
       case AST_NODE_TYPE_OR:                 generateIntermediateCodeNodeOr(root, tail);                break;
       case AST_NODE_TYPE_MINUS:              generateIntermediateCodeNodeMinus(root, tail);             break;
       case AST_NODE_TYPE_NEGATION:           generateIntermediateCodeNodeNegation(root, tail);          break;
    }
}




char * getInstructionTypeString(InstructionType instType) {
    switch(instType) {
        case INSTRUCTION_TYPE_BEGIN_METHOD:           return "BEGIN_METHOD";
        case INSTRUCTION_TYPE_END_METHOD:             return "END_METHOD";
        case INSTRUCTION_GLOBAL_VAR_DECL:             return "GLOBAL_VAR_DECL";
        case INSTRUCTION_TYPE_LABEL:                  return "LABEL"; 
        case INSTRUCTION_TYPE_JMP:                    return "JMP";
        case INSTRUCTION_TYPE_JMP_ZERO:               return "JMP_ZERO";
        case INSTRUCTION_TYPE_ASSIGNMENT_INT_INT:     return "ASSIGNMENT_INT_INT";
        case INSTRUCTION_TYPE_ASSIGNMENT_INT_FLOAT:   return "ASSIGNMENT_INT_FLOAT";
        case INSTRUCTION_TYPE_ASSIGNMENT_FLOAT_INT:   return "ASSIGNMENT_FLOAT_INT";
        case INSTRUCTION_TYPE_ASSIGNMENT_FLOAT_FLOAT: return "ASSIGNMENT_FLOAT_FLOAT";
        case INSTRUCTION_TYPE_ASSIGNMENT_BOOL_BOOL:   return "ASSIGNMENT_BOOL_BOOL";   
        case INSTRUCTION_TYPE_ADDITION_INT_INT:       return "ADDITION_INT_INT";
        case INSTRUCTION_TYPE_ADDITION_INT_FLOAT:     return "ADDITION_INT_FLOAT";
        case INSTRUCTION_TYPE_ADDITION_FLOAT_INT:     return "ADDITION_FLOAT_INT";
        case INSTRUCTION_TYPE_ADDITION_FLOAT_FLOAT:   return "ADDITION_FLOAT_FLOAT";
        case INSTRUCTION_TYPE_AND:                    return "AND";
        case INSTRUCTION_TYPE_PUSH_ARGUMENT:          return "PUSH_ARGUMENT";
        case INSTRUCTION_TYPE_CALL_METHOD:            return "CALL_METHOD";
        case INSTRUCTION_TYPE_RETURN:                 return "RETURN";
        default:                                      return "?";
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




void generateIntermediateCodeNodeP(AstNode *node, Instruction **tail) {
    DEBUG_IR("node P visited")
    if (node->children1) generateIntermediateCodeAux(node->children1, tail);
}




void generateIntermediateCodeNodeGlobalDeclList(AstNode *node, Instruction **tail) {
    DEBUG_IR("node GlobalDeclList visited")

    if (node->children1) generateIntermediateCodeAux(node->children1, tail);
    if (node->children2) generateIntermediateCodeAux(node->children2, tail);
}




void generateIntermediateCodeNodeVarDecl(AstNode *node, Instruction **tail) {
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
        generateIntermediateCodeAux(node->children2, tail);
    }
}




void generateIntermediateCodeNodeMethodDeclList(AstNode *node, Instruction **tail) {
    DEBUG_IR("node MethodDeclList visited")
    if (node->children1) generateIntermediateCodeAux(node->children1, tail);
    if (node->children2) generateIntermediateCodeAux(node->children2, tail);
}




void generateIntermediateCodeNodeMethodDecl(AstNode *node, Instruction **tail) {
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
    if (node->children4) generateIntermediateCodeAux(node->children4, tail);

    InstructionConfig configEndMethod = {
        .type    = INSTRUCTION_TYPE_END_METHOD,
        .result  = methodSymbol,
    };

    Instruction *endMethodInstruction = newInstruction(&configEndMethod);

    insertInstruction(tail, endMethodInstruction);
}




void generateIntermediateCodeNodeListId(AstNode *node, Instruction **tail) {
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

    if (node->children2->type == AST_NODE_TYPE_LIST_ID) generateIntermediateCodeAux(node->children2, tail);
}




void generateIntermediateCodeNodeId(AstNode *node, Instruction **tail) {
    DEBUG_IR("node Id visited")
    // no hace falta hacer nada
}




void generateIntermediateCodeNodeParams(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeParams() not implemented yet")
}




void generateIntermediateCodeNodeVoid(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeVoid() not implemented yet")
}




void generateIntermediateCodeNodeParam(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeParam() not implemented yet")
}




void generateIntermediateCodeNodeBlock(AstNode *node, Instruction **tail) {
    DEBUG_IR("node Block visited")
    // genero instruccion para abrir bloque?
    if (node->children1) generateIntermediateCodeAux(node->children1, tail);
}




void generateIntermediateCodeNodeBlockElems(AstNode *node, Instruction **tail) {
    DEBUG_IR("node BlockElems visited")
    if (node->children1) generateIntermediateCodeAux(node->children1, tail);
    if (node->children2) generateIntermediateCodeAux(node->children2, tail);
}




void generateIntermediateCodeNodeStatements(AstNode *node, Instruction **tail) {
    DEBUG_IR("node Statements visited")
    
    if (node->children1) generateIntermediateCodeAux(node->children1, tail);
    if (node->children2) generateIntermediateCodeAux(node->children2, tail);
}




void generateIntermediateCodeNodeType(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeType() not implemented yet")
}




void generateIntermediateCodeNodeAssignment(AstNode *node, Instruction **tail) {
    DEBUG_IR("node Assignment visited")
    
    // generar codigo para la expresion que asigno
    if (node->children2) generateIntermediateCodeAux(node->children2, tail);

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




void generateIntermediateCodeNodeMethodCall(AstNode *node, Instruction **tail) {
    DEBUG("node MethodCallVisited")

    // primero generamos instrucciones de pusheo de los argumentos
    if (node->children2) {
        AstNode *aux = node->children2;

        while (aux) {
            if (aux->type == AST_NODE_TYPE_LIST_EXPR) {
                // push hijo izq
                generateIntermediateCodeAux(aux->children1, tail);

                InstructionConfig config = {
                    .type   = INSTRUCTION_TYPE_PUSH_ARGUMENT,
                    .result = aux->children1->symbol,
                };

                Instruction *i = newInstruction(&config);
                insertInstruction(tail, i);

                // push los otros args si hay
                aux = aux->children2;
            } else {
                generateIntermediateCodeAux(aux->children2, tail);

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




void generateIntermediateCodeNodeIfElse(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeIfElse() not implemented yet")
}




void generateIntermediateCodeNodeWhile(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeWhile() not implemented yet")
}




void generateIntermediateCodeNodeReturn(AstNode *node, Instruction **tail) {
    DEBUG_IR("node Return visited")

    Symbol *returnExprSymbol = NULL;

    if (node->children1) {
        generateIntermediateCodeAux(node->children1, tail);
        returnExprSymbol = node->children1->symbol;
    }

    InstructionConfig config = {
        .type   = INSTRUCTION_TYPE_RETURN,
        .result = returnExprSymbol,
    };

    Instruction *i = newInstruction(&config);
    insertInstruction(tail, i);
}




void generateIntermediateCodeNodeListExpr(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeListExpr() not implemented yet")
}




void generateIntermediateCodeNodeIntLiteral(AstNode *node, Instruction **tail) {
    DEBUG_IR("node IntLiteral visited")
    // no habria que hacer nada
}




void generateIntermediateCodeNodeFloatLiteral(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeFloatLiteral() not implemented yet")
}




void generateIntermediateCodeNodeBoolLiteral(AstNode *node, Instruction **tail) {
    DEBUG_IR("node BoolLiteral visited")
    // no hace falta hacer nada
}




void generateIntermediateCodeNodeAddition(AstNode *node, Instruction **tail) {
    DEBUG_IR("node Addition visited")

    // analizar la expr del operando izquierdo
    if (node->children1) generateIntermediateCodeAux(node->children1, tail);

    // analizar la expr del operando derecho
    if (node->children2) generateIntermediateCodeAux(node->children2, tail);

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




void generateIntermediateCodeNodeSubtraction(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeSubtraction() not implemented yet")
}




void generateIntermediateCodeNodeMultiplication(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeMultiplication() not implemented yet")
}




void generateIntermediateCodeNodeDivision(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeDivision() not implemented yet")
}




void generateIntermediateCodeNodeMod(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeMod() not implemented yet")
}




void generateIntermediateCodeNodeComparisonSmaller(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeComparisonSmaller() not implemented yet")
}




void generateIntermediateCodeNodeComparisonGreater(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeComparisonGreater() not implemented yet")
}




void generateIntermediateCodeNodeEqual(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeEqual() not implemented yet")
}




void generateIntermediateCodeNodeAnd(AstNode *node, Instruction **tail) {
    DEBUG("node And visited")

    if (node->children1) generateIntermediateCodeAux(node->children1, tail);
    if (node->children2) generateIntermediateCodeAux(node->children2, tail);

    InstructionConfig config = {
        .type   = INSTRUCTION_TYPE_AND,
        .op1    = node->children1->symbol,
        .op2    = node->children2->symbol,
        .result = node->symbol,
    };

    Instruction *i = newInstruction(&config);
    insertInstruction(tail, i);
}




void generateIntermediateCodeNodeOr(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeOr() not implemented yet")
}




void generateIntermediateCodeNodeMinus(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeMinus() not implemented yet")
}




void generateIntermediateCodeNodeNegation(AstNode *node, Instruction **tail) {
    TODO("generateIntermediateCodeNodeNegation() not implemented yet")
}
