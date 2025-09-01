#ifndef QUEUE_H
#define QUEUE_H
#include "definition.h"
#include <time.h>
#include "log.h"

typedef struct Queue Queue;
typedef struct QueueNode QueueNode;

struct QueueNode
{
  Node *node;
  QueueNode *next;
  QueueNode *prev;
  struct timespec ts;
  int depth;
};

struct Queue
{
  QueueNode *head;
  QueueNode *tail;
  int len;
};

extern long int memory_used;
extern long int total_memory_used;

Queue *enqueue(Queue *queue, Node *node);
Node *dequeue(Queue *queue);
int len(Queue *queue);
void clear(Queue *queue);
Queue *init();

#endif