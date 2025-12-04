#include <iostream>
#include <vector>
using namespace std;

void DFS(int v, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& component) {
    visited[v] = true;
    component.push_back(v); 
    for (int i = 0; i < graph[v].size(); i++) {
        if (graph[v][i] == 1 && !visited[i]) {
            int node = component.back();
            cout << (char)(node + 'A') << " "; 
            DFS(i, graph, visited, component);
            cout << (char)(node + 'A') << " "; 
        }
    }
    int node = component.back();
    cout << (char)(node + 'A') << " "; 
}
void BFS (int v, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& component) {
    vector<int> queue;
    queue.push_back(v);
    visited[v] = true;
    while (!queue.empty()) {
        int node = component.back(); 
        int current = queue.front();
        queue.erase(queue.begin());
        component.push_back(current);
        for (int i = 0; i < graph[current].size(); i++) { 
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                queue.push_back(i);
            }
        }
    }
}
int main () {
    int n;

    cout << "Ingrese el número de nodos: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));

    cout << "Ingrese la matriz de adyacencia (1 para conexión, 0 para no conexión):\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }
    vector<bool> visited(n, false);
    vector<int> component;
    cout << "Recorrido DFS: ";
    DFS(0, graph, visited, component);
    cout << endl;
    cout << "Recorrido BFS: ";
    BFS(0, graph, visited, component);
    cout << endl;
    return 0;
}