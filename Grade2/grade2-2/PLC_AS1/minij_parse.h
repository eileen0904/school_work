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

#ifndef YY_YY_MINIJ_PARSE_H_INCLUDED
# define YY_YY_MINIJ_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CLASS = 258,
    PUB = 259,
    STATIC = 260,
    AND = 261,
    OR = 262,
    LT = 263,
    LE = 264,
    EQ = 265,
    ADD = 266,
    MINUS = 267,
    TIMES = 268,
    LBP = 269,
    RBP = 270,
    LSP = 271,
    RSP = 272,
    LP = 273,
    RP = 274,
    INT = 275,
    BOOLEAN = 276,
    IF = 277,
    ELSE = 278,
    WHILE = 279,
    PRINT = 280,
    ASSIGN = 281,
    VOID = 282,
    MAIN = 283,
    STR = 284,
    RETURN = 285,
    SEMI = 286,
    COMMA = 287,
    THIS = 288,
    NEW = 289,
    DOT = 290,
    ID = 291,
    LIT = 292,
    TRUE = 293,
    FALSE = 294,
    NOT = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MINIJ_PARSE_H_INCLUDED  */
