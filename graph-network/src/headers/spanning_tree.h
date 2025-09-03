#ifndef SPANNING_TREE_H
#define SPANNING_TREE_H
#include "definition.h"
TreeNode *create_tree_node(int id, TreeNode *parent);
TreeNode *add_child(TreeNode *parent, TreeNode *child);
void free_tree(TreeNode *root);
void print_tree(TreeNode *root, int depth);
int get_tree_depth(TreeNode *root);
int count_leaves(TreeNode *root);
int max_branching(TreeNode *root);
int get_diameter(TreeNode *root);
double compute_symmetry(TreeNode *root, int node_count);
#endif