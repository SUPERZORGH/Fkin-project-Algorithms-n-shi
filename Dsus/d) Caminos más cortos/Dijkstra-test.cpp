//Código de ejemplo para el algoritmo de Dijkstra para encontrar caminos más cortos en un grafo ponderado dirigido.
#include <iostream>
#include <vector>
#include <list>

using namespace std;

//Función para ejecutar el algoritmo de Dijkstra
void dijkstra(int nunodes, const vector<list<pair<int, int>>>& graph, int origin, vector<int>& pondtch, vector<int>& prevnode) {
    pondtch[origin] = 0; // La distancia al nodo de origen es 0

    for (int i = 0; i < nunodes; i++) { // Inicializa las distancias y nodos previos
        if (i != origin) {
            pondtch[i] = -1;
            prevnode[i] = -1;
        }
    }

    for (int i = 0; i < nunodes - 1; i++) { 
        for (int u = 0; u < nunodes; u++) { // Recorre todos los nodos
            for (auto& adya : graph[u]) { // Recorre todos los nodos adyacentes
                int v = adya.first; // Nodo adyacente
                int w = adya.second; // Peso de la arista
                if (pondtch[u] != -1 && (pondtch[u] + w < pondtch[v] || pondtch[v] == -1)) { // Actualiza la distancia si es menor
                    pondtch[v] = pondtch[u] + w;
                    prevnode[v] = u;
                }
            }
        }
    }
}

//Función para reconstruir y mostrar el camino más corto desde el nodo de origen a todos los demás nodos
void pathfinder(int nunodes, const vector<int>& prevnode, const vector<int>& pondtch) {
    cout << "Camino más corto: \n"; 
    for (int i = 0; i < nunodes; i++) { // Recorre todos los nodos
        if (pondtch[i] == -1) { // Si el nodo no es alcanzable
            cout << "Nodo " << i << ": No es alcanzable en exte momento\n";
        } else { // Muestra la distancia y el camino
            cout << "Nodo " << i << ": " << pondtch[i] << " (Camino: "; 

            vector<int> path; // Vector para almacenar el camino
            for (int j = i; j != -1; j = prevnode[j]) { // Reconstruye el camino
                path.push_back(j); // Agrega el nodo al camino
            }

            for (int j = path.size() - 1; j >= 0; j--) { // Imprime el camino en orden correcto
                cout << path[j]; 
                if (j > 0) cout << " -> "; // Separador entre nodos
            }
            cout << ")\n";
        }
    }
}

int main() {
    int nunodes;
    cout << "Ingresa el número de nodos: ";
    cin >> nunodes;

    vector<list<pair<int, int>>> graph(nunodes); // Lista de adyacencia

    cout << "Ingresa las conexiones y pesos de los nodos (ingresa el nodo de destino y el peso):\n";
    for (int i = 0; i < nunodes; i++) { // Rellena la lista de adyacencia
        int numCon;
        cout << "Nodo " << i << " tiene cuántas conexiones? ";
        cin >> numCon;
        cout << "Ingresa las conexiones (nodo destino y peso) del nodo " << i << ":\n";
        for (int j = 0; j < numCon; j++) {
            int dest, pond;
            cin >> dest >> pond;
            graph[i].push_back({dest, pond});
        }
    }

    int origin;
    cout << "Ingresa el nodo de origen: ";
    cin >> origin;

    vector<int> pondtch(nunodes, -1); // Vector para almacenar las distancias más cortas
    vector<int> prevnode(nunodes, -1); // Vector para almacenar los nodos previos en el camino más corto

    dijkstra(nunodes, graph, origin, pondtch, prevnode); // Ejecuta el algoritmo de Dijkstra
    pathfinder(nunodes, prevnode, pondtch); // Muestra los caminos más cortos

    return 0;
}
