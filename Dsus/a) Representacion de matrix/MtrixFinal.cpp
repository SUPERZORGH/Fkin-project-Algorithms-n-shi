#include <iostream>
#include <vector>
#include <limits>
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

void printAdjList(const vector<vector<int>>& adjList) {
    int n = adjList.size();
    for (int i = 0; i < n; i++) {
        cout << "Nodo " << i << ": ";
        for (int j : adjList[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    int choice;

    cout << "¿Qué deseas crear?\n";
    cout << "1. Matriz de adyacencia\n";
    cout << "2. Lista de adyacencia\n";
    cout << "Elige una opción (1 o 2): ";
    cin >> choice;

    // Validar que la opción ingresada sea válida
    if (choice != 1 && choice != 2) {
        cout << "Opción no válida\n";
        return 1;
    }

    cout << "Ingrese el número de nodos: ";
    cin >> n;

    // Validar que n sea positivo
    if (n <= 0) {
        cout << "El número de nodos debe ser positivo.\n";
        return 1;
    }

    if (choice == 1) {
        // Crear y llenar la matriz de adyacencia
        vector<vector<int>> matrix(n, vector<int>(n));
        cout << "Ingrese la matriz de adyacencia (1 para conexión, 0 para no conexión):\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                while (!(cin >> matrix[i][j]) || (matrix[i][j] != 0 && matrix[i][j] != 1)) {
                    cout << "Por favor ingrese solo 1 o 0 para las conexiones: ";
                    cin.clear(); // Limpiar error
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar entrada incorrecta
                }
            }
        }
        cout << "Matriz de adyacencia ingresada:\n";
        printMatrix(matrix);

        // Convertir matriz a lista de adyacencia
        vector<vector<int>> adjList(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 1) {
                    adjList[i].push_back(j);
                }
            }
        }
        cout << "\nLista de adyacencia generada:\n";
        printAdjList(adjList);

    } else if (choice == 2) {
        // Crear y llenar la lista de adyacencia
        vector<vector<int>> adjList(n);
        cout << "Ingrese las conexiones (nodos separados por espacio, -1 para terminar):\n";
        for (int i = 0; i < n; i++) {
            cout << "Nodo " << i << " conectado con: ";
            int node;
            while (true) {
                cin >> node;
                if (node == -1) break; // Terminar la entrada de nodos
                if (node >= 0 && node < n) { // Validar que el nodo esté dentro del rango
                    adjList[i].push_back(node);
                } else {
                    cout << "Nodo inválido. Debe ser un número entre 0 y " << n - 1 << endl;
                }
            }
            cin.clear();  // Limpiar el error de entrada por -1
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar cualquier entrada adicional
        }

        cout << "\nLista de adyacencia ingresada:\n";
        printAdjList(adjList);

        // Convertir lista de adyacencia a matriz
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j : adjList[i]) {
                matrix[i][j] = 1;
            }
        }
        cout << "\nMatriz de adyacencia generada:\n";
        printMatrix(matrix);

    }

    return 0;
}
