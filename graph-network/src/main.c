#include "stack.h"
#include "read_file.h"
#include "log.h"
#include <time.h>

void dfs(Node *starting_node, int *depth)
{
  Stack *stack = init();

  // mark starting node visited when pushing
  starting_node->visited = true;
  push(stack, starting_node, 1);
  int deepest_depth = 1;

  while (stack->len != 0)
  {
    StackNode *stack_node = pop(stack);
    if (stack_node->depth > deepest_depth)
      deepest_depth = stack_node->depth;
    printf("Visited %d Depth %d\n", stack_node->node->id, stack_node->depth);

    for (int i = 0; i < stack_node->node->connected_nodes_count; i++)
    {
      Node *child = stack_node->node->connected_nodes[i];
      if (!child->visited)
      {
        child->visited = true; // mark visited **before** pushing
        push(stack, child, stack_node->depth + 1);
      }
    }
    free(stack_node); // free after use since pop now returns StackNode*
  }
  *depth = deepest_depth;
}

int main(int argc, char **argv)
{
  int line_count, deepest_depth;
  FILE *execution_logs = fopen("execution_logs.log", "a");

  Node *starting_node = read_file(argv[1], &line_count);

  char file_name[100];

  sprintf(file_name, "%s_stack.log", argv[1]);
  verify_nodes(starting_node, line_count);
  init_file(file_name);
  struct timespec start_time, end_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);

  dfs(starting_node, &deepest_depth);

  clock_gettime(CLOCK_MONOTONIC, &end_time);

  double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

  fprintf(execution_logs, "%s,%.09f,%ld,%d,%s\n", argv[1], elapsed_time, total_memory_used, deepest_depth, "dfs");

  return 0;
}