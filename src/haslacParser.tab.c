#define yylval haslaclval
#define yy_create_buffer haslac_create_buffer
#define yy_delete_buffer haslac_delete_buffer
#define yy_flex_debug haslac_flex_debug
#define yy_init_buffer haslac_init_buffer
#define yy_flush_buffer haslac_flush_buffer
#define yy_load_buffer_state haslac_load_buffer_state
#define yy_switch_to_buffer haslac_switch_to_buffer
#define yyin haslacin
#define yyleng haslacleng
#define yylex haslaclex
#define yylineno haslaclineno
#define yyout haslacout
#define yyrestart haslacrestart
#define yytext haslactext
#define yywrap haslacwrap
#define yyalloc haslacalloc
#define yyrealloc haslacrealloc
#define yyfree haslacfree

/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         haslacparse
#define yylex           haslaclex
#define yyerror         haslacerror
#define yydebug         haslacdebug
#define yynerrs         haslacnerrs

#define yylval          haslaclval
#define yychar          haslacchar

/* Copy the first part of user declarations.  */
#line 1 "parsers/haslacParser.y" /* yacc.c:339  */
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include "structs.h"

	//#include "featureCompute.h"
	//#define PARSER_DEBUG_ON
	//#define COND_DEBUG
	//#define ID_DEBUG
	
	
	#ifndef MAX_STR_LENGTH
		#define MAX_STR_LENGTH 4096
	#endif

	void yyerror(char *);
	extern int yylex();
	extern int haslac_lineNo,haslac_charPos,yyleng,yyhaslac_lineno,yychar,haslac_oldPos;
	extern char haslac_line[MAX_STR_LENGTH],haslac_oldLine[MAX_STR_LENGTH];
	extern double haslac_maxNumber;
	
	extern FILE *yyin;
	extern char* yytext;
	int haslac_errNo,haslac_err1No,haslac_err2No,haslac_err3No,haslac_err4No,haslac_err5No,haslac_err6No;
	int haslac_currentMatch;
	
	struct location* loc_root = NULL;
	struct phaver* HA = NULL;
	struct automaton* hybridAut = NULL;
	
	char err[MAX_STR_LENGTH];
	char syncLabelTemp[] = "hop\0";
	
	enum haslac_errorType {
		//BLOCK_NO_NEWLINE = 1,
		IF_NO_TEST = 2,
		IF_NO_COLON = 3,
		TEST_EQ_EXPR = 4,
		WHILE_NO_COLON = 5,
		WHILE_NO_TEST = 6,
		PRINT_INVALID = 7,
		TEST_NO_LOGICAL = 8,
		EXPR_INVALID = 9
	};
	
	char P_dummy[1] = {'\0'};

#line 124 "haslacParser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "haslacParser.tab.h".  */
#ifndef YY_HASLAC_HASLACPARSER_TAB_H_INCLUDED
# define YY_HASLAC_HASLACPARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int haslacdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NEWLINE = 258,
    MODULE = 259,
    ENDMODULE = 260,
    INPUT = 261,
    OUTPUT = 262,
    PARAM = 263,
    BEGINN = 264,
    END = 265,
    MODE = 266,
    MODE_NEXT = 267,
    DDT = 268,
    PROPERTY = 269,
    ENDPROPERTY = 270,
    INITIALL = 271,
    SETT = 272,
    OUTPUT_VAR = 273,
    TRANS = 274,
    INV = 275,
    TRUE = 276,
    ASSIGN = 277,
    EQ = 278,
    LEQ = 279,
    GEQ = 280,
    LT = 281,
    GT = 282,
    SEMICOLON = 283,
    OPENCURLY = 284,
    CLOSECURLY = 285,
    OPENSQUARE = 286,
    CLOSESQUARE = 287,
    AND = 288,
    ANY = 289,
    IDENTIFIER = 290,
    NUMBER = 291,
    NEXT = 292,
    OPENROUND = 293,
    CLOSEROUND = 294,
    COMMA = 295,
    COLON = 296,
    OP = 297,
    DOT = 298,
    IMPLIES = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 53 "parsers/haslacParser.y" /* yacc.c:355  */

	char string[MAX_STR_LENGTH];
	struct phaver* pha;
	struct automaton* aut;
	struct condition* cond;
	struct identifier* ident;
	struct location* loc;
	struct transition* trans;
	struct initial* init;
	int code;		

#line 221 "haslacParser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE haslaclval;

int haslacparse (void);

#endif /* !YY_HASLAC_HASLACPARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 238 "haslacParser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   134

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  140

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    77,    77,    88,   111,   110,   148,   147,   185,   229,
     267,   307,   317,   328,   339,   348,   358,   369,   376,   385,
     393,   400,   408,   419,   425,   433,   439,   449,   478,   516,
     524,   533,   542,   549,   560,   567,   576,   581,   576,   595,
     605,   610,   605,   625,   632,   639,   645,   665,   672,   681,
     691,   698,   705,   712,   719,   728,   738,   745,   753,   761,
     808,   825,   834
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NEWLINE", "MODULE", "ENDMODULE",
  "INPUT", "OUTPUT", "PARAM", "BEGINN", "END", "MODE", "MODE_NEXT", "DDT",
  "PROPERTY", "ENDPROPERTY", "INITIALL", "SETT", "OUTPUT_VAR", "TRANS",
  "INV", "TRUE", "ASSIGN", "EQ", "LEQ", "GEQ", "LT", "GT", "SEMICOLON",
  "OPENCURLY", "CLOSECURLY", "OPENSQUARE", "CLOSESQUARE", "AND", "ANY",
  "IDENTIFIER", "NUMBER", "NEXT", "OPENROUND", "CLOSEROUND", "COMMA",
  "COLON", "OP", "DOT", "IMPLIES", "$accept", "program", "interface",
  "automatonDef", "$@1", "$@2", "locListBlock", "inputs", "outputs",
  "param_list", "params", "param", "locList", "locn", "dynamics",
  "ddtExpr", "properties", "property", "invariantProperty",
  "transitionProperty", "id_list", "id", "rational", "conjunction",
  "comparison", "$@3", "$@4", "arith_expr", "$@5", "$@6", "comparisons",
  "set_comparison", "ineq", "initially", "initial_sets", "set",
  "mode_assignment", "reset_conjunction", "reset", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299
};
# endif

#define YYPACT_NINF -91

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-91)))

#define YYTABLE_NINF -7

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      32,    24,    64,    36,   -91,    28,   -91,    24,    24,    63,
      55,    65,    33,    24,   -18,   -91,   -17,   -91,    59,    58,
      67,    24,    24,    66,    66,   -91,     9,   -91,    24,   -91,
      42,    44,   -91,   -91,   -91,    69,   -91,    66,   -15,   -91,
      54,    70,    66,   -91,   -91,   -91,    24,    24,   -91,   -91,
      68,    66,   -91,    24,    -4,    71,    75,    76,    72,    23,
     -91,   -91,   -91,   -91,    34,   -91,   -91,    38,    24,    37,
     -91,    73,    74,    77,   -91,   -91,    -4,   -91,   -91,    -4,
      78,   -91,   -91,    24,    24,    79,    80,    38,    38,    -4,
      56,    46,    24,   -91,    81,    -4,    -6,   -91,    53,   -26,
      82,    80,    83,   -91,    38,   -91,   -91,   -91,   -91,    84,
      86,    60,   -91,    30,    24,    88,    80,   -91,   -91,   -91,
     -91,   -91,    -4,    62,   -91,   -91,    38,    80,    61,    24,
      85,   -19,   -91,    87,    89,    24,    -4,   -91,   -91,    38
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    31,     0,     1,     0,     0,     0,
       4,     0,     0,     0,     0,    30,     0,     2,     0,     0,
       0,     0,     0,     0,    10,    18,     0,    11,     0,    12,
       0,     0,    24,    25,    26,     0,     7,     0,     0,    15,
       0,     0,     9,    17,     3,    29,     0,     0,    23,     5,
       0,     8,    13,     0,     0,     0,     0,     0,     0,     0,
      57,    14,    32,    40,     0,    44,    45,    16,     0,     0,
      21,     0,     0,     0,    55,    56,     0,    33,    46,     0,
       0,    19,    20,     0,     0,     0,    36,    41,    43,     0,
       0,     0,     0,    39,     0,     0,    36,    48,     0,     0,
       0,    36,     0,    49,    37,    58,    47,    42,    22,     0,
       0,    35,    59,     0,     0,     0,    36,    50,    51,    52,
      53,    54,     0,     0,    27,    34,    38,    36,     0,     0,
       0,     0,    61,     0,     0,     0,     0,    28,    60,    62
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -91,   -91,   -91,   -91,   -91,   -91,   -91,   -91,    95,    92,
     -91,    45,   -20,   -23,   -91,    39,   -91,    90,   -91,   -91,
      22,    -1,   -91,   -90,   -57,   -91,   -91,   -71,   -91,   -91,
     -91,     3,   -91,    93,   -91,    57,   -91,   -91,   -16
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     9,    18,    19,    10,    11,    12,    23,
      38,    39,    24,    25,    69,    70,    31,    32,    33,    34,
      14,    65,    66,   110,   111,    95,   113,    67,    76,    98,
      96,    97,   122,    36,    59,    60,    86,   131,   132
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       5,    43,   108,    42,   105,    87,    15,    15,    88,   134,
      27,    29,    15,    52,   135,    93,    79,    51,    99,    43,
      40,    41,    28,    28,   104,    53,   125,    45,    43,    94,
      16,     4,    62,    74,    63,    26,     1,   128,    64,    94,
      58,    21,     7,     8,    22,    56,    57,    81,    44,    28,
      68,   126,    40,   117,   118,   119,   120,   121,    30,     4,
      35,    46,    47,    78,     6,   139,    13,    80,    17,     4,
      77,    -6,     8,    30,    35,    21,    54,    22,    50,    55,
      79,    73,    90,    91,    68,    58,    71,    72,    85,   100,
     101,   102,   107,   116,   109,   127,    83,    84,    61,   106,
      89,    93,    92,   124,   137,   129,    20,   114,    82,   103,
     136,   112,    37,   123,   115,     0,    75,     0,     0,   138,
       0,    48,   133,     0,    49,     0,     0,     0,   130,     0,
       0,     0,     0,     0,   130
};

static const yytype_int16 yycheck[] =
{
       1,    24,    28,    23,    10,    76,     7,     8,    79,    28,
      28,    28,    13,    28,    33,    21,    42,    37,    89,    42,
      21,    22,    40,    40,    95,    40,   116,    28,    51,    86,
       8,    35,    36,    10,    38,    13,     4,   127,    42,    96,
      17,     8,     6,     7,    11,    46,    47,    10,    39,    40,
      13,   122,    53,    23,    24,    25,    26,    27,    14,    35,
      16,    19,    20,    64,     0,   136,    38,    68,     5,    35,
      36,    16,     7,    14,    16,     8,    22,    11,     9,     9,
      42,     9,    83,    84,    13,    17,    11,    11,    11,    33,
      44,    92,    39,    33,    12,    33,    23,    23,    53,    96,
      22,    21,    23,    15,    15,    44,    11,    23,    69,    28,
      23,    28,    20,   114,    28,    -1,    59,    -1,    -1,   135,
      -1,    31,    37,    -1,    31,    -1,    -1,    -1,   129,    -1,
      -1,    -1,    -1,    -1,   135
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    46,    47,    35,    66,     0,     6,     7,    48,
      51,    52,    53,    38,    65,    66,    65,     5,    49,    50,
      53,     8,    11,    54,    57,    58,    65,    28,    40,    28,
      14,    61,    62,    63,    64,    16,    78,    54,    55,    56,
      66,    66,    57,    58,    39,    66,    19,    20,    62,    78,
       9,    57,    28,    40,    22,     9,    66,    66,    17,    79,
      80,    56,    36,    38,    42,    66,    67,    72,    13,    59,
      60,    11,    11,     9,    10,    80,    73,    36,    66,    42,
      66,    10,    60,    23,    23,    11,    81,    72,    72,    22,
      66,    66,    23,    21,    69,    70,    75,    76,    74,    72,
      33,    44,    66,    28,    72,    10,    76,    39,    28,    12,
      68,    69,    28,    71,    23,    28,    33,    23,    24,    25,
      26,    27,    77,    66,    15,    68,    72,    33,    68,    44,
      66,    82,    83,    37,    28,    33,    23,    15,    83,    72
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    46,    47,    49,    48,    50,    48,    51,    51,
      51,    52,    53,    54,    55,    55,    56,    57,    57,    58,
      59,    59,    60,    61,    61,    62,    62,    63,    64,    65,
      65,    66,    67,    67,    68,    68,    70,    71,    69,    69,
      73,    74,    72,    72,    72,    72,    72,    75,    75,    76,
      77,    77,    77,    77,    77,    78,    79,    79,    80,    81,
      82,    82,    83
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     5,     0,     4,     0,     3,     4,     3,
       2,     3,     3,     3,     3,     1,     3,     2,     1,     5,
       2,     1,     5,     2,     1,     1,     1,    10,    16,     3,
       1,     1,     1,     2,     3,     1,     0,     0,     5,     1,
       0,     0,     5,     3,     1,     1,     2,     2,     1,     2,
       1,     1,     1,     1,     1,     4,     2,     1,     5,     4,
       3,     1,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 78 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.pha) = HA;
		
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: PROGRAM MATCH\n");
			displayAutomaton(HA);
			writeSpaceEx(HA,"batt.xml");
		#endif
	}
#line 1420 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 89 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		struct identifier* signature = duplicateIdentifierList((yyvsp[-1].ident));
		if(hybridAut==NULL){			
			hybridAut = createAutomaton(hybridAut,P_dummy,NULL,createIdentifier(syncLabelTemp),NULL);
		}
		strcpy(hybridAut->name,(yyvsp[-3].ident)->name);
		hybridAut->contr_vars = signature;
		hybridAut->synclabs = createIdentifier(syncLabelTemp);
		
		if(HA==NULL){
			HA = createPhaverStruct(HA,NULL,hybridAut,NULL);
		} else {
			HA->ha = hybridAut;
		}

		(yyval.ident) = NULL;
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: INTERFACE MATCH\n");
		#endif			
	}
#line 1445 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 111 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		#ifdef PARSER_DEBUG_ON
			printf("\n\n==========>>>  DONE HERE\n");
			printLocationList(loc_root);
		#endif
		
		HA->ha = hybridAut;
		
		#ifdef PARSER_DEBUG_ON		
			printf("HA->ha = [%p] , ha = [%p]\n",HA->ha,hybridAut);
			printf("HA->ha->locations = [%p]\n",HA->ha->locations);
			
		#endif
		
		
	}
#line 1466 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 127 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
		if(hybridAut==NULL){
			hybridAut = createAutomaton(hybridAut,P_dummy,NULL,NULL,NULL);
			#ifdef PARSER_DEBUG_ON
				printf("======>>>>>> HA WAS NULL\n");
			#endif
		}

		if(HA==NULL){
			HA = createPhaverStruct(HA,NULL,NULL,NULL);
		}
		HA->ha = hybridAut;
		HA->init = (yyvsp[0].init);
		
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: AUTOMATON MAvTCH\n");
			displayAutomaton(HA);
			printf("\n");
		#endif
	}
#line 1491 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 148 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		#ifdef PARSER_DEBUG_ON
			printf("\n\n==========>>>  DONE HERE\n");
			printLocationList(loc_root);
		#endif
		
		HA->ha = hybridAut;
		
		#ifdef PARSER_DEBUG_ON		
			printf("HA->ha = [%p] , ha = [%p]\n",HA->ha,hybridAut);
			printf("HA->ha->locations = [%p]\n",HA->ha->locations);
			
		#endif
		
		
	}
#line 1512 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 164 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
		if(hybridAut==NULL){
			hybridAut = createAutomaton(hybridAut,P_dummy,NULL,NULL,NULL);
			#ifdef PARSER_DEBUG_ON
				printf("======>>>>>> HA WAS NULL\n");
			#endif
		}

		if(HA==NULL){
			HA = createPhaverStruct(HA,NULL,NULL,NULL);
		}
		HA->ha = hybridAut;
		HA->init = (yyvsp[0].init);
		
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: AUTOMATON MAvTCH\n");
			displayAutomaton(HA);
			printf("\n");
		#endif
	}
#line 1537 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 186 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		
		//Add the param_list into "pha"
		if(HA==NULL){
			HA = createPhaverStruct(HA,NULL,NULL,NULL);
		}
		HA->params = (yyvsp[-1].cond);
		
		//Add locations to the automaton
		loc_root = (yyvsp[0].loc);
		if(hybridAut==NULL){
			hybridAut = createAutomaton(hybridAut,P_dummy,NULL,NULL,NULL);
		} else {
			char *ERR = containsIdentifier((yyvsp[-3].ident),hybridAut->contr_vars);
			if(ERR!=NULL){
				yyerror(ERR);
			} 
			
			ERR = containsIdentifier((yyvsp[-2].ident),hybridAut->contr_vars);
			if(ERR!=NULL){
				yyerror(ERR);
			}
		}
		#ifdef PARSER_DEBUG_ON
			if(HA->ha == hybridAut){
				printf("=========>>>>> THE ADDRESS IS THE SAME\n");
			} else {
				printf("=========>>>>> NO; THE ADDRESS IS NOT THE SAME\n");
			}
		#endif
		
		hybridAut->locations = (yyvsp[0].loc);
		
		//exit(0);
		#ifdef PARSER_DEBUG_ON
			if(HA->ha->locations == hybridAut->locations){
				printf("=========>>>>> THE LOCATION ADDRESS IS THE SAME\n");
			} else {
				printf("=========>>>>> NO; THE LOCATION ADDRESS IS NOT THE SAME\n");
			}
			printf("PARSER - REDUCE: LOCATION LIST BLOCK MATCH\n");
		#endif
	}
#line 1585 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 230 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
		//Add the param_list into "pha"
		if(HA==NULL){
			HA = createPhaverStruct(HA,NULL,NULL,NULL);
		}
		HA->params = (yyvsp[-1].cond);
		
		//Add locations to the automaton
		loc_root = (yyvsp[0].loc);
		if(hybridAut==NULL){
			hybridAut = createAutomaton(hybridAut,P_dummy,NULL,NULL,NULL);
		} else {
			char *ERR = containsIdentifier((yyvsp[-2].ident),hybridAut->contr_vars);
			if(ERR!=NULL){
				yyerror(ERR);
			} 
		}
		#ifdef PARSER_DEBUG_ON
			if(HA->ha == hybridAut){
				printf("=========>>>>> THE ADDRESS IS THE SAME\n");
			} else {
				printf("=========>>>>> NO; THE ADDRESS IS NOT THE SAME\n");
			}
		#endif
		
		hybridAut->locations = (yyvsp[0].loc);
		
		//exit(0);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: LOCATION LIST BLOCK - NO INPUTS MATCH\n");
			if(HA->ha->locations == hybridAut->locations){
				printf("=========>>>>> THE LOCATION ADDRESS IS THE SAME\n");
			} else {
				printf("=========>>>>> NO; THE LOCATION ADDRESS IS NOT THE SAME\n");
			}
			
		#endif
	}
#line 1628 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 268 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
		//Add the param_list into "pha"
		if(HA==NULL){
			HA = createPhaverStruct(HA,NULL,NULL,NULL);
		}
		HA->params = NULL;
		
		//Add locations to the automaton
		loc_root = (yyvsp[0].loc);
		if(hybridAut==NULL){
			hybridAut = createAutomaton(hybridAut,P_dummy,NULL,NULL,NULL);
		} else {
			char *ERR = containsIdentifier((yyvsp[-1].ident),hybridAut->contr_vars);
			if(ERR!=NULL){
				yyerror(ERR);
			} 
		}
		#ifdef PARSER_DEBUG_ON
			if(HA->ha == hybridAut){
				printf("=========>>>>> THE ADDRESS IS THE SAME\n");
			} else {
				printf("=========>>>>> NO; THE ADDRESS IS NOT THE SAME\n");
			}
		#endif
		
		hybridAut->locations = (yyvsp[0].loc);
		
		//exit(0);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: LOCATION LIST BLOCK - NO INPUTS MATCH\n");
			if(HA->ha->locations == hybridAut->locations){
				printf("=========>>>>> THE LOCATION ADDRESS IS THE SAME\n");
			} else {
				printf("=========>>>>> NO; THE LOCATION ADDRESS IS NOT THE SAME\n");
			}
			
		#endif
	}
#line 1671 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 308 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.ident) = (yyvsp[-1].ident);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: INPUT LIST MATCH\n");
			printIdentifierList((yyval.ident));
			printf("\n");
		#endif
	}
#line 1684 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 318 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.ident) = (yyvsp[-1].ident);
		//printIdentifierList($$);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: OUTPUT LIST MATCH\n");
			printIdentifierList((yyval.ident));
			printf("\n");
		#endif
	}
#line 1698 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 329 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.cond) = (yyvsp[-1].cond);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: PARAM LIST MATCH\n");
			printConditionList((yyval.cond));
			printf("\n");
		#endif
	}
#line 1711 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 340 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.cond) = addConditionToList((yyvsp[-2].cond),(yyvsp[0].cond));
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: PARAMS MATCH\n");
			printConditionList((yyval.cond));
			printf("\n");
		#endif
	}
#line 1724 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 349 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.cond) = (yyvsp[0].cond);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: PARAM LIST - PARAM MATCH\n");
			printCondition((yyval.cond));
			printf("\n");
		#endif
	}
#line 1737 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 359 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.cond) = createCondition((yyvsp[-2].ident)->name,(yyvsp[0].cond)->LHS,2);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: PARAM MATCH\n");
			printCondition((yyval.cond));
			printf("\n");
		#endif
	}
#line 1750 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 370 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.loc) = addLocationToList((yyvsp[-1].loc),(yyvsp[0].loc));
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: LOCATION LIST - MATCH\n");
		#endif
	}
#line 1761 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 377 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.loc) = (yyvsp[0].loc);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: LOCATION LIST - LOCATION MATCH\n");
			printf("\n");
		#endif
	}
#line 1773 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 386 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.loc) = createLocation((yyvsp[-3].ident)->name,NULL,(yyvsp[-1].cond),NULL);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: LOCATION MATCH\n");
		#endif
	}
#line 1784 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 394 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.cond) = addConditionToList((yyvsp[-1].cond),(yyvsp[0].cond));
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: DYNAMICS LIST MATCH\n");
		#endif
	}
#line 1795 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 401 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.cond) = (yyvsp[0].cond);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: DYNAMICS LIST DDTEXPR MATCH\n");
		#endif
	}
#line 1806 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 409 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		strcat((yyvsp[-3].ident)->name,"'");
		(yyval.cond) = createCondition((yyvsp[-3].ident)->name,(yyvsp[-1].cond)->LHS,0);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: DDTEXPR MATCH\n");
		#endif
	}
#line 1818 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 420 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		#ifdef PARSER_DEBUG_ON 
			printf("PARSER: PROPERTY LIST MATCH\n");
		#endif
	}
#line 1828 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 426 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		#ifdef PARSER_DEBUG_ON 
			printf("PARSER: PROPERTY LIST - PROPERTY MATCH\n");
		#endif
	}
#line 1838 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 434 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
		#ifdef PARSER_DEBUG_ON 
			printf("PARSER: PROPERTY INVARIANT MATCH\n");
		#endif
	}
#line 1848 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 440 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		#ifdef PARSER_DEBUG_ON 
			printf("PARSER: PROPERTY TRANSITION MATCH\n");
			printTransition((yyvsp[0].trans));
			printf("\n");
		#endif
	}
#line 1860 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 450 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		/*
		 * $3 = Property Name
		 * $6 = Location Name
		 * $8 = Condition
		 *
		 */
		struct location* from = getLocationByName(hybridAut->locations,(yyvsp[-4].ident)->name);
		if(from==NULL){
			sprintf(err,"\nLocation [%s] of Transition Property [%s] NOT FOUND.\n",(yyvsp[-4].ident)->name,(yyvsp[-7].ident)->name);
			yyerror(err);
		} 
		#ifdef PARSER_DEBUG_ON 
			else {
				printf("\nLocation [%p] = [%s]\n",from, from->name);
			}
		#endif
		
		from->invariant = (yyvsp[-2].cond);
		(yyval.cond) = from->invariant;
		
		
		
		#ifdef PARSER_DEBUG_ON
			printf("PARSER: INVARIANT MATCH\n");
		#endif
	}
#line 1892 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 479 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		/*
		 * $3 = Property Name
		 * $6 = From Location Name
		 * $10 = To Location Name
		 * $12 = Guard Condition
		 * $14 = Reset List
		 *
		 */
		
		struct location* fro = getLocationByName(loc_root,(yyvsp[-10].ident)->name);
		if(fro==NULL){
			sprintf(err,"\nLocation [%s] of Transition Property [%s] NOT FOUND.\n",(yyvsp[-10].ident)->name,(yyvsp[-13].ident)->name);
			yyerror(err);
		} 
		#ifdef PARSER_DEBUG_ON 
		else {
			printf("\nLocation [%p] = [%s]\n",fro, fro->name);
		}
		#endif
		
		struct transition* t = createTransition((yyvsp[-4].cond),syncLabelTemp,(yyvsp[-2].cond),(yyvsp[-6].ident)->name);
		//printf("Created Transition\n");fflush(stdout);
		
		//exit(0);
		//printTransition
		fro->transitions = addTransitionToLocationTransitionList(fro,t);
		//printf("Added Transition To Location List\n");fflush(stdout);	
		
		(yyval.trans) = t;
		#ifdef PARSER_DEBUG_ON
			printf("PARSER: TRANSITION MATCH\n");
			printTransition((yyval.trans));
			printf("\n");
		#endif
	}
#line 1933 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 517 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.ident) = addIdentifierToList((yyvsp[-2].ident),(yyvsp[0].ident));
		#if defined(PARSER_DEBUG_ON) || defined(ID_DEBUG)
			printf("PARSER - REDUCE: ID LIST\n");
		#endif
	}
#line 1944 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 525 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
		(yyval.ident) = (yyvsp[0].ident);
		#if defined(PARSER_DEBUG_ON) || defined(ID_DEBUG)
			printf("PARSER - REDUCE: ID LIST - SINGLE ID\n");
		#endif
	}
#line 1955 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 534 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.ident) = createIdentifier((yyvsp[0].string));
		#if defined(PARSER_DEBUG_ON) || defined(ID_DEBUG)
			printf("PARSER - REDUCE: IDENTIFIER [%s] ID Created As [%s]\n",(yyvsp[0].string),(yyval.ident)->name);
		#endif
	}
#line 1966 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 543 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
			(yyval.cond) = createCondition((yyvsp[0].string),P_dummy,-1);
			#ifdef PARSER_DEBUG_ON
				printf("PARSER - REDUCE: RATIONAL NUMBER MATCH\n");
			#endif
	 }
#line 1977 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 550 "parsers/haslacParser.y" /* yacc.c:1646  */
    {              
                        char *tempConcat = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
                        sprintf(tempConcat,"%s%s",(yyvsp[-1].string),(yyvsp[0].string));
                        (yyval.cond) = createCondition(tempConcat,P_dummy,-1);
                        #ifdef PARSER_DEBUG_ON
                                printf("PARSER - REDUCE: SIGNED RATIONAL NUMBER MATCH\n");
                        #endif
         }
#line 1990 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 561 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
		(yyval.cond) = addConditionToList((yyvsp[0].cond),(yyvsp[-2].cond));
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: CONJUNCTION LIST MATCH\n");
		#endif
	}
#line 2001 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 568 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
		(yyval.cond)=(yyvsp[0].cond);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: CONJUNCTION LIST - LOGICAL MATCH\n");
		#endif
	}
#line 2012 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 576 "parsers/haslacParser.y" /* yacc.c:1646  */
    { 	
				#ifdef PARSER_DEBUG ON 
					printf("***************************(1) Expecting an inequality\n"); fflush(stdout);
				#endif
			}
#line 2022 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 581 "parsers/haslacParser.y" /* yacc.c:1646  */
    { 
				#ifdef PARSER_DEBUG ON 
					printf("***************************(2) Expecting an inequality\n"); fflush(stdout);
				#endif
			}
#line 2032 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 586 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
		#ifdef PARSER_DEBUG ON 
			printf("*************************** (3) Expecting an inequality\n"); fflush(stdout);
		#endif
		(yyval.cond) = createCondition((yyvsp[-3].cond)->LHS,(yyvsp[0].cond)->LHS,(yyvsp[-1].code));
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: LOGICAL MATCH\n");
		#endif		
	}
#line 2046 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 596 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
		(yyval.cond) = createCondition((yyvsp[0].string),P_dummy,-1);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: LOGICAL TRUE MATCH\n");
		#endif
	}
#line 2057 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 605 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
                                        #ifdef PARSER_DEBUG_ON
                                                printf("PARSER: OPEN ROUND arith_expr start\n");
                                        #endif
                        }
#line 2067 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 610 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
                                        #ifdef PARSER_DEBUG_ON
                                                printf("PARSER: Bracketed Arith Expr Found [%s]\n",(yyvsp[0].cond)->LHS);
                                        #endif
                        }
#line 2077 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 615 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
                                        (yyval.cond) = (yyvsp[-2].cond);
                                        char *tempConcat = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
                                        sprintf(tempConcat,"( %s )",(yyvsp[-2].cond)->LHS);
                                        strcpy((yyval.cond)->LHS,tempConcat);
                                                
                                        #ifdef PARSER_DEBUG_ON
                                                printf("PARSER - REDUCE: ARITH EXPR TYPE 1 MATCH\n");
                                        #endif
                                }
#line 2092 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 625 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
                                        sprintf((yyvsp[-2].cond)->LHS,"%s %s %s",(yyvsp[-2].cond)->LHS,(yyvsp[-1].string),(yyvsp[0].cond)->LHS);
                                        (yyval.cond) = (yyvsp[-2].cond);
                                        #ifdef PARSER_DEBUG_ON
                                                printf("PARSER - REDUCE: ARITH EXPR TYPE 2 MATCH\n");
                                        #endif
                                }
#line 2104 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 632 "parsers/haslacParser.y" /* yacc.c:1646  */
    {       
                                        (yyval.cond)=createCondition((yyvsp[0].ident)->name,P_dummy,-1);//strcpy($$,$1);
                                        #ifdef PARSER_DEBUG_ON
                                                printf("PARSER - REDUCE: ARITH EXPR TYPE 3 MATCH\n");
                                        #endif
                
                                }
#line 2116 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 639 "parsers/haslacParser.y" /* yacc.c:1646  */
    {       
                                        (yyval.cond) = (yyvsp[0].cond);
                                        #ifdef PARSER_DEBUG_ON
                                                printf("PARSER - REDUCE: ARITH EXPR TYPE 5 MATCH\n");
                                        #endif
                                }
#line 2127 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 645 "parsers/haslacParser.y" /* yacc.c:1646  */
    {       //printf("OP = [%s] [%s]\n",$1,$2->name);
                                        char *tempConcat = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
                                        strcpy(tempConcat,(yyvsp[-1].string));
                                        strcat(tempConcat,(yyvsp[0].ident)->name);
                                        
                                        (yyval.cond)=createCondition(tempConcat,P_dummy,-1);//strcat($1,$2);strcpy($$,$1);
                                        #ifdef PARSER_DEBUG_ON
                                                printf("PARSER - REDUCE: ARITH EXPR TYPE 4 MATCH\n");
                                        #endif
                                }
#line 2142 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 666 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.cond) = addConditionToList((yyvsp[0].cond),(yyvsp[-1].cond));
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: COMPARISON LIST MATCH\n");
		#endif
	}
#line 2153 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 673 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
		(yyval.cond)=(yyvsp[0].cond);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: COMPARISON LIST - SET_COMPARTISON MATCH\n");
		#endif
	}
#line 2164 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 682 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
		(yyval.cond)=(yyvsp[-1].cond);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: SET COMPARTISON MATCH\n");
		#endif
	}
#line 2175 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 692 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
		(yyval.code) = 0;
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: INEQUALITY EQ MATCH\n");
		#endif		
	}
#line 2186 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 699 "parsers/haslacParser.y" /* yacc.c:1646  */
    {			
		(yyval.code) = 1;
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: INEQUALITY LEQ MATCH\n");
		#endif
	}
#line 2197 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 706 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: INEQUALITY GEQ MATCH\n");
		#endif
		(yyval.code) =3;		
	}
#line 2208 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 713 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: INEQUALITY LT MATCH\n");
		#endif
		(yyval.code) = 4;
	}
#line 2219 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 720 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: INEQUALITY GT MATCH\n");
		#endif
		(yyval.code) = 5;
	}
#line 2230 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 729 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
		(yyval.init) = (yyvsp[-1].init);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: INITIAL LIST  PARAM MATCH\n");
		#endif
	}
#line 2241 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 739 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.init) = addInitialToList((yyvsp[-1].init),(yyvsp[0].init));
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: INITIAL SET LIST MATCH\n");
		#endif
	}
#line 2252 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 746 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.init) = (yyvsp[0].init);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: INITIAL SET - SET MATCH\n");
		#endif
	}
#line 2263 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 754 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.init)=createInitial((yyvsp[-2].ident),(yyvsp[-1].cond));
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: INITIAL SET MATCH\n");
		#endif
	}
#line 2274 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 762 "parsers/haslacParser.y" /* yacc.c:1646  */
    {
		(yyval.ident) = (yyvsp[-1].ident);
		#ifdef PARSER_DEBUG_ON
			printf("PARSER - REDUCE: MODE ASSIGNMENT MATCH\n");
		#endif
	}
#line 2285 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 808 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
							(yyval.cond) = addConditionToList((yyvsp[-2].cond),(yyvsp[0].cond));
							#if defined(PARSER_DEBUG_ON) || defined(COND_DEBUG)
								printf("PARSER - REDUCE: RESET CONJUNCTION\n");
								printf("\n\n---------------CONDITION LIST-----------------\n");
								struct condition* tcond = (yyval.cond);
								while(tcond!=NULL){
									printf("\n");
									printf("%s %s %s ",tcond->LHS,operatorMap(tcond->op),tcond->RHS);	
									tcond = tcond->next;
								}
								printf("\n----------------------------------------------\n");
								printf("\n\n Printing Condition List from structs.h\n");
								printConditionList((yyval.cond));
								printf("\n");
							#endif
						}
#line 2307 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 825 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
							(yyval.cond) = (yyvsp[0].cond);
							#if defined(PARSER_DEBUG_ON) || defined(COND_DEBUG)
								printf("PARSER - REDUCE: RESET CONJUNCTION - RESET\n");
								printCondition((yyval.cond));
								printf("\n");
							#endif
						}
#line 2320 "haslacParser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 834 "parsers/haslacParser.y" /* yacc.c:1646  */
    {	
							strcat((yyvsp[-3].ident)->name,(yyvsp[-2].string));
							(yyval.cond) = createCondition((yyvsp[-3].ident)->name,(yyvsp[0].cond)->LHS,0);
							#if defined(PARSER_DEBUG_ON) || defined(COND_DEBUG)
								printf("PARSER - REDUCE: RESET\n");
								//printf("%s[%p] %s %s [%p] (%s)\n",$$->LHS,$$->LHS,operatorMap($$->op),$$->RHS,$$->RHS,$4->LHS);	
								
								
								printf("2 ---- %s %s %s [%p]\n",(yyval.cond)->LHS,operatorMap((yyval.cond)->op),(yyval.cond)->RHS,(yyval.cond)->RHS);	
								//strcpy($$->RHS,$4->LHS);
								//printf("2* ---- %s %s %s [%p]\n",$$->LHS,operatorMap($$->op),$$->RHS,$$->RHS);	
								//strcpy($$->RHS,syncLabelTemp);
								//printf("2^ ---- %s %s %s [%p] \n",$$->LHS,operatorMap($$->op),$$->RHS,$$->RHS);	
								printCondition((yyval.cond));
								printf("\n");
								//exit(0);
							#endif
						}
#line 2343 "haslacParser.tab.c" /* yacc.c:1646  */
    break;


#line 2347 "haslacParser.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 853 "parsers/haslacParser.y" /* yacc.c:1906  */

/*char* trim(char *str) {
	  char *end;

	// Trim leading space
	while(isspace(*str)) str++;

	if(*str == 0)  // All spaces?
		return str;

	// Trim trailing space
	end = str + strlen(str) - 1;
	while(end > str && isspace(*end)) end--;

	// Write new null terminator
	*(end+1) = 0;

	return str;
}
*/

void yyerror(char *s) {

	char errorMsg[256];
	int flag = 0;
	switch(haslac_errNo){
		case IF_NO_TEST:	sprintf(errorMsg,"Expected a logical condition expression AFTER \"if\".");
					break;
		case IF_NO_COLON:	sprintf(errorMsg,"Expected a \":\" after the condition expression.");
					flag = 1;
					break;
		case TEST_EQ_EXPR:	sprintf(errorMsg,"The condition expression can't contain an assignment operator. Use Logical Operators only.");
					break;
		case WHILE_NO_COLON:	sprintf(errorMsg,"Expected a \":\" after the condition expression.");
					flag = 1;
					break;
		case WHILE_NO_TEST:	sprintf(errorMsg,"Expected a logical condition expression AFTER \"while\".");
					break;
		case PRINT_INVALID :	sprintf(errorMsg,"Invalid print statement syntax.");
					break;
		case TEST_NO_LOGICAL:	sprintf(errorMsg,"Expected a logical operator between the two expressions.");
					flag = 1;
					break;
		case EXPR_INVALID:	sprintf(errorMsg,"Invalid Expression Format.");
					break;
		default:		sprintf(errorMsg,"Hey Didn't expect to see this here.");
					flag = 1;
					break;
	}
	if(strlen(haslac_line)==0){
		strcpy(haslac_line,haslac_oldLine);
		haslac_charPos = haslac_oldPos;
		haslac_lineNo--;
	}
	if(flag==1){
		haslac_currentMatch = haslac_charPos+1;
	}
	//fprintf(stderr, "%s at Line %d ; %s Match [%d], haslac_line :[%s],  ERROR CODES: [%d,%d,%d,%d,%d,%d,%d]\n", s,haslac_lineNo,errorMsg,haslac_currentMatch,haslac_line,haslac_errNo,haslac_err1No,haslac_err2No,haslac_err3No,haslac_err4No,haslac_err5No,haslac_err6No);
	fprintf(stderr, "%s at Line %d : %s \n", s,haslac_lineNo,errorMsg);
	char *line = trim(haslac_line);
	fprintf(stderr, "%s\n",line);
	int i=0;
	for(i=1;i<haslac_currentMatch;i++){
		printf(" ");
	}
	printf("^\n");
	exit(0);
	
	
}

/*int main() {
	yyin = fopen("featureAutOut.pha", "r");
	yyparse();
	//printf("MAX = %lf\n",haslac_maxNumber);
	return 0;
	
}
*/

/*
int main(int argc, char **argv){
	
	if( argc > 1 ) {
		FILE *fin = fopen(argv[1],"r");
		if(fin){
			yyin=fin;
			
		}
		yyparse();
	} else {
		printf("Incorrect Syntax\n");
		
	}
	return 0;
}
*/
