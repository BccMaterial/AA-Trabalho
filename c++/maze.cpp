#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    // Complexidade de tempo: O(m * n)
    // Complexidade de espaço: O(m * n) no pior caso para a fila, mas sem matriz extra de visitados.
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int m = maze.size();
        int n = maze[0].size();

        // Movimentos possíveis no grafo implícito: cima, baixo, esquerda, direita.
        vector<pair<int,int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}
        };

        queue<tuple<int,int,int>> bfsQueue;
        int startRow = entrance[0];
        int startCol = entrance[1];

        // Marca a célula de entrada como visitada no próprio labirinto para evitar matriz extra.
        maze[startRow][startCol] = '+';
        bfsQueue.emplace(startRow, startCol, 0);

        // A grelha é um grafo não ponderado: cada célula livre '.' é um vértice,
        // e cada adjacência entre células livres é uma aresta de peso unitário.
        while (!bfsQueue.empty()) {
            auto [row, col, steps] = bfsQueue.front();
            bfsQueue.pop();

            // Expansão nível a nível: cada iteração processa um vértice (célula)
            // e adiciona todos os vizinhos não visitados ao fim da fila.
            for (auto& dir : directions) {
                int nextRow = row + dir.first;
                int nextCol = col + dir.second;

                // Verifica se o vizinho está dentro dos limites da grelha.
                if (nextRow < 0 || nextRow >= m || nextCol < 0 || nextCol >= n) {
                    continue;
                }

                // Só podemos caminhar por células livres '.'.
                if (maze[nextRow][nextCol] != '.') {
                    continue;
                }

                // Marca como visitado assim que inserimos na fila para evitar revisitas.
                maze[nextRow][nextCol] = '+';

                // Verifica se esse vizinho é uma saída válida.
                bool isBorderCell = nextRow == 0 || nextRow == m - 1 ||
                                    nextCol == 0 || nextCol == n - 1;

                if (isBorderCell) {
                    // Se for uma borda e não for a entrada, encontramos a saída mais próxima.
                    return steps + 1;
                }

                bfsQueue.emplace(nextRow, nextCol, steps + 1);
            }
        }

        // Se a fila esgotar e não encontramos saída, não há caminho.
        return -1;
    }
};