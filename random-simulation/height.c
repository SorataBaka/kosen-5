#include "height.h"

void simulateHeight(long long int repeat, Options opts)
{
  if (opts.has_outfile)
  {
    fprintf(opts.outfile, "repeat,valid,ratio\n");
  }
  long long int validQueue = 0;
  for (long long int i = 0; i < repeat; i++)
  {
    Human *queue = generateRow();
    int valid = checkRow(queue, 1);
    validQueue += valid;

    double validRatio = (double)validQueue / (i + 1);

    LOG("repeat,%lld,valid,%lld,ratio,%.7f\n",
        i + 1, validQueue, validRatio);

    if (opts.has_outfile)
    {
      fprintf(opts.outfile, "%lld,%lld,%.7f\n",
              i + 1, validQueue, validRatio);
    }

    free(queue);
  }
}

Human *generateRow()
{
  Human *queue = malloc(sizeof(Human) * 10);
  queue[0] = M1;
  queue[1] = W1;
  queue[2] = M2;
  queue[3] = W2;
  queue[4] = M3;
  queue[5] = W3;
  queue[6] = M4;
  queue[7] = W4;
  queue[8] = M5;
  queue[9] = W5;

  for (size_t i = 9; i > 0; --i)
  {
    size_t j = generateWithinRange(0, i);
    Human temp = queue[i];
    queue[i] = queue[j];
    queue[j] = temp;
  }

  return queue;
}

int checkRow(Human *queue, int minTaller)
{
  int valid = 0;
  for (int i = 0; i < 10; i++)
  {
    if (!IS_FEMALE(queue[i]))
      continue;
    int tallerLeft = 0;
    int fh = height_key(queue[i]);
    for (int j = 0; j < i; j++)
    {
      if (IS_MALE(queue[j]) && height_key(queue[j]) < fh)
        ++tallerLeft;
    }
    if (tallerLeft >= minTaller)
      ++valid;
  }
  return (valid == 5);
}

static inline int height_key(Human h)
{
  // Directly map enum values to height ranking (1 = tallest, 10 = shortest)
  static const int height_table[10] = {
      10, // W5
      9,  // M5
      8,  // W4
      7,  // M4
      6,  // W3
      5,  // M3
      4,  // W2
      3,  // M2
      2,  // W1
      1   // M1
  };
  return height_table[(int)h];
}
