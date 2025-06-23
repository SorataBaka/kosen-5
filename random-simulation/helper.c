#include "helper.h"
int verbose = 0;
int generateWithinRange(int min, int max)
{
  long int randomNumber = random();
  return min + randomNumber % (max - min + 1);
}