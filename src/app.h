#pragma once
#include "app_option.h"
#include "scanner.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace lb_lexer
{

class app
{
private:
  std::shared_ptr<app_option> option;
  std::stringstream text;
  scanner *scanner_;
  void on_receive_token(token t);
  bool on_lexical_error(lexical_etype etype, size_t line, size_t col, size_t wcol, size_t pos);

public:
  app (const std::shared_ptr<app_option> &option);
  void run ();
  ~app ();
};

} // namespace lb_lexer
