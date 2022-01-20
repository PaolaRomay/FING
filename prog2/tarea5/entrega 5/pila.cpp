/* 5035742 */

#include "../include/pila.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stddef.h>

struct repPila{
  nat* array;
  nat tope;
  nat cota;
};

TPila crearPila(nat tamanio){
  assert(tamanio > 0);
  TPila p= new repPila();
  p->tope= 0;
  p->array = new nat [tamanio];
  p->cota = tamanio;
  return p;
}

TPila apilar(nat num, TPila p){
  if(!estaLlenaPila(p)){
    p->array [p->tope] = num;
    p->tope ++;
  }
  return p;
}

TPila desapilar(TPila p){
  assert(p->tope > 0);
  p->tope = (p->tope - 1);
  return p;
}

void liberarPila(TPila p){
  delete [] p->array;
  delete p;
}

bool estaVaciaPila(TPila p){
  return (p->tope == 0);
}

bool estaLlenaPila(TPila p){
  return (p->tope == p->cota);
}

nat cima(TPila p){
  assert(!estaVaciaPila(p));
  return p->array [p->tope - 1];
}