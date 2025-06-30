#include "area.h"

void simulatePlot(long long int count, double radius, Options opts)
{
  long long int withinCount = 0;
  double theoretical = calculateTheoreticalChance(radius);
  if (opts.has_outfile)
  {
    fprintf(opts.outfile, "index,radius,x,y,withinCount,percentageWithin,theoretical\n");
  }
  for (long long int i = 0; i < count; i++)
  {
    Plot randomizedPlot = generateRandomPlot(radius);
    int isWithin = checkWithin(randomizedPlot, radius);
    withinCount += isWithin;
    double percentageWithin = (double)withinCount / (double)(i + 1);

    LOG("Radius: %.4f | Plot(x: %.3f,y: %.3f) | "
        "Within Count: %lld | PercentageWithin: %.8f %% | Theoretical: %.8f%%\n",
        radius,
        randomizedPlot.xPlot,
        randomizedPlot.yPlot,
        withinCount,
        percentageWithin, theoretical);

    /* CSV—for spreadsheets or later crunching */
    if (opts.has_outfile && opts.outfile)
    {
      fprintf(opts.outfile,
              "%lld,%.4f,%.3f,%.3f,%lld,%.8f,%.8f\n",
              i,
              radius,
              randomizedPlot.xPlot,
              randomizedPlot.yPlot,
              withinCount,
              percentageWithin, theoretical);
    }
  }
}

Plot generateRandomPlot(double radius)
{
  double x = generateFloatWithinRange(-radius, radius);
  double y = generateFloatWithinRange(-radius, radius);
  Plot plot = {x,
               y};
  return plot;
}

int checkWithin(Plot plot, double radius)
{
  // x^2 + y^2 = r^2
  double rSquared = radius * radius;
  double xSquared = plot.xPlot * plot.xPlot;
  double ySquared = plot.yPlot * plot.yPlot;

  if (xSquared + ySquared > rSquared)
    return 0;
  return 1;
}
double calculateTheoreticalChance(double radius)
{
  double areaOfSquare = 2 * radius * 2 * radius;
  double areaOfCircle = M_PI * radius * radius;

  return areaOfCircle / areaOfSquare;
}