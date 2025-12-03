#include <iostream>
#include <vector>
#include <list>

using namespace std;

void dijkstra(int nunodes, const vector<list<pair<int, int>>>& graph, int origin, vector<int>& pondtch, vector<int>& prevnode) {
    pondtch[origin] = 0;

    for (int i = 0; i < nunodes; i++) {
        if (i != origin) {
            pondtch[i] = -1;
            prevnode[i] = -1;
        }
    }

    for (int i = 0; i < nunodes - 1; i++) {
        for (int u = 0; u < nunodes; u++) {
            for (auto& adya : graph[u]) {
                int v = adya.first;
                int w = adya.second;
                if (pondtch[u] != -1 && (pondtch[u] + w < pondtch[v] || pondtch[v] == -1)) {
                    pondtch[v] = pondtch[u] + w;
                    prevnode[v] = u;
                }
            }
        }
    }
}

void pathfinder(int nunodes, const vector<int>& prevnode, const vector<int>& pondtch) {
    cout << "Camino más largo para maximizar ganancias: \n";
    for (int i = 0; i < nunodes; i++) {
        if (pondtch[i] == -1) {
            cout << "Nodo " << i << ": No es alcanzable en exte momento\n";
        } else {
            cout << "Nodo " << i << ": " << pondtch[i] << " (Camino: ";

            vector<int> path;
            for (int j = i; j != -1; j = prevnode[j]) {
                path.push_back(j);
            }

            for (int j = path.size() - 1; j >= 0; j--) {
                cout << path[j];
                if (j > 0) cout << " -> ";
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
    for (int i = 0; i < nunodes; i++) {
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

    vector<int> pondtch(nunodes, -1);  
    vector<int> prevnode(nunodes, -1);  

    dijkstra(nunodes, graph, origin, pondtch, prevnode);
    pathfinder(nunodes, prevnode, pondtch);

    return 0;
}
