#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class ReadCSV {
    // atributos
    private:
        void** matrix; // ponteiro genérico para a matriz
        size_t element_size; // tamanho do tipo de dado
        string filename;
        char sep;
        bool header;
        int skip_rows;
        int skip_cols;
        int max_rows;
        int max_cols;
        int n_rows;  // número efetivo de linhas após a leitura do csv
        int n_cols;  // número efetivo de colunas após a leitura do csv
        string data_type; // tipo de dado da matriz (int ou float)

        // Métodos auxiliares (privados)
        string determine_data_type(const string& cell); // Método para verificar o tipo de um dado (int ou float)
        size_t get_element_size(); // determinar o tamanho do tipo de dado
        ifstream open_file(); // abre o csv
        void** allocate_matrix(size_t get_element_size); // aloca dinamicamente a matriz
        void fill_matrix(ifstream& file, void** matrix); // preencha a matriz
        void free_matrix(void** matrix); // desaloca a memória
        bool is_matrix_loaded(); // Verificar se a matriz está alocada
        void determine_dimensions_and_datatype(); // ajusta as dimensoes e o tipo de dado da matriz
        void setN_rows(int n_rows); // setter para número efetivo de linhas 
        void setN_cols(int n_cols); // setter para número efetivo de colunas
        void setData_type(string data_type); // setter para o tipo de dado

    public:
        // Construtores e destrutor
        ReadCSV(); // padrão
        ReadCSV(string filename, char sep = ',', bool header = true, int skip_rows = 0, int skip_cols = 0, int max_rows = 1000, int max_cols = 1000);
        ~ReadCSV(); // destrutor

        // Métodos públicos
        void read_file(); // faz a leitura do csv para a matriz
        void** get_matrix(); // getter para o ponteiro da matriz
        int** get_matrix_as_int(); // getter para ponteiro de matriz de inteiros
        float** get_matrix_as_float(); // getter para ponteiro de matriz de floats
        int** copy_matrix_as_int(); // cria uma cópia da matriz e entrega um ponteiro de inteiro
        float** copy_matrix_as_float(); // cria uma cópia da matriz e entrega um ponteiro de float
        void display_matrix(); // exibir a matriz
        void setFilename(string filename); // setter para configurar o nome do arquivo após a criação do objeto
        
        // Getters e setters
        int getN_rows(); // numero efetivo de linhas após leitura da matriz
        int getN_cols(); //numero efetivo de colunas após leitura da matriz
        string getData_type(); // tipo de dados da matriz

        // Métodos para teste (excluir depois)
        void atributos(); // exibicao de atributos (para teste)
};


