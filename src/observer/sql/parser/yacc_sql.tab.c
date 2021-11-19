/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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
  size_t index_length;
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
  context->index_length = 0;
  context->ssql->sstr.insertion.value_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 137 "yacc_sql.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    NOTBELONG = 301,
    GROUPBY = 302,
    DATE_T = 303,
    ORDER_BY = 304,
    ASC = 305,
    UNIQUEINDEX = 306,
    ISNOTNULL = 307,
    ISNULL = 308,
    NULLABLE = 309,
    NOTNULL = 310,
    NULL_T = 311,
    TEXT_T = 312,
    NUMBER = 313,
    FLOAT = 314,
    ID = 315,
    AGGREGATE = 316,
    PATH = 317,
    SSS = 318,
    STAR = 319,
    STRING_V = 320,
    DATE = 321
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 130 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
  char *position;

#line 266 "yacc_sql.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */



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
typedef yytype_int16 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   359

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  149
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  355

#define YYUNDEFTOK  2
#define YYMAXUTOK   321


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   158,   158,   160,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   184,   189,   194,   200,   206,   212,   218,   224,   230,
     237,   245,   255,   256,   265,   272,   282,   289,   291,   295,
     306,   314,   322,   335,   338,   339,   340,   341,   342,   345,
     353,   370,   372,   379,   388,   393,   397,   401,   404,   412,
     422,   432,   440,   457,   477,   478,   483,   484,   490,   493,
     496,   500,   502,   505,   508,   512,   513,   517,   522,   527,
     532,   537,   542,   549,   550,   555,   560,   565,   570,   575,
     583,   588,   593,   598,   603,   608,   615,   624,   633,   644,
     647,   650,   653,   660,   665,   672,   674,   681,   688,   693,
     698,   705,   707,   711,   713,   718,   724,   725,   730,   736,
     738,   742,   744,   749,   770,   783,   796,   809,   822,   838,
     851,   864,   880,   890,   900,   914,   934,   954,   976,   997,
    1018,  1040,  1041,  1042,  1043,  1044,  1045,  1046,  1047,  1051
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
  "NOTBELONG", "GROUPBY", "DATE_T", "ORDER_BY", "ASC", "UNIQUEINDEX",
  "ISNOTNULL", "ISNULL", "NULLABLE", "NOTNULL", "NULL_T", "TEXT_T",
  "NUMBER", "FLOAT", "ID", "AGGREGATE", "PATH", "SSS", "STAR", "STRING_V",
  "DATE", "$accept", "commands", "command", "exit", "help", "sync",
  "begin", "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "create_index", "create_index_attr", "drop_index", "create_table",
  "create_table_token", "attr_def_list", "attr_def", "number", "type",
  "ID_get", "insert", "other_values", "value_list", "value", "delete",
  "update", "select", "inner_join", "on_list", "agg_field",
  "agg_field_list", "order", "order_attr", "order_attr_list",
  "select_attr", "subselect_start", "subselect", "sub_in_select",
  "sub_agg_field", "sub_select_attr", "attr_list", "rel_list", "groupby",
  "group_list", "where", "condition_list", "condition", "comOp",
  "load_data", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321
};
# endif

#define YYPACT_NINF (-276)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -276,   149,  -276,    21,    52,   175,   -52,    15,    35,    49,
      19,    42,   125,   138,   142,   152,   164,    87,  -276,  -276,
    -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,
    -276,    71,  -276,  -276,  -276,  -276,  -276,  -276,    92,   118,
     126,   129,    38,   171,  -276,   170,   172,   202,   206,  -276,
     161,   163,   190,  -276,  -276,  -276,  -276,  -276,   187,   217,
     203,   205,   234,   240,   113,   -27,  -276,    84,   184,   185,
    -276,  -276,   216,   215,   188,   186,   191,   192,   193,  -276,
    -276,   110,   233,   235,   235,   237,    -7,   238,   215,   120,
     241,    32,   254,   220,   231,  -276,   242,   102,   245,   246,
      13,  -276,   204,  -276,  -276,   247,   248,   208,   247,   262,
     209,   210,   215,   215,   121,   263,  -276,  -276,  -276,   154,
    -276,   189,   212,   243,  -276,   121,   265,   191,   256,  -276,
    -276,  -276,  -276,  -276,     1,   218,   219,   235,   235,    23,
     214,  -276,   150,  -276,  -276,   259,  -276,  -276,   249,   261,
     236,   236,   266,  -276,   221,  -276,  -276,  -276,  -276,  -276,
    -276,   269,   269,  -276,  -276,    45,    51,   270,   264,   257,
      32,  -276,   215,   229,   242,   287,   239,  -276,  -276,   272,
     274,  -276,  -276,   235,   244,   276,   277,   235,    32,   285,
    -276,   250,   251,   251,   121,   278,   174,   252,   252,  -276,
    -276,   212,   271,  -276,   212,   108,   189,   253,   243,   295,
     298,  -276,  -276,  -276,   284,   255,   288,   300,  -276,   289,
     123,   144,  -276,   243,  -276,   115,   258,   302,   305,   266,
     290,   269,   269,    59,   283,   296,   286,   301,   303,   260,
     304,   306,    88,   307,    77,   215,  -276,  -276,  -276,  -276,
     272,   313,  -276,   235,   308,   309,   310,    95,  -276,   273,
     275,  -276,    17,  -276,  -276,  -276,  -276,   312,   320,   252,
     252,   311,  -276,   212,   280,  -276,   281,  -276,  -276,  -276,
    -276,  -276,  -276,   282,  -276,   315,  -276,   212,  -276,  -276,
    -276,  -276,   247,   247,   247,   248,   128,   317,   318,   291,
     292,   318,  -276,   121,  -276,   314,   316,   293,   326,  -276,
     215,   327,   294,   328,  -276,  -276,  -276,   297,  -276,  -276,
    -276,    20,    33,  -276,   266,  -276,  -276,  -276,  -276,  -276,
    -276,  -276,  -276,   317,   318,   299,   318,  -276,   318,   318,
    -276,   329,  -276,  -276,   101,  -276,  -276,  -276,   290,   318,
     318,  -276,  -276,  -276,  -276
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     0,     5,     7,     6,     4,    18,    36,     0,     0,
       0,     0,   105,     0,    90,     0,     0,     0,     0,    23,
       0,     0,     0,    24,    25,    26,    22,    21,     0,     0,
       0,     0,     0,     0,     0,     0,    91,     0,     0,     0,
      29,    28,     0,   119,     0,     0,     0,     0,     0,    27,
      34,   105,     0,   105,   105,     0,     0,     0,   119,    64,
       0,     0,     0,     0,     0,    49,    37,     0,     0,     0,
       0,   106,     0,    92,    93,    71,    71,     0,    71,     0,
       0,     0,   119,   119,     0,     0,    57,    55,    56,     0,
      58,     0,     0,   121,    59,     0,     0,     0,     0,    44,
      45,    46,    47,    48,    42,     0,     0,   105,   105,     0,
       0,    70,     0,    68,    94,     0,    69,    61,    66,   111,
     113,   113,    53,    96,     0,   141,   142,   143,   144,   145,
     146,     0,     0,   148,   147,     0,     0,     0,     0,     0,
       0,   120,   119,     0,    37,     0,     0,    40,    41,    32,
       0,   107,   108,   105,     0,     0,     0,   105,     0,    64,
     112,     0,    75,    75,     0,     0,     0,     0,     0,   136,
     123,     0,   137,   135,     0,     0,     0,     0,   121,     0,
       0,    38,    35,    43,     0,     0,     0,     0,   109,     0,
       0,     0,    95,   121,    65,   116,     0,     0,     0,    53,
      51,     0,     0,     0,   103,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   119,   122,    60,   149,    39,
      32,     0,    31,   105,     0,     0,     0,     0,    67,     0,
       0,   115,    83,    76,    62,    63,    54,     0,     0,     0,
       0,     0,   138,     0,     0,   124,     0,   125,   128,   139,
     133,   102,    99,     0,   101,   129,   132,     0,    97,    33,
      30,   110,    71,    71,    71,    71,   116,   116,    83,     0,
       0,    83,    77,     0,    50,     0,     0,     0,     0,   104,
     119,     0,     0,     0,    74,    72,    73,     0,   118,   114,
      80,    83,    83,    79,    53,   126,   127,   140,   130,    98,
     100,   134,   131,   116,    83,     0,    83,    84,    83,    83,
      78,     0,   117,    87,    83,    86,    82,    81,    51,    83,
      83,    85,    52,    89,    88
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,
    -276,  -276,  -276,    80,  -276,  -276,  -276,   157,   211,  -276,
    -276,  -276,  -276,     0,  -224,  -112,  -276,  -276,  -276,   160,
    -276,  -276,  -102,   162,  -276,  -275,  -276,  -146,  -194,  -189,
    -276,  -276,   -41,   201,   207,  -262,   -88,  -191,  -158,  -107,
    -276
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   216,    29,    30,    31,   128,    96,   214,
     134,    97,    32,   268,   195,   121,    33,    34,    35,   112,
     189,    45,   315,   227,   263,   302,    46,   122,   168,   235,
     169,   236,   218,   113,   192,   261,    92,   171,   123,   165,
      36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     109,    66,   152,   141,   143,   266,   146,   238,    47,   237,
     240,   106,   208,   172,   166,   197,   198,   246,   176,   201,
     204,   107,    48,   320,   150,   151,   323,    37,   298,    38,
     223,   334,   258,    83,   318,   319,   299,    84,    49,   299,
     101,   183,   103,   104,   338,   300,   337,   340,   335,   115,
      51,   184,   299,   200,   203,   177,   178,    64,    40,   343,
      41,   345,   115,   346,   347,   144,    65,   301,   115,   351,
     336,   342,    39,   137,   353,   354,   115,   138,    50,   308,
     305,   306,   229,   339,   209,   269,   270,   273,   116,   233,
     117,   118,   119,   313,   115,   120,   181,   182,   287,   244,
     341,   116,    52,   117,   118,   199,   282,   116,   120,   117,
     118,   202,   349,   295,   120,   116,   283,   117,   118,   271,
     299,   272,   120,   184,    58,   129,   130,   131,    53,    64,
     110,    59,   286,   116,   259,   117,   118,   285,   100,   111,
     120,    54,    85,   260,    86,    55,   222,   259,    87,     2,
     132,   350,    60,     3,     4,    56,   317,   288,     5,   133,
       6,     7,     8,     9,    10,    11,   241,    57,   242,    12,
      13,    14,   243,    81,    82,    15,    16,   116,    61,   117,
     118,   254,   154,   255,   120,    17,    62,   256,    67,    63,
     314,   324,   316,   155,   156,   157,   158,   159,   160,   161,
     162,    68,   254,    69,   257,    70,   163,   164,   256,    71,
      81,   186,   291,   155,   156,   157,   158,   159,   160,   231,
     232,    72,   329,    73,    74,    75,   163,   164,   155,   156,
     157,   158,   159,   160,    76,    42,    43,    79,    77,    44,
      78,   163,   164,    80,    88,    89,    90,    91,    93,    94,
     102,    95,    98,    99,    64,   105,   108,   124,   114,   125,
     126,   127,   135,   136,   139,   147,   140,   142,   145,   148,
     149,   173,   153,   167,   175,   185,   170,   187,   179,   180,
     111,   196,   206,   191,   188,   194,   115,   205,   207,   210,
     212,   215,   217,   220,   221,   110,   230,   213,   247,   239,
     226,   248,   249,   252,   219,   264,   251,   253,   265,   267,
     225,   274,   234,   245,   275,   250,   290,   276,   262,   277,
     279,   278,   280,   304,   281,   284,   292,   293,   294,   303,
     289,   211,   325,   296,   326,   297,   259,   299,   174,   307,
     309,   310,   311,   312,   328,   330,   332,   348,   352,   224,
     190,   321,   322,   327,   331,   228,     0,   333,   193,   344
};

static const yytype_int16 yycheck[] =
{
      88,    42,   114,   105,   106,   229,   108,   201,    60,   198,
     204,    18,   170,   125,   121,   161,   162,   208,    17,   165,
     166,    28,     7,   298,   112,   113,   301,     6,    11,     8,
     188,    11,   223,    60,   296,   297,    19,    64,     3,    19,
      81,    18,    83,    84,    11,    28,   321,   322,    28,    17,
      31,    28,    19,   165,   166,    54,    55,    19,     6,   334,
       8,   336,    17,   338,   339,   106,    28,    50,    17,   344,
      50,   333,    51,    60,   349,   350,    17,    64,    29,   273,
     269,   270,   194,    50,   172,   231,   232,   233,    56,   196,
      58,    59,    60,   287,    17,    63,   137,   138,   244,   206,
     324,    56,    60,    58,    59,    60,    18,    56,    63,    58,
      59,    60,    11,    18,    63,    56,    28,    58,    59,    60,
      19,   233,    63,    28,    37,    23,    24,    25,     3,    19,
      10,    60,   244,    56,    19,    58,    59,    60,    28,    19,
      63,     3,    58,    28,    60,     3,   187,    19,    64,     0,
      48,    50,    60,     4,     5,     3,    28,   245,     9,    57,
      11,    12,    13,    14,    15,    16,    58,     3,    60,    20,
      21,    22,    64,    60,    61,    26,    27,    56,    60,    58,
      59,    58,    28,    60,    63,    36,    60,    64,    17,    60,
     292,   303,   294,    39,    40,    41,    42,    43,    44,    45,
      46,    31,    58,    31,    60,     3,    52,    53,    64,     3,
      60,    61,   253,    39,    40,    41,    42,    43,    44,    45,
      46,    60,   310,    60,    34,    38,    52,    53,    39,    40,
      41,    42,    43,    44,    17,    60,    61,     3,    35,    64,
      35,    52,    53,     3,    60,    60,    30,    32,    60,    63,
      17,    60,    60,    60,    19,    18,    18,     3,    17,    39,
      29,    19,    17,    17,    60,     3,    19,    19,    60,    60,
      60,     6,     9,    61,    18,    61,    33,    18,    60,    60,
      19,    60,    18,    47,    35,    19,    17,    17,    31,    60,
       3,    19,    18,    17,    17,    10,    18,    58,     3,    28,
      49,     3,    18,     3,    60,     3,    18,    18,     3,    19,
      60,    28,    60,    60,    18,    60,     3,    31,    60,    18,
      60,    18,    18,     3,    18,    18,    18,    18,    18,    17,
     250,   174,    18,    60,    18,    60,    19,    19,   127,    28,
      60,    60,    60,    28,    18,    18,    18,    18,   348,   189,
     149,    60,    60,    60,    60,   193,    -1,    60,   151,    60
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    68,     0,     4,     5,     9,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    26,    27,    36,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    81,
      82,    83,    89,    93,    94,    95,   117,     6,     8,    51,
       6,     8,    60,    61,    64,    98,   103,    60,     7,     3,
      29,    31,    60,     3,     3,     3,     3,     3,    37,    60,
      60,    60,    60,    60,    19,    28,   109,    17,    31,    31,
       3,     3,    60,    60,    34,    38,    17,    35,    35,     3,
       3,    60,    61,    60,    64,    58,    60,    64,    60,    60,
      30,    32,   113,    60,    63,    60,    85,    88,    60,    60,
      28,   109,    17,   109,   109,    18,    18,    28,    18,   113,
      10,    19,    96,   110,    17,    17,    56,    58,    59,    60,
      63,    92,   104,   115,     3,    39,    29,    19,    84,    23,
      24,    25,    48,    57,    87,    17,    17,    60,    64,    60,
      19,    99,    19,    99,   109,    60,    99,     3,    60,    60,
     113,   113,    92,     9,    28,    39,    40,    41,    42,    43,
      44,    45,    46,    52,    53,   116,   116,    61,   105,   107,
      33,   114,    92,     6,    85,    18,    17,    54,    55,    60,
      60,   109,   109,    18,    28,    61,    61,    18,    35,    97,
     110,    47,   111,   111,    19,    91,    60,   104,   104,    60,
      92,   104,    60,    92,   104,    17,    18,    31,   115,   113,
      60,    84,     3,    58,    86,    19,    80,    18,   109,    60,
      17,    17,   109,   115,    96,    60,    49,   100,   100,    92,
      18,    45,    46,   116,    60,   106,   108,   106,   105,    28,
     105,    58,    60,    64,   116,    60,   114,     3,     3,    18,
      60,    18,     3,    18,    58,    60,    64,    60,   114,    19,
      28,   112,    60,   101,     3,     3,    91,    19,    90,   104,
     104,    60,    92,   104,    28,    18,    31,    18,    18,    60,
      18,    18,    18,    28,    18,    60,    92,   104,   113,    80,
       3,   109,    18,    18,    18,    18,    60,    60,    11,    19,
      28,    50,   102,    17,     3,   106,   106,    28,   105,    60,
      60,    60,    28,   105,    99,    99,    99,    28,   112,   112,
     102,    60,    60,   102,    92,    18,    18,    60,    18,   113,
      18,    60,    18,    60,    11,    28,    50,   102,    11,    50,
     102,    91,   112,   102,    60,   102,   102,   102,    18,    11,
      50,   102,    90,   102,   102
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    67,    68,    68,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    79,    80,    80,    81,    82,    83,    84,    84,    85,
      85,    85,    85,    86,    87,    87,    87,    87,    87,    88,
      89,    90,    90,    91,    91,    92,    92,    92,    92,    93,
      94,    95,    95,    95,    96,    96,    97,    97,    98,    98,
      98,    99,    99,    99,    99,   100,   100,   101,   101,   101,
     101,   101,   101,   102,   102,   102,   102,   102,   102,   102,
     103,   103,   103,   103,   103,   103,   104,   105,   106,   107,
     107,   107,   107,   108,   108,   109,   109,   109,   109,   109,
     109,   110,   110,   111,   111,   111,   112,   112,   112,   113,
     113,   114,   114,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   116,   116,   116,   116,   116,   116,   116,   116,   117
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,     9,     0,     3,     4,     7,     2,     0,     3,     5,
       3,     3,     2,     1,     1,     1,     1,     1,     1,     1,
      10,     0,     6,     0,     3,     1,     1,     1,     1,     5,
       8,     6,     9,     9,     0,     4,     0,     3,     5,     5,
       5,     0,     6,     6,     6,     0,     2,     2,     4,     3,
       3,     5,     5,     0,     3,     5,     4,     4,     6,     6,
       1,     2,     4,     4,     5,     7,     2,     4,     4,     4,
       6,     4,     4,     1,     3,     0,     3,     5,     5,     6,
       8,     0,     3,     0,     5,     3,     0,     5,     3,     0,
       3,     0,     3,     3,     5,     5,     7,     7,     5,     5,
       7,     7,     5,     5,     7,     3,     3,     3,     5,     5,
       7,     1,     1,     1,     1,     1,     1,     1,     1,     8
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, void *scanner)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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
  case 21:
#line 184 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1693 "yacc_sql.tab.c"
    break;

  case 22:
#line 189 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1701 "yacc_sql.tab.c"
    break;

  case 23:
#line 194 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1709 "yacc_sql.tab.c"
    break;

  case 24:
#line 200 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1717 "yacc_sql.tab.c"
    break;

  case 25:
#line 206 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1725 "yacc_sql.tab.c"
    break;

  case 26:
#line 212 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1733 "yacc_sql.tab.c"
    break;

  case 27:
#line 218 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1742 "yacc_sql.tab.c"
    break;

  case 28:
#line 224 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1750 "yacc_sql.tab.c"
    break;

  case 29:
#line 230 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1759 "yacc_sql.tab.c"
    break;

  case 30:
#line 237 "yacc_sql.y"
                                                                           {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
		create_index_list_init(&CONTEXT->ssql->sstr.create_index_list ,(yyvsp[-7].string), (yyvsp[-5].string));
		CreateIndex c_i;
		create_index_init_short(&c_i, (yyvsp[-3].string));
		create_index_set_first(&CONTEXT->ssql->sstr.create_index_list, &c_i);
		CONTEXT->index_length++;
	}
#line 1772 "yacc_sql.tab.c"
    break;

  case 31:
#line 245 "yacc_sql.y"
                                                                {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index unique";
		create_index_list_init(&CONTEXT->ssql->sstr.create_index_list, (yyvsp[-6].string), (yyvsp[-4].string));
		CreateIndex c_i;
		create_index_init(&c_i, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string), 1);
		create_index_set_first(&CONTEXT->ssql->sstr.create_index_list, &c_i);
		CONTEXT->index_length++;
	}
#line 1785 "yacc_sql.tab.c"
    break;

  case 33:
#line 256 "yacc_sql.y"
                                    {
		CreateIndex c_i;
		create_index_init_short(&c_i, (yyvsp[-1].string));
		create_index_list_append(&CONTEXT->ssql->sstr.create_index_list, &c_i);
		CONTEXT->index_length++;
	}
#line 1796 "yacc_sql.tab.c"
    break;

  case 34:
#line 266 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1805 "yacc_sql.tab.c"
    break;

  case 35:
#line 273 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1817 "yacc_sql.tab.c"
    break;

  case 36:
#line 282 "yacc_sql.y"
                    {
		AttrInfo attribute;
		attr_info_init(&attribute, "null_field", BITMAPS, 4);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		CONTEXT->value_length++;
	}
#line 1828 "yacc_sql.tab.c"
    break;

  case 38:
#line 291 "yacc_sql.y"
                                   {    }
#line 1834 "yacc_sql.tab.c"
    break;

  case 39:
#line 296 "yacc_sql.y"
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
#line 1849 "yacc_sql.tab.c"
    break;

  case 40:
#line 307 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init_with_null(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1860 "yacc_sql.tab.c"
    break;

  case 41:
#line 315 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init_with_null(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1871 "yacc_sql.tab.c"
    break;

  case 42:
#line 323 "yacc_sql.y"
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
#line 1886 "yacc_sql.tab.c"
    break;

  case 43:
#line 335 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1892 "yacc_sql.tab.c"
    break;

  case 44:
#line 338 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1898 "yacc_sql.tab.c"
    break;

  case 45:
#line 339 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1904 "yacc_sql.tab.c"
    break;

  case 46:
#line 340 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1910 "yacc_sql.tab.c"
    break;

  case 47:
#line 341 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1916 "yacc_sql.tab.c"
    break;

  case 48:
#line 342 "yacc_sql.y"
                    { (yyval.number)=TEXT; }
#line 1922 "yacc_sql.tab.c"
    break;

  case 49:
#line 346 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1931 "yacc_sql.tab.c"
    break;

  case 50:
#line 354 "yacc_sql.y"
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
#line 1951 "yacc_sql.tab.c"
    break;

  case 52:
#line 372 "yacc_sql.y"
                                                        {
        //printf("other values\n");

    }
#line 1960 "yacc_sql.tab.c"
    break;

  case 53:
#line 379 "yacc_sql.y"
    {
        //printf("value list finished \n");
        for(int i=0;i<CONTEXT->value_length;++i) {
            CONTEXT->values_list[CONTEXT->values_size][i]=CONTEXT->values[i];
        }
        CONTEXT->values_length_list[CONTEXT->values_size]=CONTEXT->value_length;
        CONTEXT->value_length=0;
        CONTEXT->values_size+=1;
    }
#line 1974 "yacc_sql.tab.c"
    break;

  case 54:
#line 388 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1982 "yacc_sql.tab.c"
    break;

  case 55:
#line 393 "yacc_sql.y"
          {
    //printf("value\n");
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1991 "yacc_sql.tab.c"
    break;

  case 56:
#line 397 "yacc_sql.y"
          {
    //printf("value\n");
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 2000 "yacc_sql.tab.c"
    break;

  case 57:
#line 401 "yacc_sql.y"
               {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		}
#line 2008 "yacc_sql.tab.c"
    break;

  case 58:
#line 404 "yacc_sql.y"
         {
    //printf("value\n");
		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 2018 "yacc_sql.tab.c"
    break;

  case 59:
#line 413 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 2030 "yacc_sql.tab.c"
    break;

  case 60:
#line 423 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 2042 "yacc_sql.tab.c"
    break;

  case 61:
#line 433 "yacc_sql.y"
                {
		//聚合运算的语法解析
		CONTEXT->ssql->flag = SCF_AGGREGATE;
		aggregates_init(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].string),CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->condition_length = 0;
	}
#line 2053 "yacc_sql.tab.c"
    break;

  case 62:
#line 440 "yacc_sql.y"
                                                                               {
			//单表一定进这里
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-5].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
#line 2074 "yacc_sql.tab.c"
    break;

  case 63:
#line 458 "yacc_sql.y"
                {	
			//多表一定进这里
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-5].string));

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
#line 2096 "yacc_sql.tab.c"
    break;

  case 65:
#line 478 "yacc_sql.y"
                                       {
        selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
    }
#line 2104 "yacc_sql.tab.c"
    break;

  case 67:
#line 484 "yacc_sql.y"
                                  {

    }
#line 2112 "yacc_sql.tab.c"
    break;

  case 68:
#line 490 "yacc_sql.y"
                                                  {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,NULL,(yyvsp[-2].string),(yyvsp[-4].string));
	}
#line 2120 "yacc_sql.tab.c"
    break;

  case 69:
#line 493 "yacc_sql.y"
                                                      {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,NULL,"*",(yyvsp[-4].string));
	}
#line 2128 "yacc_sql.tab.c"
    break;

  case 70:
#line 496 "yacc_sql.y"
                                                        {
		aggregates_append_field_itoa(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].number),(yyvsp[-4].string));
	}
#line 2136 "yacc_sql.tab.c"
    break;

  case 72:
#line 502 "yacc_sql.y"
                                                         {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,NULL,(yyvsp[-2].string),(yyvsp[-4].string));
	}
#line 2144 "yacc_sql.tab.c"
    break;

  case 73:
#line 505 "yacc_sql.y"
                                                            {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,NULL,"*",(yyvsp[-4].string));
	}
#line 2152 "yacc_sql.tab.c"
    break;

  case 74:
#line 508 "yacc_sql.y"
                                                              {
		aggregates_append_field_itoa(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].number),(yyvsp[-4].string));
	}
#line 2160 "yacc_sql.tab.c"
    break;

  case 76:
#line 513 "yacc_sql.y"
                          {
    }
#line 2167 "yacc_sql.tab.c"
    break;

  case 77:
#line 517 "yacc_sql.y"
                       {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-1].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2177 "yacc_sql.tab.c"
    break;

  case 78:
#line 522 "yacc_sql.y"
                                 {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2187 "yacc_sql.tab.c"
    break;

  case 79:
#line 527 "yacc_sql.y"
                              {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-2].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2197 "yacc_sql.tab.c"
    break;

  case 80:
#line 532 "yacc_sql.y"
                                {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-2].string), "desc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2207 "yacc_sql.tab.c"
    break;

  case 81:
#line 537 "yacc_sql.y"
                                     {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2217 "yacc_sql.tab.c"
    break;

  case 82:
#line 542 "yacc_sql.y"
                                      {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), "desc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2227 "yacc_sql.tab.c"
    break;

  case 84:
#line 550 "yacc_sql.y"
                               {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-1].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2237 "yacc_sql.tab.c"
    break;

  case 85:
#line 555 "yacc_sql.y"
                                      {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2247 "yacc_sql.tab.c"
    break;

  case 86:
#line 560 "yacc_sql.y"
                                   {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-2].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2257 "yacc_sql.tab.c"
    break;

  case 87:
#line 565 "yacc_sql.y"
                                    {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-2].string), "desc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2267 "yacc_sql.tab.c"
    break;

  case 88:
#line 570 "yacc_sql.y"
                                          {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2277 "yacc_sql.tab.c"
    break;

  case 89:
#line 575 "yacc_sql.y"
                                           {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), "desc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2287 "yacc_sql.tab.c"
    break;

  case 90:
#line 583 "yacc_sql.y"
         {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*",NULL);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2297 "yacc_sql.tab.c"
    break;

  case 91:
#line 588 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string),NULL);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2307 "yacc_sql.tab.c"
    break;

  case 92:
#line 593 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string),NULL);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2317 "yacc_sql.tab.c"
    break;

  case 93:
#line 598 "yacc_sql.y"
                                {
	        RelAttr attr;
	        relation_attr_init(&attr, (yyvsp[-3].string), "*",NULL);
	        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	    }
#line 2327 "yacc_sql.tab.c"
    break;

  case 94:
#line 603 "yacc_sql.y"
                                              {
			RelAttr attr;
	        relation_attr_init(&attr, NULL, (yyvsp[-2].string), (yyvsp[-4].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2337 "yacc_sql.tab.c"
    break;

  case 95:
#line 608 "yacc_sql.y"
                                                     {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string),(yyvsp[-2].string), (yyvsp[-6].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2347 "yacc_sql.tab.c"
    break;

  case 96:
#line 616 "yacc_sql.y"
        {
		//将condition的值存入，入栈
		CONTEXT->sub_selects_length++;
		CONTEXT->sub_condition_length[CONTEXT->sub_selects_length] = CONTEXT->condition_length;
	}
#line 2357 "yacc_sql.tab.c"
    break;

  case 97:
#line 625 "yacc_sql.y"
                {
		aggregates_init(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,(yyvsp[-1].string),
					CONTEXT->conditions + CONTEXT->sub_condition_length[CONTEXT->sub_selects_length], 
					CONTEXT->condition_length - CONTEXT->sub_condition_length[CONTEXT->sub_selects_length]);
		//printf("Condition start at %d\n",CONTEXT->sub_condition_length[CONTEXT->sub_selects_length]);
	}
#line 2368 "yacc_sql.tab.c"
    break;

  case 98:
#line 634 "yacc_sql.y"
                {	
			//selects_init(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection);
			selects_append_relation(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection, (yyvsp[-1].string));
			selects_append_conditions(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection, 
						CONTEXT->conditions + CONTEXT->sub_condition_length[CONTEXT->sub_selects_length],
						CONTEXT->condition_length - CONTEXT->sub_condition_length[CONTEXT->sub_selects_length]);
		}
#line 2380 "yacc_sql.tab.c"
    break;

  case 99:
#line 644 "yacc_sql.y"
                                   {
		aggregates_append_field(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,NULL,(yyvsp[-1].string),(yyvsp[-3].string));
	}
#line 2388 "yacc_sql.tab.c"
    break;

  case 100:
#line 647 "yacc_sql.y"
                                           {
		aggregates_append_field(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,(yyvsp[-3].string),(yyvsp[-1].string),(yyvsp[-5].string));
	}
#line 2396 "yacc_sql.tab.c"
    break;

  case 101:
#line 650 "yacc_sql.y"
                                       {
		aggregates_append_field(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,NULL,"*",(yyvsp[-3].string));
	}
#line 2404 "yacc_sql.tab.c"
    break;

  case 102:
#line 653 "yacc_sql.y"
                                         {
		aggregates_append_field_itoa(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,(yyvsp[-1].number),(yyvsp[-3].string));
	}
#line 2412 "yacc_sql.tab.c"
    break;

  case 103:
#line 660 "yacc_sql.y"
       {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string),NULL);
			selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection, &attr);
		}
#line 2422 "yacc_sql.tab.c"
    break;

  case 104:
#line 665 "yacc_sql.y"
                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string),NULL);
			selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection, &attr);
		}
#line 2432 "yacc_sql.tab.c"
    break;

  case 106:
#line 674 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string),NULL);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2444 "yacc_sql.tab.c"
    break;

  case 107:
#line 681 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string),NULL);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2456 "yacc_sql.tab.c"
    break;

  case 108:
#line 688 "yacc_sql.y"
                                      {
  	        RelAttr attr;
  	        relation_attr_init(&attr, (yyvsp[-3].string), "*",NULL);
  	        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
  	}
#line 2466 "yacc_sql.tab.c"
    break;

  case 109:
#line 693 "yacc_sql.y"
                                                    {
			RelAttr attr;
	        relation_attr_init(&attr, NULL, (yyvsp[-2].string), (yyvsp[-4].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2476 "yacc_sql.tab.c"
    break;

  case 110:
#line 698 "yacc_sql.y"
                                                           {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string),(yyvsp[-2].string), (yyvsp[-6].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2486 "yacc_sql.tab.c"
    break;

  case 112:
#line 707 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2494 "yacc_sql.tab.c"
    break;

  case 114:
#line 713 "yacc_sql.y"
                                      {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string),(yyvsp[-1].string),NULL);
		selects_append_group_attr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2504 "yacc_sql.tab.c"
    break;

  case 115:
#line 718 "yacc_sql.y"
                               {
		RelAttr attr;
		relation_attr_init(&attr, NULL,(yyvsp[-1].string),NULL);
		selects_append_group_attr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2514 "yacc_sql.tab.c"
    break;

  case 117:
#line 725 "yacc_sql.y"
                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string),(yyvsp[-1].string),NULL);
		selects_append_group_attr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2524 "yacc_sql.tab.c"
    break;

  case 118:
#line 730 "yacc_sql.y"
                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL,(yyvsp[-1].string),NULL);
		selects_append_group_attr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2534 "yacc_sql.tab.c"
    break;

  case 120:
#line 738 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2542 "yacc_sql.tab.c"
    break;

  case 122:
#line 744 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2550 "yacc_sql.tab.c"
    break;

  case 123:
#line 750 "yacc_sql.y"
                {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string),NULL);

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
#line 2575 "yacc_sql.tab.c"
    break;

  case 124:
#line 770 "yacc_sql.y"
                                                       {
		//in subselect
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-4].string),NULL);
		Selects* in_select = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection;
		Condition condition;
		condition_init(&condition, IN, 1, &left_attr, NULL, 0, NULL, NULL,NULL,NULL);
		condition_set_inselect(&condition,in_select);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length],1);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2593 "yacc_sql.tab.c"
    break;

  case 125:
#line 783 "yacc_sql.y"
                                                          {
		//in subselect
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-4].string),NULL);
		Selects* in_select = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection;
		Condition condition;
		condition_init(&condition, NOT_IN, 1, &left_attr, NULL, 0, NULL, NULL,NULL,NULL);
		condition_set_inselect(&condition,in_select);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length],1);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2611 "yacc_sql.tab.c"
    break;

  case 126:
#line 796 "yacc_sql.y"
                                                              {
		//in subselect
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string),NULL);
		Selects* in_select = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection;
		Condition condition;
		condition_init(&condition, IN, 1, &left_attr, NULL, 0, NULL, NULL,NULL,NULL);
		condition_set_inselect(&condition,in_select);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length],1);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2629 "yacc_sql.tab.c"
    break;

  case 127:
#line 809 "yacc_sql.y"
                                                                 {
		//in subselect
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string),NULL);
		Selects* in_select = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection;
		Condition condition;
		condition_init(&condition, NOT_IN, 1, &left_attr, NULL, 0, NULL, NULL,NULL,NULL);
		condition_set_inselect(&condition,in_select);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length],1);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2647 "yacc_sql.tab.c"
    break;

  case 128:
#line 823 "yacc_sql.y"
        {
		//出栈
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-4].string),NULL);
		Aggregates* right_agg_value = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation;
		Condition condition;
		condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length], 1, &left_attr, NULL, 0, NULL, NULL,NULL,right_agg_value);
		//TODO for memory leakage
		//destroy会把子查询的子查询destroy了，需要实现一个不destroy子查询的函数
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length],0);
		//aggregates_destroy(right_agg_value);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2667 "yacc_sql.tab.c"
    break;

  case 129:
#line 839 "yacc_sql.y"
        {
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string),NULL);
		Aggregates* left_agg_value = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation;
		Condition condition;
		condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length],0,NULL,NULL,1,&right_attr,NULL,left_agg_value,NULL);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length],0);
		//aggregates_destroy(left_agg_value);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2684 "yacc_sql.tab.c"
    break;

  case 130:
#line 852 "yacc_sql.y"
        {
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string),NULL);
		Aggregates* right_agg_value = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation;
		Condition condition;
		condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length], 1, &left_attr, NULL, 0, NULL, NULL,NULL,right_agg_value);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length],0);
		//aggregates_destroy(right_agg_value);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2701 "yacc_sql.tab.c"
    break;

  case 131:
#line 865 "yacc_sql.y"
        {
		Aggregates* right_agg_value = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation;
		CONTEXT->sub_selects_length--;

		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];

		Aggregates* left_agg_value = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation;
		CONTEXT->sub_selects_length--;

		Condition condition;
		condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length], 0, NULL, NULL, 0, NULL, NULL,left_agg_value,right_agg_value);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length+2],0);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length+1],0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2721 "yacc_sql.tab.c"
    break;

  case 132:
#line 880 "yacc_sql.y"
                                                     {
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		Aggregates* left_agg_value = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation;
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Condition condition;
		condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length],0,NULL,NULL,0,NULL,right_value,left_agg_value,NULL);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length],0);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2736 "yacc_sql.tab.c"
    break;

  case 133:
#line 890 "yacc_sql.y"
                                                     {
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		Aggregates* right_agg_value = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation;
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		Condition condition;
		condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length],0,NULL,left_value,0,NULL,NULL,NULL,right_agg_value);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length],0);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2751 "yacc_sql.tab.c"
    break;

  case 134:
#line 901 "yacc_sql.y"
        {
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string),NULL);
		Aggregates* left_agg_value = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation;
		Condition condition;
		condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length],0,NULL,NULL,1,&right_attr,NULL,left_agg_value,NULL);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length],0);
		//aggregates_destroy(left_agg_value);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2768 "yacc_sql.tab.c"
    break;

  case 135:
#line 915 "yacc_sql.y"
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
#line 2792 "yacc_sql.tab.c"
    break;

  case 136:
#line 935 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string),NULL);
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string),NULL);

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
#line 2816 "yacc_sql.tab.c"
    break;

  case 137:
#line 955 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string),NULL);

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
#line 2842 "yacc_sql.tab.c"
    break;

  case 138:
#line 977 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string),NULL);
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
#line 2867 "yacc_sql.tab.c"
    break;

  case 139:
#line 998 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string),NULL);

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
#line 2892 "yacc_sql.tab.c"
    break;

  case 140:
#line 1019 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string),NULL);
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string),NULL);

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
#line 2915 "yacc_sql.tab.c"
    break;

  case 141:
#line 1040 "yacc_sql.y"
             { CONTEXT->comp[CONTEXT->comp_length++] = EQUAL_TO; }
#line 2921 "yacc_sql.tab.c"
    break;

  case 142:
#line 1041 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->comp_length++] = LESS_THAN; }
#line 2927 "yacc_sql.tab.c"
    break;

  case 143:
#line 1042 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->comp_length++] = GREAT_THAN; }
#line 2933 "yacc_sql.tab.c"
    break;

  case 144:
#line 1043 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->comp_length++] = LESS_EQUAL; }
#line 2939 "yacc_sql.tab.c"
    break;

  case 145:
#line 1044 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->comp_length++] = GREAT_EQUAL; }
#line 2945 "yacc_sql.tab.c"
    break;

  case 146:
#line 1045 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->comp_length++] = NOT_EQUAL; }
#line 2951 "yacc_sql.tab.c"
    break;

  case 147:
#line 1046 "yacc_sql.y"
                 { CONTEXT->comp[CONTEXT->comp_length++] = IS_NULL; }
#line 2957 "yacc_sql.tab.c"
    break;

  case 148:
#line 1047 "yacc_sql.y"
                    { CONTEXT->comp[CONTEXT->comp_length++] = IS_NOT_NULL; }
#line 2963 "yacc_sql.tab.c"
    break;

  case 149:
#line 1052 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2972 "yacc_sql.tab.c"
    break;


#line 2976 "yacc_sql.tab.c"

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp, scanner);
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
#line 1057 "yacc_sql.y"

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
