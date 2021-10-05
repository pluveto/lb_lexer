#include "app_option.h"

#include <cstring>
namespace lb_lexer
{

void
usage (char const *progname)
{
  fprintf (stdout, "Usage '%s [OPTION] C_SOURCE_FILE'.\n", progname);
  fputs ("Lexical analyze given file.", stdout);
}

std::shared_ptr<app_option>
app_option::from_env (int argc, char const *argv[])
{
  std::shared_ptr<app_option> o = std::make_shared<app_option> ();
  char const *progname = argv[0];
  o->progname = progname;
  // argument validation
  if (argc != 2)
    {
      fprintf (stderr, "%s: missing operand\n", progname);
      usage (progname);
      exit (EXIT_FAILURE);
    }
  o->source_filename = argv[1];
  o->debug = strcmp(std::getenv ("LB_DEBUG"), std::string("ON").c_str()) == 0;
  return o;
}
} // namespace lb_lexer
