namespace lb_lexer
{
enum token_type
{
  PAR_L, // (
  PAR_R, // )
  BRA_L, // [
  BRA_R, // ]
  CUR_L, // {
  CUR_R, // }
  COMMA, // ,
  DOT,   // .
  PLUS,  // +
  SEMIC, // ;
  SLASH, // /
  STAR,  // *
  COLON, // :
  PERCT, // %
  QUEST, // %

  INLCOM, // 行内注释 //
  BLKCOM, // 块注释 /* ... */

  PREPROC, // 预处理指令

  MINUS,  // -
  PTMEM,  // -> 指向成员
  BANG,   // !
  BANGE,  // !=
  EQUAL,  // =
  EQUALE, // ==
  GREAT,  // >
  GREATE, // >=
  LESS,   // <
  LESSE,  // <=
  CARET,  // ^
  CARETE, // ^=
  TILDE,  // ~
  TILDEE, // ~=
  AND,    // &
  AAND,   // &&
  OR,     // |
  OOR,    // ||
  PLUSE,  // +=
  MINUSE, // -=
  MULTPE, // *=
  DIVE,   // /=

  // 字面量
  ID,  // identifier
  CHR, // char 'x'
  STR, // string
  NUM, // number

  // 关键字.
  AUTO,
  BREAK,
  CASE,
  CHAR,
  CONST,
  CONTINUE,
  DEFAULT,
  DO,
  DOUBLE,
  ELSE,
  ENUM,
  EXTERN,

  FLOAT,
  FOR,
  GOTO,
  IF,
  INLINE,
  INT,
  LONG,
  REGISTER,
  RESTRICT,
  RETURN,
  SHORT,

  SIGNED,
  SIZEOF,
  STATIC,
  STRUCT,
  SWITCH,
  TYPEDEF,
  UNION,
  UNSIGNED,
  VOID,
  VOLATILE,
  WHILE,

  _ALIGNAS,
  _ALIGNOF,
  _ATOMIC,
  _BOOL,
  _COMPLEX,
  _DECIMAL128,
  _DECIMAL32,
  _DECIMAL64,
  _GENERIC,
  _IMAGINARY,
  _NORETURN,
  _STATIC_ASSERT,
  _THREAD_LOCAL,

  END_OF_FILE,
  LINE_BREAK,
  UNKNOWN
};
}