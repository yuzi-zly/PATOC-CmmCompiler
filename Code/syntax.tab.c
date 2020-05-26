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




/* Copy the first part of user declarations.  */
#line 1 "./syntax.y" /* yacc.c:339  */


    int yylex();
    void yyerror(const char * msg);
    struct Node * root;

    // #define YYDEBUG 1
    // int yydebug = 1;

    #include "lex.yy.c"

#line 78 "./syntax.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
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
    INT = 258,
    FLOAT = 259,
    SEMI = 260,
    COMMA = 261,
    ASSIGNOP = 262,
    RELOP = 263,
    PLUS = 264,
    MINUS = 265,
    STAR = 266,
    DIV = 267,
    AND = 268,
    OR = 269,
    DOT = 270,
    NOT = 271,
    TYPE = 272,
    LP = 273,
    RP = 274,
    LB = 275,
    RB = 276,
    LC = 277,
    RC = 278,
    STRUCT = 279,
    RETURN = 280,
    IF = 281,
    ELSE = 282,
    WHILE = 283,
    ID = 284,
    LOWER_THAN_ELSE = 285,
    LOWER_THAN_RP = 286,
    HIGHER_THAN_MINUS = 287
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "./syntax.y" /* yacc.c:355  */

        struct Node *ptr;

#line 155 "./syntax.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 186 "./syntax.tab.c" /* yacc.c:358  */

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   566

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  192

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    56,    56,    66,    72,    74,    81,    82,    88,    95,
     102,   103,   104,   105,   107,   112,   122,   127,   133,   142,
     148,   150,   155,   157,   165,   170,   179,   187,   194,   196,
     203,   209,   218,   228,   234,   236,   242,   243,   244,   245,
     246,   251,   258,   259,   260,   261,   262,   271,   282,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   303,   309,
     311,   318,   319,   320,   322,   327,   335,   340,   347,   348,
     352,   359,   360,   367,   368,   375,   376,   383,   384,   391,
     392,   399,   400,   407,   408,   415,   416,   423,   424,   430,
     431,   437,   438,   446,   447,   454,   462,   463,   470,   471,
     476,   481,   487,   494,   499
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "SEMI", "COMMA",
  "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV", "AND", "OR", "DOT",
  "NOT", "TYPE", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN",
  "IF", "ELSE", "WHILE", "ID", "LOWER_THAN_ELSE", "LOWER_THAN_RP",
  "HIGHER_THAN_MINUS", "$accept", "Program", "ExtDefList", "ExtDef",
  "ExtDecList", "Specifier", "StructSpecifier", "OptTag", "Tag", "VarDec",
  "FunDec", "VarList", "ParamDec", "CompSt", "StmtList", "Stmt", "DefList",
  "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
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
     285,   286,   287
};
# endif

#define YYPACT_NINF -78

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-78)))

#define YYTABLE_NINF -60

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     321,    13,   -78,    -4,    75,   -78,   321,     8,   -78,   -78,
      73,    74,   -78,   -78,   -78,   -78,   -78,    88,    69,    62,
      93,    99,   334,   -78,   -78,    95,   127,   -78,   -78,    55,
     -78,     7,    18,   102,    55,    45,   -78,    95,   117,   156,
     -78,   -78,   144,    28,   378,   160,   -78,   112,   164,   175,
     138,   116,   -78,   -78,   -78,   -78,   162,   -78,     0,   -78,
     -78,   -78,   134,   150,   154,   381,    14,    68,   158,   -78,
     166,   378,   410,   398,   170,   -78,    28,   -78,   -78,   -78,
     -78,   -78,   174,   167,    82,   -78,    82,     9,   471,   190,
     169,   427,   177,   194,   182,   210,    89,   -78,   -78,   -78,
     -78,   214,   230,   234,   250,   254,   270,   274,   290,    37,
     294,   513,   -78,   513,   -78,   183,   110,   310,   -78,   -78,
     -78,   122,   130,   -78,   -78,   314,   378,   346,   485,   378,
     351,   499,   137,   -78,   442,   186,   -78,   513,   -78,   546,
     -78,   375,   -78,   375,   -78,    82,   -78,    82,   -78,   539,
     -78,   526,   -78,   -78,     1,   456,   188,   195,   -78,   142,
      83,   198,   378,   200,   378,   -78,   378,   -78,   378,   -78,
     -78,   330,   -78,   -78,   -78,   -78,   -78,   -78,   378,   202,
     378,   209,   -78,   -78,   -78,   -78,   -78,   378,   -78,   378,
     -78,   -78
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    16,    22,     0,     2,     0,     0,    17,    11,
      23,     0,    19,     1,     3,    12,     7,    24,     0,    14,
       0,     0,     0,     6,     5,     0,     0,    10,     9,     0,
       8,     0,     0,     0,     0,     0,    27,     0,     0,    30,
      24,    15,     0,     0,    34,     0,    20,    66,     0,    64,
       0,     0,    18,    58,    28,    13,    31,    26,     0,    25,
     100,   101,     0,     0,     0,     0,     0,     0,    99,    40,
       0,    34,     0,     0,     0,    62,     0,    63,    61,    60,
      29,    89,     0,    99,    88,    91,    90,     0,     0,     0,
      99,     0,     0,     0,     0,     0,     0,    32,    33,    36,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    68,    69,    67,    65,     0,     0,     0,    39,    87,
      86,     0,     0,    42,    41,     0,     0,     0,     0,     0,
       0,     0,     0,    94,   103,     0,    71,    70,    77,    76,
      79,    78,    81,    80,    83,    82,    85,    84,    73,    72,
      75,    74,    98,    97,     0,     0,     0,     0,    45,     0,
       0,    55,     0,    52,     0,    57,     0,    54,     0,    38,
      93,     0,    92,    37,    96,    95,    44,    43,     0,    49,
       0,    46,    51,    48,   104,   102,    56,     0,    53,     0,
      50,    47
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -78,   -78,   203,   -78,   196,     4,   -78,   -78,   -78,    -2,
     -78,   184,   -78,    41,   151,   -77,   -13,   -78,   -25,   -78,
     -62,    70
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    18,    32,     8,    11,    12,    47,
      20,    38,    39,    69,    70,    71,    33,    34,    48,    49,
      72,   135
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      84,    86,    88,    91,     7,    19,   173,    51,    45,    15,
       7,   111,   113,    16,   118,    92,    44,     2,     9,    50,
      88,    53,   174,    19,     3,    10,    37,    88,   119,    45,
      46,   128,    93,   131,   134,    56,    40,    17,   152,   137,
     139,   141,   143,   145,   147,   149,   151,    40,   155,   161,
     163,   114,   165,   167,   134,   155,    43,    40,   -59,   -59,
     134,    30,    37,   155,    54,   -59,   153,    29,    25,    94,
      23,   -59,     2,   -59,    24,    13,    55,   -59,   -59,     3,
     -59,   -59,    26,   -59,   -59,   179,    95,   181,   177,   182,
     132,   183,    60,    61,    27,   -21,    21,   109,    28,    62,
      31,   186,   117,   188,   174,    63,    22,    82,   133,   134,
     190,   156,   191,    60,    61,    29,     2,    78,    83,    74,
      62,    79,   -59,     3,    40,    52,    63,   158,    82,   133,
      42,   159,    26,    60,    61,    81,    57,    60,    61,    83,
      62,   119,   169,    77,    62,    73,    63,   176,    82,   133,
      63,    85,    82,    60,    61,    87,   170,    60,    61,    83,
      62,   170,    58,    83,    62,    59,    63,    73,    82,    75,
      63,   112,    82,    60,    61,   115,    96,    60,    61,    83,
      62,    76,    26,    83,    62,   116,    63,   122,    82,    97,
      63,   121,    82,    60,    61,   127,   126,    60,    61,    83,
      62,   129,   119,    83,    62,   172,    63,   170,    82,    14,
      63,   130,    82,    60,    61,   136,   174,    60,    61,    83,
      62,    41,    98,    83,    62,   178,    63,   180,    82,   187,
      63,   138,    82,    60,    61,   140,   189,    60,    61,    83,
      62,   185,    80,    83,    62,     0,    63,     0,    82,     0,
      63,   142,    82,    60,    61,   144,     0,    60,    61,    83,
      62,     0,     0,    83,    62,     0,    63,     0,    82,     0,
      63,   146,    82,    60,    61,   148,     0,    60,    61,    83,
      62,     0,     0,    83,    62,     0,    63,     0,    82,     0,
      63,   150,    82,    60,    61,   154,     0,    60,    61,    83,
      62,     0,     0,    83,    62,     0,    63,     0,    82,     0,
      63,   157,    82,    60,    61,   160,     0,    60,    61,    83,
      62,    -4,     1,    83,    62,     0,    63,     0,    82,     0,
      63,   184,    82,    60,    61,    35,     0,     0,     2,    83,
      62,     0,     0,    83,     0,     3,    63,     0,    82,    60,
      61,     2,     0,    36,    60,    61,    62,     0,     3,    83,
       0,    62,    63,     0,    64,   162,     0,    63,    29,    64,
     166,    65,    66,    29,    67,    68,    65,    66,     0,    67,
      68,    60,    61,     0,    60,    61,   105,   106,    62,     0,
     109,    62,     0,     0,    63,   117,    64,    63,     0,    89,
      29,    60,    61,    65,    66,     0,    67,    68,    62,     0,
      90,    99,     0,     0,    63,   100,    82,   101,   102,   103,
     104,   105,   106,   107,   108,   109,     0,    83,   123,     0,
     110,     0,   124,     0,   101,   102,   103,   104,   105,   106,
     107,   108,   109,     0,     0,     0,     0,   125,   171,   101,
     102,   103,   104,   105,   106,   107,   108,   109,     0,     0,
       0,     0,   117,   101,   102,   103,   104,   105,   106,   107,
     108,   109,     0,     0,     0,     0,   117,   175,   101,   102,
     103,   104,   105,   106,   107,   108,   109,     0,     0,     0,
     120,   117,   101,   102,   103,   104,   105,   106,   107,   108,
     109,     0,     0,     0,   164,   117,   101,   102,   103,   104,
     105,   106,   107,   108,   109,     0,     0,     0,   168,   117,
     101,   102,   103,   104,   105,   106,   107,   108,   109,     0,
       0,     0,     0,   117,   102,   103,   104,   105,   106,   107,
       0,   109,     0,     0,     0,     0,   117,   102,   103,   104,
     105,   106,     0,     0,   109,   103,   104,   105,   106,   117,
       0,   109,     0,     0,     0,     0,   117
};

static const yytype_int16 yycheck[] =
{
      62,    63,    64,    65,     0,     7,     5,    32,     1,     1,
       6,    73,    74,     5,     5,     1,    29,    17,     5,     1,
      82,    34,    21,    25,    24,    29,    22,    89,    19,     1,
      23,    93,    18,    95,    96,    37,    29,    29,     1,   101,
     102,   103,   104,   105,   106,   107,   108,    29,   110,   126,
     127,    76,   129,   130,   116,   117,     1,    29,     3,     4,
     122,    20,    58,   125,    19,    10,    29,    22,     6,     1,
       1,    16,    17,    18,     5,     0,    35,    22,    23,    24,
      25,    26,    20,    28,    29,   162,    18,   164,     5,   166,
       1,   168,     3,     4,     1,    22,    22,    15,     5,    10,
       1,   178,    20,   180,    21,    16,    18,    18,    19,   171,
     187,     1,   189,     3,     4,    22,    17,     1,    29,     7,
      10,     5,    23,    24,    29,    23,    16,     5,    18,    19,
       3,     1,    20,     3,     4,     1,    19,     3,     4,    29,
      10,    19,     5,     5,    10,     7,    16,     5,    18,    19,
      16,     1,    18,     3,     4,     1,    19,     3,     4,    29,
      10,    19,     6,    29,    10,    21,    16,     7,    18,     5,
      16,     1,    18,     3,     4,     1,    18,     3,     4,    29,
      10,     6,    20,    29,    10,    18,    16,    18,    18,    23,
      16,     1,    18,     3,     4,     1,    19,     3,     4,    29,
      10,    19,    19,    29,    10,    19,    16,    19,    18,     6,
      16,     1,    18,     3,     4,     1,    21,     3,     4,    29,
      10,    25,    71,    29,    10,    27,    16,    27,    18,    27,
      16,     1,    18,     3,     4,     1,    27,     3,     4,    29,
      10,   171,    58,    29,    10,    -1,    16,    -1,    18,    -1,
      16,     1,    18,     3,     4,     1,    -1,     3,     4,    29,
      10,    -1,    -1,    29,    10,    -1,    16,    -1,    18,    -1,
      16,     1,    18,     3,     4,     1,    -1,     3,     4,    29,
      10,    -1,    -1,    29,    10,    -1,    16,    -1,    18,    -1,
      16,     1,    18,     3,     4,     1,    -1,     3,     4,    29,
      10,    -1,    -1,    29,    10,    -1,    16,    -1,    18,    -1,
      16,     1,    18,     3,     4,     1,    -1,     3,     4,    29,
      10,     0,     1,    29,    10,    -1,    16,    -1,    18,    -1,
      16,     1,    18,     3,     4,     1,    -1,    -1,    17,    29,
      10,    -1,    -1,    29,    -1,    24,    16,    -1,    18,     3,
       4,    17,    -1,    19,     3,     4,    10,    -1,    24,    29,
      -1,    10,    16,    -1,    18,    19,    -1,    16,    22,    18,
      19,    25,    26,    22,    28,    29,    25,    26,    -1,    28,
      29,     3,     4,    -1,     3,     4,    11,    12,    10,    -1,
      15,    10,    -1,    -1,    16,    20,    18,    16,    -1,    18,
      22,     3,     4,    25,    26,    -1,    28,    29,    10,    -1,
      29,     1,    -1,    -1,    16,     5,    18,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    29,     1,    -1,
      20,    -1,     5,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    20,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    20,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    20,    21,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    -1,
      19,    20,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    -1,    19,    20,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    -1,    19,    20,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    -1,    -1,    20,     8,     9,    10,    11,    12,    13,
      -1,    15,    -1,    -1,    -1,    -1,    20,     8,     9,    10,
      11,    12,    -1,    -1,    15,     9,    10,    11,    12,    20,
      -1,    15,    -1,    -1,    -1,    -1,    20
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    17,    24,    34,    35,    36,    38,    39,     5,
      29,    40,    41,     0,    35,     1,     5,    29,    37,    42,
      43,    22,    18,     1,     5,     6,    20,     1,     5,    22,
      46,     1,    38,    49,    50,     1,    19,    38,    44,    45,
      29,    37,     3,     1,    49,     1,    23,    42,    51,    52,
       1,    51,    23,    49,    19,    46,    42,    19,     6,    21,
       3,     4,    10,    16,    18,    25,    26,    28,    29,    46,
      47,    48,    53,     7,     7,     5,     6,     5,     1,     5,
      44,     1,    18,    29,    53,     1,    53,     1,    53,    18,
      29,    53,     1,    18,     1,    18,    18,    23,    47,     1,
       5,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      20,    53,     1,    53,    51,     1,    18,    20,     5,    19,
      19,     1,    18,     1,     5,    20,    19,     1,    53,    19,
       1,    53,     1,    19,    53,    54,     1,    53,     1,    53,
       1,    53,     1,    53,     1,    53,     1,    53,     1,    53,
       1,    53,     1,    29,     1,    53,     1,     1,     5,     1,
       1,    48,    19,    48,    19,    48,    19,    48,    19,     5,
      19,     6,    19,     5,    21,    21,     5,     5,    27,    48,
      27,    48,    48,    48,     1,    54,    48,    27,    48,    27,
      48,    48
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    36,    36,    36,    36,
      36,    36,    36,    36,    37,    37,    38,    38,    39,    39,
      39,    40,    40,    41,    42,    42,    43,    43,    43,    44,
      44,    45,    46,    47,    47,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,    49,    49,
      50,    50,    50,    50,    51,    51,    52,    52,    52,    52,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    54,    54,    54
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     3,     2,     3,     3,
       3,     2,     2,     5,     1,     3,     1,     1,     5,     2,
       5,     1,     0,     1,     1,     4,     4,     3,     4,     3,
       1,     2,     4,     2,     0,     2,     2,     4,     4,     3,
       1,     3,     3,     5,     5,     4,     5,     7,     5,     5,
       7,     5,     4,     6,     4,     4,     6,     4,     2,     0,
       3,     3,     3,     3,     1,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     4,     4,     3,     4,     4,     3,     3,     1,
       1,     1,     3,     1,     3
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 56 "./syntax.y" /* yacc.c:1646  */
    {
                if((yyvsp[0].ptr) == NULL){
                    (yyval.ptr) = Create("Program",yylineno,1);
                }
                else 
                    (yyval.ptr) = Create("Program",(yylsp[0]).first_line,1);
                AddNode((yyval.ptr),(yyvsp[0].ptr));
                root = (yyval.ptr);
            }
#line 1569 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 66 "./syntax.y" /* yacc.c:1646  */
    {
                    (yyval.ptr) = Create("ExtDefList",(yylsp[-1]).first_line,1);
                    AddNode((yyval.ptr),(yyvsp[-1].ptr));
                    AddNode((yyval.ptr),(yyvsp[0].ptr));
                    root = (yyval.ptr);
                }
#line 1580 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 72 "./syntax.y" /* yacc.c:1646  */
    { (yyval.ptr) = NULL; }
#line 1586 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 74 "./syntax.y" /* yacc.c:1646  */
    {
                (yyval.ptr) = Create("ExtDef",(yylsp[-2]).first_line,1);
                AddNode((yyval.ptr),(yyvsp[-2].ptr));
                AddNode((yyval.ptr),(yyvsp[-1].ptr));
                AddNode((yyval.ptr),(yyvsp[0].ptr));
                root = (yyval.ptr);
            }
#line 1598 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 81 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0;}
#line 1604 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 82 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("ExtDef",(yylsp[-1]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 1615 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 88 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("ExtDef",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 1627 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 95 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("ExtDef",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 1639 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 102 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0;}
#line 1645 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 103 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 1651 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 104 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 1657 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 105 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 1663 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 107 "./syntax.y" /* yacc.c:1646  */
    {
                    (yyval.ptr) = Create("ExtDecList",(yylsp[0]).first_line,1);
                    AddNode((yyval.ptr),(yyvsp[0].ptr));
                    root = (yyval.ptr);
                }
#line 1673 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 112 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("ExtDecList",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 1685 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 122 "./syntax.y" /* yacc.c:1646  */
    {
                (yyval.ptr) = Create("Specifier",(yylsp[0]).first_line,1);
                AddNode((yyval.ptr),(yyvsp[0].ptr));
                root = (yyval.ptr);
            }
#line 1695 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 127 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Specifier",(yylsp[0]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 1705 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 133 "./syntax.y" /* yacc.c:1646  */
    {
                        (yyval.ptr) = Create("StructSpecifier",(yylsp[-4]).first_line,1);
                        AddNode((yyval.ptr),(yyvsp[-4].ptr));
                        AddNode((yyval.ptr),(yyvsp[-3].ptr));
                        AddNode((yyval.ptr),(yyvsp[-2].ptr));
                        AddNode((yyval.ptr),(yyvsp[-1].ptr));
                        AddNode((yyval.ptr),(yyvsp[0].ptr));
                        root = (yyval.ptr);
                    }
#line 1719 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 142 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("StructSpecifier",(yylsp[-1]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 1730 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 148 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 1736 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 150 "./syntax.y" /* yacc.c:1646  */
    {
                (yyval.ptr) = Create("OptTag",(yylsp[0]).first_line,1);
                AddNode((yyval.ptr),(yyvsp[0].ptr));
                root = (yyval.ptr);
            }
#line 1746 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 155 "./syntax.y" /* yacc.c:1646  */
    { (yyval.ptr) = NULL; }
#line 1752 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 157 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Tag",(yylsp[0]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 1762 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 165 "./syntax.y" /* yacc.c:1646  */
    {
                (yyval.ptr) = Create("VarDec",(yylsp[0]).first_line,1);
                AddNode((yyval.ptr),(yyvsp[0].ptr));
                root = (yyval.ptr);
            }
#line 1772 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 170 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("VarDec",(yylsp[-3]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-3].ptr));
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 1785 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 179 "./syntax.y" /* yacc.c:1646  */
    {
                (yyval.ptr) = Create("FunDec",(yylsp[-3]).first_line,1);
                AddNode((yyval.ptr),(yyvsp[-3].ptr));
                AddNode((yyval.ptr),(yyvsp[-2].ptr));
                AddNode((yyval.ptr),(yyvsp[-1].ptr));
                AddNode((yyval.ptr),(yyvsp[0].ptr));
                root = (yyval.ptr);
            }
#line 1798 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 187 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("FunDec",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 1810 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 194 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 1816 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 196 "./syntax.y" /* yacc.c:1646  */
    {
                (yyval.ptr) = Create("VarList",(yylsp[-2]).first_line,1);
                AddNode((yyval.ptr),(yyvsp[-2].ptr));
                AddNode((yyval.ptr),(yyvsp[-1].ptr));
                AddNode((yyval.ptr),(yyvsp[0].ptr));
                root = (yyval.ptr);
            }
#line 1828 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 203 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("VarList",(yylsp[0]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 1838 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 209 "./syntax.y" /* yacc.c:1646  */
    {
                (yyval.ptr) = Create("ParamDec",(yylsp[-1]).first_line,1);
                AddNode((yyval.ptr),(yyvsp[-1].ptr));
                AddNode((yyval.ptr),(yyvsp[0].ptr));
                root = (yyval.ptr);
            }
#line 1849 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 218 "./syntax.y" /* yacc.c:1646  */
    {
                (yyval.ptr) = Create("CompSt",(yylsp[-3]).first_line,1);
                AddNode((yyval.ptr),(yyvsp[-3].ptr));
                AddNode((yyval.ptr),(yyvsp[-2].ptr));
                AddNode((yyval.ptr),(yyvsp[-1].ptr));
                AddNode((yyval.ptr),(yyvsp[0].ptr));
                root = (yyval.ptr);
            }
#line 1862 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 228 "./syntax.y" /* yacc.c:1646  */
    {
                (yyval.ptr) = Create("StmtList",(yylsp[-1]).first_line,1);
                AddNode((yyval.ptr),(yyvsp[-1].ptr));
                AddNode((yyval.ptr),(yyvsp[0].ptr));
                root = (yyval.ptr);
            }
#line 1873 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 234 "./syntax.y" /* yacc.c:1646  */
    { (yyval.ptr) = NULL; }
#line 1879 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 236 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Stmt",(yylsp[-1]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 1890 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 242 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 1896 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 243 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 1902 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 244 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 1908 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 245 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 1914 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 246 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Stmt",(yylsp[0]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 1924 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 251 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Stmt",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 1936 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 258 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 1942 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 259 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 1948 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 260 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 1954 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 261 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 1960 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 262 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Stmt",(yylsp[-4]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-4].ptr));
            AddNode((yyval.ptr),(yyvsp[-3].ptr));
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 1974 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 271 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Stmt",(yylsp[-6]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-6].ptr));
            AddNode((yyval.ptr),(yyvsp[-5].ptr));
            AddNode((yyval.ptr),(yyvsp[-4].ptr));
            AddNode((yyval.ptr),(yyvsp[-3].ptr));
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 1990 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 282 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Stmt",(yylsp[-4]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-4].ptr));
            AddNode((yyval.ptr),(yyvsp[-3].ptr));
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2004 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 291 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 2010 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 292 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 2016 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 293 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 2022 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 294 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 2028 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 295 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 2034 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 296 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 2040 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 297 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 2046 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 298 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 2052 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 299 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 2058 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 303 "./syntax.y" /* yacc.c:1646  */
    {
                (yyval.ptr) = Create("DefList",(yylsp[-1]).first_line,1);
                AddNode((yyval.ptr),(yyvsp[-1].ptr));
                AddNode((yyval.ptr),(yyvsp[0].ptr));
                root = (yyval.ptr);
            }
#line 2069 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 309 "./syntax.y" /* yacc.c:1646  */
    { (yyval.ptr) = NULL; }
#line 2075 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 311 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Def",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2087 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 318 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 2093 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 319 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 2099 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 320 "./syntax.y" /* yacc.c:1646  */
    {print_flag = 0; }
#line 2105 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 322 "./syntax.y" /* yacc.c:1646  */
    {
                (yyval.ptr) = Create("DecList",(yylsp[0]).first_line,1);
                AddNode((yyval.ptr),(yyvsp[0].ptr));
                root = (yyval.ptr);
            }
#line 2115 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 327 "./syntax.y" /* yacc.c:1646  */
    {
                (yyval.ptr) = Create("DecList",(yylsp[-2]).first_line,1);
                AddNode((yyval.ptr),(yyvsp[-2].ptr));
                AddNode((yyval.ptr),(yyvsp[-1].ptr));
                AddNode((yyval.ptr),(yyvsp[0].ptr));
                root = (yyval.ptr);
        }
#line 2127 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 335 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Dec",(yylsp[0]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2137 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 340 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Dec",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2149 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 347 "./syntax.y" /* yacc.c:1646  */
    {print_flag = 0;}
#line 2155 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 348 "./syntax.y" /* yacc.c:1646  */
    {print_flag = 0;}
#line 2161 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 352 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2173 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 359 "./syntax.y" /* yacc.c:1646  */
    {print_flag = 0;}
#line 2179 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 360 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2191 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 367 "./syntax.y" /* yacc.c:1646  */
    {print_flag = 0;}
#line 2197 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 368 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2209 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 375 "./syntax.y" /* yacc.c:1646  */
    {print_flag = 0;}
#line 2215 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 376 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2227 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 383 "./syntax.y" /* yacc.c:1646  */
    {print_flag = 0;}
#line 2233 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 384 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2245 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 391 "./syntax.y" /* yacc.c:1646  */
    {print_flag = 0;}
#line 2251 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 392 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2263 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 399 "./syntax.y" /* yacc.c:1646  */
    {print_flag = 0;}
#line 2269 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 400 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2281 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 407 "./syntax.y" /* yacc.c:1646  */
    {print_flag = 0;}
#line 2287 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 408 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2299 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 415 "./syntax.y" /* yacc.c:1646  */
    {print_flag = 0;}
#line 2305 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 416 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2317 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 423 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 2323 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 424 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[-1]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2334 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 430 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0;}
#line 2340 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 431 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[-1]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2351 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 437 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 2357 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 438 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[-3]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-3].ptr));
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2370 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 446 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 2376 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 447 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2388 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 454 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[-3]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-3].ptr));
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2401 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 462 "./syntax.y" /* yacc.c:1646  */
    { print_flag = 0; }
#line 2407 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 463 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2419 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 470 "./syntax.y" /* yacc.c:1646  */
    {print_flag = 0;}
#line 2425 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 471 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[0]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2435 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 476 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[0]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2445 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 481 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Exp",(yylsp[0]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2455 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 487 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Args",(yylsp[-2]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[-2].ptr));
            AddNode((yyval.ptr),(yyvsp[-1].ptr));
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root =(yyval.ptr);
        }
#line 2467 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 494 "./syntax.y" /* yacc.c:1646  */
    {
            (yyval.ptr) = Create("Args",(yylsp[0]).first_line,1);
            AddNode((yyval.ptr),(yyvsp[0].ptr));
            root = (yyval.ptr);
        }
#line 2477 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 499 "./syntax.y" /* yacc.c:1646  */
    {print_flag = 0;}
#line 2483 "./syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2487 "./syntax.tab.c" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
#line 502 "./syntax.y" /* yacc.c:1906  */



void yyerror(const char* msg){
    fprintf(stderr, "Error type B at Line %d: %s.\n",yylineno,msg);
    print_flag = 0;
}


