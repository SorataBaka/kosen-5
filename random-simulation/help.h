#ifndef HELP_H
#define HELP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
  int count;
  int verbose;
  int show_help;
} Options;

void print_help(const char *prog_name);
Options parse_args(int argc, char *argv[]);

#endif