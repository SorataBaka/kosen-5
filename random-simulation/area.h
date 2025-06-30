#ifndef AREA_H
#define AREA_H
#include "helper.h"
#include <stdlib.h>
#include <stdio.h>
#include "help.h"
#include <math.h>

typedef struct Plot
{
  double xPlot;
  double yPlot;
} Plot;
typedef struct CirclePlotResult
{
  double plotIndex;
  double radius;
  Plot plot;
  int isWithin;
  double percentageWithin;
} CirclePlotResult;

void simulatePlot(long long int count, double radius, Options opts);
Plot generateRandomPlot(double radius);
int checkWithin(Plot plot, double radius);
double calculateTheoreticalChance(double radius);
#endif