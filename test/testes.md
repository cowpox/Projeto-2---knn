# Documentação dos Testes do Projeto k-NN

## Introdução

Este documento detalha os testes realizados no projeto de implementação do método k-Nearest Neighbors (k-NN). Os testes foram conduzidos com duas versões de datasets: uma contendo valores inteiros e outra contendo valores floats. Diferentes cenários de treino e teste foram considerados para avaliar o desempenho do modelo.

---

## Datasets Utilizados

1. **int_dataset_full.csv**: Contém 891 elementos, sendo:

   - 713 para treino.
   - 178 para teste.
2. **float_dataset_full.csv**: Contém 891 elementos, sendo:

   - 712 para treino.
   - 179 para teste.

---

## Cenários de Teste

Os testes foram realizados considerando os seguintes cenários:

### Cenário 1

- **Treino**: Contém todos os elementos do dataset (inclusive os de teste).
- **Teste**: Contém 100% dos elementos de teste.

### Cenário 2

- **Treino**: Contém todos os elementos do dataset (inclusive os de teste).
- **Teste**: Contém apenas 20% dos elementos de teste.

### Cenário 3

- **Treino**: Contém apenas os elementos de treino (excluindo os de teste).
- **Teste**: Contém 100% dos elementos de teste.

### Cenário 4

- **Treino**: Contém apenas os elementos de treino (excluindo os de teste).
- **Teste**: Contém apenas 20% dos elementos de teste.

---

## Configurações dos Testes

- Valores de \( k \): Variaram de 1 a 10.
- Métrica avaliada: **Acurácia**.

---

## Resultados Obtidos

### Dataset Inteiros

- **Cenário 1**: Melhor desempenho com \( k=1 \) (86,5%) e queda progressiva com \( k \) crescente.
- **Cenário 2**: Melhor desempenho geral (91,4% com \( k=1 \)) entre todos os cenários.
- **Cenário 3**: Desempenho inicial mais baixo (60,1% com \( k=1 \)), melhorando com \( k \) crescente.
- **Cenário 4**: Desempenho intermediário, com 51,4% (\( k=1 \)) a 62,9% (\( k=8 \)).

### Dataset Floats

- **Cenário 1**: Melhor desempenho com \( k=1 \) (96,1%) e queda progressiva com \( k \) crescente.
- **Cenário 2**: Ótimo desempenho inicial (94,3% com \( k=1 \)), mas decaindo mais acentuadamente.
- **Cenário 3**: Desempenho inicial (66,5%) foi maior que nos inteiros, mas estabilizou em torno de 66%.
- **Cenário 4**: Valores iniciais elevados (65,7% com \( k=1 \)), mas queda significativa com \( k \) crescente.

---

## Análise e Conclusões

1. **Impacto de \( k \)**:

   - Valores baixos de \( k \) (\( k=1 \) e \( k=2 \)) apresentaram melhor desempenho na maioria dos cenários.
   - Valores altos de \( k \) foram mais robustos em cenários onde o treino não incluía dados de teste.
2. **Impacto do Cenário**:

   - Cenários com treino completo (1 e 2) tiveram desempenho superior.
   - Reduzir o tamanho do conjunto de teste (Cenários 2 e 4) melhorou a acurácia.
3. **Inteiros vs Floats**:

   - Datasets de floats apresentaram melhor acurácia inicial (\( k=1 \)), possivelmente devido à maior granularidade dos dados.
   - Inteiros foram mais consistentes em cenários com valores altos de \( k \).

---

## Conclusão

Os testes confirmaram a eficácia do método k-NN para diferentes configurações de treino e teste, destacando o impacto do valor de \( k \) e da composição dos conjuntos. Datasets floats tendem a oferecer melhor precisão inicial, enquanto datasets inteiros são mais estáveis em cenários desafiadores.
