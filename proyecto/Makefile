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
	python3 run_tests.py -target scan tests/lexer/positive/ || python3 run_tests.py -target scan tests/lexer/positive/
	python3 run_tests.py -target scan tests/lexer/negative/ || python3 run_tests.py -target scan tests/lexer/negative/

# ejecuta hasta el analisis sintactico
test_parser: build/c-tds
	python3 run_tests.py -target parse tests/parser/positive/ || python3 run_tests.py -target parse tests/parser/positive/
	python3 run_tests.py -target parse tests/parser/negative/ || python3 run_tests.py -target parse tests/parser/negative/

# ejecuta todas las etapas del compilador
test_general: build/c-tds
	python3 run_tests.py -o tests/general/positive/ || python3 run_tests.py -o tests/general/positive/
	python3 run_tests.py -o tests/general/negative/ || python3 run_tests.py -o tests/general/negative/


