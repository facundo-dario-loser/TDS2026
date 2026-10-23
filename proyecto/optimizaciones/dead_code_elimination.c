#include "dead_code_elimination.h"




void deadCodeElimination(AstNode **root) {
    if (!(*root)) return;

    switch ((*root)->type) {
        case AST_NODE_TYPE_P:                deadCodeElimination(&(*root)->children1);    break;
        case AST_NODE_TYPE_GLOBAL_DECL_LIST: deadCodeElimination(&(*root)->children2);    break;
        case AST_NODE_TYPE_VAR_DECL:                                                      break;
        case AST_NODE_TYPE_METHOD_DECL_LIST: deadCodeEliminationNodeMethodDeclList(root); break;
        case AST_NODE_TYPE_METHOD_DECL:      deadCodeElimination(&(*root)->children4);    break;
        case AST_NODE_TYPE_LIST_ID:                                                       break;
        case AST_NODE_TYPE_ID:                                                            break;
        case AST_NODE_TYPE_PARAMS:                                                        break;
        case AST_NODE_TYPE_VOID:                                                          break;
        case AST_NODE_TYPE_PARAM:                                                         break;
        case AST_NODE_TYPE_BLOCK:            deadCodeElimination(&(*root)->children1);    break;
        case AST_NODE_TYPE_BLOCK_ELEMS:      deadCodeElimination(&(*root)->children2);    break;
        case AST_NODE_TYPE_STATEMENTS:       deadCodeEliminationNodeStatements(root);     break;
        case AST_NODE_TYPE_TYPE:                                                          break;
        case AST_NODE_TYPE_ASSIGNMENT:                                                    break;
        case AST_NODE_TYPE_METHOD_CALL:                                                   break;
        case AST_NODE_TYPE_IF_ELSE:                                                       break;
        case AST_NODE_TYPE_WHILE:                                                         break;
        case AST_NODE_TYPE_RETURN:                                                        break;
        case AST_NODE_TYPE_LIST_EXPR:                                                     break;
        case AST_NODE_TYPE_INT_LITERAL:                                                   break;
        case AST_NODE_TYPE_FLOAT_LITERAL:                                                 break;
        case AST_NODE_TYPE_BOOL_LITERAL:                                                  break;
        case AST_NODE_TYPE_ADDITION:                                                      break;
        case AST_NODE_TYPE_SUBTRACTION:                                                   break;
        case AST_NODE_TYPE_MULTIPLICATION:                                                break;
        case AST_NODE_TYPE_DIVISION:                                                      break;
        case AST_NODE_TYPE_MOD:                                                           break;
        case AST_NODE_TYPE_COMPARISON_SMALLER:                                            break;
        case AST_NODE_TYPE_COMPARISON_GREATER:                                            break;
        case AST_NODE_TYPE_EQUAL:                                                         break;
        case AST_NODE_TYPE_AND:                                                           break;
        case AST_NODE_TYPE_OR:                                                            break;
        case AST_NODE_TYPE_MINUS:                                                         break;
        case AST_NODE_TYPE_NEGATION:                                                      break;
        case AST_NODE_TYPE_EXTERN_METHOD_DECL:                                            break;
    }
}




void deadCodeEliminationNodeMethodDeclList(AstNode **node) {
    DEBUG_OPT_DEAD_CODE("node MethodDeclList visited")
    if ((*node)->children1) deadCodeElimination(&(*node)->children1);
    if ((*node)->children2) deadCodeElimination(&(*node)->children2);
}




void deadCodeEliminationNodeStatements(AstNode **node) {
    DEBUG_OPT_DEAD_CODE("node Statements visited")

    if (!(*node)->children1) return;

    switch ((*node)->children1->type) {
        case AST_NODE_TYPE_RETURN: {
            freeAst((*node)->children2);
            (*node)->children2 = NULL;
        } break;

        case AST_NODE_TYPE_IF_ELSE: {
            bool nodeWasFreed = deadCodeEliminationNodeIfElse(&(*node)->children1);
            if (nodeWasFreed) (*node)->children1 = NULL;
            deadCodeElimination(&(*node)->children2);
        } break;

        case AST_NODE_TYPE_WHILE: {
            bool nodeWasFreed = deadCodeEliminationNodeWhile(&(*node)->children1);
            
            if (nodeWasFreed && (*node)->children2) {
                (*node) = (*node)->children2;
            }
            
            if ((*node)->children2) deadCodeElimination(&(*node)->children2);
        } break;
        
        default: {
            if ((*node)->children1) deadCodeElimination(&(*node)->children1);
            if ((*node)->children2) deadCodeElimination(&(*node)->children2);
        } break;
    }
}




bool deadCodeEliminationNodeIfElse(AstNode **node) {
    DEBUG_OPT_DEAD_CODE("node IfElse visited")
    
    if ((*node)->children1->symbol->type == SYMBOL_TYPE_CONSTANT) {
        if ((*node)->children1->symbol->value.booleanValue) { // if (true) ...
            AstNode *blockTrue = (*node)->children2;
            (*node)->children2 = NULL; // para evitar liberar ese sub-arbol despues
            freeAst((*node));
            (*node) = blockTrue;
            deadCodeElimination(node);
            return false;
        } else {
            if ((*node)->children2) { // if (false) {} else {}
                AstNode *blockFalse = (*node)->children3;
                (*node)->children3 = NULL; // para evitar liberar ese sub-arbol despues
                freeAst((*node));
                (*node) = blockFalse;
                deadCodeElimination(node);
                return false;
            } else { // if (false) {} (sin el otro bloque)
                freeAst((*node));
                return true;
            }
        }
    }
}




bool deadCodeEliminationNodeWhile(AstNode **node) {
    DEBUG_OPT_DEAD_CODE("node While visited")

    if ((*node)->children1->symbol->type == SYMBOL_TYPE_CONSTANT) {
        if ((*node)->children1->symbol->value.booleanValue) { // while (true)
            WARNING(MESSAGE_SOURCE_OPT_DEAD_CODE, "infinite while loop in line %d", (*node)->line)
            deadCodeElimination(&(*node)->children2); // eliminar codigo muerto del cuerpo
            return false;
        } else { // while (false)
            freeAst((*node));
            return true;
        }
    }
}
