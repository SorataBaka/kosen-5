#include "stack.h"
long int memory_used = 0;
long int total_memory_used = 0;
Stack *push(Stack *stack, Node *node, int level)
{
  // If the stack is empty
  if (stack == NULL)
  {
    stack = (Stack *)malloc(sizeof(Stack));
    stack->head = stack->tail = NULL;
    stack->len = 0;
  }
  StackNode *new_node = (StackNode *)malloc(sizeof(StackNode));
  memory_used += sizeof(StackNode);
  total_memory_used += sizeof(StackNode);
  new_node->node = node;
  new_node->next = NULL;
  new_node->prev = stack->tail;
  new_node->depth = level;
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
StackNode *pop(Stack *stack)
{
  if (stack == NULL || stack->len == 0)
  {
    return NULL; // Empty
  }

  StackNode *old_tail = stack->tail;

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
  memory_used -= sizeof(StackNode);

  struct timespec end;
  clock_gettime(CLOCK_MONOTONIC, &end);

  double elapsed_time = (end.tv_sec - old_tail->ts.tv_sec) +
                        (end.tv_nsec - old_tail->ts.tv_nsec) / 1e9;

  log_file("%d, %.09lf, %ld", old_tail->node->id, elapsed_time, memory_used);

  stack->len--;

  // ⚠️ Do NOT free here, since caller will receive this StackNode
  return old_tail;
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