#include "dot.h"

void getNodeLabel(AstNode *node, char label[256]) {
    if (!node) return;

    switch (node->type) {
        case AST_NODE_TYPE_P:                   snprintf(label, 256, "P");                break;
        case AST_NODE_TYPE_GLOBAL_DECL_LIST:    snprintf(label, 256, "GLOBAL_DECL_LIST"); break;
        case AST_NODE_TYPE_VAR_DECL:            snprintf(label, 256, "VAR_DECL");         break;
        case AST_NODE_TYPE_METHOD_DECL_LIST:    snprintf(label, 256, "METHOD_DECL_LIST"); break;
        case AST_NODE_TYPE_METHOD_DECL:         snprintf(label, 256, "METHOD_DECL");      break;
        case AST_NODE_TYPE_LIST_ID:             snprintf(label, 256, "LIST_ID");          break;
        case AST_NODE_TYPE_ID:                  snprintf(label, 256, "%s", node->value.strValue); break;
        case AST_NODE_TYPE_PARAMS:              snprintf(label, 256, "PARAMS");           break;
        case AST_NODE_TYPE_BLOCK:               snprintf(label, 256, "BLOCK");            break;
        case AST_NODE_TYPE_VOID:                snprintf(label, 256, "VOID");             break;
        case AST_NODE_TYPE_PARAM:               snprintf(label, 256, "PARAM");            break;
        case AST_NODE_TYPE_BLOCK_ELEMS:         snprintf(label, 256, "BLOCK_ELEMS");      break;
        case AST_NODE_TYPE_STATEMENTS:          snprintf(label, 256, "STATEMENTS");       break;
        case AST_NODE_TYPE_TYPE:                {
                                                    char *type;
                                                    switch (node->declarationType) {
                                                        case AST_NODE_DECLARATION_TYPE_INT:     type = "INT";     break;
                                                        case AST_NODE_DECLARATION_TYPE_FLOAT:   type = "FLOAT";   break;
                                                        case AST_NODE_DECLARATION_TYPE_BOOLEAN: type = "BOOLEAN"; break;
                                                    }
                                                    snprintf(label, 256, "%s", type);
                                                }                                         break;
        case AST_NODE_TYPE_STATEMENT:           snprintf(label, 256, "STATEMENT");        break;
        case AST_NODE_TYPE_ASSIGNMENT:          snprintf(label, 256, "ASSIGMENT");        break;
        case AST_NODE_TYPE_METHOD_CALL:         snprintf(label, 256, "METHOD_CALL");      break;
        case AST_NODE_TYPE_IF_ELSE:             snprintf(label, 256, "IF_ELSE");          break;
        case AST_NODE_TYPE_WHILE:               snprintf(label, 256, "WHILE");            break;
        case AST_NODE_TYPE_RETURN:              snprintf(label, 256, "RETURN");           break;
        case AST_NODE_TYPE_LIST_EXPR:           snprintf(label, 256, "LIST_EXPR");        break;
        case AST_NODE_TYPE_INT_LITERAL:         snprintf(label, 256, "%d", node->value.intValue);   break;
        case AST_NODE_TYPE_FLOAT_LITERAL:       snprintf(label, 256, "%f", node->value.floatValue); break;
        case AST_NODE_TYPE_BOOL_LITERAL:        {
                                                    char *boolLiteral = node->value.booleanValue ? "true" : "false";
                                                    snprintf(label, 256, "%s", boolLiteral);
                                                }                                         break;
        case AST_NODE_TYPE_ADDITION:            snprintf(label, 256, "+");                break;
        case AST_NODE_TYPE_SUBTRACTION:         snprintf(label, 256, "-");                break;
        case AST_NODE_TYPE_MULTIPLICATION:      snprintf(label, 256, "*");                break;
        case AST_NODE_TYPE_DIVISION:            snprintf(label, 256, "/");                break;
        case AST_NODE_TYPE_MOD:                 snprintf(label, 256, "%%");               break;
        case AST_NODE_TYPE_COMPARISION_SMALLER: snprintf(label, 256, "<");                break;
        case AST_NODE_TYPE_COMPARISION_GREATER: snprintf(label, 256, ">");                break;
        case AST_NODE_TYPE_EQUAL:               snprintf(label, 256, "==");               break;
        case AST_NODE_TYPE_AND:                 snprintf(label, 256, "&&");               break;
        case AST_NODE_TYPE_OR:                  snprintf(label, 256, "||");               break;
        case AST_NODE_TYPE_MINUS:               snprintf(label, 256, "-");                break;
        case AST_NODE_TYPE_NEGATION:            snprintf(label, 256, "!");                break;
    }
}

void astToDotAux(AstNode *root, FILE *f) {
    if (!root) return;

    char label[256];
    getNodeLabel(root, label);
    fprintf(f, "  \"node_%p\" [label=\"%s\", style=filled, fillcolor=\"#E8F0FE\", shape=ellipse, style=\"rounded,filled\"];\n", (void*)root, label);

    AstNode *children[4] = { root->children1, root->children2, root->children3, root->children4 };

    for (int i = 0; i < 4; i++) {
        if (!children[i]) continue;
        fprintf(f, "  \"node_%p\" -> \"node_%p\";\n", (void*)root, (void*)children[i]);
        astToDotAux(children[i], f);
    }
}

void astToDot(AstNode *root, char *fileName) {
    char filePath[256] = "dot_files/";
    strcat(filePath, fileName);
    FILE *f = fopen(filePath, "w");

    if (!f) ERROR_DOT("couldn't open file 'dot_files/file.dot'")

    fprintf(f, "digraph AST {\n");
    fprintf(f, "  node [fontname=\"Arial\"];\n");
    fprintf(f, "  edge [arrowsize=0.8, color=\"#555555\"];\n");

    if (f) {
        astToDotAux(root, f);
    } else {
        fprintf(f, "  \"Empty\" [label=\"Empty tree\"];\n");
    }

    fprintf(f, "}\n");
    fclose(f);
}
