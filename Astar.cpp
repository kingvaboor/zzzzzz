#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

class Vertex
{
public:
    string id;
    int estimate; // h(n): Heuristic estimate to target
    vector<pair<Vertex *, int>> neighbors;

    Vertex(string i, int h) : id(i), estimate(h) {}
};

vector<string> aStarSearch(Vertex *source, Vertex *target, map<Vertex *, int> &costs)
{
    // Min-heap where each element is a pair of (estimatedCost, vertex)
    priority_queue<pair<int, Vertex *>, vector<pair<int, Vertex *>>, greater<pair<int, Vertex *>>> minHeap;

    map<Vertex *, bool> visited;   // Track visited vertices
    map<Vertex *, Vertex *> trace; // Track the path

    costs[source] = 0; // g(n): Cost from source to source is 0
    minHeap.push({source->estimate, source}); // Push the source vertex with heuristic h(source)

    while (!minHeap.empty())
    {
        Vertex *current = minHeap.top().second;
        int currentEstimate = minHeap.top().first; // This cost is f(n) = g(n) + h(n)
        minHeap.pop();

        // If we reach the target, reconstruct the path
        if (current == target)
        {
            vector<string> path;
            int totalCost = costs[current]; // g(target) value
            while (current != source)
            {
                path.push_back(current->id);
                current = trace[current];
            }
            path.push_back(source->id);
            reverse(path.begin(), path.end());
            cout << "Total Cost: " << totalCost << endl;
            return path;
        }

        visited[current] = true;

        // Iterate through adjacent vertices
        for (auto &connection : current->neighbors)
        {
            Vertex *adjVertex = connection.first;
            int pathCost = connection.second;

            int newCost = costs[current] + pathCost; // g(adjVertex) = g(current) + edge weight

            // If the vertex is unvisited or a shorter path is found
            if (!visited[adjVertex] || newCost < costs[adjVertex])
            {
                trace[adjVertex] = current;
                costs[adjVertex] = newCost; // Update g(adjVertex)

                // f(n) = g(n) + h(n)
                int estimatedCost = newCost + adjVertex->estimate;
                minHeap.push({estimatedCost, adjVertex});
            }
        }
    }

    cout << "No path found" << endl;
    return vector<string>();
}

int main()
{
    // Create some vertices
    Vertex *v1 = new Vertex("A", 4);
    Vertex *v2 = new Vertex("B", 2);
    Vertex *v3 = new Vertex("C", 0); // Target vertex
    Vertex *v4 = new Vertex("D", 3);

    // Set up adjacency lists (edges)
    v1->neighbors = {{v2, 1}, {v4, 5}}; // A -> B (1), A -> D (5)
    v2->neighbors = {{v3, 2}, {v1, 1}}; // B -> C (2), B -> A (1)
    v3->neighbors = {};                 // Target vertex has no outgoing edges
    v4->neighbors = {{v3, 2}};          // D -> C (2)

    // Define the source and target
    Vertex *source = v1; // Start at A
    Vertex *target = v3; // Goal is C

    map<Vertex *, int> costs;
    cout << "Running A* Algorithm - " << endl;

    // Execute A* Search
    vector<string> resultPath = aStarSearch(source, target, costs);

    // Print the resulting path
    cout << "Path: ";
    for (const auto &node : resultPath)
    {
        cout << node;
        if (&node != &resultPath.back()) // Avoid printing "->" after the last vertex
            cout << " -> ";
    }
    cout << endl;

    return 0;
}
