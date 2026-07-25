#include <stdio.h>

#define INF 1000000000

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int graph[100][100];
    int dist[100], visited[100], parent[100];

    // Initialize graph
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            graph[i][j] = INF;
    }

    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
    }

    int S, D;
    scanf("%d %d", &S, &D);

    // Initialize Dijkstra
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[S] = 0;

    // Dijkstra Algorithm
    for (int count = 0; count < n; count++) {

        int u = -1;
        int min = INF;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != INF && !visited[v]) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // Destination unreachable
    if (dist[D] == INF) {
        printf("UNREACHABLE\n");
        return 0;
    }

    // Print minimum time
    printf("%d\n", dist[D]);

    // Reconstruct path
    int path[100];
    int count = 0;

    int temp = D;
    while (temp != -1) {
        path[count++] = temp;
        temp = parent[temp];
    }

    // Print path
    for (int i = count - 1; i >= 0; i--)
        printf("%d ", path[i]);

    printf("\n");

    return 0;
}