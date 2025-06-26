#include "help.h"
void print_help(const char *prog_name)
{
  printf("Usage: %s [options]\n", prog_name);
  printf("  -h, --help          Show this help message\n");
  printf("  -r, --repeat N      Set repeat count (default: 0)\n");
  printf("  -v, --verbose       Enable verbose output\n");
  printf("  -o, --out FILENAME  Enable result output\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "help.h"

static void die(const char *msg)
{
  fputs(msg, stderr);
  exit(EXIT_FAILURE);
}

Options parse_args(int argc, char *argv[])
{
  if (argc < 4)
  { /* prog  mode  repeat  dice_count */
    die("Usage: prog <mode> <repeat> <dice_count> [options]\n");
  }

  Options o = {0};

  /* ── positional args ─────────────────────────────── */
  o.mode = argv[1];

  if (strcmp(o.mode, "dice") == 0)
  {
    o.repeat = atoll(argv[2]);
    o.dice_count = atoi(argv[3]);
    if (o.repeat <= 0 || o.dice_count <= 0)
      die("repeat and dice_count must be positive\n");
  }
  else
  {
    die("Unknown simulation type\n");
  }

  /* ── option flags start after the simulation-specific args ── */
  for (int i = 4; i < argc; ++i)
  {
    const char *arg = argv[i];

    if (!strcmp(arg, "-h") || !strcmp(arg, "--help"))
    {
      o.show_help = 1;
    }
    else if (!strcmp(arg, "-v") || !strcmp(arg, "--verbose"))
    {
      o.verbose = 1;
    }
    else if (!strcmp(arg, "-o") || !strcmp(arg, "--out"))
    {
      if (++i == argc)
        die("Error: --out needs a filename\n");
      o.has_outfile = 1;

      FILE *f = fopen(argv[i], "w"); /* truncate/create */
      if (!f)
        die("Cannot open output file\n");
      fclose(f);

      o.outfile = fopen(argv[i], "a");
      if (!o.outfile)
        die("Cannot reopen output file\n");
    }
    else
    {
      fprintf(stderr, "Unknown option: %s\n", arg);
      exit(EXIT_FAILURE);
    }
  }
  return o;
}
