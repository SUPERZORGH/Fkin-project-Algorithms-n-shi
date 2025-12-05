#include <bits/stdc++.h>
using namespace std;

// Implementación del Algoritmo de Blossom (Edmonds' Blossom Algorithm)
struct Blossom {
    int n;                              // numero de vertices
    vector<vector<int>> g;              // lista de adyacencia
    vector<int> match;                  // match[v] = vertice emparejado con v, o -1 si libre
    vector<int> parent;                 // padre en el arbol de busqueda
    vector<int> base;                   // base[v] = raiz de la "flor" a la que pertenece v
    vector<bool> used;                  // usado en BFS
    vector<bool> blossom;               // marca vertices dentro de una flor
    queue<int> q;                       // cola para BFS

    Blossom(int n) : n(n) {
        g.assign(n, {});
        match.assign(n, -1);
        parent.assign(n, -1);
        base.resize(n);
        used.assign(n, false);
        blossom.assign(n, false);
    }

    void addEdge(int u, int v) {
        if (u == v) return;             // ignorar bucles
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // Lowest Common Ancestor (LCA) en el arbol de busqueda
    int lca(int a, int b) {
        vector<bool> usedPath(n, false);

        while (true) {
            a = base[a];
            usedPath[a] = true;
            if (match[a] == -1) break;
            a = parent[match[a]];
        }

        while (true) {
            b = base[b];
            if (usedPath[b]) return b;
            if (match[b] == -1) break;
            b = parent[match[b]];
        }
        return -1; // en teoria no deberia llegar aqui
    }

    // Marca la ruta que forma parte de la flor (blossom)
    void markPath(int v, int b, int child) {
        while (base[v] != b) {
            blossom[base[v]] = true;
            blossom[base[match[v]]] = true;
            parent[v] = child;
            child = match[v];
            v = parent[match[v]];
        }
    }

    // Busca un camino aumentante desde la raiz 'root'
    bool findPath(int root) {
        used.assign(n, false);
        parent.assign(n, -1);
        for (int i = 0; i < n; ++i) {
            base[i] = i;
        }

        while (!q.empty()) q.pop();
        q.push(root);
        used[root] = true;

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int u : g[v]) {
                if (base[v] == base[u] || match[v] == u) continue; // ignorar ciclos triviales

                // Detectamos una flor (ciclo impar)
                if ((u == root) || (match[u] != -1 && parent[match[u]] != -1)) {
                    int curBase = lca(v, u);
                    blossom.assign(n, false);
                    markPath(v, curBase, u);
                    markPath(u, curBase, v);

                    for (int i = 0; i < n; ++i) {
                        if (blossom[base[i]]) {
                            base[i] = curBase;
                            if (!used[i]) {
                                used[i] = true;
                                q.push(i);
                            }
                        }
                    }
                }
                // Extender el arbol de busqueda
                else if (parent[u] == -1) {
                    parent[u] = v;
                    if (match[u] == -1) {
                        // Encontramos camino aumentante: aumentamos el matching
                        int cur = u;
                        while (cur != -1) {
                            int prev = parent[cur];
                            int next = (prev == -1 ? -1 : match[prev]);
                            match[cur] = prev;
                            if (prev != -1) match[prev] = cur;
                            cur = next;
                        }
                        return true;
                    } else {
                        int w = match[u];
                        if (!used[w]) {
                            used[w] = true;
                            q.push(w);
                        }
                    }
                }
            }
        }
        return false;
    }

    // Calcula matching maximo
    int solve() {
        int matchingSize = 0;
        // match ya empieza en -1 (todos libres)
        for (int i = 0; i < n; ++i) {
            if (match[i] == -1) {
                if (findPath(i)) {
                    matchingSize++;
                }
            }
        }
        return matchingSize;
    }

    void printResults() {
        int maxMatching = solve();
        cout << "Tamano del matching maximo: " << maxMatching << "\n";
        cout << "Emparejamientos (u - v):\n";

        // Imprime solo cada arista una vez (i < match[i])
        for (int i = 0; i < n; ++i) {
            if (match[i] != -1 && i < match[i]) {
                // Convertimos a 1-based para la salida
                cout << (i + 1) << " - " << (match[i] + 1) << "\n";
            }
        }

        // Verificar si el matching es PERFECTO:
        // En un matching perfecto, todos los vertices estan emparejados,
        // es decir, 2 * |M| = n
        if (2 * maxMatching == n) {
            cout << "El matching ES PERFECTO (todos los nodos estan emparejados).\n";
        } else {
            cout << "El matching NO es perfecto.\n";
        }

        // Nota: al ser maximo, este matching tambien es MAXIMAL
        // (no se puede agregar ninguna arista sin romper el matching).
    }
};

int main() {
    int n, m;
    cout << "Numero de nodos y aristas: ";
    cin >> n >> m;

    Blossom solver(n);

    cout << "Ingresa las aristas (u v) con nodos indexados a 0 [0.." << n-1 << "]:\n";
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        // Convertir a 0-based internamente
        
        solver.addEdge(u, v);
    }

    solver.printResults();

    return 0;
}
