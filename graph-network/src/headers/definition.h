#ifndef DEFNITION_H
#define DEFNITION_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "definition.h"

typedef struct Node Node;
typedef struct TreeNode TreeNode;

struct Node
{
  int id;
  bool visited;
  int connected_nodes_count;
  Node **connected_nodes;
};

struct TreeNode
{
  int id;
  int connected_nodes_count;
  TreeNode **connected_nodes;
  TreeNode *parent_node;
};

#endif