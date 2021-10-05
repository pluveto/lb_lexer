#include "app_option.h"

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
  std::shared_ptr<app_option> p = std::make_shared<app_option> ();
  char const *progname = argv[0];
  p->progname = progname;
  // argument validation
  if (argc != 2)
    {
      fprintf (stderr, "%s: missing operand\n", progname);
      usage (progname);
      exit (EXIT_FAILURE);
    }
  p->source_filename = argv[1];
  return p;
}
} // namespace lb_lexer
