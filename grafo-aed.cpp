#include <iostream>
#include <queue>
using namespace std;

const int total_nodos = 15;

void grafofijo(int grafo[][total_nodos], bool visitado[], int& n){
    
    for (int i = 1; i <= n; i++){
        visitado[i] = false;
        for (int j = 1; j <= n; j++){
            grafo[i][j] = 0;
        }
    }

    int aristas[][2] = {
        {1, 2}, {2, 3}, {2, 4}, {3, 5}, {4, 7}, {5, 3},
        {5, 4}, {5, 10}, {6, 1}, {7, 6}, {7, 10}, {8, 5},
        {9, 8}, {9, 3}, {10, 5}, {10, 11}, {10, 12}, {11, 13},
        {11, 8}, {12, 6}, {12, 10}, {12, 13}, {13, 14}, {14, 9}
    };

    int total_aristas = sizeof(aristas) / sizeof(aristas[0]);
    for (int i = 0; i < total_aristas; i++){
        grafo[aristas[i][0]][aristas[i][1]] = 1;
    }
}

void leerinicio (int& inicio) {
    cout << "Ingrese el nodo de incio: ";
    cin >> inicio;
}

void leerdestino (int& destino){
    cout << "Ingrese el nodo de destino: ";
    cin >> destino;
}

void BFS(int grafo[][total_nodos], int n, int inicio, int destino) {
    bool visitado[total_nodos] = {false};
    int padre[total_nodos];
    for (int i = 0; i <= n; i++) padre[i] = -1;

    queue<int> cola;
    cola.push(inicio);
    visitado[inicio] = true;

    bool encontrado = false;

     while (!cola.empty()) {
        int nodo = cola.front();
        cola.pop();

        if (nodo == destino){
            encontrado = true;
            break;
        }
         for (int vecino = 1; vecino <= n; vecino++) {
            if (grafo[nodo][vecino] == 1 && !visitado[vecino]) {
                cola.push(vecino);
                visitado[vecino] = true;
                padre[vecino] = nodo;
            }
        }
    }

    if (!encontrado){
        cout << "No existe camino entre " << inicio << " y " << destino << endl;
        return;
    }

    int camino[total_nodos];
    int cantidad = 0;

    for (int actual = destino; actual != -1; actual = padre[actual]) {
        camino[cantidad++] = actual;
    }

    cout << "\nCamino con menor cantidad de aristas (" << cantidad - 1 << " aristas):" << endl;
    for (int i = cantidad - 1; i >= 0; i--) {
        cout << camino[i] << (i > 0 ? " -> " : "\n");
    }
}

int main(){
    int grafo[total_nodos][total_nodos];
    bool visitado[total_nodos];
    int n = 14;
    int inicio, destino;

    grafofijo(grafo, visitado, n);
    leerinicio(inicio);
    leerdestino(destino);
    BFS(grafo, n, inicio, destino);

return 0;
}
