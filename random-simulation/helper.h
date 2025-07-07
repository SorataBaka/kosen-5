#ifndef HELPER_H
#define HELPER_H
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#define LOG(fmt, ...)                      \
  do                                       \
  {                                        \
    if (verbose)                           \
      fprintf(stderr, fmt, ##__VA_ARGS__); \
  } while (0)
int verbose;

int generateWithinRange(int min, int max);
double generateFloatWithinRange(double min, double max);
int *generateWithinRangeWithoutRepetition(int count, int min, int max);
double arc4random_double(void);

#endif