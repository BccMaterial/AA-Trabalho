#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        if (m == 0) return -1;
        int n = grid[0].size();

        queue<pair<int, int>> bfs;
        int freshCount = 0;

        // Passo 3: varredura inicial para contar laranjas frescas e inserir laranjas podres na fila
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 2) {
                    bfs.push({i, j});
                } else if (grid[i][j] == 1) {
                    freshCount++;
                }
            }
        }

        // Passo 4: se não há laranjas frescas, retorne 0 imediatamente
        if (freshCount == 0) {
            return 0;
        }

        int minutes = 0;
        const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // Passo 5: BFS multi-source, processa um nível por minuto
        while (!bfs.empty()) {
            int levelSize = bfs.size();
            bool rottenThisMinute = false;

            for (int k = 0; k < levelSize; ++k) {
                auto [r, c] = bfs.front();
                bfs.pop();

                for (auto [dr, dc] : directions) {
                    int nr = r + dr;
                    int nc = c + dc;

                    // Passo 6: vizinho válido com laranja fresca
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                        grid[nr][nc] = 2; // apodrece a laranja fresca
                        freshCount--;     // decrementa contador de frescas
                        bfs.push({nr, nc});
                        rottenThisMinute = true;
                    }
                }
            }

            // Incrementa o tempo apenas quando algum novo nó foi processado neste nível
            if (rottenThisMinute) {
                minutes++;
            }
        }

        // Passo 7: se ainda há laranjas frescas, não é possível apodrecer tudo
        return freshCount > 0 ? -1 : minutes;
    }
};

#ifdef LOCAL_TEST
int main() {
    vector<vector<int>> grid = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };

    int resultado = Solution().orangesRotting(grid);
    cout << "Resultado: " << resultado << endl;
    // Saída esperada: 4

    return 0;
}
#endif
