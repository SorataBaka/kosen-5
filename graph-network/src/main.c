#include "stack.h"
#include "read_file.h"
#include "log.h"
#include "bfs.h"
#include "dfs.h"
#include <time.h>

int main(int argc, char **argv)
{
  if (argc < 2 || argc > 2)
  {
    perror("Insufficient arguments");
    exit(EXIT_FAILURE);
  }
  int line_count;

  Node *starting_node = read_file(argv[1], &line_count);
  TreeNode *root_tree = build_spanning_tree_bfs(starting_node);
  printf("%d\n", line_count);
  int depth = get_tree_depth(root_tree);
  int leaves = count_leaves(root_tree);
  int max_branch = max_branching(root_tree);
  double symmetry = compute_symmetry(root_tree, line_count);
  int diameter = get_diameter(root_tree);
  printf("node_count: %d, depth: %d, leaves: %d, max_branch: %d, symmetry: %.09f, diameter: %d\n", line_count, depth, leaves, max_branch, symmetry, diameter);

  return 0;
}