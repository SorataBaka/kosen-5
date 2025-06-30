#ifndef HELPER_H
#define HELPER_H
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define LOG(fmt, ...)                      \
  do                                       \
  {                                        \
    if (verbose)                           \
      fprintf(stderr, fmt, ##__VA_ARGS__); \
  } while (0)

int generateWithinRange(int min, int max);
double generateFloatWithinRange(double min, double max);
int verbose;

#endif