#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NODE_SIZE 20

typedef struct {
    int u;
    int v;
    int weight;
} Edge_t;

typedef struct {
    int parent;
    int rank;
} Subset_t;

char get_node_name(int idx) {
    return 'A' + idx;
}

int compare_edges(const void* a, const void* b) {
    return ((Edge_t*)a)->weight - ((Edge_t*)b)->weight;
}

int find(Subset_t subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void union_sets(Subset_t subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int main() {
    int node_size;
    printf("Enter number of nodes (2-%d): ", MAX_NODE_SIZE);
    scanf("%d", &node_size);
    if (node_size < 2 || node_size > MAX_NODE_SIZE) {
        printf("Invalid size.\n");
        return 1;
    }
    printf("Do you want to enter the adjacency matrix manually? (1 for yes, 0 for no): ");
    int manual_input;
    scanf("%d", &manual_input);
    if (manual_input < 0 || manual_input > 1) {
        printf("Invalid input.\n");
        return 1;
    }
    int** distance = (int**)malloc(node_size * sizeof(int*));
    // Matriz de adjacência (manual)
    for (int i = 0; i < node_size; i++)
        distance[i] = (int*)malloc(node_size * sizeof(int));
    if (manual_input == 1) {
        for (int i = 0; i < node_size; i++) {
            for (int j = 0; j < node_size; j++) {
                if (i == j)
                    distance[i][j] = 0;
                else {
                    printf("Node %c to %c: ", get_node_name(i), get_node_name(j));
                    scanf("%d", &distance[i][j]);
                    if (distance[i][j] < 0) {
                        printf("Invalid distance. Please enter a non-negative value.\n");
                        for (int k = 0; k <= i; k++)
                            free(distance[k]);
                        free(distance);
                        return 1;
                    }
                }
            }
        }
    }
    // Matriz aleatória (autofill 1-9)
    else{
        srand((unsigned)time(NULL));
        for (int i = 0; i < node_size; i++) {
            distance[i] = (int*)malloc(node_size * sizeof(int));
            for (int j = 0; j < node_size; j++) {
                if (i == j)
                    distance[i][j] = 0;
                else
                    distance[i][j] = (rand() % 2) ? (rand() % 9 + 1) : 0;
            }
        }
    }
    // Printa a matriz gerada
    printf("\nAdjacency Matrix:\n  ");
    for (int i = 0; i < node_size; i++) printf("%c ", get_node_name(i));
    printf("\n");
    for (int i = 0; i < node_size; i++) {
        printf("%c ", get_node_name(i));
        for (int j = 0; j < node_size; j++) {
            printf("%d ", distance[i][j]);
        }
        printf("\n");
    }
    // Coleta arestas válidas
    Edge_t* edges = malloc(node_size * node_size * sizeof(Edge_t));
    int edge_count = 0;
    for (int i = 0; i < node_size; i++) {
        for (int j = i + 1; j < node_size; j++) {
            if (distance[i][j] > 0) {
                edges[edge_count++] = (Edge_t){i, j, distance[i][j]};
            }
        }
    }
    // Ordena arestas
    qsort(edges, edge_count, sizeof(Edge_t), compare_edges);
    // Inicializa conjuntos
    Subset_t* subsets = malloc(node_size * sizeof(Subset_t));
    for (int i = 0; i < node_size; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }
    printf("\nMinimum Spanning Tree:\n");
    int total_weight = 0;
    for (int i = 0, e = 0; e < node_size - 1 && i < edge_count; i++) {
        Edge_t next = edges[i];
        int x = find(subsets, next.u);
        int y = find(subsets, next.v);
        if (x != y) {
            printf("%c -> %c == %d\n", get_node_name(next.u), get_node_name(next.v), next.weight);
            total_weight += next.weight;
            union_sets(subsets, x, y);
            e++;
        }
    }
    printf("Total weight of MST: %d\n", total_weight);
    // Libera memória
    for (int i = 0; i < node_size; i++)
        free(distance[i]);
    free(distance);
    free(edges);
    free(subsets);
    return 0;
}
