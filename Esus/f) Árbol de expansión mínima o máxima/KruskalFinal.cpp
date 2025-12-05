#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Arista {
    int u, v, peso;
    Arista(int u, int v, int peso) : u(u), v(v), peso(peso) {}
};

bool compararMin(Arista a, Arista b) {
    return a.peso < b.peso; // Ordenar de menor a mayor (para el árbol de expansión mínima)
}

bool compararMax(Arista a, Arista b) {
    return a.peso > b.peso; // Ordenar de mayor a menor (para el árbol de expansión máxima)
}

int find(int x, vector<int>& padre) {
    if (padre[x] != x)
        padre[x] = find(padre[x], padre); // compresión de caminos
    return padre[x];
}

void union_sets(int x, int y, vector<int>& padre, vector<int>& rango) {
    int raizX = find(x, padre);
    int raizY = find(y, padre);
    if (raizX != raizY) {
        if (rango[raizX] < rango[raizY]) {
            padre[raizX] = raizY;
        } else if (rango[raizX] > rango[raizY]) {
            padre[raizY] = raizX;
        } else {
            padre[raizY] = raizX;
            rango[raizX]++;
        }
    }
}

int kruskal(int V, vector<Arista>& aristas, bool esMaximo) {
    // Seleccionar la función de comparación en función de si es mínimo o máximo
    if (esMaximo) {
        sort(aristas.begin(), aristas.end(), compararMax); // Ordenar para máximo
    } else {
        sort(aristas.begin(), aristas.end(), compararMin); // Ordenar para mínimo
    }

    vector<int> padre(V);
    vector<int> rango(V, 0);
    
    for (int i = 0; i < V; i++) {
        padre[i] = i;
    }
    
    int costoTotal = 0;
    for (auto& arista : aristas) {
        int u = arista.u;
        int v = arista.v;
        int peso = arista.peso;
        
        if (find(u, padre) != find(v, padre)) {
            costoTotal += peso;
            union_sets(u, v, padre, rango);
        }
    }
    
    return costoTotal;
}

int main() {
    int V, E;
    
    // Solicitar al usuario el número de vértices y aristas
    cout << "Ingrese el número de vértices: ";
    cin >> V;
    cout << "Ingrese el número de aristas: ";
    cin >> E;
    
    vector<Arista> aristas;
    
    // Solicitar las aristas y sus pesos
    for (int i = 0; i < E; i++) {
        int u, v, peso;
        cout << "Ingrese los vértices (u, v) y el peso de la arista " << i+1 << ": ";
        cin >> u >> v >> peso;
        aristas.push_back(Arista(u, v, peso));
    }
    
    // Llamar al algoritmo de Kruskal y mostrar el costo total para el árbol de expansión mínima
    int costoMinimo = kruskal(V, aristas, false);
    cout << "El costo del árbol de expansión mínima es: " << costoMinimo << endl;

    // Llamar al algoritmo de Kruskal y mostrar el costo total para el árbol de expansión máxima
    int costoMaximo = kruskal(V, aristas, true);
    cout << "El costo del árbol de expansión máxima es: " << costoMaximo << endl;

    return 0;
}
