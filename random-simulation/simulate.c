#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dice.h"

int main(int argc, char *argv[])
{
  for (int i = 0; i < 100; i++)
  {
    log("Rolling %d: ", i);
    int *diceArray = rollDice(2);
    for (int j = 0; j < 2; j++)
    {
      log("%d ", diceArray[j]);
    }
    log("| result %s \n", checkDice(diceArray, 2) == 1 ? "ALLSAME" : "NOTSAME");
  }
}
