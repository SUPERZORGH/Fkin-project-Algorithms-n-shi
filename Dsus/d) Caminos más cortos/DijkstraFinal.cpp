#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <climits>

using namespace std;

struct Node {
    int id;
    int distance;
    bool operator>(const Node& other) const {
        return distance > other.distance;  // Para hacer un min-heap
    }
};

//Función para ejecutar el algoritmo de Dijkstra
void dijkstra(int nunodes, const vector<list<pair<int, int>>>& graph, int origin, vector<int>& pondtch, vector<int>& prevnode) {
    pondtch[origin] = 0;  // La distancia al nodo de origen es 0
    priority_queue<Node, vector<Node>, greater<Node>> pq;  // Cola de prioridad (min-heap)
    pq.push({origin, 0});  // Inserta el nodo de origen en la cola

    while (!pq.empty()) {
        Node current = pq.top();  // Obtiene el nodo con la distancia mínima
        pq.pop();

        // Recorre todos los nodos adyacentes
        for (const auto& adya : graph[current.id]) {
            int v = adya.first;   // Nodo adyacente
            int w = adya.second;  // Peso de la arista
            if (pondtch[current.id] + w < pondtch[v]) {  // Si encontramos una distancia menor
                pondtch[v] = pondtch[current.id] + w;
                prevnode[v] = current.id;
                pq.push({v, pondtch[v]});
            }
        }
    }
}

//Función para reconstruir y mostrar el camino más corto desde el nodo de origen a todos los demás nodos
void pathfinder(int nunodes, const vector<int>& prevnode, const vector<int>& pondtch) {
    cout << "Camino más corto: \n"; 
    for (int i = 0; i < nunodes; i++) { // Recorre todos los nodos
        if (pondtch[i] == INT_MAX) { // Si el nodo no es alcanzable
            cout << "Nodo " << i << ": No es alcanzable en este momento\n";
        } else { // Muestra la distancia y el camino
            cout << "Nodo " << i << ": " << pondtch[i] << " (Camino: "; 

            vector<int> path; // Vector para almacenar el camino
            for (int j = i; j != -1; j = prevnode[j]) { // Reconstruye el camino
                path.push_back(j); // Agrega el nodo al camino
            }

            // Imprime el camino en orden correcto
            for (int j = path.size() - 1; j >= 0; j--) { 
                cout << path[j]; 
                if (j > 0) cout << " -> "; // Separador entre nodos
            }
            cout << ")\n";
        }
    }
}

int main() {
    int nunodes, naristas;
    cout << "\nIngresa el número de nodos: ";
    cin >> nunodes;
    cout << "\nIngresa el número de aristas: ";
    cin >> naristas;

    vector<list<pair<int, int>>> graph(nunodes); // Lista de adyacencia

    cout << "\nIngresa las aristas (nodo origen, nodo destino y peso) para las " << naristas << " aristas:\n";
    for (int i = 0; i < naristas; i++) {
        int src, dest, weight;
        cout << "\nArista " << i + 1 << " (nodo origen, nodo destino, peso): ";
        cin >> src >> dest >> weight;
        graph[src].push_back({dest, weight});
    }

    int origin;
    cout << "\nIngresa el nodo de origen: ";
    cin >> origin;

    vector<int> pondtch(nunodes, INT_MAX); // Vector para almacenar las distancias más cortas
    vector<int> prevnode(nunodes, -1); // Vector para almacenar los nodos previos en el camino más corto

    dijkstra(nunodes, graph, origin, pondtch, prevnode); // Ejecuta el algoritmo de Dijkstra
    pathfinder(nunodes, prevnode, pondtch); // Muestra los caminos más cortos

    return 0;
}
