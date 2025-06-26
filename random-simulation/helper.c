#include "helper.h"
int verbose = 0;
int generateWithinRange(int min, int max)
{
  if (min > max)
  {
    int temp = min;
    min = max;
    max = temp;
  }
  int range = max - min + 1;

  // To reduce modulo bias, discard numbers above a threshold
  int rand_max = RAND_MAX - (RAND_MAX % range);
  int r;
  do
  {
    r = rand();
  } while (r >= rand_max);

  return min + (r % range);
}