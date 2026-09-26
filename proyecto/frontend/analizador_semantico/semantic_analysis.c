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

    if (!flagMainExists) ERROR_SEMANTIC("method main was not declared")

    closeLevel(st); // cerrar el scope global
}

void analysisNodeGlobalDeclList(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node GlobalDeclList visited")
    if (node->children1) semanticAnalysisAux(node->children1, st);
    if (node->children2) semanticAnalysisAux(node->children2, st);
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
        };

        bool res = insertSymbol(st, &varSymbolConfig);

        if (!res) ERROR_SEMANTIC("redeclared variable '%s %s' (line: %d)", strSemanticType, varSymbolConfig.name, node->line)
    }

    if (node->children2->type == AST_NODE_TYPE_LIST_ID) {
        // arrastrar el tipo de la declaracion en la lista
        node->children2->declarationType = nodeDeclarationType;
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
        .type           = SYMBOL_TYPE_METHOD,
        .name           = methodName,
        .parameters     = paramList,
        .semanticType   = returnType,
    };

    bool res = insertSymbol(st, &methodSymbolConfig);

    if (!res) ERROR_SEMANTIC("redeclared function '%s' (line: %d)", methodName, node->line)

    Symbol *functionSymbol = searchSymbol(st, methodSymbolConfig.name);

    node->children2->symbol = functionSymbol; // solo los nodos ID apuntan a simbolos
                                              // aunque no haria falta guardar en la declaracion
     
    PRINT_SYMBOL_METHOD_PARAM_LIST(functionSymbol)

    // cuerpo de la funcion
    if (node->children4) {
        node->children4->isFunctionBlock = true;
        semanticAnalysisAux(node->children4, st);
    }

    // chequear que si la funcion retorna algo entonces en el cuerpo esten los respectivos return's
    if (hasReturn) {
        if (!checkIfFunctionHasReturn(node->children4)) 
            ERROR_SEMANTIC("function signature of '%s' says it returns an '%s', but the body miss return's statatements (line: %d)", functionSymbol->name, strReturnType, node->line)
    }

    // si la funcion no retorna nada el chequeo de que no intente retornar
    // algo se hace en la funcion de analisis del nodo return
}

void analysisNodeListId(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node ListId visited")
    SymbolSemanticType     symbolSemanticType;
    AstNodeDeclarationType nodeDeclarationType;
    char                   *strSemanticType;

    if (node->children1) {
        nodeDeclarationType = node->declarationType;
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

        SymbolConfig varSymbolConfig = {
            .type                 = SYMBOL_TYPE_VARIABLE,
            .name                 = node->children1->value.strValue,
            .semanticType         = symbolSemanticType,
        };

        bool res = insertSymbol(st, &varSymbolConfig);

        if (!res) ERROR_SEMANTIC("redeclared variable '%s %s' (line: %d)", strSemanticType, varSymbolConfig.name, node->line)
    }

    if (!node->children2) return;

    if (node->children2->type == AST_NODE_TYPE_ID) {
        // insertar el simbolo nuevo
        SymbolConfig varSymbolConfig = {
            .type                 = SYMBOL_TYPE_VARIABLE,
            .name                 = node->children2->value.strValue,
            .semanticType         = symbolSemanticType,
        };

        bool res = insertSymbol(st, &varSymbolConfig);

        if (!res) ERROR_SEMANTIC("redeclared variable '%s %s' (line: %d)", strSemanticType, varSymbolConfig.name, node->line)
    }

    if (node->children2->type == AST_NODE_TYPE_LIST_ID) {
        // arrastrar el tipo de la declaracion en la lista
        node->children2->declarationType = nodeDeclarationType;
        semanticAnalysisAux(node->children2, st);
    }
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
    
    if (node->isFunctionBlock) {
        // meter los simbolos de los parametros en el nivel actual
        // la primer funcion del nivel anterior es de la cual debemos
        // extraer los parametros
        Symbol *functionSymbol          = st->top->next->head;
        Symbol *functionSymbolParamList = functionSymbol->parameters;

        // si tenia algun param insertarlo en la tabla de simbolos
        if (functionSymbolParamList) insertSymbolListInCurrenLevel(st, functionSymbolParamList);
    }

    if (node->children1) {
        semanticAnalysisAux(node->children1, st);
    }
    closeLevel(st); 
}

void analysisNodeBlockElems(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node BlockElems visited")
    if (node->children1) semanticAnalysisAux(node->children1, st);
    if (node->children2) semanticAnalysisAux(node->children2, st);
}

void analysisNodeStatements(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node Statements visited")
    if (node->children1) semanticAnalysisAux(node->children1, st);
    if (node->children2) semanticAnalysisAux(node->children2, st);
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
    exprType    = node->children2->symbol->semanticType;
    exprTypeStr = getSemanticTypeString(exprType);

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
    DEBUG_SEMANTIC("node MethodCall visited")

    // buscar el simbolo de la primer funcion con el nombre dado
    // en la tabla de simbolos (explorando hacia afuera)

    semanticAnalysisAux(node->children1, st);
    Symbol *methodSymbol = searchMethodSymbol(st, node->children1->value.strValue);

    if (node->children2) semanticAnalysisAux(node->children2, st);

    // chequear que se pasen argumentos de los mismos tipos que los 
    // parametros y misma cantidad
    AstNode *aux         = node;
    Symbol  *paramList   = methodSymbol->parameters;
    int     currentArg   = 1; // argumento actual que se tiene que chequear

    while (aux) {
        
        switch (aux->type) {
            case AST_NODE_TYPE_METHOD_CALL: {
                if (!aux->children2 && paramList) 
                    ERROR_SEMANTIC("method '%s' was called without any arguments (line: %d)", methodSymbol->name, node->line)

                if (aux->children2 && !paramList)
                    ERROR_SEMANTIC("method '%s' doesn't have any parameters, but it was called with arguments (line: %d)", methodSymbol->name, node->line)

                aux = aux->children2; // ir a al nodo list expr
            } break;
            
            case AST_NODE_TYPE_LIST_EXPR: {
                // chequear con la expr (hijo izq)
                if (!paramList)
                    ERROR_SEMANTIC("the method '%s' was called with more arguments than the number of parameters that it has (line: %d)", methodSymbol->name, node->line)

                if (aux->children1->symbol->semanticType != paramList->semanticType)
                    ERROR_SEMANTIC("the type of parameter number %d in method '%s' is %s, but the argument passed is of type %s (line: %d)", currentArg, methodSymbol->name, getSemanticTypeString(paramList->semanticType), getSemanticTypeString(aux->children1->symbol->semanticType), node->line)
                
                paramList = paramList->next;
                currentArg++;
                aux = aux->children2; // ir al prox nodo list expr o expr
            } break;
            
            // es una expr (es el ultimo argumetno pasado)
            default: {
                if (!paramList)
                    ERROR_SEMANTIC("the method '%s' was called with more arguments than the number of parameters that it has (line: %d)", methodSymbol->name, node->line)

                if (aux->symbol->semanticType != paramList->semanticType)
                    ERROR_SEMANTIC("the type of parameter number %d in method '%s' is %s, but the argument passed is of type %s (line: %d)", currentArg, methodSymbol->name, getSemanticTypeString(paramList->semanticType), getSemanticTypeString(aux->symbol->semanticType), node->line)
                
                paramList = paramList->next;
                aux       = NULL; // ya no hay mas argumentos

                // este deberia de haber sido el ultimo arg pasado y por ende ultimo param
                if (paramList)
                    ERROR_SEMANTIC("method '%s' was called without enough arguments (line: %d)", methodSymbol->name, node->line)
            } break;
        }
    }

    // crear simbolo del temporal para guardar el valor luego de llamar 
    // al metodo si es que tiene retorno

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .name         = "temp",
        .semanticType = methodSymbol->semanticType,
    };

    Symbol *methodCallSymbol = newSymbol(&config);
    node->symbol             = methodCallSymbol;
}

void analysisNodeIfElse(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node IfElse visited")

    // chequear que la expr de la condicion sea booleana
    semanticAnalysisAux(node->children1, st);
    if (node->children1->symbol->semanticType != SYMBOL_SEMANTIC_TYPE_BOOLEAN)
        ERROR_SEMANTIC("condition in the if statement must be a logic/boolean expression (line: %d)", node->line)
    
    if (node->children2) semanticAnalysisAux(node->children2, st);
    if (node->children3) semanticAnalysisAux(node->children3, st);
}

void analysisNodeWhile(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node While visited")
    if (node->children1) semanticAnalysisAux(node->children1, st);

    // chequear que la expr de la condicion sea boolean
    if (node->children1->symbol->semanticType != SYMBOL_SEMANTIC_TYPE_BOOLEAN)
        ERROR_SEMANTIC("the expression on the condition in the while statement must be boolean, but it is %s (line: %d)", getSemanticTypeString(node->children1->symbol->semanticType), node->line)

    if (node->children2) semanticAnalysisAux(node->children2, st);
}

void analysisNodeReturn(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node Return visited")

    SymbolSemanticType returnExprSemanticType;
    SymbolSemanticType methodSemanticType;

    // chequear si retorna una expr y el tipo de la expr que retorna
    if (node->children1) {
        semanticAnalysisAux(node->children1, st);
        returnExprSemanticType = node->children1->symbol->semanticType;
    } else {
        returnExprSemanticType = SYMBOL_SEMANTIC_TYPE_VOID;
    }

    // ver si la funcion retorna una expr y su tipo
    // la funcion debe ser la primera que nos encontremos si recorremos
    // la tabla de simbolos avanzando hacia niveles inferiores (exteriores)

    Level *aux       = st->top;
    bool methodFound = false;
    char *methodName;

    while (aux && !methodFound) {
        if (aux->head && (aux->head->type == SYMBOL_TYPE_METHOD)) {
            methodName         = aux->head->name;
            methodSemanticType = aux->head->semanticType;
            break;
        }
        aux = aux->next;
    }

    // chequear si conciden los tipos
    if ((methodSemanticType == SYMBOL_SEMANTIC_TYPE_VOID) && 
        (returnExprSemanticType != SYMBOL_SEMANTIC_TYPE_VOID)) {
            ERROR_SEMANTIC("method %s doesn't return anything but there's a return with an '%s' expression (line: %d)", methodName, getSemanticTypeString(returnExprSemanticType), node->line)
        }
    
    if ((methodSemanticType != SYMBOL_SEMANTIC_TYPE_VOID) && 
        (returnExprSemanticType == SYMBOL_SEMANTIC_TYPE_VOID)) {
            ERROR_SEMANTIC("method '%s' returns an expression of type %s, but there's an empty return (line: %d)", methodName, getSemanticTypeString(methodSemanticType), node->line)
        }

    if ((methodSemanticType != SYMBOL_SEMANTIC_TYPE_VOID) &&
        (returnExprSemanticType != SYMBOL_SEMANTIC_TYPE_VOID)) {
            if (methodSemanticType != returnExprSemanticType) {
                ERROR_SEMANTIC("method '%s' returns an expression of type %s, but there's a return with an expression of type %s (line: %d)", methodName, getSemanticTypeString(methodSemanticType), getSemanticTypeString(returnExprSemanticType), node->line)
            }
        }
}

void analysisNodeListExpr(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node ListExpr visited")

    if (node->children1) semanticAnalysisAux(node->children1, st);
    if (node->children2) semanticAnalysisAux(node->children2, st);
}

void analysisNodeIntLiteral(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node IntLiteral visited")
    char *intLiteralName = "const";

    SymbolConfig config = {
        .type           = SYMBOL_TYPE_CONSTANT,
        .name           = intLiteralName,
        .semanticType   = SYMBOL_SEMANTIC_TYPE_INT,
        .value.intValue = node->value.intValue,
    };

    Symbol *intLiteralSymbol = newSymbol(&config);
    node->symbol             = intLiteralSymbol;
}

void analysisNodeFloatLiteral(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node FloatLiteral visited")
    char *intLiteralName = "const";

    SymbolConfig config = {
        .type             = SYMBOL_TYPE_CONSTANT,
        .name             = intLiteralName,
        .semanticType     = SYMBOL_SEMANTIC_TYPE_FLOAT,
        .value.floatValue = node->value.floatValue,
    };

    Symbol *floatLiteralSymbol = newSymbol(&config);
    node->symbol               = floatLiteralSymbol;
}

void analysisNodeBoolLiteral(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node BoolLiteral visited")
    char *intLiteralName = "const";

    SymbolConfig config = {
        .type               = SYMBOL_TYPE_CONSTANT,
        .name               = intLiteralName,
        .semanticType       = SYMBOL_SEMANTIC_TYPE_BOOLEAN,
        .value.booleanValue = node->value.booleanValue,
    };

    Symbol *boolLiteralSymbol = newSymbol(&config);
    node->symbol              = boolLiteralSymbol;
}

void analysisNodeAddition(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node Addition visited")
    semanticAnalysisAux(node->children1, st);
    semanticAnalysisAux(node->children2, st);

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

    if (leftExprSymbol->semanticType == rightExprSymbol->semanticType) {
        exprSemanticType = leftExprSymbol->semanticType;
    } else {
        // siempre casteo a float si son distintos
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
    node->symbol               = exprAdditionSymbol;
}

void analysisNodeSubtraction(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node Subtraction visited")
    semanticAnalysisAux(node->children1, st);
    semanticAnalysisAux(node->children2, st);

    Symbol *leftExprSymbol  = node->children1->symbol;
    Symbol *rightExprSymbol = node->children2->symbol;
    
    SymbolSemanticType exprSemanticType;

    // chequear que ninguna expresion sea logica/booleana
    if (leftExprSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("left expression of subtraction (-) is boolean (line: %d)", node->line)
    }

    if (rightExprSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("right expression of subtraction (-) is boolean (line: %d)", node->line)
    }

    if (leftExprSymbol->semanticType == rightExprSymbol->semanticType) {
        exprSemanticType = leftExprSymbol->semanticType;
    } else {
        // siempre casteo a float si son distintos
        exprSemanticType = SYMBOL_SEMANTIC_TYPE_FLOAT;
    }

    // por ahora solo se llama temp, luego le pondre ti con i de 0..N
    char *tempName = "temp";

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .name         = tempName,
        .semanticType = exprSemanticType,
    };

    Symbol *exprSubtractionSymbol = newSymbol(&config);
    node->symbol                  = exprSubtractionSymbol;
}

void analysisNodeMultiplication(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node Multiplication visited")
    semanticAnalysisAux(node->children1, st);
    semanticAnalysisAux(node->children2, st);

    Symbol *leftExprSymbol  = node->children1->symbol;
    Symbol *rightExprSymbol = node->children2->symbol;
    
    SymbolSemanticType exprSemanticType;

    // chequear que ninguna expresion sea logica/booleana
    if (leftExprSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("left expression of multiplication (*) is boolean (line: %d)", node->line)
    }

    if (rightExprSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("right expression of multiplication (*) is boolean (line: %d)", node->line)
    }

    if (leftExprSymbol->semanticType == rightExprSymbol->semanticType) {
        exprSemanticType = leftExprSymbol->semanticType;
    } else {
        // siempre casteo a float si son distintos
        exprSemanticType = SYMBOL_SEMANTIC_TYPE_FLOAT;
    }

    // por ahora solo se llama temp, luego le pondre ti con i de 0..N
    char *tempName = "temp";

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .name         = tempName,
        .semanticType = exprSemanticType,
    };

    Symbol *exprMultiplicationSymbol = newSymbol(&config);
    node->symbol                     = exprMultiplicationSymbol;
}

void analysisNodeDivision(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node Division visited")
    semanticAnalysisAux(node->children1, st);
    semanticAnalysisAux(node->children2, st);

    Symbol *leftExprSymbol  = node->children1->symbol;
    Symbol *rightExprSymbol = node->children2->symbol;
    
    SymbolSemanticType exprSemanticType;

    // chequear que ninguna expresion sea logica/booleana
    if (leftExprSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("left expression of division (/) is boolean (line: %d)", node->line)
    }

    if (rightExprSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("right expression of division (/) is boolean (line: %d)", node->line)
    }

    if (leftExprSymbol->semanticType == rightExprSymbol->semanticType) {
        exprSemanticType = leftExprSymbol->semanticType;
    } else {
        // siempre casteo a float si son distintos
        exprSemanticType = SYMBOL_SEMANTIC_TYPE_FLOAT;
    }

    // por ahora solo se llama temp, luego le pondre ti con i de 0..N
    char *tempName = "temp";

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .name         = tempName,
        .semanticType = exprSemanticType,
    };

    Symbol *exprDivisionSymbol = newSymbol(&config);
    node->symbol               = exprDivisionSymbol;
}

void analysisNodeMod(AstNode *node, SymbolTable *st) {
    // deberia dejar que los operandos puedan ser float?
    DEBUG_SEMANTIC("node Mod visited")
    semanticAnalysisAux(node->children1, st);
    semanticAnalysisAux(node->children2, st);

    Symbol *leftExprSymbol  = node->children1->symbol;
    Symbol *rightExprSymbol = node->children2->symbol;
    
    SymbolSemanticType exprSemanticType;

    // chequear que ninguna expresion sea logica/booleana
    if (leftExprSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("left expression of mod (%%) is boolean (line: %d)", node->line)
    }

    if (rightExprSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("right expression of mod (%%) is boolean (line: %d)", node->line)
    }

    if (leftExprSymbol->semanticType == rightExprSymbol->semanticType) {
        exprSemanticType = leftExprSymbol->semanticType;
    } else {
        // siempre casteo a float si son distintos
        exprSemanticType = SYMBOL_SEMANTIC_TYPE_FLOAT;
    }

    // por ahora solo se llama temp, luego le pondre ti con i de 0..N
    char *tempName = "temp";

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .name         = tempName,
        .semanticType = exprSemanticType,
    };

    Symbol *exprModSymbol = newSymbol(&config);
    node->symbol          = exprModSymbol;
}

void analysisNodeComparisionSmaller(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node ComparisionSmaller visited")

    // chequear que ambas expresiones sean int's o float's 
    // los temporales no cuentan ya que significa que se coloco una exp aritmetica
    // y necesitamos directamente numeros literales o id's
    semanticAnalysisAux(node->children1, st);
    if (!((node->children1->type == AST_NODE_TYPE_ID)             || 
          (node->children1->type == AST_NODE_TYPE_INT_LITERAL)    ||
          (node->children1->type == AST_NODE_TYPE_FLOAT_LITERAL))) {
            ERROR_SEMANTIC("left expr of '>' must be an int literal, float literal, int variable or float variable (line: %d)", node->line)
        }
    
    semanticAnalysisAux(node->children2, st);
    if (!((node->children2->type == AST_NODE_TYPE_ID)             || 
          (node->children2->type == AST_NODE_TYPE_INT_LITERAL)    ||
          (node->children2->type == AST_NODE_TYPE_FLOAT_LITERAL))) {
            ERROR_SEMANTIC("right expr of '>' must be an int literal, float literal, int variable or float variable (line: %d)", node->line)
        }

    // crear el simbolo para el temporal
    char *symbolName                      = "temp";
    SymbolSemanticType symbolSemanticType = SYMBOL_SEMANTIC_TYPE_BOOLEAN;

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .name         = symbolName,
        .semanticType = symbolSemanticType,
    };

    Symbol *compSmallerSymbol = newSymbol(&config);
    node->symbol              = compSmallerSymbol;
}

void analysisNodeComparisionGreater(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node ComparisionGreater visited")

    // chequear que ambas expresiones sean int's o float's 
    // los temporales no cuentan ya que significa que se coloco una exp aritmetica
    // y necesitamos directamente numeros literales o id's
    semanticAnalysisAux(node->children1, st);
    if (!((node->children1->type == AST_NODE_TYPE_ID)             || 
          (node->children1->type == AST_NODE_TYPE_INT_LITERAL)    ||
          (node->children1->type == AST_NODE_TYPE_FLOAT_LITERAL))) {
            ERROR_SEMANTIC("left expr of '>' must be an int literal, float literal, int variable or float variable (line: %d)", node->line)
        }
    
    semanticAnalysisAux(node->children2, st);
    if (!((node->children2->type == AST_NODE_TYPE_ID)             || 
          (node->children2->type == AST_NODE_TYPE_INT_LITERAL)    ||
          (node->children2->type == AST_NODE_TYPE_FLOAT_LITERAL))) {
            ERROR_SEMANTIC("right expr of '>' must be an int literal, float literal, int variable or float variable (line: %d)", node->line)
        }

    // crear el simbolo para el temporal
    char *symbolName                      = "temp";
    SymbolSemanticType symbolSemanticType = SYMBOL_SEMANTIC_TYPE_BOOLEAN;

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .name         = symbolName,
        .semanticType = symbolSemanticType,
    };

    Symbol *compGreaterSymbol = newSymbol(&config);
    node->symbol              = compGreaterSymbol;
}

void analysisNodeEqual(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node Equal visited")

    if (node->children1) semanticAnalysisAux(node->children1, st);
    if (node->children2) semanticAnalysisAux(node->children2, st);

    // chequear que ambos operandos sean del mismo tipo
    if (node->children1->symbol->semanticType != node->children2->symbol->semanticType)
        ERROR_SEMANTIC("in '==' left expr is of type %s and the right expr is of type %s (line: %d)", getSemanticTypeString(node->children1->symbol->semanticType), getSemanticTypeString(node->children2->symbol->semanticType), node->line)

    // crear el simbolo temporal para guardar luego el resultado
    char *tempName = "temp";

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .name         = tempName,
        .semanticType = SYMBOL_SEMANTIC_TYPE_BOOLEAN,
    };

    Symbol *equalSymbol = newSymbol(&config);
    node->symbol        = equalSymbol;
}

void analysisNodeAnd(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node And visited")
    semanticAnalysisAux(node->children1, st);
    semanticAnalysisAux(node->children2, st);

    Symbol *leftExprSymbol  = node->children1->symbol;
    Symbol *rightExprSymbol = node->children2->symbol;

    // chequear que ninguna expresion sea int/float
    if (leftExprSymbol->semanticType != SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("left expression of and (&&) is '%s' (line: %d)", getSemanticTypeString(leftExprSymbol->semanticType), node->line)
    }

    if (rightExprSymbol->semanticType != SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("right expression of and (&&) is '%s' (line: %d)", getSemanticTypeString(rightExprSymbol->semanticType), node->line)
    }

    // por ahora solo se llama temp, luego le pondre ti con i de 0..N
    char *tempName = "temp";

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .name         = tempName,
        .semanticType = SYMBOL_SEMANTIC_TYPE_BOOLEAN,
    };

    Symbol *exprAndSymbol = newSymbol(&config);
    node->symbol          = exprAndSymbol;
}

void analysisNodeOr(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node Or visited")
    semanticAnalysisAux(node->children1, st);
    semanticAnalysisAux(node->children2, st);

    Symbol *leftExprSymbol  = node->children1->symbol;
    Symbol *rightExprSymbol = node->children2->symbol;

    // chequear que ninguna expresion sea int/float
    if (leftExprSymbol->semanticType != SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("left expression of or (||) is '%s' (line: %d)", getSemanticTypeString(leftExprSymbol->semanticType), node->line)
    }

    if (rightExprSymbol->semanticType != SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("right expression of or (||) is '%s' (line: %d)", getSemanticTypeString(rightExprSymbol->semanticType), node->line)
    }

    // por ahora solo se llama temp, luego le pondre ti con i de 0..N
    char *tempName = "temp";

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .name         = tempName,
        .semanticType = SYMBOL_SEMANTIC_TYPE_BOOLEAN,
    };

    Symbol *exprOrSymbol = newSymbol(&config);
    node->symbol         = exprOrSymbol;
}

void analysisNodeMinus(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node Minus visited")

    if (node->children1) semanticAnalysisAux(node->children1, st);

    // chequear que el operando sea int o float
    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN)
        ERROR_SEMANTIC("in '-' (unary) the operand must be int or float, but it's boolean (line: %d)", node->line)

    // crear simbolo para el temporal que guarda el resultado
    char *tempName = "temp";

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .name         = tempName,
        .semanticType = node->children1->symbol->semanticType,
    };

    Symbol *minusSymbol = newSymbol(&config);
    node->symbol        = minusSymbol;
}

void analysisNodeNegation(AstNode *node, SymbolTable *st) {
    DEBUG_SEMANTIC("node Negation visited")

    if (node->children1) semanticAnalysisAux(node->children1, st);

    // chequear que el operando sea int o float
    if (node->children1->symbol->semanticType != SYMBOL_SEMANTIC_TYPE_BOOLEAN)
        ERROR_SEMANTIC("in '!' the operand must be boolean, but it's %s (line: %d)", getSemanticTypeString(node->children1->symbol->semanticType), node->line)

    // crear simbolo para el temporal que guarda el resultado
    char *tempName = "temp";

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .name         = tempName,
        .semanticType = SYMBOL_SEMANTIC_TYPE_BOOLEAN,
    };

    Symbol *negationSymbol = newSymbol(&config);
    node->symbol           = negationSymbol;
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

