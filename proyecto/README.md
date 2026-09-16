# TDS2026
repositorio de la materia Taller de Diseño de Software UNRC 2026

### Integrante: Loser Facundo Dario

## Instrucciones para compilar
si se cuenta con la herramienta `Make` instalada, ejecutar en la terminal:

```
cd proyecto
make
```

en caso de no tener `Make` entonces hacer:

```
cd proyecto

cd frontend/analizador_lexico/
flex lexer.l
cd ..

frontend/analizador_sintactico/
bison parser.y
cd ..

gcc frontend/analizador_lexico/lex.yy.c         \
	frontend/analizador_sintactico/parser.tab.c \
	utils/argument.c							\
	utils/debug.c							    \
	main.c -o build/c-tds
```

Esto creará un ejecutable llamado `c-tds` dentro de la carpeta `/proyecto/build/`.

## Uso

`./proyecto/build/c-tds -option path_to_file`

**Opciones**
- `-o <salida>` Renombra el archivo ejecutable a `<salida>`.
- `-target <etapa>` Indicar hasta que etapa ejecutar el proceso de compilación (todavia no esta implementado).
- `-opt` Aplicar optimizaciones (todavia no esta implementado).
- `-debug` Ejecuta la compilación con logs e información útil en la terminal.

<br>

**Etapas**
- `scan` ejecutar solo el análisis léxico.
- `parse` ejecutar hasta el análisis sintáctico.
- `codinter` ejecutar hasta la generación de código intermedio de bajo nivel.
- `assembly` ejecutar hasta la generación de assembly.

**Ejemplos de uso**

`./proyecto/build/c-tds -o main path_to_file/main.ctds`

`./proyecto/build/c-tds -target scan path_to_file/main.ctds`

`./proyecto/build/c-tds -opt path_to_file/main.ctds`

`./proyecto/build/c-tds -debug path_to_file/main.ctds`

## Organización
Dentro de la carpeta `/proyecto` se encuentran las siguientes carpetas y archivos:

**Carpetas**
- `/build` acá se guarda el ejecutable del compilador llamado `c-tds`.

- `/frontend` contiene los archivos correspondientes al frontend del compilador:
    - `/analizador_lexico` contiene el lexer dentro del archivo `lexer.l`.
    - `/analizador_sintactico` contiene el parser en el archivo `parser.y`.

- `/tests` contiene archivos con extensión `.ctds` para testear el compilador.

- `/utils` contiene archivos con utilidades.
    - `argument.h/.c` contiene funciones para obtener los argumentos y opciones con los que se ejecuta el compilador.
    - `debug.h/.c` contiene funciones y macros para debugear e imprimir errores.

**Archivos**

- `main.c` punto de entrada de todo el compilador

- `run_tests.py` script para ejecutar todos los tests automáticamente.

- `Makefile` archivo para compilar y ejecutar tests automáticamente

- `TODO.txt` sirve para anotar que cosas debo implementar/refatorizar/etc.

<br>

**Nota:**
Dentro de cada archivo `.h` se puede encontrar una descripción mas completa sobre que hace cada módulo.

## Ejecución automática de tests

Si se cuenta con la herramienta `Make` instalada hacer:

- para ejecutar los test normalmente (sin debuguear):
```
cd proyecto
make test
```

- para ejecutar los test con logs e informacion util en la terminal por cada test:
```
cd proyecto
make debug_test
```


en caso de no tener `Make` entonces hacer:
```
```

## Decisiones de diseno

- No se permiten comentarios multilinea anidados `/*.../**/...*/`. Ademas dentro del comentario solo se puede usar letras minusculas/mayusculas y numeros.


