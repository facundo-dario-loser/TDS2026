PROGRAMAS_C =  frontend/analizador_lexico/lex.yy.c         \
			   frontend/analizador_sintactico/parser.tab.c \
			   utils/argument.c							   \
			   utils/debug.c							   \
			   main.c

main : frontend/analizador_lexico/lexer.l frontend/analizador_sintactico/parser.y $(PROGRAMAS_C)
	make -C frontend/analizador_lexico/
	make -C frontend/analizador_sintactico/ 
	gcc $(PROGRAMAS_C) -o build/c-tds

test: build/c-tds
	./build/c-tds -o main tests/test1.ctds
