
#include "app.h"
#include "app_option.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>

int
main (int argc, char const *argv[])
{
  spdlog::cfg::load_env_levels();
  // Read arguments
  auto opt = lb_lexer::app_option::from_env (argc, argv);
  spdlog::info("Options loaded");
  /* Create and run application */
  auto app = std::make_shared<lb_lexer::app> (opt);    
  app->run ();
  return 0;
}