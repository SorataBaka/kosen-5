#include "bfs.h"
#include <stdio.h>
#include <stdlib.h>

TreeNode *build_spanning_tree_bfs(Node *root_node)
{
  if (!root_node)
    return NULL;

  TreeNode *root_tree = create_tree_node(root_node->id, NULL);
  Queue *q = init_queue();

  int queue_size = 0; // queue length counter

  // open log file
  FILE *logf = fopen("queue_log.csv", "w");
  if (!logf)
  {
    perror("fopen");
    exit(1);
  }
  fprintf(logf, "op,id,queue_size\n"); // header

  root_node->visited = true;
  enqueue(q, root_node, root_tree);
  queue_size++;
  fprintf(logf, "enqueue,%d,%d\n", root_node->id, queue_size);

  while (!is_empty_queue(q))
  {
    QueueNode *current_queue_node = dequeue(q);
    queue_size--;
    fprintf(logf, "dequeue,%d,%d\n",
            current_queue_node->graph_node->id, queue_size);

    Node *current_node = current_queue_node->graph_node;
    TreeNode *current_tree_node = current_queue_node->tree_parent;

    for (int i = 0; i < current_node->connected_nodes_count; i++)
    {
      Node *child_graph = current_node->connected_nodes[i];
      if (!child_graph->visited)
      {
        child_graph->visited = true;
        TreeNode *child_tree = create_tree_node(child_graph->id, current_tree_node);
        add_child(current_tree_node, child_tree);
        enqueue(q, child_graph, child_tree);
        queue_size++;
        fprintf(logf, "enqueue,%d,%d\n", child_graph->id, queue_size);
      }
    }
    free(current_queue_node);
  }

  fclose(logf);
  clear_queue(q);
  return root_tree;
}
