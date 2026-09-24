# Documentación correspondiente a la entrega de la tabla de simbolos y el árbol sintáctico abstracto (TS y AST)

## Tabla de símbolos (TS)
Su implementación se encuentra dentro de `/proyecto/tads` en los archivos `st.h/.c`.

Los simbolos se definen como:

```
typedef struct Symbol {
    SymbolType         type;
    char               *name;
    SymbolSemanticType semanticType;
    SymbolValue        value;
    struct Symbol      *parameters;
    struct Symbol      *next;       
    int                referenceCount;
    int                offset;
    bool               offsetSet;
} Symbol;
```

- `type` es el tipo de simbolo. Pueden ser de tipo variable, metodo/función o constate. En el caso de los simbolos correspondientes a parametros de funciones los voy a tratar como variables locales.

- `name` es el nombre del simbolo (que viene dado por el nombre de la variable, función o parámetro). En el caso de constantes su nombre es el string de su valor y para el caso de valores temporales su nombre es ti donde i es un entero natural.

- `semanticType` es el tipo semántico del simbolo (int, boolean, float). En el caso de funciones que retornan algo representa el tipo de la expresión que retorna.

- `value` permite guardar el valor del simbolo que puede ser un int, float o un booleano. Este campo es una union entre int, float y bool. Es util para constantes.

- `parameters` es una lista enlazada de simbolos que representan los parametros de una función. Este campo solo se usa si el tipo del simbolo es función.

- `next` puntero a otro simbolo. Permite crear una lista enlazada de simbolos. Es útil para crear la lista de parametros de una función y para crear la lista de simbolos en un nivel de la pila de la tabla de simbolos.

- `referenceCount` contador de punteros que hacen referencia al simbolo. Es útil a la hora de liberar el AST ya que varios nodos pueden apuntar a un mismo simbolo.

- `offset` es el offset del simbolo respecto del registro base rbp. Este campo sirve en la etapa de generación de assembly.

- `offsetSet` flag para saber si a un simbolo ya se le seteo su offset o no.

<br>La tabla de simbolos se implementa como una pila de niveles en donde cada nivel tiene una lista enlazada de simbolos.
La pila de niveles también esta implementada como una lista enlazada.

**Nivel:**<br>
El campo `head` es un puntero a la cabeza de la lista enlazada de simbolos del nivel correspondiente.<br>
`next` es un puntero al siguiente nivel (inferior). 
```
typedef struct Level {
    Symbol       *head;
    struct Level *next;
} Level;
```

**Tabla de símbolos:**<br>
Contiene simplemente el puntero al tope de la pila (que es la cabeza de la lista enlazada de niveles). Cada vez que se inserta un nuevo nivel se hace a la cabeza de la lista.
```
typedef struct SymbolTable {
    Level *top;
} SymbolTable;
```

<br>**Funciones de la tabla de símbolos:**<br><br>
Apila un nuevo nivel en el tope, insertando el nivel a la cabeza de la lista enlazada de la pila.
```
void newLevel(SymbolTable *st);
```

Elimina el nivel del tope de la pila.
```
void closeLevel(SymbolTable *st);
```

Dada la configuración de un símbolo, crea el simbolo y lo inserta en el nivel actual de la pila. Retorna true sii lo pudo insertar y false en otro caso (por ejemplo cuando ya existe el símbolo entonces no lo puede volver a insertar).<br> 
**Nota**: mas abajo se detalla que es el struct de configuración (en la sección 'Decisiones de diseño').
```
bool insertSymbol(SymbolTable *st, SymbolConfig *config);
```

Dado el nombre de un simbolo lo busca en toda la pila y retorna un puntero al mismo. Si no lo encuentra retorna NULL.
```
Symbol * searchSymbol(SymbolTable *st, char *name);
```

Printea la tabla de simbolos en la terminal.
```
void printSymbolTable(SymbolTable *st);
```

Libera la memoria de la pila de la tabla de simbolos. No elimina los simbolos de cada nivel ya que estos quedan apuntados por nodos del ast.
```
void freeSymbolTable(SymbolTable *st);
```

Libera la memoria para de un simbolo.
```
void freeSymbol(Symbol *s);
```

## Árbol sintáctico abstracto (AST)
Su implementación se encuentra dentro de `/proyecto/tads` en los archivos `ast.h/.c`.

El ast se define como:
```
typedef struct AstNode {
    AstNodeType            type;
    AstNodeDeclarationType declarationType;
    AstNodeValue           value;
    Symbol                 *symbol;
    struct AstNode         *children1;
    struct AstNode         *children2;
    struct AstNode         *children3;
    struct AstNode         *children4;
    bool                   hasReturn;
    int                    line;
} AstNode;
```

- `type` tipo de nodo del ast. Es un valor el enum `AstNodeType`.

- `declarationType` puede ser (int, float, boolean). En mi ast tengo un tipo de nodo que llamado 'AST_NODE_TYPE_TYPE' el cual es para el tipo de las declaraciones de variables o funciones. Entonces declarationType permite saber dado un nodo de estos si el type es int, float o boolean.<br>
**Ejemplo**: si tenemos `int x;` entonces tendriamos un nodo de tipo 'declaración de variable' con hijo izquierdo un nodo de tipo 'type' y con hijo derecho un nodo de tipo 'id'. Entonces en el nodo de tipo 'type' en el campo declarationType se le asigna que es int.<br>
Esta información se guarda temporalmente aqui y luego se traslada al simbolo correspondiente al crearse.

- `value` permite guardar un valor int, float, boolean o string. Sirve para guardar el valor de las constantes de manera temporal ya que luego durante el analisis semántico al crear los simbolos guardare este valor en los mismos.  

- `symbol` es un puntero a un símbolo de la tabla de simbolos.

- `children1`, `children2`, `children3`, `children4` son punteros a nodos hijos del ast. 

- `hasReturn` flag que es util para saber si una función que en el perfil indica que retorna algo, entonces chequear que en el cuerpo efectivamente tenga los return's correspondientes.

- `line` guarda la linea de una declaración, sentencia, etc. Sirve para indicar la linea cuando hay un error semántico. 

<br>**Funciones del AST**:<br>

Dada la configuración de un nodo, lo crea y retorna un puntero al mismo.<br>
**Nota**: mas abajo se detalla que es la estructura de configuración (en la sección 'Decisiones de diseño'). 
```
AstNode * newAstNode(AstNodeConfig *config);
```

Libera la memoria de todos los nodos (y simbolos a los que apuntan) del árbol.
```
void freeAst(AstNode *root);
```

## Decisiones de diseño

- La creación de los simbolos la decidi postergar para el análisis semántico. Si bien es posible crear todos los simbolos en el mismo parser a medida que se construye el ast, considere que no seria muy limpio dado que estaria obligado a hacerlo en el mismo archivo `parser.y` ya que necesito acceder a las variables de bison ($1, $2, ...). Ademas me parecia mas sencillo hacerlo en el análisis semántico ya que seguiría la misma estructura que tenia en el preproyecto.

- Tanto en `ast.h` como en `st.h` cree estructuras de 'configuración' para los simbolos y nodos del ast:

```
typedef struct SymbolConfig {
    SymbolType         type;
    char               *name;
    SymbolSemanticType semanticType;
    SymbolValue        value;
    struct Symbol      *parameters;
} SymbolConfig;

typedef struct AstNodeConfig {
    AstNodeType            type;
    AstNodeDeclarationType declarationType;
    AstNodeValue           value;
    AstNode                *children1;
    AstNode                *children2;
    AstNode                *children3;
    AstNode                *children4;
    int                    line;
} AstNodeConfig;
```

El objetivo de las mismas es hacer más fácil el diseño de las funciones que permiten crear simbolos y nodos del ast.<br>
`SymbolConfig` y `AstNodeConfig` contienen todos los campos que se podrian llegar a setear en la creación de un nuevo simbolo o nodo del ast.

```
bool      insertSymbol(SymbolTable *st, SymbolConfig *config);
AstNode * newAstNode(AstNodeConfig *config);
```
Este diseño permite que solo tenga una única función para crear nodos y lo mismo para crear nuevos simbolos usando pocos parametros. La razón por la cual ambas funciones toman un puntero a las configuraciones es por una cuestion de eficiencia (para evitar que se copie todo el struct).

Por ejemplo en el caso del ast en lugar de tener varias funciones para crear diferentes tipos de nodos o tener 1 sola función con muchos parametros, entonces le paso solo 1 estructura con los campos que me interesen setear.<br>
En el archivo `/proyecto/frontend/analizador_sintactico/parser.y` a su vez cuando llamo a newAstNode creo la estructura en la misma invocación.<br> 
Esta forma de crear e inicializar structs en C se llama `designated initializers`.<br> 
<br>**Ejemplo general**:
```
typedef struct MyStruct { ... } MyStruct;

MyStruct s = (MyStruct){
    .campo1 = valor1,
    .campo2 = valor2,
    ...
};
```

Los campos que no setee por defecto se setean en 0 para números y NULL para punteros.<br>
De esta manera logro 'simular' funciones que toman un numero variable de parametros y ademas en cualquier orden.
Esta práctica la aprendi de api's y bibliotecas modernas de C que lo suelen hacer.

**Ejemplo**<br>
A continuación muestro como crear diferentes tipos de nodos del ast usando la misma función y llenando solo los campos que me interesan en la configuración. Los mismos fueron sacados del archivo `parser.y`.<br>

Para los nodos de tipo `ID` llamo a newNode asi:
```
newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = $1});
``` 

Para los nodos de tipo `IF_ELSE` llamo a newNode asi:
```
newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_IF_ELSE, .children1 = $3, .children2 = $5, .children3 = $7});
```
donde children 1 es la condición, children2 es el nodo del bloque que se ejecuta si se cumple la condición y children3 es el nodo del else.
