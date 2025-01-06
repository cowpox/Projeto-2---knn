#include "knn.h"
#include <iostream>

using namespace std;

void KNN::free_matrix(int** matrix, int rows) {
    // desaloca a memória apontada pelo ponteiro **matrix
    for (int i = 0; i < rows; ++i) {
        delete[] (matrix[i]);
    }
    delete[] matrix;
}




// Construtores e destrutor
KNN::KNN(){
    // padrão
    k = 5;
}
KNN::KNN(int k){
    // parametrizado
    this->k = k;
}
KNN::~KNN(){
    // destrutor
    if (mat_training != nullptr) {
        free_matrix(mat_training, rows_training); // Libera a memória alocada para a matriz de treino
        cout << "Matriz de treino desalocada no destrutor." << endl << endl;
    }
    if (mat_labels != nullptr) {
        delete[] mat_labels; // Libera a memória alocada para a matriz de labels
        cout << "Matriz de labels desalocada no destrutor." << endl << endl;
    }
    if (mat_testing != nullptr) {
        free_matrix(mat_testing, rows_testing); // Libera a memória alocada para a matriz de teste
        cout << "Matriz de teste desalocada no destrutor." << endl << endl;
    }
    if (mat_prediction != nullptr) {
        delete[] mat_prediction; // Libera a memória alocada para a matriz de labels
        cout << "Matriz de resultados desalocada no destrutor." << endl << endl;
    }
}

// Métodos públicos
void KNN::set_tables(int rows_training, int cols_training, int rows_labels, int rows_testing, int cols_testing){
    this->rows_training = rows_training;
    this->cols_training = cols_training;
    this->rows_labels = rows_labels;
    this->rows_testing = rows_testing;
    this->cols_testing = cols_testing;
}
void KNN::fit(int ** mat_treino, int * mat_labels){
    cout << endl; // teste apenas
}
int* KNN::predict(int ** mat_teste){

}