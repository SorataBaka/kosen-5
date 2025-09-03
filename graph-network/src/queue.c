#include "queue.h"
Queue *init_queue()
{
  Queue *new_queue = (Queue *)malloc(sizeof(Queue));
  new_queue->head = NULL;
  new_queue->tail = NULL;
  new_queue->len = 0;
  return new_queue;
}
QueueNode *create_queue_node(Node *graph_node, TreeNode *tree_parent)
{
  QueueNode *new_queue_node = (QueueNode *)malloc(sizeof(QueueNode));
  new_queue_node->graph_node = graph_node;
  new_queue_node->tree_parent = tree_parent;
  new_queue_node->next = NULL;
  return new_queue_node;
}
Queue *enqueue(Queue *queue, Node *graph_node, TreeNode *tree_parent)
{
  QueueNode *node = create_queue_node(graph_node, tree_parent);

  if (!queue->tail)
  {
    queue->head = queue->tail = node;
  }
  else
  {
    queue->tail->next = node;
    queue->tail = node;
  }
  queue->len++;
  return queue;
}
QueueNode *dequeue(Queue *queue)
{
  if (!queue->head)
    return NULL;

  QueueNode *temp = queue->head;

  queue->head = queue->head->next;
  if (!queue->head)
    queue->tail = NULL;

  queue->len--;
  return temp;
}
bool is_empty_queue(Queue *queue)
{
  return queue->head == NULL;
}
void clear_queue(Queue *queue)
{
  while (!is_empty_queue(queue))
  {
    QueueNode *temp = dequeue(queue);
    free(temp);
  }
}