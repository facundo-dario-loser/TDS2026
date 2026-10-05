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
    INSTRUCTION_TYPE_JMP,                    // salto incondicional
    INSTRUCTION_TYPE_JMP_ZERO,               // salto condicional
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
    INSTRUCTION_TYPE_PUSH_ARGUMENT,
    INSTRUCTION_TYPE_CALL_METHOD,
    INSTRUCTION_TYPE_RETURN,
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

void generateIntermediateCodeAux(AstNode *root, Instruction **tail);

// dado un tipo de instruccion lo retorna en forma de string
char * getInstructionTypeString(InstructionType instType);

// imprime la lista de instrucciones en la terminal
void printInstructions(Instruction *head);

// libera la lista enlazada de instrucciones
void freeInstructionLinkedList(Instruction *head);

// funciones para generar codigo intermedio para cada nodo
void generateIntermediateCodeNodeP(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeGlobalDeclList(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeVarDecl(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeMethodDeclList(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeMethodDecl(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeListId(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeId(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeParams(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeVoid(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeParam(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeBlock(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeBlockElems(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeStatements(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeType(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeAssignment(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeMethodCall(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeIfElse(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeWhile(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeReturn(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeListExpr(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeIntLiteral(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeFloatLiteral(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeBoolLiteral(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeAddition(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeSubtraction(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeMultiplication(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeDivision(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeMod(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeComparisonSmaller(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeComparisonGreater(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeEqual(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeAnd(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeOr(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeMinus(AstNode *node, Instruction **tail);
void generateIntermediateCodeNodeNegation(AstNode *node, Instruction **tail);

#endif // INTERMEDIATE_CODE_H
