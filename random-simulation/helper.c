#include "helper.h"
int verbose = 0;
int generateWithinRange(int min, int max)
{
  if (min > max)
  {
    uint32_t t = min;
    min = max;
    max = t;
  }
  return min + arc4random_uniform(max - min + 1);
}

double generateFloatWithinRange(double min, double max)
{
  if (min > max)
  {
    double tmp = min;
    min = max;
    max = tmp;
  }
  return min + (max - min) * arc4random_double();
}

double arc4random_double(void)
{
  uint64_t x;
  arc4random_buf(&x, sizeof x);                  // 64 random bits from the CSPRNG
  return (x >> 11) * (1.0 / 9007199254740992.0); // 2^53
}
int *generateWithinRangeWithoutRepetition(int count, int min, int max)
{
  int range = max - min + 1;
  if (count > range)
    return NULL; // Too many requested

  // Step 1: fill array with all numbers in range
  int *pool = malloc(sizeof(int) * range);
  for (int i = 0; i < range; i++)
  {
    pool[i] = min + i;
  }

  // Step 2: shuffle first `count` elements using Fisher–Yates
  for (int i = 0; i < count; i++)
  {
    int j = i + arc4random_uniform(range - i); // [i, range-1]
    int tmp = pool[i];
    pool[i] = pool[j];
    pool[j] = tmp;
  }

  // Step 3: copy first `count` values into result
  int *result = malloc(sizeof(int) * count);
  for (int i = 0; i < count; i++)
  {
    result[i] = pool[i];
  }

  free(pool);
  return result;
}