#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "help.h"

void print_help(const char *prog_name)
{
  printf("Usage: %s <mode> <repeat> <args> [options]\n", prog_name);
  printf("  mode: 'dice' or 'area'\n");
  printf("  -h, --help          Show this help message\n");
  printf("  -r, --repeat N      Set repeat count (default: 0)\n");
  printf("  -v, --verbose       Enable verbose output\n");
  printf("  -o, --out FILENAME  Write output to file\n");
}

static void die(const char *msg)
{
  fputs(msg, stderr);
  exit(EXIT_FAILURE);
}

Options *parse_args(int argc, char *argv[])
{
  if (argc < 4)
  {
    die("Usage: prog <mode> <repeat> <variable> [options]\n");
  }

  /* 1. allocate and zero‑initialise */
  Options *o = calloc(1, sizeof *o); /* calloc sets memory to 0 */
  if (!o)
  {
    perror("calloc");
    exit(EXIT_FAILURE);
  }

  /* 2. mandatory positional args */
  o->mode = argv[1];
  o->repeat = atoll(argv[2]);

  if (strcmp(o->mode, "dice") == 0)
  {
    o->dice_count = atoi(argv[3]);
    if (o->repeat <= 0 || o->dice_count <= 0)
      die("repeat and dice_count must be positive.\n");
  }
  else if (strcmp(o->mode, "area") == 0)
  {
    o->radius = atof(argv[3]);
    if (o->repeat <= 0 || o->radius <= 0.0)
      die("repeat and radius must be positive.\n");
  }
  else if (strcmp(o->mode, "janken") == 0)
  {
    o->step = atof(argv[3]);
    if (o->repeat <= 0 || o->step <= 0)
      die("repeat and step must be positive.\n");
  }
  else if (strcmp(o->mode, "height") == 0)
  {
    o->minTaller = atoi(argv[3]);
    if (o->repeat <= 0 || o->minTaller <= 0)
      die("Repeat and minimum taller value must be positive");
  }
  else if (strcmp(o->mode, "bingo") == 0)
  {
    int bingomode = atoi(argv[3]);
    if (bingomode < 0 || bingomode > 2)
      die("Invalid bingo mode\n");
    o->bingomode = bingomode;
  }
  else
  {
    die("Unknown mode. Use 'dice' or 'area'.\n");
  }

  /* 3. optional flags */
  for (int i = 4; i < argc; ++i)
  {
    const char *arg = argv[i];

    if (!strcmp(arg, "-h") || !strcmp(arg, "--help"))
      o->show_help = 1;
    else if (!strcmp(arg, "-v") || !strcmp(arg, "--verbose"))
      o->verbose = 1;
    else if (!strcmp(arg, "-o") || !strcmp(arg, "--out"))
    {
      if (++i == argc)
        die("--out needs a filename.\n");
      o->outfile = fopen(argv[i], "w");
      if (!o->outfile)
      {
        perror("fopen");
        exit(EXIT_FAILURE);
      }
      o->has_outfile = 1;
    }
    else
    {
      fprintf(stderr, "Unknown option: %s\n", arg);
      exit(EXIT_FAILURE);
    }
  }

  return o; /* caller must free(o) and fclose(o->outfile) */
}
