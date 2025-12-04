#include <bits/stdc++.h>

using namespace std;


void DFS(int v, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);  
    for (int i = 0; i < graph[v].size(); i++) {
        if (graph[v][i] == 1 && !visited[i]) {
            DFS(i, graph, visited, component);
        }
    }
}

/*
1 1 1 0 0 0
1 1 1 0 0 0
1 1 1 0 0 0 
0 0 0 1 1 0
0 0 0 1 1 0
0 0 0 0 0 1
*/

void ComponentesConectadosMagia(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    int componentNumber = 1;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            vector<int> component;
            DFS(i, graph, visited, component);
            
            
            cout << "Componente conexo " << componentNumber << ": ";
            for (int node : component) {
                cout << (char)(node + 'A') << " ";  
            }
            cout << endl;
            componentNumber++;
        }
    }
}

int main() {
    int n;

    cout << "Ingrese el número de nodos: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));

    cout << "Ingrese la matriz de adyacencia con los cuadrantes ya acomodados en la diagonal principal :\n";
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    ComponentesConectadosMagia(graph);

    return 0;
}
