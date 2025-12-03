//Enrique Saldaña Vacio ID: 339424


#include <bits/stdc++.h>
#include <iostream>

using namespace std;

const int MAX = 20;   // Establecemos un límite para evitar que nos tardemos mucho
int adj[MAX][MAX];    // Matriz de adyacencia con ese número máximo de nodos
int n;                // Número de nodos
bool visitedDFS[MAX]; // Para evitar que si visita el nodo 0-1 trate de visitar el 1-0 ya que es un grafo no dirigido

void mostrarMatriz() {
    cout << "\nMatriz de adyacencia:\n";
    for (int i = 0; i < n; i++) {           //fila
        for (int j = 0; j < n; j++) {       //columna
            cout << adj[i][j] << " ";       //casilla
        }
        cout << endl;
    }
}

void DFS(int start) {
    cout << start << " ";      // Visitamos el nodo del inicio del gradfo
    visitedDFS[start] = true;  // Lo marcamos como visitado

    for (int i = 0; i < n; i++) {
        if (adj[start][i] == 1 && !visitedDFS[i]) {  // si la conexión existe y no se ha visitado
            DFS(i); //regresa la siguiente posición del nodo
        }
    }
}


void BFS(int start) {
    bool visitedBFS[MAX] = {false}; // Marca todo el arreglo como no visitados
    queue<int> q;                   // Cola para almacenar nodos

    visitedBFS[start] = true;  // Marcamos el nodo inicial como visitado
    q.push(start);             // Lo metemos a la cola

    while (!q.empty()) { //chacamos si la cola no está vacía
        int node = q.front();  // Sacamos el primero de la cola y cuando regresemos seguimos hasta vaciar la cola
        q.pop();    
        cout << node << " ";   // Mostramos el nodo y ya eliminamos el nodo de la queue

        // Revisamos todos los vecinos del nodo
        for (int i = 0; i < n; i++) {
            if (adj[node][i] == 1 && !visitedBFS[i]) { //si ña conexión existe y no se ha visitado
                visitedBFS[i] = true;
                q.push(i); // Lo agregamos a la cola para seguir
            }
        }
    }
}


int main() {
    int opcion, start;

    cout << "Ingrese el numero de nodos del grafo: (máximo 20)\n";

    do{
        cin >> n;
        if (n<1 || n>20)
        {
            cout << "Ingresa una cantidad de nodos válida\n"; 
        }
        
    } while (n<1 || n>20);
    
    cout << "Ingrese la matriz de adyacencia (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Mostrar matriz de adyacencia\n";
        cout << "2. Recorrido DFS\n";
        cout << "3. Recorrido BFS\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarMatriz();
                break;
            case 2:
                cout << "Ingrese nodo inicial: ";
                cin >> start;
                for (int i = 0; i < n; i++) visitedDFS[i] = false; // Reiniciamos visitados para poder contar desde cualquier nodo
                cout << "Recorrido DFS: ";
                DFS(start);
                cout << endl;
                break;
            case 3:
                cout << "Ingrese nodo inicial: ";
                cin >> start;
                cout << "Recorrido BFS: ";
                BFS(start);
                cout << endl;
                break;
            case 4:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no valida\n";
        }
    } while (opcion != 4);

    return 0;
}
