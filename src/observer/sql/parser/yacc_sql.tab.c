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
    BELONG = 300,
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
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 125 "yacc_sql.y" /* yacc.c:355  */

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
  char *position;

#line 245 "yacc_sql.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 261 "yacc_sql.tab.c" /* yacc.c:358  */

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
#define YYLAST   298

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  131
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  302

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   318

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
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   153,   153,   155,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   179,   184,   189,   195,   201,   207,   213,   219,   225,
     232,   237,   245,   252,   262,   269,   271,   275,   286,   294,
     302,   315,   318,   319,   320,   321,   324,   332,   349,   351,
     358,   367,   372,   376,   380,   383,   391,   401,   411,   419,
     435,   454,   455,   460,   461,   467,   470,   473,   477,   479,
     482,   485,   489,   490,   494,   499,   504,   509,   514,   519,
     526,   527,   532,   537,   542,   547,   552,   560,   565,   570,
     575,   582,   591,   600,   611,   614,   617,   620,   627,   632,
     639,   641,   648,   655,   662,   664,   668,   670,   674,   676,
     681,   702,   716,   728,   743,   755,   767,   780,   800,   820,
     842,   863,   884,   906,   907,   908,   909,   910,   911,   912,
     913,   917
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "TABLE",
  "TABLES", "INDEX", "SELECT", "INNER_JOIN", "DESC", "SHOW", "SYNC",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "HELP",
  "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON",
  "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE", "GE", "NE", "BELONG",
  "DATE_T", "ORDER_BY", "ASC", "UNIQUEINDEX", "ISNOTNULL", "ISNULL",
  "NULLABLE", "NOTNULL", "NULL_T", "NUMBER", "FLOAT", "ID", "AGGREGATE",
  "PATH", "SSS", "STAR", "STRING_V", "DATE", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "desc_table", "create_index", "drop_index",
  "create_table", "create_table_token", "attr_def_list", "attr_def",
  "number", "type", "ID_get", "insert", "other_values", "value_list",
  "value", "delete", "update", "select", "inner_join", "on_list",
  "agg_field", "agg_field_list", "order", "order_attr", "order_attr_list",
  "select_attr", "subselect_start", "subselect", "sub_in_select",
  "sub_agg_field", "sub_select_attr", "attr_list", "rel_list", "where",
  "condition_list", "condition", "comOp", "load_data", YY_NULLPTR
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318
};
# endif

#define YYPACT_NINF -225

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-225)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -225,   104,  -225,     8,   126,    53,   -37,    19,    24,     3,
       2,   -18,    44,    55,    56,    62,    95,    70,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,    64,  -225,  -225,  -225,  -225,  -225,  -225,    88,    91,
      92,    93,    68,   127,  -225,    81,   120,   149,   176,  -225,
     123,   124,   157,  -225,  -225,  -225,  -225,  -225,   154,   177,
     158,   160,   195,   196,   143,   -17,  -225,    86,   144,   145,
    -225,  -225,   173,   172,   148,   147,   151,   152,   153,  -225,
    -225,    74,   187,   187,   193,   194,   197,   172,    87,   199,
       7,   210,   175,   188,  -225,   200,    76,   201,   203,    16,
    -225,  -225,  -225,   202,   202,   202,   219,   166,   167,   172,
     172,    73,   216,  -225,  -225,  -225,   118,  -225,   146,   168,
     198,  -225,    73,   221,   151,   211,  -225,  -225,  -225,  -225,
     -10,   171,   178,   187,   187,   174,  -225,  -225,  -225,  -225,
     204,   214,   183,   183,   215,  -225,   179,  -225,  -225,  -225,
    -225,  -225,  -225,   220,  -225,  -225,    28,    82,   223,   224,
     207,     7,  -225,   172,   184,   200,   240,   189,  -225,  -225,
     227,   228,  -225,  -225,   230,     7,   238,  -225,   192,   247,
     248,    73,   234,   133,   205,  -225,  -225,   168,   225,  -225,
     109,   146,   206,   198,   251,   252,  -225,  -225,  -225,   239,
     253,   255,   110,   198,  -225,     6,  -225,  -225,  -225,   215,
     241,   220,    35,   231,   243,   233,   249,   208,   250,    13,
     254,   209,   172,  -225,  -225,  -225,  -225,  -225,  -225,   256,
     257,   258,  -225,   259,   212,   213,   259,  -225,  -225,   260,
     268,   205,   245,  -225,   168,   222,  -225,   226,  -225,  -225,
    -225,  -225,   229,  -225,   261,  -225,   202,   202,   202,  -225,
      75,     0,  -225,    73,  -225,   262,   235,   263,  -225,   172,
     264,   236,  -225,  -225,  -225,   259,   237,   259,  -225,   259,
     259,  -225,   215,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
      27,  -225,  -225,  -225,   266,   259,   259,  -225,   241,  -225,
    -225,  -225
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     0,     5,     7,     6,     4,    18,    34,     0,     0,
       0,     0,   100,     0,    87,     0,     0,     0,     0,    23,
       0,     0,     0,    24,    25,    26,    22,    21,     0,     0,
       0,     0,     0,     0,     0,     0,    88,     0,     0,     0,
      29,    28,     0,   106,     0,     0,     0,     0,     0,    27,
      32,   100,   100,   100,     0,     0,     0,   106,    61,     0,
       0,     0,     0,     0,    46,    35,     0,     0,     0,     0,
     101,    89,    90,    68,    68,    68,     0,     0,     0,   106,
     106,     0,     0,    54,    52,    53,     0,    55,     0,     0,
     108,    56,     0,     0,     0,     0,    42,    43,    44,    45,
      40,     0,     0,   100,   100,     0,    67,    65,    66,    58,
      63,   104,    72,    72,    50,    91,     0,   123,   124,   125,
     126,   127,   128,     0,   130,   129,     0,     0,     0,     0,
       0,     0,   107,   106,     0,    35,     0,     0,    38,    39,
       0,     0,   102,   103,     0,     0,    61,   105,     0,     0,
       0,     0,     0,     0,     0,   118,   110,     0,   119,   117,
       0,     0,     0,   108,     0,     0,    36,    33,    41,     0,
       0,     0,     0,   108,    62,    80,    73,    59,    60,    50,
      48,     0,     0,    98,     0,     0,     0,     0,     0,     0,
       0,     0,   106,   109,    57,   131,    37,    30,    31,     0,
       0,     0,    64,    80,     0,     0,    80,    74,    51,     0,
       0,     0,     0,   120,     0,     0,   111,     0,   113,   121,
      97,    94,     0,    96,   114,    92,    68,    68,    68,    77,
      80,    80,    76,     0,    47,     0,     0,     0,    99,   106,
       0,     0,    71,    69,    70,    80,     0,    80,    81,    80,
      80,    75,    50,   112,   122,   115,    93,    95,   116,    84,
      80,    83,    79,    78,     0,    80,    80,    82,    48,    86,
      85,    49
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,  -225,
    -225,  -225,  -225,  -225,  -225,  -225,   122,   161,  -225,  -225,
    -225,  -225,    -8,  -203,  -107,  -225,  -225,  -225,   112,  -225,
    -225,  -103,   155,  -225,  -224,  -225,  -143,  -184,    50,  -225,
    -225,   -53,   156,   -87,  -185,  -140,  -113,  -225
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,   125,    95,   199,   130,
      96,    32,   240,   182,   118,    33,    34,    35,   109,   176,
      45,   136,   179,   206,   237,    46,   119,   159,   214,   160,
     215,    66,   110,    91,   162,   120,   156,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     106,   137,   138,   216,   144,   157,   238,   167,   223,   259,
     184,   279,   262,   187,    37,   163,    38,   233,   232,   234,
      47,   193,   142,   143,   112,   234,    48,    49,   100,   101,
     102,   251,    50,    51,   235,   203,   278,   281,   295,    52,
      82,   252,   168,   169,    83,   112,   234,    53,   280,   186,
     189,   289,   112,   291,   236,   292,   293,    39,    54,    55,
     267,   113,   114,   115,   116,    56,   297,   117,   241,   244,
     212,   299,   300,   133,   209,   296,   194,   134,   221,   294,
     172,   173,   113,   114,   115,   185,   275,    64,   117,   113,
     114,   115,   242,    64,   234,   117,    65,   107,    57,   126,
     127,   128,    99,   276,     2,   243,   108,    58,     3,     4,
      42,    43,    68,     5,    44,     6,     7,     8,     9,    10,
      11,    59,   129,   277,    12,    13,    14,   113,   114,   115,
      15,    16,    40,   117,    41,   255,   113,   114,   115,   188,
      17,    84,   117,    85,    67,    60,   146,    86,    61,    62,
      63,    69,    70,   272,   273,   274,   282,   147,   148,   149,
     150,   151,   152,   153,   218,   229,   219,   230,   154,   155,
     220,   231,   147,   148,   149,   150,   151,   152,   211,    71,
      72,    73,   286,   154,   155,   147,   148,   149,   150,   151,
     152,    74,    75,    77,    76,    78,   154,   155,    79,    80,
      81,    87,    88,    89,    90,    92,    64,    93,    94,    97,
      98,   103,   104,   121,   122,   105,   111,   123,   131,   124,
     132,   135,   139,   140,   141,   145,   158,   164,   170,   166,
     178,   161,   174,   108,   181,   171,   183,   112,   192,   175,
     190,   195,   191,   197,   198,   200,   201,   202,   107,   205,
     207,   208,   210,   217,   224,   225,   227,   226,   228,   245,
     239,   246,   213,   222,   247,   249,   254,   248,   250,   260,
     261,   264,   253,   266,   256,   257,   258,   263,   234,   268,
     283,   285,   287,   269,   298,   165,   270,   196,   204,   271,
     301,   265,   284,   288,   290,     0,     0,   177,   180
};

static const yytype_int16 yycheck[] =
{
      87,   104,   105,   187,   111,   118,   209,    17,   193,   233,
     153,    11,   236,   156,     6,   122,     8,    11,   203,    19,
      57,   161,   109,   110,    17,    19,     7,     3,    81,    82,
      83,    18,    29,    31,    28,   175,   260,   261,    11,    57,
      57,    28,    52,    53,    61,    17,    19,     3,    48,   156,
     157,   275,    17,   277,    48,   279,   280,    49,     3,     3,
     244,    54,    55,    56,    57,     3,   290,    60,   211,   212,
     183,   295,   296,    57,   181,    48,   163,    61,   191,   282,
     133,   134,    54,    55,    56,    57,    11,    19,    60,    54,
      55,    56,    57,    19,    19,    60,    28,    10,     3,    23,
      24,    25,    28,    28,     0,   212,    19,    37,     4,     5,
      57,    58,    31,     9,    61,    11,    12,    13,    14,    15,
      16,    57,    46,    48,    20,    21,    22,    54,    55,    56,
      26,    27,     6,    60,     8,   222,    54,    55,    56,    57,
      36,    55,    60,    57,    17,    57,    28,    61,    57,    57,
      57,    31,     3,   256,   257,   258,   263,    39,    40,    41,
      42,    43,    44,    45,    55,    55,    57,    57,    50,    51,
      61,    61,    39,    40,    41,    42,    43,    44,    45,     3,
      57,    57,   269,    50,    51,    39,    40,    41,    42,    43,
      44,    34,    38,    35,    17,    35,    50,    51,     3,     3,
      57,    57,    57,    30,    32,    57,    19,    60,    57,    57,
      57,    18,    18,     3,    39,    18,    17,    29,    17,    19,
      17,    19,     3,    57,    57,     9,    58,     6,    57,    18,
      47,    33,    58,    19,    19,    57,    57,    17,    31,    35,
      17,    57,    18,     3,    55,    18,    18,    17,    10,    57,
       3,     3,    18,    28,     3,     3,     3,    18,     3,    28,
      19,    18,    57,    57,    31,    57,    57,    18,    18,    57,
      57,     3,    18,    28,    18,    18,    18,    17,    19,    57,
      18,    18,    18,    57,    18,   124,    57,   165,   176,    28,
     298,   241,    57,    57,    57,    -1,    -1,   141,   143
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
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
      42,    43,    44,    45,    50,    51,   110,   110,    58,   101,
     103,    33,   108,    88,     6,    81,    18,    17,    52,    53,
      57,    57,   105,   105,    58,    35,    93,   106,    47,    96,
      96,    19,    87,    57,   100,    57,    88,   100,    57,    88,
      17,    18,    31,   109,   107,    57,    80,     3,    55,    82,
      18,    18,    17,   109,    92,    57,    97,     3,     3,    88,
      18,    45,   110,    57,   102,   104,   101,    28,    55,    57,
      61,   110,    57,   108,     3,     3,    18,     3,     3,    55,
      57,    61,   108,    11,    19,    28,    48,    98,    87,    19,
      86,   100,    57,    88,   100,    28,    18,    31,    18,    57,
      18,    18,    28,    18,    57,   107,    18,    18,    18,    98,
      57,    57,    98,    17,     3,   102,    28,   101,    57,    57,
      57,    28,    95,    95,    95,    11,    28,    48,    98,    11,
      48,    98,    88,    18,    57,    18,   107,    18,    57,    98,
      57,    98,    98,    98,    87,    11,    48,    98,    18,    98,
      98,    86
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    64,    65,    65,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    76,    77,    78,    79,    80,    80,    81,    81,    81,
      81,    82,    83,    83,    83,    83,    84,    85,    86,    86,
      87,    87,    88,    88,    88,    88,    89,    90,    91,    91,
      91,    92,    92,    93,    93,    94,    94,    94,    95,    95,
      95,    95,    96,    96,    97,    97,    97,    97,    97,    97,
      98,    98,    98,    98,    98,    98,    98,    99,    99,    99,
      99,   100,   101,   102,   103,   103,   103,   103,   104,   104,
     105,   105,   105,   105,   106,   106,   107,   107,   108,   108,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   110,   110,   110,   110,   110,   110,   110,
     110,   111
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
       9,     9,     4,     7,     2,     0,     3,     5,     3,     3,
       2,     1,     1,     1,     1,     1,     1,    10,     0,     6,
       0,     3,     1,     1,     1,     1,     5,     8,     6,     8,
       8,     0,     4,     0,     3,     5,     5,     5,     0,     6,
       6,     6,     0,     2,     2,     4,     3,     3,     5,     5,
       0,     3,     5,     4,     4,     6,     6,     1,     2,     4,
       4,     2,     4,     4,     4,     6,     4,     4,     1,     3,
       0,     3,     5,     5,     0,     3,     0,     3,     0,     3,
       3,     5,     7,     5,     5,     7,     7,     3,     3,     3,
       5,     5,     7,     1,     1,     1,     1,     1,     1,     1,
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
#line 179 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1557 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 184 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1565 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 189 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1573 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 195 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1581 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 201 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1589 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 207 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1597 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 213 "yacc_sql.y" /* yacc.c:1646  */
    {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1606 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 219 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1614 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 225 "yacc_sql.y" /* yacc.c:1646  */
    {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1623 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 233 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string), 0);
		}
#line 1632 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 238 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string), 1);
		}
#line 1641 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 246 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1650 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 253 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1662 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 262 "yacc_sql.y" /* yacc.c:1646  */
    {
		AttrInfo attribute;
		attr_info_init(&attribute, "null_field", BITMAPS, 4);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		CONTEXT->value_length++;
	}
#line 1673 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 271 "yacc_sql.y" /* yacc.c:1646  */
    {    }
#line 1679 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 276 "yacc_sql.y" /* yacc.c:1646  */
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
#line 1694 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 287 "yacc_sql.y" /* yacc.c:1646  */
    {
			AttrInfo attribute;
			attr_info_init_with_null(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1705 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 295 "yacc_sql.y" /* yacc.c:1646  */
    {
			AttrInfo attribute;
			attr_info_init_with_null(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1716 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 303 "yacc_sql.y" /* yacc.c:1646  */
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
#line 1731 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 315 "yacc_sql.y" /* yacc.c:1646  */
    {(yyval.number) = (yyvsp[0].number);}
#line 1737 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 318 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=INTS; }
#line 1743 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 319 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=CHARS; }
#line 1749 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 320 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=FLOATS; }
#line 1755 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 321 "yacc_sql.y" /* yacc.c:1646  */
    { (yyval.number)=DATES; }
#line 1761 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 325 "yacc_sql.y" /* yacc.c:1646  */
    {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1770 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 333 "yacc_sql.y" /* yacc.c:1646  */
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
#line 1790 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 351 "yacc_sql.y" /* yacc.c:1646  */
    {
        //printf("other values\n");

    }
#line 1799 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 358 "yacc_sql.y" /* yacc.c:1646  */
    {
        //printf("value list finished \n");
        for(int i=0;i<CONTEXT->value_length;++i) {
            CONTEXT->values_list[CONTEXT->values_size][i]=CONTEXT->values[i];
        }
        CONTEXT->values_length_list[CONTEXT->values_size]=CONTEXT->value_length;
        CONTEXT->value_length=0;
        CONTEXT->values_size+=1;
    }
#line 1813 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 367 "yacc_sql.y" /* yacc.c:1646  */
    { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1821 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 372 "yacc_sql.y" /* yacc.c:1646  */
    {
    //printf("value\n");
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1830 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 376 "yacc_sql.y" /* yacc.c:1646  */
    {
    //printf("value\n");
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1839 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 380 "yacc_sql.y" /* yacc.c:1646  */
    {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		}
#line 1847 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 383 "yacc_sql.y" /* yacc.c:1646  */
    {
    //printf("value\n");
		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1857 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 392 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1869 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 402 "yacc_sql.y" /* yacc.c:1646  */
    {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1881 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 412 "yacc_sql.y" /* yacc.c:1646  */
    {
		//聚合运算的语法解析
		CONTEXT->ssql->flag = SCF_AGGREGATE;
		aggregates_init(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].string),CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->condition_length = 0;
	}
#line 1892 "yacc_sql.tab.c" /* yacc.c:1646  */
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
#line 1912 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 436 "yacc_sql.y" /* yacc.c:1646  */
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
#line 1933 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 455 "yacc_sql.y" /* yacc.c:1646  */
    {
        selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
    }
#line 1941 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 461 "yacc_sql.y" /* yacc.c:1646  */
    {

    }
#line 1949 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 467 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].string),(yyvsp[-4].string));
	}
#line 1957 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 470 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,"*",(yyvsp[-4].string));
	}
#line 1965 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 473 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field_itoa(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].number),(yyvsp[-4].string));
	}
#line 1973 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 479 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].string),(yyvsp[-4].string));
	}
#line 1981 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 482 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,"*",(yyvsp[-4].string));
	}
#line 1989 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 485 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field_itoa(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].number),(yyvsp[-4].string));
	}
#line 1997 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 490 "yacc_sql.y" /* yacc.c:1646  */
    {
    }
#line 2004 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 494 "yacc_sql.y" /* yacc.c:1646  */
    {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-1].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2014 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 499 "yacc_sql.y" /* yacc.c:1646  */
    {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2024 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 504 "yacc_sql.y" /* yacc.c:1646  */
    {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-2].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2034 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 509 "yacc_sql.y" /* yacc.c:1646  */
    {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-2].string), "desc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2044 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 514 "yacc_sql.y" /* yacc.c:1646  */
    {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2054 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 519 "yacc_sql.y" /* yacc.c:1646  */
    {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), "desc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2064 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 527 "yacc_sql.y" /* yacc.c:1646  */
    {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-1].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2074 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 532 "yacc_sql.y" /* yacc.c:1646  */
    {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2084 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 537 "yacc_sql.y" /* yacc.c:1646  */
    {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-2].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2094 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 542 "yacc_sql.y" /* yacc.c:1646  */
    {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-2].string), "desc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2104 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 547 "yacc_sql.y" /* yacc.c:1646  */
    {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2114 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 552 "yacc_sql.y" /* yacc.c:1646  */
    {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), "desc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2124 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 560 "yacc_sql.y" /* yacc.c:1646  */
    {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2134 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 565 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2144 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 570 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2154 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 575 "yacc_sql.y" /* yacc.c:1646  */
    {
	        RelAttr attr;
	        relation_attr_init(&attr, (yyvsp[-3].string), "*");
	        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	    }
#line 2164 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 583 "yacc_sql.y" /* yacc.c:1646  */
    {
		//将condition的值存入，入栈
		CONTEXT->sub_selects_length++;
		CONTEXT->sub_condition_length[CONTEXT->sub_selects_length] = CONTEXT->condition_length;
	}
#line 2174 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 592 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_init(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,(yyvsp[-1].string),
					CONTEXT->conditions + CONTEXT->sub_condition_length[CONTEXT->sub_selects_length], 
					CONTEXT->condition_length - CONTEXT->sub_condition_length[CONTEXT->sub_selects_length]);
		//printf("Condition start at %d\n",CONTEXT->sub_condition_length[CONTEXT->sub_selects_length]);
	}
#line 2185 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 601 "yacc_sql.y" /* yacc.c:1646  */
    {	
			//selects_init(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection);
			selects_append_relation(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection, (yyvsp[-1].string));
			selects_append_conditions(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection, 
						CONTEXT->conditions + CONTEXT->sub_condition_length[CONTEXT->sub_selects_length],
						CONTEXT->condition_length - CONTEXT->sub_condition_length[CONTEXT->sub_selects_length]);
		}
#line 2197 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 611 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,(yyvsp[-1].string),(yyvsp[-3].string));
	}
#line 2205 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 614 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,(yyvsp[-1].string),(yyvsp[-5].string));
	}
#line 2213 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 617 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,"*",(yyvsp[-3].string));
	}
#line 2221 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 620 "yacc_sql.y" /* yacc.c:1646  */
    {
		aggregates_append_field_itoa(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,(yyvsp[-1].number),(yyvsp[-3].string));
	}
#line 2229 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 627 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection, &attr);
		}
#line 2239 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 632 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection, &attr);
		}
#line 2249 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 641 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2261 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 648 "yacc_sql.y" /* yacc.c:1646  */
    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2273 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 655 "yacc_sql.y" /* yacc.c:1646  */
    {
  	        RelAttr attr;
  	        relation_attr_init(&attr, (yyvsp[-3].string), "*");
  	        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
  	}
#line 2283 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 664 "yacc_sql.y" /* yacc.c:1646  */
    {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2291 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 670 "yacc_sql.y" /* yacc.c:1646  */
    {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2299 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 676 "yacc_sql.y" /* yacc.c:1646  */
    {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2307 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 682 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2332 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 702 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2351 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 716 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2368 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 729 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2387 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 744 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2403 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 756 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2419 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 768 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2435 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 781 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2459 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 801 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2483 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 821 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2509 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 843 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2534 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 864 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2559 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 885 "yacc_sql.y" /* yacc.c:1646  */
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
#line 2582 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 906 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = EQUAL_TO; }
#line 2588 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 907 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = LESS_THAN; }
#line 2594 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 908 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = GREAT_THAN; }
#line 2600 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 909 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = LESS_EQUAL; }
#line 2606 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 910 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = GREAT_EQUAL; }
#line 2612 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 911 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = NOT_EQUAL; }
#line 2618 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 912 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = IS_NULL; }
#line 2624 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 913 "yacc_sql.y" /* yacc.c:1646  */
    { CONTEXT->comp[CONTEXT->comp_length++] = IS_NOT_NULL; }
#line 2630 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 918 "yacc_sql.y" /* yacc.c:1646  */
    {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2639 "yacc_sql.tab.c" /* yacc.c:1646  */
    break;


#line 2643 "yacc_sql.tab.c" /* yacc.c:1646  */
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
#line 923 "yacc_sql.y" /* yacc.c:1906  */

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
