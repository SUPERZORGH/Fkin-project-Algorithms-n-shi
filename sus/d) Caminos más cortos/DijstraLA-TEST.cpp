#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

void hamburguesa(int nunodos, const vector<list<pair<int, int>>>& grafo, int origen, vector<int>& pesosmx, vector<int>& nodoantes) {
    pesosmx[origen] = 0;

    //ponemos -1 para que todo esté sin conección
    for (int i = 0; i < nunodos; i++) {
        if (i != origen) {
            pesosmx[i] = -1;
            nodoantes[i] = -1;
        }
    }

    for (int i = 0; i < nunodos - 1; i++) {
        for (int u = 0; u < nunodos; u++) {
            for (auto& vecino : grafo[u]) {
                int v = vecino.first;
                int peso = vecino.second;
                if (pesosmx[u] != -1 && (pesosmx[u] + peso < pesosmx[v] || pesosmx[v] == -1)) {
                    pesosmx[v] = pesosmx[u] + peso;
                    nodoantes[v] = u;
                }
            }
        }
    }
}

void papasconqueso(int nunodos, const vector<int>& nodoantes, const vector<int>& pesosmx) {
    cout << "Camino menos pesado desde el nodo que elegimos: \n";
    for (int i = 0; i < nunodos; i++) {
        if (pesosmx[i] == -1) {
            cout << "Nodo " << i << ": No podemos llegar\n";
        } else {
            cout << "Nodo " << i << ": " << pesosmx[i] << " (Camino: ";

            vector<int> camino;
            for (int j = i; j != -1; j = nodoantes[j]) {
                camino.push_back(j);
            }

            for (int j = camino.size() - 1; j >= 0; j--) {
                cout << camino[j];
                if (j > 0) cout << " -> ";
            }
            cout << ")\n";
        }
    }
}

int main() {
    int nunodos;
    cout << "Ingresa el número de nodos: ";
    cin >> nunodos;

    vector<list<pair<int, int>>> grafo(nunodos); // Lista de adyacencia

    cout << "Ingresa las conexiones y pesos de los nodos (ingresa el nodo de destino y el peso):\n";
    for (int i = 0; i < nunodos; i++) {
        int numConexiones;
        cout << "Nodo " << i << " tiene cuántas conexiones? ";
        cin >> numConexiones;
        cout << "Ingresa las conexiones (nodo destino y peso) del nodo " << i << ":\n";
        for (int j = 0; j < numConexiones; j++) {
            int destino, peso;
            cin >> destino >> peso;
            grafo[i].push_back({destino, peso});
        }
    }

    int origen;
    cout << "Ingresa el nodo de origen: ";
    cin >> origen;

    vector<int> pesosmx(nunodos, -1);  
    vector<int> nodoantes(nunodos, -1);  

    hamburguesa(nunodos, grafo, origen, pesosmx, nodoantes);
    papasconqueso(nunodos, nodoantes, pesosmx);

    return 0;
}
