/* Implementação Algoritmo genético para o problema das p-medianas */
/* Autor: Bruno Cesar, RA 95378, bcesar.g6@gmail.com               */
/* 13/12/17                                                        */
/*******************************************************************/
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

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
};

class Mediana{
  Vertice* m;
  vector<Vertice*> vertices;
  int custo;

public:
  int getCusto() { return custo;}

  /* Calcula o custo (distancia) do vertice associado a mediana */
  int calcCusto(int x, int y){
    int custo = 0;
    custo += abs(x - m->getX());
    custo += abs(y - m->getY());
    return custo;
  }

  bool associa(Vertice* v){
    if(m->aplicaDemanda(v->demanda())){
      vector<Vertice*>::iterator it;
      it = vertices.end();
      vertices.insert(it,v);
      custo += calcCusto(v->getX(), v->getY());
      return true;
    }
    return false;
  }

  void printMediana(){
    int i = 0;
    printf("\nMediana [%d/%d] (%d) :\n", m->getX(), m->getY(), custo);

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
  }

};

/* Variáveis globais */
static vector<Vertice*> inputVertices;
static int tam; //Número de vertices
static int p; //Número de medianas

/* Lê o problema (input passa por arquivo no stdin) */
void leInput(){
  int i,x,y,c,d;
  scanf("%d %d", &tam, &p);
  scanf("%d %d", &x,&y); // Lê dados desnecessários para descartar do stdin
  vector<Vertice*>::iterator it;

  for(i = 0; i < tam; i++){
    scanf("%d %d %d %d",&x,&y,&c,&d);
    printf("%d %d %d %d\n",x,y,c,d );
    Vertice v(x,y,c,d);
    it = inputVertices.end();
    inputVertices.insert(it,&v);
  }

  for(Vertice* vv : inputVertices){
    vv->toString();
  }
}

int main(int argc, char** argv){
  //TODO Parametrização, inicialização correta
  /* Teste básico*/
  Vertice v(10,5,400,50);
  Vertice v2(20,4,60,30);
  Vertice v3(15,7,80,40);

  Mediana m(&v);
  m.associa(&v2);
  m.associa(&v3);

  //m.printMediana();
  leInput();
  printf("Tam = %d\n %d Medianas",tam, p);


  return 0;
}
