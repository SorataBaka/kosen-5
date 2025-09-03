#ifndef QUEUE_H
#define QUEUE_H
#include "definition.h"
typedef struct Queue Queue;
typedef struct QueueNode QueueNode;

struct QueueNode
{
  Node *graph_node;
  TreeNode *tree_parent;
  QueueNode *next;
};
struct Queue
{
  QueueNode *head;
  QueueNode *tail;
  int len;
};

Queue *init_queue();
QueueNode *create_queue_node(Node *graph_node, TreeNode *tree_parent);
Queue *enqueue(Queue *queue, Node *graph_node, TreeNode *tree_parent);
QueueNode *dequeue(Queue *queue);
bool is_empty_queue(Queue *queue);
void clear_queue(Queue *queue);

#endif