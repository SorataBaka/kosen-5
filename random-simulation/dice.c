#include "dice.h"

void simulateDice(long long count, int diceCount, Options opts)
{
  if (opts.has_outfile)
    fprintf(opts.outfile, "dice_count,same_count,throw_count,percentage\n");

  int sameCount = 0;
  for (long long int i = 1; i <= count; i++)
  {
    int *dices = rollDice(diceCount);

    if (checkAllDice(dices, diceCount) == 1)
      sameCount++;

    free(dices);

    double percentageSame = (double)sameCount / (double)i * 100;

    LOG("DiceCount: %d | SameCount: %d | ThrowCount: %lld | PercentageSame: %.8f%%\n",
        diceCount,
        sameCount,
        i,
        percentageSame);

    if (opts.has_outfile == 1)
      fprintf(opts.outfile, "%d,%d,%lld,%.8f\n",
              diceCount,
              sameCount,
              i,
              percentageSame);
  }
}

int *rollDice(int count)
{
  int *diceArray = (int *)malloc(sizeof(int) * count);
  for (int i = 0; i < count; i++)
  {
    diceArray[i] = generateWithinRange(1, 6);
  }
  return diceArray;
}
int checkAllDice(int *diceArray, int length)
{
  for (int i = 0; i < length - 1; i++)
  {
    if (diceArray[i] != diceArray[i + 1])
      return 0; // Not all the same, return immediately
  }
  return 1; // All are the same
}