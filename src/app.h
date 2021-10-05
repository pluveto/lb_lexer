#pragma once
#include "app_option.h"
namespace lb_lexer
{

class app
{
private:
  std::shared_ptr<app_option> option;

public:
  app (const std::shared_ptr<app_option>& option);
  void run();
  ~app ();
};

} // namespace lb_lexer
