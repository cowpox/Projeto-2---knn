
# Projeto k-NN

## Visão Geral

Este projeto implementa o algoritmo k-Nearest Neighbors (k-NN) para classificação de dados. A solução foi projetada para processar dados do tipo **inteiro (int)** e **números reais (float)** em diferentes cenários de treino e teste. O código é modular e foi desenvolvido para ser reutilizável e fácil de adaptar.

## Características

* **Flexibilidade de tipos de dados** : Suporte para matrizes de inteiros e floats.
* **Configuração de k** : Valor de kk configurável no construtor.
* **Módulos reutilizáveis** : Inclui classes auxiliares para leitura de arquivos CSV e manipulação de matrizes.
* **Testes com diferentes cenários** : Avaliação de desempenho em várias divisões de treino e teste.

## Estrutura do Projeto

* `knn.h`: Definição da classe principal KNN.
* `read_csv.h` e `read_csv.cpp`: Classe auxiliar para leitura e processamento de arquivos CSV.
* `Adriano_Brandao.cpp`: Módulo principal utilizando dados inteiros.
* `Adriano_Brandao_float.cpp`: Módulo principal utilizando dados float.
* `Resultados - tabelas e graficos.pdf`: Gráficos e tabelas de acurácia obtidos durante os testes.
* `testes.md`: Detalhamento dos cenários de teste e análises.

## Configuração do Ambiente

### Requisitos

* **Compilador C++** : Suporte a C++11 ou superior.
* **Bibliotecas** :
* `iostream`
* `fstream`
* `sstream`
* **Sistema Operacional** : Testado no Windows e Linux.

### Instalação

1. Clone este repositório:
   ```bash
   git clone https://github.com/usuario/projeto-knn.git
   ```
2. Navegue até a pasta do projeto:
   ```bash
   cd projeto-knn
   ```
3. Compile o código principal (exemplo com `g++`):
   ```bash
   g++ Adriano_Brandao.cpp -o adriano_brandao
   g++ Adriano_Brandao_float.cpp -o adriano_brandao_float
   ```

## Uso

### Executando o Modelo com Inteiros

1. Certifique-se de que os arquivos CSV estão na pasta `tables`.
2. Execute o binário:
   ```bash
   ./adriano_brandao
   ```
3. Verifique os resultados exibidos no console.

### Executando o Modelo com Floats

1. Certifique-se de que os arquivos CSV estão na pasta `tables`.
2. Execute o binário:
   ```bash
   ./adriano_brandao_float
   ```
3. Verifique os resultados exibidos no console.

## Estrutura dos Arquivos CSV

* **Formato esperado** :
* Arquivos `features`: Matrizes bidimensionais com valores numéricos.
* Arquivos `labels`: Vetores unidimensionais com classes correspondentes.
* **Exemplo** :

```csv
  1.0, 2.0, 3.0
  4.0, 5.0, 6.0
  7.0, 8.0, 9.0
```

## Testes e Resultados

Resultados detalhados de acurácia para diferentes valores de kk e cenários de teste estão em `Resultados - tabelas e graficos.pdf` e `testes.md`.

## Licença

Este projeto é licenciado sob a Licença MIT. Consulte o arquivo LICENSE para mais detalhes.
