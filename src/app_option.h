#pragma once
#include <string>
#include <memory>

namespace lb_lexer
{

struct app_option
{
  std::string source_filename;
  std::string progname;

  static std::shared_ptr<app_option> from_env (int argc, char const *argv[]);
};
}