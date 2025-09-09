#ifndef CLIQUE_H
#define CLIQUE_H
#include "definition.h"
int extend_clique(Node **clique, int clique_size, Node **candidates, int candidate_size, int node_count);
bool is_connected_to_all(Node *v, Node **clique, int size);
bool is_connected(Node *a, Node *b);
#endif