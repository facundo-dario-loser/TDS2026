#include "semantic_analysis.h"

void semanticAnalysis(AstNode *root) {
    if (!root) ERROR_SEMANTIC("root node is NULL in semanticAnalysis()")
    
    SymbolTable st;
    st.top = NULL;
    semanticAnalysisAux(root, &st);
}

void semanticAnalysisAux(AstNode *root, SymbolTable *st) {
    if (!root) ERROR_SEMANTIC("root node is NULL in semanticAnalysisAux()")
    if (!st)   ERROR_SEMANTIC("symbol table is NULL in semanticAnalysisAux()")

    switch (root->type) {
        case AST_NODE_TYPE_P:                   analysisNodeP(root, st);                  break;                
        case AST_NODE_TYPE_GLOBAL_DECL_LIST:    analysisNodeGlobalDeclList(root, st);     break;    
        case AST_NODE_TYPE_VAR_DECL:            analysisNodeVarDecl(root, st);            break;            
        case AST_NODE_TYPE_METHOD_DECL_LIST:    analysisNodeMethodDeclList(root, st);     break;     
        case AST_NODE_TYPE_METHOD_DECL:         analysisNodeMethodDecl(root, st);         break;         
        case AST_NODE_TYPE_LIST_ID:             analysisNodeListId(root, st);             break;            
        case AST_NODE_TYPE_ID:                  analysisNodeId(root, st);                 break;                  
        case AST_NODE_TYPE_PARAMS:              analysisNodeParams(root, st);             break;              
        case AST_NODE_TYPE_VOID:                analysisNodeVoid(root, st);               break;               
        case AST_NODE_TYPE_PARAM:               analysisNodeParam(root, st);              break;               
        case AST_NODE_TYPE_BLOCK:               analysisNodeBlock(root, st);              break;
        case AST_NODE_TYPE_BLOCK_ELEMS:         analysisNodeBlockElems(root, st);         break;         
        case AST_NODE_TYPE_STATEMENTS:          analysisNodeStatements(root, st);         break;          
        case AST_NODE_TYPE_TYPE:                analysisNodeType(root, st);               break;                
        case AST_NODE_TYPE_ASSIGNMENT:          analysisNodeAssignment(root, st);         break;          
        case AST_NODE_TYPE_METHOD_CALL:         analysisNodeMethodCall(root, st);         break;        
        case AST_NODE_TYPE_IF_ELSE:             analysisNodeIfElse(root, st);             break;             
        case AST_NODE_TYPE_WHILE:               analysisNodeWhile(root, st);              break;               
        case AST_NODE_TYPE_RETURN:              analysisNodeReturn(root, st);             break;             
        case AST_NODE_TYPE_LIST_EXPR:           analysisNodeListExpr(root, st);           break;          
        case AST_NODE_TYPE_INT_LITERAL:         analysisNodeIntLiteral(root, st);         break;         
        case AST_NODE_TYPE_FLOAT_LITERAL:       analysisNodeFloatLiteral(root, st);       break;       
        case AST_NODE_TYPE_BOOL_LITERAL:        analysisNodeBoolLiteral(root, st);        break;       
        case AST_NODE_TYPE_ADDITION:            analysisNodeAddition(root, st);           break;            
        case AST_NODE_TYPE_SUBTRACTION:         analysisNodeSubtraction(root, st);        break;         
        case AST_NODE_TYPE_MULTIPLICATION:      analysisNodeMultiplication(root, st);     break;      
        case AST_NODE_TYPE_DIVISION:            analysisNodeDivision(root, st);           break;            
        case AST_NODE_TYPE_MOD:                 analysisNodeMod(root, st);                break;                 
        case AST_NODE_TYPE_COMPARISION_SMALLER: analysisNodeComparisionSmaller(root, st); break; 
        case AST_NODE_TYPE_COMPARISION_GREATER: analysisNodeComparisionGreater(root, st); break; 
        case AST_NODE_TYPE_EQUAL:               analysisNodeEqual(root, st);              break;               
        case AST_NODE_TYPE_AND:                 analysisNodeAnd(root, st);                break;                 
        case AST_NODE_TYPE_OR:                  analysisNodeOr(root, st);                 break;                  
        case AST_NODE_TYPE_MINUS:               analysisNodeMinus(root, st);              break;               
        case AST_NODE_TYPE_NEGATION:            analysisNodeNegation(root, st);           break;   
    }
}

void analysisNodeP(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node P visited")
    newLevel(st); // scope global
    if (node->children1) semanticAnalysisAux(node->children1, st);

    // chequear que exista un metodo llamado main
    Symbol *aux = st->top->head;
    bool flagMainExists = false;

    while (aux) {
        if (strcmp(aux->name, "main") == 0) {
            flagMainExists = true;
            break;
        }
        aux = aux->next;
    }

    if (!flagMainExists) ERROR_SEMANTIC("no method main was declared")

    closeLevel(st); // cerrar el scope global
}

void analysisNodeGlobalDeclList(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeGlobalDeclList not implemented yet")
}

void analysisNodeVarDecl(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node VarDecl visited")
    SymbolSemanticType     symbolSemanticType;
    AstNodeDeclarationType nodeDeclarationType;
    char                   *strSemanticType;

    if (node->children1) {
        nodeDeclarationType = node->children1->declarationType;
        switch (nodeDeclarationType) {
            case AST_NODE_DECLARATION_TYPE_INT:     {
                                                        symbolSemanticType = SYMBOL_SEMANTIC_TYPE_INT;
                                                        strSemanticType    = "int";
                                                    } break;
            case AST_NODE_DECLARATION_TYPE_FLOAT:   {
                                                        symbolSemanticType = SYMBOL_SEMANTIC_TYPE_FLOAT;
                                                        strSemanticType    = "float";
                                                    } break;
            case AST_NODE_DECLARATION_TYPE_BOOLEAN: {
                                                        symbolSemanticType = SYMBOL_SEMANTIC_TYPE_BOOLEAN;
                                                        strSemanticType    = "boolean";
                                                    } break;
        }
    }

    if (!node->children2) return;

    if (node->children2->type == AST_NODE_TYPE_ID) {
        // insertar el simbolo nuevo
        SymbolConfig varSymbolConfig = {
            .type                 = SYMBOL_TYPE_VARIABLE,
            .name                 = node->children2->value.strValue,
            .semanticType         = symbolSemanticType,
            .functionWhichBelongs = node->functionWhichBelongs, // lo arrastra de arriba   
        };

        bool res = insertSymbol(st, &varSymbolConfig);

        if (!res) ERROR_SEMANTIC("redeclared variable '%s %s' (line: %d)", strSemanticType, varSymbolConfig.name, node->line)
    }

    if (node->children2->type == AST_NODE_TYPE_LIST_ID) {
        // arrastrar el tipo de la declaracion en la lista y la funcion dentro de la cual estan
        node->children2->declarationType      = nodeDeclarationType;
        node->children2->functionWhichBelongs = node->functionWhichBelongs;
        semanticAnalysisAux(node->children2, st);
    }
}

void analysisNodeMethodDeclList(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node MethodDeclList visited")
    if (node->children1) semanticAnalysisAux(node->children1, st);
    if (node->children2) semanticAnalysisAux(node->children2, st);
}

void analysisNodeMethodDecl(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node MethodDecl visited")
    SymbolSemanticType returnType;
    char               *methodName;
    bool               hasReturn; // para saber si la funcion retorna algo
    char               *strReturnType;

    hasReturn = false;

    // tipo de retorno de la funcion
    if (node->children1->type == AST_NODE_TYPE_TYPE) {
        switch (node->children1->declarationType) {
            case AST_NODE_DECLARATION_TYPE_INT:     {
                                                        returnType    = SYMBOL_SEMANTIC_TYPE_INT;
                                                        strReturnType = "int";
                                                    } break;
            case AST_NODE_DECLARATION_TYPE_FLOAT:   {
                                                        returnType    = SYMBOL_SEMANTIC_TYPE_FLOAT;
                                                        strReturnType = "float"; 
                                                    }   break;
            case AST_NODE_DECLARATION_TYPE_BOOLEAN: {
                                                        returnType    = SYMBOL_SEMANTIC_TYPE_BOOLEAN;
                                                        strReturnType = "boolean";
                                                    } break;
        }
        hasReturn = true;
    }

    if (node->children1->type == AST_NODE_TYPE_VOID) {
        returnType = SYMBOL_SEMANTIC_TYPE_VOID;
    }

    // ID de la funcion
    //semanticAnalysisAux(node->children2, st); // hace falta?
    if (node->children2) methodName = node->children2->value.strValue;

    // parametros de la funcion
    Symbol *paramList = NULL;
    
    if (node->children3) {
        // main no puede tener ningun param
        if (strcmp(methodName, "main") == 0) ERROR_SEMANTIC("main can't have any parameters (line %d)", node->line)

        semanticAnalysisAux(node->children3, st);
        getSymbolParamList(node->children3, &paramList);
    }

    // primero inserta el simbolo de la funcion y luego agregar los parametros 
    SymbolConfig methodSymbolConfig = {
        .type         = SYMBOL_TYPE_METHOD,
        .name         = methodName,
        .parameters   = paramList,
        .semanticType = returnType,
    };

    bool res = insertSymbol(st, &methodSymbolConfig);

    if (!res) ERROR_SEMANTIC("redeclared function '%s' (line: %d)", methodName, node->line)

    Symbol *functionSymbol = searchSymbol(st, methodSymbolConfig.name);

    node->children2->symbol = functionSymbol; // solo los nodos ID apuntan a simbolos
                                              // aunque no haria falta guardar en la declaracion
     
    PRINT_SYMBOL_METHOD_PARAM_LIST(functionSymbol)

    // cuerpo de la funcion
    if (node->children4) {
        // las declaraciones de variables y sentencias del bloque pertencen a esta funcion
        node->children4->functionWhichBelongs = functionSymbol;
        semanticAnalysisAux(node->children4, st);
    }

    // TODO:
    if (hasReturn) {
        // chequear si no retorna nada
        if (!checkIfFunctionHasReturn(node->children4)) 
            ERROR_SEMANTIC("function signature of '%s' says it returns an '%s', but the body miss return's statatements (line: %d)", functionSymbol->name, strReturnType, node->line)
    }

    // si la funcion no retorna nada el chequeo de que no intente retornar
    // algo se hace en la funcion de analisis del nodo return
}

void analysisNodeListId(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeListIdVoid not implemented yet")
}

void analysisNodeId(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node Id visited")
    Symbol *idSymbol = searchSymbol(st, node->value.strValue);

    if (!idSymbol) ERROR_SEMANTIC("variable '%s' was not declared (line: %d)", node->value.strValue, node->line)
    
    node->symbol = idSymbol;
}

void analysisNodeParams(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node Params visited")
    if (node->children1) semanticAnalysisAux(node->children1, st);
    if (node->children2) semanticAnalysisAux(node->children2, st);
}

void analysisNodeVoid(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeVoid not implemented yet")
}

void analysisNodeParam(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node Param visited")
    SymbolSemanticType symbolSemanticType;

    switch (node->children1->declarationType) {
        case AST_NODE_DECLARATION_TYPE_INT:     symbolSemanticType = SYMBOL_SEMANTIC_TYPE_INT;     break;
        case AST_NODE_DECLARATION_TYPE_FLOAT:   symbolSemanticType = SYMBOL_SEMANTIC_TYPE_FLOAT;   break;
        case AST_NODE_DECLARATION_TYPE_BOOLEAN: symbolSemanticType = SYMBOL_SEMANTIC_TYPE_BOOLEAN; break;
    }

    char *symbolName = node->children2->value.strValue;

    SymbolConfig config = (SymbolConfig){
        .type         = SYMBOL_TYPE_VARIABLE,
        .name         = symbolName,
        .semanticType = symbolSemanticType,
    };

    Symbol *paramSymbol = newSymbol(&config);
    node->children2->symbol = paramSymbol;
}

void analysisNodeBlock(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node Block visited")
    newLevel(st);
    if (node->children1) {
        // solamente abjo la funcion si el hijo es un block elems (porque se que puede haber mas decl de var)
        if (!(node->children1->type == AST_NODE_TYPE_STATEMENTS)) {
            node->children1->functionWhichBelongs = node->functionWhichBelongs; // baja la funcion
        }
        semanticAnalysisAux(node->children1, st);
    }
    closeLevel(st); 
}

void analysisNodeBlockElems(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node BlockElems visited")
    if (node->children1) {
        node->children1->functionWhichBelongs = node->functionWhichBelongs;
        semanticAnalysisAux(node->children1, st);
    }

    if (node->children2) {
        // solamente abjo la funcion si el hijo es un block elems (porque se que puede haber mas decl de var)
        if (!(node->children2->type == AST_NODE_TYPE_STATEMENTS)) {
            node->children2->functionWhichBelongs = node->functionWhichBelongs;
        }
        semanticAnalysisAux(node->children2, st);
    }
}

void analysisNodeStatements(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node Statements visited")
    if (node->children1) {
        semanticAnalysisAux(node->children1, st);
    }

    if (node->children2) {
        semanticAnalysisAux(node->children2, st);
    }
}

void analysisNodeType(AstNode *node, SymbolTable *st) {
     TODO("analysisNodeType not implemented yet")
}

void analysisNodeAssignment(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node Assigment visited")
    // ver que el tipo de la expresion de la derecha tenga el mismo tipo que el id de la izquierda
    SymbolSemanticType idType;
    SymbolSemanticType exprType;
    char               *idTypeStr;
    char               *exprTypeStr;

    semanticAnalysisAux(node->children1, st);
    idType    = node->children1->symbol->semanticType;
    idTypeStr = getSemanticTypeString(idType);

    semanticAnalysisAux(node->children2, st);
    if (node->children2) {
        exprType    = node->children2->symbol->semanticType;
        exprTypeStr = getSemanticTypeString(exprType);
    }

    if (idType != exprType) {
        if ((idType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (exprType == SYMBOL_SEMANTIC_TYPE_INT)) {
            // castear int a float
        } else if ((idType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (exprType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
            // castear float a int
        } else {
            ERROR_SEMANTIC("invalid assigment -> '%s' type is %s, but the right expression type is %s (line: %d)", node->children1->value.strValue, idTypeStr, exprTypeStr, node->line)
        }
    }
}

void analysisNodeMethodCall(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeMethodCall not implemented yet")
}

void analysisNodeIfElse(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeIfElse not implemented yet")
}

void analysisNodeWhile(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeWhile not implemented yet")
}

void analysisNodeReturn(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeReturn not implemented yet")
}

void analysisNodeListExpr(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeListExpr not implemented yet")
}

void analysisNodeIntLiteral(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node IntLiteral visited")
    char *intLiteralName = "const";

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_CONSTANT,
        .name         = intLiteralName,
        .semanticType = SYMBOL_SEMANTIC_TYPE_INT,
        .value        = node->value.intValue,
    };

    Symbol *intLiteralSymbol = newSymbol(&config);
    node->symbol             = intLiteralSymbol;
}

void analysisNodeFloatLiteral(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeFloatLiteral not implemented yet")
}

void analysisNodeBoolLiteral(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeBoolLiteral not implemented yet")
}

void analysisNodeAddition(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node Addition visited")
    semanticAnalysisAux(node->children1, st);
    semanticAnalysisAux(node->children2, st);

    // casteos
    Symbol *leftExprSymbol  = node->children1->symbol;
    Symbol *rightExprSymbol = node->children2->symbol;
    
    SymbolSemanticType exprSemanticType;

    // chequear que ninguna expresion sea logica/booleana
    if (leftExprSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("left expression of additon (+) is boolean (line: %d)", node->line)
    }

    if (rightExprSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("right expression of additon (+) is boolean (line: %d)", node->line)
    }

    // siempre casteo a float si son distintos
    if (leftExprSymbol->semanticType == rightExprSymbol->semanticType) {
        exprSemanticType = leftExprSymbol->semanticType;
    } else {
        exprSemanticType = SYMBOL_SEMANTIC_TYPE_FLOAT;
    }

    // por ahora solo se llama temp, luego le pondre ti con i de 0..N
    char *tempName = "temp";

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .name         = tempName,
        .semanticType = exprSemanticType,
    };

    Symbol *exprAdditionSymbol = newSymbol(&config);
    node->symbol = exprAdditionSymbol;
}

void analysisNodeSubtraction(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeSubtraction not implemented yet")
}

void analysisNodeMultiplication(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeMultiplication not implemented yet")
}

void analysisNodeDivision(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeDivision not implemented yet")
}

void analysisNodeMod(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeMod not implemented yet")
}

void analysisNodeComparisionSmaller(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeComparisionSmaller not implemented yet")
}

void analysisNodeComparisionGreater(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeComparisionGreater not implemented yet")
}

void analysisNodeEqual(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeEqual not implemented yet")
}

void analysisNodeAnd(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeAnd not implemented yet")
}

void analysisNodeOr(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeOr not implemented yet")
}

void analysisNodeMinus(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeMinus not implemented yet")
}

void analysisNodeNegation(AstNode *node, SymbolTable *st) {
    TODO("analysisNodeNegation not implemented yet")
}

// chequea que haya un return en todas las ramas
bool checkIfFunctionHasReturn(AstNode *node) {
    if (!node) return false;

    switch (node->type) {
        case AST_NODE_TYPE_BLOCK: {
            if (node->children1) return checkIfFunctionHasReturn(node->children1);
            return false;
        } break;

        case AST_NODE_TYPE_BLOCK_ELEMS: {
            // el hijo izq es una declaracion y por ende la ignoramos
            if (node->children2) return checkIfFunctionHasReturn(node->children2);
            return false;
        } break;

        case AST_NODE_TYPE_STATEMENTS: {
            bool leftChildrenHasReturn  = false;
            bool rightChildrenHasReturn = false;
            if (node->children1) leftChildrenHasReturn  = checkIfFunctionHasReturn(node->children1);
            if (node->children2) rightChildrenHasReturn = checkIfFunctionHasReturn(node->children2);
            return leftChildrenHasReturn || rightChildrenHasReturn;  
        } break;

        // debe haber return en ambas ramas. En un 'if' solo sin 'else' se retornaria false
        case AST_NODE_TYPE_IF_ELSE: {
            bool leftChildrenHasReturn  = false;
            bool rightChildrenHasReturn = false;
            if (node->children2) leftChildrenHasReturn  = checkIfFunctionHasReturn(node->children2);
            if (node->children3) rightChildrenHasReturn = checkIfFunctionHasReturn(node->children3);
            return leftChildrenHasReturn && rightChildrenHasReturn;
        } break;

        case AST_NODE_TYPE_RETURN: return true;

        default: return false;
    }
}

void getSymbolParamList(AstNode *node, Symbol **symbolParamList) {
    if (!node) return;

    switch (node->type) {
        case AST_NODE_TYPE_PARAM: {
            // inserta a la cabeza
            node->children2->symbol->next = *symbolParamList;
            *symbolParamList = node->children2->symbol;
        } break;

        case AST_NODE_TYPE_PARAMS: {
            getSymbolParamList(node->children1, symbolParamList);
            getSymbolParamList(node->children2, symbolParamList);
        } break;
        
        default: return;
    }
}

void printMethodParamList(Symbol *methodSymbol) {
    if (!(methodSymbol->type == SYMBOL_TYPE_METHOD)) return;

    printf("%s params: ", methodSymbol->name);

    Symbol *aux = methodSymbol->parameters;

    while (aux) {
        printf("[%s] -> ", aux->name);
        aux = aux->next;
    }

    printf("NULL\n");
}
