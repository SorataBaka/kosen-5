#include "read_file.h"

Node *read_file(const char *filename, int *node_count)
{
  // First, read the file
  FILE *input_pointer = fopen(filename, "r");
  if (!input_pointer)
  {
    perror("Error opening file");
    return NULL;
  }
  else
  {
    printf("File opened successfully.\n");
  }

  // Find out how many lines are in the file
  int lines = 0;
  char c;
  while ((c = fgetc(input_pointer)) != EOF)
    if (c == '\n')
      lines++;
  *node_count = lines;

  rewind(input_pointer);

  // Create an adjacency matrix
  int **adjacency_matrix = (int **)malloc(sizeof(int *) * lines);
  for (int i = 0; i < lines; i++)
  {
    adjacency_matrix[i] = (int *)malloc(sizeof(int) * lines);
  }

  // Read the file
  int row, column;
  row = column = 0;
  char ch;
  while ((ch = fgetc(input_pointer)) != EOF && row < lines)
  {
    if (ch == '0' || ch == '1')
    {
      adjacency_matrix[row][column] = ch - '0';
      column++;
      if (column == lines)
      {
        column = 0;
        row++;
      }
    }
  }

  Node *nodes = (Node *)malloc(sizeof(Node) * lines);
  for (int i = 0; i < lines; i++)
  {
    nodes[i].id = i + 1;
    nodes[i].visited = false;
    nodes[i].connected_nodes_count = 0;
    // Count how many connected nodes
    for (int index = 0; index < lines; index++)
    {
      if (adjacency_matrix[i][index] == 1)
        nodes[i].connected_nodes_count++;
    }

    nodes[i].connected_nodes = (Node **)malloc(sizeof(Node *) * nodes[i].connected_nodes_count);
    int index = 0;
    for (int j = 0; j < lines; j++)
    {
      if (adjacency_matrix[i][j] == 1)
      {
        nodes[i].connected_nodes[index++] = &nodes[j];
      }
    }
  }
  fclose(input_pointer);
  free(adjacency_matrix);
  return nodes;
}
void verify_nodes(Node *starting_node, int line_count)
{
  for (int i = 0; i < line_count; i++)
  {
    printf("Node id: %d , connected to: ", starting_node[i].id);
    int actual_count = 0;
    for (int index = 0; index < starting_node[i].connected_nodes_count; index++)
    {
      printf("%d ", starting_node[i].connected_nodes[index]->id);
      actual_count++;
    }

    printf(" Reported %d Actual %d\n", starting_node[i].connected_nodes_count, actual_count);
  }
}