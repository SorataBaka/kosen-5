#include "stack.h"
long int memory_used = 0;
long int total_memory_used = 0;

Stack *init()
{
  Stack *new_empty_stack = (Stack *)malloc(sizeof(Stack));
  new_empty_stack->head = NULL;
  new_empty_stack->len = 0;
  return new_empty_stack;
}
StackNode *create_stack_node(Node *graph_node, TreeNode *tree_parent)
{
  StackNode *new_stack_node = (StackNode *)malloc(sizeof(StackNode));
  new_stack_node->graph_node = graph_node;
  new_stack_node->tree_parent = tree_parent;
  new_stack_node->next = NULL;
  return new_stack_node;
}

Stack *push(Stack *stack, Node *graph_node, TreeNode *tree_parent)
{
  StackNode *new_stack_node = create_stack_node(graph_node, tree_parent);
  new_stack_node->next = stack->head;
  stack->head = new_stack_node;
  stack->len++;
  return stack;
}
StackNode *pop(Stack *stack)
{
  if (!stack->head)
    return NULL;
  StackNode *popped_node = stack->head;
  stack->head = popped_node->next;
  popped_node->next = NULL;
  stack->len--;
  return popped_node;
}
void clear(Stack *stack)
{
  while (stack->head != NULL)
  {
    StackNode *head = stack->head;
    stack->head = head->next;
    free(head);
  }
  stack->len = 0;
}
bool isEmpty(Stack *stack)
{
  return stack->head == NULL;
}
