#include "dice.h"

int *rollDice(int count)
{
  int *diceArray = (int *)malloc(sizeof(int) * count);
  for (int i = 0; i < count; i++)
  {
    diceArray[i] = generateWithinRange(1, 6);
  }
  return diceArray;
}

int checkDice(int *diceArray, int length)
{
  int allSame = 1;
  for (int i = 0; i < length - 1; i++)
    if (diceArray[i] != diceArray[i + 1])
      allSame = 0;
  return allSame;
}