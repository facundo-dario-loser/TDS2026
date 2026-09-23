# Documentación correspondiente a la entrega de la tabla de simbolos y el árbol sintáctico abstracto (TS y AST)

## Tabla de simbolos (TS)
Su implementacion se encuentra dentro de `/proyecto/tads` en los archivos `st.h/.c`.

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

- `type` es el tipo de simbolo. Los simbolos pueden ser de tipo variable, metodo/funcion o constate. Para el caso de los simbolos correspondientes a parametros de funciones los voy a tratar como variables locales.

- `name` es el nombre del simbolo (que viene dado por el nombre de la varaible, funcion o parametro). En el caso de constantes su nombre es el string de su valor y para el caso de valores temporales su nombre es ti donde i es un entero natural.

- `semanticType` es el tipo semantico del simbolo (int, boolean, float). En el caso de funciones que retornan algo representa el tipo de la expresion que retorna.

- `value` permite guardar el valor del simbolo que puede ser un int, float o booleano. Este campo es una union entre int, float y bool. Es util para constantes.

- `parameters` es una lista enlazada de simbolos que representan los parametros de una funcion. Este campo solo se usa si el tipo del simbolo es funcion.

- `next` puntero a otro simbolo. permite crear una lista enlazada de simbolos. Es util para crear la lista de parametros de una funcion y para crear la lista de simbolos de un nivel en la pila de la tabla de simbolos.

- `referenceCount` contador de punteros hacen referencia al simbolo. Es util a la hora de liberar el AST ya que varios nodos pueden apuntar a un mismo simbolo.

- `offset` es el offset del simbolo respecto del registro base rbp. Este campo es util en la etapa de generacion de assembly.

- `offsetSet` flag para saber si a un simbolo ya se le seteo cual va a ser su offset o no.

**Nota**: Para el caso de los simbolos correspondientes a parametros de funciones los voy a tratar como variables locales.


La tabla de simbolos se implementa como una pila de niveles en donde cada nivel tiene una lista enlazada de simbolos.
La pila de niveles tambien esta implementada como una lista enlazada.

**Nivel:**<br>
El campo `head` es un puntero a la cabeza de la lista enlazada de simbolos del nivel correspondiente.<br>
`next` es un puntero al siguiente nivel (inferior). 
```
typedef struct Level {
    Symbol       *head;
    struct Level *next;
} Level;
```

**Tabla de simbolos:**<br>
Contiene simplemente el puntero al tope de la pila (que es la cabeza de la lista enlazada de niveles). Cada vez que se inserta un nuevo nivel se hace a la cabeza de la lista.
```
typedef struct SymbolTable {
    Level *top;
} SymbolTable;
```

<br>**Funciones de la tabla de simbolos:**<br><br>
Apila un nuevo nivel en el tope insertando el nivel a la cabeza de la lista enlazada de la pila.
```
void newLevel(SymbolTable *st);
```

Elimina el nivel del tope de la pila.
```
void closeLevel(SymbolTable *st);
```

Dada la configuracion de un simbolo, crea el simbolo y lo inserta en el nivel actual de la pila. Retorna true sii lo pudo insertar y false en otro caso (por ejemplo cuando ya existe el simbolo entonces no lo puede volver a insertar).
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
Su implementacion se encuentra dentro de `/proyecto/tads` en los archivos `ast.h/.c`.

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

- `declarationType` puede ser (int, float, boolean). En mi ast tengo un tipo de nodo que es: `AST_NODE_TYPE_TYPE` el cual es para el tipo de las declaraciones de variables o funciones. Entonces `declarationType` permite saber dado un nodo de type si es int, float o boolean.

- `value` permite guardar un int, float, boolean o string. Es util para guardar el valor de las constantes de manera temporal ya que luego durante el analisis semantico al crear los simbolos guardare este valor en los mismos.  

- `symbol` es un puntero a un simbolo de la tabla de simbolos.

- `children1`, `children2`, `children3`, `children4` son punteros a nodos hijos del ast. 

- `hasReturn` flag que es util para saber si una funcion que en el perfil indica que tiene retorna algo, entonces chequear que en el cuerpo efectivamente tenga return's;

- `line` guarda la linea de una declaracion, sentencia, etc. Sirve para indicar la linea cuando hay un error semantico. 

## Decisiones de diseño

- La creacion de los simbolos la decidi postergar para el analisis semantico. Si bien es posible crear todos los simbolos en el mismo parser a medida que se construye el ast, considere que no seria muy limpio dado que estaria obligado a hacerlo en el mismo archivo `parser.y` ya que necesito acceder a las variables de bison ($1, $2, ...).

- Tanto en `ast.h` como en `st.h` cree estructuras de 'configuracion' para los simbolos y nodos del ast:

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

El objetivo de las mismas es para hacer mas facil el diseño de las funciones que permiten crear simbolos y nodos del ast.<br>
`SymbolConfig` y `AstNodeConfig` contienen todos los campos que se podrian llegar a setear en la creacion de un nuevo simbolo o nodo del ast.

```
bool      insertSymbol(SymbolTable *st, SymbolConfig *config);
AstNode * newAstNode(AstNodeConfig *config);
```
este diseño permite que solo tenga una unica funcion para crear nodos y lo mismo para crear nuevos simbolos. La razon por la cual ambas funciones toman un puntero a las configuraciones es por una cuestion de eficiencia (para evitar que se copie todo el struct).

Por ejemplo en el caso del ast en lugar de tener varias funciones para crear diferentes tipos de nodos o tener 1 sola funcion con muchos parametros, entonces le paso solo 1 estructura con los campos que me interesen setear.<br>
En el archivo `/proyecto/frontend/analizador_sintactico/parser.y` a su vez cuando llamo a newAstNode creo la estructura en la misma invocacion.<br> 
Esta forma de crear e inicializar structs en C se llama `designated initializers`. Los campos que no setee por defecto se setean en 0 para numeros y NULL para punteros.<br>
De esta manera logro 'simular' funciones que toman un numero variable de parametros y ademas en cualquier orden.
Esta practica la aprendi de api's y bibliotecas modernas de C que lo suelen hacer.

**Ejemplo**<br>
A continuacion muestro como crear diferentes tipos de nodos del ast usando la misma funcion y llenando solo los campos que me interesan en la configuracion. Los mismos fueron sacados del archivo `parser.y`.<br>

Para los nodos de tipo `ID` llamo a newNode asi:
```
newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = $1});
``` 

Para los nodos de tipo `IF_ELSE` llamo a newNode asi:
```
newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_IF_ELSE, .children1 = $3, .children2 = $5, .children3 = $7});
```
donde children 1 es la condicion, children2 es el nodo del bloque que se ejecuta si se cumple la condicion y children3 es el nodo del else.

## Problemas que tuve
- ??
