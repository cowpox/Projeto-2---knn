#include "read_csv.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;

// Métodos auxiliares (privados)
string ReadCSV::determine_data_type(const string& cell) {
    // retorna o tipo de dado de cada célula (int, float, empty ou unknown)
    if (cell.empty()) {
        return "empty"; // Célula vazia
    }

    // Verifica se contém um ponto decimal ou notação científica ('e' ou 'E')
    bool is_float_candidate = (cell.find('.') != string::npos || 
                               cell.find('e') != string::npos || 
                               cell.find('E') != string::npos);

    // Tenta converter para float se for um candidato válido
    if (is_float_candidate) {
        try {
            stof(cell); // Tenta converter para float
            return "float";  // Retorna float se a conversão for bem-sucedida
        } catch (const exception&) {
            // Ignora exceção
        }
    }

    // Tenta converter para inteiro
    try {
        stoi(cell); // Tenta converter para int
        return "int";    // Retorna int se a conversão for bem-sucedida
    } catch (const exception&) {
        // Ignora exceção
    }

    return "unknown"; // Retorna "unknown" para valores inválidos
}
size_t ReadCSV::get_element_size() {
    //determina o tamanho do tipo de dado
    if (data_type == "int") {
        return sizeof(int);
    } else if (data_type == "float") {
        return sizeof(float);
    } else {
        cerr << "Erro: Tipo de dado desconhecido (" << data_type << ")." << endl;
        throw runtime_error("Tipo de dado inválido.");
    }
}
ifstream ReadCSV::open_file(){
    // abre o arquivo
    if (filename.empty()) {
        cerr << "Erro: Nome do arquivo não foi configurado!" << endl;
        throw runtime_error("Nome do arquivo não configurado.");
    }

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        throw runtime_error("Erro ao abrir o arquivo.");
    }

    return file;
}
void** ReadCSV::allocate_matrix(size_t element_size) {
    // aloca um a memória para um ponteiro void, que pode conter
    // tanto dados int quanto float. Porém, eles devem ser tipados
    // (casting) antes da manipulação
    if (n_rows <= 0 || n_cols <= 0) {
        cerr << "Erro: Dimensões inválidas para a matriz (" << n_rows << " x "
             << n_cols << ")." << endl;
        throw runtime_error("Dimensões inválidas para alocação da matriz.");
    }

    // Alocar matriz como um array de ponteiros para linhas
    void** matrix = new void*[n_rows];
    for (int i = 0; i < n_rows; ++i) {
        // Alocar memória para cada linha com base no tamanho do elemento
        matrix[i] = new char[element_size * n_cols];
    }

    cout << "Matriz alocada dinamicamente com sucesso: (" << data_type << ") [" << n_rows << "]["
         << n_cols << "]" << endl;
    return matrix;
}
void ReadCSV::fill_matrix(ifstream& file, void** matrix) {
    // preenche a matriz alocada com os dados válidos do CSV
    string line;
    int row = 0;

    int cabecalho = header ? 1 : 0; // Verifica a presença do cabeçalho
    int first_row = skip_rows + cabecalho;

    // Pular linhas iniciais
    for (int i = 0; i < first_row && getline(file, line); i++) {
        continue;
    }

    // Processar cada linha da matriz
    while (getline(file, line) && row < n_rows) {
        stringstream ss(line);
        string cell;

        // Pular colunas iniciais
        for (int discard_col = 0; discard_col < skip_cols; discard_col++) {
            getline(ss, cell, sep);
        }

        // Processar cada célula válida usando `for`
        for (int col = 0; col < n_cols; col++) {
            if (!getline(ss, cell, sep)) {
                // Caso não existam mais células, completar com valores padrão
                cerr << "Aviso: Linha incompleta na linha " << row + 1 << ", coluna " << col + 1 << endl;
                cell = ""; // Define a célula como vazia para tratamento abaixo
            }

            // Verificar se a célula está vazia
            if (cell.empty()) {
                if (data_type == "int") {
                    reinterpret_cast<int*>(matrix[row])[col] = 0; // Valor padrão
                } else if (data_type == "float") {
                    reinterpret_cast<float*>(matrix[row])[col] = 0.0f; // Valor padrão
                }
            } else {
                try {
                    if (data_type == "int") {
                        reinterpret_cast<int*>(matrix[row])[col] = stoi(cell);
                    } else if (data_type == "float") {
                        reinterpret_cast<float*>(matrix[row])[col] = stof(cell);
                    }
                } catch (const exception& e) {
                    cerr << "Erro: Valor inválido na linha " << row + 1 << ", coluna " << col + 1
                         << ". Valor: \"" << cell << "\". Exceção: " << e.what() << endl;
                    if (data_type == "int") {
                        reinterpret_cast<int*>(matrix[row])[col] = 0; // Valor padrão
                    } else if (data_type == "float") {
                        reinterpret_cast<float*>(matrix[row])[col] = 0.0f; // Valor padrão
                    }
                }
            }
        }
        row++; // Incrementa a linha
    }
}
void ReadCSV::free_matrix(void** matrix) {
    // desaloca a memória apontada pelo ponteiro **matrix
    for (int i = 0; i < n_rows; ++i) {
        delete[] reinterpret_cast<char*>(matrix[i]);
    }
    delete[] matrix;
}
bool ReadCSV::is_matrix_loaded(){
    // Verificar se a matriz está alocada
    return matrix != nullptr;
}
void ReadCSV::determine_dimensions_and_datatype() {
    // calcula as dimensoes da matriz com os dados validos
    // determina o tipo de dado (se houver pelo menos 1 float => float)     
     
     //abre o arquivo
    ifstream file;

    try {
        file = open_file();
    } catch (const runtime_error& e) {
        cerr << "Exceção: " << e.what() << endl;
        return;
    }
    
    // Determinar dimensões necessárias (n_rows e n_cols)
    string line;
    int n_rows = 0;
    int n_cols = 0;

    // Pula linhas iniciais conforme skip_rows e cabeçalho
    int cabecalho = header ? 1 : 0; //ternário para definir a presença de cabeçalho
    int first_row = skip_rows + cabecalho;

    // Contagem preliminar
    int row = 0;
    while (row < first_row && getline(file, line)) {
        row++;
    }

    // Agora conta o número de linhas e colunas necessárias
    bool has_float = false; // tag para identificar float
    while (getline(file, line)) {
        if (n_rows >= max_rows) break; // Respeita o limite de linhas
        stringstream ss(line);
        string cell;
        int col = 0;

        // Conta colunas, ignorando as colunas descartadas (skip_cols)
        int discard_col = 0;
        while (discard_col < skip_cols && getline(ss, cell, sep)) {
            discard_col++;
        }

        // Conta o número de colunas válidas e verifica a presenca de float
        while (getline(ss, cell, sep) && col < max_cols) {
            // Verifica se o tipo da célula é float (apenas se ainda não foi detectado)
            if (!has_float) {
                if (determine_data_type(cell) == "float") {
                    has_float = true;
                }
            }
            col++;
        }

        if (col > n_cols) n_cols = col;  // Atualiza o número máximo de colunas
        n_rows++;
    }

    string data_type = has_float ? "float" : "int"; //ternário para definir o datatype

    // Atualiza os valores da classe
    setN_rows(n_rows);
    setN_cols(n_cols);
    setData_type(data_type);

    // Fecha e reabre o arquivo para a leitura final
    file.close();
}
void ReadCSV::setN_rows(int n_rows){
    // setter para o numero efetivo de linhas após leitura da matriz
    this->n_rows = n_rows;
}
void ReadCSV::setN_cols(int n_cols){
    // setter para o numero efetivo de colunas após leitura da matriz
    this->n_cols = n_cols;
}
void ReadCSV::setData_type(string data_type){
    // setter para o tipo de dado
    this->data_type = data_type;
}


// Construtores e destrutor
ReadCSV::ReadCSV(){
    // padrão
    matrix = nullptr;
    element_size = 0;
    sep = ',';
    header = true;
    skip_rows = 0;
    skip_cols = 0;
    max_rows = 100;
    max_cols = 100;
}
ReadCSV::ReadCSV(string filename, char sep, bool header, int skip_rows, int skip_cols, int max_rows, int max_cols){
    // parametrizado
    matrix = nullptr;
    element_size = 0;
    this->filename = filename;
    this->sep = sep;
    this->header = header;
    this->skip_rows = skip_rows;
    this->skip_cols = skip_cols;
    this->max_rows = max_rows;
    this->max_cols = max_cols;
}
ReadCSV::~ReadCSV(){
    // destrutor
    if (matrix != nullptr) {
        free_matrix(matrix); // Libera a memória alocada
        cout << "Matriz desalocada no destrutor." << endl << endl;
    }
}

// Métodos públicos
void ReadCSV::read_file() {
    // abre o arquivo, determina o tipo do dado e as dimensoes da matriz
    // aloca e preenche a matriz
    ifstream file;

    try {
        file = open_file();
    } catch (const runtime_error& e) {
        cerr << "Exceção: " << e.what() << endl;
        return;
    }

    // Determinar dimensões e tipo de dados
    determine_dimensions_and_datatype();

    // Obter tamanho do elemento com base no tipo de dado
    element_size = get_element_size();

    // Alocar matriz dinamicamente
    if (matrix != nullptr) {
        free_matrix(matrix); // Libera a matriz anterior, se existir
    }
    matrix = allocate_matrix(element_size);

    // Preencher a matriz
    fill_matrix(file, matrix);

    file.close();
}
void** ReadCSV::get_matrix() {
    // getter para o ponteiro da matriz
    return matrix;
}
int** ReadCSV::get_matrix_as_int() {
    // getter para ponteiro de matriz de inteiros
    if (data_type != "int") {
        cerr << "Erro: A matriz não contém dados inteiros!" << endl;
        return nullptr;
    }
    return reinterpret_cast<int**>(matrix);
}
float** ReadCSV::get_matrix_as_float() {
    // getter para ponteiro de matriz de floats
    if (data_type != "float") {
        cerr << "Erro: A matriz não contém dados float!" << endl;
        return nullptr;
    }
    return reinterpret_cast<float**>(matrix);
}
int** ReadCSV::copy_matrix_as_int() {
    // cria uma cópia da matriz e entrega um ponteiro de inteiro
    // Verifica se a matriz está carregada
    if (matrix == nullptr) {
        cerr << "Erro: Nenhuma matriz carregada para copiar." << endl;
        return nullptr;
    }

    // Verifica se o tipo de dado é compatível
    if (data_type != "int") {
        cerr << "Erro: A matriz não contém dados inteiros!" << endl;
        return nullptr;
    }

    // Alocar uma nova matriz de inteiros
    int** new_matrix = new int*[n_rows];
    for (int i = 0; i < n_rows; ++i) {
        new_matrix[i] = new int[n_cols];
        for (int j = 0; j < n_cols; ++j) {
            new_matrix[i][j] = reinterpret_cast<int*>(matrix[i])[j];
        }
    }

    return new_matrix;
}
float** ReadCSV::copy_matrix_as_float() {
    // cria uma cópia da matriz e entrega um ponteiro de float
    // Verifica se a matriz está carregada
    if (matrix == nullptr) {
        cerr << "Erro: Nenhuma matriz carregada para copiar." << endl;
        return nullptr;
    }

    // Verifica se o tipo de dado é compatível
    if (data_type != "float") {
        cerr << "Erro: A matriz não contém dados float!" << endl;
        return nullptr;
    }

    // Alocar uma nova matriz de floats
    float** new_matrix = new float*[n_rows];
    for (int i = 0; i < n_rows; ++i) {
        new_matrix[i] = new float[n_cols];
        for (int j = 0; j < n_cols; ++j) {
            new_matrix[i][j] = reinterpret_cast<float*>(matrix[i])[j];
        }
    }

    return new_matrix;
}
void ReadCSV::display_matrix() {
    // exibe os dados da matriz alocada pelo objeto
    cout << "Matriz lida (objeto):" << endl;
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            if (data_type == "int") {
                cout << reinterpret_cast<int*>(matrix[i])[j] << "\t";
            } else if (data_type == "float") {
                cout << reinterpret_cast<float*>(matrix[i])[j] << "\t ";
            }
        }
        cout << endl;
    }
}
void ReadCSV::setFilename(string filename){
    // setter para configurar nome do arquivo após criação do objeto
    this->filename = filename;
}

// Getters e Setters
int ReadCSV::getN_rows(){
    // numero efetivo de linhas após leitura da matriz
    return n_rows;
}
int ReadCSV::getN_cols(){
    // numero efetivo de linhas após leitura da matriz
    return n_cols;
}
string ReadCSV::getData_type(){
    // tipo de dados da matriz
    return data_type;
}

// Métodos para teste (excluir depois)
void ReadCSV::atributos(){
    // exibicao de atributos (para testes)
    cout << "Filename: " << filename << endl;
    cout << "Separator: " << sep << endl;
    cout << "Header: " << header << endl;
    cout << "Skip_rows: " << skip_rows << endl;
    cout << "Skip_cols: " << skip_cols << endl;
    cout << "Max_rows: " << max_rows << endl;
    cout << "Max_cols: " << max_cols << endl;
}



























