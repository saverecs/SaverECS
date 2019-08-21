/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 53 "parsers/haslacParser.y" /* yacc.c:1909  */

	char string[MAX_STR_LENGTH];
	struct phaver* pha;
	struct automaton* aut;
	struct condition* cond;
	struct identifier* ident;
	struct location* loc;
	struct transition* trans;
	struct initial* init;
	int code;		

#line 111 "haslacParser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE haslaclval;

int haslacparse (void);

#endif /* !YY_HASLAC_HASLACPARSER_TAB_H_INCLUDED  */
