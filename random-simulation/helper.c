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
  arc4random_buf(&x, sizeof x); // 64 random bits from the CSPRNG
  /* Keep the top 53 bits (IEEE‑754 mantissa width) and scale */
  return (x >> 11) * (1.0 / 9007199254740992.0); // 2^53
}