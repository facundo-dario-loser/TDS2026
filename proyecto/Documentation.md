# Documentación correspondiente a la entrega del generador de código intermedio.
La implementación del generador de código intermedio se encuentra en el path: `/proyecto/frontend/codigo_intermedio/` en los archivos `intermediate_code.h/.c`.

## Actualizaciones en el AST
implemente una nueva funcion que dado el tipo de un nodo, lo retorna en forma de string:

```
char * getAstNodeTypeString(AstNodeType nodeType);
```
Se utiliza para debugear.

## Actualizaciones en los símbolos y la tabla de simbolos
agregue esta funcion que dado el tipo de un simbolo, lo retorna en forma de string:
```
char * getSymbolTypeString(SymbolType sType);
```
Se utiliza para debugear.

Por otro lado agregue un nuevo tipo de simbolo que es el de label
```
typedef enum SymbolType {
    SYMBOL_TYPE_VARIABLE,
    SYMBOL_TYPE_METHOD,
    SYMBOL_TYPE_CONSTANT,
    SYMBOL_TYPE_LABEL,    // <----
} SymbolType;
```
Este nuevo tipo de simbolo es útil para la generación de código intermedio ya que hay instrucciones que denotan un label y uno de sus operandos debe apuntar a un simbolo de tipo label justamente.

## Correciones y actualizaciones en el analizador semántico
En la funcion que se encarga de analizar semanticamente los nodos para los operadores `<` y `>`:
```
void analysisComparisonOperator(AstNode *comparisonOpNode, SymbolTable *st, int *tempCount)
```
corregi un error conceptual, ya que antes para los operadores de comparacion solo permitia que sus operandos fueran literales de enteros, reales o un id, pero esto es erroneo ya que por ejemplo no podria usar como uno de sus operando una llamada a un metodo que retorne un int.
Entonces modifique el chequeo para que solo permita expresiones aritmeticas (las cuales abarcan a los id y literales enteras o reales y ademas permiten por ejemplo llamadas a metodo que retonen un int o float).
Ademas agregue warnings de casteo, en donde si uno de los operandos es un float y el otro un int, el operando de tipo int se casteara a float.

## Instrucciones de código intermedio
A continuacion se listan y detalla la semántica de cada una de las instrucciones de codigo intermedio que siguen la estructura del codigo de 3 direcciones.

Todas las instrucciones tienen esta estructura:
```
INSTRUCTION_NAME op1 op2 result
```
dónde `INSTRUCTION_NAME` es el nombre de la instrucción, `op1` es el operando 1, `op2` el operando 2 y `result` el operando donde se almacena el resultado.

**Tipos de instrucciones:**<br><br>
Identifica que hay una declaración de variable global.
`result` apunta al simbolo de la variable global.
```
INSTRUCTION_TYPE_GLOBAL_VAR_DECL
```

<br>Esta es una pseudo instrucción ya que hace de etiqueta/label para identificar que comienza la declaración de un método.
`result` apunta al simbolo del método.
```
INSTRUCTION_TYPE_BEGIN_METHOD
```

<br>Esta es una pseudo instrucción ya que hace de etiqueta/label para identificar que termina la declaración de un método.
`result` apunta al simbolo del método.
```
INSTRUCTION_TYPE_END_METHOD
```

<br>Esta es una pseudo instrucción que sirve para denotar un label en el código. `result` apunta al simbolo del label.
```
INSTRUCTION_TYPE_LABEL
```

<br>Conjunto de instrucciones instrucciones que indican que hay una asignación en donde a una variable de tipo int o float se le asigna una expresión de tipo int o float.
El `op1` apunta al simbolo de la expresión y `result` apunta al simbolo de la variable a la cual se le asigna la expresión.
```
INSTRUCTION_TYPE_ASSIGNMENT_INT_INT     // result(int)   = op1(int)
INSTRUCTION_TYPE_ASSIGNMENT_INT_FLOAT   // result(int)   = op1(float)
INSTRUCTION_TYPE_ASSIGNMENT_FLOAT_INT   // result(float) = op1(int) 
INSTRUCTION_TYPE_ASSIGNMENT_FLOAT_FLOAT // result(float) = op1(float)
```

<br>Instrucción que indica que hay una asignación en donde a una variable de tipo boolean se le asigna una expresión booleana.
El `op1` apunta al simbolo de la expresión y `result` apunta al simbolo de la variable a la cual se le asigna la expresión.
```
INSTRUCTION_TYPE_ASSIGNMENT_BOOL_BOOL // result(boolean) = op1(boolean)
```

<br>Instrucción que denota la operación 'and' lógico (&&). `op1` apunta al simbolo de la expresión izquierda del and y `op2` apunta al simbolo de la expresión derecha. `result` apunta al simbolo donde se guardara el resultado del and.
```
INSTRUCTION_TYPE_AND // result(boolean) = op1(boolean) && op2(boolean)
```

<br>Instrucción que denota la operación 'or' lógico (||). `op1` apunta al simbolo de la expresión izquierda del or y `op2` apunta al simbolo de la expresión derecha. `result` apunta al simbolo donde se guardara el resultado del or.
```
INSTRUCTION_TYPE_OR // result(boolean) = op1(boolean) || op2(boolean)
```

<br>Instrucción que indica que se esta pasando un argumento para la invocación de un método. Luego en Assembly se interpreta como que se debe pasar el argumento en un registro o en la pila si no hay mas lugar. `result` apunta al simbolo del argumento. 
```
INSTRUCTION_TYPE_ARGUMENT
```

<br>Instrucción que indica que hay una llamada a un método. `op1` apunta al simbolo del método y si es que este retorna una expresión, entonces `result` apunta al simbolo del temporal donde se almacenara el resultado de la invocación.
```
INSTRUCTION_TYPE_CALL_METHOD
```

<br>Instrucción que denota un return. `result` apunta al simbolo de la expresión que se retorna.
```
INSTRUCTION_TYPE_RETURN
```

<br>Conjunto de instrucciones que indican que hay una suma entre dos operandos que puede ser de tipo int o float. `op1` apunta al simbolo del operando izquierdo, `op2` apunta al simbolo del operando derecho y `result` apunta al simbolo del temporal donde se almacenara el resultado de la suma.
```
// result(int) = op1(int) + op2(int)
INSTRUCTION_TYPE_ADDITION_INT_INT

// result(float) = op1(int) + op2(float)
INSTRUCTION_TYPE_ADDITION_INT_FLOAT

// result(float) = op1(float) + op2(int)
INSTRUCTION_TYPE_ADDITION_FLOAT_INT

// result(float) = op1(float) + op2(float)
INSTRUCTION_TYPE_ADDITION_FLOAT_FLOAT
```

<br>Conjunto de instrucciones que indican que hay una resta entre dos operandos que puede ser de tipo int o float. `op1` apunta al simbolo del operando izquierdo, `op2` apunta al simbolo del operando derecho y `result` apunta al simbolo del temporal donde se almacenara el resultado de la resta.
```
// result(int) = op1(int) - op2(int)
INSTRUCTION_TYPE_SUBTRACTION_INT_INT

// result(float) = op1(int) - op2(float)
INSTRUCTION_TYPE_SUBTRACTION_INT_FLOAT

// result(float) = op1(float) - op2(int)
INSTRUCTION_TYPE_SUBTRACTION_FLOAT_INT

// result(float) = op1(float) - op2(float)
INSTRUCTION_TYPE_SUBTRACTION_FLOAT_FLOAT
```

<br>Conjunto de instrucciones que indican que hay una multiplicación entre dos operandos que puede ser de tipo int o float. `op1` apunta al simbolo del operando izquierdo, `op2` apunta al simbolo del operando derecho y `result` apunta al simbolo del temporal donde se almacenara el resultado de la multiplicación.
```
// result(int) = op1(int) * op2(int)
INSTRUCTION_TYPE_MULTIPLICATION_INT_INT

// result(float) = op1(int) * op2(float)
INSTRUCTION_TYPE_MULTIPLICATION_INT_FLOAT

// result(float) = op1(float) * op2(int)
INSTRUCTION_TYPE_MULTIPLICATION_FLOAT_INT

// result(float) = op1(float) * op2(float)
INSTRUCTION_TYPE_MULTIPLICATION_FLOAT_FLOAT
```

<br>Conjunto de instrucciones que indican que hay una división entre dos operandos que puede ser de tipo int o float. `op1` apunta al simbolo del operando izquierdo, `op2` apunta al simbolo del operando derecho y `result` apunta al simbolo del temporal donde se almacenara el resultado de la división.
```
// result(int) = op1(int) / op2(int)
INSTRUCTION_TYPE_DIVISION_INT_INT

// result(float) = op1(int) / op2(float)
INSTRUCTION_TYPE_DIVISION_INT_FLOAT

// result(float) = op1(float) / op2(int)
INSTRUCTION_TYPE_DIVISION_FLOAT_INT

// result(float) = op1(float) / op2(float)
INSTRUCTION_TYPE_DIVISION_FLOAT_FLOAT
```

<br>Conjunto de instrucciones que indican que hay una operación de móodulo entre dos operandos que puede ser de tipo int o float. `op1` apunta al simbolo del operando izquierdo, `op2` apunta al simbolo del operando derecho y `result` apunta al simbolo del temporal donde se almacenara el resultado del móodulo.
```
// result(int) = op1(int) % op2(int)
INSTRUCTION_TYPE_MOD_INT_INT

// result(float) = op1(int) % op2(float)
INSTRUCTION_TYPE_MOD_INT_FLOAT

// result(float) = op1(float) % op2(int)
INSTRUCTION_TYPE_MOD_FLOAT_INT

// result(float) = op1(float) % op2(float)
INSTRUCTION_TYPE_MOD_FLOAT_FLOAT
```

<br>Conjunto de instrucciones que indican que hay una operación de comparación `<`. `op1` apunta al simbolo del operando izquierdo, `op2` apunta al simbolo del operando derecho y `result` apunta al simbolo del temporal donde se almacenara el resultado de la operación.
```
// result(boolean) = op1(int) < op2(int) 
INSTRUCTION_TYPE_COMPARISON_SMALLER_INT_INT

// result(boolean) = op1(int) < op2(float)
INSTRUCTION_TYPE_COMPARISON_SMALLER_INT_FLOAT

// result(boolean) = op1(float) < op2(int)
INSTRUCTION_TYPE_COMPARISON_SMALLER_FLOAT_INT

// result(boolean) = op1(float) < op2(float)
INSTRUCTION_TYPE_COMPARISON_SMALLER_FLOAT_FLOAT
```

<br>Conjunto de instrucciones que indican que hay una operación de comparación `>`. `op1` apunta al simbolo del operando izquierdo, `op2` apunta al simbolo del operando derecho y `result` apunta al simbolo del temporal donde se almacenara el resultado de la operación.
```
// result(boolean) = op1(int) > op2(int) 
INSTRUCTION_TYPE_COMPARISON_GREATER_INT_INT

// result(boolean) = op1(int) > op2(float)
INSTRUCTION_TYPE_COMPARISON_GREATER_INT_FLOAT

// result(boolean) = op1(float) > op2(int)
INSTRUCTION_TYPE_COMPARISON_GREATER_FLOAT_INT

// result(boolean) = op1(float) > op2(float)
INSTRUCTION_TYPE_COMPARISON_GREATER_FLOAT_FLOAT
```

<br>Conjunto de instrucciones que indican que se multiplico por -1 a una expresión aritmetica (se aplico el `-` unario a la expresión). `op1` apunta al simbolo del operando y `result` apunta al simbolo del temporal donde de almacenara el resultado de aplicarle el `-` a la expresión.
```
INSTRUCTION_TYPE_UNARY_MINUS_INT   // result(int)   = -op1(int)
INSTRUCTION_TYPE_UNARY_MINUS_FLOAT // result(float) = -op2(float)
```

<br>Instrucción que denota la operación de negación `!`. `op1` apunta al simbolo del operando y `result` apunta al simbolo donde se almacenara el resultado de la operación.
```
INSTRUCTION_TYPE_NEGATION // result(boolean) = !op1(boolean)
```
<br>Instrucción que indica un salto/jump condicional. `op1` apunta al simbolo del operando (que es un booleano) y `result` apunta a un simbolo que denota una etiqueta/label. Si `op1` es false entonces se saltaria a la etiqueta de `result`.
```
INSTRUCTION_TYPE_JMP_FALSE // if (!op1(boolean)) goto result(label)
```

<br>Instrucción que indica un salto/jump incondicional. `result` apunta a un simbolo que denota la etiqueta/label a la que se salta.
```
INSTRUCTION_TYPE_JMP // goto result(label)
```

<br>Instrucción que indica que hay una operación de comparación por iguales `==`. `op1` apunta al simbolo del operando izquierdo, `op2` apunta al simbolo del operando derecho y `result` apunta al simbolo del temporal donde se almacena el resultado de la comparación.
```
INSTRUCTION_TYPE_EQUAL // result(boolean) = op1 == op2
```

## Estructura de una instrucción
La implentación de las instrucciones y la generación de código intermedio se encuentra en el path `frontend/codigo_intermedio` en los archivos `intermediate_code.h/.c`.

```
typedef struct Instruction {
    InstructionType    type;
    Symbol             *op1;
    Symbol             *op2;
    Symbol             *result;
    struct Instruction *next;
    struct Instruction *prev;
} Instruction;
```

Dónde:
- **type**: es el tipo de la instrucción (alguno de los ya listados anteriormente).
- **op1**: puntero al simbolo del operando 1.
- **op2**: puntero al simbolo del operando 2.
- **result**: puntero al simbolo del resultado. 
- **next**: puntero a la proxima instrucción.
- **prev**: puntero a la instrucción previa.

Como resultado de la generación de código intermedio se retorna una lista doblemente enlazada de instrucciones (por eso existen los campos `next` y `prev`).

Por otro lado también implemente esta estructura:

```
typedef struct InstructionConfig {
    InstructionType    type;
    Symbol             *op1;
    Symbol             *op2;
    Symbol             *result;
} InstructionConfig;
```

que contiene todos los campos que se podria llegar a setear en la creación de una nueva instrucción. Sigue la misma lógica que ya utilice con los nodos y simbolos comom explique anteriormente en las entregas respectivas. 
La razón de este struct es para que la función que crea una isntrucción solo tome un parámetro que es este config. Esto me evita hacer varias funciones para crear una instrucción o tener que hacer una función pero con muchos parametros. Ademas me permite pasar solo los campos que me interesan.  

## Funciones del generador de código intermedio

Función que dada la configuración de una instrucción crea una nueva instrucción y la retorna.
```
Instruction * newInstruction(InstructionConfig *config);
```

<br>Función que dada una instrucción y la cola de una lista enlazada, inserta la instrucción al final de la lista.
```
void insertInstruction(Instruction **tail, Instruction *i);
```

<br>Función que genera el código intermedio. Toma como parametro la raiz del ast y retorna una lista doblemente enlazada de isntrucciones. Llama a la función auxiliar de abajo.
```
Instruction * generateIntermediateCode(AstNode *root);
```

<br>Función auxiliar que genera el código intermedio. Toma como parametro la raiz del ast, la cola de una lista enlazada y un contador de labels. Cada vez que inserta una nueva instrucción en la lista lo hace al final de la misma usando el puntero a la cola y ademas necesita llevar el contador de labels ya que los mismos se identifican por su numero (label_1, label_2, etc).
```
void generateIntermediateCodeAux(AstNode *root, Instruction **tail, int *labelCount);
```

<br>Función que dado el tipo de una instrucción, lo retorna en forma de string.
```
char * getInstructionTypeString(InstructionType instType);
```

<br>Función que dada la cabeza de una lista enlazada de instrucciones, las imprime a todas en la terminal.
```
void printInstructions(Instruction *head);
```

<br>Función que dada la cabeza de una lista enlazada de instrucciones, libera la memoria para cada una.
```
void freeInstructionLinkedList(Instruction *head);
```

<br>Funciones para generan instrucciones de código intermedio para cada tipo de nodo del ast. Todas toman un puntero al nodo, la cola de la lista de instrucciones y el contador de labels. 
```
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
```

<br>Función auxiliar para generar código intermedio para los nodos del ast que se corresponden con operaciones binarias aritmeticas (`+`, `-`, `*`, `/` y `%`).
```
void generateIntermediateCodeArithmeticBinaryOperation(AstNode *node, Instruction **tail, int *labelCount);
```

<br>Función auxiliar para generar código intermedio para los los nodos del ast que se corresponden con operaciones binarias de comparación (`<` y `>`).
```
void generateIntermediateCodeComparisonBinaryOperation(AstNode *node, Instruction **tail, int *labelCount);
```

<br>Función auxiliar para generar código intermedio para los nodos del ast  que se corresponden con operaciones binarias lógicas/booleanas (`&&` y `||`).
```
void generateIntermediateCodeLogicalBinaryOperation(AstNode *node, Instruction **tail, int *labelCount);
```
