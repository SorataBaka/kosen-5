#include "help.h"
void print_help(const char *prog_name)
{
  printf("Usage: %s [options]\n", prog_name);
  printf("  -h, --help        Show this help message\n");
  printf("  -c, --count N     Set count (default: 0)\n");
  printf("  -v, --verbose     Enable verbose output\n");
}

Options parse_args(int argc, char *argv[])
{
  Options opts = {.count = 0, .verbose = 0, .show_help = 0};

  for (int i = 1; i < argc; i++)
  {
    if ((strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "-h") == 0))
    {
      opts.show_help = 1;
    }
    else if ((strcmp(argv[i], "--verbose") == 0) || (strcmp(argv[i], "-v") == 0))
    {
      opts.verbose = 1;
    }
    else if ((strcmp(argv[i], "--count") == 0) || (strcmp(argv[i], "-c") == 0))
    {
      if (i + 1 < argc)
      {
        opts.count = atoi(argv[++i]);
      }
      else
      {
        fprintf(stderr, "Error: --count requires an argument\n");
        exit(EXIT_FAILURE);
      }
    }
    else
    {
      fprintf(stderr, "Unknown option: %s\n", argv[i]);
      exit(EXIT_FAILURE);
    }
  }

  return opts;
}