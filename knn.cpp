#include "knn.h"
#include <iostream>
#include <cmath> //para usar sqrt
#include <cfloat> //para usar DBL_MAX
#include <map> //para usar map

using namespace std;

void KNN::free_matrix(int** matrix, int rows) {
    // desaloca a memória apontada pelo ponteiro **matrix
    for (int i = 0; i < rows; ++i) {
        delete[] (matrix[i]);
    }
    delete[] matrix;
}

double KNN::calculate_distance(int* a, int* b, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return sqrt(sum);
}

// Retorna um array (neighbors) de tamanho k, onde cada
// elemento é o índice de um dos k exemplos de treinamento mais próximos.
int* KNN::find_k_nearest_neighbors(double* distances, int k, int num_examples) {
    int* neighbors = new int[k];
    for (int i = 0; i < k; i++) { //itera k vezes para encontrar os k vizinhos mais próximos
        //encontra o índice do menor valor
        double min_dist = DBL_MAX; //inicializa com o maior valor possível
        int min_index = -1; //indica que ainda não há vizinho selecionado
        for (int j = 0; j < num_examples; j++) { //percorre todos os exemplos de treinamento
            if (distances[j] < min_dist) {
                //Atualiza min_dist com o menor valor encontrado e min_index com o índice correspondente.
                min_dist = distances[j];
                min_index = j;
            }
        }
        neighbors[i] = min_index; // Armazena o índice do vizinho mais próximo
        distances[min_index] = DBL_MAX; // Define a distância do vizinho selecionado como DBL_MAX,
                                        //garantindo que ele não será selecionado novamente nas próximas iterações
    }
    return neighbors;
}

//Retorna a classe mais frequente entre os k vizinhos.
int KNN::determine_majority_class(int* neighbors, int k) {
    //inicializar um mapa para contar frequencias
    //este mapa associa cada classe (chave) ao número de ocorrências dessa classe (valor).
    map<int, int> class_count;

    //contar a frequencia das classes
    for (int i = 0; i < k; i++) { //Itera pelos índices dos k vizinhos mais próximos
        // o mapa começa zerado
        // neighbors[i]: Recupera o índice do vizinho atual.
        // arr_labels[neighbors[i]]: Recupera o rótulo da classe correspondente ao vizinho.
        // class_count[arr_labels[neighbors[i]]]++: Incrementa a contagem da classe no mapa.
        // Se a classe ainda não estiver presente no mapa, ela será automaticamente adicionada com valor inicial 0
        // e depois incrementada para 1 (na mesma iteração)
        class_count[arr_labels[neighbors[i]]]++;
    }

    //encontrar a classe mais frequente
    //inicializa a classe majoritária como -1 (indicando que nenhuma foi encontrada ainda).
    //inicializa o contador máximo como 0.
    int majority_class = -1, max_count = 0;
    for (auto& pair : class_count) { //percorre cada par (key, value) do map.
        // Compara o número de ocorrências (pair.second) com max_count.
        // Se maior, atualiza:
        // max_count com o novo número de ocorrências.
        // majority_class com a classe correspondente (pair.first).
        // CRITÉRIO DE DESEMPATE
        // Quando ocorre um empate, escolhemos a classe com o menor valor numérico.
        if (pair.second > max_count || (pair.second == max_count && pair.first < majority_class)) {
            max_count = pair.second;
            majority_class = pair.first;
        }
    }
    return majority_class;
}



// Construtores e destrutor
KNN::KNN() {
    // Inicialização padrão
    mat_training = nullptr;
    arr_labels = nullptr;
    mat_testing = nullptr;
    arr_prediction = nullptr;
    k = 5;
    is_trained = false;
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
    is_trained = false;
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
    is_trained = true;
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
    // Não há necessidade, pois já foram copiados no método de conversao de
    // matriz para array
    is_trained = true;
    cout << "Modelo treinado com sucesso!" << endl;
}

int* KNN::predict(int** mat_testing) {
    // Validar dados de entrada
    if (mat_testing == nullptr) {
        cout << "Erro: Dados de entrada inválidos (nullptr)!" << endl;
        return nullptr;
    }

    // Garantir que o modelo foi treinado
    if (!is_trained) {
        cout << "Erro: o modelo não foi treinado! Por favor, chame o método fit antes de predict." << endl;
        return nullptr;
    }

    // Garantir que as dimensões sejam consistentes
    if (cols_training != cols_testing) {
        cout << "Erro: O número de colunas da matriz de teste não corresponde ao número de colunas da matriz de treino!" << endl;
        return nullptr;
    }

    // Alocar memória para arr_prediction
    arr_prediction = new int[rows_testing];

    // Iterar por cada exemplo
    for (int i = 0; i < rows_testing; i++) {
        // Calcular distâncias
        double* distances = new double[rows_training]; //cria um array de distâncias
        for (int j = 0; j < rows_training; j++) {
            distances[j] = calculate_distance(mat_testing[i], mat_training[j], cols_training);
        }

        // Encontrar os k vizinhos mais próximos
        int* neighbors = find_k_nearest_neighbors(distances, k, rows_training);

        // Determinar a classe majoritária
        arr_prediction[i] = determine_majority_class(neighbors, k);

        // Liberar memória temporária
        delete[] distances;
        delete[] neighbors;
    }

    return arr_prediction;
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
