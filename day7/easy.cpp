#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
    // Create an adjacency list
    vector<vector<int>> graph(n);
    for (const auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }

    // BFS setup
    queue<int> q;
    vector<bool> visited(n, false);

    q.push(source);
    visited[source] = true;

    // BFS traversal
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        // If destination is found, return true
        if (node == destination) {
            return true;
        }

        // Visit neighbors
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    // If traversal completes without finding the destination
    return false;
}

int main() {
    // Example 1
    int n1 = 3;
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {2, 0}};
    int source1 = 0, destination1 = 2;
    cout << (validPath(n1, edges1, source1, destination1) ? "true" : "false") << endl;

    // Example 2
    int n2 = 6;
    vector<vector<int>> edges2 = {{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}};
    int source2 = 0, destination2 = 5;
    cout << (validPath(n2, edges2, source2, destination2) ? "true" : "false") << endl;

    return 0;
}

