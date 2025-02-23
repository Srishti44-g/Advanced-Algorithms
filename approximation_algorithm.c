#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6 // Number of vertices

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// Function to print the shortest distance from source
void printSolution(int dist[]) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t %d\n", i, dist[i]);
}

// Dijkstra's algorithm for shortest path
void dijkstra(int graph[V][V], int src) {
    int dist[V]; // Stores shortest distance from src
    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest path tree

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printSolution(dist);
}

int main() {
    int graph[V][V] = {
        {0, 10, 0, 0, 0, 0},
        {10, 0, 20, 0, 0, 0},
        {0, 20, 0, 5, 0, 0},
        {0, 0, 5, 0, 15, 0},
        {0, 0, 0, 15, 0, 30},
        {0, 0, 0, 0, 30, 0}
    };
    
    dijkstra(graph, 0);
    return 0;
}
