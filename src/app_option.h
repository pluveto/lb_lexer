#pragma once
#include <memory>
#include <string>

namespace lb_lexer
{

struct app_option
{
  std::string source_filename;
  std::string progname;
  bool debug;

  static std::shared_ptr<app_option> from_env (int argc, char const *argv[]);
};
}