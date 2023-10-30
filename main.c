#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GRAPH_FILE_PATH "./graphs/a.dat"
#define FSCANF_SUCCESS 3

typedef struct
{
    int start_node;
    int end_node;
    int weight;
} Edge;

// Prototypes
bool is_contained(int value, int *array, int array_size);
void sort_by_weight_asc(Edge *edges, int n_edges);
Edge *kruskal(Edge *original_graph, int n_edges);

// Main ------------------------------------------------------------------------------

int main()
{
    FILE *file_pointer;
    Edge *edges;
    int n_edges = 0;
    int temp_a, temp_b, temp_w;
    int i;

    file_pointer = fopen(GRAPH_FILE_PATH, "r");

    edges = malloc(n_edges);

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
        edges = (Edge *)realloc(edges, sizeof(Edge) * n_edges);
        edges[current].start_node = temp_a;
        edges[current].end_node = temp_b;
        edges[current].weight = temp_w;
    }
    // apply kruskal's algorithm
    return 0;
}

// Functions ------------------------------------------------------------------------------

// IS CONTAINED
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

// MERGE SORT
void merge_sort(int start, int end, Edge *edges, Edge *temp)
{
    int half, l1, l2, i;

    if (start < end)
    {
        half = (start + end) / 2;
        merge_sort(start, half, edges, temp);
        merge_sort(half + 1, end, edges, temp);
        for (l1 = start, l2 = half + 1, i = start; l1 <= half && l2 <= end; i++)
        {
            if (edges[l1].weight <= edges[l2].weight)
                temp[i] = edges[l1++];
            else
                temp[i] = edges[l2++];
        }

        while (l1 <= half)
        {
            temp[i] = edges[l1];
            i++;
            l1++;
        }

        while (l2 <= end)
        {
            temp[i++] = edges[l2++];
        }

        for (i = start; i <= end; i++)
        {
            edges[i] = temp[i];
        }
    }
    else
    {
        return;
    }
}

// SORT BY WEIGHT ASC
void sort_by_weight_asc(Edge *edges, int n_edges)
{
    Edge *temp = malloc(sizeof(Edge) * n_edges);
    merge_sort(0, n_edges - 1, edges, temp);
}

// KRUSKAL
Edge *kruskal(Edge *original_graph, int n_edges)
{
    int i;
    int pending_list_size = 0;
    int *pending_list;

    pending_list = malloc(pending_list_size);
    // Extract node list (pending list)
    for (i = 0; i < n_edges; i++)
    {
        if (!is_contained(original_graph[i].start_node, pending_list, pending_list_size))
        {
            int current_node = pending_list_size;
            pending_list_size++;
            pending_list = (int *)realloc(pending_list, sizeof(int) * pending_list_size);
            pending_list[current_node] = original_graph[i].start_node;
        }
        if (!is_contained(original_graph[i].end_node, pending_list, pending_list_size))
        {
            int current_node = pending_list_size;
            pending_list_size++;
            pending_list = (int *)realloc(pending_list, sizeof(int) * pending_list_size);
            pending_list[current_node] = original_graph[i].end_node;
        }
    }
    // sort edges by weight in ascending order
    sort_by_weight_asc(original_graph, n_edges);
    // for each edge:
    // check if starting or ending node is in pending list
    // if none is:
    // skip
    // if only one is:
    // add edge to solution
    // remove node from pending list
    // check partial list for node, recursive removal of other partial list items
    // if pending list is empty, break
    // if both are:
    // if exact path is not already in partial list:
    // add node to partial list
}
