# Manual do Usuário - Projeto k-NN

## Introdução

Bem-vindo ao manual do usuário do projeto k-NN! Este documento tem como objetivo orientar o uso do sistema de classificação baseado no algoritmo k-Nearest Neighbors (k-NN). O sistema permite processar dados inteiros ou reais para realizar classificação e avaliar o desempenho do modelo.

---

## Requisitos do Sistema

* **Compilador C++** : Suporte a C++11 ou superior.
* **Sistema Operacional** : Windows ou Linux.
* **Arquivos de Dados** : Os arquivos de entrada devem estar no formato CSV e seguir o padrão descrito na seção "Estrutura dos Dados".

---

## Instruções de Instalação

1. **Baixe o repositório** :

* Use o comando:
  ```bash
  git clone https://github.com/usuario/projeto-knn.git
  ```

1. **Compile os arquivos** :

* Entre na pasta do projeto:
  ```bash
  cd projeto-knn
  ```
* Compile os módulos principais:
  ```bash
  g++ Adriano_Brandao.cpp -o adriano_brandao
  g++ Adriano_Brandao_float.cpp -o adriano_brandao_float
  ```

1. **Verifique os arquivos CSV** :

* Certifique-se de que os arquivos de dados estão localizados na pasta `tables`.

---

## Estrutura dos Dados

Os arquivos CSV devem seguir estas especificações:

* **Formato dos arquivos** :
* **`features`** : Cada linha representa um exemplo e cada coluna uma característica.
* **`labels`** : Arquivo unidimensional contendo as classes de cada exemplo.
* **Exemplo de arquivo `features`** :

```csv
  1.0, 2.0, 3.0
  4.0, 5.0, 6.0
  7.0, 8.0, 9.0
```

* **Exemplo de arquivo `labels`** :

```csv
  1
  0
  1
```

Certifique-se de que os arquivos `features` e `labels` correspondem ao mesmo conjunto de dados.

---

## Uso do Módulo `ReadCSV`

O módulo `ReadCSV` é responsável por carregar os dados de arquivos CSV e convertê-los para matrizes utilizáveis pelo modelo k-NN.

### Construtores

1. **Construtor padrão** :

* Inicializa um objeto `ReadCSV` com valores padrão para os parâmetros.

```cpp
   ReadCSV csv;
```

1. **Construtor parametrizado** :

* Permite configurar os seguintes parâmetros:
  * `filename` (string): Caminho para o arquivo CSV.
  * `sep` (char): Separador dos campos (ex.: `,` ou `;`).
  * `header` (bool): Indica se o arquivo possui cabeçalho.
  * `skip_rows` (int): Quantidade de linhas a serem ignoradas no início do arquivo.
  * `skip_cols` (int): Quantidade de colunas a serem ignoradas no início de cada linha.
  * `max_rows` (int): Limite máximo de linhas a serem lidas.
  * `max_cols` (int): Limite máximo de colunas a serem lidas.

   Exemplo:

```cpp
   ReadCSV csv("tables/int_treino.csv", ',', true, 0, 0, 1000, 10);
```

### Métodos Principais

1. **`read_file`** :

* Realiza a leitura do arquivo CSV e aloca os dados em uma matriz.

```cpp
   csv.read_file();
```

1. **`get_matrix_as_int` e `get_matrix_as_float`** :

* Retornam a matriz de dados carregada, convertida para `int` ou `float`.

```cpp
   int** matriz_int = csv.get_matrix_as_int();
   float** matriz_float = csv.get_matrix_as_float();
```

1. **`display_matrix`** :

* Exibe os dados da matriz carregada no console.

```cpp
   csv.display_matrix();
```

1. **Getters** :

* `getN_rows`: Retorna o número de linhas da matriz carregada.
* `getN_cols`: Retorna o número de colunas da matriz carregada.

---

## Executando o Sistema

### Modelo com Inteiros

1. **Configuração** :

* Certifique-se de que os arquivos CSV para inteiros estão no formato correto e localizados na pasta `tables`.

1. **Execução** :

* Execute o comando:
  ```bash
  ./adriano_brandao
  ```

1. **Saída** :

* O console exibirá as matrizes lidas, as predições realizadas e a acurácia do modelo.

### Modelo com Floats

1. **Configuração** :

* Certifique-se de que os arquivos CSV para floats estão no formato correto e localizados na pasta `tables`.

1. **Execução** :

* Execute o comando:
  ```bash
  ./adriano_brandao_float
  ```

1. **Saída** :

* O console exibirá as matrizes lidas, as predições realizadas e a acurácia do modelo.

---

## Personalizações

### Alterando o Valor de kk

1. No arquivo principal (ex.: `Adriano_Brandao.cpp`), altere o valor de kk na inicialização da classe `KNN`:
   ```cpp
   KNN knn(3);  // Define k como 3
   ```
2. Recompile o programa:
   ```bash
   g++ Adriano_Brandao.cpp -o adriano_brandao
   ```

### Adicionando Novos Dados

1. Adicione seus arquivos CSV na pasta `tables`.
2. Atualize os nomes dos arquivos no código principal, se necessário.
   ```cpp
   ReadCSV treino("tables/novo_treino.csv", ',', true, 0, 0, 1000, 10);
   ```
3. Recompile o programa.

---

## Resolução de Problemas

* **Erro: "Arquivo não encontrado"** :
* Verifique se o caminho do arquivo está correto.
* Certifique-se de que os arquivos estão localizados na pasta `tables`.
* **Resultados inesperados** :
* Verifique se os arquivos de treino e teste possuem as mesmas dimensões.
* Certifique-se de que o valor de kk é apropriado para o tamanho do dataset.

---

## Contato

Para dúvidas ou problemas, entre em contato pelo e-mail: [adrianobrandao@uel.br]().

Obrigado por utilizar o sistema k-NN!
