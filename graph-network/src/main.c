#include "stack.h"
#include "read_file.h"
#include "log.h"
#include <time.h>

int main(int argc, char **argv)
{
  if (argc < 2 || argc > 2)
  {
    perror("Insufficient arguments");
    exit(EXIT_FAILURE);
  }
  int line_count, deepest_depth = 0;

  FILE *execution_logs = fopen("execution_logs.log", "a");
  Node *starting_node = read_file(argv[1], &line_count);

  return 0;
}