#include "stack.h"
#include "read_file.h"
#include "log.h"
#include "bfs.h"
#include "dfs.h"
#include "clique.h"
#include <time.h>
#include "connected_components.h"

int main(int argc, char **argv)
{
  if (argc < 2 || argc > 2)
  {
    perror("Insufficient arguments");
    exit(EXIT_FAILURE);
  }
  int line_count;
  Node *starting_node = read_file(argv[1], &line_count); // This is also just an array of all the nodes.
  // Node **node_pointer_array = (Node **)malloc(sizeof(Node *) * line_count);
  // Node **clique = (Node **)malloc(sizeof(Node *) * line_count);
  // for (int i = 0; i < line_count; i++)
  // {
  //   node_pointer_array[i] = &starting_node[i];
  // }
  // int biggest_clique = extend_clique(clique, 0, node_pointer_array, line_count, line_count);
  // printf("Biggest Clique: %d\n", biggest_clique);

  // This is mostly for the third task
  // int dfs_connected_count = count_connected_dfs(starting_node, line_count);
  // int bfs_connected_cou4 nt = count_connected_bfs(starting_node, line_count);

  // printf("DFS Connected Node Count %d\n", dfs_connected_count);
  // printf("BFS Connected Node Count %d\n", bfs_connected_count);

  // This is mostly for the first and second task
  TreeNode *root_tree = build_spanning_tree_bfs(starting_node);
  int depth = get_tree_depth(root_tree);
  int leaves = count_leaves(root_tree);
  int max_branch = max_branching(root_tree);
  double symmetry = compute_symmetry(root_tree, line_count);
  int diameter = get_diameter(root_tree);
  printf("node_count: %d, depth: %d, leaves: %d, max_branch: %d, symmetry: %.09f, diameter: %d\n", line_count, depth, leaves, max_branch, symmetry, diameter);

  return 0;
}