#include "clique.h"
int extend_clique(Node **clique, int clique_size, Node **candidates, int candidate_size, int node_count)
{
  if (candidate_size == 0)
    return clique_size;

  int max_clique_size = clique_size;

  for (int i = 0; i < candidate_size; i++)
  {
    Node *v = candidates[i];
    Node **new_candidates = malloc(sizeof(Node *) * node_count);
    int new_count = 0;

    clique[clique_size] = v; // add v first

    for (int j = 0; j < candidate_size; j++)
    {
      if (i == j)
        continue;
      Node *u = candidates[j];
      if (is_connected_to_all(u, clique, clique_size + 1)) // include v now
        new_candidates[new_count++] = u;
    }

    clique[clique_size] = v;
    int result = extend_clique(clique, clique_size + 1, new_candidates, new_count, node_count);
    if (result > max_clique_size)
      max_clique_size = result;

    free(new_candidates);
  }

  return max_clique_size;
}

bool is_connected_to_all(Node *v, Node **clique, int size)
{
  for (int i = 0; i < size; i++)
  {
    if (!is_connected(v, clique[i]))
      return false;
  }
  return true;
}
bool is_connected(Node *a, Node *b)
{
  for (int i = 0; i < a->connected_nodes_count; i++)
  {
    if (a->connected_nodes[i] == b)
    {
      return true;
    }
  }
  return false;
}