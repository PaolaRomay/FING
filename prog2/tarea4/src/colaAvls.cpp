/* 5035742 */

#include "../include/colaAvls.h"
#include "../include/avl.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stddef.h>

struct nodo{
  TAvl elem;
  nodo * sig;
};

struct repColaAvls{
  nodo *primero, *ultimo;
};

TColaAvls crearColaAvls(){ 
  TColaAvls res = new repColaAvls;
  res->primero = res->ultimo = NULL;
  return res;
}

TColaAvls encolar(TAvl avl, TColaAvls c){
  nodo *navl = new nodo;
  navl->elem = avl;
  navl->sig = NULL;
  if (c->primero == NULL) {
    c->primero = navl;
  } else {
    c->ultimo->sig = navl;
  }
  c->ultimo = navl;
  return c;
}

TColaAvls desencolar(TColaAvls c){
  if (!estaVaciaColaAvls(c)) {
      nodo *aux = c->primero;
      c->primero = c->primero->sig;
      if (c->primero == NULL)
        c->ultimo = NULL;
      delete aux;
   }
  return c;
}

void liberarColaAvls(TColaAvls c){
  nodo *aux;
  while(c->primero != NULL){
    aux = c->primero;
    c->primero = c->primero->sig;
    delete aux;
  }
  delete c;
}

bool estaVaciaColaAvls(TColaAvls c){
  return c->primero == NULL;
}

TAvl frente(TColaAvls c){
  assert(!estaVaciaColaAvls(c));
  return c->primero->elem;
}
