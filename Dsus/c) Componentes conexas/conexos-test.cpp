//Código de ejemplo para encontrar componentes conexas en un grafo representado por una matriz de adyacencia.
#include <iostream>
#include <vector>
using namespace std;

//Función para realizar DFS (Mismo que el código de DFS en dfsbfstest.cpp)
void DFS(int v, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& component) {
    visited[v] = true; 
    component.push_back(v); 
    for (int i = 0; i < graph[v].size(); i++) {
        if (graph[v][i] == 1 && !visited[i]) {
            DFS(i, graph, visited, component);
        }
    }
}

//Función para encontrar y mostrar todos los componentes conexas en el grafo
void findConnectedComponents(vector<vector<int>>& graph) { 
    int n = graph.size(); // Número de nodos
    vector<bool> visited(n, false); // Vector para rastrear nodos visitados
    int componentNumber = 1; // Contador de componentes conexas

    for (int i = 0; i < n; i++) { // Recorre todos los nodos
        if (!visited[i]) { // Si el nodo no ha sido visitado, es el inicio de un nuevo componente
            vector<int> component; // Vector para almacenar el componente actual
            DFS(i, graph, visited, component); // Realiza DFS desde el nodo i
            
            cout << "Componente conexo " << componentNumber << ": "; // Muestra el componente encontrado
            for (int node : component) { // Imprime los nodos del componente
                cout << (char)(node + 'A') << " "; 
            }
            cout << endl;
            componentNumber++; // Incrementa el contador de componentes
        }
    }
}

int main() {
    int n;

    cout << "Ingrese el número de nodos: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n)); // Matriz de adyacencia

    cout << "Ingrese la matriz de adyacencia (1 para conexión, 0 para no conexión):\n";

    for (int i = 0; i < n; i++) { // Rellena la matriz de adyacencia
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    findConnectedComponents(graph); // Encuentra y muestra los componentes conexas

    return 0;
}
