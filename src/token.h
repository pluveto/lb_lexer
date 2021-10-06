#pragma once
#include "token_type.h"
#include <string>
#define MAX_TOKEN_STR_SIZE (256)
namespace lb_lexer
{
class token
{
private:
  token_type type;
  std::string lexeme;
  std::string literal;
  size_t line;
  size_t col;

public:
  token (token_type type, std::string lexeme, std::string literal, size_t line,
         size_t col)
      : type (type), lexeme (lexeme), literal (literal), line (line),
        col (col){};
  token (token_type type, size_t line, size_t col)
      : type (type), line (line), col (col){};
  char *c_str ();  
  std::string get_type_str ();
  token_type get_type ();
  std::string get_lexeme ();
  std::string get_literal ();
  size_t get_line ();
  size_t get_col ();
  static token_type from_string (std::string s);

  ~token (){};
};

}