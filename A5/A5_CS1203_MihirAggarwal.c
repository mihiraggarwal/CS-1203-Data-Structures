// Assignment additions: Modified printSolution(), floydWarshall(), main()

#include <stdio.h>
 
#define V 4
#define INF 99999
 
/* A utility function to print solution */
void printSolution(int dist[][V], int parent[][V])
{
    printf(
        "The following matrix shows the shortest distances"
        " between every pair of vertices \n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            int n = parent[i][j], k = 0;
            int t = j;
            int path[V];

            if (n != -1) {
                printf("Path from %d to %d: ", i, j);
                while (n != -1) {
                    path[k++] = n;
                    t = parent[i][t];
                    n = parent[i][t];
                }

                for (int p = k-1; p > -1; p--) {
                    printf("%d -> ", path[p]);
                }
                printf("%d\n", j);
            }
        }
    }
}
 
void floydWarshall(int dist[][V], int parent[][V])
{
    int i, j, k;
 
    for (k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for (i = 0; i < V; i++) {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < V; j++) {
                // If vertex k is on the shortest path from
                // i to j, then update the value of
                // dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }
 
    // Print the shortest distance matrix
    printSolution(dist, parent);
}
 
 
// driver's code
int main()
{
    /* Let us create the following weighted graph
            10
       (0)------->(3)
        |         /|\
      5 |          |
        |          | 1
       \|/         |
       (1)------->(2)
            3           */
    int graph[V][V] = { { 0, 5, INF, 10 },
                        { INF, 0, 3, INF },
                        { INF, INF, 0, 1 },
                        { INF, INF, INF, 0 } };
    
    int parent[V][V];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if ((graph[i][j] == 0) || (graph[i][j] == INF)) parent[i][j] = -1;
            else parent[i][j] = i;
        }
    }
 
    // Function call
    floydWarshall(graph, parent);
    
    return 0;
}
