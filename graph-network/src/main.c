#include "stack.h"
#include "read_file.h"
#include "log.h"

void dfs(Node *starting_node)
{
  Stack *stack = init();
  push(stack, starting_node);
  while (stack->len != 0)
  {
    Node *stack_node = pop(stack);
    if (stack_node->visited == false)
    {
      printf("Visited %d\n", stack_node->id);
      stack_node->visited = true;
      for (int i = 0; i < stack_node->connected_nodes_count; i++)
      {
        if ((stack_node->connected_nodes[i])->visited == false)
        {
          push(stack, stack_node->connected_nodes[i]);
        }
      }
    }
  }
}

int main(int argc, char **argv)
{
  int line_count;

  Node *starting_node = read_file(argv[1], &line_count);

  char file_name[100];

  sprintf(file_name, "%s_stack.log", argv[1]);

  init_file("file_name");

  return 0;
}