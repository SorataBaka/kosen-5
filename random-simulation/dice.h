#ifndef DICE_H
#define DICE_H
#include "helper.h"
#include <stdlib.h>
#include "help.h"

typedef struct DiceRollResult
{
  int diceCount;
  int sameCount;
  long long int throwCount;
  double percentageSame;
} DiceRollResult;

void simulateDice(long long int count, int diceCount, Options opts);
int *rollDice(int count);
int checkAllDice(int *diceArray, int length);
#endif