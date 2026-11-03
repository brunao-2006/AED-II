#include <iostream>
#include <queue>
#include <vector>
#include <utility> // Necesaria para usar 'pair'

using namespace std;

const int total_nodos = 15;

// Modificamos el grafo para que asigne un peso (ej. minutos) a cada arista
void grafofijo(double grafo[][total_nodos], int& n){
    
    // Inicializamos matriz en 0 (0 indica que no hay conexión)
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            grafo[i][j] = 0; 
        }
    }

    // Estructura: {origen, destino, peso_en_minutos}
    double aristas[][3] = {
        {1, 2, 5}, {2, 3, 2}, {2, 4, 0.5}, {3, 5, 1}, {4, 7, 0.5}, {5, 3, 1},
        {5, 4, 0.5}, {5, 10, 1}, {6, 1, 3}, {7, 6, 0.5}, {7, 10, 0.5}, {8, 5, 0.5},
        {9, 8, 0.5}, {9, 3, 5}, {10, 5, 1}, {10, 11, 0.5}, {10, 12, 1}, {11, 13, 0.5},
        {11, 8, 0.5}, {12, 6, 2}, {12, 10, 1}, {12, 13, 2}, {13, 14, 3}, {14, 9, 2}
    };

    int total_aristas = sizeof(aristas) / sizeof(aristas[0]);
    for (int i = 0; i < total_aristas; i++){
        int origen = aristas[i][0];
        int destino = aristas[i][1];
        double peso = aristas[i][2];
        grafo[origen][destino] = peso;
    }
}

void leerinicio (int& inicio) {
    cout << "Ingrese el nodo de inicio (1-14): ";
    cin >> inicio;
}

void leerdestino (int& destino){
    cout << "Ingrese el nodo de destino (1-14): ";
    cin >> destino;
}

// Algoritmo de Dijkstra para grafos ponderados
void Dijkstra(double grafo[][total_nodos], int n, int inicio, int destino) {
    
    double dist[total_nodos];
    int padre[total_nodos];
    
    // Inicializamos los arreglos
    for (int i = 0; i < total_nodos; i++) {
        dist[i] = 999999; // Nuestro "infinito"
        padre[i] = -1;
    }
    
    // Cola de prioridad que ordena de menor a mayor distancia: {distancia_acumulada, nodo}
    priority_queue< pair<double, int>, vector< pair<double, int> >, greater< pair<double, int> > > pq;

    // Configuración inicial
    dist[inicio] = 0;
    pq.push(make_pair(0, inicio)); // make_pair es compatible con versiones antiguas de C++

    while (!pq.empty()) {
        double d = pq.top().first;    // Distancia acumulada hasta este nodo
        int nodo = pq.top().second;   // Nodo actual
        pq.pop();

        // Si encontramos un camino más largo en la cola de lo que ya tenemos registrado, lo ignoramos
        if (d > dist[nodo]) continue;

        // Optimización: si llegamos al destino, no necesitamos explorar más
        if (nodo == destino) break;

        // Explorar vecinos
        for (int vecino = 1; vecino <= n; vecino++) {
            double peso = grafo[nodo][vecino];
            
            // Si hay conexión (peso > 0)
            if (peso > 0) {

                // Si la distancia acumulada + el peso de la arista es menor que la distancia conocida al vecino
                if (dist[nodo] + peso < dist[vecino]) {
                    dist[vecino] = dist[nodo] + peso; // Actualizar distancia más corta
                    padre[vecino] = nodo;             // Guardar de dónde venimos
                    pq.push(make_pair(dist[vecino], vecino)); // Encolar nueva ruta a evaluar
                }
            }
        }
    }

    // Comprobar si se alcanzó el destino
    if (dist[destino] == 999999){
        cout << "No existe camino entre " << inicio << " y " << destino << endl;
        return;
    }

    // Reconstruir el camino
    int camino[total_nodos];
    int cantidad = 0;
    
    for (int actual = destino; actual != -1; actual = padre[actual]) {
        camino[cantidad++] = actual;
    }

    cout << "\nRuta mas rapida encontrada (Tiempo total: " << dist[destino] << " minutos):" << endl;
    for (int i = cantidad - 1; i >= 0; i--) {
        cout << camino[i] << (i > 0 ? " -> " : "\n");
    }
}

int main(){
    double grafo[total_nodos][total_nodos];
    int n = 14;
    int inicio, destino;

    grafofijo(grafo, n); // Ya no necesitamos el arreglo 'visitado' manual de tu código anterior
    leerinicio(inicio);
    leerdestino(destino);
    Dijkstra(grafo, n, inicio, destino);

    return 0;
}