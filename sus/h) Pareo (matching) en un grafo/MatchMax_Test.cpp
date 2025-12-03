#include <bits/stdc++.h>
using namespace std;

/* ============================================================
   1. MATCHING MAXIMAL EN GRAFO GENERAL
   (Greedy algorithm for maximal matching)
   ============================================================ */

void matchingMaximal_General() {
    int n, m;
    cout << "\n--- MATCHING MAXIMAL (GRAFO GENERAL) ---\n";
    cout << "Numero de nodos y aristas: ";
    cin >> n >> m;

    vector<pair<int,int>> edges(m);
    cout << "Aristas (u v):\n";
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    vector<bool> used(n + 1, false);
    vector<pair<int,int>> matching;

    // Greedy: si ambos nodos están libres, se agrega la arista
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        if (!used[u] && !used[v]) {
            matching.push_back(e);
            used[u] = used[v] = true;
        }
    }

    cout << "\nMatching maximal encontrado (tam = " 
         << matching.size() << "):\n";
    for (auto &p : matching) {
        cout << p.first << " - " << p.second << "\n";
    }
}

/* ============================================================
   2. MATCHING MÁXIMO EN GRAFO BIPARTITO
   Algoritmo de Kuhn (DFS para caminos aumentantes)
   ============================================================ */

vector<vector<int>> adj;
vector<int> matchL, matchR;
vector<bool> vis;

bool dfs_kuhn(int u) {
    for (int v : adj[u]) {
        if (vis[v]) continue;
        vis[v] = true;

        if (matchR[v] == 0 || dfs_kuhn(matchR[v])) {
            matchR[v] = u;
            matchL[u] = v;
            return true;
        }
    }
    return false;
}

void matchingMaximo_Bipartito() {
    int nL, nR, m;
    cout << "\n--- MATCHING MAXIMO (BIPARTITO, ALGORITMO DE KUHN) ---\n";
    cout << "Numero de nodos en la izquierda (nL) y derecha (nR): ";
    cin >> nL >> nR;

    cout << "Numero de aristas: ";
    cin >> m;

    adj.assign(nL + 1, {});
    cout << "Aristas (u v): u en [1.." << nL << "], v en [1.." << nR << "]\n";
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    matchL.assign(nL + 1, 0);
    matchR.assign(nR + 1, 0);

    int matchingSize = 0;
    for (int u = 1; u <= nL; ++u) {
        vis.assign(nR + 1, false);
        if (dfs_kuhn(u)) matchingSize++;
    }

    cout << "\nMatching MAXIMO encontrado (tam = " << matchingSize << "):\n";
    for (int u = 1; u <= nL; ++u) {
        if (matchL[u] != 0)
            cout << u << " <--> " << matchL[u] << "\n";
    }
}

/* ============================================================
   MENÚ PRINCIPAL
   ============================================================ */

int main() {
    while (true) {
        cout << "\n======================================\n";
        cout << "          ALGORITMOS DE MATCHING     \n";
        cout << "======================================\n";
        cout << "1) Matching maximal (grafo general)\n";
        cout << "2) Matching maximo (bipartito, Kuhn)\n";
        cout << "3) Salir\n";
        cout << "Opcion: ";

        int op;
        cin >> op;

        if (op == 1) matchingMaximal_General();
        else if (op == 2) matchingMaximo_Bipartito();
        else if (op == 3) break;
        else cout << "Opcion invalida.\n";
    }
    return 0;
}
