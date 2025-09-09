#ifndef CONNECTED_COMPONENTS_H
#define CONNECTED_COMPONENTS_H
#include "definition.h"
#include "spanning_tree.h"
#include "bfs.h"
#include "dfs.h"

int count_connected_dfs(Node *node_list, int node_count);
int count_connected_bfs(Node *node_list, int node_count);

#endif