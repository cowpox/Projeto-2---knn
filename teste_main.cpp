#include <iostream>
#include "knn.cpp"

using namespace std;

int main() {
    // Exemplo de matriz 3x3
    int rows = 3, cols = 3;
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j + 1; // Preenchendo a matriz com valores exemplo
        }
    }

    // Exemplo de array convertido para matriz 3x1
    int* array = new int[3]{15, 4, 75};
    int** array_as_matrix = new int*[3];
    for (int i = 0; i < 3; i++) {
        array_as_matrix[i] = new int[1]; // Cria uma "coluna"
        array_as_matrix[i][0] = array[i];
    }

    // Criar objeto KNN
    KNN knn;

    // Exibir matriz 3x3
    knn.display_matrix(matrix, rows, cols);

    // Exibir array como matriz 3x1
    knn.display_matrix(array_as_matrix, 3, 1);

    // Liberar memória da matriz 3x3
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    // Liberar memória do array convertido
    for (int i = 0; i < 3; i++) {
        delete[] array_as_matrix[i];
    }
    delete[] array_as_matrix;

    // Liberar memória do array original
    delete[] array;

    return 0;
}

