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
  int *numberArray = (int *)malloc(sizeof(int) * count);
  for (int i = 0; i < count; i++)
  {
    int found = 1;
    int newnum;
    while (found)
    {
      newnum = generateWithinRange(min, max);
      found = 0;
      for (int j = 0; j < i; j++)
      {
        if (numberArray[j] == newnum)
        {
          found = 1;
          break;
        }
      }
    }
    numberArray[i] = newnum;
  }
  return numberArray;
}