#ifndef STACK_H
#define STACK_H
#include "definition.h"
#include <time.h>
#include "log.h"
typedef struct Stack Stack;
typedef struct StackNode StackNode;

struct StackNode
{
  Node *node;
  StackNode *next;
  StackNode *prev;
  struct timespec ts;
  int depth;
};

struct Stack
{
  StackNode *head;
  StackNode *tail;
  int len;
};
extern long int memory_used;
extern long int total_memory_used;

Stack *push(Stack *stack, Node *node, int level);
StackNode *pop(Stack *stack);
int len(Stack *stack);
void clear(Stack *stack);
Stack *init();

#endif