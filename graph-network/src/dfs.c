#include "dfs.h"
TreeNode *build_spanning_tree_dfs(Node *root_node)
{
  TreeNode *root_tree = create_tree_node(root_node->id, NULL);
  Stack *stack = init();
  push(stack, root_node, root_tree);
  while (!isEmpty(stack))
  {
    StackNode *current_stack_node = pop(stack);
    Node *current_node = current_stack_node->graph_node;
    TreeNode *current_tree_node = current_stack_node->tree_parent;

    if (current_node->visited == false)
    {
      current_node->visited = true;

      for (int i = 0; i < current_node->connected_nodes_count; i++)
      {
        Node *children = current_node->connected_nodes[i];
        if (children->visited == false)
        {
          TreeNode *child_tree_node = create_tree_node(children->id, current_tree_node);
          add_child(current_tree_node, child_tree_node);
          push(stack, children, child_tree_node);
        }
      }
    }
    free(current_stack_node);
  }
  return root_tree;
}