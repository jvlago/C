#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX_NODE_SIZE 20

typedef struct Nodes_t{
    int sdist;
    struct Nodes_t *prev;
    int visited;
    int index;
} Nodes_t;

char get_node_name(int idx) {
    return 'A' + idx;
}

int min_distance(Nodes_t* node, int node_size) {
    int min = INT_MAX, min_index = -1;
    for (int i = 0; i < node_size; i++) {
        if (!node[i].visited && node[i].sdist < min) {
            min = node[i].sdist;
            min_index = i;
        }
    }
    return min_index;
}

int main() {
    int node_size, init, target;
    printf("Enter number of nodes (2-%d): ", MAX_NODE_SIZE);
    scanf("%d", &node_size);
    if (node_size < 2 || node_size > MAX_NODE_SIZE) {
        printf("Invalid size.\n");
        return 1;
    }
    Nodes_t* node = (Nodes_t*)malloc(sizeof(Nodes_t) * node_size);
    for (int i = 0; i < node_size; i++) {
        node[i].sdist = INT_MAX;
        node[i].prev = NULL;
        node[i].visited = 0;
        node[i].index = i;
    }
    printf("Do you want to enter the adjacency matrix manually? (1 for yes, 0 for no): ");
    int manual_input;
    scanf("%d", &manual_input);
    if (manual_input < 0 || manual_input > 1) {
        printf("Invalid input. Please enter 1 for yes or 0 for no.\n");
        free(node);
        return 1;
    }
    int** distance = (int**)malloc(node_size * sizeof(int*));
    // Matriz de adjacência (manual)
    if(manual_input == 1){
        for (int i = 0; i < node_size; i++) {
            distance[i] = (int*)malloc(node_size * sizeof(int));
            for (int j = 0; j < node_size; j++) {
                if (i == j)
                    distance[i][j] = 0;
                else {
                    printf("Node %c to %c: ", get_node_name(i), get_node_name(j));
                    scanf("%d", &distance[i][j]);
                    if (distance[i][j] < 0) {
                        printf("Invalid distance. Please enter a non-negative value.\n");
                        free(node);
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
    printf("\n");
    printf("Enter start node index (0-%d): ", node_size-1);
    scanf("%d", &init);
    printf("Enter target node index (0-%d): ", node_size-1);
    scanf("%d", &target);
    if (init < 0 || init >= node_size || target < 0 || target >= node_size) {
        printf("Invalid node index.\n");
        for (int i = 0; i < node_size; i++)
            free(distance[i]);
        free(distance);
        free(node);
        return 1;
    }
    // Dijkstra
    node[init].sdist = 0;
    for (int count = 0; count < node_size; count++) {
        int u = min_distance(node, node_size);
        if (u == -1) break;
        node[u].visited = 1;
        for (int v = 0; v < node_size; v++) {
            if (!node[v].visited && distance[u][v] && node[u].sdist != INT_MAX && node[u].sdist + distance[u][v] < node[v].sdist) {
                node[v].sdist = node[u].sdist + distance[u][v];
                node[v].prev = &node[u];
            }
        }
    }
    // Resultado
    printf("Shortest path from %c to %c: ", get_node_name(init), get_node_name(target));
    int path[MAX_NODE_SIZE];
    int path_len = 0;
    int current = target;
    while (current != init && node[current].prev != NULL) {
        path[path_len++] = current;
        current = node[current].prev->index;
    }
    if (current == init) {
        path[path_len++] = init;
        for (int i = path_len - 1; i >= 0; i--) {
            printf("%c", get_node_name(path[i]));
            if (i > 0)
                printf(" -> ");
        }
        printf("\nTotal distance: %d\n", node[target].sdist);
    } else {
        printf("No path found.\n");
    }
    for (int i = 0; i < node_size; i++)
        free(distance[i]);
    free(distance);
    free(node);
    return 0;
}