PROGRAMAS_C =  frontend/analizador_lexico/lex.yy.c         \
			   frontend/analizador_sintactico/parser.tab.c \
			   utils/argument.c							   \
			   utils/debug.c							   \
			   main.c

main: frontend/analizador_lexico/lexer.l frontend/analizador_sintactico/parser.y $(PROGRAMAS_C)
	make -C frontend/analizador_lexico/
	make -C frontend/analizador_sintactico/ 
	gcc $(PROGRAMAS_C) -o build/c-tds

test_lexer: build/c-tds
	python3 run_tests.py -target scan tests/lexer/ || python3 run_tests.py -target scan tests/lexer/

test_parser: build/c-tds
	python3 run_tests.py -target parse tests/parser/ || python3 run_tests.py -target parse tests/parser/

test_general: build/c-tds
	python3 run_tests.py -o tests/general/ || python3 run_tests.py -o tests/general/

# Nota: 'test_fase_debug' ejecuta todas las fases del compilador (en modo debug), pero con solo los tests correspodientes a la fase seleccionada

test_lexer_debug: build/c-tds
	python3 run_tests.py -debug tests/lexer/ || python3 run_tests.py -debug tests/lexer/

test_parser_debug: build/c-tds
	python3 run_tests.py -debug tests/parser/ || python3 run_tests.py -debug tests/parser/

# son tests que no corresponden a ninguna etapa en concreto
test_general_debug: build/c-tds
	python3 run_tests.py -debug tests/general/ || python3 run_tests.py -debug tests/general/
