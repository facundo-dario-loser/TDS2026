/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../utils/debug.h"
#include "../../tads/ast.h"

extern int yylex(void);
void yyerror(const char *s);

extern FILE *yyin;
extern int  yylineno;

AstNode *root = NULL;

#line 87 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INT_LITERAL = 4,                /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 5,              /* FLOAT_LITERAL  */
  YYSYMBOL_BOOL_LITERAL = 6,               /* BOOL_LITERAL  */
  YYSYMBOL_VOID = 7,                       /* VOID  */
  YYSYMBOL_INT = 8,                        /* INT  */
  YYSYMBOL_BOOLEAN = 9,                    /* BOOLEAN  */
  YYSYMBOL_FLOAT = 10,                     /* FLOAT  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_RETURN = 14,                    /* RETURN  */
  YYSYMBOL_EQUAL = 15,                     /* EQUAL  */
  YYSYMBOL_AND = 16,                       /* AND  */
  YYSYMBOL_OR = 17,                        /* OR  */
  YYSYMBOL_18_ = 18,                       /* '<'  */
  YYSYMBOL_19_ = 19,                       /* '>'  */
  YYSYMBOL_20_ = 20,                       /* '-'  */
  YYSYMBOL_21_ = 21,                       /* '+'  */
  YYSYMBOL_22_ = 22,                       /* '*'  */
  YYSYMBOL_23_ = 23,                       /* '/'  */
  YYSYMBOL_24_ = 24,                       /* '%'  */
  YYSYMBOL_UMINUS = 25,                    /* UMINUS  */
  YYSYMBOL_26_ = 26,                       /* '!'  */
  YYSYMBOL_27_ = 27,                       /* ';'  */
  YYSYMBOL_28_ = 28,                       /* ','  */
  YYSYMBOL_29_ = 29,                       /* '('  */
  YYSYMBOL_30_ = 30,                       /* ')'  */
  YYSYMBOL_31_ = 31,                       /* '{'  */
  YYSYMBOL_32_ = 32,                       /* '}'  */
  YYSYMBOL_33_ = 33,                       /* '='  */
  YYSYMBOL_YYACCEPT = 34,                  /* $accept  */
  YYSYMBOL_p = 35,                         /* p  */
  YYSYMBOL_global_decl_list = 36,          /* global_decl_list  */
  YYSYMBOL_method_decl_list = 37,          /* method_decl_list  */
  YYSYMBOL_var_decl = 38,                  /* var_decl  */
  YYSYMBOL_list_id = 39,                   /* list_id  */
  YYSYMBOL_method_decl = 40,               /* method_decl  */
  YYSYMBOL_params = 41,                    /* params  */
  YYSYMBOL_param = 42,                     /* param  */
  YYSYMBOL_block = 43,                     /* block  */
  YYSYMBOL_block_elems = 44,               /* block_elems  */
  YYSYMBOL_type = 45,                      /* type  */
  YYSYMBOL_statements = 46,                /* statements  */
  YYSYMBOL_statement = 47,                 /* statement  */
  YYSYMBOL_method_call = 48,               /* method_call  */
  YYSYMBOL_list_expr = 49,                 /* list_expr  */
  YYSYMBOL_expr = 50                       /* expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   244

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  112

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   273


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,     2,     2,    24,     2,     2,
      29,    30,    22,    21,    28,    20,     2,    23,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    27,
      18,    33,    19,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    25
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    54,    54,    60,    61,    64,    65,    68,    71,    72,
      78,    82,    86,    91,    98,    99,   102,   108,   111,   112,
     115,   116,   117,   120,   121,   124,   128,   129,   130,   131,
     132,   133,   134,   135,   138,   142,   148,   149,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "ID", "INT_LITERAL",
  "FLOAT_LITERAL", "BOOL_LITERAL", "VOID", "INT", "BOOLEAN", "FLOAT", "IF",
  "ELSE", "WHILE", "RETURN", "EQUAL", "AND", "OR", "'<'", "'>'", "'-'",
  "'+'", "'*'", "'/'", "'%'", "UMINUS", "'!'", "';'", "','", "'('", "')'",
  "'{'", "'}'", "'='", "$accept", "p", "global_decl_list",
  "method_decl_list", "var_decl", "list_id", "method_decl", "params",
  "param", "block", "block_elems", "type", "statements", "statement",
  "method_call", "list_expr", "expr", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-40)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      48,     0,   -40,   -40,   -40,     1,   -40,   -40,    48,    48,
      50,    41,   -40,   -40,   -40,    70,    -2,    61,     3,    46,
      86,    22,   -40,    60,    62,    65,    96,    73,   -40,    60,
      72,    51,   -40,    60,    59,   -40,   -40,    60,   -25,    74,
      75,    92,   -40,    51,   -40,    76,    86,   -40,    63,    78,
     -40,   -40,   -40,    80,   110,   110,   110,    82,   -40,   -40,
     -40,   110,   110,   -40,   110,   -40,   187,   -40,   -40,   -40,
     -40,   -40,    77,   173,   200,   125,   141,   -40,   -40,   157,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     -40,   -40,   110,   -40,    60,    60,   -40,   105,   220,   210,
      16,    16,    57,    57,   -40,   -40,   -40,   -40,   119,   -40,
      60,   -40
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       6,     0,    20,    21,    22,     0,     2,     4,     6,     6,
       0,     0,     1,     3,     5,     0,     8,     0,     0,     0,
       0,     0,     7,     0,     0,    15,     0,     8,     9,     0,
       0,    24,    13,     0,     0,    16,    11,     0,     0,     0,
       0,     0,    32,    24,    33,     0,     0,    19,    24,     0,
      12,    14,    10,     0,     0,     0,     0,    38,    40,    41,
      42,     0,     0,    31,     0,    39,     0,    18,    17,    23,
      26,    34,     0,    37,     0,     0,     0,    53,    54,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      30,    35,     0,    25,     0,     0,    55,    50,    51,    52,
      48,    49,    44,    43,    45,    46,    47,    36,    27,    29,
       0,    28
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -40,   109,   113,   -22,   112,   -40,   -16,   -40,   -23,
      90,    20,    87,   -40,   -24,    42,   -39
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,     8,    17,     9,    24,    25,    44,
      45,    26,    47,    48,    65,    72,    73
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      32,    12,    66,    11,    53,    30,    36,    49,    54,    43,
      50,     2,     3,     4,    52,    74,    75,    76,    51,    49,
      10,    43,    77,    78,    49,    79,    20,    21,    10,    15,
       2,     3,     4,    23,    -1,    -1,    85,    86,    87,    88,
      89,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,    46,    29,    16,    38,     1,     2,     3,     4,     2,
       3,     4,    39,    46,    40,    41,    38,     2,     3,     4,
      18,   108,   109,    19,    39,    21,    40,    41,    42,    87,
      88,    89,    31,    57,    58,    59,    60,   111,    22,    27,
      42,    31,    33,    34,    31,    57,    58,    59,    60,    35,
      61,    20,    37,    55,    56,    70,    62,    91,    68,    64,
      71,    53,    61,    57,    58,    59,    60,    13,    62,    63,
      -1,    64,    14,    83,    84,    85,    86,    87,    88,    89,
      61,   110,    28,    67,   107,    69,    62,     0,     0,    64,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
       0,     0,     0,     0,     0,    94,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,     0,     0,     0,     0,
       0,    95,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,     0,     0,     0,     0,     0,    96,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,     0,     0,
       0,    92,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,     0,     0,    90,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    80,    81,    93,    83,    84,
      85,    86,    87,    88,    89,    80,     0,     0,    83,    84,
      85,    86,    87,    88,    89
};

static const yytype_int8 yycheck[] =
{
      23,     0,    41,     3,    29,    21,    29,    31,    33,    31,
      33,     8,     9,    10,    37,    54,    55,    56,    34,    43,
       0,    43,    61,    62,    48,    64,    28,    29,     8,     9,
       8,     9,    10,    30,    18,    19,    20,    21,    22,    23,
      24,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    31,    30,     3,     3,     7,     8,     9,    10,     8,
       9,    10,    11,    43,    13,    14,     3,     8,     9,    10,
      29,    94,    95,     3,    11,    29,    13,    14,    27,    22,
      23,    24,    31,     3,     4,     5,     6,   110,    27,     3,
      27,    31,    30,    28,    31,     3,     4,     5,     6,     3,
      20,    28,    30,    29,    29,    27,    26,    30,    32,    29,
      30,    29,    20,     3,     4,     5,     6,     8,    26,    27,
      15,    29,     9,    18,    19,    20,    21,    22,    23,    24,
      20,    12,    20,    43,    92,    48,    26,    -1,    -1,    29,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    28,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    27,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    15,    16,    27,    18,    19,
      20,    21,    22,    23,    24,    15,    -1,    -1,    18,    19,
      20,    21,    22,    23,    24
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     8,     9,    10,    35,    36,    37,    38,    40,
      45,     3,     0,    36,    37,    45,     3,    39,    29,     3,
      28,    29,    27,    30,    41,    42,    45,     3,    39,    30,
      41,    31,    43,    30,    28,     3,    43,    30,     3,    11,
      13,    14,    27,    38,    43,    44,    45,    46,    47,    48,
      43,    41,    43,    29,    33,    29,    29,     3,     4,     5,
       6,    20,    26,    27,    29,    48,    50,    44,    32,    46,
      27,    30,    49,    50,    50,    50,    50,    50,    50,    50,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      27,    30,    28,    27,    30,    30,    30,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    49,    43,    43,
      12,    43
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    38,    39,    39,
      40,    40,    40,    40,    41,    41,    42,    43,    44,    44,
      45,    45,    45,    46,    46,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    48,    48,    49,    49,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     0,     3,     1,     3,
       6,     5,     6,     5,     3,     1,     2,     3,     2,     1,
       1,     1,     1,     2,     0,     4,     2,     5,     7,     5,
       3,     2,     1,     1,     3,     4,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif



static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yystrlen (yysymbol_name (yyarg[yyi]));
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp = yystpcpy (yyp, yysymbol_name (yyarg[yyi++]));
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* p: global_decl_list  */
#line 54 "parser.y"
                    {
                        (yyval.node)   = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_P, .children1 = (yyvsp[0].node)});
                        root = (yyval.node);
                    }
#line 1437 "parser.tab.c"
    break;

  case 3: /* global_decl_list: var_decl global_decl_list  */
#line 60 "parser.y"
                                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_GLOBAL_DECL_LIST, .children1 = (yyvsp[-1].node), .children2 = (yyvsp[0].node)}); }
#line 1443 "parser.tab.c"
    break;

  case 4: /* global_decl_list: method_decl_list  */
#line 61 "parser.y"
                                            { (yyval.node) = (yyvsp[0].node); }
#line 1449 "parser.tab.c"
    break;

  case 5: /* method_decl_list: method_decl method_decl_list  */
#line 64 "parser.y"
                                               { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_METHOD_DECL_LIST, .children1 = (yyvsp[-1].node), .children2 = (yyvsp[0].node)}); }
#line 1455 "parser.tab.c"
    break;

  case 6: /* method_decl_list: %empty  */
#line 65 "parser.y"
                                               { (yyval.node) = NULL; }
#line 1461 "parser.tab.c"
    break;

  case 7: /* var_decl: type list_id ';'  */
#line 68 "parser.y"
                           { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_VAR_DECL, .children1 = (yyvsp[-2].node), .children2 = (yyvsp[-1].node)}); }
#line 1467 "parser.tab.c"
    break;

  case 8: /* list_id: ID  */
#line 71 "parser.y"
                        { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = (yyvsp[0].strValue)}); }
#line 1473 "parser.tab.c"
    break;

  case 9: /* list_id: ID ',' list_id  */
#line 72 "parser.y"
                        {   
                            AstNode *aux = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = (yyvsp[-2].strValue)});
                            (yyval.node)           = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_LIST_ID, .children1 = aux, .children2 = (yyvsp[0].node)}); 
                        }
#line 1482 "parser.tab.c"
    break;

  case 10: /* method_decl: type ID '(' params ')' block  */
#line 78 "parser.y"
                                          { 
                                            AstNode *auxID = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = (yyvsp[-4].strValue)});
                                            (yyval.node)             = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_METHOD_DECL, .children1 = (yyvsp[-5].node), .children2 = auxID, .children3 = (yyvsp[-2].node), .children4 = (yyvsp[0].node)}); 
                                          }
#line 1491 "parser.tab.c"
    break;

  case 11: /* method_decl: type ID '(' ')' block  */
#line 82 "parser.y"
                                          {
                                            AstNode *auxID = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = (yyvsp[-3].strValue)});
                                            (yyval.node)             = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_METHOD_DECL, .children1 = (yyvsp[-4].node), .children2 = auxID, .children4 = (yyvsp[0].node)});
                                          }
#line 1500 "parser.tab.c"
    break;

  case 12: /* method_decl: VOID ID '(' params ')' block  */
#line 86 "parser.y"
                                          {
                                            AstNode *auxVoid = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_VOID });
                                            AstNode *auxID   = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = (yyvsp[-4].strValue)});
                                            (yyval.node)               = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_METHOD_DECL, .children1 = auxVoid, .children2 = auxID, .children3 = (yyvsp[-2].node), .children4 = (yyvsp[0].node)}); 
                                          }
#line 1510 "parser.tab.c"
    break;

  case 13: /* method_decl: VOID ID '(' ')' block  */
#line 91 "parser.y"
                                          {
                                            AstNode *auxVoid = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_VOID });
                                            AstNode *auxID   = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = (yyvsp[-3].strValue)});
                                            (yyval.node)               = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_METHOD_DECL, .children1 = auxVoid, .children2 = auxID, .children4 = (yyvsp[0].node)});
                                          }
#line 1520 "parser.tab.c"
    break;

  case 14: /* params: param ',' params  */
#line 98 "parser.y"
                         { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_PARAMS, .children1 = (yyvsp[-2].node), .children2 = (yyvsp[0].node)}); }
#line 1526 "parser.tab.c"
    break;

  case 15: /* params: param  */
#line 99 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 1532 "parser.tab.c"
    break;

  case 16: /* param: type ID  */
#line 102 "parser.y"
               { 
                AstNode *auxID = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = (yyvsp[0].strValue)});
                (yyval.node)             = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_PARAM, .children1 = (yyvsp[-1].node), .children2 = auxID}); 
               }
#line 1541 "parser.tab.c"
    break;

  case 17: /* block: '{' block_elems '}'  */
#line 108 "parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 1547 "parser.tab.c"
    break;

  case 18: /* block_elems: var_decl block_elems  */
#line 111 "parser.y"
                                  { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_BLOCK_ELEMS, .children1 = (yyvsp[-1].node), .children2 = (yyvsp[0].node)}); }
#line 1553 "parser.tab.c"
    break;

  case 19: /* block_elems: statements  */
#line 112 "parser.y"
                                  { (yyval.node) = (yyvsp[0].node); }
#line 1559 "parser.tab.c"
    break;

  case 20: /* type: INT  */
#line 115 "parser.y"
              { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_TYPE, .declarationType = AST_NODE_DECLARATION_TYPE_INT}); }
#line 1565 "parser.tab.c"
    break;

  case 21: /* type: BOOLEAN  */
#line 116 "parser.y"
              { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_TYPE, .declarationType = AST_NODE_DECLARATION_TYPE_BOOLEAN}); }
#line 1571 "parser.tab.c"
    break;

  case 22: /* type: FLOAT  */
#line 117 "parser.y"
              { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_TYPE, .declarationType = AST_NODE_DECLARATION_TYPE_FLOAT}); }
#line 1577 "parser.tab.c"
    break;

  case 23: /* statements: statement statements  */
#line 120 "parser.y"
                                 { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_STATEMENTS, .children1 = (yyvsp[-1].node), .children2 = (yyvsp[0].node)}); }
#line 1583 "parser.tab.c"
    break;

  case 24: /* statements: %empty  */
#line 121 "parser.y"
                                 { (yyval.node) = NULL; }
#line 1589 "parser.tab.c"
    break;

  case 25: /* statement: ID '=' expr ';'  */
#line 124 "parser.y"
                                            {
                                                AstNode *auxID = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = (yyvsp[-3].strValue)});
                                                (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ASSIGNMENT, .children1 = auxID, .children2 = (yyvsp[-1].node)});
                                            }
#line 1598 "parser.tab.c"
    break;

  case 26: /* statement: method_call ';'  */
#line 128 "parser.y"
                                            { (yyval.node) = (yyvsp[-1].node); }
#line 1604 "parser.tab.c"
    break;

  case 27: /* statement: IF '(' expr ')' block  */
#line 129 "parser.y"
                                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_IF_ELSE, .children1 = (yyvsp[-2].node), .children2 = (yyvsp[0].node)}); }
#line 1610 "parser.tab.c"
    break;

  case 28: /* statement: IF '(' expr ')' block ELSE block  */
#line 130 "parser.y"
                                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_IF_ELSE, .children1 = (yyvsp[-4].node), .children2 = (yyvsp[-2].node), .children3 = (yyvsp[0].node)}); }
#line 1616 "parser.tab.c"
    break;

  case 29: /* statement: WHILE '(' expr ')' block  */
#line 131 "parser.y"
                                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_WHILE, .children1 = (yyvsp[-2].node), .children2 = (yyvsp[0].node)}); }
#line 1622 "parser.tab.c"
    break;

  case 30: /* statement: RETURN expr ';'  */
#line 132 "parser.y"
                                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_RETURN, .children1 = (yyvsp[-1].node)}); }
#line 1628 "parser.tab.c"
    break;

  case 31: /* statement: RETURN ';'  */
#line 133 "parser.y"
                                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_RETURN}); }
#line 1634 "parser.tab.c"
    break;

  case 32: /* statement: ';'  */
#line 134 "parser.y"
                                            { (yyval.node) = NULL; }
#line 1640 "parser.tab.c"
    break;

  case 33: /* statement: block  */
#line 135 "parser.y"
                                            { (yyval.node) = (yyvsp[0].node); }
#line 1646 "parser.tab.c"
    break;

  case 34: /* method_call: ID '(' ')'  */
#line 138 "parser.y"
                                  { 
                                    AstNode *auxID = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = (yyvsp[-2].strValue)});
                                    (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_METHOD_CALL, .children1 = auxID}); 
                                  }
#line 1655 "parser.tab.c"
    break;

  case 35: /* method_call: ID '(' list_expr ')'  */
#line 142 "parser.y"
                                  {
                                    AstNode *auxID = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = (yyvsp[-3].strValue)});
                                    (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_METHOD_CALL, .children1 = auxID, .children2 = (yyvsp[-1].node)}); 
                                  }
#line 1664 "parser.tab.c"
    break;

  case 36: /* list_expr: expr ',' list_expr  */
#line 148 "parser.y"
                              { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_LIST_EXPR, .children1 = (yyvsp[-2].node), .children2 = (yyvsp[0].node)}); }
#line 1670 "parser.tab.c"
    break;

  case 37: /* list_expr: expr  */
#line 149 "parser.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 1676 "parser.tab.c"
    break;

  case 38: /* expr: ID  */
#line 152 "parser.y"
                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ID, .value.strValue = (yyvsp[0].strValue)}); }
#line 1682 "parser.tab.c"
    break;

  case 39: /* expr: method_call  */
#line 153 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1688 "parser.tab.c"
    break;

  case 40: /* expr: INT_LITERAL  */
#line 154 "parser.y"
                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_INT_LITERAL, .value.intValue = (yyvsp[0].intValue)}); }
#line 1694 "parser.tab.c"
    break;

  case 41: /* expr: FLOAT_LITERAL  */
#line 155 "parser.y"
                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_FLOAT_LITERAL, .value.floatValue = (yyvsp[0].floatValue)}); }
#line 1700 "parser.tab.c"
    break;

  case 42: /* expr: BOOL_LITERAL  */
#line 156 "parser.y"
                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_BOOL_LITERAL, .value.booleanValue = (yyvsp[0].boolValue)}); }
#line 1706 "parser.tab.c"
    break;

  case 43: /* expr: expr '+' expr  */
#line 157 "parser.y"
                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_ADDITION, .children1 = (yyvsp[-2].node), .children2 = (yyvsp[0].node)}); }
#line 1712 "parser.tab.c"
    break;

  case 44: /* expr: expr '-' expr  */
#line 158 "parser.y"
                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_SUBTRACTION, .children1 = (yyvsp[-2].node), .children2 = (yyvsp[0].node)}); }
#line 1718 "parser.tab.c"
    break;

  case 45: /* expr: expr '*' expr  */
#line 159 "parser.y"
                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_MULTIPLICATION, .children1 = (yyvsp[-2].node), .children2 = (yyvsp[0].node)}); }
#line 1724 "parser.tab.c"
    break;

  case 46: /* expr: expr '/' expr  */
#line 160 "parser.y"
                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_DIVISION, .children1 = (yyvsp[-2].node), .children2 = (yyvsp[0].node)}); }
#line 1730 "parser.tab.c"
    break;

  case 47: /* expr: expr '%' expr  */
#line 161 "parser.y"
                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_MOD, .children1 = (yyvsp[-2].node), .children2 = (yyvsp[0].node)}); }
#line 1736 "parser.tab.c"
    break;

  case 48: /* expr: expr '<' expr  */
#line 162 "parser.y"
                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_COMPARISION_SMALLER, .children1 = (yyvsp[-2].node), .children2 = (yyvsp[0].node)}); }
#line 1742 "parser.tab.c"
    break;

  case 49: /* expr: expr '>' expr  */
#line 163 "parser.y"
                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_COMPARISION_GREATER, .children1 = (yyvsp[-2].node), .children2 = (yyvsp[0].node)}); }
#line 1748 "parser.tab.c"
    break;

  case 50: /* expr: expr EQUAL expr  */
#line 164 "parser.y"
                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_EQUAL, .children1 = (yyvsp[-2].node), .children2 = (yyvsp[0].node)}); }
#line 1754 "parser.tab.c"
    break;

  case 51: /* expr: expr AND expr  */
#line 165 "parser.y"
                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_AND, .children1 = (yyvsp[-2].node), .children2 = (yyvsp[0].node)}); }
#line 1760 "parser.tab.c"
    break;

  case 52: /* expr: expr OR expr  */
#line 166 "parser.y"
                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_OR, .children1 = (yyvsp[-2].node), .children2 = (yyvsp[0].node)}); }
#line 1766 "parser.tab.c"
    break;

  case 53: /* expr: '-' expr  */
#line 167 "parser.y"
                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_MINUS, .children1 = (yyvsp[0].node)}); }
#line 1772 "parser.tab.c"
    break;

  case 54: /* expr: '!' expr  */
#line 168 "parser.y"
                            { (yyval.node) = newAstNode(&(AstNodeConfig){.type = AST_NODE_TYPE_NEGATION, .children1 = (yyvsp[0].node)}); }
#line 1778 "parser.tab.c"
    break;

  case 55: /* expr: '(' expr ')'  */
#line 169 "parser.y"
                            { (yyval.node) = (yyvsp[-1].node); }
#line 1784 "parser.tab.c"
    break;


#line 1788 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 172 "parser.y"


void yyerror(const char *s) {
    ERROR_PARSER("%s (line %d)\n", s, yylineno)
}

