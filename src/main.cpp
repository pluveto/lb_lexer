
#include "app.h"
#include "app_option.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int
main (int argc, char const *argv[])
{
  using namespace lb_lexer;
  auto opt = app_option::from_env (argc, argv);
  auto app = std::make_shared<lb_lexer::app> (opt);
  app->run ();
  return 0;
}