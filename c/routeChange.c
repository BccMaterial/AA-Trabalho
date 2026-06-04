#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int main() {
    int N, M, C, K;

    // Executa até que todos os parâmetros sejam zero
    while (scanf("%d %d %d %d", &N, &M, &C, &K) == 4 && (N || M || C || K)) {
        
        // Alocação e inicialização da matriz de adjacência
        int **adj = (int **)malloc(N * sizeof(int *));
        for (int i = 0; i < N; i++) {
            adj[i] = (int *)malloc(N * sizeof(int));
            for (int j = 0; j < N; j++) {
                adj[i][j] = INF;
            }
        }

        // Leitura das estradas
        for (int i = 0; i < M; i++) {
            int u, v, p;
            scanf("%d %d %d", &u, &v, &p);

            // Se ambas as cidades estão fora da rota de serviço, adiciona estrada bidirecional
            // Se u está na rota e v está fora, a estrada só pode ser percorrida de v para u
            if (u >= C && v >= C) {
                adj[u][v] = p;
                adj[v][u] = p;
            } else if (u < C && v >= C) {
                adj[v][u] = p;
            } else if (v < C && u >= C) {
                adj[u][v] = p;
            } else {
                // Se ambas estão na rota, só importa se forem consecutivas (u e u + 1)
                if (abs(u - v) == 1) {
                    if (u < v) adj[u][v] = p;
                    else adj[v][u] = p;
                }
            }
        }

        // Vetores auxiliares para o Algoritmo de Dijkstra
        int *dist = (int *)malloc(N * sizeof(int));
        int *visitado = (int *)malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) {
            dist[i] = INF;
            visitado[i] = 0;
        }

        dist[K] = 0; // Ponto de partida: cidade de conserto K

        // Dijkstra tradicional por busca linear do mínimo (N <= 250)
        for (int i = 0; i < N; i++) {
            int u = -1;
            int min_dist = INF;

            // Busca pelo vértice não visitado com menor distância
            for (int j = 0; j < N; j++) {
                if (!visitado[j] && dist[j] < min_dist) {
                    min_dist = dist[j];
                    u = j;
                }
            }

            if (u == -1 || dist[u] == INF) break;

            visitado[u] = 1;

            // Relaxamento das arestas adjacentes
            for (int v = 0; v < N; v++) {
                if (adj[u][v] != INF) {
                    if (dist[u] + adj[u][v] < dist[v]) {
                        dist[v] = dist[u] + adj[u][v];
                    }
                }
            }
        }

        // Resultado do caso de teste
        printf("%d\n", dist[C - 1]);

        // Liberação de memória temporária
        for (int i = 0; i < N; i++) free(adj[i]);
        free(adj);
        free(dist);
        free(visitado);
    }

    return 0;
}