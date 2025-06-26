#ifndef HELPER_H
#define HELPER_H
#include <stdlib.h>
#include <stdio.h>

#define log(fmt, ...)                      \
  do                                       \
  {                                        \
    if (verbose)                           \
      fprintf(stderr, fmt, ##__VA_ARGS__); \
  } while (0)

int generateWithinRange(int min, int max);
int verbose;

#endif