#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dice.h"
#include "help.h"
#include "area.h"
#include "janken.h"
#include "height.h"
#include "bingo.h"

int main(int argc, char *argv[])
{
  Options *opts = parse_args(argc, argv);
  verbose = opts->verbose;

  if (opts->show_help)
  {
    print_help(argv[0]);
    return 0;
  }

  if (strcmp(opts->mode, "dice") == 0)
  {
    LOG("Running dice\n");
    simulateDice(opts->repeat, opts->dice_count, *opts);
  }
  if (strcmp(opts->mode, "area") == 0)
  {
    LOG("Running area\n");
    simulatePlot(opts->repeat, opts->radius, *opts);
  }
  if (strcmp(opts->mode, "janken") == 0)
  {
    LOG("Running janken\n");
    simulateJanken(opts->repeat, *opts);
  }
  if (strcmp(opts->mode, "height") == 0)
  {
    LOG("Running height\n");
    simulateHeight(opts->repeat, *opts);
  }
  if (strcmp(opts->mode, "bingo") == 0)
  {
    LOG("Running bingo\n");
    simulateBingo(opts->repeat, *opts);
  }
  if (opts->has_outfile)
    fclose(opts->outfile);

  return 0;
}
