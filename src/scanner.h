#include "token.h"
#include <functional>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

namespace lb_lexer
{

enum lexical_etype
{
  UNEXPECTED_CHAR
};

typedef std::function<void (lb_lexer::token)> yield_token;
typedef std::function<bool (lexical_etype type, size_t line, size_t col)>
    error_handler;

class scanner
{
private:
  // 源代码字符流
  std::ostream &chstream;
  // token 回调函数。当一个 token 产生之后执行。
  yield_token yield;
  error_handler on_error;
  // 是否源码读取完毕
  bool finished;
  // buffer 起始位置指针
  size_t start;
  // buffer 当前位置指针
  size_t current;
  // 当前行
  size_t line;
  // 当前列
  size_t col;
  // buffer，仅当 advance 时推入字符
  std::string buff;
  // 返回前一个字符，即 buff 的最后一个字符. 不存在则返回 0
  char prev ();
  // 获取 buff
  std::string capture ();
  // 返回当前字符，并让指针前进 1
  char advance ();
  // 返回当前字符
  char peek ();
  // 获取下个字符。如果不存在则返回 0。
  char peek_next ();
  // 是否是 [a-zA-Z_]
  bool is_word (char c);
  // 是否是 [0-9]
  bool is_digit (char c);
  // 处理转义字符
  void handle_escape ();
  // 是否是给定字符，是则返回 true 并前进
  bool match (char expected);
  // 匹配标识符
  void match_identifier ();
  // 匹配数字
  void match_number ();
  // 匹配字符
  void match_char ();
  // 匹配字符串
  void match_string ();
  // 匹配行内注释
  void match_inline_comment ();
  // 匹配块注释
  void match_block_comment ();
  // 匹配预处理指令
  void match_preproc ();
  // 扫描一个 token
  void scan_token ();

  // 快速返回一个 token
  void fast_yield (token_type type);

public:
  // s: 源码输出流
  // y: token 创建时的回调函数
  scanner (std::ostream &s, lb_lexer::yield_token y, lb_lexer::error_handler e)
      : chstream (s), yield (y), on_error (e){};
  // 执行词法分析
  void scan ();
  ~scanner (){};
};

}