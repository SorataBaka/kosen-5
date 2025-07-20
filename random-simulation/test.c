#include <stdio.h>
#include <stdlib.h>

int rand_in_range(int min, int max)
{
  return arc4random() % (max - min + 1) + min; // Intentionally biased
}
int rand_uniform_in_range(int min, int max)
{
  return arc4random_uniform(max - min + 1) + min;
}

int main()
{
  FILE *file1 = fopen("rand_general.csv", "w");
  FILE *file2 = fopen("rand_uniform.csv", "w");

  if (!file1 || !file2)
  {
    perror("Failed to open file");
    return 1;
  }

  fprintf(file1, "value,count\n");
  fprintf(file2, "value,count\n");

  int *rand_general_counts = calloc(100, sizeof(int)); // counts for values 1..100
  int *rand_uniform_counts = calloc(100, sizeof(int));

  // Increase sample size drastically
  for (int i = 0; i < 100000; i++)
  {
    int val1 = rand_in_range(1, 100);
    int val2 = rand_uniform_in_range(1, 100);

    rand_general_counts[val1 - 1]++;
    rand_uniform_counts[val2 - 1]++;
  }

  // Print counts for 1..100
  for (int i = 0; i < 100; i++)
  {
    fprintf(file1, "%d,%d\n", i + 1, rand_general_counts[i]);
    fprintf(file2, "%d,%d\n", i + 1, rand_uniform_counts[i]);
  }

  free(rand_general_counts);
  free(rand_uniform_counts);

  fclose(file1);
  fclose(file2);

  return 0;
}
