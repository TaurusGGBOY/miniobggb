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
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "yacc_sql.y" /* yacc.c:339  */


#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  size_t values_size;
  size_t sub_selects_length;
  //sub_selects和sub_condtion_length是一个栈
  SubQuries sub_selects[10];
  size_t sub_condition_length[10];
  Value values_list[MAX_NUM][MAX_NUM];
  size_t values_length_list[MAX_NUM];
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp[MAX_NUM];
  size_t comp_length;
	char id[MAX_NUM];
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->ssql->sstr.insertion.value_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 131 "yacc_sql.tab.c" /* yacc.c:339  */

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
   by #include "yacc_sql.tab.h".  */
#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
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
    SEMICOLON = 258,
    CREATE = 259,
    DROP = 260,
    TABLE = 261,
    TABLES = 262,
    INDEX = 263,
    SELECT = 264,
<<<<<<< HEAD
    INNER_JOIN = 265,
    DESC = 266,
    SHOW = 267,
    SYNC = 268,
    INSERT = 269,
    DELETE = 270,
    UPDATE = 271,
    LBRACE = 272,
    RBRACE = 273,
    COMMA = 274,
    TRX_BEGIN = 275,
    TRX_COMMIT = 276,
    TRX_ROLLBACK = 277,
    INT_T = 278,
    STRING_T = 279,
    FLOAT_T = 280,
    HELP = 281,
    EXIT = 282,
    DOT = 283,
    INTO = 284,
    VALUES = 285,
    FROM = 286,
    WHERE = 287,
    AND = 288,
    SET = 289,
    ON = 290,
    LOAD = 291,
    DATA = 292,
    INFILE = 293,
    EQ = 294,
    LT = 295,
    GT = 296,
    LE = 297,
    GE = 298,
    NE = 299,
    IN = 300,
    DATE_T = 301,
    ORDER_BY = 302,
    ASC = 303,
    UNIQUEINDEX = 304,
    ISNOTNULL = 305,
    ISNULL = 306,
    NULLABLE = 307,
    NOTNULL = 308,
    NULL_T = 309,
    NUMBER = 310,
    FLOAT = 311,
    ID = 312,
    AGGREGATE = 313,
    PATH = 314,
    SSS = 315,
    STAR = 316,
    STRING_V = 317,
    DATE = 318
=======
    DESC = 265,
    SHOW = 266,
    SYNC = 267,
    INSERT = 268,
    DELETE = 269,
    UPDATE = 270,
    LBRACE = 271,
    RBRACE = 272,
    COMMA = 273,
    TRX_BEGIN = 274,
    TRX_COMMIT = 275,
    TRX_ROLLBACK = 276,
    INT_T = 277,
    STRING_T = 278,
    FLOAT_T = 279,
    HELP = 280,
    EXIT = 281,
    DOT = 282,
    INTO = 283,
    VALUES = 284,
    FROM = 285,
    WHERE = 286,
    AND = 287,
    SET = 288,
    ON = 289,
    LOAD = 290,
    DATA = 291,
    INFILE = 292,
    EQ = 293,
    LT = 294,
    GT = 295,
    LE = 296,
    GE = 297,
    NE = 298,
    BELONG = 299,
    DATE_T = 300,
    ORDER_BY = 301,
    ASC = 302,
    UNIQUEINDEX = 303,
    NUMBER = 304,
    FLOAT = 305,
    ID = 306,
    AGGREGATE = 307,
    PATH = 308,
    SSS = 309,
    STAR = 310,
    STRING_V = 311,
    DATE = 312
>>>>>>> support in select
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
<<<<<<< HEAD
#line 125 "yacc_sql.y" /* yacc.c:355  */
=======
#line 119 "yacc_sql.y" /* yacc.c:355  */
>>>>>>> support in select

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
  char *position;

<<<<<<< HEAD
#line 245 "yacc_sql.tab.c" /* yacc.c:355  */
=======
#line 239 "yacc_sql.tab.c" /* yacc.c:355  */
>>>>>>> support in select
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

<<<<<<< HEAD
#line 261 "yacc_sql.tab.c" /* yacc.c:358  */
=======
#line 255 "yacc_sql.tab.c" /* yacc.c:358  */
>>>>>>> support in select

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
<<<<<<< HEAD
#define YYLAST   286

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
=======
#define YYLAST   282

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
>>>>>>> support in select
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
<<<<<<< HEAD
#define YYNRULES  131
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  298
=======
#define YYNRULES  121
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  286
>>>>>>> support in select

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
<<<<<<< HEAD
#define YYMAXUTOK   318
=======
#define YYMAXUTOK   312
>>>>>>> support in select

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
<<<<<<< HEAD
      55,    56,    57,    58,    59,    60,    61,    62,    63
=======
      55,    56,    57
>>>>>>> support in select
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
<<<<<<< HEAD
       0,   153,   153,   155,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   179,   184,   189,   195,   201,   207,   213,   219,   225,
     232,   237,   245,   252,   262,   269,   271,   275,   286,   294,
     302,   315,   318,   319,   320,   321,   324,   332,   349,   351,
     358,   367,   372,   376,   380,   383,   391,   401,   411,   419,
     435,   454,   455,   460,   461,   467,   470,   473,   477,   479,
     482,   485,   489,   490,   494,   499,   504,   509,   514,   519,
     526,   527,   532,   537,   542,   547,   552,   560,   565,   570,
     575,   582,   591,   598,   608,   611,   614,   617,   624,   629,
     637,   641,   643,   650,   657,   664,   666,   670,   672,   676,
     678,   683,   704,   719,   731,   743,   756,   776,   796,   818,
     839,   860,   882,   883,   884,   885,   886,   887,   888,   889,
     890,   894
=======
       0,   147,   147,   149,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   173,   178,   183,   189,   195,   201,   207,   213,   219,
     226,   231,   239,   246,   255,   257,   261,   272,   285,   288,
     289,   290,   291,   294,   303,   320,   322,   329,   338,   343,
     347,   352,   357,   365,   375,   385,   392,   411,   414,   417,
     421,   423,   426,   429,   433,   434,   438,   443,   448,   453,
     458,   463,   470,   471,   476,   481,   486,   491,   496,   504,
     509,   514,   519,   526,   535,   544,   555,   558,   561,   564,
     571,   576,   583,   585,   592,   599,   606,   608,   612,   614,
     618,   620,   625,   646,   660,   672,   687,   699,   711,   724,
     744,   764,   786,   807,   828,   850,   851,   852,   853,   854,
     855,   859
>>>>>>> support in select
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "TABLE",
<<<<<<< HEAD
  "TABLES", "INDEX", "SELECT", "INNER_JOIN", "DESC", "SHOW", "SYNC",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "HELP",
  "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON",
  "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE", "GE", "NE", "IN",
  "DATE_T", "ORDER_BY", "ASC", "UNIQUEINDEX", "ISNOTNULL", "ISNULL",
  "NULLABLE", "NOTNULL", "NULL_T", "NUMBER", "FLOAT", "ID", "AGGREGATE",
  "PATH", "SSS", "STAR", "STRING_V", "DATE", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "desc_table", "create_index", "drop_index",
  "create_table", "create_table_token", "attr_def_list", "attr_def",
  "number", "type", "ID_get", "insert", "other_values", "value_list",
  "value", "delete", "update", "select", "inner_join", "on_list",
  "agg_field", "agg_field_list", "order", "order_attr", "order_attr_list",
  "select_attr", "subselect_start", "subselect", "sub_agg_field",
  "sub_select_attr", "sub_rel_list", "attr_list", "rel_list", "where",
  "condition_list", "condition", "comOp", "load_data", YY_NULLPTR
=======
  "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC", "INSERT", "DELETE",
  "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT",
  "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "HELP", "EXIT", "DOT",
  "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON", "LOAD", "DATA",
  "INFILE", "EQ", "LT", "GT", "LE", "GE", "NE", "BELONG", "DATE_T",
  "ORDER_BY", "ASC", "UNIQUEINDEX", "NUMBER", "FLOAT", "ID", "AGGREGATE",
  "PATH", "SSS", "STAR", "STRING_V", "DATE", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "desc_table", "create_index", "drop_index",
  "create_table", "attr_def_list", "attr_def", "number", "type", "ID_get",
  "insert", "other_values", "value_list", "value", "delete", "update",
  "select", "agg_field", "agg_field_list", "order", "order_attr",
  "order_attr_list", "select_attr", "subselect_start", "subselect",
  "sub_in_select", "sub_agg_field", "sub_select_attr", "attr_list",
  "rel_list", "where", "condition_list", "condition", "comOp", "load_data", YY_NULLPTR
>>>>>>> support in select
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
<<<<<<< HEAD
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318
};
# endif

#define YYPACT_NINF -219

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-219)))
=======
     305,   306,   307,   308,   309,   310,   311,   312
};
# endif

#define YYPACT_NINF -212

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-212)))
>>>>>>> support in select

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
<<<<<<< HEAD
    -219,    97,  -219,    18,    25,    64,   -39,    36,    53,    41,
      57,    39,   100,   102,   124,   129,   133,    56,  -219,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,
    -219,    99,  -219,  -219,  -219,  -219,  -219,  -219,   108,   117,
     119,   120,    47,   161,  -219,   148,   149,   178,   179,  -219,
     126,   127,   151,  -219,  -219,  -219,  -219,  -219,   150,   169,
     152,   154,   187,   188,   135,    59,  -219,    89,   136,   137,
    -219,  -219,   165,   164,   140,   138,   142,   143,   144,  -219,
    -219,    58,   183,   183,   185,   186,   189,   164,    75,   191,
      -9,   202,   167,   180,  -219,   192,   -11,   193,   195,   114,
    -219,  -219,  -219,   194,   194,   194,   211,   158,   159,   164,
     164,    44,   208,  -219,  -219,  -219,    98,  -219,   118,   115,
     190,  -219,    44,   212,   142,   201,  -219,  -219,  -219,  -219,
      62,   163,   168,   183,   183,   166,  -219,  -219,  -219,  -219,
     196,   203,   174,   174,   207,  -219,   170,  -219,  -219,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,    27,    74,   200,   213,
     214,   198,   204,    -9,  -219,   164,   176,   192,   231,   181,
    -219,  -219,   219,   220,  -219,  -219,   222,    -9,   230,  -219,
     184,   239,   240,    44,   226,   118,  -219,  -219,   115,   217,
    -219,   197,    90,   118,   199,   205,   190,   243,   244,  -219,
    -219,  -219,   232,   245,   246,   109,   190,  -219,     6,  -219,
    -219,  -219,   207,   233,    35,   235,   206,  -219,   237,     2,
     241,   209,   164,   238,  -219,  -219,  -219,  -219,  -219,  -219,
     242,   247,   249,  -219,   250,   215,   216,   250,  -219,  -219,
     234,   255,   236,  -219,   115,  -219,  -219,  -219,  -219,   218,
    -219,   248,  -219,   221,   164,   194,   194,   194,  -219,    10,
      17,  -219,    44,  -219,   223,   252,   253,   224,  -219,  -219,
    -219,  -219,  -219,   250,   225,   250,  -219,   250,   250,  -219,
     207,  -219,  -219,  -219,  -219,  -219,    21,  -219,  -219,  -219,
     256,   250,   250,  -219,   233,  -219,  -219,  -219
=======
    -212,   113,  -212,    29,   143,    49,   -43,    12,    10,    -2,
       8,   -15,    41,    52,    53,    58,    85,    59,  -212,  -212,
    -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,  -212,  -212,  -212,  -212,    43,    69,    79,    86,
     101,    -7,    87,  -212,   106,   124,   107,   159,  -212,   112,
     114,    76,  -212,  -212,  -212,  -212,  -212,   127,   100,   132,
     147,   179,   180,   133,    34,  -212,   -10,   134,   135,  -212,
    -212,   158,   157,   138,   136,   140,   141,   142,  -212,  -212,
      13,   176,   176,   178,   181,   182,   157,   183,   184,    30,
     193,   164,   169,  -212,   185,     6,   188,   189,    64,  -212,
    -212,  -212,   190,   190,   190,   203,   156,   157,    48,   200,
    -212,  -212,   117,  -212,  -212,   137,   160,   186,  -212,    48,
     204,   140,   194,  -212,  -212,  -212,  -212,   197,   163,   165,
     176,   176,   167,  -212,  -212,  -212,  -212,   183,   171,   202,
    -212,   170,  -212,  -212,  -212,  -212,  -212,  -212,   199,    42,
      96,   206,   207,   195,    30,  -212,   157,   172,   185,   223,
     187,   210,   211,  -212,  -212,   213,  -212,   191,   227,    48,
     214,   130,   192,  -212,  -212,   160,   205,  -212,    27,   137,
     196,   186,   230,   231,  -212,  -212,  -212,   218,   234,   235,
      80,     0,  -212,  -212,   202,   221,   199,    57,   217,   224,
     215,   229,   198,   233,     5,   236,   201,   157,  -212,  -212,
    -212,  -212,  -212,  -212,   237,   238,   239,   222,   208,   209,
     222,  -212,  -212,   232,   248,   192,   240,  -212,   160,   212,
    -212,   219,  -212,  -212,  -212,  -212,   220,  -212,   241,  -212,
     190,   190,   190,  -212,    39,     7,  -212,    48,  -212,   244,
     225,   245,  -212,   157,   247,   226,  -212,  -212,  -212,   222,
     228,   222,  -212,   222,   222,  -212,   202,  -212,  -212,  -212,
    -212,  -212,  -212,  -212,    65,  -212,  -212,  -212,   249,   222,
     222,  -212,   221,  -212,  -212,  -212
>>>>>>> support in select
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
<<<<<<< HEAD
       8,     0,     5,     7,     6,     4,    18,    34,     0,     0,
       0,     0,   101,     0,    87,     0,     0,     0,     0,    23,
       0,     0,     0,    24,    25,    26,    22,    21,     0,     0,
       0,     0,     0,     0,     0,     0,    88,     0,     0,     0,
      29,    28,     0,   107,     0,     0,     0,     0,     0,    27,
      32,   101,   101,   101,     0,     0,     0,   107,    61,     0,
       0,     0,     0,     0,    46,    35,     0,     0,     0,     0,
     102,    89,    90,    68,    68,    68,     0,     0,     0,   107,
     107,     0,     0,    54,    52,    53,     0,    55,     0,     0,
     109,    56,     0,     0,     0,     0,    42,    43,    44,    45,
      40,     0,     0,   101,   101,     0,    67,    65,    66,    58,
      63,   105,    72,    72,    50,    91,     0,   122,   123,   124,
     125,   126,   127,   130,   129,   128,     0,     0,    98,     0,
       0,     0,     0,     0,   108,   107,     0,    35,     0,     0,
      38,    39,     0,     0,   103,   104,     0,     0,    61,   106,
       0,     0,     0,     0,     0,     0,   117,   111,     0,   118,
     116,     0,     0,     0,     0,     0,   109,     0,     0,    36,
      33,    41,     0,     0,     0,     0,   109,    62,    80,    73,
      59,    60,    50,    48,     0,     0,     0,    99,     0,     0,
       0,     0,   107,     0,   110,    57,   131,    37,    30,    31,
       0,     0,     0,    64,    80,     0,     0,    80,    74,    51,
       0,     0,     0,   119,     0,   112,   120,    97,    94,     0,
      96,   113,    92,     0,   107,    68,    68,    68,    77,    80,
      80,    76,     0,    47,     0,     0,     0,     0,   100,    93,
      71,    69,    70,    80,     0,    80,    81,    80,    80,    75,
      50,   121,   114,    95,   115,    84,    80,    83,    79,    78,
       0,    80,    80,    82,    48,    86,    85,    49
=======
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
       0,    92,     0,    79,     0,     0,     0,     0,    23,     0,
       0,     0,    24,    25,    26,    22,    21,     0,     0,     0,
       0,     0,     0,     0,     0,    80,     0,     0,     0,    29,
      28,     0,    98,     0,     0,     0,     0,     0,    27,    32,
      92,    92,    92,     0,     0,     0,    98,    96,     0,     0,
       0,     0,     0,    43,    34,     0,     0,     0,     0,    93,
      81,    82,    60,    60,    60,     0,     0,    98,     0,     0,
      49,    50,     0,    52,    51,     0,     0,   100,    53,     0,
       0,     0,     0,    39,    40,    41,    42,    37,     0,     0,
      92,    92,     0,    59,    57,    58,    55,    96,    64,    47,
      83,     0,   115,   116,   117,   118,   119,   120,     0,     0,
       0,     0,     0,     0,     0,    99,    98,     0,    34,     0,
       0,     0,     0,    94,    95,     0,    97,     0,     0,     0,
       0,     0,     0,   110,   102,     0,   111,   109,     0,     0,
       0,   100,     0,     0,    35,    33,    38,     0,     0,     0,
       0,    72,    65,    56,    47,    45,     0,     0,    90,     0,
       0,     0,     0,     0,     0,     0,     0,    98,   101,    54,
     121,    36,    30,    31,     0,     0,     0,    72,     0,     0,
      72,    66,    48,     0,     0,     0,     0,   112,     0,     0,
     103,     0,   105,   113,    89,    86,     0,    88,   106,    84,
      60,    60,    60,    69,    72,    72,    68,     0,    44,     0,
       0,     0,    91,    98,     0,     0,    63,    61,    62,    72,
       0,    72,    73,    72,    72,    67,    47,   104,   114,   107,
      85,    87,   108,    76,    72,    75,    71,    70,     0,    72,
      72,    74,    45,    78,    77,    46
>>>>>>> support in select
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
<<<<<<< HEAD
    -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,    94,   153,  -219,  -219,
    -219,  -219,   -26,  -209,  -107,  -219,  -219,  -219,   101,  -219,
    -219,  -103,   141,  -219,  -218,  -219,  -150,  -181,  -219,  -219,
    -219,   -72,   145,   -87,  -169,  -124,  -113,  -219
=======
    -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,  -212,
    -212,  -212,  -212,  -212,  -212,    99,   144,  -212,  -212,  -212,
    -212,   -24,  -192,  -107,  -212,  -212,  -212,  -212,   -99,  -212,
    -212,  -211,  -212,  -125,  -168,    44,  -212,  -212,   -66,   145,
     -86,    91,   119,  -112,  -212
>>>>>>> support in select
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
<<<<<<< HEAD
      26,    27,    28,    29,    30,    31,   125,    95,   202,   130,
      96,    32,   241,   184,   118,    33,    34,    35,   109,   178,
      45,   136,   181,   209,   238,    46,   119,   160,   161,   162,
     254,    66,   110,    91,   164,   120,   156,    36
=======
      26,    27,    28,    29,    30,   122,    94,   187,   127,    95,
      31,   224,   170,   115,    32,    33,    34,    44,   133,   168,
     192,   221,    45,   116,   152,   199,   153,   200,    65,   107,
      90,   155,   117,   149,    35
>>>>>>> support in select
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
<<<<<<< HEAD
     106,   137,   138,   239,   144,   157,   188,   215,   112,   100,
     101,   102,   126,   127,   128,   165,   258,   234,    47,   261,
     248,   273,   142,   143,    37,   235,    38,   224,   277,   235,
     249,    40,   291,    41,   236,   129,   235,   233,   274,   196,
     235,   276,   279,    48,   112,   113,   114,   115,   116,   187,
     190,   117,   112,   206,   237,   285,    49,   287,   275,   288,
     289,   174,   175,   265,   244,   278,    64,    39,   293,   292,
      50,   290,   214,   295,   296,    65,   212,    64,   197,   169,
     221,   113,   114,   115,   186,   107,    99,   117,    51,   113,
     114,   115,   242,    58,   108,   117,    52,     2,   113,   114,
     115,     3,     4,    53,   117,    54,     5,   243,     6,     7,
       8,     9,    10,    11,   170,   171,    82,    12,    13,    14,
      83,    42,    43,    15,    16,    44,   146,    55,   113,   114,
     115,   189,    56,    17,   117,   252,    57,   147,   148,   149,
     150,   151,   152,   153,    84,   218,    85,   219,   154,   155,
      86,   220,   270,   271,   272,   280,    59,   147,   148,   149,
     150,   151,   152,   153,   230,    60,   231,   269,   154,   155,
     232,   133,   158,   159,    61,   134,    62,    63,    67,    68,
      69,    70,    71,    72,    73,    74,    76,    77,    75,    78,
      79,    80,    81,    87,    88,    89,    90,    92,    93,    94,
      97,    98,    64,   103,   104,   121,   122,   105,   111,   123,
     131,   124,   132,   135,   139,   140,   141,   145,   166,   168,
     172,   180,   108,   163,   176,   173,   183,   185,   191,   194,
     192,   177,   193,   198,   200,   195,   201,   203,   204,   205,
     107,   208,   210,   211,   213,   216,   225,   226,   228,   229,
     227,   262,   240,   245,   217,   247,   222,   253,   263,   250,
     255,   199,   223,   246,   264,   256,   251,   257,   297,   235,
     282,   283,   259,   260,   294,   266,   267,   167,   268,   207,
     281,   284,   286,     0,   182,     0,   179
=======
     105,   139,   222,   150,   134,   135,   243,   201,    46,   246,
     217,    63,   156,    48,    99,   100,   101,   263,   218,    47,
      64,   138,   235,   172,   175,   218,    49,   219,   123,   124,
     125,    63,   236,   262,   265,    36,    51,    37,    50,    83,
      98,    84,   174,   177,    52,    85,   109,   220,   273,   259,
     275,   126,   276,   277,   264,    53,    54,   218,   109,   197,
     251,    55,   194,   281,   163,   164,   260,   206,   283,   284,
     182,   225,   228,   109,   278,   279,   203,    38,   204,   110,
     111,   112,   205,   218,   113,    81,   261,   114,    56,    82,
     227,   110,   111,   173,    58,    57,   113,   110,   111,   114,
      41,    42,   113,    66,    43,   114,   110,   111,   226,    73,
      69,   113,   280,     2,   114,   130,    75,     3,     4,   131,
      59,   239,     5,     6,     7,     8,     9,    10,    11,   214,
      60,   215,    12,    13,    14,   216,    67,    61,    15,    16,
     266,   256,   257,   258,   141,   110,   111,   176,    17,    39,
     113,    40,    62,   114,    68,   142,   143,   144,   145,   146,
     147,   148,    70,    71,    74,    72,    76,   270,   142,   143,
     144,   145,   146,   147,   196,   142,   143,   144,   145,   146,
     147,    77,    78,    79,    80,    86,    87,    88,    89,    91,
      92,    93,    96,    97,    63,   102,   118,   120,   103,   104,
     108,   106,   119,   121,   128,   129,   136,   137,   132,   140,
     157,   159,   151,   160,   161,   109,   162,   167,   154,   165,
     169,   171,   178,   183,   179,   180,   185,   188,   189,   190,
     193,   195,   202,   209,   210,   211,   186,   212,   213,   223,
     218,   230,   191,   198,   229,   231,   232,   207,   247,   233,
     234,   248,   238,   237,   240,   241,   242,   184,   285,   244,
     245,   267,   269,   252,   271,   158,   282,   250,   255,   249,
     253,   254,   208,   181,     0,     0,   268,   272,     0,   274,
       0,     0,   166
>>>>>>> support in select
};

static const yytype_int16 yycheck[] =
{
<<<<<<< HEAD
      87,   104,   105,   212,   111,   118,   156,   188,    17,    81,
      82,    83,    23,    24,    25,   122,   234,    11,    57,   237,
      18,    11,   109,   110,     6,    19,     8,   196,    11,    19,
      28,     6,    11,     8,    28,    46,    19,   206,    28,   163,
      19,   259,   260,     7,    17,    54,    55,    56,    57,   156,
     157,    60,    17,   177,    48,   273,     3,   275,    48,   277,
     278,   133,   134,   244,   214,    48,    19,    49,   286,    48,
      29,   280,   185,   291,   292,    28,   183,    19,   165,    17,
     193,    54,    55,    56,    57,    10,    28,    60,    31,    54,
      55,    56,    57,    37,    19,    60,    57,     0,    54,    55,
      56,     4,     5,     3,    60,     3,     9,   214,    11,    12,
      13,    14,    15,    16,    52,    53,    57,    20,    21,    22,
      61,    57,    58,    26,    27,    61,    28,     3,    54,    55,
      56,    57,     3,    36,    60,   222,     3,    39,    40,    41,
      42,    43,    44,    45,    55,    55,    57,    57,    50,    51,
      61,    61,   255,   256,   257,   262,    57,    39,    40,    41,
      42,    43,    44,    45,    55,    57,    57,   254,    50,    51,
      61,    57,    57,    58,    57,    61,    57,    57,    17,    31,
      31,     3,     3,    57,    57,    34,    17,    35,    38,    35,
       3,     3,    57,    57,    57,    30,    32,    57,    60,    57,
      57,    57,    19,    18,    18,     3,    39,    18,    17,    29,
      17,    19,    17,    19,     3,    57,    57,     9,     6,    18,
      57,    47,    19,    33,    58,    57,    19,    57,    28,    31,
      17,    35,    18,    57,     3,    31,    55,    18,    18,    17,
      10,    57,     3,     3,    18,    28,     3,     3,     3,     3,
      18,    17,    19,    18,    57,    18,    57,    19,     3,    18,
      18,   167,    57,    57,    28,    18,    57,    18,   294,    19,
      18,    18,    57,    57,    18,    57,    28,   124,    57,   178,
      57,    57,    57,    -1,   143,    -1,   141
=======
      86,   108,   194,   115,   103,   104,   217,   175,    51,   220,
      10,    18,   119,     3,    80,    81,    82,    10,    18,     7,
      27,   107,    17,   148,   149,    18,    28,    27,    22,    23,
      24,    18,    27,   244,   245,     6,    51,     8,    30,    49,
      27,    51,   149,   150,     3,    55,    16,    47,   259,    10,
     261,    45,   263,   264,    47,     3,     3,    18,    16,   171,
     228,     3,   169,   274,   130,   131,    27,   179,   279,   280,
     156,   196,   197,    16,   266,    10,    49,    48,    51,    49,
      50,    51,    55,    18,    54,    51,    47,    57,     3,    55,
     197,    49,    50,    51,    51,    36,    54,    49,    50,    57,
      51,    52,    54,    16,    55,    57,    49,    50,    51,    33,
       3,    54,    47,     0,    57,    51,    16,     4,     5,    55,
      51,   207,     9,    10,    11,    12,    13,    14,    15,    49,
      51,    51,    19,    20,    21,    55,    30,    51,    25,    26,
     247,   240,   241,   242,    27,    49,    50,    51,    35,     6,
      54,     8,    51,    57,    30,    38,    39,    40,    41,    42,
      43,    44,     3,    51,    37,    51,    34,   253,    38,    39,
      40,    41,    42,    43,    44,    38,    39,    40,    41,    42,
      43,    34,     3,     3,    51,    51,    51,    29,    31,    51,
      54,    51,    51,    51,    18,    17,     3,    28,    17,    17,
      16,    18,    38,    18,    16,    16,     3,    51,    18,     9,
       6,    17,    52,    16,    51,    16,    51,    46,    32,    52,
      18,    51,    16,    51,    17,    30,     3,    17,    17,    16,
       3,    17,    27,     3,     3,    17,    49,     3,     3,    18,
      18,    17,    51,    51,    27,    30,    17,    51,    16,    51,
      17,     3,    51,    17,    17,    17,    17,   158,   282,    51,
      51,    17,    17,    51,    17,   121,    17,    27,    27,   225,
      51,    51,   181,   154,    -1,    -1,    51,    51,    -1,    51,
      -1,    -1,   137
>>>>>>> support in select
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
<<<<<<< HEAD
       0,    65,     0,     4,     5,     9,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    26,    27,    36,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    85,    89,    90,    91,   111,     6,     8,    49,
       6,     8,    57,    58,    61,    94,    99,    57,     7,     3,
      29,    31,    57,     3,     3,     3,     3,     3,    37,    57,
      57,    57,    57,    57,    19,    28,   105,    17,    31,    31,
       3,     3,    57,    57,    34,    38,    17,    35,    35,     3,
       3,    57,    57,    61,    55,    57,    61,    57,    57,    30,
      32,   107,    57,    60,    57,    81,    84,    57,    57,    28,
     105,   105,   105,    18,    18,    18,   107,    10,    19,    92,
     106,    17,    17,    54,    55,    56,    57,    60,    88,   100,
     109,     3,    39,    29,    19,    80,    23,    24,    25,    46,
      83,    17,    17,    57,    61,    19,    95,    95,    95,     3,
      57,    57,   107,   107,    88,     9,    28,    39,    40,    41,
      42,    43,    44,    45,    50,    51,   110,   110,    57,    58,
     101,   102,   103,    33,   108,    88,     6,    81,    18,    17,
      52,    53,    57,    57,   105,   105,    58,    35,    93,   106,
      47,    96,    96,    19,    87,    57,    57,    88,   100,    57,
      88,    28,    17,    18,    31,    31,   109,   107,    57,    80,
       3,    55,    82,    18,    18,    17,   109,    92,    57,    97,
       3,     3,    88,    18,   110,   101,    28,    57,    55,    57,
      61,   110,    57,    57,   108,     3,     3,    18,     3,     3,
      55,    57,    61,   108,    11,    19,    28,    48,    98,    87,
      19,    86,    57,    88,   100,    18,    57,    18,    18,    28,
      18,    57,   107,    19,   104,    18,    18,    18,    98,    57,
      57,    98,    17,     3,    28,   101,    57,    28,    57,   107,
      95,    95,    95,    11,    28,    48,    98,    11,    48,    98,
      88,    57,    18,    18,    57,    98,    57,    98,    98,    98,
      87,    11,    48,    98,    18,    98,    98,    86
=======
       0,    59,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    25,    26,    35,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    78,    82,    83,    84,   102,     6,     8,    48,     6,
       8,    51,    52,    55,    85,    90,    51,     7,     3,    28,
      30,    51,     3,     3,     3,     3,     3,    36,    51,    51,
      51,    51,    51,    18,    27,    96,    16,    30,    30,     3,
       3,    51,    51,    33,    37,    16,    34,    34,     3,     3,
      51,    51,    55,    49,    51,    55,    51,    51,    29,    31,
      98,    51,    54,    51,    74,    77,    51,    51,    27,    96,
      96,    96,    17,    17,    17,    98,    18,    97,    16,    16,
      49,    50,    51,    54,    57,    81,    91,   100,     3,    38,
      28,    18,    73,    22,    23,    24,    45,    76,    16,    16,
      51,    55,    18,    86,    86,    86,     3,    51,    98,    81,
       9,    27,    38,    39,    40,    41,    42,    43,    44,   101,
     101,    52,    92,    94,    32,    99,    81,     6,    74,    17,
      16,    51,    51,    96,    96,    52,    97,    46,    87,    18,
      80,    51,    91,    51,    81,    91,    51,    81,    16,    17,
      30,   100,    98,    51,    73,     3,    49,    75,    17,    17,
      16,    51,    88,     3,    81,    17,    44,   101,    51,    93,
      95,    92,    27,    49,    51,    55,   101,    51,    99,     3,
       3,    17,     3,     3,    49,    51,    55,    10,    18,    27,
      47,    89,    80,    18,    79,    91,    51,    81,    91,    27,
      17,    30,    17,    51,    17,    17,    27,    17,    51,    98,
      17,    17,    17,    89,    51,    51,    89,    16,     3,    93,
      27,    92,    51,    51,    51,    27,    86,    86,    86,    10,
      27,    47,    89,    10,    47,    89,    81,    17,    51,    17,
      98,    17,    51,    89,    51,    89,    89,    89,    80,    10,
      47,    89,    17,    89,    89,    79
>>>>>>> support in select
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
<<<<<<< HEAD
       0,    64,    65,    65,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    76,    77,    78,    79,    80,    80,    81,    81,    81,
      81,    82,    83,    83,    83,    83,    84,    85,    86,    86,
      87,    87,    88,    88,    88,    88,    89,    90,    91,    91,
      91,    92,    92,    93,    93,    94,    94,    94,    95,    95,
      95,    95,    96,    96,    97,    97,    97,    97,    97,    97,
      98,    98,    98,    98,    98,    98,    98,    99,    99,    99,
      99,   100,   101,   101,   102,   102,   102,   102,   103,   103,
     104,   105,   105,   105,   105,   106,   106,   107,   107,   108,
     108,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   111
=======
       0,    58,    59,    59,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    70,    71,    72,    73,    73,    74,    74,    75,    76,
      76,    76,    76,    77,    78,    79,    79,    80,    80,    81,
      81,    81,    81,    82,    83,    84,    84,    85,    85,    85,
      86,    86,    86,    86,    87,    87,    88,    88,    88,    88,
      88,    88,    89,    89,    89,    89,    89,    89,    89,    90,
      90,    90,    90,    91,    92,    93,    94,    94,    94,    94,
      95,    95,    96,    96,    96,    96,    97,    97,    98,    98,
      99,    99,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   101,   101,   101,   101,   101,
     101,   102
>>>>>>> support in select
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
<<<<<<< HEAD
       9,     9,     4,     7,     2,     0,     3,     5,     3,     3,
       2,     1,     1,     1,     1,     1,     1,    10,     0,     6,
       0,     3,     1,     1,     1,     1,     5,     8,     6,     8,
       8,     0,     4,     0,     3,     5,     5,     5,     0,     6,
       6,     6,     0,     2,     2,     4,     3,     3,     5,     5,
       0,     3,     5,     4,     4,     6,     6,     1,     2,     4,
       4,     2,     4,     5,     4,     6,     4,     4,     1,     3,
       2,     0,     3,     5,     5,     0,     3,     0,     3,     0,
       3,     3,     5,     5,     7,     7,     3,     3,     3,     5,
       5,     7,     1,     1,     1,     1,     1,     1,     1,     1,
=======
       9,     9,     4,     8,     0,     3,     5,     2,     1,     1,
       1,     1,     1,     1,    10,     0,     6,     0,     3,     1,
       1,     1,     1,     5,     8,     6,     8,     5,     5,     5,
       0,     6,     6,     6,     0,     2,     2,     4,     3,     3,
       5,     5,     0,     3,     5,     4,     4,     6,     6,     1,
       2,     4,     4,     2,     4,     4,     4,     6,     4,     4,
       1,     3,     0,     3,     5,     5,     0,     3,     0,     3,
       0,     3,     3,     5,     7,     5,     5,     7,     7,     3,
       3,     3,     5,     5,     7,     1,     1,     1,     1,     1,
>>>>>>> support in select
       1,     8
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
      yyerror (scanner, YY_("syntax error: cannot back up")); \
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
                  Type, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (scanner);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, scanner);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, void *scanner)
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
                                              , scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

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
      yychar = yylex (&yylval, scanner);
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
        case 21:
<<<<<<< HEAD
#line 179 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1552 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 184 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1560 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 189 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1568 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 195 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1576 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 201 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1584 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 207 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1592 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 213 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 173 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1537 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 178 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1545 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 183 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1553 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 189 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1561 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 195 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1569 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 201 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1577 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 207 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
<<<<<<< HEAD
#line 1601 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 219 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1609 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 225 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1586 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 213 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1594 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 219 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
<<<<<<< HEAD
#line 1618 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 233 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1603 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 227 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string), 0);
		}
<<<<<<< HEAD
#line 1627 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 238 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1612 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 232 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string), 1);
		}
<<<<<<< HEAD
#line 1636 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 246 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1621 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 240 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
<<<<<<< HEAD
#line 1645 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 253 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1630 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 247 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
<<<<<<< HEAD
#line 1657 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 262 "yacc_sql.y" /* yacc.c:1646  */
    {
		AttrInfo attribute;
		attr_info_init(&attribute, "null_field", BITMAPS, 4);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		CONTEXT->value_length++;
	}
#line 1668 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 271 "yacc_sql.y" /* yacc.c:1646  */
    {    }
#line 1674 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 276 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1642 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 257 "yacc_sql.y" /* yacc.c:1646  */
    {    }
#line 1648 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 262 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
#line 1689 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 287 "yacc_sql.y" /* yacc.c:1646  */
    {
			AttrInfo attribute;
			attr_info_init_with_null(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1700 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 295 "yacc_sql.y" /* yacc.c:1646  */
    {
			AttrInfo attribute;
			attr_info_init_with_null(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1711 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 303 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1663 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 273 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
#line 1726 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 315 "yacc_sql.y" /* yacc.c:1646  */
    {(yyval.number) = (yyvsp[0].number);}
#line 1732 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 318 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=INTS; }
#line 1738 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 319 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=CHARS; }
#line 1744 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 320 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=FLOATS; }
#line 1750 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 321 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=DATES; }
#line 1756 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 325 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1678 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 285 "yacc_sql.y" /* yacc.c:1646  */
    {(yyval.number) = (yyvsp[0].number);}
#line 1684 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 288 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=INTS; }
#line 1690 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 289 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=CHARS; }
#line 1696 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 290 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=FLOATS; }
#line 1702 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 291 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=DATES; }
#line 1708 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 295 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
<<<<<<< HEAD
#line 1765 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 333 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1717 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 304 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string), CONTEXT->values_list,CONTEXT->values_length_list, CONTEXT->values_size);

      //临时变量清零
      CONTEXT->value_length=0;
      CONTEXT->values_size=0;
    }
<<<<<<< HEAD
#line 1785 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 351 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1737 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 322 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
        //printf("other values\n");

    }
<<<<<<< HEAD
#line 1794 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 358 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1746 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 329 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
        //printf("value list finished \n");
        for(int i=0;i<CONTEXT->value_length;++i) {
            CONTEXT->values_list[CONTEXT->values_size][i]=CONTEXT->values[i];
        }
        CONTEXT->values_length_list[CONTEXT->values_size]=CONTEXT->value_length;
        CONTEXT->value_length=0;
        CONTEXT->values_size+=1;
    }
<<<<<<< HEAD
#line 1808 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 367 "yacc_sql.y" /* yacc.c:1646  */
    { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1816 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 372 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1760 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 338 "yacc_sql.y" /* yacc.c:1646  */
    { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1768 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 343 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
    //printf("value\n");
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
<<<<<<< HEAD
#line 1825 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 376 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1777 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 347 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
    //printf("value\n");
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
<<<<<<< HEAD
#line 1834 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 380 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1786 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 352 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		}
<<<<<<< HEAD
#line 1842 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 383 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1796 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 357 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
    //printf("value\n");
		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
<<<<<<< HEAD
#line 1852 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 392 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1806 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 366 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
<<<<<<< HEAD
#line 1864 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 402 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1818 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 376 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
<<<<<<< HEAD
#line 1876 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 412 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1830 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 386 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
		//聚合运算的语法解析
		CONTEXT->ssql->flag = SCF_AGGREGATE;
		aggregates_init(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].string),CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->condition_length = 0;
	}
<<<<<<< HEAD
#line 1887 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 419 "yacc_sql.y" /* yacc.c:1646  */
    {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
#line 1907 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 436 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1841 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 393 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
			//printf("Sub select length is %d\n",CONTEXT->sub_selects_length);
			}
<<<<<<< HEAD
#line 1928 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 455 "yacc_sql.y" /* yacc.c:1646  */
    {
        selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
    }
#line 1936 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 461 "yacc_sql.y" /* yacc.c:1646  */
    {

    }
#line 1944 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 467 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].string),(yyvsp[-4].string));
	}
#line 1952 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 470 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,"*",(yyvsp[-4].string));
	}
#line 1960 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 473 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field_itoa(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].number),(yyvsp[-4].string));
	}
#line 1968 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 479 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].string),(yyvsp[-4].string));
	}
#line 1976 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 482 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,"*",(yyvsp[-4].string));
	}
#line 1984 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 485 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field_itoa(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].number),(yyvsp[-4].string));
	}
#line 1992 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 490 "yacc_sql.y" /* yacc.c:1646  */
    {
    }
#line 1999 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 494 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1862 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 411 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].string),(yyvsp[-4].string));
	}
#line 1870 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 414 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,"*",(yyvsp[-4].string));
	}
#line 1878 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 417 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field_itoa(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].number),(yyvsp[-4].string));
	}
#line 1886 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 423 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].string),(yyvsp[-4].string));
	}
#line 1894 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 426 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,"*",(yyvsp[-4].string));
	}
#line 1902 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 429 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field_itoa(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].number),(yyvsp[-4].string));
	}
#line 1910 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 434 "yacc_sql.y" /* yacc.c:1646  */
    {
    }
#line 1917 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 438 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-1].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
<<<<<<< HEAD
#line 2009 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 499 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1927 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 443 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
<<<<<<< HEAD
#line 2019 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 504 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1937 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 448 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-2].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
<<<<<<< HEAD
#line 2029 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 509 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1947 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 453 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-2].string), "desc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
<<<<<<< HEAD
#line 2039 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 514 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1957 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 458 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
<<<<<<< HEAD
#line 2049 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 519 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1967 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 463 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), "desc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
<<<<<<< HEAD
#line 2059 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 527 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1977 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 471 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-1].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
<<<<<<< HEAD
#line 2069 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 532 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1987 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 476 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
<<<<<<< HEAD
#line 2079 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 537 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 1997 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 481 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-2].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
<<<<<<< HEAD
#line 2089 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 542 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2007 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 486 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-2].string), "desc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
<<<<<<< HEAD
#line 2099 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 547 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2017 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 491 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
<<<<<<< HEAD
#line 2109 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 552 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2027 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 496 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), "desc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
<<<<<<< HEAD
#line 2119 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 560 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2037 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 504 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
<<<<<<< HEAD
#line 2129 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 565 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2047 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 509 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
<<<<<<< HEAD
#line 2139 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 570 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2057 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 514 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
<<<<<<< HEAD
#line 2149 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 575 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2067 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 519 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
	        RelAttr attr;
	        relation_attr_init(&attr, (yyvsp[-3].string), "*");
	        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	    }
<<<<<<< HEAD
#line 2159 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 583 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2077 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 527 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
		//将condition的值存入，入栈
		CONTEXT->sub_selects_length++;
		CONTEXT->sub_condition_length[CONTEXT->sub_selects_length] = CONTEXT->condition_length;
	}
<<<<<<< HEAD
#line 2169 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 592 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2087 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 536 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
		aggregates_init(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,(yyvsp[-1].string),
					CONTEXT->conditions + CONTEXT->sub_condition_length[CONTEXT->sub_selects_length], 
					CONTEXT->condition_length - CONTEXT->sub_condition_length[CONTEXT->sub_selects_length]);
		//printf("Condition start at %d\n",CONTEXT->sub_condition_length[CONTEXT->sub_selects_length]);
	}
<<<<<<< HEAD
#line 2180 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 599 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2098 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 545 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {	
			//selects_init(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection);
			selects_append_relation(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection, (yyvsp[-1].string));
			selects_append_conditions(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection, 
						CONTEXT->conditions + CONTEXT->sub_condition_length[CONTEXT->sub_selects_length],
						CONTEXT->condition_length - CONTEXT->sub_condition_length[CONTEXT->sub_selects_length]);
		}
<<<<<<< HEAD
#line 2191 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 608 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,(yyvsp[-1].string),(yyvsp[-3].string));
	}
#line 2199 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 611 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,(yyvsp[-1].string),(yyvsp[-5].string));
	}
#line 2207 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 614 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,"*",(yyvsp[-3].string));
	}
#line 2215 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 617 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field_itoa(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,(yyvsp[-1].number),(yyvsp[-3].string));
	}
#line 2223 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 624 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2110 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 555 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,(yyvsp[-1].string),(yyvsp[-3].string));
	}
#line 2118 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 558 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,(yyvsp[-1].string),(yyvsp[-5].string));
	}
#line 2126 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 561 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,"*",(yyvsp[-3].string));
	}
#line 2134 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 564 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field_itoa(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,(yyvsp[-1].number),(yyvsp[-3].string));
	}
#line 2142 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 571 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection, &attr);
		}
<<<<<<< HEAD
#line 2233 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 629 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2152 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 576 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection, &attr);
		}
<<<<<<< HEAD
#line 2243 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 637 "yacc_sql.y" /* yacc.c:1646  */
    {	
				selects_append_relation(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection, (yyvsp[0].string));
		  }
#line 2251 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 643 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2162 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 585 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
<<<<<<< HEAD
#line 2263 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 650 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2174 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 592 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
<<<<<<< HEAD
#line 2275 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 657 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2186 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 599 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
  	        RelAttr attr;
  	        relation_attr_init(&attr, (yyvsp[-3].string), "*");
  	        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
  	}
<<<<<<< HEAD
#line 2285 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 666 "yacc_sql.y" /* yacc.c:1646  */
    {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2293 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 672 "yacc_sql.y" /* yacc.c:1646  */
    {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2301 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 678 "yacc_sql.y" /* yacc.c:1646  */
    {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2309 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 684 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2196 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 608 "yacc_sql.y" /* yacc.c:1646  */
    {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2204 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 614 "yacc_sql.y" /* yacc.c:1646  */
    {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2212 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 620 "yacc_sql.y" /* yacc.c:1646  */
    {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2220 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 626 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length], 1, &left_attr, NULL, 0, NULL, right_value,NULL,NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
<<<<<<< HEAD
#line 2334 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 705 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2245 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 646 "yacc_sql.y" /* yacc.c:1646  */
    {
		//in subselect
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-4].string));
		Selects* in_select = &CONTEXT->sub_selects[CONTEXT->sub_selects_length];
		Condition condition;
		condition_init(&condition, IN, 1, &left_attr, NULL, 0, NULL, NULL,NULL,NULL);
		condition_set_inselect(&condition,in_select);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;


	}
#line 2264 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 660 "yacc_sql.y" /* yacc.c:1646  */
    {
		//in subselect
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
		Selects* in_select = &CONTEXT->sub_selects[CONTEXT->sub_selects_length];
		Condition condition;
		condition_init(&condition, IN, 1, &left_attr, NULL, 0, NULL, NULL,NULL,NULL);
		condition_set_inselect(&condition,in_select);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2281 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 673 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
		//出栈
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-4].string));
		Aggregates* right_agg_value = &CONTEXT->sub_selects[CONTEXT->sub_selects_length];
		Condition condition;
		condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length], 1, &left_attr, NULL, 0, NULL, NULL,NULL,right_agg_value);
		//TODO for memory leakage
		//destroy会把子查询的子查询destroy了，需要实现一个不destroy子查询的函数
		//aggregates_destroy(right_agg_value);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
<<<<<<< HEAD
#line 2353 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 720 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2300 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 688 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));
		Aggregates* left_agg_value = &CONTEXT->sub_selects[CONTEXT->sub_selects_length];
		Condition condition;
		condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length],0,NULL,NULL,1,&right_attr,NULL,left_agg_value,NULL);
		//aggregates_destroy(left_agg_value);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
<<<<<<< HEAD
#line 2369 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 732 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2316 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 700 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
		Aggregates* right_agg_value = &CONTEXT->sub_selects[CONTEXT->sub_selects_length];
		Condition condition;
		condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length], 1, &left_attr, NULL, 0, NULL, NULL,NULL,right_agg_value);
		//aggregates_destroy(right_agg_value);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
<<<<<<< HEAD
#line 2385 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 744 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2332 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 712 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
		Aggregates* left_agg_value = &CONTEXT->sub_selects[CONTEXT->sub_selects_length];
		Condition condition;
		condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length],0,NULL,NULL,1,&right_attr,NULL,left_agg_value,NULL);
		//aggregates_destroy(left_agg_value);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
<<<<<<< HEAD
#line 2401 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 757 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2348 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 725 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length], 0, NULL, left_value, 0, NULL, right_value,NULL,NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
<<<<<<< HEAD
#line 2425 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 777 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2372 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 745 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length], 1, &left_attr, NULL, 1, &right_attr, NULL,NULL,NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
<<<<<<< HEAD
#line 2449 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 797 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2396 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 765 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length], 0, NULL, left_value, 1, &right_attr, NULL,NULL,NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
<<<<<<< HEAD
#line 2475 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 819 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2422 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 787 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length], 1, &left_attr, NULL, 0, NULL, right_value,NULL,NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
<<<<<<< HEAD
#line 2500 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 840 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2447 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 808 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length], 0, NULL, left_value, 1, &right_attr, NULL,NULL,NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
<<<<<<< HEAD
#line 2525 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 861 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2472 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 829 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length], 1, &left_attr, NULL, 1, &right_attr, NULL,NULL,NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
<<<<<<< HEAD
#line 2548 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 882 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = EQUAL_TO; }
#line 2554 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 883 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = LESS_THAN; }
#line 2560 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 884 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = GREAT_THAN; }
#line 2566 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 885 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = LESS_EQUAL; }
#line 2572 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 886 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = GREAT_EQUAL; }
#line 2578 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 887 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = NOT_EQUAL; }
#line 2584 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 888 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = IS_NULL; }
#line 2590 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 889 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = IS_NOT_NULL; }
#line 2596 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 890 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = IN}
#line 2602 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 895 "yacc_sql.y" /* yacc.c:1646  */
=======
#line 2495 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 850 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = EQUAL_TO; }
#line 2501 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 851 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = LESS_THAN; }
#line 2507 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 852 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = GREAT_THAN; }
#line 2513 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 853 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = LESS_EQUAL; }
#line 2519 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 854 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = GREAT_EQUAL; }
#line 2525 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 855 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = NOT_EQUAL; }
#line 2531 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 860 "yacc_sql.y" /* yacc.c:1646  */
>>>>>>> support in select
    {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
<<<<<<< HEAD
#line 2611 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;


#line 2615 "yacc_sql.tab.c" /* yacc.c:1646  */
=======
#line 2540 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;


#line 2544 "yacc_sql.tab.c" /* yacc.c:1646  */
>>>>>>> support in select
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
      yyerror (scanner, YY_("syntax error"));
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
        yyerror (scanner, yymsgp);
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
                      yytoken, &yylval, scanner);
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
                  yystos[yystate], yyvsp, scanner);
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
  yyerror (scanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, scanner);
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
<<<<<<< HEAD
#line 900 "yacc_sql.y" /* yacc.c:1906  */
=======
#line 865 "yacc_sql.y" /* yacc.c:1906  */
>>>>>>> support in select

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
