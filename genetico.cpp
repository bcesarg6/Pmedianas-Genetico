/* Implementação Algoritmo genético para o problema das p-medianas */
/* Autor: Bruno Cesar, RA 95378, bcesar.g6@gmail.com               */
/* 13/12/17                                                        */
/*******************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

/* Header das funções */

/* Classes da estrutura */
class Vertice{
  int x; //Posição X
  int y; //Posição Y
  int c; //Capacidade
  int d; //Demanda

 public:
  int getX() {return x;}
  int getY() {return y;}
  int capacidade() {return c;}
  int demanda() {return d;}

  bool aplicaDemanda(int demanda){
    if(c - demanda >= 0){
      c = c - demanda;
      return true;
    }

    return false;
  }

  void toString(){
    printf("[%d/%d] : (%d) %d\n", x, y, d, c);
  }

  /* Construtor do vertice */
  Vertice(int nx, int ny,int nc,int nd){
    x = nx;
    y = ny;
    c = nc;
    d = nd;
  }

  /* Construtor cópia */
  Vertice(Vertice* nv){
    x = nv->getX();
    y = nv->getY();
    c = nv->capacidade();
    d = nv->demanda();
  }
};

class Mediana{
  Vertice* m;
  vector<Vertice*> vertices;
  int custo;

public:
  int getCusto() { return custo;}
  vector<Vertice*> getVertices(){ return vertices; }
  int capacidade() {return m->capacidade();}

  /* Calcula o custo (distancia) do vertice associado a mediana */
  int calcCusto(int x, int y){
    int custo = 0;
    custo += abs(x - m->getX());
    custo += abs(y - m->getY());
    return custo;
  }

  bool associa(Vertice* v){
    if(m->aplicaDemanda(v->demanda())){
      vertices.push_back(v);
      custo += calcCusto(v->getX(), v->getY());
      return true;
    }
    printf("Tentando enfiar %d no espaço %d\n",v->demanda(), m->capacidade());
    return false;
  }

  /* Printa a mediana o vertices associados a ela */
  void printMediana(){
    int i = 0;
    printf("\nMediana [%d/%d] (%d) : custo = %d\n", m->getX(), m->getY(), m->capacidade(), custo);

    for(Vertice* v : vertices){
      i++;
      printf("\t%d - ", i);
      v->toString();
    }

    printf("\n");
  }

  /* Construtor */
  Mediana(Vertice* v){
    m = v;
    custo = 0;
    m->aplicaDemanda(v->demanda());
  }
};

class Solution{
  int custoTotal;
  vector<Mediana*> medianas;

public:
  vector<Mediana*> getMedianas(){ return medianas; }
  int getTotal(){ return custoTotal;}

  void printCusto(){
    printf("Custo total = %d\n", custoTotal);
  }

  void printSolution(){
    printf("Custo total = %d\n", custoTotal);
    for(Mediana* m : medianas){
      m->printMediana();
    }
  }

  Solution(vector<Mediana*> ms){
    medianas = ms;
    custoTotal = 0;

    for(Mediana* m : medianas){
        custoTotal += m->getCusto();
    }
  }
};

/* Variáveis globais */
static vector<Vertice*> inputVertices;
static int tam; //Número de vertices
static int p; //Número de medianas
static int n; //Número de soluções da população
vector<Solution*> populacao; //População atual

/* Lê o problema (input passa por arquivo no stdin) */
void leInput(){
  int i,x,y,c,d;
  scanf("%d %d", &tam, &p);
  scanf("%d %d", &x,&y); // Lê dados desnecessários para descartar do stdin

  for(i = 0; i < tam; i++){
    scanf("%d %d %d %d",&x,&y,&c,&d);
    inputVertices.push_back(new Vertice(x,y,c,d));
  }
}

/* Copia vertices de src -> dest */
void copiaVertices(vector<Vertice*> *src, vector<Vertice*> *dest){
  for(Vertice* v : *src){
    dest->push_back(new Vertice(v));
  }
}

/* Cria a população inicial */
Solution* criaSolInicial(){
  int i, pos = 0;
  i = p;

  vector<Vertice*> auxVertices;
  vector<Mediana*> medianas;

  copiaVertices(&inputVertices, &auxVertices);

  /* Aleatoriza a ordem no vetor de vértices */
  random_shuffle(auxVertices.begin(), auxVertices.end());

  /* Os 10 primeiros se tornam as medianas */
  for(i = 0; i < p; i++){
    medianas.push_back(new Mediana(auxVertices[i]));
  }

  /* Associa os demais vertices as medianas */
  while(i < tam){
    if(medianas[pos]->associa(auxVertices[i])){
      i++;
    }
    //printf("pos = %d\n",pos );

    pos++;
    if(pos >= p) pos = 0;
  }

  return new Solution(medianas);
}

/* Inicialização das estruturas de dados */
void inicializa(long int seed){
  printf("***Algoritmo genético : P-medianas ***\n|Execução iniciada\n");

  if(seed <= 0){
    seed = time(0);
    printf("|Seed gerada pelo time(0): %ld\n", seed);
  } else{
    printf("|Seed passada como entrada: %ld\n", seed);
  }

  srand(seed);

  leInput();

  printf("\n");
}

int main(int argc, char** argv){
  //TODO Parametrização, inicialização correta
  int i;

  n = atoi(argv[1]);
  long int seed = atol(argv[2]);

  if( n <= 0 ){
    printf("Parametros errados\n");
    return 0;
  }

  inicializa(seed);

  for(i = 0; i < n; i++){
    populacao.push_back(criaSolInicial());
    populacao[i]->printCusto();

  }

  return 0;
}
