/*********************************************************************/
/**   ACH2024 - Algoritmos e Estruturas de Dados II                 **/
/**   EACH-USP - Primeiro Semestre de 2024                          **/
/**   Turma 04 - Prof. Luciano Digiampietri                         **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   <Felipe Freire Silva>                   <14749596>            **/
/**                                                                 **/
/*********************************************************************/

// gcc completeERenomeie.c -lm

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int bool;

/* Estrutura para representar nosso grafo usando matriz binaria de adjacencias 
 */
typedef struct {
  int numVertices;
  int numArestas;
  bool **matriz;
} Grafo;

/* Funcao auxiliar para o sistema de correcao automatica (nao mexer) */
void printf123() {
  // Funcao usada pelo sistema de correcao automatica (nao mexer)
}

/* Funcao que inicializa o grafo cujo endereco foi passado como parametro.
   Isto e, cria a matriz de adjacencias (preenchida com false),
   e atribui valor para numVertices (recebendo o valor passado por parametro)
   e numArestas igual a zero.
*/
bool inicializaGrafo(Grafo *g, int vertices) {
  if (g == NULL || vertices < 1)
    return false;
  g->numVertices = vertices;
  g->numArestas = 0;
  int x, y;
  g->matriz = (bool **)malloc(sizeof(bool *) * vertices);
  for (x = 0; x < vertices; x++) {
    g->matriz[x] = (bool *)malloc(sizeof(bool) * vertices);
    for (y = 0; y < vertices; y++) {
      g->matriz[x][y] = false;
    }
  }
  return true;
}

/* Funcao que libera a memoria da matriz de adjacencia do grafo cujo endereco
   foi passado como parametro. */
bool liberaGrafo(Grafo *g) {
  if (g == NULL)
    return false;
  int x;
  for (x = 0; x < g->numVertices; x++)
    free(g->matriz[x]);
  free(g->matriz);
  g->numVertices = 0;
  g->numArestas = 0;
  g->matriz = NULL;
  return true;
}

/* Funcao que retorna o numero de vertices do grafo apontado por g, caso o
   endereco armazenado em g seja diferente de NULL. Caso contrario, retorna -1.
*/
int numeroDeVertices(Grafo *g) {
  if (g != NULL)
    return g->numVertices;
  else
    return -1;
}

/* Funcao que retorna o numero de arestas do grafo apontado por g, caso o
   endereco armazenado em g seja diferente de NULL. Caso contrario, retorna -1.
*/
int numeroDeArestas(Grafo *g) {
  if (g != NULL)
    return g->numArestas;
  else
    return -1;
}

/* Funcao que retorna o grau do vertice v, caso ele exista.
   Caso contrario, retorna -1.
*/
int retornaGrauDoVertice(Grafo *g, int v) {
  if (!g || v < 0 || v >= g->numVertices)
    return -1;
  int x, grau = 0;
  for (x = 0; x < g->numVertices; x++) {
    if (g->matriz[v][x])
      grau++;
  }
  return grau;
}

/* Funcao que retorna true se o vertice v possui um ou mais
   vertices adjacentes (vizinhos).
*/
bool possuiVizinhos(Grafo *g, int v) {
  if (!g || v < 0 || v >= g->numVertices)
    return false;
  int x;
  for (x = 0; x < g->numVertices; x++)
    if (g->matriz[v][x])
      return true;
  return false;
}

/* Funcao que insere uma nova aresta no grafo.
   Se os vertices passados como parametro forem validos, ha duas possibilidades:
   - a aresta nao existia;
   - a aresta existia.
*/
bool insereAresta(Grafo *g, int v1, int v2) {
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices ||
      v1 == v2)
    return false;
  if (g->matriz[v1][v2] == false) {
    g->matriz[v1][v2] = true;
    g->matriz[v2][v1] = true;
    g->numArestas++;
  }
  return true;
}

/* Funcao que exclui a aresta entre v1 e v2 (caso exista uma aresta valida
   entre v1 e v2) e retorna true; ou retorna false, caso contrario.
*/
bool removeAresta(Grafo *g, int v1, int v2) {
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices ||
      g->matriz[v1][v2] == false)
    return false;
  g->matriz[v1][v2] = false;
  g->matriz[v2][v1] = false;
  g->numArestas--;
  return true;
}

/* Funcao que retorna true se existe uma aresta valida entre v1 e v2
   e false caso contrario.
*/
bool arestaExiste(Grafo *g, int v1, int v2) {
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices ||
      g->matriz[v1][v2] == false)
    return false;
  return true;
}

/* Funcao que cria um grafo com o numero de vertices e
   numero de arestas passados como parametro e retorna seu endereco.
*/
Grafo *criaGrafoAleatorio(int numVertices, int numArestas) {
  printf("################# Criando grafo com %i vertice(s) e com %i "
         "aresta(s). #################\n",
         numVertices, numArestas);
  int x, y, a = 0;
  if (numVertices < 1 || numArestas >= numVertices * (numVertices - 1) / 2) {
    printf("Parametros invalidos, o grafo nao sera gerado.\n");
    return NULL;
  }
  Grafo *g = (Grafo *)malloc(sizeof(Grafo));
  inicializaGrafo(g, numVertices);
  while (a < numArestas) {
    x = rand() % numVertices;
    y = rand() % numVertices;
    if (x != y && g->matriz[x][y] == false) {
      g->matriz[x][y] = true;
      g->matriz[y][x] = true;
      a++;
    }
  }
  g->numArestas = numArestas;
  return g;
}

/* Funcao desenvolvida para exibir um grafo, no formato de uma matriz
   de adjacencia.
*/
void exibeGrafo(Grafo *g) {
  if (!g)
    return;
  int x, y;
  printf("\nImprimindo grafo (vertices: %i; arestas: %i).\n   ", g->numVertices,
         g->numArestas);
  for (x = 0; x < g->numVertices; x++)
    printf(" %3i", x);
  printf("\n");
  for (x = 0; x < g->numVertices; x++) {
    printf("%3i", x);
    for (y = 0; y < g->numVertices; y++)
      printf(" %3i", g->matriz[x][y]);
    printf("\n");
  }
  printf("\n");
}

/* Funcao que exibe os valores de um arranjo de numeros reais */
void exibeArranjoReais(float *arranjo, int n) {
  int x;
  for (x = 0; x < n; x++)
    printf("  v%i\t", x);
  printf("\n");
  for (x = 0; x < n; x++) {
    printf("%3.2f\t", arranjo[x]);
  }
  printf("\n\n");
}

/* Funcao que exibe os valores de um arranjo de numeros inteiros */
void exibeArranjoInteiros(int *arranjo, int n) {
  int x;
  for (x = 0; x < n; x++)
    printf(" v%i\t", x);
  printf("\n");
  for (x = 0; x < n; x++) {
    printf("%3i\t", arranjo[x]);
  }
  printf("\n\n");
}

/* FUNCOES QUE DEVEM SER COMPLETADAS PARA RESOLVER O EP.
   A DESCRICAO DE CADA FUNCAO ESTA NO ENUNCIADO DO EP.
   www.each.usp.br/digiampietri/ACH2024/ep1/ep1.pdf        */

/* Vizinhos em Comum */
void vizinhosEmComum(Grafo *g, int v, int *vizinhos) {
  /* loop que passa por todos os vetores,loop que passa por todas as arestas,
  Verifica se v e v1 possuem vizinhosem comum, caso verdade add 1 */
  vizinhos[v]=0;
  for(int v1=0; v1<g->numVertices; v1++){
    vizinhos[v1]=0;
    for(int x=0; x<g->numVertices; x++){
      if(g->matriz[v][x]==1)
      if(g->matriz[v1][x]==1)
        vizinhos[v1]++;
    }
  }
}

/* Coeficiente de Jaccard */
void coeficienteDeJaccard(Grafo *g, int v, float *coeficientes) {
  /* loop que passa por todos os vetores, loop que passa por todas as arestas,
  Verifica se o vetor escolhido como parâmetro possui vizinhos,Verifica se v1 possui vizinhos além dos em comum com v, Calcula o coeficiente de Jaccard caso o denominador seja positivo*/
  for(int v1=0; v1<g->numVertices; v1++){
    float intersecao=0, uniao=0;
    for(int x=0; x<g->numVertices; x++){
      if(g->matriz[v][x]==1){
        uniao++;
      }
      if(g->matriz[v1][x]==1 && g->matriz[v][x]==1){
        intersecao++; 
      }
      if(g->matriz[v1][x]==1 && g->matriz[v][x]==0){
        uniao++;
      }
      if(uniao > 0)
        coeficientes[v1]=(float) intersecao / (float) uniao;
      else{
        coeficientes[v1] = -1;
      }
    }
  }
}

/* Medida Adamic Adar */
void AdamicAdar(Grafo *g, int v, float *coeficientes) {
  /*  loop que passa pelos vetores do grafo, zera o arranjo após passar por todas
  as arrestas, loop arrestas, verifica se são vizinhos, aplica a fórmula se há intersecção e soma em relação a cada um dos vértices do grafo */
  for (int v1 = 0; v1 < g->numVertices; v1++) {
    coeficientes[v1] = 0.0;
    for (int x = 0; x < g->numVertices; x++) {
      if (g->matriz[v][x] == 1 && g->matriz[v1][x] == 1) {
        coeficientes[v1] += 1.0 / log(retornaGrauDoVertice(g, x));
      }
    }
  }
}

/* Alocacao de Recursos */
void alocacaoDeRecursos(Grafo *g, int v, float *coeficientes) {
  /*   aqui não usa log, de resto esta função exerce o mesmo que a de cima
  */
  for (int v1 = 0; v1 < g->numVertices; v1++) {
    coeficientes[v1] = 0.0;
    for (int x = 0; x < g->numVertices; x++) {
      if (g->matriz[v][x] == 1 && g->matriz[v1][x] == 1) {
        coeficientes[v1] += 1.0 / retornaGrauDoVertice(g, x);
      }
    }
  }
}

/* Similaridade Cosseno */
void similaridadeCosseno(Grafo *g, int v, float *coeficientes) {
  /* 
  passa pelos vértices, passa peloas arrestas, verifica se há intersecção e vizinhos, se x1 e y positivos aplica a fórmula
  */
  for (int v1 = 0; v1 < g->numVertices; v1++) {
    float i = 0.0, x1 = 0.0, y = 0.0;
    for (int x = 0; x < g->numVertices; x++) {
      if (g->matriz[v][x] == 1 && g->matriz[v1][x] == 1) {
        i++;
      }
      if (g->matriz[v][x] == 1) {
        x1++;
      }
      if (g->matriz[v1][x] == 1) {
        y++;
      }
    }
    if(x1 > 0 && y > 0)
      coeficientes[v1]= i / sqrt(x1 * y);
      else{
        coeficientes[v1] = -1;
      }
  } 
}

/* Coeficiente de Dice */
void coeficienteDeDice(Grafo *g, int v, float *coeficientes) {
/* igual a função acima, muda a fórmula no final
  */
  for (int v1 = 0; v1 < g->numVertices; v1++) {
    float i = 0.0, x1 = 0.0, y = 0.0;
    for (int x = 0; x < g->numVertices; x++) {
      if (g->matriz[v][x] == 1 && g->matriz[v1][x] == 1) {
        i++;
      }
      if (g->matriz[v][x] == 1) {
        x1++;
      }
      if (g->matriz[v1][x] == 1) {
        y++;
      }
    }
    if(x1+y > 0)
      coeficientes[v1]= (2 * i) / (x1 + y);
      else{
        coeficientes[v1] = -1;
      }
  }
}

/* Hub Promoted Index */
void HPI(Grafo *g, int v, float *coeficientes) {
  /* passa pelos vértices, passa peloas arrestas, verifica se há intersecção e vizinhos,
utiliza o que possui menos vizinhos na fórmula */ 
  for (int v1 = 0; v1 < g->numVertices; v1++) {
    float i = 0.0, x1 = 0.0, y = 0.0;
    for (int x = 0; x < g->numVertices; x++) {
      if (g->matriz[v][x] == 1 && g->matriz[v1][x] == 1) {
        i++;
      }
      if (g->matriz[v][x] == 1) {
        x1++;
      }
      if (g->matriz[v1][x] == 1) {
        y++;
      }
    }
    if(x1<0 || x1==0 || y<0 || y == 0)
      coeficientes[v1] = -1;
    if(x1>=y && y > 0)
      coeficientes[v1] = i / y;
    if(y>x1 || x1 == y && x1 > 0)
      coeficientes[v1] = i / x1;
  }
}

/* Hub Depressed Index */
void HDI(Grafo *g, int v, float *coeficientes) {
  /* passa pelos vértices, passa peloas arrestas, verifica se há intersecção e vizinhos,
utiliza o que possui mais vizinhos na fórmula*/
  for (int v1 = 0; v1 < g->numVertices; v1++) {
    float i = 0.0, x1 = 0.0, y = 0.0;
    for (int x = 0; x < g->numVertices; x++) {
      if (g->matriz[v][x] == 1 && g->matriz[v1][x] == 1) {
        i++;
      }
      if (g->matriz[v][x] == 1) {
        x1++;
      }
      if (g->matriz[v1][x] == 1) {
        y++;
      }
    }  
    if(x1<0 || y<0 && x1==0 || y==0)
      coeficientes[v1] = -1;
    if(x1>=y && x1 > 0)
      coeficientes[v1] = i / x1;
    if(y>x1 || x1 == y && y > 0)
      coeficientes[v1] = i / y;
  }
}