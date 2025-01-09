# Documentação Detalhada do Código

## Visão Geral
Este documento descreve detalhadamente o funcionamento do código do projeto k-NN, incluindo as classes, métodos e decisões técnicas envolvidas. O projeto é composto por dois módulos principais:

1. **Módulo `KNN`**: Implementa o algoritmo k-Nearest Neighbors.
2. **Módulo `ReadCSV`**: Responsável por carregar dados de arquivos CSV e convertê-los para matrizes.

---

## Classe `KNN`

### Propósito
A classe `KNN` realiza a classificação de dados usando o método k-NN. Suporta dados de tipo inteiro e float.

### Atributos Privados
- **Matrizes de Treino e Teste**:
  - `int** mat_training`: Matriz de treino para inteiros.
  - `float** mat_training_float`: Matriz de treino para floats.
  - `int** mat_testing`: Matriz de teste para inteiros.
  - `float** mat_testing_float`: Matriz de teste para floats.

- **Rótulos e Predições**:
  - `int* arr_labels`: Rótulos do conjunto de treino para inteiros.
  - `float* arr_labels_float`: Rótulos do conjunto de treino para floats.
  - `int* arr_prediction`: Predições para inteiros.
  - `float* arr_prediction_float`: Predições para floats.

- **Outros Atributos**:
  - `int k`: Número de vizinhos mais próximos.
  - `bool is_trained`: Indica se o modelo foi treinado.
  - `bool is_float`: Define se os dados são floats.
  - `bool enable_logs`: Controla a exibição de logs durante a execução.

### Construtores
1. **Construtor Padrão**:
   Define `k = 5` e inicializa os atributos como nulos ou valores padrão.
   ```cpp
   KNN::KNN() {
       k = 5;
       is_trained = false;
       is_float = false;
   }
   ```

2. **Construtor Parametrizado**:
   Permite definir o valor de `k` ao criar o objeto.
   ```cpp
   KNN::KNN(int k) {
       this->k = k;
       is_trained = false;
       is_float = false;
   }
   ```

### Métodos Públicos

#### `set_tables`
Define as dimensões das matrizes de treino e teste, verificando inconsistências.
```cpp
void KNN::set_tables(int rows_training, int cols_training, int num_labels, int rows_testing, int cols_testing);
```

#### `fit`
Realiza o treinamento do modelo armazenando os dados de treino e rótulos.
```cpp
void KNN::fit(int** mat_training, int* arr_labels);
void KNN::fit(float** mat_training, float* arr_labels);
```

#### `predict`
Realiza a classificação dos exemplos no conjunto de teste.
```cpp
int* KNN::predict(int** mat_testing);
float* KNN::predict(float** mat_testing);
```

#### `array_to_matrix` e `matrix_to_array`
Converte entre arrays unidimensionais e matrizes bidimensionais para facilitar a manipulação dos dados.
```cpp
int** KNN::array_to_matrix(int* array, int num_registers);
float** KNN::array_to_matrix_float(float* array, int num_registers);
```

### Métodos Privados

#### `calculate_distance`
Calcula a distância Euclidiana entre dois exemplos.
```cpp
double KNN::calculate_distance(int* a, int* b, int size);
double KNN::calculate_distance_float(float* a, float* b, int size);
```

#### `find_k_nearest_neighbors`
Identifica os `k` vizinhos mais próximos com base nas distâncias calculadas.
```cpp
int* KNN::find_k_nearest_neighbors(double* distances, int k, int num_examples);
```

#### `determine_majority_class`
Determina a classe majoritária entre os `k` vizinhos mais próximos.
```cpp
int KNN::determine_majority_class(int* neighbors, int k);
```

---

## Classe `ReadCSV`

### Propósito
Carregar dados de arquivos CSV, identificando automaticamente o tipo de dado (int ou float), e convertê-los em matrizes utilizáveis pelo modelo.

### Atributos Privados
- `void** matrix`: Ponteiro genérico para armazenar a matriz carregada.
- `string filename`: Nome do arquivo CSV.
- `char sep`: Separador dos campos (ex.: `,`).
- `bool header`: Indica se o CSV possui cabeçalho.
- `int n_rows`, `int n_cols`: Dimensões efetivas da matriz carregada.
- `string data_type`: Tipo de dado identificado (int ou float).

### Construtores
1. **Construtor Padrão**:
   Inicializa os atributos com valores padrão.
   ```cpp
   ReadCSV::ReadCSV() {
       matrix = nullptr;
       sep = ',';
       header = true;
   }
   ```

2. **Construtor Parametrizado**:
   Permite configurar o nome do arquivo, separador, e outras opções.
   ```cpp
   ReadCSV::ReadCSV(string filename, char sep, bool header, int skip_rows, int skip_cols, int max_rows, int max_cols);
   ```

### Métodos Públicos

#### `read_file`
Lê o arquivo CSV, determina o tipo de dado, aloca e preenche a matriz.
```cpp
void ReadCSV::read_file();
```

#### `get_matrix_as_int` e `get_matrix_as_float`
Retorna a matriz carregada, convertida para o tipo apropriado.
```cpp
int** ReadCSV::get_matrix_as_int();
float** ReadCSV::get_matrix_as_float();
```

#### `display_matrix`
Exibe a matriz carregada no console para verificação.
```cpp
void ReadCSV::display_matrix();
```

### Métodos Privados

#### `determine_dimensions_and_datatype`
Determina as dimensões da matriz e o tipo de dado (int ou float).
```cpp
void ReadCSV::determine_dimensions_and_datatype();
```

#### `allocate_matrix`
Aloca memória dinamicamente para a matriz carregada.
```cpp
void** ReadCSV::allocate_matrix(size_t element_size);
```

---

## Fluxo de Execução

1. **Inicialização**:
   - O usuário cria objetos `ReadCSV` para carregar os dados de treino e teste.
   - Os dados são convertidos para matrizes adequadas (int ou float).

2. **Treinamento**:
   - Um objeto `KNN` é criado, com `k` configurado no construtor.
   - O método `fit` é chamado para armazenar os dados de treino e seus rótulos.

3. **Classificação**:
   - O método `predict` classifica os exemplos de teste com base nos vizinhos mais próximos.

4. **Saída**:
   - As predições e a acurácia do modelo são exibidas no console.

---

Se houver dúvidas ou ajustes necessários, não hesite em entrar em contato!

