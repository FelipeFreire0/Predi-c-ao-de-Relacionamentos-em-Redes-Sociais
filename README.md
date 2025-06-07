# EP1 - Predição de Relacionamentos em Redes Socias

Este projeto implementa funções de análise de similaridade em grafos não direcionados, utilizando matriz de adjacência. O código foi desenvolvido como parte de um exercício prático da disciplina de Algoritmos e Estruturas de Dados 2.

## Estrutura do Projeto

- **EP1.c**: Arquivo principal contendo toda a implementação das funções e exemplos de uso.
- O grafo é representado por uma matriz binária de adjacências.

## Funcionalidades Implementadas

A estrutura básica do projeto já estava pronta, incluindo:
- Criação e liberação de grafos
- Inserção e remoção de arestas
- Exibição do grafo e de arranjos
- Funções auxiliares para manipulação de grafos

As seguintes funções de análise de similaridade foram implementadas neste EP:

1. **Vizinhos em Comum**  
   Calcula, para cada vértice, quantos vizinhos ele tem em comum com um vértice de referência.

2. **Coeficiente de Jaccard**  
   Mede a similaridade entre conjuntos de vizinhos de dois vértices, usando a razão entre a interseção e a união dos conjuntos.

3. **Medida Adamic-Adar**  
   Soma, para cada vizinho em comum, o inverso do logaritmo do grau do vizinho, atribuindo maior peso a vizinhos menos conectados.

4. **Alocação de Recursos**  
   Similar ao Adamic-Adar, mas soma o inverso do grau dos vizinhos em comum.

5. **Similaridade Cosseno**  
   Mede a similaridade entre os conjuntos de vizinhos de dois vértices usando o cosseno do ângulo entre seus vetores de adjacência.

6. **Coeficiente de Dice**  
   Mede a similaridade entre dois conjuntos de vizinhos, dando peso dobrado à interseção.

7. **Hub Promoted Index (HPI)**  
   Mede a similaridade entre dois vértices, promovendo o vértice com menor grau.

8. **Hub Depressed Index (HDI)**  
   Mede a similaridade entre dois vértices, promovendo o vértice com maior grau.

## Como Compilar e Executar

Compile o programa usando um compilador C, por exemplo:

```bash
gcc -o ep1 EP1.c -lm
```

Execute o programa:

```bash
./ep1
```

## Observações

- O código foi desenvolvido para fins didáticos e segue o padrão de entrada/saída especificado pelo professor.
- As funções implementadas podem ser utilizadas para análise de redes sociais, recomendação de links e outras aplicações em grafos.

Desenvolvido para a disciplina de Algoritmos e Estruturas de Dados 2.
