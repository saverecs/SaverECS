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
#line 58 "parsers/featureParser.y" /* yacc.c:1909  */

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
	

#line 104 "featureParser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE featurelval;

int featureparse (void);

#endif /* !YY_FEATURE_FEATUREPARSER_TAB_H_INCLUDED  */
