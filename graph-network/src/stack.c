#include "stack.h"
Stack *push(Stack *stack, Node *node)
{
  // If the stack is empty
  if (stack == NULL)
  {
    stack = (Stack *)malloc(sizeof(Stack));
    stack->head = stack->tail = NULL;
    stack->len = 0;
  }
  StackNode *new_node = (StackNode *)malloc(sizeof(StackNode));
  new_node->node = node;
  new_node->next = NULL;
  new_node->prev = stack->tail;
  clock_gettime(CLOCK_MONOTONIC, &(new_node->ts));
  if (stack->len == 0)
  {
    // First node in stack
    stack->head = stack->tail = new_node;
  }
  else
  {
    stack->tail->next = new_node;
    stack->tail = new_node;
  }

  stack->len++;
  return stack;
}
Node *pop(Stack *stack)
{
  if (stack == NULL || stack->len == 0)
  {
    return NULL; // Empty
  }

  StackNode *old_tail = stack->tail;
  Node *node = old_tail->node;

  // Move tail back
  stack->tail = old_tail->prev;
  if (stack->tail != NULL)
  {
    stack->tail->next = NULL;
  }
  else
  {
    // Stack is now empty → reset head
    stack->head = NULL;
  }

  free(old_tail);
  stack->len--;

  return node;
}
int len(Stack *stack)
{
  return stack->len;
}
void clear(Stack *stack)
{
  if (stack == NULL)
    return;

  StackNode *current = stack->head;
  while (current != NULL)
  {
    StackNode *next = current->next;
    free(current);
    current = next;
  }

  stack->head = NULL;
  stack->tail = NULL;
  stack->len = 0;
}
Stack *init()
{
  Stack *new_stack = (Stack *)malloc(sizeof(Stack));
  new_stack->head = NULL;
  new_stack->tail = NULL;
  new_stack->len = 0;
  return new_stack;
}