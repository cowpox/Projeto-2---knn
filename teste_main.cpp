#include <iostream>
#include "knn.cpp"

using namespace std;

#include <iostream>
#include "knn.h"

using namespace std;

void display_matrix(int** matrix, int rows, int cols) {
    // exibe os dados da matriz alocada pelo objeto
    cout << "Matriz lida (objeto):" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

int main() {
    // Definir dados de treinamento
    int training_data[10][4] = {
        {1, 2, 3, 4},     // Treino 1
        {2, 3, 4, 5},     // Treino 2
        {3, 4, 5, 6},     // Treino 3
        {4, 5, 6, 7},     // Treino 4
        {5, 6, 7, 8},     // Treino 5
        {6, 7, 8, 9},     // Treino 6
        {7, 8, 9, 10},    // Treino 7
        {8, 9, 10, 11},   // Treino 8
        {9, 10, 11, 12},  // Treino 9
        {10, 11, 12, 13}  // Treino 10
    };
    int labels[10] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1};  // Labels correspondentes

    // Definir dados de teste
    int testing_data[5][4] = {
        {2, 3, 4, 5},      // Teste 1
        {5, 6, 7, 8},      // Teste 2
        {8, 9, 10, 11},    // Teste 3
        {11, 12, 13, 14},  // Teste 4
        {1, 2, 3, 4}       // Teste 5
    };

    // Inicializar matrizes de treinamento e teste
    int rows_training = 10, cols_training = 4;
    int** mat_training = new int*[rows_training];
    for (int i = 0; i < rows_training; i++) {
        mat_training[i] =
            new int[cols_training]{training_data[i][0], training_data[i][1],
                                   training_data[i][2], training_data[i][3]};
    }

    int rows_testing = 5, cols_testing = 4;
    int** mat_testing = new int*[rows_testing];
    for (int i = 0; i < rows_testing; i++) {
        mat_testing[i] =
            new int[cols_testing]{testing_data[i][0], testing_data[i][1],
                                  testing_data[i][2], testing_data[i][3]};
    }

    // Criar e treinar modelo KNN
    KNN knn(3);  // k = 3
    knn.set_tables(rows_training, cols_training, rows_training, rows_testing,
                   cols_testing);
    knn.fit(mat_training, labels);

    int* predictions = knn.predict(mat_testing);
    for (int i = 0; i < rows_testing; i++) {
        cout << "Teste " << i + 1 << ": Classe " << predictions[i] << endl;
    }

    // Liberar memória
    for (int i = 0; i < rows_training; i++) delete[] mat_training[i];
    delete[] mat_training;
    for (int i = 0; i < rows_testing; i++) delete[] mat_testing[i];
    delete[] mat_testing;
    delete[] predictions;

    return 0;
}


