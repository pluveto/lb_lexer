#include "app.h"

#include <fmt/core.h>
#include <fstream>
#include <spdlog/spdlog.h>
namespace lb_lexer
{

bool
app::on_lexical_error (lexical_etype etype, size_t line, size_t col, size_t wcol,
                       size_t pos)
{
  auto file = this->option->source_filename;
  std::string msg;
  bool recover = false;
  switch (etype)
    {
    case lexical_etype::UNEXPECTED_CHAR:
      {
        msg = "Unexpected char";
        recover = true;
        break;
      }
    case lexical_etype::EMPTY_CHAR_LITERAL:
      {
        msg = "Expect char literal, nothing given";
        recover = true;
        break;
      }
    case lexical_etype::INVALID_ESCAPE_CHAR:
      {
        msg = "Invalid escape char";
        recover = true;
        break;
      }
    case lexical_etype::UNTERMINATED_STRING:
      {
        msg = "Missing closing quote";
        recover = true;
        break;
      }
    case lexical_etype::UNTERMINATED_CHAR:
      {
        msg = "Missing closing quote";
        recover = true;
        break;
      }
    case lexical_etype::UNTERMINATED_BLOCK_COMMENT:
      {
        msg = "Unterminated block comment";        
        col--;
        recover = true;
        break;
      }
    default:
      break;
    }
  spdlog::error ("Lexical error: " + msg + " ({}:{}:{},{})", file, line, col,
                 pos);
  std::ifstream ifs (file, std::ios::in);
  ifs.seekg (pos - col, std::ios::beg);
  std::string line_str;
  std::getline (ifs, line_str);
  std::string pref = fmt::format ("{} | ", line);
  spdlog::error (pref + line_str);
  std::string blanks (pref.size () + col - 1, ' ');
  spdlog::error (blanks + "^ here");
  ifs.close ();
  return recover;
}

void
app::on_receive_token (token t)
{
  if (t.get_type () == token_type::STR)
    {
      spdlog::info ("{}:{}:{:<3}\tTYPE={:8s}STR={:12s}",
                    option->source_filename, t.get_line (), t.get_col (),
                    t.get_type_str (), t.get_literal ());
      return;
    };
  if (t.get_type () == token_type::INLCOM)
    {
      spdlog::info ("{}:{}:{:<3}\tInline comment: {}", option->source_filename,
                    t.get_line (), t.get_col (), t.get_lexeme ());
      return;
    };
  if (t.get_type () == token_type::BLKCOM)
    {
      spdlog::info ("{}:{}:{:<3}\tBlock comment: \n{}",
                    option->source_filename, t.get_line (), t.get_col (),
                    t.get_lexeme ());
      return;
    };
  spdlog::info ("{}:{}:{:<3}\tTYPE={:8s}TEXT={:12s}", option->source_filename,
                t.get_line (), t.get_col (), t.get_type_str (),
                t.get_lexeme ());

  // auto s = t.c_str ();
  // spdlog::info (s);
  // free(s);
}

app::app (const std::shared_ptr<app_option> &option) { this->option = option; }

void
app::run ()
{
  spdlog::info ("Started");
  auto sfile = this->option->source_filename;
  if (sfile.length () > 0)
    {
      std::ifstream s (sfile);
      if (!s)
        {
          throw std::system_error (errno, std::system_category (),
                                   "failed to open " + sfile);
        }
      this->text << s.rdbuf ();
      spdlog::info ("File is open");
    }

  if (this->option->debug)
    {
      spdlog::info ("Source file content:");
      std::cout << this->text.str () << std::endl;
    }
  this->scanner_ = new lb_lexer::scanner (
      this->text, [this] (token t) -> void { this->on_receive_token (t); },
      [this] (lb_lexer::lexical_etype type, size_t line, size_t col, size_t wcol,
              size_t pos) -> bool {
        return this->on_lexical_error (type, line, col, pos, wcol);
      });
  spdlog::info ("Start scanning");
  this->scanner_->scan ();
  spdlog::info ("Scan over");
  delete this->scanner_;
}

app::~app () {}
} // namespace lb_lexer
