#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
using namespace std;

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    // Step 1: Build the graph as an adjacency list
    unordered_map<int, vector<pair<int, int>>> graph;
    for (const auto& edge : times) {
        int u = edge[0], v = edge[1], w = edge[2];
        graph[u].emplace_back(v, w);
    }

    // Step 2: Initialize distances and priority queue
    vector<int> dist(n + 1, INT_MAX);
    dist[k] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, k); // (distance, node)

    // Step 3: Dijkstra's algorithm
    while (!pq.empty()) {
        auto [currDist, node] = pq.top();
        pq.pop();

        // Skip if we already found a shorter path
        if (currDist > dist[node]) continue;

        for (const auto& [neighbor, weight] : graph[node]) {
            int newDist = currDist + weight;
            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                pq.emplace(newDist, neighbor);
            }
        }
    }

    // Step 4: Find the maximum distance
    int maxDist = 0;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INT_MAX) return -1; // Unreachable node
        maxDist = max(maxDist, dist[i]);
    }

    return maxDist;
}

int main() {
    vector<vector<int>> times1 = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    int n1 = 4, k1 = 2;
    cout << networkDelayTime(times1, n1, k1) << endl; // Output: 2

    vector<vector<int>> times2 = {{1, 2, 1}};
    int n2 = 2, k2 = 1;
    cout << networkDelayTime(times2, n2, k2) << endl; // Output: 1

    vector<vector<int>> times3 = {{1, 2, 1}};
    int n3 = 2, k3 = 2;
    cout << networkDelayTime(times3, n3, k3) << endl; // Output: -1

    return 0;
}
