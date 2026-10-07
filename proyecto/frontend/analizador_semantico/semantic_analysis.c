#include "semantic_analysis.h"

void semanticAnalysis(AstNode *root) {
    if (!root) ERROR_SEMANTIC("root node is NULL in semanticAnalysis()")
    
    SymbolTable st;
    st.top = NULL;

    int tempCount = 0;

    semanticAnalysisAux(root, &st, &tempCount);
}

void semanticAnalysisAux(AstNode *root, SymbolTable *st, int *tempCount) {
    if (!root) ERROR_SEMANTIC("root node is NULL in semanticAnalysisAux()")
    if (!st)   ERROR_SEMANTIC("symbol table is NULL in semanticAnalysisAux()")

    switch (root->type) {
        case AST_NODE_TYPE_P:                   analysisNodeP(root, st, tempCount);                 break;                
        case AST_NODE_TYPE_GLOBAL_DECL_LIST:    analysisNodeGlobalDeclList(root, st, tempCount);    break;    
        case AST_NODE_TYPE_VAR_DECL:            analysisNodeVarDecl(root, st, tempCount);           break;            
        case AST_NODE_TYPE_METHOD_DECL_LIST:    analysisNodeMethodDeclList(root, st, tempCount);    break;     
        case AST_NODE_TYPE_METHOD_DECL:         analysisNodeMethodDecl(root, st, tempCount);        break;         
        case AST_NODE_TYPE_LIST_ID:             analysisNodeListId(root, st, tempCount);            break;            
        case AST_NODE_TYPE_ID:                  analysisNodeId(root, st, tempCount);                break;                  
        case AST_NODE_TYPE_PARAMS:              analysisNodeParams(root, st, tempCount);            break;              
        case AST_NODE_TYPE_VOID:                analysisNodeVoid(root, st, tempCount);              break;               
        case AST_NODE_TYPE_PARAM:               analysisNodeParam(root, st, tempCount);             break;               
        case AST_NODE_TYPE_BLOCK:               analysisNodeBlock(root, st, tempCount);             break;
        case AST_NODE_TYPE_BLOCK_ELEMS:         analysisNodeBlockElems(root, st, tempCount);        break;         
        case AST_NODE_TYPE_STATEMENTS:          analysisNodeStatements(root, st, tempCount);        break;          
        case AST_NODE_TYPE_TYPE:                analysisNodeType(root, st, tempCount);              break;                
        case AST_NODE_TYPE_ASSIGNMENT:          analysisNodeAssignment(root, st, tempCount);        break;          
        case AST_NODE_TYPE_METHOD_CALL:         analysisNodeMethodCall(root, st, tempCount);        break;        
        case AST_NODE_TYPE_IF_ELSE:             analysisNodeIfElse(root, st, tempCount);            break;             
        case AST_NODE_TYPE_WHILE:               analysisNodeWhile(root, st, tempCount);             break;               
        case AST_NODE_TYPE_RETURN:              analysisNodeReturn(root, st, tempCount);            break;             
        case AST_NODE_TYPE_LIST_EXPR:           analysisNodeListExpr(root, st, tempCount);          break;          
        case AST_NODE_TYPE_INT_LITERAL:         analysisNodeIntLiteral(root, st, tempCount);        break;         
        case AST_NODE_TYPE_FLOAT_LITERAL:       analysisNodeFloatLiteral(root, st, tempCount);      break;       
        case AST_NODE_TYPE_BOOL_LITERAL:        analysisNodeBoolLiteral(root, st, tempCount);       break;       
        case AST_NODE_TYPE_ADDITION:            analysisNodeAddition(root, st, tempCount);          break;            
        case AST_NODE_TYPE_SUBTRACTION:         analysisNodeSubtraction(root, st, tempCount);       break;         
        case AST_NODE_TYPE_MULTIPLICATION:      analysisNodeMultiplication(root, st, tempCount);    break;      
        case AST_NODE_TYPE_DIVISION:            analysisNodeDivision(root, st, tempCount);          break;            
        case AST_NODE_TYPE_MOD:                 analysisNodeMod(root, st, tempCount);               break;                 
        case AST_NODE_TYPE_COMPARISON_SMALLER:  analysisNodeComparisonSmaller(root, st, tempCount); break; 
        case AST_NODE_TYPE_COMPARISON_GREATER:  analysisNodeComparisonGreater(root, st, tempCount); break; 
        case AST_NODE_TYPE_EQUAL:               analysisNodeEqual(root, st, tempCount);             break;               
        case AST_NODE_TYPE_AND:                 analysisNodeAnd(root, st, tempCount);               break;                 
        case AST_NODE_TYPE_OR:                  analysisNodeOr(root, st, tempCount);                break;                  
        case AST_NODE_TYPE_MINUS:               analysisNodeMinus(root, st, tempCount);             break;               
        case AST_NODE_TYPE_NEGATION:            analysisNodeNegation(root, st, tempCount);          break;   
    }
}




void analysisNodeP(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node P visited")
    newLevel(st); // scope global
    if (node->children1) semanticAnalysisAux(node->children1, st, tempCount);

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




void analysisNodeGlobalDeclList(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node GlobalDeclList visited")
    
    if (node->children1) {
        node->children1->variableType = SYMBOL_VARIABLE_TYPE_GLOBAL; // bajamos la info de que es una var global
        semanticAnalysisAux(node->children1, st, tempCount);
        AstNode *varDeclNode = node->children1;
    }

    if (node->children2) semanticAnalysisAux(node->children2, st, tempCount);
}




void analysisNodeVarDecl(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node VarDecl visited")
    SymbolSemanticType     symbolSemanticType;
    char                   *strSemanticType;
    AstNodeDeclarationType nodeDeclarationType;

    if (node->children1) {
        nodeDeclarationType = node->children1->declarationType;
        symbolSemanticType  = getSymbolSemanticTypeFromAstNodeDeclarationType(nodeDeclarationType);
        strSemanticType     = getSemanticTypeString(symbolSemanticType);
    }

    if (!node->children2) return;

    if (node->children2->type == AST_NODE_TYPE_ID) {
        // insertar el simbolo nuevo
        SymbolConfig varSymbolConfig = {
            .type                 = SYMBOL_TYPE_VARIABLE,
            .variableType         = node->variableType,
            .name                 = node->children2->value.strValue,
            .semanticType         = symbolSemanticType,
        };

        bool res = insertSymbol(st, &varSymbolConfig);

        if (!res) ERROR_SEMANTIC("redeclared variable '%s %s' (line: %d)", strSemanticType, varSymbolConfig.name, node->line)
        
        // guardar el simbolo en el nodo ID (sirve en la generacion de codigo intermedio)
        Symbol *varSymbol = searchSymbol(st, node->children2->value.strValue, SYMBOL_TYPE_VARIABLE);
        
        if (!varSymbol)
            ERROR_SEMANTIC("varSymbol is NULL in analysisNodeVarDecl()")

        node->children2->symbol = varSymbol;
    }

    if (node->children2->type == AST_NODE_TYPE_LIST_ID) {
        // arrastrar el tipo de la declaracion en la lista
        node->children2->declarationType = nodeDeclarationType;
        // bajamos el tipo de variable tambien
        node->children2->variableType = node->variableType;
        semanticAnalysisAux(node->children2, st, tempCount);
    }
}




void analysisNodeMethodDeclList(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node MethodDeclList visited")
    if (node->children1) semanticAnalysisAux(node->children1, st, tempCount);
    if (node->children2) semanticAnalysisAux(node->children2, st, tempCount);
}




void analysisNodeMethodDecl(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node MethodDecl visited")
    SymbolSemanticType returnType;
    char               *strReturnType;
    char               *methodName;
    bool               hasReturn; // para saber si la funcion retorna algo

    hasReturn = false;

    // tipo de retorno de la funcion
    if (node->children1->type == AST_NODE_TYPE_TYPE) {
        AstNodeDeclarationType nodeDeclarationType = node->children1->declarationType;
        returnType    = getSymbolSemanticTypeFromAstNodeDeclarationType(nodeDeclarationType);
        strReturnType = getSemanticTypeString(returnType);
        hasReturn     = true;
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

        semanticAnalysisAux(node->children3, st, tempCount);
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

    Symbol *functionSymbol = searchSymbol(st, methodSymbolConfig.name, SYMBOL_TYPE_METHOD);

    node->children2->symbol = functionSymbol; // solo los nodos ID apuntan a simbolos
                                              // aunque no haria falta guardar en la declaracion
    functionSymbol->referenceCount++;

    // cuerpo de la funcion
    if (node->children4) {
        node->children4->isFunctionBlock = true;
        semanticAnalysisAux(node->children4, st, tempCount);
    }

    // chequear que si la funcion retorna algo entonces en el cuerpo esten los respectivos return's
    if (hasReturn) {
        if (!checkIfFunctionHasReturn(node->children4)) 
            ERROR_SEMANTIC("function signature of '%s' says it returns an '%s', but the body miss return's statatements (line: %d)", functionSymbol->name, strReturnType, node->line)
    }

    // si la funcion no retorna nada el chequeo de que no intente retornar
    // algo se hace en la funcion de analisis del nodo return
}




void analysisNodeListId(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node ListId visited")
    SymbolSemanticType     symbolSemanticType;
    char                   *strSemanticType;
    AstNodeDeclarationType nodeDeclarationType;

    if (node->children1) {
        nodeDeclarationType = node->declarationType;
        symbolSemanticType  = getSymbolSemanticTypeFromAstNodeDeclarationType(nodeDeclarationType);
        strSemanticType     = getSemanticTypeString(symbolSemanticType);

        SymbolConfig varSymbolConfig = {
            .type                 = SYMBOL_TYPE_VARIABLE,
            .variableType         = node->variableType,
            .name                 = node->children1->value.strValue,
            .semanticType         = symbolSemanticType,
        };

        bool res = insertSymbol(st, &varSymbolConfig);
        
        if (!res) ERROR_SEMANTIC("redeclared variable '%s %s' (line: %d)", strSemanticType, varSymbolConfig.name, node->line)

        // guardar el simbolo en el nodo ID (sirve para la generacion de codigo intermedio)
        Symbol *varSymbol = searchSymbol(st, node->children1->value.strValue, SYMBOL_TYPE_VARIABLE);

        if (!varSymbol)
            ERROR_SEMANTIC("varSymbol is NULL in analysisNodeListId()")
        
        node->children1->symbol = varSymbol;
    }

    if (!node->children2) return;

    if (node->children2->type == AST_NODE_TYPE_ID) {
        // insertar el simbolo nuevo
        SymbolConfig varSymbolConfig = {
            .type                 = SYMBOL_TYPE_VARIABLE,
            .variableType         = node->variableType,
            .name                 = node->children2->value.strValue,
            .semanticType         = symbolSemanticType,
        };

        bool res = insertSymbol(st, &varSymbolConfig);

        if (!res) ERROR_SEMANTIC("redeclared variable '%s %s' (line: %d)", strSemanticType, varSymbolConfig.name, node->line)
        
        // guardar el simbolo en el nodo ID (sirve para la generacion de codigo intermedio)
        Symbol *varSymbol = searchSymbol(st, node->children2->value.strValue, SYMBOL_TYPE_VARIABLE);

        if (!varSymbol)
            ERROR_SEMANTIC("varSymbol is NULL in analysisNodeListId()")
        
        node->children2->symbol = varSymbol;
    }

    if (node->children2->type == AST_NODE_TYPE_LIST_ID) {
        // arrastrar el tipo de la declaracion en la lista
        node->children2->declarationType = nodeDeclarationType;
        // bajamos el tipo de variable
        node->children2->variableType = node->variableType;
        semanticAnalysisAux(node->children2, st, tempCount);
    }
}




void analysisNodeId(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node Id visited")
    Symbol *idSymbol = searchSymbol(st, node->value.strValue, SYMBOL_TYPE_VARIABLE);

    if (!idSymbol) ERROR_SEMANTIC("variable '%s' was not declared (line: %d)", node->value.strValue, node->line)
    
    node->symbol = idSymbol;
    idSymbol->referenceCount++;
}




void analysisNodeParams(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node Params visited")
    if (node->children1) semanticAnalysisAux(node->children1, st, tempCount);
    if (node->children2) semanticAnalysisAux(node->children2, st, tempCount);
}




void analysisNodeVoid(AstNode *node, SymbolTable *st, int *tempCount) {
    TODO("analysisNodeVoid not implemented yet")
}




void analysisNodeParam(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node Param visited")
    SymbolSemanticType symbolSemanticType;

    AstNodeDeclarationType nodeDeclarationType = node->children1->declarationType;
    symbolSemanticType = getSymbolSemanticTypeFromAstNodeDeclarationType(nodeDeclarationType);

    char *symbolName = node->children2->value.strValue;

    SymbolConfig config = (SymbolConfig){
        .type         = SYMBOL_TYPE_VARIABLE,
        .variableType = SYMBOL_VARIABLE_TYPE_PARAMETER,
        .name         = symbolName,
        .semanticType = symbolSemanticType,
    };

    Symbol *paramSymbol = newSymbol(&config);
    node->children2->symbol = paramSymbol;
    paramSymbol->referenceCount++;
}




void analysisNodeBlock(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node Block visited")
    newLevel(st);
    
    if (node->isFunctionBlock) {
        // meter los simbolos de los parametros en el nivel actual.
        // la primer funcion del nivel anterior es de la cual debemos
        // extraer los parametros
        Symbol *functionSymbol          = st->top->next->head;
        Symbol *functionSymbolParamList = functionSymbol->parameters;

        // si tenia algun param insertarlo en la tabla de simbolos
        // nota: esto es seguro porque el nivel al inicio es NULL, si no podria modificar la lista de params de la funcion
        if (functionSymbolParamList) insertSymbolListInCurrentLevel(st, functionSymbolParamList);
    }

    if (node->children1) semanticAnalysisAux(node->children1, st, tempCount);
    closeLevel(st); 
}




void analysisNodeBlockElems(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node BlockElems visited")
    
    if (node->children1) {
        // bajamos la info para que en la declaracion de variable se sepa que es local
        node->children1->variableType = SYMBOL_VARIABLE_TYPE_LOCAL;
        semanticAnalysisAux(node->children1, st, tempCount);
    }

    if (node->children2) semanticAnalysisAux(node->children2, st, tempCount);
}




void analysisNodeStatements(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node Statements visited")
    if (node->children1) semanticAnalysisAux(node->children1, st, tempCount);
    if (node->children2) semanticAnalysisAux(node->children2, st, tempCount);
}




void analysisNodeType(AstNode *node, SymbolTable *st, int *tempCount) {
     TODO("analysisNodeType not implemented yet")
}




void analysisNodeAssignment(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node Assigment visited")
    // ver que el tipo de la expresion de la derecha tenga el mismo tipo que el id de la izquierda
    SymbolSemanticType idType;
    SymbolSemanticType exprType;
    char               *idTypeStr;
    char               *exprTypeStr;

    semanticAnalysisAux(node->children1, st, tempCount);
    idType    = node->children1->symbol->semanticType;
    idTypeStr = getSemanticTypeString(idType);

    semanticAnalysisAux(node->children2, st, tempCount);
    exprType    = node->children2->symbol->semanticType;
    exprTypeStr = getSemanticTypeString(exprType);

    if (idType != exprType) {
        if ((idType == SYMBOL_SEMANTIC_TYPE_FLOAT) && (exprType == SYMBOL_SEMANTIC_TYPE_INT)) {
            // castear int a float
            WARNING_SEMANTIC("casting right expression of the assignment '=' (which is of type int) to float (line: %d)", node->line)
        } else if ((idType == SYMBOL_SEMANTIC_TYPE_INT) && (exprType == SYMBOL_SEMANTIC_TYPE_FLOAT)) {
            // castear float a int
            WARNING_SEMANTIC("casting right expression of the assignment '=' (which is of type float) to int (line: %d)", node->line)
        } else {
            ERROR_SEMANTIC("invalid assigment -> '%s' type is %s, but the right expression type is %s (line: %d)", node->children1->value.strValue, idTypeStr, exprTypeStr, node->line)
        }
    }
}




void analysisNodeMethodCall(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node MethodCall visited")

    // el nodo id lo analizo a mano (porque si no 'analysisNodeID()' va a buscar el simbolo como una variable y es una funcion)
    Symbol *methodSymbol = searchSymbol(st, node->children1->value.strValue, SYMBOL_TYPE_METHOD);
    methodSymbol->referenceCount++;

    if (!methodSymbol)
        ERROR_SEMANTIC("method '%s' was not declared (line: %d)", node->children1->value.strValue, node->line)

    node->children1->symbol = methodSymbol; // en realidad no hace falta hacer esto 

    if (node->children2) semanticAnalysisAux(node->children2, st, tempCount);

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
            
            // es una expr (es el ultimo argumento pasado)
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

    char tempName[24] = "t";
    char strTempCount[8];

    snprintf(strTempCount, 8, "%d", *tempCount);
    strcat(tempName, strTempCount);
    (*tempCount)++;

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .variableType = SYMBOL_VARIABLE_TYPE_LOCAL,
        .name         = strdup(tempName),
        .semanticType = methodSymbol->semanticType,
    };

    Symbol *methodCallSymbol = newSymbol(&config);
    node->symbol             = methodCallSymbol;
    methodCallSymbol->referenceCount++;
}




void analysisNodeIfElse(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node IfElse visited")

    // chequear que la expr de la condicion sea booleana
    semanticAnalysisAux(node->children1, st, tempCount);
    if (node->children1->symbol->semanticType != SYMBOL_SEMANTIC_TYPE_BOOLEAN)
        ERROR_SEMANTIC("condition in the if statement must be a logic/boolean expression, but it's of type %s (line: %d)", getSemanticTypeString(node->children1->symbol->semanticType), node->line)
    
    if (node->children2) semanticAnalysisAux(node->children2, st, tempCount);
    if (node->children3) semanticAnalysisAux(node->children3, st, tempCount);
}




void analysisNodeWhile(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node While visited")
    if (node->children1) semanticAnalysisAux(node->children1, st, tempCount);

    // chequear que la expr de la condicion sea boolean
    if (node->children1->symbol->semanticType != SYMBOL_SEMANTIC_TYPE_BOOLEAN)
        ERROR_SEMANTIC("the expression on the condition in the while statement must be boolean, but it is %s (line: %d)", getSemanticTypeString(node->children1->symbol->semanticType), node->line)

    if (node->children2) semanticAnalysisAux(node->children2, st, tempCount);
}




void analysisNodeReturn(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node Return visited")

    SymbolSemanticType returnExprSemanticType;
    SymbolSemanticType methodSemanticType;

    // chequear si retorna una expr y el tipo de la expr que retorna
    if (node->children1) {
        semanticAnalysisAux(node->children1, st, tempCount);
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




void analysisNodeListExpr(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node ListExpr visited")

    if (node->children1) semanticAnalysisAux(node->children1, st, tempCount);
    if (node->children2) semanticAnalysisAux(node->children2, st, tempCount);
}




void analysisNodeIntLiteral(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node IntLiteral visited")
    setLiteralSymbolInAstNode(node);
}




void analysisNodeFloatLiteral(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node FloatLiteral visited")
    setLiteralSymbolInAstNode(node);
}




void analysisNodeBoolLiteral(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node BoolLiteral visited")
    setLiteralSymbolInAstNode(node);
}




void analysisNodeAddition(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node Addition visited")
    analysisArithmeticBinaryOperator(node, st, tempCount);
}




void analysisNodeSubtraction(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node Subtraction visited")
    analysisArithmeticBinaryOperator(node, st, tempCount);
}




void analysisNodeMultiplication(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node Multiplication visited")
    analysisArithmeticBinaryOperator(node, st, tempCount);
}




void analysisNodeDivision(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node Division visited")
    analysisArithmeticBinaryOperator(node, st, tempCount);
}




void analysisNodeMod(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node Mod visited")
    analysisArithmeticBinaryOperator(node, st, tempCount);
}




void analysisNodeComparisonSmaller(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node ComparisionSmaller visited")
    analysisComparisonOperator(node, st, tempCount);
}




void analysisNodeComparisonGreater(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node ComparisionGreater visited")
    analysisComparisonOperator(node, st, tempCount);
}




void analysisNodeEqual(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node Equal visited")

    if (node->children1) semanticAnalysisAux(node->children1, st, tempCount);
    if (node->children2) semanticAnalysisAux(node->children2, st, tempCount);

    // chequear que ambos operandos sean del mismo tipo
    if (node->children1->symbol->semanticType != node->children2->symbol->semanticType)
        ERROR_SEMANTIC("in '==' left expr is of type %s and the right expr is of type %s (line: %d)", getSemanticTypeString(node->children1->symbol->semanticType), getSemanticTypeString(node->children2->symbol->semanticType), node->line)

    // crear el simbolo temporal para guardar luego el resultado
    char tempName[24] = "t";
    char strTempCount[8];

    snprintf(strTempCount, 8, "%d", *tempCount);
    strcat(tempName, strTempCount);
    (*tempCount)++;

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .variableType = SYMBOL_VARIABLE_TYPE_LOCAL,
        .name         = strdup(tempName),
        .semanticType = SYMBOL_SEMANTIC_TYPE_BOOLEAN,
    };

    Symbol *equalSymbol = newSymbol(&config);
    node->symbol        = equalSymbol;
    equalSymbol->referenceCount++;
}




void analysisNodeAnd(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node And visited")
    analysisLogicalBinaryOperator(node, st, tempCount);
}




void analysisNodeOr(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node Or visited")
    analysisLogicalBinaryOperator(node, st, tempCount);
}




void analysisNodeMinus(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node Minus visited")

    if (node->children1) semanticAnalysisAux(node->children1, st, tempCount);

    // chequear que el operando sea int o float
    if (node->children1->symbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN)
        ERROR_SEMANTIC("in '-' (unary) the operand must be int or float, but it's boolean (line: %d)", node->line)

    // crear simbolo para el temporal que guarda el resultado
    char tempName[24] = "t";
    char strTempCount[8];

    snprintf(strTempCount, 8, "%d", *tempCount);
    strcat(tempName, strTempCount);
    (*tempCount)++;

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .variableType = SYMBOL_VARIABLE_TYPE_LOCAL,
        .name         = strdup(tempName),
        .semanticType = node->children1->symbol->semanticType,
    };

    Symbol *minusSymbol = newSymbol(&config);
    node->symbol        = minusSymbol;
    minusSymbol->referenceCount++;
}




void analysisNodeNegation(AstNode *node, SymbolTable *st, int *tempCount) {
    DEBUG_SEMANTIC("node Negation visited")

    if (node->children1) semanticAnalysisAux(node->children1, st, tempCount);

    // chequear que el operando sea int o float
    if (node->children1->symbol->semanticType != SYMBOL_SEMANTIC_TYPE_BOOLEAN)
        ERROR_SEMANTIC("in '!' the operand must be boolean, but it's %s (line: %d)", getSemanticTypeString(node->children1->symbol->semanticType), node->line)

    // crear simbolo para el temporal que guarda el resultado
    char tempName[24] = "t";
    char strTempCount[8];

    snprintf(strTempCount, 8, "%d", *tempCount);
    strcat(tempName, strTempCount);
    (*tempCount)++;

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .variableType = SYMBOL_VARIABLE_TYPE_LOCAL,
        .name         = strdup(tempName),
        .semanticType = SYMBOL_SEMANTIC_TYPE_BOOLEAN,
    };

    Symbol *negationSymbol = newSymbol(&config);
    node->symbol           = negationSymbol;
    negationSymbol->referenceCount++;
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

        // en el caso de la sentencia while siempre retorno false, por que no necesariamente entro al mismo
        default: return false;
    }
}




void getSymbolParamList(AstNode *node, Symbol **symbolParamList) {
    Symbol *tail = NULL;
    getSymbolParamListAux(node, symbolParamList, &tail);
    tail->next = NULL;
}




void getSymbolParamListAux(AstNode *node, Symbol **symbolParamList, Symbol **tail) {
    if (!node) return;

    switch (node->type) {
        case AST_NODE_TYPE_PARAM: {
            Symbol *paramSymbol = node->children2->symbol;

            // inserta a la cola
            if (!(*symbolParamList) && !(*tail)) {
                *symbolParamList = paramSymbol;
                *tail = paramSymbol;
            } else {
                (*tail)->next = paramSymbol;
                *tail = paramSymbol;
            }
        } break;

        case AST_NODE_TYPE_PARAMS: {
            getSymbolParamListAux(node->children1, symbolParamList, tail);
            getSymbolParamListAux(node->children2, symbolParamList, tail);
        } break;
        
        default: return;
    }
}




SymbolSemanticType getSymbolSemanticTypeFromAstNodeDeclarationType(AstNodeDeclarationType declType) {
    switch (declType) {
        case AST_NODE_DECLARATION_TYPE_INT:     return SYMBOL_SEMANTIC_TYPE_INT;
        case AST_NODE_DECLARATION_TYPE_FLOAT:   return SYMBOL_SEMANTIC_TYPE_FLOAT;
        case AST_NODE_DECLARATION_TYPE_BOOLEAN: return SYMBOL_SEMANTIC_TYPE_BOOLEAN;
    }
}



void setLiteralSymbolInAstNode(AstNode *nodeLiteral) {
    char *literalName = "const";

    SymbolConfig config = {
        .type = SYMBOL_TYPE_CONSTANT,
        .name = strdup(literalName),
    };

    switch (nodeLiteral->type) {
        case AST_NODE_TYPE_INT_LITERAL: {
            config.semanticType   = SYMBOL_SEMANTIC_TYPE_INT;
            config.value.intValue = nodeLiteral->value.intValue;
        } break;

        case AST_NODE_TYPE_FLOAT_LITERAL: {
            config.semanticType     = SYMBOL_SEMANTIC_TYPE_FLOAT;
            config.value.floatValue = nodeLiteral->value.floatValue;
        } break;

        case AST_NODE_TYPE_BOOL_LITERAL: {
            config.semanticType       = SYMBOL_SEMANTIC_TYPE_BOOLEAN;
            config.value.booleanValue = nodeLiteral->value.booleanValue;
        } break;
    }

    Symbol *literalSymbol = newSymbol(&config);
    nodeLiteral->symbol   = literalSymbol;
    literalSymbol->referenceCount++;
}




void analysisArithmeticBinaryOperator(AstNode *arithBinOpNode, SymbolTable *st, int *tempCount) {
    char *binOpStr;

    switch (arithBinOpNode->type) {
        case AST_NODE_TYPE_ADDITION:       binOpStr = "addition (+)";       break;
        case AST_NODE_TYPE_SUBTRACTION:    binOpStr = "subtraction (-)";    break;
        case AST_NODE_TYPE_MULTIPLICATION: binOpStr = "multiplication (*)"; break;
        case AST_NODE_TYPE_DIVISION:       binOpStr = "division (/)";       break;
        case AST_NODE_TYPE_MOD:            binOpStr = "mod (%%)";           break;
    }
    
    semanticAnalysisAux(arithBinOpNode->children1, st, tempCount);
    semanticAnalysisAux(arithBinOpNode->children2, st, tempCount);

    Symbol *leftExprSymbol  = arithBinOpNode->children1->symbol;
    Symbol *rightExprSymbol = arithBinOpNode->children2->symbol;
    
    SymbolSemanticType exprSemanticType;

    // chequear que ninguna expresion sea logica/booleana
    if (leftExprSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("left expression of %s is boolean (line: %d)", binOpStr, arithBinOpNode->line)
    }

    if (rightExprSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("right expression of %s is boolean (line: %d)", binOpStr, arithBinOpNode->line)
    }

    if (leftExprSymbol->semanticType == rightExprSymbol->semanticType) {
        exprSemanticType = leftExprSymbol->semanticType;
    } else {
        // siempre casteo a float si son distintos
        exprSemanticType = SYMBOL_SEMANTIC_TYPE_FLOAT;

        if (leftExprSymbol->semanticType == SYMBOL_SEMANTIC_TYPE_INT)  {
            WARNING_SEMANTIC("casting left expression of %s (which is of type int) to float (line: %d)", binOpStr, arithBinOpNode->line);
        } else {
            WARNING_SEMANTIC("casting right expression of %s (which is of type int) to float (line: %d)", binOpStr, arithBinOpNode->line);
        }
    }

    // por ahora solo se llama temp, luego le pondre ti con i de 0..N
    char tempName[24] = "t";
    char strTempCount[8];

    snprintf(strTempCount, 8, "%d", *tempCount);
    strcat(tempName, strTempCount);
    (*tempCount)++;

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .variableType = SYMBOL_VARIABLE_TYPE_LOCAL,
        .name         = strdup(tempName),
        .semanticType = exprSemanticType,
    };

    Symbol *exprArithBinOpSymbol = newSymbol(&config);
    arithBinOpNode->symbol       = exprArithBinOpSymbol;
    exprArithBinOpSymbol->referenceCount++;
}




void analysisLogicalBinaryOperator(AstNode *logicalBinOpNode, SymbolTable *st, int *tempCount) {
    char *binOpStr;

    switch (logicalBinOpNode->type) {
        case AST_NODE_TYPE_AND: binOpStr = "and (&&)"; break;
        case AST_NODE_TYPE_OR:  binOpStr = "or (||)";  break;
    }
    
    semanticAnalysisAux(logicalBinOpNode->children1, st, tempCount);
    semanticAnalysisAux(logicalBinOpNode->children2, st, tempCount);

    Symbol *leftExprSymbol  = logicalBinOpNode->children1->symbol;
    Symbol *rightExprSymbol = logicalBinOpNode->children2->symbol;

    // chequear que ninguna expresion sea int/float
    if (leftExprSymbol->semanticType != SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("left expression of %s is '%s' (line: %d)", binOpStr, getSemanticTypeString(leftExprSymbol->semanticType), logicalBinOpNode->line)
    }

    if (rightExprSymbol->semanticType != SYMBOL_SEMANTIC_TYPE_BOOLEAN) {
        ERROR_SEMANTIC("right expression of %s is '%s' (line: %d)", binOpStr, getSemanticTypeString(rightExprSymbol->semanticType), logicalBinOpNode->line)
    }

    // por ahora solo se llama temp, luego le pondre ti con i de 0..N
    char tempName[24] = "t";
    char strTempCount[8];

    snprintf(strTempCount, 8, "%d", *tempCount);
    strcat(tempName, strTempCount);
    (*tempCount)++;

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .variableType = SYMBOL_VARIABLE_TYPE_LOCAL,
        .name         = strdup(tempName),
        .semanticType = SYMBOL_SEMANTIC_TYPE_BOOLEAN,
    };

    Symbol *exprLogicalBinOpSymbol = newSymbol(&config);
    logicalBinOpNode->symbol       = exprLogicalBinOpSymbol;
    exprLogicalBinOpSymbol->referenceCount++;
}




void analysisComparisonOperator(AstNode *comparisonOpNode, SymbolTable *st, int *tempCount) {
    char *binOpStr;

    switch (comparisonOpNode->type) {
        case AST_NODE_TYPE_COMPARISON_GREATER: binOpStr = ">"; break;
        case AST_NODE_TYPE_COMPARISON_SMALLER: binOpStr = "<"; break;
    }
    
    // chequear que ambas expresiones sean int's o float's 
    // los temporales no cuentan ya que significa que se coloco una exp aritmetica
    // y necesitamos directamente numeros literales o id's
    semanticAnalysisAux(comparisonOpNode->children1, st, tempCount);
    if (!((comparisonOpNode->children1->type == AST_NODE_TYPE_ID)             || 
          (comparisonOpNode->children1->type == AST_NODE_TYPE_INT_LITERAL)    ||
          (comparisonOpNode->children1->type == AST_NODE_TYPE_FLOAT_LITERAL))) {
            ERROR_SEMANTIC("left expr of '%s' must be an int literal, float literal, int variable or float variable (line: %d)", binOpStr, comparisonOpNode->line)
        }
    
    semanticAnalysisAux(comparisonOpNode->children2, st, tempCount);
    if (!((comparisonOpNode->children2->type == AST_NODE_TYPE_ID)             || 
          (comparisonOpNode->children2->type == AST_NODE_TYPE_INT_LITERAL)    ||
          (comparisonOpNode->children2->type == AST_NODE_TYPE_FLOAT_LITERAL))) {
            ERROR_SEMANTIC("right expr of '%s' must be an int literal, float literal, int variable or float variable (line: %d)", binOpStr, comparisonOpNode->line)
        }

    // crear el simbolo para el temporal
    char tempName[24] = "t";
    char strTempCount[8];

    snprintf(strTempCount, 8, "%d", *tempCount);
    strcat(tempName, strTempCount);
    (*tempCount)++;

    SymbolSemanticType symbolSemanticType = SYMBOL_SEMANTIC_TYPE_BOOLEAN;

    SymbolConfig config = {
        .type         = SYMBOL_TYPE_VARIABLE,
        .variableType = SYMBOL_VARIABLE_TYPE_LOCAL,
        .name         = strdup(tempName),
        .semanticType = symbolSemanticType,
    };

    Symbol *comparisonSymbol = newSymbol(&config);
    comparisonOpNode->symbol = comparisonSymbol;
    comparisonSymbol->referenceCount++;
}
