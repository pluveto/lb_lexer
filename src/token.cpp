#include "token.h"
#include "stdio.h"
#include <cstdlib>
#include <map>
#include <spdlog/spdlog.h>
namespace lb_lexer
{
token_type
token::from_string (std::string s)
{
  std::map<std::string, token_type> cvt_map = {
    { "auto", token_type::AUTO },
    { "break", token_type::BREAK },
    { "case", token_type::CASE },
    { "char", token_type::CHAR },
    { "const", token_type::CONST },
    { "continue", token_type::CONTINUE },
    { "default", token_type::DEFAULT },
    { "do", token_type::DO },
    { "double", token_type::DOUBLE },
    { "else", token_type::ELSE },
    { "enum", token_type::ENUM },
    { "extern", token_type::EXTERN },
    { "float", token_type::FLOAT },
    { "for", token_type::FOR },
    { "goto", token_type::GOTO },
    { "if", token_type::IF },
    { "inline", token_type::INLINE },
    { "int", token_type::INT },
    { "long", token_type::LONG },
    { "register", token_type::REGISTER },
    { "restrict", token_type::RESTRICT },
    { "return", token_type::RETURN },
    { "short", token_type::SHORT },
    { "signed", token_type::SIGNED },
    { "sizeof", token_type::SIZEOF },
    { "static", token_type::STATIC },
    { "struct", token_type::STRUCT },
    { "switch", token_type::SWITCH },
    { "typedef", token_type::TYPEDEF },
    { "union", token_type::UNION },
    { "unsigned", token_type::UNSIGNED },
    { "void", token_type::VOID },
    { "volatile", token_type::VOLATILE },
    { "while", token_type::WHILE },
    { "_Alignas", token_type::_ALIGNAS },
    { "_Alignof", token_type::_ALIGNOF },
    { "_Atomic", token_type::_ATOMIC },
    { "_Bool", token_type::_BOOL },
    { "_Complex", token_type::_COMPLEX },
    { "_Decimal128", token_type::_DECIMAL128 },
    { "_Decimal32", token_type::_DECIMAL32 },
    { "_Decimal64", token_type::_DECIMAL64 },
    { "_Generic", token_type::_GENERIC },
    { "_Imaginary", token_type::_IMAGINARY },
    { "_Noreturn", token_type::_NORETURN },
    { "_Static_assert", token_type::_STATIC_ASSERT },
    { "_Thread_local", token_type::_THREAD_LOCAL },
  };

  auto it = cvt_map.find (s);
  return it == cvt_map.end () ? token_type::UNKNOWN : it->second;
}

const char *
token_type_to_str (token_type t)
{

  const std::map<lb_lexer::token_type, const char *> cvt_map{
    { token_type::PAR_L, "PAR_L" },
    { token_type::PAR_R, "PAR_R" },
    { token_type::BRA_L, "BRA_L" },
    { token_type::BRA_R, "BRA_R" },
    { token_type::CUR_L, "CUR_L" },
    { token_type::CUR_R, "CUR_R" },
    { token_type::COMMA, "COMMA" },
    { token_type::DOT, "DOT" },
    { token_type::MINUS, "MINUS" },
    { token_type::PLUS, "PLUS" },
    { token_type::SEMIC, "SEMIC" },
    { token_type::SLASH, "SLASH" },
    { token_type::STAR, "STAR" },
    { token_type::COLON, "COLON" },
    { token_type::PERCT, "PERCT" },
    { token_type::QUEST, "QUEST" },

    { token_type::INLCOM, "INLCOM" },
    { token_type::BLKCOM, "BLKCOM" },
    { token_type::PREPROC, "PREPROC" },

    { token_type::BANG, "BANG" },
    { token_type::BANGE, "BANGE" },
    { token_type::EQUAL, "EQUAL" },
    { token_type::EQUALE, "EQUALE" },
    { token_type::GREAT, "GREAT" },
    { token_type::GREATE, "GREATE" },
    { token_type::LESS, "LESS" },
    { token_type::LESSE, "LESSE" },
    { token_type::AND, "AND" },
    { token_type::AAND, "AAND" },
    { token_type::CARET, "CARET" },
    { token_type::CARETE, "CARETE" },
    { token_type::TILDE, "TILDE" },
    { token_type::TILDEE, "TILDEE" },
    { token_type::OR, "OR" },
    { token_type::OOR, "OOR" },
    { token_type::PLUSE, "PLUSE" },
    { token_type::MINUSE, "MINUSE" },
    { token_type::MULTPE, "MULTPE" },
    { token_type::DIVE, "DIVE" },

    { token_type::ID, "ID" },
    { token_type::CHR, "CHR" },
    { token_type::STR, "STR" },
    { token_type::NUM, "NUM" },

    { token_type::AUTO, "AUTO" },
    { token_type::BREAK, "BREAK" },
    { token_type::CASE, "CASE" },
    { token_type::CHAR, "CHAR" },
    { token_type::CONST, "CONST" },
    { token_type::CONTINUE, "CONTINUE" },
    { token_type::DEFAULT, "DEFAULT" },
    { token_type::DO, "DO" },
    { token_type::DOUBLE, "DOUBLE" },
    { token_type::ELSE, "ELSE" },
    { token_type::ENUM, "ENUM" },
    { token_type::EXTERN, "EXTERN" },
    { token_type::FLOAT, "FLOAT" },
    { token_type::FOR, "FOR" },
    { token_type::GOTO, "GOTO" },
    { token_type::IF, "IF" },
    { token_type::INLINE, "INLINE" },
    { token_type::INT, "INT" },
    { token_type::LONG, "LONG" },
    { token_type::REGISTER, "REGISTER" },
    { token_type::RESTRICT, "RESTRICT" },
    { token_type::RETURN, "RETURN" },
    { token_type::SHORT, "SHORT" },
    { token_type::SIGNED, "SIGNED" },
    { token_type::SIZEOF, "SIZEOF" },
    { token_type::STATIC, "STATIC" },
    { token_type::STRUCT, "STRUCT" },
    { token_type::SWITCH, "SWITCH" },
    { token_type::TYPEDEF, "TYPEDEF" },
    { token_type::UNION, "UNION" },
    { token_type::UNSIGNED, "UNSIGNED" },
    { token_type::VOID, "VOID" },
    { token_type::VOLATILE, "VOLATILE" },
    { token_type::WHILE, "WHILE" },
    { token_type::_ALIGNAS, "_ALIGNAS" },
    { token_type::_ALIGNOF, "_ALIGNOF" },
    { token_type::_ATOMIC, "_ATOMIC" },
    { token_type::_BOOL, "_BOOL" },
    { token_type::_COMPLEX, "_COMPLEX" },
    { token_type::_DECIMAL128, "_DECIMAL128" },
    { token_type::_DECIMAL32, "_DECIMAL32" },
    { token_type::_DECIMAL64, "_DECIMAL64" },
    { token_type::_GENERIC, "_GENERIC" },
    { token_type::_IMAGINARY, "_IMAGINARY" },
    { token_type::_NORETURN, "_NORETURN" },
    { token_type::_STATIC_ASSERT, "_STATIC_ASSER" },
    { token_type::_THREAD_LOCAL, "_THREAD_LOCAL" },
    { token_type::LINE_BREAK, "LINE_BREAK" },
    { token_type::UNKNOWN, "UNKNOWN" }
  };
  auto it = cvt_map.find (t);
  return it == cvt_map.end () ? "Out of range" : it->second;
}
std::string token::get_type_str (){
  return std::string(token_type_to_str (this->type));
}
char *
token::c_str ()
{
  spdlog::info("to str lexeme={}", lexeme);
  char *s = (char *)malloc (MAX_TOKEN_STR_SIZE * sizeof (char));
  switch (this->type)
    {
    case token_type::ID:
      {

        snprintf (s, MAX_TOKEN_STR_SIZE, "%s text=%s at %llu:%llu",
                  token_type_to_str (this->type), this->lexeme.c_str(), this->line,
                  this->col);
      }
      break;

    default:
      {
        snprintf (s, MAX_TOKEN_STR_SIZE, "%s at %llu:%llu",
                  token_type_to_str (this->type), this->line, this->col);
        break;
      }
    }
  return s;
}


  token_type token::get_type (){return type;}
  std::string token::get_lexeme (){return lexeme;}
  std::string token::get_literal (){return literal;}
  size_t token::get_line (){return line;}
  size_t token::get_col (){return col;}

}