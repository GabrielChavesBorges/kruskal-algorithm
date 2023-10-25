#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GRAPH_FILE_PATH "./graphs/a.dat"
#define FSCANF_SUCCESS 3

bool is_contained(int value, int *array, int array_size);

struct edge
{
    int start_node;
    int end_node;
    int weight;
};

int main()
{
    FILE *file_pointer;
    struct edge *edges;
    int *node_list;
    int n_edges = 0;
    int node_list_size = 0;
    int temp_a, temp_b, temp_w;
    int i;

    file_pointer = fopen(GRAPH_FILE_PATH, "r");

    edges = malloc(n_edges);
    node_list = malloc(node_list_size);

    while (true)
    {
        int operation_result;
        int current;
        int is_unique_node = true;
        operation_result = fscanf(file_pointer, "%d %d %d", &temp_a, &temp_b, &temp_w);
        if (operation_result != FSCANF_SUCCESS)
        {
            break;
        }
        current = n_edges;
        n_edges++;
        edges = (struct edge *)realloc(edges, sizeof(struct edge) * n_edges);
        edges[current].start_node = temp_a;
        edges[current].end_node = temp_b;
        edges[current].weight = temp_w;

        if (!is_contained(temp_a, node_list, node_list_size))
        {
            int current_node = node_list_size;
            node_list_size++;
            node_list = (int *)realloc(node_list, sizeof(int) * node_list_size);
            node_list[current_node] = temp_a;
        }
        if (!is_contained(temp_b, node_list, node_list_size))
        {
            int current_node = node_list_size;
            node_list_size++;
            node_list = (int *)realloc(node_list, sizeof(int) * node_list_size);
            node_list[current_node] = temp_b;
        }
    }

    // apply kruskal's algorithm
    return 0;
}

bool is_contained(int value, int *array, int array_size)
{
    int i;
    for (i = 0; i < array_size; i++)
    {
        if (array[i] == value)
        {
            return true;
        }
    }
    return false;
}

