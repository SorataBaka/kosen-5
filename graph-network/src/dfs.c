#include "dfs.h"

#include <stdio.h>
#include <stdlib.h>
TreeNode *build_spanning_tree_dfs(Node *root_node)
{
  TreeNode *root_tree = create_tree_node(root_node->id, NULL);
  Stack *stack = init();

  // add a size counter
  int stack_size = 0;

  // open log file
  FILE *logf = fopen("stack_log.csv", "w");
  if (!logf)
  {
    perror("fopen");
    exit(1);
  }
  fprintf(logf, "op,id,stack_size\n"); // header

  root_node->visited = true;
  push(stack, root_node, root_tree);
  stack_size++;
  fprintf(logf, "push,%d,%d\n", root_node->id, stack_size);

  while (!isEmpty(stack))
  {
    StackNode *current_stack_node = pop(stack);
    stack_size--;
    fprintf(logf, "pop,%d,%d\n", current_stack_node->graph_node->id, stack_size);

    Node *current_node = current_stack_node->graph_node;
    TreeNode *current_tree_node = current_stack_node->tree_parent;

    for (int i = 0; i < current_node->connected_nodes_count; i++)
    {
      Node *children = current_node->connected_nodes[i];
      if (!children->visited)
      {
        children->visited = true;
        TreeNode *child_tree_node = create_tree_node(children->id, current_tree_node);
        add_child(current_tree_node, child_tree_node);
        push(stack, children, child_tree_node);
        stack_size++;
        fprintf(logf, "push,%d,%d\n", children->id, stack_size);
      }
    }
    free(current_stack_node);
  }

  fclose(logf);
  return root_tree;
}