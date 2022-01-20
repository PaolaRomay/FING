/* 5035742 */

#include "../include/iterador.h"
#include "../include/mapping.h"
#include "../include/avl.h"
#include "../include/utils.h"
#include "../include/grafo.h"

#include <assert.h>
#include <stdio.h> 
#include <stdlib.h>

struct repGrafo{
  TMapping aristas;
  TAvl *vertices;
  nat cantVertices;
};

typedef repGrafo *TGrafo;

TGrafo crearGrafo(nat N, nat M){
  TGrafo grafo = new repGrafo;
  grafo->vertices = new TAvl[N+1];
  for (nat i = 0; i<N+1; i++){
    grafo->vertices[i] = crearAvl();
  }
  grafo->aristas = crearMap(M);
  grafo->cantVertices = N;
  return grafo; 
}

nat cantidadVertices(TGrafo g){
  return g->cantVertices;
}

bool hayMParejas(TGrafo g){
  return estaLlenoMap(g->aristas);
}

nat min(nat val1, nat val2){
  if (val1 > val2)
    return val2;
  else
    return val1;
}

nat max(nat val1, nat val2){
  if (val1 > val2)
    return val1;
  else
    return val2;
}

TGrafo hacerVecinos(nat v1, nat v2, double d, TGrafo g){
  assert(1 <= v1 && v2 <= g->cantVertices);
  assert(v1 != v2);
  assert(!sonVecinos(v1, v2, g));
  assert(!hayMParejas(g));
  assert(d >= 0);

  nat numParVertices = (min(v1,v2)-1) * g->cantVertices + (max(v1,v2)-1);

  g->aristas = asociarEnMap(numParVertices, d, g->aristas);
  g->vertices[v1] = insertarEnAvl(v2, g->vertices[v1]);
  g->vertices[v2] = insertarEnAvl(v1, g->vertices[v2]);
  return g;
}

bool sonVecinos(nat v1, nat v2, TGrafo g){
  assert(1 <= v1 && v2 <= g->cantVertices);
  nat numParVertices = (min(v1,v2)-1) * g->cantVertices + (max(v1,v2)-1);
  return existeAsociacionEnMap(numParVertices,g->aristas);
}

double distancia(nat v1, nat v2, TGrafo g){
  assert(1 <= v1 && v2 <= g->cantVertices);
  nat numParVertices = (min(v1,v2)-1) * g->cantVertices + (max(v1,v2)-1);
  return valorEnMap(numParVertices,g->aristas);
}

TIterador vecinos(nat v, TGrafo g){
  assert(1 <= v && v <= g->cantVertices);
  TIterador res = enOrdenAvl(g->vertices[v]);
  return res;
}

void liberarGrafo(TGrafo g){
  for (nat i = 0; i <= g->cantVertices; i++){
    if (g->vertices[i] != NULL){
      liberarAvl(g->vertices[i]);
    }
  }
  liberarMap(g->aristas);
  delete [] g->vertices;
  delete g;
}
