#ifndef SPANNING_TREE_H
#define SPANNING_TREE_H
#include "definition.h"
TreeNode *create_tree_node(int id, TreeNode *parent);
TreeNode *add_child(TreeNode *parent, TreeNode *child);
void free_tree(TreeNode *root);
void print_tree(TreeNode *root, int depth);

#endif