#include "bingo.h"

void simulateBingo(long long int repeat, Options opts)
{
  if (opts.bingomode == WITHIN)
  {
    if (opts.has_outfile)
      fprintf(opts.outfile, "repeat,valid,percentage\n");
    int valid = 0;
    for (long long int i = 0; i < repeat; i++)
    {
      BingoCard *card = generateHand();
      int calledNumbers[76] = {0};
      for (int j = 0; j < 7; j++)
      {
        simulateCalls(card, calledNumbers);
        int isvalid = validateCard(card);
        if (isvalid == 1)
        {
          valid++;
          break; // If the card is valid, we can stop calling numbers for this card
        }
      }
      LOG("Repeat: %lld | Valid: %5d | Percentage: %06f\n", i + 1, valid, (double)valid / ((double)i + 1));
      if (opts.has_outfile)
        fprintf(opts.outfile, "%lld,%d,%06f\n", i + 1, valid, (double)valid / ((double)i + 1));
      free(card);
    }
  }
  else if (opts.bingomode == EXACT)
  {
    if (opts.has_outfile)
      fprintf(opts.outfile, "repeat,valid,percentage\n");
    int valid = 0;
    for (long long int i = 0; i < repeat; i++)
    {
      BingoCard *card = generateHand();
      int calledNumbers[75] = {0};
      for (int j = 0; j < 4; j++)
      {
        simulateCalls(card, calledNumbers);
      }
      valid += validateCard(card);
      LOG("Repeat: %lld | Valid: %5d | Percentage: %06f\n", i + 1, valid, (double)valid / ((double)i + 1));
      if (opts.has_outfile)
        fprintf(opts.outfile, "%lld,%d,%06f\n", i + 1, valid, (double)valid / ((double)i + 1));
      free(card);
    }
  }
  else
  {
    if (opts.has_outfile)
      fprintf(opts.outfile, "repeat,current_max,current_call_count,percentage\n");
    int current_max = 0;
    int callCounts[76] = {0};
    for (long long int i = 0; i < repeat; i++)
    {
      BingoCard *card = generateHand();

      int calls[76] = {0};

      int callCount = 1;
      simulateCalls(card, calls);
      int valid = validateCard(card);
      while (valid != 1)
      {
        simulateCalls(card, calls);
        valid = validateCard(card);
        callCount++;
      }
      callCounts[callCount]++;
      if (callCount > current_max)
        current_max = callCount;

      free(card);

      LOG("Repeat: %lld | Current Max: %5d | Loop Count: %5d | Percentage: %0.06f\n", i + 1, current_max, callCount, (double)callCounts[callCount] / (i + 1));

      if (opts.has_outfile)
        fprintf(opts.outfile, "%lld,%d,%d,%0.06f\n", i + 1, current_max, callCount, (double)callCounts[callCount] / (i + 1));
    }
  }
}

BingoCard *generateHand()
{
  BingoCard *card = malloc(sizeof(BingoCard));
  for (int i = 0; i < SIDE; i++)
  {
    int lowLimit = (15 * i) + 1;
    int upperLimit = (15 * (i + 1));
    int *row = generateWithinRangeWithoutRepetition(SIDE, lowLimit, upperLimit);
    for (int j = 0; j < SIDE; j++)
    {
      if (i == 2 && j == 2) // Center space is free
      {
        (*card)[i][j].value = 0;  // Free space
        (*card)[i][j].called = 1; // Mark as called
        continue;
      }
      (*card)[i][j].value = row[j];
      (*card)[i][j].called = 0;
    }
    free(row);
  }
  (*card)[2][2].called = 1;
  return card;
}

int validateCard(const BingoCard *card)
{
  // Check for rows
  for (int i = 0; i < SIDE; i++)
  {
    int calledCount = 0;
    for (int j = 0; j < SIDE; j++)
    {
      if ((*card)[i][j].called == 1)
        calledCount++;
    }
    if (calledCount == SIDE)
      return 1;
  }
  // Check for columns
  for (int i = 0; i < SIDE; i++)
  {
    int calledCount = 0;
    for (int j = 0; j < SIDE; j++)
    {
      if ((*card)[j][i].called == 1)
        calledCount++;
    }
    if (calledCount == SIDE)
      return 1;
  }
  // Check for diagonals
  int mainDiagonal = 1;
  int antiDiagonal = 1;

  for (int i = 0; i < SIDE; i++)
  {
    if ((*card)[i][i].called != 1)
    {
      mainDiagonal = 0;
    }
    if ((*card)[i][SIDE - 1 - i].called != 1)
    {
      antiDiagonal = 0;
    }
  }
  if (mainDiagonal || antiDiagonal)
    return 1;
  return 0;
}

void simulateCalls(BingoCard *card, int calledNumbers[76])
{
  int call;
  do
  {
    call = generateWithinRange(1, 75);
  } while (calledNumbers[call]);
  calledNumbers[call] = 1;

  for (int i = 0; i < SIDE; i++)
  {
    for (int j = 0; j < SIDE; j++)
    {
      if ((*card)[i][j].value == call)
        (*card)[i][j].called = 1;
    }
  }
}