#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Function to add an edge to the adjacency list
void addEdge(vector<vector<int>>& adj, int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u); // Because it's an undirected graph
}

// BFS function
void bfs(vector<vector<int>>& adj, int s, vector<bool>& visited) {
    queue<int> q;

    visited[s] = true;
    q.push(s);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << curr << " ";

        for (int x : adj[curr]) {
            if (!visited[x]) {
                visited[x] = true;
                q.push(x);
            }
        }
    }
}

// Recursive function for DFS traversal
void DFSRec(vector<vector<int>>& adj, vector<bool>& visited, int s) {
    visited[s] = true;
    cout << s << " ";

    for (int i : adj[s]) {
        if (!visited[i]) {
            DFSRec(adj, visited, i);
        }
    }
}

// DFS function
void DFS(vector<vector<int>>& adj, int s) {
    vector<bool> visited(adj.size(), false);
    DFSRec(adj, visited, s);
}

int main() {
    int V = 5; // Number of vertices in the graph

    // Create an adjacency list for the graph
    vector<vector<int>> adj(V);

    // Add edges to the graph
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 4);

    cout << "BFS starting from vertex 0:\n";
    vector<bool> visitedBFS(V, false);
    bfs(adj, 0, visitedBFS);
    cout << "\n";

    cout << "DFS starting from vertex 0:\n";
    DFS(adj, 0);

    return 0;
}
