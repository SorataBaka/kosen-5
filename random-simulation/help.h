#ifndef HELP_H
#define HELP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Options
{
  const char *mode; /* "dice", "coin", ...              */
  long long repeat; /* always required                  */
  int dice_count;   /* only used by "dice"              */
  double radius;
  double step;
  int minTaller;

  /* generic flags */
  int verbose;
  int show_help;
  int has_outfile;
  FILE *outfile;
} Options;

void print_help(const char *prog_name);
Options *parse_args(int argc, char *argv[]);

#endif