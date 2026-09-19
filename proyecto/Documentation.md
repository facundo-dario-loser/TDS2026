# Documentación correspondiente a la entrega del analizador sintáctico y léxico (Scanner y Parser)

## Análisis léxico (Scanner)
El lexer se encuentra en el path `/proyecto/frontend/analizador_lexico/lexer.l`.<br> 
A continuación se detallan los tokens del lenguaje reconocidos con flex indicando la expresión regular y el token que se retorna:

- **Palabras reservadas:** 
    - `int` (retorna el token `INT`)
    - `boolean` (retorna el token `BOOLEAN`)
    - `void` (retorna el token `VOID`)
    - `float` (retorna el token `FLOAT`)
    - `if` (retorna el token `IF`)
    - `else` (retorna el token `ELSE`)
    - `while` (retorna el token `WHILE`)
    - `return` (retorna el token `RETURN`)

- **Operadores binarios aritmeticos:**
    - `+` (retorna el token `'+'`)
    - `-` (retorna el token `'-'`)
    - `*` (retorna el token `'*'`)
    - `/` (retorna el token `'/'`)
    - `%` (retorna el token `'%'`)

- **Operadores binarios relacionales:**
    - `>` (retorna el token `'>'`)
    - `<` (retorna el token `'<'`)
    - `==` (retorna el token `EQUAL`)

- **Operadores binarios logicos:**
    - `&&` (retorna el token `AND`)
    - `||` (retorna el token `OR`)

- **Operador de asignacion:**
    - `=` (retorna el token `'='`)

- **Operadores unarios:**
    - `!` (retorna el token `'!'`)
    - `-` (retorna el token `'-'`)

- **Constantes enteras:**
    - `[0-9][0-9]*` (retorna el token `INT_LITERAL`)

- **Constantes float:** 
    - `[0-9][0-9]*.[0-9][0-9]*` (retorna el token `FLOAT_LITERAL`)

- **Constantes booleanas:**
    - `true` (retorna el token `BOOL_LITERAL`)
    - `false` (retorna el token `BOOL_LITERAL`)

- **Delimitadores:**
    - `(` (retorna el token `'('`)
    - `)` (retorna el token `')'`)
    - `{` (retorna el token `'{'`)
    - `}` (retorna el token `'}'`)
    - `;` (retorna el token `';'`)
    - `,` (retorna el token `','`)

- **Comentarios de una linea:**
    - `"//".*` (no retorna ningun token)
 
- **Identificadores:** 
    - `[a-zA-Z][a-zA-Z0-9_]*` (retorna el token `ID`)

- **Comentarios multilinea:** para esto primero se reconoce con flex  el inicio del comentario `/*` y luego se salta a la función `void processMultilineComment(void)` que se encarga manualmente de reconocer el comentario.

## Análisis sintáctico (Parser)
El parser en encuentra en el path `/proyecto/frontend/analizador_sintactico`. 

**Precedencia de operadores y asociatividad**<br>
Los operadores estan ordenados de menor a mayor prioridad:<br>
- `OR` (asociativo a izquierda) <-- menor prioridad<br> 
- `AND` (asociativo a izquierda) <br> 
- `EQUAL` (no es asociativo)<br>  
- `<, >` (tienen la misma precedencia y no son asociativos)<br> 
- `-, +` (tienen la misma precedencia y son asociativos a izquierda)<br>
- `*, /, %` (tienen la misma precedencia y son asociativos a izquierda) <br>
- `UMINUS, !` (tienen la misma precedencia) <-- maxima prioridad<br>

## Gramática del lenguaje
**Nota:** la gramatica aca no esta escrita con reglas de bison para que sea mas legible.<br>
El archivo `parser.y` ubicado en el path `/proyecto/frontend/analizador_sintactico` contiene la gramatica descripta con reglas de bison.

```
p                -> global_decl_list

global_decl_list -> var_decl global_decl_list
global_decl_list -> method_decl_list

method_decl_list -> method_decl method_decl_list
method_decl_list -> λ

var_decl         -> type list_id ';'

list_id          -> ID
list_id          -> ID ',' list_id

method_decl      -> type ID '(' params ')' block
method_decl      -> type ID '(' ')' block
method_decl      -> VOID ID '(' params ')' block
method_decl      -> VOID ID '(' ')' block

params           -> param ',' params
params           -> param

param            -> type ID

block            -> '{' block_elems '}'

block_elems      -> var_decl block_elems
block_elems      -> statements

type             -> INT
type             -> BOOLEAN
type             -> FLOAT

statements       -> statement statements
statements       -> λ

statement        -> ID '=' expr ';'
statement        -> method_call ';'
statement        -> IF '(' expr ')' block
statement        -> IF '(' expr ')' block ELSE block
statement        -> WHILE '(' expr ')' block
statement        -> RETURN expr ';'
statement        -> RETURN ';' 
statement        -> ';'
statement        -> block

method_call      -> ID '(' ')'
method_call      -> ID '(' list_expr ')'

list_expr        -> expr ',' list_expr
list_expr        -> expr

expr             -> ID
expr             -> method_call
expr             -> literal
expr             -> INT_LITERAL
expr             -> FLOAT_LITERAL
expr             -> BOOL_LITERAL
expr             -> expr '+' expr
expr             -> expr '-' expr 
expr             -> expr '*' expr 
expr             -> expr '/' expr
expr             -> expr '%' expr
expr             -> expr '<' expr
expr             -> expr '>' expr
expr             -> expr EQUAL expr
expr             -> expr AND expr
expr             -> expr OR expr
expr             -> '-' expr
expr             -> '!' expr
expr             -> '(' expr ')'
```

## Decisiones de diseño
- No se permiten comentarios multilinea anidados `/*../*...*/...*/`. Pero es posible meter un comentario de una linea dentro de un comentario de varias lineas `/*...//...*/`.

- El procesamiento de comentarios multilinea decidi hacerlo manualmente ya que era complejo dar una expresion regular para los mismos.
Basicamente flex se encargar de reconocer la apertura del comentario `/*` y luego salta a mi propia función para consumir el resto del comentario: <br>`void processMultilineComment(void)`.<br>
La misma utiliza por abajo la funcion `input()` y la macro `unput(c)` de flex.<br>

    Flex internamente lo que hace al abrir un archivo es ir cargando partes del mismo en un buffer en lugar de ir leyendo caracter por caracter del archivo directamente.
Entonces:<br>
    - `input()` es una función que retorna el caracter que esta leyendo actualmente el cabezal de lectura en el buffer y luego avanza en una posicion el cabezal.

    - `unput(c)` es una macro que vuelve a pushear en el buffer de lectura el caracter 'c' y mueve el cabezal de lectura una posicion para atras. Esta macro expande en la funcion 'yyunput'.

    La función `void processMultilineComment(void)` va leyendo el proximo caracter con `input()` para saber si lo proximo es el cierre del comentario `*/` y por ende terminar la lectura o si se esta intentado abrir otro comentario anidado dentro `/*` lo cual es un error. Ademas va guardando los caracteres que lee en un arreglo ya que `yytext` no esta guardando la cadena leida. <br>La implementación de esta función se encuentra en el archivo `/proyecto/frontend/analizador_lexico/lexer.l`. Puede consultar el mismo para mas detalles.

- Toda la funcionalidad para hacer logs (utiles para debugear) e información de errores estan implementada en los archivos `debug.h/.c` en la carpeta `/proyecto/utils/`. Decidi crear el módulo porque es mucho mas limpio para manejar los logs y errores asi que con un printf() o exit()  directamente.
Dentro del mismo tenemos las macros:
    - `TODO(msg)`: se utiliza en en funciones o partes del programa que aun no cuentan con una implementación. Permite hacer implementaciones parciales e informar si entramos en la rama/bloque sin implementar. Luego finaliza el programa terminando el proceso con exit().

    - `LOG(msgSrc, ...)`: permite hacer un print normal si se ejecuto el compilador con la opcion `-debug`. Se le debe pasar un valor de un enumerado indicando de donde proviene el mensaje.

    - `ERROR(msgSrc, ...)`: permite hacer un log de un mensaje indicando que ocurrio un error y mostrando de donde proviene el error. Luego finaliza el programa terminando el proceso con exit().

    La razon por la cual decidí usar macros y no funciones es por el hecho que necesitaba en si hacer wrappers alrededor de printf() y como uno podria pasar un numero variable de argumentos, entonces me resultaba mucho mas facil y rapido de implementar con una macro variadica en lugar de con una función variadica. Con una función variadica se debe acceder a cada argumento reccoriendo con un puntero en un ciclo. En cambio en una macro variadica se puede utilizar la macro `__VA_ARGS__` que reemplaza justamente `__VA_ARGS__` por todos los argumentos pasados en `...` (argumentos variables).<br>
    Si bien abusar de macros en C no es buena practica, en este caso facilitaba la implementacion y mantenia la legibilidad del codigo.

- El manejo de argumentos pasados por la linea de comandos se implementa en los archivos `argument.h/.c` que se encuentran en la carpeta `/proyecto/utils/`. Este modulo ofrece funciones para obtener los argumentos pasados al compilador (que son la 'opcion' y la 'etapa' en caso de haber usado la opcion `-target`). Luego provee 4 funciones que permiten ejecutar el compilador de acuerdo a la opcion elegida.

    - `void processOptionO(int argc, char *argv[]);`: para ejecutar el compilador con la opcion `-o <nombre_ejecutable>`.

    - `void processOptionTarget(int argc, char *argv[]);`: para ejecutar el compilador con la opcion `-target <etapa>` (solo se implementaron las etapas 'scan' y 'parse'). 

    - `void processOptionOpt(int argc, char *argv[]);`: para ejecutar el compilador con la opcion `-opt` (no implementado aun).

    - `void processOptionDebug(int argc, char *argv[]);`: para ejecutar el compilador con la opcion `-debug`.


## Problemas que tuve
- Tuve dificultad para dar una expresión regular para los comentarios multilinea. Al principio solo permitia hacer comentarios que contuvieran letras y numeros con la expresion regular `"/*"[a-zA-Z0-9]*"*/"` pero era muy limitada y ademas no era capaz de dar un mensaje de error apropiado en caso de que en el programa se abriera un comentario multilinea con `/*` pero nunca se cerrara y entonces termine creando la funcion `void processMultilineComment(void)` como se explico anteriormente.

- Otro problema menor fue que tuve que diferenciar de alguna forma el `-(menos binario)` del `-(menos unario)` y entonces en la gramática escrita en el parser use la directiva de bison `%precedence UMINUS` para crear un 'pseudotoken' y luego indique en la regla de las expresiones: `expr: '-' expr %prec UMINUS` para que cuando se entre por esa regla se use la precedencia del menos unario.<br> 
**Aclaración:** 'UMINUS' es por 'UNARY MINUS' (menos unario).


