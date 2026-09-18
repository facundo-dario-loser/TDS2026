PROGRAMAS_C =  frontend/analizador_lexico/lex.yy.c         \
			   frontend/analizador_sintactico/parser.tab.c \
			   utils/argument.c							   \
			   utils/debug.c							   \
			   main.c

main: frontend/analizador_lexico/lexer.l frontend/analizador_sintactico/parser.y $(PROGRAMAS_C)
	make -C frontend/analizador_lexico/
	make -C frontend/analizador_sintactico/ 
	gcc $(PROGRAMAS_C) -o build/c-tds


# reglas para ejecutar cada etapa del compilador:

# ejecuta solo el analizador lexico
test_lexer: build/c-tds
	python3 run_tests.py -target scan tests/lexer/ || python3 run_tests.py -target scan tests/lexer/

# ejecuta hasta el analisis sintactico
test_parser: build/c-tds
	python3 run_tests.py -target parse tests/parser/ || python3 run_tests.py -target parse tests/parser/

# ejecuta todas las etapas del compilador
test_general: build/c-tds
	python3 run_tests.py -o tests/general/ || python3 run_tests.py -o tests/general/


# reglas para correr un test en particular:
# quixa esto no hace falta ?????????????????

# la variable FILE_PATH se puede sobreescribir desde la terminal.
# ejemplo para sobre escribir FILE_PATH:
# make test_individual FILE_PATH=tests/parser/test5.ctds
FILE_PATH = /tests/general/test1.ctds # por default

test_individual: build/c-tds
	./build/c-tds -o a $(FILE_PATH)

test_individual_debug: build/c-tds
	./build/c-tds -debug $(FILE_PATH)

