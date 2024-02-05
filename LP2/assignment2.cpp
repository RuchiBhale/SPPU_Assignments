#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

unordered_map<char, vector<pair<char, int>>> Graph_nodes;

vector<char> aStarAlgo(char start_node, char stop_node) {
    unordered_set<char> open_set{start_node};
    unordered_set<char> closed_set;
    unordered_map<char, int> g;      // store distance from starting node
    unordered_map<char, char> parents; // parents contain an adjacency map of all nodes

    // distance of starting node from itself is zero
    g[start_node] = 0;

    // start_node is the root node, i.e., it has no parent nodes
    parents[start_node] = start_node;

    while (!open_set.empty()) {
        char n = '\0';

        // node with the lowest f() is found
        for (char v : open_set) {
            // if the first node or a node with a lower f() is found
            if (n == '\0' || g[v] + heuristic(v) < g[n] + heuristic(n)) {
                n = v;
            }
        }

        if (n == stop_node || Graph_nodes[n].empty()) {
            // Goal reached or no neighbors for the current node
            break;
        } else {
            for (const auto& neighbor : get_neighbors(n)) {
                char m = neighbor.first;
                int weight = neighbor.second;

                // if we are encountering a new node
                if (open_set.find(m) == open_set.end() && closed_set.find(m) == closed_set.end()) {
                    open_set.insert(m);
                    parents[m] = n;
                    g[m] = g[n] + weight;
                } else {
                    // if the new path is shorter than the previous one
                    if (g[m] > g[n] + weight) {
                        g[m] = g[n] + weight;
                        parents[m] = n;

                        // if m is in the closed set, remove and add to open
                        if (closed_set.find(m) != closed_set.end()) {
                            closed_set.erase(m);
                            open_set.insert(m);
                        }
                    }
                }
            }
        }

        if (n == '\0') {
            cout << "Path does not exist!" << endl;
            return {};
        }

        // if the current node is the stop_node, backtrack to find the path
        if (n == stop_node) {
            vector<char> path;
            while (parents[n] != n) {
                path.push_back(n);
                n = parents[n];
            }
            path.push_back(start_node);
            reverse(path.begin(), path.end());
            cout << "Path found: ";
            for (char node : path) {
                cout << node << " ";
            }
            cout << endl;
            return path;
        }

        // remove n from the open_set and add it to the closed_set
        open_set.erase(n);
        closed_set.insert(n);
    }

    cout << "Path does not exist!" << endl;
    return {};
}

vector<pair<char, int>> get_neighbors(char v) {
    if (Graph_nodes.find(v) != Graph_nodes.end()) {
        return Graph_nodes[v];
    } else {
        return {};
    }
}

int heuristic(char n) {
    unordered_map<char, int> H_dist{
        {'A', 11},
        {'B', 6},
        {'C', 99},
        {'D', 1},
        {'E', 7},
        {'G', 0},
    };

    return H_dist[n];
}

int main() {
    Graph_nodes = {
        {'A', {{'B', 2}, {'E', 3}}},
        {'B', {{'A', 2}, {'C', 1}, {'G', 9}}},
        {'C', {{'B', 1}}},
        {'D', {{'E', 6}, {'G', 1}}},
        {'E', {{'A', 3}, {'D', 6}}},
        {'G', {{'B', 9}, {'D', 1}}},
    };

    aStarAlgo('A', 'G');

    return 0;
}
