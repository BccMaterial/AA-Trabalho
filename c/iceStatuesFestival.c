#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;

    while (T--) {
        int N, M;
        if (scanf("%d %d", &N, &M) != 2) break;

        int *blocos = (int *)malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) {
            scanf("%d", &blocos[i]);
        }

        // Alocação da tabela DP para o tamanho M
        int *dp = (int *)malloc((M + 1) * sizeof(int));
        
        // Inicialização da tabela
        dp[0] = 0;
        for (int i = 1; i <= M; i++) {
            dp[i] = INF;
        }

        // Construção Bottom-Up
        for (int i = 1; i <= M; i++) {
            for (int j = 0; j < N; j++) {
                if (blocos[j] <= i) {
                    int num_blocos = dp[i - blocos[j]] + 1;
                    if (num_blocos < dp[i]) {
                        dp[i] = num_blocos;
                    }
                }
            }
        }

        // Impressão do resultado
        printf("%d\n", dp[M]);

        free(blocos);
        free(dp);
    }

    return 0;
}