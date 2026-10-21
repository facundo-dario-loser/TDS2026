# Documentación correspondiente a la entrega del generador de código objeto.
La implementación del generador de código objeto se encuentra en el path: `/proyecto/backend/generacion_assembly` en los archivos:<br> 
- `offsets.h/.c`.
- `assembly_instructions.h/.c`
- `assembly_gen.h/.c`

## Actualizaciones en el lexer
Ahora puede reconocer un nuevo token para la palabra reservada `extern`.

```
extern { DEBUG_LEXER("EXTERN"); return EXTERN; }
```

## Actualizaciones en el parser
Se extendio la gramática para permitir el uso de métodos externos (definidos en otro archivo).

```
method_decl: ...
           | EXTERN type ID '(' params ')' ';' { ... }
           | EXTERN type ID '(' ')' ';'        { ... }
           | EXTERN VOID ID '(' params ')' ';' { ... }
           | EXTERN VOID ID '(' ')' ';'        { ... }
           ;
```

Dentro de la carpeta `proyecto/files_to_link` contiene el archivo `print.c` con funciones para printear enteros y booleanos. De esta manera ahora es posible debugear programas linkeando el assembly generado por el compilador `c-tds` con este archivo de C para printear valores y variables.
Para usar alguna de estas funciones en un programa escribir entre las declaraciones de métodos:
- `extern void printInt(int n);`
- `extern void printBoolean(boolean n);`


## Actualizaciones en el AST
Se agrego un nuevo tipo de nodo: `AST_NODE_TYPE_EXTERN_METHOD_DECL`.
Sirve para representar las declaraciones de métodos externos en el AST.

## Actualizaciones en los símbolos y la tabla de simbolos
Se agregaron nuevos campos a los simbolos
```
typedef struct Symbol {
    ...
    int numberOfLocalVariables;
    int numberOfParameters;
} Symbol;
```

- `numberOfLocalVariables`: se utliza en métodos y es para saber el numero de variables locales (contando a los parametros tambien) que tiene. Esto es util para la generacion de assembly ya que en la llamada de un metodo se reserva espacio en el frame para las variables locales y parametros restandole al stack pointer un valor de acuerdo a cuantos bytes se necesiten.

- `numberOfParameters`: se utiliza en métodos y permite saber el numero de parametros del mismo. Esto es util en la generacion de assembly ya que si el numero de parametros es mayor a 6, entonces se hace pop de la pila al terminar la llamada a un metodo tantas veces como sea necesario (se hace numberOfParameters - 6 veces).

Tambien se agrego esta función

```
int getNumberOfParametersFromMethod(Symbol *params);
```

que dada la cabeza de la lista de parametros de un metodo, retorna la cantidad que hay. Luego este valor se usa para setear el campo `numberOfParameters` de un simbolo.

## Actualizaciones en el analizador semántico
En la funcion `semanticAnalysisAux`, se agrego un caso para analizar el nodo de declaración externa de metodo:
```
case AST_NODE_TYPE_EXTERN_METHOD_DECL: 
analysisNodeMethodDecl(root, st, tempCount); break;
```

En ese caso reutilice la misma función `analysisNodeMethodDecl` que ya tenia y lo unico que le tuve que modificar es que analice el cuerpo del metodo solamente si es un nodo de tipo declaración de metodo (no externo):

```
if (node->children4 && (node->type == AST_NODE_TYPE_METHOD_DECL)) {
        node->children4->isFunctionBlock = true;
        semanticAnalysisAux(node->children4, st, tempCount);
    }
```

Entonces en el caso de metodos externos, lo unico que se hace es insertar su simbolo correspondiente en la tabla de simbolos.

## Actualizaciones en el generador de código intermedio
Elimine las instrucciones de tipo `And` y `Or` ya que las operaciones `&&` y `||` las cambie para que tengan corto-circuito traduciendolas en comparaciones, saltos a labels y asignaciones.

## Seteo de offsets
En los archivos `offsets.h/.c` que se encuentran en el path `proyecto/backend/generacion_assembly` se implementa el seteo de offsets a los simbolos (son offsets respecto del rbp). Los archivos contienen las siguientes funciones:

Setea los offsets a todos los simbolos recorriendo la lista de instrucciones de codigo intermedio.
```
void setSymbolOffsets(Instruction *list);
```

printea el offset asignado a cada simbolo recorriendo la lista de código intermedio.
```
void printSymbolOffsets(Instruction *list);
```

## generador de assembly
Para la generación de assembly se generan instrucciones para la arquitectura x86_64. Se asumio que todas las variables son de 64 bits (8 bytes). Los archivos `assembly_gen.h/.c` que se encuentran en el path `proyecto/backend/generacion_assembly` implementan las funciones para generar el código assembly para cada tipo de instrucción de código intermedio.

La función `generateAssembly` es la principal y se encarga de crear el archivo assembly y luego llamar a `generateAssemblyAux` la cual a su vez recorre la lista de instrucciones de código intermedio y genera las instrucciones de assembly llamando a otras funciones. El nombre del archivo de assembly generado viene dado por `outputFileName`.
```
char * generateAssembly(Instruction *list, char *outputFileName);
void   generateAssemblyAux(Instruction *list, FILE *f);
```

Funciones para generar instrucciones de assembly x86_64 para cada tipo de instrucción de código intermedio.
```
void generateAssemblyInstructionGlobalVarDecl(Instruction *i, FILE *f);
void generateAssemblyInstructionBeginMethod(Instruction *i, FILE *f);
void generateAssemblyInstructionEndMethod(Instruction *i, FILE *f);
void generateAssemblyInstructionLabel(Instruction *i, FILE *f);
void generateAssemblyInstructionAssignmentIntInt(Instruction *i, FILE *f);
void generateAssemblyInstructionAssignmentIntFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionAssignmentFloatInt(Instruction *i, FILE *f);
void generateAssemblyInstructionAssignmentFloatFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionAssignmentBoolBool(Instruction *i, FILE *f);
void generateAssemblyInstructionAdditionIntInt(Instruction *i, FILE *f);
void generateAssemblyInstructionAdditionIntFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionAdditionFloatInt(Instruction *i, FILE *f);
void generateAssemblyInstructionAdditionFloatFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionArgument(Instruction *i, FILE *f);
void generateAssemblyInstructionCallMethod(Instruction *i, FILE *f);
void generateAssemblyInstructionReturn(Instruction *i, FILE *f);
void generateAssemblyInstructionSubtractionIntInt(Instruction *i, FILE *f);
void generateAssemblyInstructionSubtractionIntFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionSubtractionFloatInt(Instruction *i, FILE *f);
void generateAssemblyInstructionSubtractionFloatFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionMultiplicationIntInt(Instruction *i, FILE *f);
void generateAssemblyInstructionMultiplicationIntFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionMultiplicationFloatInt(Instruction *i, FILE *f);
void generateAssemblyInstructionMultiplicationFloatFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionDivisionIntInt(Instruction *i, FILE *f);
void generateAssemblyInstructionDivisionIntFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionDivisionFloatInt(Instruction *i, FILE *f);
void generateAssemblyInstructionDivisionFloatFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionModIntInt(Instruction *i, FILE *f);
void generateAssemblyInstructionModIntFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionModFloatInt(Instruction *i, FILE *f);
void generateAssemblyInstructionModFloatFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionComparisonSmallerIntInt(Instruction *i, FILE *f);
void generateAssemblyInstructionComparisonSmallerIntFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionComparisonSmallerFloatInt(Instruction *i, FILE *f);
void generateAssemblyInstructionComparisonSmallerFloatFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionComparisonGreaterIntInt(Instruction *i, FILE *f);
void generateAssemblyInstructionComparisonGreaterIntFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionComparisonGreaterFloatInt(Instruction *i, FILE *f);
void generateAssemblyInstructionComparisonGreaterFloatFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionUnaryMinusInt(Instruction *i, FILE *f);
void generateAssemblyInstructionUnaryMinusFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionNegation(Instruction *i, FILE *f);
void generateAssemblyInstructionJmpFalse(Instruction *i, FILE *f);
void generateAssemblyInstructionJmpTrue(Instruction *i, FILE *f);
void generateAssemblyInstructionJmp(Instruction *i, FILE *f);
void generateAssemblyInstructionEqual(Instruction *i, FILE *f);
```


## funciones que generan instrucciones assembly
Las funciones de los archivos `assembly_gen.h/.c` llaman a otras funciones a su vez que se encargan de escribir en un archivo las instrucciones de assembly. Estas otras funciones estan implementadas en los archivos `assembly_instructions.h/.c` ubicados en el path `proyecto/backend/generacion_assembly`.

<br>Se creo este struct para diferenciar entre comparaciones `<`, `>` y `==`. El mismo se usa en la funcion `cmp()`.
```
typedef enum ComparisonType {
    COMPARISON_TYPE_GREATER, // op1 > op2?  in cmp
    COMPARISON_TYPE_SMALLER, // op1 < op2?  in cmp
    COMPARISON_TYPE_EQUAL,   // op1 == op2? in cmp
} ComparisonType;
```

<br>**Lista de funciones:**
<br>**Nota**: estas funciones tienen en cuenta el tipo de los operandos (int, boolean o float) y si ademas son constantes, variables globales o variables locales. 
<br><br>Escribe un comentario de assembly (con `#`) en el archivo.
```
void comment(FILE *f, char *string);
```
<br>Escribe la directiva `.globl` para el ensamblador.
```
void globl(FILE *f, char *name);
```
<br>Escribe un label de método en el archivo.
```
void methodLabel(FILE *f, char *name);
```
<br>Escribe la instrucción `enter` en el archivo.
```
void enter(FILE *f, int numberOfBytes);
```
<br>Escribe la instrucción `mov src, dst` en el archivo.
```
void mov(FILE *f, Symbol *src, Symbol *dst);
```
<br>Escribe la instruccion `leave` en el archivo.
```
void leave(FILE *f);
```
<br>Escribe la instrucción `ret` en el archivo.
```
void ret(FILE *f);
```
<br>Escribe la instrucción `mov $0, %rax` en el archivo.
```
void movZeroRax(FILE *f);
```
<br>Genera una nueva linea en el archivo.
```
void newLine(FILE *f);
```
<br>Escribe las instrucciones `add op1, op2` y `mov op2, result` en el archivo.
```
void add(FILE *f, Symbol *op1, Symbol *op2, Symbol *result);
```
<br>Escribe las instrucciones para setear el registro `rax` con el valor que retorna un método (esta función se llama con un método que retorne una expresión obviamente).
```
void returnFromMethod(FILE *f, Symbol *symbolReturned);
```
<br>Escribe un label en el archivo.
```
void label(FILE *f, char *str);
```
<br>Escribe la instrucción `jmp label` en el archivo.
```
void jmp(FILE *f, char *label);
```
<br>Escribe las instrucciones `mov src, %r10` y `push %r10` en el archivo.
```
void push(FILE *f, Symbol *src);
```
<br>Genera el código para llamar a una rutina: `call nombre_rutina`.
```
void call(FILE *f, char *methodName);
```
<br>Genera la instrucción `mov %rax, temp`.
```
void movFromRaxToTemporal(FILE *f, Symbol *temp);
```
<br>Genera las intrucciones para hacer una comparación entre `op1` y `op2` dependiendo del valor de `compType` y deja el resultado de dicha comparacion en `result` (deja 0 o 1 en `result`).
```
void cmp(FILE *f, Symbol *op1, Symbol *op2, Symbol *result, ComparisonType compType);
```
<br>Escribe instrucciones para hacer un salto a `label` si `cond` es falsa.
```
void jmpToLabelIfFalse(FILE *f, Symbol *cond, char *label);
```
<br>Escribe instrucciones para hacer un salto a `label` si `cond` es verdadera.
```
void jmpToLabelIfTrue(FILE *f, Symbol *cond, char *label);
```
<br>Genera instrucciones para multiplicar `op1` con `op2` (`imul op1, op2`) y luego para guardar el resultado de la multiplicacion en `result`.
```
void imul(FILE *f, Symbol *op1, Symbol *op2, Symbol *result);
```
<br>Escribe instrucciones para negar (multiplicar por -1) el valor de `result` usando la instrucción `neg` (`result` es un simbolo de tipo int o float).
```
void neg(FILE *f, Symbol *op, Symbol *result);
```
<br>Genera instrucciones para invertir el valor de `result` (es un simbolo de tipo boolean).
```
void negationBoolean(FILE *f, Symbol *op, Symbol *result);
```
<br>Escribe instrucciones para hacer una division (`result` = `op1`/`op2`). Primero se mueve al registro `rax` el valor de op1 y se extiende el signo del mismo hacia el registro `rdx`. Luego se divide por el valor que tenga el registro `r10`. El resultado de la division queda en el `rax`.
```
void idiv(FILE *f, Symbol *op1, Symbol *op2, Symbol *result);
```
<br>Escribe instrucciones para hacer una resta (`result` = `op1` - `op2`).
```
void sub(FILE *f, Symbol *op1, Symbol *op2, Symbol *result);
```
<br>Genera instrucciones para hacer la operación de modulo (`result` = `op1` % `op2`). Es igual a la función de para hacer una division, pero al final se queda con el resto de la misma que se ubica en el registro `rdx`.
```
void mod(FILE *f, Symbol *op1, Symbol *op2, Symbol *result);
```
<br>Escribe la directiva de ensamblador `.data` en el archivo.
```
void dataSegment(FILE *f);
```
<br>Escribe directivas de ensamblador para una variable local en el archivo assembly. Todas las variables ocupan 64 bits.
```
void globalVarDecl(FILE *f, Symbol *globalVarSymbol);
```
<br>Escribe la directiva de ensamblador `.text` en el archivo.
```
void text(FILE *f);
```

<br>**Funciones auxiliares:**<br>
<br>Se utiliza para salvar todos los argumentos pasados a una rutina. Salva los primeros 6 argumentos de los registros y el resto si es que los hay los salva desde el stack. Todos los argumentos salvados los almacena en el stack nuevamente copiando los valores solamente. Esto implementa justamente el pasaje de parametros por copia/valor.
```
void saveAllArguments(Symbol *methodSymbol, FILE *f);
```
<br>Esta función mapea un numero entre 1 y 6 a un registro. Se utiliza para pasar argumentos a una rutina o salvarlos dentro de la misma.
```
char * getRegisterForArgument(int numberOfArgument);
```
<br>Genera instrucciones para pasar un argumento a un registro. Dado el argumento y el numero de argumento, mapea a que registro se lo debe salvar y lo guarda ahi.
```
void passArgumentToMethodInRegister(FILE *f, Symbol *argumentSymbol, int numberOfArgument);
```
<br>Dada una instrucción de tipo `INSTRUCTION_TYPE_ARGUMENT` cuyo número de argumento que se pasa es mayor a 6, lo que hace es seguir recorriendo la lista de instrucciones hasta llegar a la ultima instruccion de este tipo. Luego de esto comienza a pushear cada argumento en la pila y va recorriendo la lista en orden inverso hasta llegar a la instrucción que se paso originalmente. Esto justamente implementa la convencion de que si se pasan mas de 6 argumentos a un método, se debe hacer en el stack pusheandolos en orden inverso para que el metodo los reciba en el mismo orden que los tiene en sus parametros dado por el perfil del método.
```
Instruction * passArgumentsToMethodInStack(FILE *f, Instruction *argumentInstruction);
```
<br>Si se pasaron argumentos a un metodo en el stack, los popea de la pila luego de la llamada al mismo. En cada pop guarda el valor en el registro `r10`.
```
void popArgumentsFromStackAfterMethodCall(FILE *f, Symbol *methodSymbol);
```
