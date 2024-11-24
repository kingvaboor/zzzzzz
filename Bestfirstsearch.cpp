// C++ program to implement Best-First Search using priority queue
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Alias for a pair of integers (cost, node)
using NodeCostPair = pair<int, int>;

// Graph represented as an adjacency list
vector<vector<NodeCostPair>> adjList;

// Function to add bidirectional edges with weights
void addEdge(int src, int dest, int weight) {
    adjList[src].push_back({weight, dest});
    adjList[dest].push_back({weight, src});
}

// Function to perform Best-First Search from startNode to endNode
void bestFirstSearch(int startNode, int endNode, int totalNodes) {
    // Vector to keep track of visited nodes
    vector<bool> isVisited(totalNodes, false);

    // Priority queue for exploring nodes with minimum cost first (min-heap)
    priority_queue<NodeCostPair, vector<NodeCostPair>, greater<NodeCostPair>> minHeap;
    minHeap.push({0, startNode});
    isVisited[startNode] = true;

    // Perform search until all nodes are explored or target is reached
    while (!minHeap.empty()) {
        int currentNode = minHeap.top().second;
        cout << currentNode << " ";  // Output the path
        minHeap.pop();

        // If the target node is reached, exit the loop
        if (currentNode == endNode) {
            break;
        }

        // Explore all neighboring nodes of the current node
        for (const auto& neighbor : adjList[currentNode]) {
            int neighborNode = neighbor.second;
            int pathCost = neighbor.first;

            // Only add unvisited neighbors to the priority queue
            if (!isVisited[neighborNode]) {
                isVisited[neighborNode] = true;
                minHeap.push({pathCost, neighborNode});
            }
        }
    }
    cout << endl;
}

// Main function to test Best-First Search
int main() {
    // Number of nodes in the graph
    int nodeCount = 14;
    adjList.resize(nodeCount);

    // Adding edges with their respective weights
    addEdge(0, 1, 3);
    addEdge(0, 2, 6);
    addEdge(0, 3, 5);
    addEdge(1, 4, 9);
    addEdge(1, 5, 8);
    addEdge(2, 6, 12);
    addEdge(2, 7, 14);
    addEdge(3, 8, 7);
    addEdge(8, 9, 5);
    addEdge(8, 10, 6);
    addEdge(9, 11, 1);
    addEdge(9, 12, 10);
    addEdge(9, 13, 2);

    int start = 0;  // Starting node
    int goal = 9;   // Target node

    // Call the Best-First Search function
    bestFirstSearch(start, goal, nodeCount);

    return 0;
}
