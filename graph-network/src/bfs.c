#include "bfs.h"
TreeNode *build_spanning_tree_bfs(Node *root_node)
{
  if (!root_node)
    return NULL;

  TreeNode *root_tree = create_tree_node(root_node->id, NULL);

  Queue *q = init_queue();
  enqueue(q, root_node, root_tree);

  while (!is_empty_queue(q))
  {
    QueueNode *current_queue_node = dequeue(q);
    Node *current_node = current_queue_node->graph_node;
    TreeNode *current_tree_node = current_queue_node->tree_parent;

    if (!current_node->visited)
    {
      current_node->visited = true;

      for (int i = 0; i < current_node->connected_nodes_count; i++)
      {
        Node *child_graph = current_node->connected_nodes[i];
        if (!child_graph->visited)
        {
          TreeNode *child_tree = create_tree_node(child_graph->id, current_tree_node);
          add_child(current_tree_node, child_tree);

          enqueue(q, child_graph, child_tree);
        }
      }
    }
  }

  clear_queue(q);
  return root_tree;
}