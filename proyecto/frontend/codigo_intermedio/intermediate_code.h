#ifndef INTERMEDIATE_CODE_H
#define INTERMEDIATE_CODE_H

#include "../../tads/st.h"
#include "../../utils/debug.h"
#include "../../tads/ast.h"

typedef enum InstructionType {
    INSTRUCTION_TYPE_GLOBAL_VAR_DECL,                // para meter las var globales en el .data
    INSTRUCTION_TYPE_BEGIN_METHOD,                   // label de inicio de declaracion de metodo
    INSTRUCTION_TYPE_END_METHOD,                     // label de fin de declaracion de metodo
    INSTRUCTION_TYPE_LABEL,                          // label/etiqueta 
    INSTRUCTION_TYPE_ASSIGNMENT_INT_INT,             // result(int) = op1(int)
    INSTRUCTION_TYPE_ASSIGNMENT_INT_FLOAT,           // result(int) = op1(float)
    INSTRUCTION_TYPE_ASSIGNMENT_FLOAT_INT,           // result(float) = op1(int)
    INSTRUCTION_TYPE_ASSIGNMENT_FLOAT_FLOAT,         // result(float) = op1(float)
    INSTRUCTION_TYPE_ASSIGNMENT_BOOL_BOOL,           // result(boolean) = op1(boolean)
    INSTRUCTION_TYPE_ADDITION_INT_INT,               // result(int) = op1(int) + op2(int)
    INSTRUCTION_TYPE_ADDITION_INT_FLOAT,             // result(float) = op1(int) + op2(float)
    INSTRUCTION_TYPE_ADDITION_FLOAT_INT,             // result(float) = op1(float) + op2(int)
    INSTRUCTION_TYPE_ADDITION_FLOAT_FLOAT,           // result(float) = op1(float) + op2(float)
    INSTRUCTION_TYPE_AND,                            // result(boolean) = op1(boolean) && op2(boolean)
    INSTRUCTION_TYPE_OR,                             // result(boolean) = op1(boolean) || op2(boolean)
    INSTRUCTION_TYPE_ARGUMENT,                       // pasar arg en un registro o en la pila (en llamada a un metodo)
    INSTRUCTION_TYPE_CALL_METHOD,           
    INSTRUCTION_TYPE_RETURN,
    INSTRUCTION_TYPE_SUBTRACTION_INT_INT,            // result(int) = op1(int) - op2(int)
    INSTRUCTION_TYPE_SUBTRACTION_INT_FLOAT,          // result(float) = op1(int) - op2(float)
    INSTRUCTION_TYPE_SUBTRACTION_FLOAT_INT,          // result(float) = op1(float) - op2(int)
    INSTRUCTION_TYPE_SUBTRACTION_FLOAT_FLOAT,        // result(float) = op1(float) - op2(float)
    INSTRUCTION_TYPE_MULTIPLICATION_INT_INT,         // result(int) = op1(int) * op2(int)
    INSTRUCTION_TYPE_MULTIPLICATION_INT_FLOAT,       // result(float) = op1(int) * op2(float)
    INSTRUCTION_TYPE_MULTIPLICATION_FLOAT_INT,       // result(float) = op1(float) * op2(int)
    INSTRUCTION_TYPE_MULTIPLICATION_FLOAT_FLOAT,     // result(float) = op1(float) * op2(float)
    INSTRUCTION_TYPE_DIVISION_INT_INT,               // result(int) = op1(int) / op2(int)
    INSTRUCTION_TYPE_DIVISION_INT_FLOAT,             // result(float) = op1(int) / op2(float)
    INSTRUCTION_TYPE_DIVISION_FLOAT_INT,             // result(float) = op1(float) / op2(int)
    INSTRUCTION_TYPE_DIVISION_FLOAT_FLOAT,           // result(float) = op1(float) / op2(float)
    INSTRUCTION_TYPE_MOD_INT_INT,                    // result(int) = op1(int) % op2(int)
    INSTRUCTION_TYPE_MOD_INT_FLOAT,                  // result(float) = op1(int) % op2(float)
    INSTRUCTION_TYPE_MOD_FLOAT_INT,                  // result(float) = op1(float) % op2(int)
    INSTRUCTION_TYPE_MOD_FLOAT_FLOAT,                // result(float) = op1(float) % op2(float)
    INSTRUCTION_TYPE_COMPARISON_SMALLER_INT_INT,     // result(boolean) = op1(int) < op2(int)
    INSTRUCTION_TYPE_COMPARISON_SMALLER_INT_FLOAT,   // result(boolean) = op1(int) < op2(float)
    INSTRUCTION_TYPE_COMPARISON_SMALLER_FLOAT_INT,   // result(boolean) = op1(float) < op2(int)
    INSTRUCTION_TYPE_COMPARISON_SMALLER_FLOAT_FLOAT, // result(boolean) = op1(float) < op2(float)
    INSTRUCTION_TYPE_COMPARISON_GREATER_INT_INT,     // result(boolean) = op1(int) > op2(int)
    INSTRUCTION_TYPE_COMPARISON_GREATER_INT_FLOAT,   // result(boolean) = op1(int) > op2(float)
    INSTRUCTION_TYPE_COMPARISON_GREATER_FLOAT_INT,   // result(boolean) = op1(float) > op2(int)
    INSTRUCTION_TYPE_COMPARISON_GREATER_FLOAT_FLOAT, // result(boolean) = op1(float) > op2(float)
    INSTRUCTION_TYPE_UNARY_MINUS_INT,                // result(int) = -op1(int)
    INSTRUCTION_TYPE_UNARY_MINUS_FLOAT,              // result(float) = -op1(float)
    INSTRUCTION_TYPE_NEGATION,                       // result(boolean) = !op1(boolean)
    INSTRUCTION_TYPE_JMP_FALSE,                      // salta a la etiqueta del result si op1 es false (salto condicional)
    INSTRUCTION_TYPE_JMP,                            // salto incondicional. salta lal label/etiqueta de result
    INSTRUCTION_TYPE_EQUAL,                          // result(boolean) = a == b
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

// funcion auxiliar para generar el codigo intermedio
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

// genera codigo intermedio para nodos correspondientes a operaciones binarias aritmeticas (+, -, *, /, %)
void generateIntermediateCodeArithmeticBinaryOperation(AstNode *node, Instruction **tail, int *labelCount);

// genera codigo intermedio para nodos correspondientes a operaciones de comparacion (<, >)
void generateIntermediateCodeComparisonBinaryOperation(AstNode *node, Instruction **tail, int *labelCount);

// genera codigo intermedio para nodos correspondientes a operaciones binarias logicas/booleanas (&&, ||)
void generateIntermediateCodeLogicalBinaryOperation(AstNode *node, Instruction **tail, int *labelCount);

#endif // INTERMEDIATE_CODE_H
