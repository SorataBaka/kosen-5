#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dice.h"
#include "help.h"

int main(int argc, char *argv[])
{
  Options opts = parse_args(argc, argv);
  verbose = opts.verbose;

  if (opts.show_help)
  {
    print_help(argv[0]);
    return 0;
  }

  if (opts.has_outfile)
    fprintf(opts.outfile, "dice_count,same_count,throw_count,percentage\n");

  if (strcmp(opts.mode, "dice") == 0)
  {
    log("Running dice\n");
    simulateDice(opts.repeat, opts.dice_count, opts);
  }

  if (opts.has_outfile)
    fclose(opts.outfile);

  return 0;
}
