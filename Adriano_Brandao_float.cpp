#include <iostream>
#include "read_csv.cpp"
#include "KNN.cpp"

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

void display_matrix(float** matrix, int rows, int cols) {
    // exibe os dados da matriz alocada pelo objeto
    cout << "Matriz lida (objeto):" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

float compare_matrices(int** matrix1, int** matrix2, int num_elements){
    float equals = 0;
    for (int i = 0; i < num_elements; i++){
        if (matrix1[i][0] == matrix2[i][0])
            equals++;
    }
    return equals / num_elements;
}

float compare_matrices(float** matrix1, float** matrix2, int num_elements){
    float equals = 0;
    for (int i = 0; i < num_elements; i++){
        if (matrix1[i][0] == matrix2[i][0])
            equals++;
    }
    return equals / num_elements;
}

int main(){
    // conjunto de treino
    cout << "\n=== treino.csv ===\n";
    // Criação do objeto treino
    // ReadCSV treino("tables\\float_dataset.csv", ',', true, 0, 0, 1000, 10);//dataset completo (inclui o teste)
    ReadCSV treino("tables\\float_treino.csv", ',', true, 0, 0, 20, 10);
    cout << "Objeto treino criado com sucesso." << endl;
    // Leitura do arquivo e criação da matrix
    treino.read_file();
    cout << endl;
    // Exibição da matriz pelo objeto
    treino.display_matrix();
    cout << endl;
    // Dimensões da matriz
    int rows_training = treino.getN_rows();
    int cols_training = treino.getN_cols();
    // Atribuição da matriz de treino
    float** matrix_training = treino.get_matrix_as_float();
    
    
    // labels
    cout << "\n=== labels.csv ===\n";
    // Criação do objeto labels
    // ReadCSV labels("tables\\float_label_dataset.csv", ',', true, 0, 0, 1000, 10);//todos os labels(inclui o teste)
    ReadCSV labels("tables\\float_labels.csv", ',', true, 0, 0, 20, 10);
    cout << "Objeto labels criado com sucesso." << endl;
    // Leitura do arquivo e criação da matrix
    labels.read_file();
    cout << endl;
    // Exibição da matriz pelo objeto
    labels.display_matrix();
    cout << endl;
    // Dimensões da matriz
    int num_labels = labels.getN_rows();
    // Atribuição da matriz de labels
    float** matrix_labels = labels.get_matrix_as_float();
    

    // conjunto de teste
    cout << "\n=== tables/teste.csv ===\n";
    // Criação do objeto teste
    ReadCSV teste("tables\\float_teste.csv", ',', true, 0, 0, 10, 10);
    cout << "Objeto teste criado com sucesso." << endl;
    // Leitura do arquivo e criação da matrix
    teste.read_file();
    cout << endl;
    // Exibição da matriz pelo objeto
    teste.display_matrix();
    cout << endl;
    // Dimensões da matriz
    int rows_testing = teste.getN_rows();
    int cols_testing = teste.getN_cols();
    // Atribuição da matriz de teste
    float** matrix_testing = teste.get_matrix_as_float();
    

    // gabarito
    cout << "\n=== gabarito.csv ===\n";
    // Criação do objeto gabarito
    ReadCSV gabarito("tables\\float_gabarito.csv", ',', true, 0, 0, 10, 10);
    cout << "Objeto gabarito criado com sucesso." << endl;
    // Leitura do arquivo e criação da matrix
    gabarito.read_file();
    cout << endl;
    // Exibição da matriz pelo objeto
    gabarito.display_matrix();
    cout << endl;
    // Dimensões da matriz
    int num_gabarito = gabarito.getN_rows();
    // Atribuição da matriz de teste
    float** matrix_gabarito = gabarito.get_matrix_as_float();

     
    // Criar e treinar modelo KNN
    KNN knn(3);  // k = 5
    knn.set_tables(rows_training, cols_training, num_labels, rows_testing, cols_testing);
    knn.fit(matrix_training, matrix_labels);
    float* predictions = knn.predict(matrix_testing);
    for (int i = 0; i < rows_testing; i++) {
        cout << "Teste " << i + 1 << ": Classe " << predictions[i] << endl;
    }
    // Atribuição da matriz de predições (para comparar com o gabarito)
    float ** matrix_predictions = knn.array_to_matrix_float(predictions, rows_testing);

    display_matrix(matrix_predictions, rows_testing, 1);

    float acuracia = compare_matrices(matrix_predictions, matrix_gabarito, rows_testing);

    cout << "Acurácia do modelo: " << acuracia * 100 << "%" << endl;

    return 0; 
}