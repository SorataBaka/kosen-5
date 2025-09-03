#include "spanning_tree.h"
TreeNode *create_tree_node(int id, TreeNode *parent)
{
  TreeNode *new_tree_node = (TreeNode *)malloc(sizeof(TreeNode));
  if (!new_tree_node)
  {
    perror("Failed to allocate TreeNode");
    exit(EXIT_FAILURE);
  }
  new_tree_node->connected_nodes = NULL;
  new_tree_node->connected_nodes_count = 0;
  new_tree_node->id = id;
  new_tree_node->parent_node = parent;
  return new_tree_node;
}
TreeNode *add_child(TreeNode *parent, TreeNode *child)
{
  parent->connected_nodes = realloc(
      parent->connected_nodes,
      (parent->connected_nodes_count + 1) * sizeof(TreeNode *));
  if (!parent->connected_nodes)
  {
    perror("Failed to allocate child nodes");
    exit(EXIT_FAILURE);
  }
  parent->connected_nodes[parent->connected_nodes_count] = child;
  parent->connected_nodes_count++;
  return parent;
}
void free_tree(TreeNode *root)
{
  if (!root)
    return;

  // Free all children recursively
  for (int i = 0; i < root->connected_nodes_count; i++)
  {
    free_tree(root->connected_nodes[i]);
  }

  // Free the dynamic array of child pointers
  free(root->connected_nodes);

  // Free the node itself
  free(root);
}
#include <stdio.h>

void print_tree(TreeNode *root, int depth)
{
  if (!root)
    return;

  // Indent according to depth
  for (int i = 0; i < depth; i++)
  {
    printf("  "); // 2 spaces per level
  }

  // Print node info
  printf("%d\n", root->id);

  // Print all children
  for (int i = 0; i < root->connected_nodes_count; i++)
  {
    print_tree(root->connected_nodes[i], depth + 1);
  }
}
