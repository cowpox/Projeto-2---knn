#include <iostream>

using namespace std;

class KNN {
    // atributos
    private:
        int ** mat_training; // ponteiro para a matriz de treino
        int * arr_labels; // ponteiro para a matriz de labels
        int ** mat_testing; // ponteiro para a matriz de teste
        int * arr_prediction; // ponteiro para a matriz de predição

        int k; // k do knn

        int rows_training, cols_training; // dimensões da matriz de treino
        int rows_labels; // dimensão do array de labels
        int rows_testing, cols_testing; // dimensões do array de teste

        // Métodos auxiliares (privados)
        void free_matrix(int** matrix, int rows); // desaloca a memória

    public:
        // Construtores e destrutor
        KNN(); // padrão
        KNN(int k);
        ~KNN(); // destrutor

        // Métodos públicos
        void set_tables(int rows_training, int cols_training, int rows_labels, int rows_testing, int cols_testing);
        void fit(int ** mat_training, int * arr_labels);
        int* predict(int ** mat_teste);
        void display_matrix(int ** matrix, int rows, int cols);
        int* matrix_to_array(int ** matrix, int num_registers); //num_registers = número de linhas matrix = número de elementos array
        int** array_to_matrix(int * array, int num_registers); ////num_registers = número de elementos do array = número de linhas matrix

};