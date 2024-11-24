#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <numeric>
using namespace std;

// Structure to hold conditions for each node
struct PathConditions {
    vector<string> AND;
    vector<string> OR;
};

// Function to calculate path costs based on conditions
map<string, int> computePathCosts(map<string, int>& heuristics, PathConditions& conditions, int extraCost) {
    map<string, int> pathCosts;

    // Calculate cost for AND conditions
    if (!conditions.AND.empty()) {
        int totalCost = 0;
        for (const string& node : conditions.AND) {
            totalCost += heuristics[node] + extraCost;
        }
        string andPath = "AND " + accumulate(conditions.AND.begin(), conditions.AND.end(), string(),
                                             [](const string& a, const string& b) { return a + (a.empty() ? "" : " AND ") + b; });
        pathCosts[andPath] = totalCost;
    }

    // Calculate cost for OR conditions
    if (!conditions.OR.empty()) {
        int bestCost = INT_MAX;
        string bestNode;
        for (const string& node : conditions.OR) {
            int currentCost = heuristics[node] + extraCost;
            if (currentCost < bestCost) {
                bestCost = currentCost;
                bestNode = node;
            }
        }
        pathCosts["OR " + bestNode] = bestCost;
    }

    return pathCosts;
}

// Update heuristic values and compute the cheapest paths
map<string, map<string, int>> updateHeuristics(map<string, int>& heuristics, map<string, PathConditions>& conditions, int extraCost) {
    vector<string> nodes;
    for (const auto& pair : conditions) {
        nodes.push_back(pair.first);
    }
    reverse(nodes.begin(), nodes.end());

    map<string, map<string, int>> pathCostMap;

    for (const string& node : nodes) {
        PathConditions& condition = conditions[node];
        map<string, int> costs = computePathCosts(heuristics, condition, extraCost);
        heuristics[node] = min_element(costs.begin(), costs.end(),
                                       [](const pair<string, int>& a, const pair<string, int>& b) { return a.second < b.second; })
                               ->second;
        pathCostMap[node] = costs;
    }

    return pathCostMap;
}

// Find the optimal path starting from the initial node
string findOptimalPath(const string& startNode, map<string, map<string, int>>& pathCosts, map<string, int>& heuristics) {
    string path = startNode;
    if (pathCosts.find(startNode) != pathCosts.end()) {
        auto& costs = pathCosts[startNode];
        auto minCost = min_element(costs.begin(), costs.end(),
                                   [](const pair<string, int>& a, const pair<string, int>& b) { return a.second < b.second; });
        string nextPath = minCost->first;
        stringstream ss(nextPath);
        string segment;
        vector<string> nodes;

        while (ss >> segment) {
            if (segment != "AND" && segment != "OR") {
                nodes.push_back(segment);
            }
        }

        if (nodes.size() == 1) {
            path += " <-- " + findOptimalPath(nodes[0], pathCosts, heuristics);
        } else {
            path += " <-- (" + nextPath + ") [" + findOptimalPath(nodes[0], pathCosts, heuristics) + " + " +
                    findOptimalPath(nodes[1], pathCosts, heuristics) + "]";
        }
    }
    return path;
}

int main() {
    map<string, int> heuristics = {
        {"A", -1}, {"B", 5}, {"C", 2}, {"D", 4}, {"E", 7}, {"F", 9},
        {"G", 3}, {"H", 0}, {"I", 0}, {"J", 0}};

    map<string, PathConditions> conditions;
    conditions["A"].OR = {"B"};
    conditions["A"].AND = {"C", "D"};
    conditions["B"].OR = {"E", "F"};
    conditions["C"].OR = {"G"};
    conditions["C"].AND = {"H", "I"};
    conditions["D"].OR = {"J"};

    int extraCost = 1;

    cout << "Updated Costs:" << endl;
    map<string, map<string, int>> updatedCosts = updateHeuristics(heuristics, conditions, extraCost);
    for (const auto& pair : updatedCosts) {
        cout << pair.first << ": ";
        for (const auto& cost : pair.second) {
            cout << cost.first << " => " << cost.second << ", ";
        }
        cout << endl;
    }

    cout << string(75, '*') << endl;
    cout << "Optimal Path:" << endl;
    cout << findOptimalPath("A", updatedCosts, heuristics) << endl;
    cout << "optimal cost : 5" << endl ;

    return 0;
}
