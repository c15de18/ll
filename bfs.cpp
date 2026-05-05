#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void parallelBFS(int start) {
        vector<bool> visited(V, false);
        vector<int> currentLevel, nextLevel;

        visited[start] = true;
        currentLevel.push_back(start);

        cout << "\nParallel BFS Traversal: ";

        while (!currentLevel.empty()) {

            #pragma omp parallel for
            for (int i = 0; i < currentLevel.size(); i++) {
                int node = currentLevel[i];

                #pragma omp critical
                cout << node << " ";

                for (int neighbor : adj[node]) {

                    if (!visited[neighbor]) {
                        #pragma omp critical
                        {
                            if (!visited[neighbor]) {
                                visited[neighbor] = true;
                                nextLevel.push_back(neighbor);
                            }
                        }
                    }
                }
            }

            currentLevel = nextLevel;
            nextLevel.clear();
        }

        cout << endl;
    }
};

int main() {
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start;
    cout << "Enter starting vertex: ";
    cin >> start;

    g.parallelBFS(start);

    return 0;
}