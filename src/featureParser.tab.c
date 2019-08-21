#define yylval featurelval
#define yy_create_buffer feature_create_buffer
#define yy_delete_buffer feature_delete_buffer
#define yy_flex_debug feature_flex_debug
#define yy_init_buffer feature_init_buffer
#define yy_flush_buffer feature_flush_buffer
#define yy_load_buffer_state feature_load_buffer_state
#define yy_switch_to_buffer feature_switch_to_buffer
#define yyin featurein
#define yyleng featureleng
#define yylex featurelex
#define yylineno featurelineno
#define yyout featureout
#define yyrestart featurerestart
#define yytext featuretext
#define yywrap featurewrap
#define yyalloc featurealloc
#define yyrealloc featurerealloc
#define yyfree featurefree

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
#define yyparse         featureparse
#define yylex           featurelex
#define yyerror         featureerror
#define yydebug         featuredebug
#define yynerrs         featurenerrs

#define yylval          featurelval
#define yychar          featurechar

/* Copy the first part of user declarations.  */
#line 1 "parsers/featureParser.y" /* yacc.c:339  */

	//#define YACC_DEBUG_ON
	
	#ifndef MAX_STR_LENGTH
		#define MAX_STR_LENGTH 256
	#endif
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <float.h>
	#include "structs.h"
	#include "featureCompute.h"
	//#include "featureStructs.h"
	
	//Function Declarations
	void yyerror(char *);
	
	//External Objects
	extern int yylex();
	extern int lineNo,charPos,yyleng,yylineno,yychar,oldPos;
	extern char line[MAX_STR_LENGTH],oldLine[MAX_STR_LENGTH];
	extern FILE *yyin;
	extern char* yytext;
	extern struct phaver* HA;
	extern struct phaver* featureHA;
	
	//Global Objects
	struct feature* sysFeature;
	int errNo,err1No,err2No,err3No,err4No,err5No,err6No;
	int currentMatch;
	int porvID = 1;
	int temporalFlag = 0;
	char F_dummy[1] = {'\0'};
	char* syncLabel = NULL;			//Will eventually be a user input
	
	//Error Types : Will be eventually useful when the parsers show detailed, helpful parse error messages
	enum errorType {
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

#line 124 "featureParser.tab.c" /* yacc.c:339  */

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
   by #include "featureParser.tab.h".  */
#ifndef YY_FEATURE_FEATUREPARSER_TAB_H_INCLUDED
# define YY_FEATURE_FEATUREPARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int featuredebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    FEATURE = 258,
    FBEGIN = 259,
    FEND = 260,
    FVAR = 261,
    FCOMPUTE = 262,
    FLEFT_SQR_BRKT = 263,
    FRIGHT_SQR_BRKT = 264,
    FOPENROUND = 265,
    FCLOSEROUND = 266,
    FCOMMA = 267,
    FATPOSEDGE = 268,
    FATNEGEDGE = 269,
    FATANYEDGE = 270,
    FINTIME = 271,
    FAND = 272,
    FOR = 273,
    FRATIONAL = 274,
    FARITHOP = 275,
    FTRUE = 276,
    FASSIGN = 277,
    FEQ = 278,
    FLEQ = 279,
    FGEQ = 280,
    FLT = 281,
    FGT = 282,
    FSEMICOLON = 283,
    FCOLON = 284,
    FANY = 285,
    FATOM = 286,
    FDOLLARTIME = 287,
    FSTATE = 288
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 58 "parsers/featureParser.y" /* yacc.c:355  */

		char string[1024];
		struct identifier* id;
		struct condition* cond;
		struct PORV* porvType;
		struct eventType* event;
		struct PORVExpression* porvExpr;
		struct expression* subSeqExpr;
		struct timeDelay* delay;
		struct sequenceExpr* seq;
		struct featureDef* def;
		struct feature* featureSkeleton;
		int code;
	

#line 214 "featureParser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE featurelval;

int featureparse (void);

#endif /* !YY_FEATURE_FEATUREPARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 231 "featureParser.tab.c" /* yacc.c:358  */

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   107

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  54
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  102

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    86,    86,    99,   115,   125,   137,   146,   156,   164,
     174,   193,   203,   218,   226,   256,   269,   281,   295,   307,
     338,   344,   350,   357,   366,   372,   378,   387,   394,   404,
     428,   435,   445,   461,   470,   481,   492,   499,   506,   512,
     518,   527,   534,   541,   552,   560,   572,   581,   592,   600,
     627,   637,   650,   659,   667
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FEATURE", "FBEGIN", "FEND", "FVAR",
  "FCOMPUTE", "FLEFT_SQR_BRKT", "FRIGHT_SQR_BRKT", "FOPENROUND",
  "FCLOSEROUND", "FCOMMA", "FATPOSEDGE", "FATNEGEDGE", "FATANYEDGE",
  "FINTIME", "FAND", "FOR", "FRATIONAL", "FARITHOP", "FTRUE", "FASSIGN",
  "FEQ", "FLEQ", "FGEQ", "FLT", "FGT", "FSEMICOLON", "FCOLON", "FANY",
  "FATOM", "FDOLLARTIME", "FSTATE", "$accept", "featureSpec", "params",
  "param", "featureDefinition", "featureBody", "varDecl",
  "featureStatement", "sequenceExpression", "timing", "time",
  "subExpression", "mixedExpr", "PORVExprWrapper", "PORVExpr",
  "BPORVconjunct", "PORVconjunct", "porv", "eventExpr", "ineq",
  "eventType", "arithExpr", "arithStatement", "assignments", "assignment",
  "rational", YY_NULLPTR
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
     285,   286,   287,   288
};
# endif

#define YYPACT_NINF -67

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-67)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      11,   -14,    45,    -3,   -67,    22,    55,   -67,    61,    62,
      48,   -67,    47,    22,    22,     0,   -67,   -67,   -67,    68,
      42,   -67,    21,   -67,    64,    60,   -67,    63,    65,    69,
      55,   -67,    50,   -67,    -1,   -67,   -67,    41,   -67,    72,
      73,    74,    70,    41,    66,   -67,   -67,   -67,    49,     3,
      42,    49,    56,    78,    79,    15,   -67,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   -67,    22,   -67,   -67,   -67,    15,
      19,    19,    71,    67,    80,    -7,    75,   -67,   -67,   -67,
     -67,   -67,    15,   -67,   -67,    85,   -67,   -67,   -67,   -67,
      19,   -67,    49,    76,   -67,   -67,   -67,    -4,    81,    82,
     -67,   -67
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     6,     0,     5,
       0,     3,     0,     0,     0,     0,    41,    42,    43,     0,
       0,     9,     0,    13,    18,    20,    24,    27,    22,     0,
       0,     4,     0,    53,     0,    33,    49,     0,    46,     0,
       0,     0,    31,     0,    45,    48,     7,     8,     0,     0,
       0,     0,     0,     0,     0,     0,     2,    10,    54,    47,
      40,    38,    39,    36,    37,     0,    26,    25,    29,     0,
       0,     0,     0,     0,    51,     0,     0,    14,    17,    12,
      19,    21,     0,    28,    23,     0,    34,    30,    32,    44,
       0,    11,     0,     0,    35,    52,    50,     0,     0,     0,
      16,    15
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -67,   -67,    27,    -5,    77,   -67,   -67,    83,   -67,   -67,
     -67,    51,   -67,   -12,    -9,   -67,    28,    43,    52,    57,
     -67,   -66,   -67,   -49,   -67,   -48
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     8,    38,    11,    19,    20,    21,    22,    50,
      77,    23,    24,    25,    26,    27,    41,    42,    28,    65,
      29,    43,    44,    73,    74,    45
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       9,    78,    80,    39,    88,    89,    40,     5,     9,     9,
      15,    75,    33,    76,     1,    33,    76,     3,    58,    33,
      34,    35,    33,    76,    95,     6,    98,    93,    48,    59,
       7,     7,    36,    37,    33,    34,    35,    49,    33,    34,
      31,    32,    84,    96,    83,     4,     7,    36,    37,    99,
       7,    36,    15,     7,    14,    16,    17,    18,    15,    10,
      86,    16,    17,    18,    60,    61,    62,    63,    64,    16,
      17,    18,    12,    46,    13,    30,    51,    52,    57,    55,
      72,    53,    54,    66,    67,    68,    71,    69,    82,    15,
     100,   101,    92,    90,    58,    91,    94,    87,    85,     0,
      70,    79,     0,    47,    81,    97,     0,    56
};

static const yytype_int8 yycheck[] =
{
       5,    49,    51,    15,    70,    71,    15,    10,    13,    14,
      10,     8,    19,    20,     3,    19,    20,    31,    19,    19,
      20,    21,    19,    20,    90,    28,    30,    75,     7,    34,
      31,    31,    32,    33,    19,    20,    21,    16,    19,    20,
      13,    14,    54,    92,    53,     0,    31,    32,    33,    97,
      31,    32,    10,    31,     6,    13,    14,    15,    10,     4,
      65,    13,    14,    15,    23,    24,    25,    26,    27,    13,
      14,    15,    11,     5,    12,    28,    12,    17,    28,    10,
      31,    18,    17,    11,    11,    11,    20,    17,    10,    10,
       9,     9,    12,    22,    19,    28,    11,    69,    55,    -1,
      43,    50,    -1,    20,    52,    29,    -1,    30
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    35,    31,     0,    10,    28,    31,    36,    37,
       4,    38,    11,    12,     6,    10,    13,    14,    15,    39,
      40,    41,    42,    45,    46,    47,    48,    49,    52,    54,
      28,    36,    36,    19,    20,    21,    32,    33,    37,    47,
      48,    50,    51,    55,    56,    59,     5,    41,     7,    16,
      43,    12,    17,    18,    17,    10,    38,    28,    19,    37,
      23,    24,    25,    26,    27,    53,    11,    11,    11,    17,
      53,    20,    31,    57,    58,     8,    20,    44,    59,    45,
      57,    52,    10,    48,    47,    51,    37,    50,    55,    55,
      22,    28,    12,    59,    11,    55,    57,    29,    30,    59,
       9,     9
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    34,    35,    35,    36,    36,    37,    38,    39,    39,
      40,    41,    42,    42,    43,    44,    44,    44,    45,    45,
      46,    46,    46,    46,    47,    47,    47,    48,    48,    49,
      50,    50,    51,    51,    51,    52,    53,    53,    53,    53,
      53,    54,    54,    54,    55,    55,    56,    56,    56,    56,
      57,    57,    58,    59,    59
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     7,     4,     3,     1,     1,     3,     2,     1,
       3,     4,     3,     1,     2,     5,     5,     1,     1,     3,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     1,     3,     1,     3,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     2,     1,     1,
       3,     1,     3,     1,     2
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
#line 86 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
												#ifdef YACC_DEBUG_ON 
													printf("PARSER: Finito - featureSpec (A) \n");
												#endif
												(yyval.featureSkeleton) = createFeature((yyvsp[-5].string),(yyvsp[-3].id),(yyvsp[0].def));
												//printFeature($$);
												sysFeature = (yyval.featureSkeleton);
												
												if(temporalFlag == 1){
													tuneForTemporalProperties(HA);
												}
												//displayAutomaton(HA);
											}
#line 1393 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 99 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
												#ifdef YACC_DEBUG_ON 
													printf("PARSER: Finito - featureSpec (B)\n");
												#endif
												(yyval.featureSkeleton) = createFeature((yyvsp[-2].string),NULL,(yyvsp[0].def));
												//printFeature($$);
												sysFeature = (yyval.featureSkeleton);
												
												if(temporalFlag == 1){
													tuneForTemporalProperties(HA);
												}
												//displayAutomaton(HA);
											}
#line 1411 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 115 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: Parameter List\n");
							#endif
							
							(yyval.id)=addToIdentifierList((yyvsp[0].id),(yyvsp[-2].string));
							
							//strcpy($$,$1);
						}
#line 1425 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 125 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: Single Parameter\n");
							#endif
							
							(yyval.id)=createIdentifier((yyvsp[0].string));
							
							
							//strcpy($$,$1);
						}
#line 1440 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 137 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: Single FATOM [  %s  ]\n",(yyvsp[0].string));
							#endif
							strcpy((yyval.string),(yyvsp[0].string));
							//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1452 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 146 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: Feature Definition : BEGIN featureBody END\n");
							#endif
							(yyval.def) = (yyvsp[-1].def);
							//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1464 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 156 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: featureBody: varDecl featureStatement\n");
							#endif
							(yyvsp[0].def)->localVars = (yyvsp[-1].id);
							(yyval.def) = (yyvsp[0].def);
							//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1477 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 164 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: featureBody: featureStatement\n");
							#endif
							(yyval.def) = (yyvsp[0].def);
							//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1489 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 174 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: varDecl: FVAR params : [   %s  ]\n",(yyvsp[-2].string));
							#endif
							(yyval.id) = (yyvsp[-1].id);
							
							//Add each local variable to the set of control variable of the HA
							struct identifier *var = (yyval.id);
							while(var!=NULL){
								//Add each local variable to the set of control variable of the HA
								addLocalVariable(HA,var,DBL_MIN,0);
								var = var->next;
							}
							
							//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1510 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 194 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: featureStatement: sequenceExpression FCOMPUTE assignments\n");
							#endif
							(yyval.def) = createFeatureDef(NULL,(yyvsp[-3].seq),(yyvsp[-1].cond));
						}
#line 1521 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 203 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: sequenceExpression: subExpression timing sequenceExpression\n");
							#endif
							(yyvsp[0].seq)->delay = (yyvsp[-1].delay);
							
							#ifdef YACC_DEBUG_ON 
								printf("Setting the Time Delay $2 = %u\n",(yyvsp[-1].delay));
								printf("After Setting the Time Delay $3->delay = %u\n",(yyvsp[0].seq)->delay);
								
								printf("[FINTIME --------------- ] CRETED NODE [%f %f %d]\n",(yyvsp[0].seq)->delay->lower,(yyvsp[0].seq)->delay->upper,(yyvsp[0].seq)->delay->type);
							#endif
							(yyval.seq) = addSequenceExprToEOfList((yyvsp[-2].seq),(yyvsp[0].seq));
							
						}
#line 1541 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 218 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: sequenceExpression: subExpression \n");
							#endif
							(yyval.seq) = (yyvsp[0].seq);
						}
#line 1552 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 226 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: timing:	FINTIME time\n");
							#endif
							(yyval.delay) = (yyvsp[0].delay);
							
							#ifdef YACC_DEBUG_ON 
								printf("$2 = %u\n",(yyvsp[0].delay));
								printf("$$ = %u\n",(yyval.delay));
							
								printf("HA->temporal = %d\n",HA->temporal);
							#endif
							temporalFlag = 1;
							/*if(HA->temporal==0)
								tuneForTemporalProperties(HA);
							
							#ifdef YACC_DEBUG_ON 
							if(HA->temporal==0){
								printf("ERROR TEMPORAL\n");
								exit(0);
							}
							#endif 
							*/
							#ifdef YACC_DEBUG_ON 
								printf("[FINTIME --------------- ] CRETED NODE [%f %f %d]\n",(yyval.delay)->lower,(yyval.delay)->upper,(yyval.delay)->type);
							#endif
							//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1585 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 256 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
									#ifdef YACC_DEBUG_ON 
										printf("PARSER: time");//: %s %s %s %s %s\n",$1,$2,$3,$4,$5);
									#endif
									
									(yyval.delay) = createTimeDelay(atof((yyvsp[-3].string)),atof((yyvsp[-1].string)),0);
									
									#ifdef YACC_DEBUG_ON 
										printf("Time = ##[%f:%f]\n",(yyval.delay)->lower,(yyval.delay)->upper);
										printf("Return %u\n",(yyval.delay));
									#endif
									//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
								}
#line 1603 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 269 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
									#ifdef YACC_DEBUG_ON 
										printf("PARSER: time");//: %s %s %s %s %s\n",$1,$2,$3,$4,$5);
									#endif
									
									(yyval.delay) = createTimeDelay(atof((yyvsp[-3].string)),0,1);
									#ifdef YACC_DEBUG_ON 
										printf("Time = ##[%f:]\n",(yyval.delay)->lower);
										printf("Return %u\n",(yyval.delay));
									#endif
									//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
								}
#line 1620 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 281 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: time: %s\n",(yyvsp[0].string));
							#endif
							
							(yyval.delay) = createTimeDelay(atof((yyvsp[0].string)),0,2);printf("Time = ##%f\n",(yyval.delay)->lower);
							#ifdef YACC_DEBUG_ON 
								printf("Return %u\n",(yyval.delay));
							#endif
							
							//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1637 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 295 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: subExpression: mixedExpr\n");
							#endif
							(yyval.seq) = createSequenceExpr((yyvsp[0].subSeqExpr),NULL,NULL);
							//Split on Event
							if(syncLabel==NULL){
								syncLabel = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
								strcpy(syncLabel,HA->ha->synclabs->name);
							}
							//splitOnEvent(HA,$$,syncLabel);
						}
#line 1654 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 307 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: subExpression: mixedExpr FCOMMA assignments\n");
							#endif
							(yyval.seq) = createSequenceExpr((yyvsp[-2].subSeqExpr),NULL,(yyvsp[0].cond));
							// Split on event
							#ifdef YACC_DEBUG_ON 
								printf("Created Sequence Expr HERE");
							#endif
							
							if(syncLabel==NULL){
								syncLabel = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
								#ifdef YACC_DEBUG_ON 
									printf("syncLabel HERE");
								#endif
								strcpy(syncLabel,HA->ha->synclabs->name);
								#ifdef YACC_DEBUG_ON 
									printf("copied HERE");
								#endif
							}
							#ifdef YACC_DEBUG_ON 
								printf("before split HERE");
							#endif
							//splitOnEvent(HA,$$,syncLabel);
							#ifdef YACC_DEBUG_ON 
								printf("split HERE");
							#endif
						}
#line 1687 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 338 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: mixedExpr: PORVExprWrapper\n");
							#endif
							(yyval.subSeqExpr) = createExpression((yyvsp[0].porvExpr),NULL);
						}
#line 1698 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 344 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: mixedExpr:  PORVExprWrapper FAND eventExpr\n");
							#endif
							(yyval.subSeqExpr)=createExpression((yyvsp[-2].porvExpr),(yyvsp[0].event));
						}
#line 1709 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 350 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: mixedExpr: eventExprs\n");
							#endif
							(yyval.subSeqExpr) = createExpression(NULL,(yyvsp[0].event));		
							
						}
#line 1721 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 357 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: mixedExpr:  PORVExprWrapper FAND eventExpr\n");
							#endif
							(yyval.subSeqExpr)=createExpression((yyvsp[0].porvExpr),(yyvsp[-2].event));
						}
#line 1732 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 366 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: PORVExprWrapper: PORVExpr\n");
							#endif
							(yyval.porvExpr) = (yyvsp[0].porvExpr);
						}
#line 1743 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 372 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: PORVExprWrapper: FOPENROUND PORVExpr FCLOSEROUND	\n");
							#endif
							(yyval.porvExpr) = (yyvsp[-1].porvExpr);
						}
#line 1754 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 378 "parsers/featureParser.y" /* yacc.c:1646  */
    {
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: PORVExprWrapper: FOPENROUND PORVExprWrapper FCLOSEROUND	\n");
							#endif
							(yyval.porvExpr) = (yyvsp[-1].porvExpr);
						}
#line 1765 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 387 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: PORVExpr: BPORVconjunct\n");
							#endif
							(yyval.porvExpr) = createPORVExpression((yyvsp[0].porvType));
							
						}
#line 1777 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 394 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: PORVExpr: BPORVconjunct FOR PORVExpr\n");
							#endif
							struct PORVExpression* porvExpr = createPORVExpression((yyvsp[-2].porvType));
							(yyval.porvExpr) = addPORVExpressionToEOfList((yyvsp[0].porvExpr),porvExpr);	
						}
#line 1789 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 404 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: BPORVconjunct: FOPENROUND PORVconjunct FCLOSEROUND\n");
							#endif
							
							(yyval.porvType) = (yyvsp[-1].porvType);
							
							#ifdef YACC_DEBUG_ON 
								printPORVConjunct((yyval.porvType));
							#endif
							
							struct PORV* porvConjunct = (yyval.porvType);
							//printPORVConjunct($$);
							
							//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
							if(syncLabel==NULL){
								syncLabel = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
								strcpy(syncLabel,HA->ha->synclabs->name);
							}
							//HA = splitPORVConjunct(HA,$$,syncLabel);
						}
#line 1815 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 428 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: PORVconjunct: porv FAND PORVconjunct\n");
							#endif
							(yyval.porvType) = addPORVToList((yyvsp[0].porvType),(yyvsp[-2].porvType));
							//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1827 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 435 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: PORVconjunct: porv\n");
							#endif
							
							(yyval.porvType)=(yyvsp[0].porvType);
							//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1840 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 445 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: porv: arithExpr ineq arithExpr\n");
							#endif
							
							(yyvsp[-2].cond)->op = (yyvsp[-1].code);
							strcpy((yyvsp[-2].cond)->RHS,(yyvsp[0].cond)->LHS);
							(yyval.porvType) = createPORV((yyvsp[-2].cond),porvID++);
							#ifdef YACC_DEBUG_ON 
								printf("====================== [%u] [%u]==============\n",(yyvsp[-2].cond),(yyvsp[-2].cond)->next);
								if((yyvsp[-2].cond) == (yyvsp[-2].cond)->next){
									exit(0);
								}
							#endif
							//strcpy($$,$1);
						}
#line 1861 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 461 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: porv: FTRUE\n");
							#endif
							
							struct condition* temp = createCondition((yyvsp[0].string),F_dummy,-1);
							(yyval.porvType) = createPORV(temp,-1);
							//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1875 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 470 "parsers/featureParser.y" /* yacc.c:1646  */
    {
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: porv: FSTATE ineq param\n");
							#endif
							struct condition* stateCond = createCondition((yyvsp[-2].string),(yyvsp[0].string),(yyvsp[-1].code));
							(yyval.porvType) = createPORV(stateCond,0);
						}
#line 1887 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 481 "parsers/featureParser.y" /* yacc.c:1646  */
    {
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: eventExpr: eventType FOPENROUND porv FCLOSEROUND\n");
							#endif
							
							(yyval.event)=createEvent((yyvsp[-3].code),(yyvsp[-1].porvType));
							//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1900 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 492 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: ineq: FLT [  %s  ]\n",(yyvsp[0].string));
							#endif
							yyerror("A '<' inequality is not allowed\n");
							(yyval.code) =4;//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1912 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 499 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: ineq: FGT [  %s  ]\n",(yyvsp[0].string));
							#endif
							yyerror("A '>' inequality is not allowed\n");
							(yyval.code) = 5;//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1924 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 506 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: ineq: FLEQ [  %s  ]\n",(yyvsp[0].string));
							#endif
							(yyval.code) = 1;//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1935 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 512 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: ineq: FGEQ [  %s  ]\n",(yyvsp[0].string));
							#endif
							(yyval.code) = 3;//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1946 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 518 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: ineq: FEQ [  %s  ]\n",(yyvsp[0].string));
							#endif
							(yyval.code) = 0;//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1957 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 527 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: eventType: FATPOSEDGE [  %s  ]\n",(yyvsp[0].string));
							#endif
							(yyval.code) = 1;
							//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1969 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 534 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: eventType: FATNEGEDGE [  %s  ]\n",(yyvsp[0].string));
							#endif
							(yyval.code) = -1;
							//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1981 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 541 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
							#ifdef YACC_DEBUG_ON 
								printf("PARSER: eventType: FATANYEDGE [  %s  ]\n",(yyvsp[0].string));
							#endif
							
							(yyval.code) = 0;
							//$$=createCondition($1->name,F_dummy,-1);//strcpy($$,$1);
						}
#line 1994 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 552 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
								#ifdef YACC_DEBUG_ON 
									printf("PARSER: Complex Arith Expr\n");	
								#endif
								sprintf((yyvsp[-2].cond)->LHS,"%s %s %s",(yyvsp[-2].cond)->LHS,(yyvsp[-1].string),(yyvsp[0].cond)->LHS);
								(yyval.cond) = (yyvsp[-2].cond);
								//strcat($2,$3);strcat($1,$2);strcpy($$,$1);
							}
#line 2007 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 560 "parsers/featureParser.y" /* yacc.c:1646  */
    {
								#ifdef YACC_DEBUG_ON 
									printf("PARSER: Simple Arith Statement\n");
								#endif
								
								(yyval.cond) = (yyvsp[0].cond);
								//strcpy($$,$1);
							}
#line 2020 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 572 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
								#ifdef YACC_DEBUG_ON 
									printf("PARSER: Linear Expr is an ID\n");
								//strcpy($$,$1);
								#endif
							
								(yyval.cond)=createCondition((yyvsp[0].string),F_dummy,-1);
								//strcpy($$,$1);
							}
#line 2034 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 581 "parsers/featureParser.y" /* yacc.c:1646  */
    {
								#ifdef YACC_DEBUG_ON 
									printf("PARSER: Linear Expr is an ID\n");
								//strcpy($2,$1);//strcpy($$,$1);
								#endif
								
								sprintf((yyvsp[-1].string),"%s %s",(yyvsp[-1].string),(yyvsp[0].string));
								(yyval.cond)=createCondition((yyvsp[-1].string),F_dummy,-1);
								
								//strcat($1,$2);strcpy($$,$1);
							}
#line 2050 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 592 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
								#ifdef YACC_DEBUG_ON 
									printf("PARSER: Linear Expr is a Rational\n");
								#endif
								
								(yyval.cond)=createCondition((yyvsp[0].string),F_dummy,-1);
								//strcpy($$,$1);
							}
#line 2063 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 600 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
								#ifdef YACC_DEBUG_ON 
									printf("PARSER: Linear Expr is $TIME\n");
								#endif
								
								(yyval.cond)=createCondition("time",F_dummy,-1);
								#ifdef YACC_DEBUG_ON 
									printf("HA->temporal = %d\n",HA->temporal);
								#endif
								
								temporalFlag = 1;
								/*if(HA->temporal==0)
									tuneForTemporalProperties(HA);
								
								#ifdef YACC_DEBUG_ON 
								if(HA->temporal==0){
									printf("ERROR TEMPORAL\n");
									exit(0);
								}
								#endif
								*/
								
								//strcpy($$,$1);
							}
#line 2092 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 627 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
								#ifdef YACC_DEBUG_ON 
									printf("PARSER: assignments: assignment FCOMMA assignments\n");
								#endif
								
								(yyval.cond) = addConditionToList((yyvsp[0].cond),(yyvsp[-2].cond));
								
								//$$=createCondition($1->name,F_dummy,-1);
								//strcpy($$,$1);
							}
#line 2107 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 637 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
								#ifdef YACC_DEBUG_ON 
									printf("PARSER: assignments: assignment\n");
								#endif
								
								(yyval.cond) = (yyvsp[0].cond);
								
								//$$=createCondition($1->name,F_dummy,-1);
								//strcpy($$,$1);
							}
#line 2122 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 650 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
								#ifdef YACC_DEBUG_ON 
									printf("PARSER: assignment: FATOM FASSIGN arithExpr [  %s %s %s  ]\n",(yyvsp[-2].string),(yyvsp[-1].string),(yyvsp[0].cond));
								#endif
								
								(yyval.cond)=createCondition((yyvsp[-2].string),(yyvsp[0].cond)->LHS,2);//strcpy($$,$1);
							}
#line 2134 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 659 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
								#ifdef YACC_DEBUG_ON 
									printf("PARSER: Linear Expr is a Rational\n");
								#endif
								
								//$$=createCondition($1,F_dummy,-1);
								strcpy((yyval.string),(yyvsp[0].string));
							}
#line 2147 "featureParser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 668 "parsers/featureParser.y" /* yacc.c:1646  */
    {	
								#ifdef YACC_DEBUG_ON 
									printf("PARSER: Linear Expr is a Rational\n");
								#endif
								
								//$$=createCondition($1,F_dummy,-1);
								sprintf((yyval.string),"%s%s",(yyvsp[-1].string),(yyvsp[0].string));
								//strcpy($$,$1);
							}
#line 2161 "featureParser.tab.c" /* yacc.c:1646  */
    break;


#line 2165 "featureParser.tab.c" /* yacc.c:1646  */
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
#line 679 "parsers/featureParser.y" /* yacc.c:1906  */



void yyerror(char *s) {

	char errorMsg[MAX_STR_LENGTH];
	int flag = 0;
	switch(errNo){
		/*case BLOCK_NO_NEWLINE:	sprintf(errorMsg,"New statements must fall on a new line.");
					currentMatch = charPos;
					break;*/
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
	if(strlen(line)==0){
		strcpy(line,oldLine);
		charPos = oldPos;
		lineNo--;
	}
	if(flag==1){
		currentMatch = charPos+1;
	}
	//fprintf(stderr, "%s at Line %d ; %s Match [%d], line :[%s],  ERROR CODES: [%d,%d,%d,%d,%d,%d,%d]\n", s,lineNo,errorMsg,currentMatch,line,errNo,err1No,err2No,err3No,err4No,err5No,err6No);
	fprintf(stderr, "%s at Line %d : %s \n", s,lineNo,errorMsg);
	fprintf(stderr, "%s\n",line);
	int i=0;
	for(i=1;i<currentMatch;i++){
		printf(" ");
	}
	printf("^\n");
	exit(0);
	
	
}
/*
int main(int argc, char *argv[]) {
	yyin = fopen(argv[1], "r");
	setbuf(stdout, NULL);
	yyparse();
}

*/
