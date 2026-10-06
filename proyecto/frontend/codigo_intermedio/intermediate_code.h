#ifndef INTERMEDIATE_CODE_H
#define INTERMEDIATE_CODE_H

#include "../../tads/st.h"
#include "../../utils/debug.h"
#include "../../tads/ast.h"

typedef enum InstructionType {
    INSTRUCTION_GLOBAL_VAR_DECL,            // para meter las var globales en el .data
    INSTRUCTION_TYPE_BEGIN_METHOD,
    INSTRUCTION_TYPE_END_METHOD,
    INSTRUCTION_TYPE_LABEL,                  // label/etiqueta 
    INSTRUCTION_TYPE_ASSIGNMENT_INT_INT,     // int var = expr_int
    INSTRUCTION_TYPE_ASSIGNMENT_INT_FLOAT,   // int var = expr_float
    INSTRUCTION_TYPE_ASSIGNMENT_FLOAT_INT,   // float var = expr_int
    INSTRUCTION_TYPE_ASSIGNMENT_FLOAT_FLOAT, // float var = expr_float
    INSTRUCTION_TYPE_ASSIGNMENT_BOOL_BOOL,   // boolean var = expr_boolean
    INSTRUCTION_TYPE_ADDITION_INT_INT,
    INSTRUCTION_TYPE_ADDITION_INT_FLOAT,
    INSTRUCTION_TYPE_ADDITION_FLOAT_INT,
    INSTRUCTION_TYPE_ADDITION_FLOAT_FLOAT,
    INSTRUCTION_TYPE_AND,
    INSTRUCTION_TYPE_OR,
    INSTRUCTION_TYPE_PUSH_ARGUMENT,
    INSTRUCTION_TYPE_CALL_METHOD,
    INSTRUCTION_TYPE_RETURN,
    INSTRUCTION_TYPE_SUBTRACTION_INT_INT,
    INSTRUCTION_TYPE_SUBTRACTION_INT_FLOAT,
    INSTRUCTION_TYPE_SUBTRACTION_FLOAT_INT,
    INSTRUCTION_TYPE_SUBTRACTION_FLOAT_FLOAT,
    INSTRUCTION_TYPE_MULTIPLICATION_INT_INT,
    INSTRUCTION_TYPE_MULTIPLICATION_INT_FLOAT,
    INSTRUCTION_TYPE_MULTIPLICATION_FLOAT_INT,
    INSTRUCTION_TYPE_MULTIPLICATION_FLOAT_FLOAT,
    INSTRUCTION_TYPE_DIVISION_INT_INT,
    INSTRUCTION_TYPE_DIVISION_INT_FLOAT,
    INSTRUCTION_TYPE_DIVISION_FLOAT_INT,
    INSTRUCTION_TYPE_DIVISION_FLOAT_FLOAT,
    INSTRUCTION_TYPE_MOD_INT_INT,
    INSTRUCTION_TYPE_MOD_INT_FLOAT,
    INSTRUCTION_TYPE_MOD_FLOAT_INT,
    INSTRUCTION_TYPE_MOD_FLOAT_FLOAT,
    INSTRUCTION_TYPE_COMPARISON_SMALLER_INT_INT,
    INSTRUCTION_TYPE_COMPARISON_SMALLER_INT_FLOAT,
    INSTRUCTION_TYPE_COMPARISON_SMALLER_FLOAT_INT,
    INSTRUCTION_TYPE_COMPARISON_SMALLER_FLOAT_FLOAT,
    INSTRUCTION_TYPE_COMPARISON_GREATER_INT_INT,
    INSTRUCTION_TYPE_COMPARISON_GREATER_INT_FLOAT,
    INSTRUCTION_TYPE_COMPARISON_GREATER_FLOAT_INT,
    INSTRUCTION_TYPE_COMPARISON_GREATER_FLOAT_FLOAT,
    INSTRUCTION_TYPE_UNARY_MINUS_INT,
    INSTRUCTION_TYPE_UNARY_MINUS_FLOAT, 
    INSTRUCTION_TYPE_NEGATION,
    INSTRUCTION_TYPE_JMP_ZERO, // salta a la etiqueta del result si op1 es 0 (salto condicional)
    INSTRUCTION_TYPE_JMP,      // salto incondicional
    INSTRUCTION_TYPE_EQUAL,    // a == b
} InstructionType;

typedef struct Instruction {
    InstructionType    type;
    Symbol             *op1;
    Symbol             *op2;
    Symbol             *result;
    struct Instruction *next; // lista doblemente enlazada
    struct Instruction *prev;
} Instruction;

typedef struct InstructionConfig {
    InstructionType    type;
    Symbol             *op1;
    Symbol             *op2;
    Symbol             *result;
} InstructionConfig;

Instruction * newInstruction(InstructionConfig *config);

// inserta la instruccion a la cola
void insertInstruction(Instruction **tail, Instruction *i);

// dada la raiz del ast, retorna una lista enlazada de instrucciones
Instruction * generateIntermediateCode(AstNode *root);

void generateIntermediateCodeAux(AstNode *root, Instruction **tail, int *labelCount);

// dado un tipo de instruccion lo retorna en forma de string
char * getInstructionTypeString(InstructionType instType);

// imprime la lista de instrucciones en la terminal
void printInstructions(Instruction *head);

// libera la lista enlazada de instrucciones
void freeInstructionLinkedList(Instruction *head);

// funciones para generar codigo intermedio para cada nodo
void generateIntermediateCodeNodeP(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeGlobalDeclList(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeVarDecl(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeMethodDeclList(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeMethodDecl(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeListId(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeId(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeParams(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeVoid(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeParam(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeBlock(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeBlockElems(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeStatements(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeType(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeAssignment(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeMethodCall(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeIfElse(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeWhile(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeReturn(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeListExpr(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeIntLiteral(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeFloatLiteral(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeBoolLiteral(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeAddition(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeSubtraction(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeMultiplication(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeDivision(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeMod(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeComparisonSmaller(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeComparisonGreater(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeEqual(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeAnd(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeOr(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeMinus(AstNode *node, Instruction **tail, int *labelCount);
void generateIntermediateCodeNodeNegation(AstNode *node, Instruction **tail, int *labelCount);

#endif // INTERMEDIATE_CODE_H
