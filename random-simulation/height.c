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

    double validRatio = (double)validQueue / ((double)i + 1);

    LOG("repeat,%lld,valid,%lld,ratio,%.7f\n",
        i, validQueue, validRatio);

    if (opts.has_outfile)
    {
      fprintf(opts.outfile, "%lld,%lld,%.7f\n",
              repeat, validQueue, validRatio);
    }
  }
}

Human *generateRow()
{
  Human *queue = (Human *)malloc(sizeof(Human) * 10);
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
    size_t j = (size_t)generateWithinRange(0, i + 1);
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
    int higher = 0;
    int femaleHeight = height_key(queue[i]);
    for (int j = 0; j < i; j++)
    {
      if (!IS_MALE(queue[j]))
        continue;
      if (height_key(queue[j]) < femaleHeight)
        ++higher;
    }
    if (higher >= minTaller)
      valid++;
  }
  if (valid == 5)
    return 1;
  return 0;
}

static inline int height_key(Human h)
/* Returns 1..5, where 1 is the tallest. */
{
  return 10 - ((int)h);
}