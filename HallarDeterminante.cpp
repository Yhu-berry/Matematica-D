#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Función para calcular el determinante de una matriz
int determinante(vector<vector<int>> matriz, int n) {
    int det = 0;
    if (n == 1) {
        return matriz[0][0];
    }
    if (n == 2) {
        return matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0];
    }
    vector<vector<int>> submatriz(n, vector<int>(n));
    for (int x = 0; x < n; x++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == x) continue;
                submatriz[subi][subj] = matriz[i][j];
                subj++;
            }
            subi++;
        }
        det += pow(-1, x) * matriz[0][x] * determinante(submatriz, n - 1);
    }
    return det;
}

// Función para guardar la matriz y el resultado en un archivo de texto
void guardarEnArchivo(vector<vector<int>> matriz, int resultado, int intento) {
    ofstream archivo("resultado.txt", ios::app); // Abre el archivo en modo de añadir
    if (archivo.is_open()) {
        archivo << "Intento " << intento << ":\n";
        for (const auto& fila : matriz) {
            archivo << "| ";
            for (const auto& elemento : fila) {
                archivo << setw(4) << elemento << " "; // Usar setw(4) para columnas uniformes
            }
            archivo << "|\n";
        }
        archivo << "Determinante: " << resultado << "\n\n";
        archivo.close();
    }
}

// Función principal
int main() {
    int n, intentos;
    cout << "Número de intentos: ";
    cin >> intentos;

    for (int k = 1; k <= intentos; k++) {
        cout << "\nIntento " << k << "\nTamaño de la matriz: ";
        cin >> n;

        vector<vector<int>> matriz(n, vector<int>(n));
        cout << "Elementos de la matriz:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> matriz[i][j];
            }
        }

        int resultado = determinante(matriz, n);
        cout << "Determinante: " << resultado << "\n";

        guardarEnArchivo(matriz, resultado, k);
    }

    cout << "\nResultados guardados en resultado.txt\n";
    return 0;
}
