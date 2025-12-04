#include <iostream>
#include <vector>
using namespace std;



void printMatrix(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
int main() {
    int n;

    cout << "Ingrese el número de nodos: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));

    cout << "Ingrese la matriz de adyacencia (1 para conexión, 0 para no conexión):\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    cout << "Matriz de adyacencia ingresada:\n";
    printMatrix(graph);

    return 0;
}
