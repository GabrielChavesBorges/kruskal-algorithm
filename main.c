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
void int_push(int *array, int *array_size, int value);
void int_pop(int *array, int *array_size, int value);
void sort_by_weight_asc(Edge *edges, int n_edges);
Edge *kruskal(Edge *original_graph, int n_edges, int *solution_size);

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
    int mst_size = 0;
    int *mst_size_ptr = &mst_size;
    Edge *mst = kruskal(edges, n_edges, mst_size_ptr);
    printf("MST:\n");
    for (i = 0; i < mst_size; i++)
    {
        printf("%d -- %d --> %d\n", mst[i].start_node, mst[i].weight, mst[i].end_node);
    }
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

// INT PUSH
void int_push(int *array, int *array_size, int value)
{
    int j;
    int current_index = *array_size;
    (*array_size)++;
    int *temp_array = (int *)realloc(array, sizeof(int) * (*array_size));
    if (temp_array == NULL)
    {
        printf("ERROR in realloc for value %d, asking for %d bytes\n", value, sizeof(int) * (*array_size));
    }
    else
    {
        array = temp_array;
    }
    array[current_index] = value;
}

// INT POP
void int_pop(int *array, int *array_size, int value)
{
    int target_index = -1;
    int i;
    int limit = *array_size;
    // find target index
    for (i = 0; i < limit; i++)
    {
        if (array[i] == value)
        {
            target_index = i;
            break;
        }
    }
    // if value not found
    if (target_index == -1)
    {
        return;
    }
    limit--;
    // remove value
    for (i = target_index; i < limit; i++)
    {
        array[i] = array[i++];
    }
    // resize
    *array_size--;
    array = (int *)realloc(array, sizeof(int) * (*array_size));
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
Edge *kruskal(Edge *edges, int n_edges, int *solution_size)
{
    int i;
    int node_list_size = 0;
    int forest_size = 0;
    int *tree_size_list;
    int *node_list;
    Edge *solution;
    int **forest;

    node_list = (int *)malloc(node_list_size);
    tree_size_list = (int *)malloc(forest_size);
    solution = (Edge *)malloc(*solution_size);
    forest = (int **)malloc(forest_size);

    // Extract node list
    for (i = 0; i < n_edges; i++)
    {
        int start = edges[i].start_node;
        int j;
        bool is_start_in_list = is_contained(start, node_list, node_list_size);
        int end = edges[i].end_node;
        bool is_end_in_list = is_contained(end, node_list, node_list_size);

        if (!is_start_in_list)
        {
            int current_index = node_list_size;
            node_list_size++;
            int *temp_array = (int *)realloc(node_list, sizeof(int) * (node_list_size));
            if (temp_array == NULL)
            {
                printf("ERROR in realloc for value %d, asking for %d bytes\n", start, sizeof(int) * (node_list_size));
            }
            else
            {
                node_list = temp_array;
            }
            node_list[current_index] = start;
        }
        if (!is_end_in_list)
        {
            int current_index = node_list_size;
            node_list_size++;
            int *temp_array = (int *)realloc(node_list, sizeof(int) * (node_list_size));
            if (temp_array == NULL)
            {
                printf("ERROR in realloc for value %d, asking for %d bytes\n", end, sizeof(int) * (node_list_size));
            }
            else
            {
                node_list = temp_array;
            }
            node_list[current_index] = end;
        }
    }

    // sort edges by weight in ascending order
    sort_by_weight_asc(edges, n_edges);

    // set initial forest:
    forest_size = node_list_size;
    forest = (int **)realloc(forest, sizeof(int *) * (forest_size));
    tree_size_list = (int *)realloc(tree_size_list, sizeof(int) * forest_size);
    for (i = 0; i < forest_size; i++)
    {
        tree_size_list[i] = 1;
        forest[i] = (int *)malloc(sizeof(int) * tree_size_list[i]);
        forest[i][0] = node_list[i];
    }

    // for each edge:
    int edge_idx;
    for (edge_idx = 0; edge_idx < n_edges; edge_idx++)
    {
        // take the starting point and look for it in the forest.
        int tree_idx;
        for (tree_idx = 0; tree_idx < forest_size; tree_idx++)
        {
            int node_idx;
            int node_limit = tree_size_list[tree_idx];
            bool is_start_found = false;
            for (node_idx = 0; node_idx < node_limit; node_idx++)
            {
                if (forest[tree_idx][node_idx] == edges[edge_idx].start_node)
                {
                    is_start_found = true;
                    break;
                }
            }
            if (is_start_found)
            {
                // once we find it, check if the ending point is in the same tree
                bool is_end_found = false;
                for (node_idx = 0; node_idx < node_limit; node_idx++)
                {
                    if (forest[tree_idx][node_idx] == edges[edge_idx].end_node)
                    {
                        is_end_found = true;
                        break;
                    }
                }
                // if it is, continue to next edge without taking action
                if (is_end_found)
                {
                    break;
                }
                // if it's not
                // find tree where end node is
                int tree_idx_2;
                for (tree_idx_2 = 0; tree_idx_2 < forest_size; tree_idx_2++)
                {
                    int node_idx_2;
                    int node_2_limit = tree_size_list[tree_idx_2];
                    bool is_end_found = false;
                    for (node_idx_2 = 0; node_idx_2 < node_2_limit; node_idx_2++)
                    {
                        if (forest[tree_idx_2][node_idx_2] == edges[edge_idx].end_node)
                        {
                            is_end_found = true;
                            break;
                        }
                    }
                    if (is_end_found)
                    {
                        // copy all end node tree nodes to starting node tree
                        for (node_idx_2 = 0; node_idx_2 < node_2_limit; node_idx_2++)
                        {
                            int current_index = tree_size_list[tree_idx];
                            tree_size_list[tree_idx]++;
                            int *temp_array = (int *)realloc(forest[tree_idx], sizeof(int) * (tree_size_list[tree_idx]));
                            if (temp_array == NULL)
                            {
                                printf("ERROR in realloc for value %d, asking for %d bytes\n", forest[tree_idx_2][node_idx_2], sizeof(int) * (tree_size_list[tree_idx]));
                            }
                            else
                            {
                                forest[tree_idx] = temp_array;
                            }
                            forest[tree_idx][current_index] = forest[tree_idx_2][node_idx_2];
                        }
                        // remove end node tree
                        int tree_2_limit = forest_size - 1;
                        for (/*no init*/; tree_idx_2 < tree_2_limit; tree_idx_2++)
                        {
                            forest[tree_idx_2] = forest[tree_idx_2 + 1];
                            tree_size_list[tree_idx_2] = tree_size_list[tree_idx_2 + 1];
                        }
                        forest_size--;
                        forest = (int **)realloc(forest, sizeof(int *) * forest_size);
                        // add edge to solution set
                        int current_solution = *solution_size;
                        (*solution_size)++;
                        solution = (Edge *)realloc(solution, sizeof(Edge) * (*solution_size));
                        solution[current_solution] = edges[edge_idx];
                        break;
                    }
                }
                break;
            }
        }
        // check if forest size is 1, if it is, return answer
        if (forest_size == 1)
        {
            return solution;
        }
    }
    // If tree wasn't formed return null.
    // Edge error[] = {};
    return NULL;
}
