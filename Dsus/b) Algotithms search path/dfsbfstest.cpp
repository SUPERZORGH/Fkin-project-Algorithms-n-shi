//Código de ejemplo para realizar DFS y BFS en un grafo representado por una matriz de adyacencia.
#include <iostream>
#include <vector>
using namespace std;

//Función para realizar DFS
void DFS(int v, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& component) {
    visited[v] = true; // Marca el nodo como visitado
    component.push_back(v); // Agrega el nodo al componente actual
    cout << v << " "; // Imprimir el nodo directamente cuando se agrega
    for (int i = 0; i < graph[v].size(); i++) { // Recorre todos los nodos adyacentes
        if (graph[v][i] == 1 && !visited[i]) { // Si hay una conexión y no ha sido visitado
            DFS(i, graph, visited, component); // Llama recursivamente a DFS
        }
    }
}

//Función para realizar BFS
void BFS(int v, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& component) {
    vector<int> queue; // Cola para manejar los nodos a visitar
    queue.push_back(v); // Agrega el nodo inicial a la cola
    visited[v] = true; // Marca el nodo como visitado
    while (!queue.empty()) { // Mientras haya nodos en la cola
        int current = queue.front(); // Toma el primer nodo de la cola
        queue.erase(queue.begin()); // Elimina el nodo de la cola
        component.push_back(current); // Agrega el nodo al componente actual
        cout << current << " "; // Imprimir el nodo directamente cuando lo procesas
        for (int i = 0; i < graph[current].size(); i++) { // Recorre todos los nodos adyacentes
            if (graph[current][i] == 1 && !visited[i]) { // Si hay una conexión y no ha sido visitado
                visited[i] = true; // Marca el nodo como visitado
                queue.push_back(i); // Agrega el nodo a la cola
            }
        }
    }
}

int main () {
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

    vector<bool> visited(n, false); // Vector para rastrear nodos visitados
    vector<int> component; // Vector para almacenar el componente actual
    
    cout << "Recorrido DFS: ";
    DFS(0, graph, visited, component); // Inicia DFS desde el nodo 0
    cout << endl;
    
    fill(visited.begin(), visited.end(), false); // Reinicia el vector de visitados para BFS
    
    cout << "Recorrido BFS: ";
    BFS(0, graph, visited, component); // Inicia BFS desde el nodo 0
    cout << endl;
    return 0;
}
