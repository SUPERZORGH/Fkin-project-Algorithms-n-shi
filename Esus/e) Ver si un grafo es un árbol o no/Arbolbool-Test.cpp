#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

bool dfs(int nodo, const vector<vector<int>>& grafo, vector<bool>& visitado, int padre) {
    visitado[nodo] = true;
    
    for (int vecino : grafo[nodo]) {
        if (!visitado[vecino]) {
            if (!dfs(vecino, grafo, visitado, nodo)) {
                return false;
            }
        } else if (vecino != padre) {
            // Si encontramos un vecino ya visitado que no es el padre,
            // significa que hay un ciclo
            return false;
        }
    }
    return true;
}

bool esArbol(int nunodos, const vector<vector<int>>& grafo) {
    // Un árbol debe tener exactamente n-1 aristas
    int numAristas = 0;
    for (int i = 0; i < nunodos; i++) {
        numAristas += grafo[i].size();
    }
    numAristas /= 2; // Dado que el grafo es no dirigido, contamos las aristas dos veces
    
    if (numAristas != nunodos - 1) {
        return false;
    }
    
    // Verificamos si el grafo es conexo y no tiene ciclos usando DFS
    vector<bool> visitado(nunodos, false);
    if (!dfs(0, grafo, visitado, -1)) {
        return false;
    }
    
    // Verificamos si todos los nodos fueron visitados (grafo conexo)
    for (int i = 0; i < nunodos; i++) {
        if (!visitado[i]) {
            return false;
        }
    }
    
    return true;
}

int main() {
    int nunodos;
    cout << "Ingresa el número de nodos: ";
    cin >> nunodos;
    
    vector<vector<int>> grafo(nunodos);

    cout << "Ingresa las conexiones del grafo (nodo1 nodo2) (ingresa -1 -1 para terminar):\n";
    int nodo1, nodo2;
    while (true) {
        cin >> nodo1 >> nodo2;
        if (nodo1 == -1 && nodo2 == -1) {
            break;
        }
        grafo[nodo1].push_back(nodo2);
        grafo[nodo2].push_back(nodo1);  // Grafo no dirigido
    }

    if (esArbol(nunodos, grafo)) {
        cout << "El grafo es un árbol.\n";
    } else {
        cout << "El grafo no es un árbol.\n";
    }

    return 0;
}
