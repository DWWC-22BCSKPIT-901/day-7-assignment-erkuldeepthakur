#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int m = mat.size();
    int n = mat[0].size();
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
    queue<pair<int, int>> q;

    // Initialize the queue with all 0 cells
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mat[i][j] == 0) {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    // Directions for moving in the matrix
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // BFS
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (auto [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            // Check bounds and whether the cell is visited
            if (nx >= 0 && ny >= 0 && nx < m && ny < n && dist[nx][ny] == INT_MAX) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return dist;
}

int main() {
    vector<vector<int>> mat1 = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    vector<vector<int>> mat2 = {{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};

    vector<vector<int>> result1 = updateMatrix(mat1);
    vector<vector<int>> result2 = updateMatrix(mat2);

    // Print results
    for (const auto& row : result1) {
        for (int cell : row) cout << cell << " ";
        cout << endl;
    }
    cout << endl;

    for (const auto& row : result2) {
        for (int cell : row) cout << cell << " ";
        cout << endl;
    }

    return 0;
}
