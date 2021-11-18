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
    DATE_T = 302,
    ORDER_BY = 303,
    ASC = 304,
    UNIQUEINDEX = 305,
    ISNOTNULL = 306,
    ISNULL = 307,
    NULLABLE = 308,
    NOTNULL = 309,
    NULL_T = 310,
    TEXT_T = 311,
    EXPRESSION = 312,
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
#define YYLAST   342

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  149
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  338

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
     353,   370,   372,   377,   385,   390,   393,   396,   399,   406,
     416,   426,   428,   436,   452,   471,   472,   477,   478,   484,
     487,   490,   494,   496,   499,   502,   506,   507,   511,   516,
     521,   526,   531,   536,   543,   544,   549,   554,   559,   564,
     569,   577,   582,   587,   592,   597,   602,   611,   620,   631,
     634,   637,   640,   647,   652,   659,   661,   668,   675,   680,
     684,   686,   690,   692,   695,   697,   701,   702,   703,   704,
     705,   706,   707,   708,   720,   733,   746,   759,   772,   788,
     801,   814,   830,   840,   850,   863,   883,   903,   925,   946,
     967,   990,   991,   992,   993,   994,   995,   996,   997,  1002
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
  "NOTBELONG", "DATE_T", "ORDER_BY", "ASC", "UNIQUEINDEX", "ISNOTNULL",
  "ISNULL", "NULLABLE", "NOTNULL", "NULL_T", "TEXT_T", "EXPRESSION",
  "NUMBER", "FLOAT", "ID", "AGGREGATE", "PATH", "SSS", "STAR", "STRING_V",
  "DATE", "$accept", "commands", "command", "exit", "help", "sync",
  "begin", "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "create_index", "create_index_attr", "drop_index", "create_table",
  "create_table_token", "attr_def_list", "attr_def", "number", "type",
  "ID_get", "insert", "other_values", "value_list", "value", "delete",
  "update", "select", "inner_join", "on_list", "agg_field",
  "agg_field_list", "order", "order_attr", "order_attr_list",
  "select_attr", "subselect_start", "subselect", "sub_in_select",
  "sub_agg_field", "sub_select_attr", "attr_list", "rel_list", "where",
  "condition_list", "condition", "comOp", "load_data", YY_NULLPTR
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

#define YYPACT_NINF (-223)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -223,   112,  -223,    19,    74,   171,   -45,    23,    28,    29,
      34,   -12,    65,    83,    94,    99,   101,    50,   119,  -223,
    -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
    -223,  -223,    69,  -223,  -223,  -223,  -223,  -223,  -223,    75,
      77,    82,    90,   128,    15,   153,  -223,   140,   144,   173,
     175,  -223,   117,   123,   159,  -223,  -223,  -223,  -223,  -223,
     169,  -223,   191,   185,   194,   206,   227,   -47,  -223,    35,
    -223,   134,   178,   181,  -223,  -223,   203,   210,   184,   182,
     186,   187,   188,  -223,  -223,   128,    22,   128,   128,   231,
     232,   233,   210,    32,   235,     4,   250,   215,   226,  -223,
     237,    84,   240,   241,  -223,    54,  -223,  -223,  -223,   242,
     242,   242,   256,   200,   202,   210,   210,   109,   254,  -223,
     174,  -223,  -223,   145,  -223,   174,   204,   234,  -223,   109,
     258,   186,   248,  -223,  -223,  -223,  -223,  -223,    20,   208,
     209,   128,   128,   211,  -223,  -223,  -223,  -223,   236,   251,
     225,   225,   255,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
    -223,  -223,   164,   216,   260,   260,    86,    96,   261,   257,
     249,     4,  -223,   210,   219,   237,   278,   224,  -223,  -223,
     264,   266,  -223,  -223,   268,     4,   276,  -223,   228,   284,
     286,   109,   272,  -223,   263,  -223,   160,   238,   238,  -223,
    -223,  -223,   204,  -223,   265,  -223,   204,   176,   174,   239,
     234,   289,   291,  -223,  -223,  -223,   277,   243,   279,   293,
     179,   234,  -223,    87,  -223,  -223,  -223,   255,   281,   244,
     260,   260,   103,   273,   287,   271,   288,   290,   247,   292,
     294,    11,   295,    -3,   210,  -223,  -223,  -223,  -223,   264,
     306,  -223,   296,   297,   298,  -223,   299,   259,   262,   299,
    -223,  -223,   300,   308,  -223,   238,   238,  -223,   301,  -223,
     204,   267,  -223,   270,  -223,  -223,  -223,  -223,  -223,  -223,
     274,  -223,   303,  -223,   204,  -223,  -223,  -223,   242,   242,
     242,  -223,   146,    17,  -223,   109,  -223,   302,   305,   275,
     307,  -223,   210,   310,   280,   314,  -223,  -223,  -223,   299,
     282,   299,  -223,   299,   299,  -223,   255,  -223,  -223,  -223,
    -223,  -223,  -223,  -223,  -223,  -223,    21,  -223,  -223,  -223,
     315,   299,   299,  -223,   281,  -223,  -223,  -223
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
      20,    19,    14,    15,    16,    17,     9,    10,    11,    12,
      13,     8,     0,     5,     7,     6,     4,    18,    36,     0,
       0,     0,     0,   105,   105,     0,    91,     0,     0,     0,
       0,    23,     0,     0,     0,    24,    25,    26,    22,    21,
       0,    61,     0,     0,     0,     0,     0,     0,    95,     0,
      92,     0,     0,     0,    29,    28,     0,   112,     0,     0,
       0,     0,     0,    27,    34,   105,   105,   105,   105,     0,
       0,     0,   112,    65,     0,     0,     0,     0,     0,    49,
      37,     0,     0,     0,   109,     0,   106,    93,    94,    72,
      72,    72,     0,     0,     0,   112,   112,     0,     0,    57,
       0,    55,    56,     0,    58,     0,     0,   114,    59,     0,
       0,     0,     0,    44,    45,    46,    47,    48,    42,     0,
       0,   105,   105,     0,    71,    69,    70,    62,    67,   110,
      76,    76,    53,    96,   141,   142,   143,   144,   145,   146,
     148,   147,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   113,   112,     0,    37,     0,     0,    40,    41,
      32,     0,   107,   108,     0,     0,    65,   111,     0,     0,
       0,     0,     0,   122,   117,   121,     0,     0,     0,   116,
     136,   123,     0,   120,   137,   135,     0,     0,     0,     0,
     114,     0,     0,    38,    35,    43,     0,     0,     0,     0,
       0,   114,    66,    84,    77,    63,    64,    53,    51,     0,
       0,     0,     0,   103,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   115,    60,   149,    39,    32,
       0,    31,     0,     0,     0,    68,    84,     0,     0,    84,
      78,    54,     0,     0,   119,     0,     0,   118,     0,   138,
       0,     0,   124,     0,   125,   128,   139,   133,   102,    99,
       0,   101,   129,   132,     0,    97,    33,    30,    72,    72,
      72,    81,    84,    84,    80,     0,    50,     0,     0,     0,
       0,   104,   112,     0,     0,     0,    75,    73,    74,    84,
       0,    84,    85,    84,    84,    79,    53,   126,   127,   140,
     130,    98,   100,   134,   131,    88,    84,    87,    83,    82,
       0,    84,    84,    86,    51,    90,    89,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
    -223,  -223,  -223,    72,  -223,  -223,  -223,   149,   195,  -223,
    -223,  -223,  -223,     2,  -222,  -113,  -223,  -223,  -223,   151,
    -223,  -223,  -109,   190,  -223,  -221,  -223,  -147,  -195,  -189,
    -223,  -223,   -41,   189,   -92,  -188,  -159,  -117,  -223
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,   218,    30,    31,    32,   132,   100,   216,
     138,   101,    33,   263,   192,   125,    34,    35,    36,   115,
     186,    47,   144,   189,   224,   260,    48,   126,   169,   234,
     170,   235,    68,   116,    96,   172,   127,   162,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     112,   145,   146,    70,   152,   261,   166,   237,   167,   236,
      85,   239,   210,    86,   118,    49,   173,   197,   198,   202,
     206,   118,   245,   150,   151,    38,   221,    39,   313,   279,
      50,    51,   331,   255,    67,   291,   257,   177,   294,   280,
     257,    67,   113,    69,   104,   106,   107,   108,    54,   195,
     105,   114,   119,   201,   205,   121,   122,   282,    52,   119,
     124,   120,   121,   122,   123,    53,   314,   124,    55,    40,
     332,   312,   315,   178,   179,   300,   297,   298,   227,   232,
      41,   211,    42,   265,   266,   270,    56,    60,   325,   305,
     327,   243,   328,   329,   330,    87,   284,    57,   256,    88,
     182,   183,    58,   118,    59,   333,   257,   133,   134,   135,
     335,   336,     2,   118,   141,   258,     3,     4,   142,   269,
     118,     5,    61,     6,     7,     8,     9,    10,    11,    62,
     283,   136,    12,    13,    14,    63,   259,    64,    15,    16,
     137,   119,    65,   199,   121,   122,   200,    67,    17,   124,
      66,   119,   285,   203,   121,   122,   204,   309,   119,   124,
     267,   121,   122,   268,   119,   257,   124,   121,   122,    18,
      71,    72,   124,   163,   310,    73,    74,    76,    75,   306,
     307,   308,   316,    77,   154,   155,   156,   157,   158,   159,
     164,   165,    89,    78,    90,   311,   160,   161,    91,   154,
     155,   156,   157,   158,   159,   230,   231,    79,    80,    83,
     321,   160,   161,   154,   155,   156,   157,   158,   159,   119,
      81,   193,   121,   122,   194,   160,   161,   124,    43,    82,
      84,    44,    45,    94,   240,    46,   241,   252,    92,   253,
     242,    93,    95,   254,    97,    98,    99,   102,   103,   109,
     110,   111,   117,   128,   129,   130,   131,   139,   140,   147,
     148,   143,   149,   153,   174,   168,   176,   171,   180,   181,
     114,   185,   184,   188,   191,   208,   196,   118,   207,   212,
     209,   214,   215,   217,   219,   220,   113,   225,   223,   226,
     228,   229,   246,   238,   247,   248,   251,   250,   233,   244,
     262,   271,   273,   249,   264,   272,   274,   276,   275,   287,
     277,   296,   278,   281,   288,   289,   290,   295,   257,   292,
     317,   286,   293,   318,   213,   320,   175,   301,   322,   299,
     302,   304,   324,   334,   303,   319,   337,   222,   187,     0,
     323,   190,   326
};

static const yytype_int16 yycheck[] =
{
      92,   110,   111,    44,   117,   227,   123,   202,   125,   198,
      57,   206,   171,    60,    17,    60,   129,   164,   165,   166,
     167,    17,   210,   115,   116,     6,   185,     8,    11,    18,
       7,     3,    11,   221,    19,   256,    19,    17,   259,    28,
      19,    19,    10,    28,    85,    86,    87,    88,    60,   162,
      28,    19,    55,   166,   167,    58,    59,    60,    29,    55,
      63,    57,    58,    59,    60,    31,    49,    63,     3,    50,
      49,   292,   293,    53,    54,   270,   265,   266,   191,   196,
       6,   173,     8,   230,   231,   232,     3,    37,   309,   284,
     311,   208,   313,   314,   316,    60,   243,     3,    11,    64,
     141,   142,     3,    17,     3,   326,    19,    23,    24,    25,
     331,   332,     0,    17,    60,    28,     4,     5,    64,   232,
      17,     9,     3,    11,    12,    13,    14,    15,    16,    60,
     243,    47,    20,    21,    22,    60,    49,    60,    26,    27,
      56,    55,    60,    57,    58,    59,    60,    19,    36,    63,
      60,    55,   244,    57,    58,    59,    60,    11,    55,    63,
      57,    58,    59,    60,    55,    19,    63,    58,    59,    57,
      17,    31,    63,    28,    28,    31,     3,    60,     3,   288,
     289,   290,   295,    60,    39,    40,    41,    42,    43,    44,
      45,    46,    58,    34,    60,    49,    51,    52,    64,    39,
      40,    41,    42,    43,    44,    45,    46,    38,    17,     3,
     302,    51,    52,    39,    40,    41,    42,    43,    44,    55,
      35,    57,    58,    59,    60,    51,    52,    63,    57,    35,
       3,    60,    61,    30,    58,    64,    60,    58,    60,    60,
      64,    60,    32,    64,    60,    63,    60,    60,    60,    18,
      18,    18,    17,     3,    39,    29,    19,    17,    17,     3,
      60,    19,    60,     9,     6,    61,    18,    33,    60,    60,
      19,    35,    61,    48,    19,    18,    60,    17,    17,    60,
      31,     3,    58,    19,    18,    17,    10,     3,    60,     3,
      18,    28,     3,    28,     3,    18,     3,    18,    60,    60,
      19,    28,    31,    60,    60,    18,    18,    60,    18,     3,
      18,     3,    18,    18,    18,    18,    18,    17,    19,    60,
      18,   249,    60,    18,   175,    18,   131,    60,    18,    28,
      60,    28,    18,    18,    60,    60,   334,   186,   149,    -1,
      60,   151,    60
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    68,     0,     4,     5,     9,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    26,    27,    36,    57,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      81,    82,    83,    89,    93,    94,    95,   115,     6,     8,
      50,     6,     8,    57,    60,    61,    64,    98,   103,    60,
       7,     3,    29,    31,    60,     3,     3,     3,     3,     3,
      37,     3,    60,    60,    60,    60,    60,    19,   109,    28,
     109,    17,    31,    31,     3,     3,    60,    60,    34,    38,
      17,    35,    35,     3,     3,    57,    60,    60,    64,    58,
      60,    64,    60,    60,    30,    32,   111,    60,    63,    60,
      85,    88,    60,    60,   109,    28,   109,   109,   109,    18,
      18,    18,   111,    10,    19,    96,   110,    17,    17,    55,
      57,    58,    59,    60,    63,    92,   104,   113,     3,    39,
      29,    19,    84,    23,    24,    25,    47,    56,    87,    17,
      17,    60,    64,    19,    99,    99,    99,     3,    60,    60,
     111,   111,    92,     9,    39,    40,    41,    42,    43,    44,
      51,    52,   114,    28,    45,    46,   114,   114,    61,   105,
     107,    33,   112,    92,     6,    85,    18,    17,    53,    54,
      60,    60,   109,   109,    61,    35,    97,   110,    48,   100,
     100,    19,    91,    57,    60,    92,    60,   104,   104,    57,
      60,    92,   104,    57,    60,    92,   104,    17,    18,    31,
     113,   111,    60,    84,     3,    58,    86,    19,    80,    18,
      17,   113,    96,    60,   101,     3,     3,    92,    18,    28,
      45,    46,   114,    60,   106,   108,   106,   105,    28,   105,
      58,    60,    64,   114,    60,   112,     3,     3,    18,    60,
      18,     3,    58,    60,    64,   112,    11,    19,    28,    49,
     102,    91,    19,    90,    60,   104,   104,    57,    60,    92,
     104,    28,    18,    31,    18,    18,    60,    18,    18,    18,
      28,    18,    60,    92,   104,   111,    80,     3,    18,    18,
      18,   102,    60,    60,   102,    17,     3,   106,   106,    28,
     105,    60,    60,    60,    28,   105,    99,    99,    99,    11,
      28,    49,   102,    11,    49,   102,    92,    18,    18,    60,
      18,   111,    18,    60,    18,   102,    60,   102,   102,   102,
      91,    11,    49,   102,    18,   102,   102,    90
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
      94,    95,    95,    95,    95,    96,    96,    97,    97,    98,
      98,    98,    99,    99,    99,    99,   100,   100,   101,   101,
     101,   101,   101,   101,   102,   102,   102,   102,   102,   102,
     102,   103,   103,   103,   103,   103,   104,   105,   106,   107,
     107,   107,   107,   108,   108,   109,   109,   109,   109,   109,
     110,   110,   111,   111,   112,   112,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   114,   114,   114,   114,   114,   114,   114,   114,   115
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
       8,     2,     6,     8,     8,     0,     4,     0,     3,     5,
       5,     5,     0,     6,     6,     6,     0,     2,     2,     4,
       3,     3,     5,     5,     0,     3,     5,     4,     4,     6,
       6,     1,     2,     4,     4,     2,     2,     4,     4,     4,
       6,     4,     4,     1,     3,     0,     3,     5,     5,     3,
       0,     3,     0,     3,     0,     3,     3,     3,     5,     5,
       3,     3,     3,     3,     5,     5,     7,     7,     5,     5,
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
#line 1682 "yacc_sql.tab.c"
    break;

  case 22:
#line 189 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1690 "yacc_sql.tab.c"
    break;

  case 23:
#line 194 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1698 "yacc_sql.tab.c"
    break;

  case 24:
#line 200 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1706 "yacc_sql.tab.c"
    break;

  case 25:
#line 206 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1714 "yacc_sql.tab.c"
    break;

  case 26:
#line 212 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1722 "yacc_sql.tab.c"
    break;

  case 27:
#line 218 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1731 "yacc_sql.tab.c"
    break;

  case 28:
#line 224 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1739 "yacc_sql.tab.c"
    break;

  case 29:
#line 230 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1748 "yacc_sql.tab.c"
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
#line 1761 "yacc_sql.tab.c"
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
#line 1774 "yacc_sql.tab.c"
    break;

  case 33:
#line 256 "yacc_sql.y"
                                    {
		CreateIndex c_i;
		create_index_init_short(&c_i, (yyvsp[-1].string));
		create_index_list_append(&CONTEXT->ssql->sstr.create_index_list, &c_i);
		CONTEXT->index_length++;
	}
#line 1785 "yacc_sql.tab.c"
    break;

  case 34:
#line 266 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1794 "yacc_sql.tab.c"
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
#line 1806 "yacc_sql.tab.c"
    break;

  case 36:
#line 282 "yacc_sql.y"
                    {
		AttrInfo attribute;
		attr_info_init(&attribute, "null_field", BITMAPS, 4);
		create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
		CONTEXT->value_length++;
	}
#line 1817 "yacc_sql.tab.c"
    break;

  case 38:
#line 291 "yacc_sql.y"
                                   {    }
#line 1823 "yacc_sql.tab.c"
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
#line 1838 "yacc_sql.tab.c"
    break;

  case 40:
#line 307 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init_with_null(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1849 "yacc_sql.tab.c"
    break;

  case 41:
#line 315 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init_with_null(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1860 "yacc_sql.tab.c"
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
#line 1875 "yacc_sql.tab.c"
    break;

  case 43:
#line 335 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1881 "yacc_sql.tab.c"
    break;

  case 44:
#line 338 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1887 "yacc_sql.tab.c"
    break;

  case 45:
#line 339 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1893 "yacc_sql.tab.c"
    break;

  case 46:
#line 340 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1899 "yacc_sql.tab.c"
    break;

  case 47:
#line 341 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1905 "yacc_sql.tab.c"
    break;

  case 48:
#line 342 "yacc_sql.y"
                    { (yyval.number)=TEXT; }
#line 1911 "yacc_sql.tab.c"
    break;

  case 49:
#line 346 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1920 "yacc_sql.tab.c"
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
#line 1940 "yacc_sql.tab.c"
    break;

  case 52:
#line 372 "yacc_sql.y"
                                                        {
    }
#line 1947 "yacc_sql.tab.c"
    break;

  case 53:
#line 377 "yacc_sql.y"
    {
        for(int i=0;i<CONTEXT->value_length;++i) {
            CONTEXT->values_list[CONTEXT->values_size][i]=CONTEXT->values[i];
        }
        CONTEXT->values_length_list[CONTEXT->values_size]=CONTEXT->value_length;
        CONTEXT->value_length=0;
        CONTEXT->values_size+=1;
    }
#line 1960 "yacc_sql.tab.c"
    break;

  case 54:
#line 385 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1968 "yacc_sql.tab.c"
    break;

  case 55:
#line 390 "yacc_sql.y"
          {
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1976 "yacc_sql.tab.c"
    break;

  case 56:
#line 393 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1984 "yacc_sql.tab.c"
    break;

  case 57:
#line 396 "yacc_sql.y"
               {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		}
#line 1992 "yacc_sql.tab.c"
    break;

  case 58:
#line 399 "yacc_sql.y"
         {
		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 2001 "yacc_sql.tab.c"
    break;

  case 59:
#line 407 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 2013 "yacc_sql.tab.c"
    break;

  case 60:
#line 417 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 2025 "yacc_sql.tab.c"
    break;

  case 61:
#line 426 "yacc_sql.y"
                            {
	}
#line 2032 "yacc_sql.tab.c"
    break;

  case 62:
#line 429 "yacc_sql.y"
                {
		//聚合运算的语法解析
		CONTEXT->ssql->flag = SCF_AGGREGATE;
		aggregates_init(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].string),CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->condition_length = 0;
	}
#line 2043 "yacc_sql.tab.c"
    break;

  case 63:
#line 436 "yacc_sql.y"
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
#line 2063 "yacc_sql.tab.c"
    break;

  case 64:
#line 453 "yacc_sql.y"
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
#line 2084 "yacc_sql.tab.c"
    break;

  case 66:
#line 472 "yacc_sql.y"
                                       {
        selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
    }
#line 2092 "yacc_sql.tab.c"
    break;

  case 68:
#line 478 "yacc_sql.y"
                                  {

    }
#line 2100 "yacc_sql.tab.c"
    break;

  case 69:
#line 484 "yacc_sql.y"
                                                  {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,NULL,(yyvsp[-2].string),(yyvsp[-4].string));
	}
#line 2108 "yacc_sql.tab.c"
    break;

  case 70:
#line 487 "yacc_sql.y"
                                                      {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,NULL,"*",(yyvsp[-4].string));
	}
#line 2116 "yacc_sql.tab.c"
    break;

  case 71:
#line 490 "yacc_sql.y"
                                                        {
		aggregates_append_field_itoa(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].number),(yyvsp[-4].string));
	}
#line 2124 "yacc_sql.tab.c"
    break;

  case 73:
#line 496 "yacc_sql.y"
                                                         {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,NULL,(yyvsp[-2].string),(yyvsp[-4].string));
	}
#line 2132 "yacc_sql.tab.c"
    break;

  case 74:
#line 499 "yacc_sql.y"
                                                            {
		aggregates_append_field(&CONTEXT->ssql->sstr.aggregation,NULL,"*",(yyvsp[-4].string));
	}
#line 2140 "yacc_sql.tab.c"
    break;

  case 75:
#line 502 "yacc_sql.y"
                                                              {
		aggregates_append_field_itoa(&CONTEXT->ssql->sstr.aggregation,(yyvsp[-2].number),(yyvsp[-4].string));
	}
#line 2148 "yacc_sql.tab.c"
    break;

  case 77:
#line 507 "yacc_sql.y"
                          {
    }
#line 2155 "yacc_sql.tab.c"
    break;

  case 78:
#line 511 "yacc_sql.y"
                       {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-1].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2165 "yacc_sql.tab.c"
    break;

  case 79:
#line 516 "yacc_sql.y"
                                 {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2175 "yacc_sql.tab.c"
    break;

  case 80:
#line 521 "yacc_sql.y"
                              {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-2].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2185 "yacc_sql.tab.c"
    break;

  case 81:
#line 526 "yacc_sql.y"
                                {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-2].string), "desc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2195 "yacc_sql.tab.c"
    break;

  case 82:
#line 531 "yacc_sql.y"
                                     {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2205 "yacc_sql.tab.c"
    break;

  case 83:
#line 536 "yacc_sql.y"
                                      {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), "desc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2215 "yacc_sql.tab.c"
    break;

  case 85:
#line 544 "yacc_sql.y"
                               {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-1].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2225 "yacc_sql.tab.c"
    break;

  case 86:
#line 549 "yacc_sql.y"
                                      {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2235 "yacc_sql.tab.c"
    break;

  case 87:
#line 554 "yacc_sql.y"
                                   {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-2].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2245 "yacc_sql.tab.c"
    break;

  case 88:
#line 559 "yacc_sql.y"
                                    {
            OrderAttr attr;
            order_attr_init(&attr, NULL, (yyvsp[-2].string), "desc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2255 "yacc_sql.tab.c"
    break;

  case 89:
#line 564 "yacc_sql.y"
                                          {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), "asc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2265 "yacc_sql.tab.c"
    break;

  case 90:
#line 569 "yacc_sql.y"
                                           {
            OrderAttr attr;
            order_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string), "desc");
            selects_append_order_attr(&CONTEXT->ssql->sstr.selection, &attr);
        }
#line 2275 "yacc_sql.tab.c"
    break;

  case 91:
#line 577 "yacc_sql.y"
         {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2285 "yacc_sql.tab.c"
    break;

  case 92:
#line 582 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2295 "yacc_sql.tab.c"
    break;

  case 93:
#line 587 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2305 "yacc_sql.tab.c"
    break;

  case 94:
#line 592 "yacc_sql.y"
                                {
	        RelAttr attr;
	        relation_attr_init(&attr, (yyvsp[-3].string), "*");
	        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	    }
#line 2315 "yacc_sql.tab.c"
    break;

  case 95:
#line 597 "yacc_sql.y"
                              {

	}
#line 2323 "yacc_sql.tab.c"
    break;

  case 96:
#line 603 "yacc_sql.y"
        {
		//将condition的值存入，入栈
		CONTEXT->sub_selects_length++;
		CONTEXT->sub_condition_length[CONTEXT->sub_selects_length] = CONTEXT->condition_length;
	}
#line 2333 "yacc_sql.tab.c"
    break;

  case 97:
#line 612 "yacc_sql.y"
                {
		aggregates_init(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,(yyvsp[-1].string),
					CONTEXT->conditions + CONTEXT->sub_condition_length[CONTEXT->sub_selects_length], 
					CONTEXT->condition_length - CONTEXT->sub_condition_length[CONTEXT->sub_selects_length]);
		//printf("Condition start at %d\n",CONTEXT->sub_condition_length[CONTEXT->sub_selects_length]);
	}
#line 2344 "yacc_sql.tab.c"
    break;

  case 98:
#line 621 "yacc_sql.y"
                {	
			//selects_init(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection);
			selects_append_relation(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection, (yyvsp[-1].string));
			selects_append_conditions(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection, 
						CONTEXT->conditions + CONTEXT->sub_condition_length[CONTEXT->sub_selects_length],
						CONTEXT->condition_length - CONTEXT->sub_condition_length[CONTEXT->sub_selects_length]);
		}
#line 2356 "yacc_sql.tab.c"
    break;

  case 99:
#line 631 "yacc_sql.y"
                                   {
		aggregates_append_field(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,NULL,(yyvsp[-1].string),(yyvsp[-3].string));
	}
#line 2364 "yacc_sql.tab.c"
    break;

  case 100:
#line 634 "yacc_sql.y"
                                           {
		aggregates_append_field(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,(yyvsp[-3].string),(yyvsp[-1].string),(yyvsp[-5].string));
	}
#line 2372 "yacc_sql.tab.c"
    break;

  case 101:
#line 637 "yacc_sql.y"
                                       {
		aggregates_append_field(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,NULL,"*",(yyvsp[-3].string));
	}
#line 2380 "yacc_sql.tab.c"
    break;

  case 102:
#line 640 "yacc_sql.y"
                                         {
		aggregates_append_field_itoa(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation,(yyvsp[-1].number),(yyvsp[-3].string));
	}
#line 2388 "yacc_sql.tab.c"
    break;

  case 103:
#line 647 "yacc_sql.y"
       {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection, &attr);
		}
#line 2398 "yacc_sql.tab.c"
    break;

  case 104:
#line 652 "yacc_sql.y"
                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection, &attr);
		}
#line 2408 "yacc_sql.tab.c"
    break;

  case 106:
#line 661 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2420 "yacc_sql.tab.c"
    break;

  case 107:
#line 668 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2432 "yacc_sql.tab.c"
    break;

  case 108:
#line 675 "yacc_sql.y"
                                      {
  	        RelAttr attr;
  	        relation_attr_init(&attr, (yyvsp[-3].string), "*");
  	        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
  	}
#line 2442 "yacc_sql.tab.c"
    break;

  case 109:
#line 680 "yacc_sql.y"
                                    {
	}
#line 2449 "yacc_sql.tab.c"
    break;

  case 111:
#line 686 "yacc_sql.y"
                        {	
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
	}
#line 2457 "yacc_sql.tab.c"
    break;

  case 113:
#line 692 "yacc_sql.y"
                                     {	
	}
#line 2464 "yacc_sql.tab.c"
    break;

  case 115:
#line 697 "yacc_sql.y"
                                   {
	}
#line 2471 "yacc_sql.tab.c"
    break;

  case 116:
#line 701 "yacc_sql.y"
                           {}
#line 2477 "yacc_sql.tab.c"
    break;

  case 117:
#line 702 "yacc_sql.y"
                            {}
#line 2483 "yacc_sql.tab.c"
    break;

  case 118:
#line 703 "yacc_sql.y"
                                   {}
#line 2489 "yacc_sql.tab.c"
    break;

  case 119:
#line 704 "yacc_sql.y"
                                   {}
#line 2495 "yacc_sql.tab.c"
    break;

  case 120:
#line 705 "yacc_sql.y"
                               {}
#line 2501 "yacc_sql.tab.c"
    break;

  case 121:
#line 706 "yacc_sql.y"
                               {}
#line 2507 "yacc_sql.tab.c"
    break;

  case 122:
#line 707 "yacc_sql.y"
                                    {}
#line 2513 "yacc_sql.tab.c"
    break;

  case 123:
#line 709 "yacc_sql.y"
                {	
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length], 1, &left_attr, NULL, 0, NULL, right_value,NULL,NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			
		}
#line 2529 "yacc_sql.tab.c"
    break;

  case 124:
#line 720 "yacc_sql.y"
                                                       {
		//in subselect
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-4].string));
		Selects* in_select = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection;
		Condition condition;
		condition_init(&condition, IN, 1, &left_attr, NULL, 0, NULL, NULL,NULL,NULL);
		condition_set_inselect(&condition,in_select);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length],1);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2547 "yacc_sql.tab.c"
    break;

  case 125:
#line 733 "yacc_sql.y"
                                                          {
		//in subselect
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-4].string));
		Selects* in_select = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection;
		Condition condition;
		condition_init(&condition, NOT_IN, 1, &left_attr, NULL, 0, NULL, NULL,NULL,NULL);
		condition_set_inselect(&condition,in_select);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length],1);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2565 "yacc_sql.tab.c"
    break;

  case 126:
#line 746 "yacc_sql.y"
                                                              {
		//in subselect
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
		Selects* in_select = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection;
		Condition condition;
		condition_init(&condition, IN, 1, &left_attr, NULL, 0, NULL, NULL,NULL,NULL);
		condition_set_inselect(&condition,in_select);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length],1);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2583 "yacc_sql.tab.c"
    break;

  case 127:
#line 759 "yacc_sql.y"
                                                                 {
		//in subselect
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
		Selects* in_select = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].selection;
		Condition condition;
		condition_init(&condition, NOT_IN, 1, &left_attr, NULL, 0, NULL, NULL,NULL,NULL);
		condition_set_inselect(&condition,in_select);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length],1);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2601 "yacc_sql.tab.c"
    break;

  case 128:
#line 773 "yacc_sql.y"
        {
		//出栈
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-4].string));
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
#line 2621 "yacc_sql.tab.c"
    break;

  case 129:
#line 789 "yacc_sql.y"
        {
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));
		Aggregates* left_agg_value = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation;
		Condition condition;
		condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length],0,NULL,NULL,1,&right_attr,NULL,left_agg_value,NULL);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length],0);
		//aggregates_destroy(left_agg_value);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2638 "yacc_sql.tab.c"
    break;

  case 130:
#line 802 "yacc_sql.y"
        {
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
		Aggregates* right_agg_value = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation;
		Condition condition;
		condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length], 1, &left_attr, NULL, 0, NULL, NULL,NULL,right_agg_value);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length],0);
		//aggregates_destroy(right_agg_value);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2655 "yacc_sql.tab.c"
    break;

  case 131:
#line 815 "yacc_sql.y"
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
#line 2675 "yacc_sql.tab.c"
    break;

  case 132:
#line 830 "yacc_sql.y"
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
#line 2690 "yacc_sql.tab.c"
    break;

  case 133:
#line 840 "yacc_sql.y"
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
#line 2705 "yacc_sql.tab.c"
    break;

  case 134:
#line 851 "yacc_sql.y"
        {
		CONTEXT->condition_length = CONTEXT->sub_condition_length[CONTEXT->sub_selects_length];
		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
		Aggregates* left_agg_value = &CONTEXT->sub_selects[CONTEXT->sub_selects_length].aggregation;
		Condition condition;
		condition_init(&condition, CONTEXT->comp[--CONTEXT->comp_length],0,NULL,NULL,1,&right_attr,NULL,left_agg_value,NULL);
		query_stack_pop(&CONTEXT->sub_selects[CONTEXT->sub_selects_length],0);
		//aggregates_destroy(left_agg_value);
		CONTEXT->sub_selects_length--;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2722 "yacc_sql.tab.c"
    break;

  case 135:
#line 864 "yacc_sql.y"
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
#line 2746 "yacc_sql.tab.c"
    break;

  case 136:
#line 884 "yacc_sql.y"
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
#line 2770 "yacc_sql.tab.c"
    break;

  case 137:
#line 904 "yacc_sql.y"
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
#line 2796 "yacc_sql.tab.c"
    break;

  case 138:
#line 926 "yacc_sql.y"
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
#line 2821 "yacc_sql.tab.c"
    break;

  case 139:
#line 947 "yacc_sql.y"
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
#line 2846 "yacc_sql.tab.c"
    break;

  case 140:
#line 968 "yacc_sql.y"
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
#line 2869 "yacc_sql.tab.c"
    break;

  case 141:
#line 990 "yacc_sql.y"
             { CONTEXT->comp[CONTEXT->comp_length++] = EQUAL_TO; }
#line 2875 "yacc_sql.tab.c"
    break;

  case 142:
#line 991 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->comp_length++] = LESS_THAN; }
#line 2881 "yacc_sql.tab.c"
    break;

  case 143:
#line 992 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->comp_length++] = GREAT_THAN; }
#line 2887 "yacc_sql.tab.c"
    break;

  case 144:
#line 993 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->comp_length++] = LESS_EQUAL; }
#line 2893 "yacc_sql.tab.c"
    break;

  case 145:
#line 994 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->comp_length++] = GREAT_EQUAL; }
#line 2899 "yacc_sql.tab.c"
    break;

  case 146:
#line 995 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->comp_length++] = NOT_EQUAL; }
#line 2905 "yacc_sql.tab.c"
    break;

  case 147:
#line 996 "yacc_sql.y"
                 { CONTEXT->comp[CONTEXT->comp_length++] = IS_NULL; }
#line 2911 "yacc_sql.tab.c"
    break;

  case 148:
#line 997 "yacc_sql.y"
                    { CONTEXT->comp[CONTEXT->comp_length++] = IS_NOT_NULL; }
#line 2917 "yacc_sql.tab.c"
    break;

  case 149:
#line 1003 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2926 "yacc_sql.tab.c"
    break;


#line 2930 "yacc_sql.tab.c"

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
#line 1008 "yacc_sql.y"

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
