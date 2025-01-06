#include <iostream>
#include "read_csv.cpp"

using namespace std;

int main(){
    // Teste 1: 
    cout << "\n=== features-Aula 13 - Projeto 1 - dataset1.csv ===\n";

    // Criação do objeto dataset1
    ReadCSV dataset1("features-Aula 13 - Projeto 1 - dataset1.csv", ',', true, 0, 0, 10, 10);
    cout << "Objeto dataset1 criado com sucesso." << endl;

    // Leitura do arquivo e criação da matrix
    dataset1.read_file();
    cout << endl;

    // Exibição da matriz pelo objeto
    dataset1.display_matrix();
    cout << endl;

    // Atribuição do ponteiro retornado pelo objeto dependendo do tipo de dados
    if (dataset1.getData_type() == "int") {
        int** matrix = dataset1.get_matrix_as_int();
        cout << "Ponteiro (int) atribuído com sucesso." << endl;

        // Exibição da matriz pelo ponteiro
        cout << endl;
        cout << "Matriz lida (ponteiro - int):" << endl;
        for (int i = 0; i < dataset1.getN_rows(); ++i) {
            for (int j = 0; j < dataset1.getN_cols(); ++j) {
                cout << matrix[i][j] << "\t";  // Tabulação entre os elementos
            }
            cout << endl;
        }
    } else if (dataset1.getData_type() == "float") {
        float** matrix = dataset1.get_matrix_as_float();
        cout << "Ponteiro (float) atribuído com sucesso." << endl;

        // Exibição da matriz pelo ponteiro
        cout << endl;
        cout << "Matriz lida (ponteiro - float):" << endl;
        for (int i = 0; i < dataset1.getN_rows(); ++i) {
            for (int j = 0; j < dataset1.getN_cols(); ++j) {
                cout << matrix[i][j] << "\t";  // Tabulação entre os elementos
            }
            cout << endl;
        }
    }

    // Teste 2: 
    cout << "\n=== features-Aula 13 - Projeto 1 - dataset2.csv ===\n";

    // Criação do objeto dataset2
    ReadCSV dataset2("features-Aula 13 - Projeto 1 - dataset2.csv", ',', true, 0, 0, 10, 10);
    cout << "Objeto dataset2 criado com sucesso." << endl;

    // Leitura do arquivo e criação da matrix
    dataset2.read_file();
    cout << endl;

    // Exibição da matriz pelo objeto
    dataset2.display_matrix();
    cout << endl;

    // Atribuição do ponteiro retornado pelo objeto dependendo do tipo de dados
    if (dataset2.getData_type() == "int") {
        int** matrix = dataset2.get_matrix_as_int();
        cout << "Ponteiro (int) atribuído com sucesso." << endl;

        // Exibição da matriz pelo ponteiro
        cout << endl;
        cout << "Matriz lida (ponteiro - int):" << endl;
        for (int i = 0; i < dataset2.getN_rows(); ++i) {
            for (int j = 0; j < dataset2.getN_cols(); ++j) {
                cout << matrix[i][j] << "\t";  // Tabulação entre os elementos
            }
            cout << endl;
        }
    } else if (dataset2.getData_type() == "float") {
        float** matrix = dataset2.get_matrix_as_float();
        cout << "Ponteiro (float) atribuído com sucesso." << endl;

        // Exibição da matriz pelo ponteiro
        cout << endl;
        cout << "Matriz lida (ponteiro - float):" << endl;
        for (int i = 0; i < dataset2.getN_rows(); ++i) {
            for (int j = 0; j < dataset2.getN_cols(); ++j) {
                cout << matrix[i][j] << "\t";  // Tabulação entre os elementos
            }
            cout << endl;
        }
    }

    return 0; // O destrutor de `reader` desaloca a matriz automaticamente
}