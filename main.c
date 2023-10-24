#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GRAPH_FILE_PATH "./graphs/a.dat"
#define FSCANF_SUCCESS 3

struct edge {
    int start_node;
    int end_node;
    int weight;
};

int main() {
    FILE* file_pointer;
    struct edge* edges;
    int n_edges = 0;
    int temp_a, temp_b, temp_w;
    int i;

    file_pointer = fopen(GRAPH_FILE_PATH, "r");

    edges = malloc(n_edges);

    while (true) {
        int operation_result;
        int current;
        operation_result = fscanf(file_pointer, "%d %d %d", &temp_a, &temp_b, &temp_w);
        if (operation_result != FSCANF_SUCCESS) {
            break;
        }
        current = n_edges;
        n_edges++;
        edges = (struct edge*) realloc (edges, sizeof(struct edge) * n_edges);
        edges[current].start_node = temp_a;
        edges[current].end_node = temp_b;
        edges[current].weight = temp_w;
    }

    for (i = 0; i < n_edges; i++) {
        printf("Edge %d: %d %d %d\n", i + 1, edges[i].start_node, edges[i].end_node, edges[i].weight);
    }

    // apply kruskal's algorithm
    return 0;
}