%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include "../analizador_sintactico/parser.tab.h"
    #include "../../utils/debug.h"

    // se encarga de consumir/procesar los comentarios multilinea y ademas
    // printea la cadena del comentario e informa errores en caso de haberlos
    void processMultilineComment(void);
%}

%option noyywrap
%option yylineno

%%
int                       { DEBUG_LEXER("INT");                       return INT;           }
boolean                   { DEBUG_LEXER("BOOLEAN");                   return BOOLEAN;       }
void                      { DEBUG_LEXER("VOID");                      return VOID;          }
float                     { DEBUG_LEXER("FLOAT");                     return FLOAT;         }
if                        { DEBUG_LEXER("IF");                        return IF;            }
else                      { DEBUG_LEXER("ELSE");                      return ELSE;          }
while                     { DEBUG_LEXER("WHILE");                     return WHILE;         }
return                    { DEBUG_LEXER("RETURN");                    return RETURN;        }
==                        { DEBUG_LEXER("EQUAL");                     return EQUAL;         }
"&&"                      { DEBUG_LEXER("AND");                       return AND;           }
"||"                      { DEBUG_LEXER("OR");                        return OR;            }
true                      { DEBUG_LEXER("BOOL_LITERAL(true)");        return BOOL_LITERAL;  }
false                     { DEBUG_LEXER("BOOL_LITERAL(false)");       return BOOL_LITERAL;  }
[0-9][0-9]*               { DEBUG_LEXER("INT_LITERAL(%s)", yytext);   return INT_LITERAL;   }
[0-9][0-9]*.[0-9][0-9]*   { DEBUG_LEXER("FLOAT_LITERAL(%s)", yytext); return FLOAT_LITERAL; }
[a-zA-Z][a-zA-Z0-9_]*     { DEBUG_LEXER("ID(%s)", yytext);            return ID;            }
"+"                       { DEBUG_LEXER("+");                         return '+';           }
"-"                       { DEBUG_LEXER("-");                         return '-';           }
"*"                       { DEBUG_LEXER("*");                         return '*';           }
"/"                       { DEBUG_LEXER("/");                         return '/';           }
"%"                       { DEBUG_LEXER("%%");                        return '%';           }
"<"                       { DEBUG_LEXER("<");                         return '<';           }
">"                       { DEBUG_LEXER(">");                         return '>';           }
"!"                       { DEBUG_LEXER("!");                         return '!';           }
"="                       { DEBUG_LEXER("=");                         return '=';           }
"("                       { DEBUG_LEXER("(");                         return '(';           }
")"                       { DEBUG_LEXER(")");                         return ')';           }
"{"                       { DEBUG_LEXER("{");                         return '{';           }
"}"                       { DEBUG_LEXER("}");                         return '}';           }
";"                       { DEBUG_LEXER(";");                         return ';';           }
","                       { DEBUG_LEXER(",");                         return ',';           }
[ \n\t]+                  { /* ignorar espacios, new line y tab */                          }
"//".*                    { DEBUG_LEXER("LINE_COMMENT(%s)", yytext);                        }
"/*"                      { processMultilineComment();                                      }
.                         { ERROR_LEXER("invalid token '%s' (line: %d)", yytext, yylineno)  }
%%

// input() es una funcion de flex que retorna el caracter que esta 
// leyendo actualmente el cabezal de lectura en un buffer 
// y luego avanza en una posicion el cabezal.

// unput(c) es una macro de flex que vuelve a pushear en el buffer de 
// lectura el caracter 'c' y mueve el cabezal de lectura una posicion 
// para atras. Esta macro expande en la funcion 'yyunput'.

// el cabezal de lectura en flex se llama 'yy_c_buf_p' el cual es un 
// puntero al caracter actual/corriente en un buffer.

void processMultilineComment(void) {
    int  currentCharacter;         // caracter corriente que se esta leyendo del comentario
    bool multilineCommentIsClosed; // para saber si el comentario se cerro o se dejo abierto
    char multilineComment[2048];   // es para guardar el comentario multilinea para imprimirlo
    int index;                     // indice en el buffer multilineComment

    multilineCommentIsClosed = false;
    index                    = 0;
    currentCharacter         = input();

    while (currentCharacter != 0) { // si no llego al final del archivo
        multilineComment[index] = currentCharacter;
        index++;

        if (currentCharacter == '*') {
            int nextCharacter = input();
            if (nextCharacter == '/') {
                multilineCommentIsClosed = true;
                break;
            } else {
                unput(nextCharacter);
            }
        } else if (currentCharacter == '/') {
            int nextCharacter = input();
            if (nextCharacter == '*') {
                ERROR_LEXER("nested multiline comment is not allowed (line: %d)", yylineno)
            } else {
                unput(nextCharacter);
            }
        }

        currentCharacter = input();
    }

    // si el comentario esta bien cerrado, entonces eliminar el * de */
    if (multilineComment[index-1] == '*') multilineComment[index-1] = '\0';

    if (!multilineCommentIsClosed) {
        ERROR_LEXER("multiline comment is not closed (line: %d)", yylineno)
    } else {
        DEBUG_LEXER("MULTILINE_COMMENT(%s)", multilineComment)
    }
}
