#ifndef CLIQUE_H
#define CLIQUE_H
#include "definition.h"
int extend_clique(Node **clique, int clique_size, Node **candidates, int candidate_size, int node_count, int * best_so_far);
bool is_connected_to_all(Node *v, Node **clique, int size);
bool is_connected(Node *a, Node *b);
int greedy_coloring(Node **candidates, int candidate_size, int *colors);
#endif