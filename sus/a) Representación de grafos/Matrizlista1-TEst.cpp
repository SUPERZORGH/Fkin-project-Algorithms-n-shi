#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

static bool VERBOSE = true; // ver todos los pasos detalladamente


void imprimirMatriz(const vector<string>& lab, const vector<vector<int>>& M, const string& titulo="") {
    int n = (int)lab.size();
    if (!titulo.empty()) cout << titulo << "\n";
    cout << "   ";
    for (int j = 0; j < n; ++j) cout << setw(2) << lab[j] << ' ';
    cout << "\n";
    for (int i = 0; i < n; ++i) {
        cout << setw(2) << lab[i] << ' ';
        for (int j = 0; j < n; ++j) cout << setw(2) << M[i][j] << ' ';
        cout << "\n";
    }
    cout << "\n";
}

int contarUnosFila(const vector<int>& row) {
    int s = 0; for (int v : row) s += v; return s;
}

// daigonal y copia de los 1s en cada nivel de la matriz
vector<vector<int>> clausuraTransitivaConTraza(vector<vector<int>> R, const vector<string>& labels) {
    int n = (int)R.size();

    cout << "Paso 2) Colocar diagonal principal en 1\n";
    for (int i = 0; i < n; ++i) R[i][i] = 1;
    imprimirMatriz(labels, R, "Matriz tras diagonal=1:"); 

    cout << "Paso 3) Construir matriz de caminos (clausura transitiva)\n";
    for (int k = 0; k < n; ++k) {
        cout << "  3." << (k+1) << ") Usando nodo intermedio " << labels[k] << "\n";
        if (VERBOSE) imprimirMatriz(labels, R, "  Estado antes de propagar con " + labels[k] + ":");
        for (int i = 0; i < n; ++i) {
            if (R[i][k] == 1) {
                vector<int> antes = R[i];
                for (int j = 0; j < n; ++j) {
                    R[i][j] = R[i][j] || R[k][j];
                }
                if (VERBOSE && R[i] != antes) {
                    cout << "    - Fila " << labels[i]
                         << " se actualiza OR copiando 1's de " << labels[k] << "\n";
                    imprimirMatriz(labels, R, "    Matriz parcial:");
                }
            }
        }
        cout << "  Fin subpaso con intermedio " << labels[k] << ".\n\n";
    }
    cout << "Fin Paso 3) Matriz de caminos lista.\n\n";
    return R;
}

// acomodar nodos según su número de 1s (mayor a menor)
pair<vector<int>, vector<vector<int>>> reordenarPorUnos(const vector<vector<int>>& R) {
    int n = (int)R.size();
    vector<pair<int,int>> score_idx;
    score_idx.reserve(n);
    for (int i = 0; i < n; ++i) score_idx.push_back({contarUnosFila(R[i]), i});
    // estable, desc por # de 1's
    stable_sort(score_idx.begin(), score_idx.end(),
                [](auto& a, auto& b){ return a.first > b.first; });
    vector<int> orden(n);
    for (int k = 0; k < n; ++k) orden[k] = score_idx[k].second;

    vector<vector<int>> R2(n, vector<int>(n,0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            R2[i][j] = R[orden[i]][orden[j]];
    return {orden, R2};
}

// Nodos que forman un bloque en la diagonal principal
vector<vector<int>> bloquesSCC(const vector<vector<int>>& R2) {
    int n = (int)R2.size();
    vector<vector<int>> bloques;
    int i = 0;
    while (i < n) {
        int j = i;
        while (j + 1 < n) {
            bool ok = true;
            for (int k = i; k <= j; ++k) {
                if (!(R2[k][j+1] && R2[j+1][k])) { ok = false; break; }
            }
            if (!ok) break;
            ++j;
        }
        vector<int> bloque;
        for (int k = i; k <= j; ++k) bloque.push_back(k);
        bloques.push_back(bloque);
        i = j + 1;
    }
    return bloques;
}

int main() {
    int n;
    cout << "Ingrese el numero de nodos: ";
    cin >> n;

    vector<string> labels(n);
    cout << "Ingrese las etiquetas de los nodos (ej: A B C ...):\n";
    for (int i = 0; i < n; ++i) cin >> labels[i];

    cout << "Ingrese la matriz de adyacencia (" << n << "x" << n << " con 0/1):\n";
    vector<vector<int>> A(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];


    cout << "\nPaso 1) Matriz de adyacencia (original)\n";
    imprimirMatriz(labels, A);


    auto R = clausuraTransitivaConTraza(A, labels); // diagonal y relleno de 1s


    cout << "Paso 4) Conteo de 1's por fila\n";
    for (int i = 0; i < n; ++i) {
        cout << "  " << labels[i] << ": " << contarUnosFila(R[i]) << " unos\n";
    }


    auto [orden, R2] = reordenarPorUnos(R);
    vector<string> labels2(n);
    for (int i = 0; i < n; ++i) labels2[i] = labels[orden[i]];

    cout << "\nPaso 5) Orden aplicado (mismo para filas y columnas): ";
    for (auto idx : orden) cout << labels[idx] << " ";
    cout << "\n";
    imprimirMatriz(labels2, R2, "Matriz reordenada:");


    cout << "Paso 6) Componentes fuertemente conexos (bloques diagonales de 1's con alcanzabilidad mutua)\n";
    auto bloques = bloquesSCC(R2);
    for (size_t b = 0; b < bloques.size(); ++b) {
        cout << "  V" << (b+1) << " = {";
        for (size_t t = 0; t < bloques[b].size(); ++t) {
            if (t) cout << ",";
            cout << labels2[bloques[b][t]];
        }
        cout << "}\n";
    }

    return 0;
}
