/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    CREATE = 259,                  /* CREATE  */
    DROP = 260,                    /* DROP  */
    TABLE = 261,                   /* TABLE  */
    TABLES = 262,                  /* TABLES  */
    INDEX = 263,                   /* INDEX  */
    SELECT = 264,                  /* SELECT  */
    INNER_JOIN = 265,              /* INNER_JOIN  */
    DESC = 266,                    /* DESC  */
    SHOW = 267,                    /* SHOW  */
    SYNC = 268,                    /* SYNC  */
    INSERT = 269,                  /* INSERT  */
    DELETE = 270,                  /* DELETE  */
    UPDATE = 271,                  /* UPDATE  */
    LBRACE = 272,                  /* LBRACE  */
    RBRACE = 273,                  /* RBRACE  */
    COMMA = 274,                   /* COMMA  */
    TRX_BEGIN = 275,               /* TRX_BEGIN  */
    TRX_COMMIT = 276,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 277,            /* TRX_ROLLBACK  */
    INT_T = 278,                   /* INT_T  */
    STRING_T = 279,                /* STRING_T  */
    FLOAT_T = 280,                 /* FLOAT_T  */
    HELP = 281,                    /* HELP  */
    EXIT = 282,                    /* EXIT  */
    DOT = 283,                     /* DOT  */
    INTO = 284,                    /* INTO  */
    VALUES = 285,                  /* VALUES  */
    FROM = 286,                    /* FROM  */
    WHERE = 287,                   /* WHERE  */
    AND = 288,                     /* AND  */
    SET = 289,                     /* SET  */
    ON = 290,                      /* ON  */
    LOAD = 291,                    /* LOAD  */
    DATA = 292,                    /* DATA  */
    INFILE = 293,                  /* INFILE  */
    EQ = 294,                      /* EQ  */
    LT = 295,                      /* LT  */
    GT = 296,                      /* GT  */
    LE = 297,                      /* LE  */
    GE = 298,                      /* GE  */
    NE = 299,                      /* NE  */
    BELONG = 300,                  /* BELONG  */
    NOTBELONG = 301,               /* NOTBELONG  */
    DATE_T = 302,                  /* DATE_T  */
    ORDER_BY = 303,                /* ORDER_BY  */
    ASC = 304,                     /* ASC  */
    UNIQUEINDEX = 305,             /* UNIQUEINDEX  */
    ISNOTNULL = 306,               /* ISNOTNULL  */
    ISNULL = 307,                  /* ISNULL  */
    NULLABLE = 308,                /* NULLABLE  */
    NOTNULL = 309,                 /* NOTNULL  */
    NULL_T = 310,                  /* NULL_T  */
    TEXT_T = 311,                  /* TEXT_T  */
    NUMBER = 312,                  /* NUMBER  */
    FLOAT = 313,                   /* FLOAT  */
    ID = 314,                      /* ID  */
    AGGREGATE = 315,               /* AGGREGATE  */
    PATH = 316,                    /* PATH  */
    SSS = 317,                     /* SSS  */
    STAR = 318,                    /* STAR  */
    STRING_V = 319,                /* STRING_V  */
    DATE = 320                     /* DATE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 127 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
  char *position;

#line 139 "yacc_sql.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyparse (void *scanner);


#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
