#ifndef STACK_H
#define STACK_H
#include "definition.h"
#include <time.h>
typedef struct Stack Stack;
typedef struct StackNode StackNode;

struct StackNode
{
  Node *node;
  StackNode *next;
  StackNode *prev;
  struct timespec ts;
};

struct Stack
{
  StackNode *head;
  StackNode *tail;
  int len;
};

Stack *push(Stack *stack, Node *node);
Node *pop(Stack *stack);
int len(Stack *stack);
void clear(Stack *stack);
Stack *init();

#endif