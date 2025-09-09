#include "connected_components.h"

void reset_nodes(Node *node_list, int node_count)
{
  for (int i = 0; i < node_count; i++)
  {
    node_list[i].visited = false;
  }
}

int count_connected_dfs(Node *node_list, int node_count)
{
  reset_nodes(node_list, node_count);
  int connected_nodes_count = 0;
  for (int i = 0; i < node_count; i++)
  {
    if (node_list[i].visited == false)
    {
      TreeNode *tree_node = build_spanning_tree_dfs(node_list); // Perform dfs from that node if its not visited.
      free_tree(tree_node);
      connected_nodes_count++;
    }
  }
  return connected_nodes_count;
}
int count_connected_bfs(Node *node_list, int node_count)
{
  reset_nodes(node_list, node_count);
  int connected_nodes_count = 0;
  for (int i = 0; i < node_count; i++)
  {
    if (node_list[i].visited == false)
    {
      TreeNode *tree_node = build_spanning_tree_bfs(node_list); // Perform dfs from that node if its not visited.
      free_tree(tree_node);
      connected_nodes_count++;
    }
  }
  return connected_nodes_count;
}