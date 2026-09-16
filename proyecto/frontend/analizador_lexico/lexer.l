%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include "../analizador_sintactico/parser.tab.h"
    #include "../../utils/debug.h"
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
"/*"[a-zA-Z0-9 \t\n]*"*/" { DEBUG_LEXER("MULTILINE_COMMENT(%s)", yytext);                   }
.                         { ERROR(MESSAGE_SOURCE_LEXICAL_ANALYSIS, "invalid token '%s' (line: %d)", yytext, yylineno) }
%%
