#include "clique.h"
int extend_clique(Node **clique, int clique_size, Node **candidates, int candidate_size, int node_count, int *best_so_far)
{

  int *colors = malloc(sizeof(int) * candidate_size);
  int graph_gradient = greedy_coloring(candidates, candidate_size, colors);
  free(colors);
  if (candidate_size == 0 || clique_size + graph_gradient <= *best_so_far)
  {
    if (clique_size > *best_so_far)
      *best_so_far = clique_size;
    return clique_size;
  }

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
    int result = extend_clique(clique, clique_size + 1, new_candidates, new_count, node_count, best_so_far);
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
int greedy_coloring(Node **candidates, int candidate_size, int *colors)
{
  int max_color = 0;
  for (int i = 0; i < candidate_size; i++)
  {
    int color = 1;
    bool conflict;
    do
    {
      conflict = false;
      for (int j = 0; j < i; j++)
      {
        if (is_connected(candidates[i], candidates[j]) && colors[j] == color)
        {
          conflict = true;
          break;
        }
      }
      if (conflict)
        color++;
    } while (conflict);
    colors[i] = color;
    if (color > max_color)
      max_color = color;
  }
  return max_color;
}
