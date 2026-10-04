# Documentación correspondiente a la entrega del analizador semántico
La implementación del analizador semántico se encuentra en el path: `/proyecto/frontend/analizador_semantico/` en los archivos `semantic_analysis.h/.c`.

## Modificaciones y actualizaciones en el AST
La implementacion del ast se encuentra en el path `/proyecto/tads/` en los archivos `ast.h/.c`.

- Dentro del enum `AstNodeType` tuve que agregar el tipo de nodo: `AST_NODE_TYPE_BLOCK` que es para los bloques { }. Antes directamente al abrir un bloque colocaba las decalraciones de varaibles y sentencia directamente, pero el problema que me encontre es que sin este nodo no iba a saber en que momento abrir un nuevo nivel en la tabla de simbolos.

- Dentro del struct `AstNode` agregue el campo: `bool isFunctionBlock;`. Basicamente los parametros de las funciones/metodos los trato como variables locales (variables que se declararon dentro del bloque principal de la funcion). Entonces cuando encuentro una decalracion de un metodo/funcion este tiene 4 hijos: el tipo de retorno, el id/nombre, los parametros y el cuerpo que es un bloque. Entonces al hijo que se corresponde con el bloque le bajo la informacion de que es un bloque de una funcion. Luego al procesar el bloque se abre un nuevo nivel en la tabla de simbolos y como tiene seteado el flag `isFunctionBlock` entonces lo que hace es en la tabal de simbolos ir un nivel hacia atras y buscar el simbolo de la funcion para extraer la lista de parametros (que es una lsita de simbolos) y entonces insertarla esta lista en el nivel corriente en la tabla de simbolos que se acaba de abrir.

- Dentro del struct `AstNode` agregue el campo: `SymbolVariableType     variableType;` que sirve para bajar informacion en los nodos y entonces al encontrar una declaracion de variable o parametro de una funcion cuando se cree el simbolo correspondiente se le pase la info de si es una variable local, global o si es un parametro. Esta informacion va a ser de utilidad en la generacion de codigo intermedio y generacion de assembly.

## Modificaciones y actualizaciones en los símbolos y la tabla de simbolos
La implementacion de los simbolos y la taba de simbolos se encuentra en el path `/proyecto/tads` en los archivos `st.h/.c`.

- Agregue este enum que permite saber si el simbolo de una variable corresponde a una variable global, local o si es un parametro de una funcion.

    ```
    typedef enum SymbolVariableType {
        SYMBOL_VARIABLE_TYPE_LOCAL,
        SYMBOL_VARIABLE_TYPE_GLOBAL,
        SYMBOL_VARIABLE_TYPE_PARAMETER,
    } SymbolVariableType;
    ```
    Esta informacion va a ser de utilidad en la generacion de codigo intermedio y en la generacion de assembly.
    Luego agregue en el struct `Symbol` el campo `SymbolVariableType variableType;`

- Modifique la funcion `insertSymbol` para que al chequear antes de insertar el nuevo simbolo que no colisione con otro simbolo del mismo nombre tambien chequee aparte del nombre que sea del mismo tipo (variable o funcion). Entonces es posible por ejemplo a nivel global tener una varaible llamada 'f' y una funcion con el nombre 'f' sin ningun problema.

    ```
    bool insertSymbol(SymbolTable *st, SymbolConfig *config) {
        if (!st) ERROR_ST("the symbol table is null (insertSymbol)")

        // chequear que no exista el simbolo en el nivel corriente
        Symbol *aux = st->top->head;

        while (aux) {
            if ((strcmp(aux->name, config->name) == 0) && (aux->type == config->type)) {
                return false; // ya existe el simbolo
            }
        
            aux = aux->next;
        }
        ...
    ```

- Modifique la funcion `searchSymbol` para que ahora ademas de apsarle el simbolo que se desea buscar en la tabla de simbolos, tambien se indique si lo que se busca es una variable o una funcion.
    ```
    Symbol * searchSymbol(SymbolTable *st, char *name, SymbolType sType) {
        if (!st) ERROR_ST("the symbol table is NULL (searchSymbol)")

        Level *currentLevel = st->top;

        while (currentLevel) {
            Symbol *aux = currentLevel->head;

            while (aux) {
                if ((strcmp(aux->name, name) == 0) && (aux->type == sType)) return aux;
                aux = aux->next;
            }

            currentLevel = currentLevel->next;
        }

        return NULL;
    }
    ```
    Esto lo tuve que hacer ya que podria tener el siguiente programa:
    ```
    int f;

    int f() {
        return f;
    }
    ```
    En donde dentro de la funcion 'f' cuando se llegue al return se encontrara que retorna una expresion que es un 'ID', luego se buscara en la tabla de simbolos el simbolo f (variable), pero como siempre inserto a la cabeza los simbolos en cada nivel de la pila de la tabla de simbolos, bajaria un nivel por fuera del bloque de la funcion y se quedaria parado en el nivel correspondiente al scope global que tendria los simbolos de f(funcion) y f(variable):
    ```
    level 1: -> NULL (dentro de la funcion f no hay ninguna variable).
      ^
      |
    level 0: -> [f:funcion] -> [f:variable] -> NULL
    ``` 
    Y encontraria primero el simbolo de la funcion 'f' y como tiene el nombre buscado, retornaria ese simbolo lo cual estaba mal.

- Agregue las funciones:

    Dado el tipo semantico de un simbolo (int, float o boolean), lo retorna en forma de string.
    ```
    char * getSemanticTypeString(SymbolSemanticType semanticType);
    ```

    Crea un nuevo simbolo a partir de una configuracion dada y lo retorna, pero no lo inserta en la tabla de simbolos. Si no pudo crear el simbolo retorna NULL.
    ```
    Symbol * newSymbol(SymbolConfig *config);
    ```

    Dada una lista enlazada de simbolos, la inserta en el nivel corriente de la tabla de simbolos. Esta funcion se utiliza para insertar la lista de parametros de una funcion en el nivel que corresponde al bloque principal de la misma. Es decir que los parametros se tratan como variables locales en el bloque principal de la funcion.
    ```
    void insertSymbolListInCurrentLevel(SymbolTable *st, Symbol *symbolList);
    ```

    Imprime la informacion de los campos del struct del simbolo en la terminal
    ```
    void printSymbolInfo(Symbol *s);
    ```

## Funciones del análisis semántico
La implementación del analizador semántico se encuentra en el path: `/proyecto/frontend/analizador_semantico/` en los archivos `semantic_analysis.h/.c`.<br>
El analisis semantico se realiza de manera recursiva sobre el ast obtenido luego del analisis sintactico.<br><br>
Las funciones que se implementaron son las siguientes:

- Funcion principal que crea la tabla de simbolos y llama a la funcion auxiliar descripta abajo con el mismo puntero al nodo root y la direccion de la tabla de simbolos que creo.
    ```
    void semanticAnalysis(AstNode *root);
    ```

- Funcion que chequea el nodo root y en base a su tipo llama a la funcion correspondiente para analizar cada tipo de nodo del ast. Ademas va guardando el puntero a la tabla de simbolos para no perderlo entre las llamadas recursivas y tambien lleva un puntero a un contador de cantidad de simbolos temporales creados para que cuando cree un nuevo temporal se le asigne correctamente el nombre (por ej: t0, t1, etc).
    ```
    void semanticAnalysisAux(AstNode *root, SymbolTable *st, int *tempCount);
    ```

- Funciones para analizar cada tipo de nodo del ast (una funcion por cada valor del enum `AstNodeType`). Cada una de estas recibe el nodo correspondiente, la tabla de simbolos y el contador de temporales:
    ```
    void analysisNodeP(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeGlobalDeclList(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeVarDecl(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeMethodDeclList(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeMethodDecl(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeListId(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeId(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeParams(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeVoid(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeParam(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeBlock(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeBlockElems(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeStatements(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeType(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeAssignment(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeMethodCall(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeIfElse(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeWhile(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeReturn(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeListExpr(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeIntLiteral(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeFloatLiteral(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeBoolLiteral(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeAddition(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeSubtraction(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeMultiplication(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeDivision(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeMod(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeComparisonSmaller(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeComparisonGreater(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeEqual(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeAnd(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeOr(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeMinus(AstNode *node, SymbolTable *st, int *tempCount);
    
    void analysisNodeNegation(AstNode *node, SymbolTable *st, int *tempCount);
    ```
    En la implementacion se pueden encontrar mas explicaciones en comentarios sobre que hace cada una de estas funciones.
    <br>
- **Funciones Auxiliares:**<br><br>
    Chequea que una funcion/metodo  que retorna una expresion entonces efectivamente en todas las posibles trazas dentro del cuerpo de la misma siempre se termine con un return. Es decir que nunca se deberia poder alcanzar el final de la funcion porque siempre hay un return antes.
    ```
    bool checkIfFunctionHasReturn(AstNode *node);
    ```
    Un nodo de declaracion de metodo/funcion tiene 4 hijos: el nodo tipo de retorno, el nodo id/nombre, el nodo parametros y el nodo del cuerpo. Esta funcion dado el nodo de parametros y dado un puntero a una lista enlazada de simbolos vacia, completa la lista enlazada con todos los parametros del metodo en el mismo orden que los tiene.
    ```
    void getSymbolParamList(AstNode *node, Symbol **symbolParamList); 
    ```
    Funcion auxiliar de 'getSymbolParamList' que se encarga de hacer todo el trabajo. Es una funcion recursiva y para poder obtener la lista de parametros de la funcion en el mismo orden debe insertar los simbolos siempre a la cola y para ello debe guardar en el parametro 'tail' la cola o ultimo elemento de la lista. 'symbolParamList' seria la cabeza de la lista.
    ```
    void getSymbolParamListAux(AstNode *node, Symbol **symbolParamList, Symbol **tail);
    ```
    Dado un nodo del ast correspondiente a una constante, crea el simbolo para dicha constante y hace que ese nodo apunte al simbolo creado.
    ```
    void setLiteralSymbolInAstNode(AstNode *nodeLiteral);
    ```
    Dado un valor del enum DeclarationType del ast, que era para guardar el tipo (int, float, boolean o void) en un nodo type de una declaracion de funcion o metodo, retorna el tipo semantico equivalente para poder crear un simbolo luego.
    ```
    SymbolSemanticType getSymbolSemanticTypeFromAstNodeDeclarationType(AstNodeDeclarationType declType);
    ```
    Funcion para analizar semanticamente nodos correspondientes a operadores binarios aritmeticos (`+`, `-`, `*`, `/`, `%`).
    ```
    void analysisArithmeticBinaryOperator(AstNode *arithBinOpNode, SymbolTable *st, int *tempCount);
    ```
    Funcion para analizar semanticamente nodos correspondientes a operadores binarios logicos (`&&` and, `||` or).
    ```
    void analysisLogicalBinaryOperator(AstNode *logicalBinOpNode, SymbolTable *st, int *tempCount);
    ```
    Funcion para analizar semanticamente nodos correspondientes a operadores binarios de comparacion (`<`, `>`).
    ```
    void analysisComparisonOperator(AstNode *comparisonOpNode, SymbolTable *st, int *tempCount);
    ```

## Chequeos semánticos
En el analisis semantico se chequearon los 14 puntos del enunciado del proyecto:

**1.** Ningun identificador es declarado dos veces en un mismo bloque.

**2.** Ningun identificador es usado antes de ser declarado.

**3.** Todo programa contiene la definicion de un metodo llamado main. Este metodo no tiene parametros. Notar que la ejecucion comienza con el metodo main.

**4.** El numero y tipos de los argumentos en una invocacion a un metodo debe ser iguales al numero y tipos declarados en la definicion del metodo (los parametros formales y los reales deben ser iguales).

**5.** Si la invocacion a un metodo es usada como una expresion, el metodo debe retornar un resultado.

**6.** Una sentencia return solo tiene asociada una expresion si el metodo retorna un valor, si le metodo no retorna un valor (es un metodo void) entonces la sentencia return no puede tener asociada ninguna expresion.

**7.** La expresion en una sentencia return debe ser igual al tipo de retorno declarado para el metodo.

**8.** Un ⟨id⟩ usado como una ⟨location⟩ debe estar declarado como un parametro o como una variable local o global.

**9.** La ⟨expr⟩ en una sentencia if o while debe ser boolean.

**10.** Los operandos de ⟨arith op⟩’s y ⟨rel op⟩’s deben ser de tipo int o float.

**11.** Los operandos de ⟨eq op⟩’s (==) deben tener el mismo tipo (int, o float boolean).

**12.** Los operandos de ⟨cond op⟩’s y el operando de la negacion (!) deben ser de tipo boolean.

**13.** La ⟨location⟩ y la ⟨expr⟩ en una asignacion, ⟨location⟩ = ⟨expr⟩, deben tener el mismo tipo.

**14.** Se permiten coerciones o truncamientos entre int y float

Y como chequeo extra tambien hice:

**15.** En el caso de metodos que retornen una expresion (int, float o boolean) entonces se debe chequear que en el cuerpo del metodo en todas las posibles trazas siempre se termina con un 'return expr;'. Es decir un metodo que retorne algo al ejecutarse no se deberia poder alcanzar el fin del metodo por que se salio del mismo previamente con un return.

**Aclaraciones extra**:

- Cada vez que hay un nuevo bloque `{}` se abre un nuevo nivel en la pila de la tabla de simbolos.

- En las declaraciones de metodos/funciones el simbolo correspondiente a la funcion se inserta en el nivel actual 'n' y todas los simbolos correspondientes a declaraciones de variables dentro del cuerpo del metodo se insertan en el nivel 'n + 1' o niveles mas profundos si se abren mas sub bloques dentro del cuerpo.

- Los parametros de una funcion son tratados como variables locales del bloque principal de la funcion. Por lo que no se puede declarar ninguna variable con el mismo nombre que un parametro dentro del bloque principal de la funcion. Pero si es posible abrir nuevos sub bloques dentro del cuerpo de la funcion y declarar variables con los mismos nombres que los parametros.
Por ejemplo esto no se puede hacer:
    ```
    void f(int x, int y) {
        int x; // ERROR
    }
    ```
    Pero esto si se puede hacer:
    ```
    void f(int x, int y) {
        {
            int x;
        }
    }
    ```

- En cuanto a los casteos, en las expresiones resultantes de las operaciones: `+`, `-`, `*`, `/` y `%` si alguno de los operandos es de tipo `float` y el otro de tipo `int`, este ultimo de casteara a tipo `float` y el resultado final sera de tipo `float`.
<br>Tambien en el caso de asignaciones si la variable es de tipo `float` y la expresion que se le asigna es de tipo `int`, esta ultima se casteara a `float`. Y si la variable es de tipo `int` y la expresion es de tipo `float`, esta ultima se casteara a `int` (es un casteo que producira un truncamiento por lo que se perdera informacion del `float`).
<br>En cualquiera de estos casos de casteo, el compilador emitira un mensaje de warning indicando el mismo.

- Luego de terminar el analisis semantico todos los nodos de tipo `ID` correspondientes a una misma variable, van a apuntar a un mismo simbolo de la variable. <br>Todos los nodos `ID` correspondientes a un mismo metodo van a apuntar a un mismo simbolo correspondiente al metodo.<br>Por cada nodo de tipo literal (intLiteral, floatLiteral y boolLiteral) se va a crear un nuevo simbolo para esa constante/literal y se va a dejar al nodo apuntando al simbolo creado.<br>Por cada nodo correspondiente a alguna de estas expresiones: `methodCall`, `+`, `-(binario)`, `*`, `/`, `%`, `<`, `>`, `==`, `&&`, `||`, `-(unario)` y `!` se va a crear un simbolo de una variable temporal cuyo proposito sera guardar el resultado de evaluar dicha expresion. Luego se deja al nodo correspondiente apuntando al simbolo del temporal creado.

