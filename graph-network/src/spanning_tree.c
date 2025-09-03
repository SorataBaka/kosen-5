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
  for (int i = 0; i < depth; i++)
  {
    printf(" "); // 2 spaces per level
  }
  printf("%d\n", root->id);
  for (int i = 0; i < root->connected_nodes_count; i++)
  {
    print_tree(root->connected_nodes[i], depth + 1);
  }
}
int get_tree_depth(TreeNode *root)
{
  if (!root)
    return 0;

  int max_child_depth = 0;
  for (int i = 0; i < root->connected_nodes_count; i++)
  {
    int child_depth = get_tree_depth(root->connected_nodes[i]);
    if (child_depth > max_child_depth)
      max_child_depth = child_depth;
  }
  return 1 + max_child_depth;
}
int count_leaves(TreeNode *root)
{
  if (!root)
    return 0;
  if (root->connected_nodes_count == 0)
    return 1;

  int leaves = 0;
  for (int i = 0; i < root->connected_nodes_count; i++)
    leaves += count_leaves(root->connected_nodes[i]);
  return leaves;
}
int max_branching(TreeNode *root)
{
  if (!root)
    return 0;

  int max_children = root->connected_nodes_count;
  for (int i = 0; i < root->connected_nodes_count; i++)
  {
    int child_max = max_branching(root->connected_nodes[i]);
    if (child_max > max_children)
      max_children = child_max;
  }
  return max_children;
}
int subtree_sizes(TreeNode *root, int *sizes, int *count)
{
  if (!root)
    return 0;
  int total = 1;
  for (int i = 0; i < root->connected_nodes_count; i++)
    total += subtree_sizes(root->connected_nodes[i], sizes, count);
  sizes[(*count)++] = total;
  return total;
}

double compute_symmetry(TreeNode *root, int node_count)
{
  int *sizes = malloc(sizeof(int) * node_count);
  if (!sizes)
  {
    fprintf(stderr, "malloc failed\n");
    return 0.0;
  }

  int count = 0;
  subtree_sizes(root, sizes, &count);

  if (count <= 1)
  {
    free(sizes);
    return 1.0;
  }

  // compute variance
  double mean = 0;
  for (int i = 0; i < count; i++)
    mean += sizes[i];
  mean /= count;

  double variance = 0;
  for (int i = 0; i < count; i++)
  {
    double diff = sizes[i] - mean;
    variance += diff * diff;
  }
  variance /= count;

  free(sizes);
  return 1.0 / (1.0 + variance); // higher = more symmetric
}
int diameter_helper(TreeNode *root, int *diameter)
{
  if (!root)
    return 0;
  int max1 = 0, max2 = 0;
  for (int i = 0; i < root->connected_nodes_count; i++)
  {
    int depth = diameter_helper(root->connected_nodes[i], diameter);
    if (depth > max1)
    {
      max2 = max1;
      max1 = depth;
    }
    else if (depth > max2)
    {
      max2 = depth;
    }
  }
  if (max1 + max2 > *diameter)
    *diameter = max1 + max2;
  return max1 + 1;
}
int get_diameter(TreeNode *root)
{
  int dia = 0;
  diameter_helper(root, &dia);
  return dia;
}