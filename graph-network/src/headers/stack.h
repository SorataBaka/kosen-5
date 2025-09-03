#ifndef STACK_H
#define STACK_H
#include "definition.h"
#include <time.h>
#include "log.h"
typedef struct Stack Stack;
typedef struct StackNode StackNode;

struct StackNode
{
  Node *graph_node;
  TreeNode *tree_parent;
  StackNode *next;
};

struct Stack
{
  StackNode *head;
  int len;
};
extern long int memory_used;
extern long int total_memory_used;

Stack *init();
StackNode *create_stack_node(Node *graph_node, TreeNode *tree_parent);

Stack *push(Stack *stack, Node *node, TreeNode *tree_parent);
StackNode *pop(Stack *stack);

void clear(Stack *stack);
bool isEmpty(Stack *stack);
#endif