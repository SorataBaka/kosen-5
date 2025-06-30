#include "helper.h"
int verbose = 0;
int generateWithinRange(int min, int max)
{
  if (min > max)
  {
    // Swap if range is invalid
    int temp = min;
    min = max;
    max = temp;
  }
  int range = max - min + 1;
  return min + rand() % range;
}

double generateFloatWithinRange(double min, double max)
{
  return min + (max - min) * (double)rand() / ((double)RAND_MAX + 1);
}