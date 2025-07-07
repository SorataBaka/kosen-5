#include "bingo.h"

void simulateBingo(long long int repeat, Options opts)
{
  if (opts.has_outfile)
    fprintf(opts.outfile, "repeat,valid,percentage\n");
  if (opts.bingomode == WITHIN)
  {
    int valid = 0;
    for (int i = 0; i < repeat; i++)
    {
      BingoCard *card = generateHand();
      for (int j = 0; j < 7; j++)
      {
        simulateCalls(card);
        valid += validateCard(card);
      }
      LOG("Repeat: %5d | Valid: %5d | Percentage: %06f\n", i + 1, valid, (double)valid / ((double)i + 1));
      if (opts.has_outfile)
        fprintf(opts.outfile, "%d,%d,%06f\n", i + 1, valid, (double)valid / ((double)i + 1));
      free(card);
    }
  }
  else if (opts.bingomode == EXACT)
  {
    if (opts.has_outfile)
      fprintf(opts.outfile, "repeat,valid,percentage\n");
    int valid = 0;
    for (int i = 0; i < repeat; i++)
    {
      BingoCard *card = generateHand();
      for (int j = 0; j < 4; j++)
      {
        simulateCalls(card);
        valid += validateCard(card);
      }
      LOG("Repeat: %5d | Valid: %5d | Percentage: %06f\n", i + 1, valid, (double)valid / ((double)i + 1));
      if (opts.has_outfile)
        fprintf(opts.outfile, "%d,%d,%06f\n", i + 1, valid, (double)valid / ((double)i + 1));
      free(card);
    }
  }
  else
  {
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
      (*card)[i][j] = row[j];
    }
    free(row);
  }
  (*card)[2][2] = 0;

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
      if ((*card)[i][j] == 0)
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
      if ((*card)[j][i] == 0)
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
    if ((*card)[i][i] != 0)
    {
      mainDiagonal = 0;
    }
    if ((*card)[i][SIDE - 1 - i] != 0)
    {
      antiDiagonal = 0;
    }
  }
  if (mainDiagonal || antiDiagonal)
    return 1;
  return 0;
}

void simulateCalls(BingoCard *card)
{
  int call = generateWithinRange(1, 75);
  for (int i = 0; i < SIDE; i++)
  {
    for (int j = 0; j < SIDE; j++)
    {
      if ((*card)[i][j] == call)
        (*card)[i][j] = 0;
    }
  }
}