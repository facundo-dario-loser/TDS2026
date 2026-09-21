# TDS2026 (Proyecto)
Repositorio de la materia Taller de Diseño de Software UNRC 2026

### Integrante: Loser Facundo Dario

## Entregas
La entrega de cada etapa se hace en el branch correspodiente.

## Instrucciones para compilar
**Nota:** el repositorio ya provee un ejecutable llamado `c-tds` en la carpeta `/proyecto/build/`. El mismo es para Linux x86_64. Si tiene otro sistema operativo o arquitectura debera seguir las instrucciones de abajo para compilar el proyecto.

Si se cuenta con la herramienta `Make` instalada, ejecutar en la terminal:

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
Ejemplo para ejecutar en la terminal:<br>
`./proyecto/build/c-tds -option path_to_file`

**Opciones**
- `-o <salida>` Renombra el archivo ejecutable a `<salida>`.
- `-target <etapa>` Indicar hasta que etapa ejecutar el proceso de compilación (implementado parcialmente).
- `-opt` Aplicar optimizaciones (todavia no esta implementado).
- `-debug` Ejecuta el compilador con logs e información útil en la terminal.

<br>

**Etapas**
- `scan` ejecutar solo el análisis léxico.
- `parse` ejecutar hasta el análisis sintáctico.
- `codinter` ejecutar hasta la generación de código intermedio de bajo nivel (no implementado aun).
- `assembly` ejecutar hasta la generación de assembly (no implementado aun).

**Ejemplos de uso**

`./proyecto/build/c-tds -o main path_to_file/main.ctds`

`./proyecto/build/c-tds -target scan path_to_file/main.ctds`

`./proyecto/build/c-tds -opt path_to_file/main.ctds`

`./proyecto/build/c-tds -debug path_to_file/main.ctds`

**Nota:** si se ejecuta el compilador con la opcion `-o <salida>` o `-target <etapa>` no se producira ninguna salida (a excepción de los errores). Solamente con `-debug` se pueden visualizar los logs de cada etapa.

## Ejecución automática de tests
El proyecto cuenta con un script de python y reglas en el Makefile que permiten ejecutar tests automaticamente. Debera contar obligatoriamente con Make y un interprete de python instalados.

Dentro de la carpeta `/proyecto/tests` se encuentran las subcarpetas:
- `/lexer`: tests para la etapa del analisis lexico.
- `/parser`: tests para la etapa del analisis sintactico.
- `/general`: tests generales para todas las etapas del compilador.

Cada una de estas carpetas a su vez tiene dos subcarpetas `/positive` y `/negative` con tests que deben pasar y tests que no deben pasar respectivemente. 

**Uso**: <br>
Para poder correr los tests debe ejecutar las siguientes reglas de Make en la terminal:

Ejecutar los tests para la etapa de **análisis léxico**:
```
make test_lexer
```

Ejecutar los tests para la etapa de **análisis sintáctico**:
```
make test_parser
```

Ejecutar los tests **generales**:
```
make test_general
```

Cada una de estas reglas de Make llama al script `run_tests.py` que se encuentra en `/proyecto`. Este script se corre 2 veces (una para los tests en `/positive` y otra para los tests en `/negative`). El mismo genera un log indicando cada test que va corriendo y si este paso o no (TEST PASSED o TEST FAILED). En el caso de los tests que fallaron tambien se muestra un mensaje adicional del compilador informando los errores especificos.<br>
Finalmente muestra un resumen (SUMMARY) con los tests que pasaron y los que fallaron. Al ejecutar el script se mostraran 2 resúmenes ya que el script se corre 2 veces como se menciono tanto para los tests que deben pasar como para los que deben fallar.

**Nota:** si se desea, puede agregar mas tests a las carpetas respectivas y ejecutarlos con las reglas de Make dadas.

## Documentación
El archivo `Documentation.md` dentro de `/proyecto` contiene una descripcion mas detallada del proyecto junto con decisiones diseño para la etapa correspondiente.

## Organización
Dentro de la carpeta `/proyecto` se encuentran las siguientes subcarpetas y archivos:

**Carpetas:**
- `/build` acá se guarda el ejecutable del compilador llamado `c-tds`.

- `/frontend` contiene subcarpetas correspondientes al frontend del compilador:
    - `/analizador_lexico` contiene el lexer dentro del archivo `lexer.l`.
    - `/analizador_sintactico` contiene el parser en el archivo `parser.y`.

- `/tests` contiene subcarpetas con tests correspondientes a cada etapa implementada del compilador. Los tests son archivos `.ctds`.
    - `/lexer` contiene tests correspondientes a la etapa del analisis lexico.
    - `/parser` contiene tests correspondientes a la etapa del analisis sintactico.
    - `/general` contiene tests que no corresponden a ninguna etapa en concreto.

- `/utils` contiene archivos con utilidades.
    - `argument.h/.c` tiene funciones para obtener los argumentos y opciones con los que se ejecuta el compilador.
    - `debug.h/.c` tiene funciones y macros para debugear e imprimir errores.

**Archivos:**

- `main.c` punto de entrada de todo el compilador.

- `run_tests.py` script para ejecutar tests automáticamente.

- `Makefile` archivo para compilar y ejecutar tests automáticamente.

- `TODO.txt` para anotar que cosas debo implementar, refactorizar, ideas, etc.

- `Documentation.md`: archivo markdown con documentacion mas detallada del proyecto.

<br>

**Nota:**
Dentro de cada archivo `.h` y `.c` se pueden encontrar comentarios con una descripción mas completa sobre que hace cada módulo y que hacen sus funciones, macros y tipos de datos.



