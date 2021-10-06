#include "scanner.h"
#include <spdlog/spdlog.h>
#include <string>
namespace lb_lexer
{
std::string
scanner::capture ()
{
  spdlog::debug ("capture: {}", this->buff);
  return this->buff;
  // auto b = chstream.rdbuf ();
  // off	  -	relative position to set the next pointer(s) to
  // way	  -	defines base position to apply the relative offset to.
  //    It can be one of the following constants:
  // which	-	defines whether the input sequences, the output
  //    sequence, or both are affected. It can be one or a combination of
  //    the following constants:
  // spdlog::info ("current = {}, start = {}", current, start);
  // auto count = current - start;
  // b->pubseekoff (-count, std::ios_base::cur, std::ios_base::out);
  // auto buffer = new char[count + 1];
  // std::memset (buffer, 0, count + 1);
  // b->sgetn (buffer, count);
  // b->pubseekoff (+count, std::ios_base::cur, std::ios_base::out);
  // auto str = std::string (buffer);
  // delete buffer;
  // return str;
}
char
scanner::advance ()
{
  col++;
  current++;
  char c = chstream.rdbuf ()->sbumpc ();
  if (EOF == c)
    {
      spdlog::trace ("Taken EOF", c);
      finished = true;
      return c;
    }
  buff.push_back (c);
  spdlog::trace ("Taken {}", c);

  return c;
}

char
scanner::prev ()
{
  if (buff.size ())
    {
      return buff.back ();
    }
  return '\0';
}
char
scanner::peek ()
{
  if (finished)
    return '\0';
  return chstream.rdbuf ()->sgetc ();
}
char
scanner::peek_next ()
{
  auto c = chstream.rdbuf ()->snextc ();
  if (c == std::char_traits<char>::eof ())
    {
      return '\0';
    }
  chstream.rdbuf ()->sungetc ();
  return c;
}
bool
scanner::is_word (char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}
bool
scanner::is_digit (char c)
{
  return c >= '0' && c <= '9';
}
bool
scanner::match (char expected)
{
  if (finished)
    return false;
  if (chstream.rdbuf ()->sgetc () != expected)
    return false;
  advance ();
  return true;
}
void
scanner::match_identifier ()
{
  while (is_digit (peek ()) || is_word (peek ()))
    {
      // spdlog::info ("March !");
      advance ();
    }
  std::string text = capture ();
  token_type type = token::from_string (text);
  if (type == token_type::UNKNOWN)
    {
      type = token_type::ID;
    }
  fast_yield (type);
}
void
scanner::match_number ()
{
  while (is_digit (peek ()))
    advance ();

  // Look for a fractional part.
  if (peek () == '.' || peek () == 'x' && is_digit (peek_next ()))
    {
      // Consume the "."
      advance ();

      while (is_digit (peek ()))
        advance ();
    }
  if (peek () == 'e' || peek () == 'E')
    {
      if (peek_next () == '-')
        {
          advance ();
        }
      if (is_digit (peek_next ()))
        {

          // Consume the "."
          advance ();

          while (is_digit (peek ()))
            advance ();
        }
    }
  yield (token (token_type::NUM, capture (), "", line, col));
}
void
scanner::match_char ()
{
  //读取，直到读到 "，并且前一个字符不是 '\'
  while (peek () != '\'' && !finished)
    {
      if (peek () == '\n')
        {
          col = 0;
          line++;
        }
      handle_escape ();
      advance ();
    }

  if (finished)
    {
      spdlog::error ("Unterminated char. at {}:{}", line, col);
      throw std::exception ();
    }

  // The closing ".
  advance ();
  int ignore = 1;
  auto value = capture (); //.substr(ignore, capture ().size() - ignore);
  yield (token (token_type::CHR, "", value, line, col));
}
void
scanner::match_string ()
{
  // 空串简单处理
  if (peek () == '"')
    {
      advance ();
      yield (token (token_type::STR, "", capture (), line, col));
      return;
    }
  // 【弃用】读取，直到读到 "，并且前一个字符不是 '\'
  //        !(prev () != '\\' && peek () == '"'
  // 这种方法在识别 "\\" 时会出错

  while (peek () != '"' && !finished)
    {
      if (peek () == '\n')
        {
          col = 0;
          line++;
        }
      handle_escape ();
      advance ();
    }

  if (finished)
    {
      spdlog::error ("Unterminated string. at {}:{}", line, col);
      throw std::exception ();
    }

  // The closing ".
  advance ();
  int ignore = 1;
  auto value = capture (); //.substr(ignore, capture ().size() - ignore);
  yield (token (token_type::STR, "", value, line, col));
}

void
scanner::handle_escape ()
{
  if (peek () == '\\')
    {
      switch (peek_next ())
        {
        case '\n': // 续行
          advance ();
          break;
          /* 八进制 */
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
          advance ();
          break;
        case 'a':  // Alert (bell, alarm)
        case 'b':  // Backspace
        case 'f':  // Form feed (new page)
        case 'n':  // New-line
        case 'r':  // Carriage return
        case 't':  // Horizontal tab
        case 'v':  // Vertical tab
        case '\'': // Single quotation mark
        case '\"': // Double quotation mark
        case '?':  // Question mark
        case '\\': // Backslash
          advance ();
          break;
        case '\0': /* End of string */
          spdlog::error ("Unterminated. Unexpected end of string. at {}:{}",
                         line, col);
          break;
        default: /* Escaped character like \ ^ : = */
          spdlog::error ("Unterminated. Escaped character invalid. at {}:{}",
                         line, col);
          break;
        }
    }
}

void
scanner::match_inline_comment ()
{
  while (peek () != '\n' && !finished)
    {
      if (peek () == '\n')
        {
          col = 0;
          line++;
        }
      advance ();
    }
  fast_yield (token_type::INLCOM);
  return;
}
void
scanner::match_preproc ()
{
  // 允许续行符号
  while (!(prev () != '\\' && peek () == '\n') && !finished)
    {
      if (peek () == '\n')
        {
          col = 0;
          line++;
        }
      advance ();
    }
  fast_yield (token_type::PREPROC);
  return;
}
void
scanner::match_block_comment ()
{
  while (!(peek () == '*' && peek_next () == '/') && !finished)
    {
      // spdlog::info ("p,pn = {},{}", peek (), peek_next ());
      if (peek () == '\n')
        {
          col = 0;
          line++;
        }
      advance ();
    }
  if (finished)
    {
      spdlog::error ("Unterminated block comment, at {}:{}", line, col);
      throw std::exception ();
    }
  advance ();
  advance ();
  fast_yield (token_type::BLKCOM);
}
void
scanner::fast_yield (token_type type)
{
  auto text = capture ();
  yield (token (type, text, "", line, col));
}

void
scanner::scan_token ()
{
  auto c = advance ();

  switch (c)
    {
    case EOF:
      spdlog::info ("EOF");
      finished = true;
      break;
    case '#':
      match_preproc ();
      break;
    case '(':
      fast_yield (token_type::PAR_L);
      break;
    case ')':
      fast_yield (token_type::PAR_R);
      break;
    case '{':
      fast_yield (token_type::CUR_L);
      break;
    case '}':
      fast_yield (token_type::CUR_R);
      break;
    case '[':
      fast_yield (token_type::BRA_L);
      break;
    case ']':
      fast_yield (token_type::BRA_R);
      break;
    case ',':
      fast_yield (token_type::COMMA);
      break;
    case '.':
      fast_yield (token_type::DOT);
      break;
    case '-':
      fast_yield (token_type::MINUS);
      break;
    case '+':
      fast_yield (token_type::PLUS);
      break;
    case ':':
      fast_yield (token_type::COLON);
      break;
    case ';':
      fast_yield (token_type::SEMIC);
      break;
    case '*':
      fast_yield (token_type::STAR);
      break;
    case '%':
      fast_yield (token_type::PERCT);
      break;
    case '?':
      fast_yield (token_type::QUEST);
        break;
    case '&':
      fast_yield (match ('&') ? token_type::AAND : token_type::AND);
      break;
    case '|':
      fast_yield (match ('|') ? token_type::OOR : token_type::OR);
      break;
    case '!':
      fast_yield (match ('=') ? token_type::BANGE : token_type::BANG);
      break;
    case '=':
      fast_yield (match ('=') ? token_type::EQUALE : token_type::EQUAL);
      break;
    case '<':
      fast_yield (match ('=') ? token_type::LESSE : token_type::LESS);
      break;
    case '>':
      fast_yield (match ('=') ? token_type::GREATE : token_type::GREAT);
      break;
    case '~':
      fast_yield (match ('=') ? token_type::TILDE : token_type::TILDE);
      break;
    case '^':
      fast_yield (match ('=') ? token_type::CARETE : token_type::CARET);
      break;
    case '/':
      if (match ('/'))
        {
          match_inline_comment ();
        }
      else if (match ('*'))
        {
          match_block_comment ();
        }
      else
        {
          fast_yield (token_type::SLASH);
        }
      break;
    case ' ':
    case '\r':
    case '\t':
      // Ignore whitespace.
      break;
    case '\n':
      col = 0;
      line++;
      break;
    case '\'':
      match_char ();
      break;
    case '"':
      match_string ();
      break;
    default:
      if (is_digit (c))
        match_number ();
      else if (is_word (c))
        match_identifier ();
      else
        {
          if (on_error (lexical_etype::UNEXPECTED_CHAR, line, col))
            {
              // try recover
            }
          else
            {
              throw std::exception ();
            }
        }

      break;
    }
}

void
scanner::scan ()
{
  // 修正
  line++;
  while (!finished)
    {
      start = current;
      buff.clear ();
      scan_token ();
    }
}

} // namespace lb_lexer