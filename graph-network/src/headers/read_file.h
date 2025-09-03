#ifndef READFILE_H
#define READFILE_H
#include "definition.h"

Node *read_file(const char *filename, int *node_count);
void verify_nodes(Node *starting_node, int line_count);
#endif