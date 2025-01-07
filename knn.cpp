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
KNN::KNN() {
    // Inicialização padrão
    mat_training = nullptr;
    arr_labels = nullptr;
    mat_testing = nullptr;
    arr_prediction = nullptr;
    k = 5;
    cout << "Objeto KNN criado com construtor padrão." << endl;
}

KNN::KNN(int k) {
    // Inicialização com k parametrizado
    mat_training = nullptr;
    arr_labels = nullptr;
    mat_testing = nullptr;
    arr_prediction = nullptr;
    this->k = (k > 0) ? k : 5; // Garante que k seja válido
    if (k <= 0) {
        cout << "Erro: Valor de k inválido. Definindo k como 5." << endl;
    }
    cout << "Objeto KNN criado com construtor parametrizado." << endl;
}

KNN::~KNN() {
    // Destrutor
    if (mat_training != nullptr) {
        free_matrix(mat_training, rows_training); // Libera matriz de treino
        mat_training = nullptr;
        cout << "Matriz de treino desalocada no destrutor." << endl;
    }
    if (arr_labels != nullptr) {
        delete[] arr_labels; // Libera labels
        arr_labels = nullptr;
        cout << "Labels desalocados no destrutor." << endl;
    }
    if (mat_testing != nullptr) {
        free_matrix(mat_testing, rows_testing); // Libera matriz de teste
        mat_testing = nullptr;
        cout << "Matriz de teste desalocada no destrutor." << endl;
    }
    if (arr_prediction != nullptr) {
        delete[] arr_prediction; // Libera predições
        arr_prediction = nullptr;
        cout << "Predições desalocadas no destrutor." << endl;
    }
}


// Métodos públicos
void KNN::set_tables(int rows_training, int cols_training, int num_labels, int rows_testing, int cols_testing){
    this->rows_training = rows_training;
    this->cols_training = cols_training;
    this->num_labels = num_labels;
    this->rows_testing = rows_testing;
    this->cols_testing = cols_testing;
}
void KNN::fit(int** mat_training, int* arr_labels) {
    // Validar dados de entrada
    if (mat_training == nullptr || arr_labels == nullptr) {
        cout << "Erro: Dados de entrada inválidos (nullptr)!" << endl;
        return;
    }

    // Verificar consistência dos dados
    if (rows_training != num_labels) {
        cout << "Erro: Número de exemplos não corresponde ao número de labels!" << endl;
        return;
    }

    // Copiar matriz de treino para o atributo interno
    this->mat_training = new int*[rows_training];
    for (int i = 0; i < rows_training; i++) {
        this->mat_training[i] = new int[cols_training];
        for (int j = 0; j < cols_training; j++) {
            this->mat_training[i][j] = mat_training[i][j]; // Copiar valores
        }
    }

    // Copiar labels para o atributo interno
    this->arr_labels = new int[rows_training];
    for (int i = 0; i < rows_training; i++) {
        this->arr_labels[i] = arr_labels[i]; // Copiar valores
    }

    cout << "Modelo treinado com sucesso!" << endl;
}
void KNN::fit(int** mat_training, int** mat_labels) {
    // Validar dados de entrada
    if (mat_training == nullptr || mat_labels == nullptr) {
        cout << "Erro: Dados de entrada inválidos (nullptr)!" << endl;
        return;
    }

    // Verificar consistência dos dados
    if (rows_training != num_labels) {
        cout << "Erro: Número de exemplos não corresponde ao número de labels!"
             << endl;
        return;
    }

    // Converter matriz1D para array1D
    arr_labels = matrix_to_array(mat_labels, num_labels);

    // Copiar matriz de treino para o atributo interno
    this->mat_training = new int*[rows_training];
    for (int i = 0; i < rows_training; i++) {
        this->mat_training[i] = new int[cols_training];
        for (int j = 0; j < cols_training; j++) {
            this->mat_training[i][j] = mat_training[i][j]; // Copiar valores
        }
    }

    // Copiar labels para o atributo interno
    // Não há necessidade, pois já foram copiados no método de conversao de matriz para array

    cout << "Modelo treinado com sucesso!" << endl;
}


int* KNN::predict(int ** mat_teste){

}
void KNN::display_matrix(int ** matrix, int rows, int cols){
    cout << "Matriz: " << rows << " linhas x " << cols << " colunas." << endl;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    } 
}
int* KNN::matrix_to_array(int ** matrix, int num_registers){
    int* matrix_as_array = new int[num_registers];
    for (int i = 0; i < num_registers; i++){
        matrix_as_array[i] = matrix[i][0];
    }
    return matrix_as_array;
}
int** KNN::array_to_matrix(int * array, int num_registers){
    int** array_as_matrix = new int*[num_registers];
    for (int i = 0; i < num_registers; i++){
        array_as_matrix[i] = new int[1]; //cria uma coluna
        array_as_matrix[i][0] = array[i];
    }
    return array_as_matrix;
}
