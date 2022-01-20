/* 5035742 */

#include "../include/avl.h"
#include "../include/pila.h"
#include "../include/colaAvls.h"
#include "../include/iterador.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h> 
#include <stdlib.h>

struct repAvl {
  nat dato;
  nat altura;
  nat cantidad;
  TAvl izq, der;
};

TAvl crearAvl() {
  return NULL; 
}

bool estaVacioAvl(TAvl avl) {
  return (avl == NULL);
}

static nat max(nat a, nat b) {
  if (a > b)
    return a;
  else
    return b;
}

static void rotarDerecha(TAvl &z) {
  assert(z != NULL && z->izq != NULL);
  TAvl y = z->izq;
  TAvl T3 = y->der;

  y->der = z;
  z->izq = T3;

  z->altura = max(alturaDeAvl(z->izq), alturaDeAvl(z->der)) +1;
  y->altura = max(alturaDeAvl(y->izq), alturaDeAvl(y->der)) +1;
  z->cantidad = cantidadEnAvl(z); 
  y->cantidad = cantidadEnAvl(y); 

  z = y;
}

static void rotarIzquierda(TAvl &z) {
  assert(z != NULL && z->der != NULL);
  TAvl y = z->der;
  TAvl T2 = y->izq;

  y->izq = z;
  z->der = T2;

  z->altura = max(alturaDeAvl(z->izq), alturaDeAvl(z->der)) +1;
  y->altura = max(alturaDeAvl(y->izq), alturaDeAvl(y->der)) +1;
  z->cantidad = cantidadEnAvl(z); 
  y->cantidad = cantidadEnAvl(y); 

  z = y;
}

TAvl insertarEnAvl(nat elem, TAvl avl) { 
  if (avl == NULL) {
    avl = new repAvl;
    avl->dato = elem;
    avl->izq = avl->der = NULL;
    avl->altura = 1;
    avl->cantidad = 1;
  } else{
    if (elem < avl->dato) {
      avl->izq = insertarEnAvl(elem, avl->izq);
      avl->altura = max(alturaDeAvl(avl->izq), alturaDeAvl(avl->der)) +1;
      avl->cantidad = cantidadEnAvl(avl) + 1; 
      
      int FB = alturaDeAvl(avl->izq) - alturaDeAvl(avl->der);

      if (FB > 1) {
        if (alturaDeAvl(avl->izq->izq) > alturaDeAvl(avl->izq->der))
          rotarDerecha(avl);
        else {
          rotarIzquierda(avl->izq);
          rotarDerecha(avl);
        }
      }
    }
    else {
      avl->der = insertarEnAvl(elem, avl->der);
      avl->altura = max(alturaDeAvl(avl->izq), alturaDeAvl(avl->der)) +1;
      avl->cantidad = cantidadEnAvl(avl) + 1; 

      int FB = alturaDeAvl(avl->izq) - alturaDeAvl(avl->der);

      if (FB < -1){
        if (alturaDeAvl(avl->der->der) > alturaDeAvl(avl->der->izq))
          rotarIzquierda(avl);
        else {
          rotarDerecha(avl->der);
          rotarIzquierda(avl);
        }
      }
    }
  }
  return avl;
}

TAvl buscarEnAvl(nat elem, TAvl avl){
    if (avl == NULL){
    return avl;
  } else if (raizAvl(avl) == elem){
    return avl;
  } else if (raizAvl(avl) > elem){
    return buscarEnAvl(elem, izqAvl(avl));
  } else { 
    return buscarEnAvl(elem, derAvl(avl));
  }
}

nat raizAvl(TAvl avl) {
  assert(!estaVacioAvl(avl));
  return avl->dato; 
}

TAvl izqAvl(TAvl avl) {
  assert(!estaVacioAvl(avl));
  return avl->izq; 
}

TAvl derAvl(TAvl avl) {
  assert(!estaVacioAvl(avl));
  return avl->der; 
}

nat cantidadEnAvl(TAvl avl){
  if (avl == NULL)
    return 0;
  else
    return 1 + cantidadEnAvl(avl->izq) + cantidadEnAvl(avl->der);
}

nat alturaDeAvl(TAvl avl){
  nat alt = 0;
  if (avl != NULL)
    alt = avl->altura;
  return alt;
}

static TIterador auxEnOrdenAvl(TIterador arr, TAvl avl){
  if (avl != NULL){
    auxEnOrdenAvl(arr,avl->izq);
    arr = agregarAIterador(avl->dato,arr);    
    auxEnOrdenAvl(arr,avl->der);
  }
  return arr;
} 

TIterador enOrdenAvl(TAvl avl){
    TIterador arr = crearIterador();
  return auxEnOrdenAvl(arr,avl);
}

static nat auxalturaAvl(TAvl avl){
  if (avl == NULL) 
    return 0;
  else{
    nat alturaIzq = auxalturaAvl(avl->izq);
    nat alturaDer = auxalturaAvl(avl->der);
    if (alturaIzq >= alturaDer)
      return alturaIzq + 1;
    else
      return alturaDer + 1;
  }
}

static TAvl nuevoNodo(nat i){
  TAvl res = new repAvl;
  res->dato = i;
  res->izq = NULL;
  res->der = NULL;
  return res;
}

static TAvl auxarregloAAvl(nat *elems, int start, int end){
  if (start > end) 
    return NULL;
  nat mid = (start +end)/2;
  TAvl res = nuevoNodo(elems[mid]);
  res->izq = auxarregloAAvl(elems,start, mid-1);
  res->der = auxarregloAAvl(elems,mid+1, end);
  return res;
}

TAvl arregloAAvl(nat *elems, nat n){
  TAvl res;
  res = auxarregloAAvl(elems,0,n-1);
  res->altura = auxalturaAvl(res);
  res->cantidad = cantidadEnAvl(res);
  return res;
}

static TAvl auxavlmin (int h, int *cont){
  TAvl T = crearAvl();  
  if (h >= 1){
    T = new repAvl;
    T->izq = auxavlmin(h-1, cont);
    T->dato = ++*cont;
    T->altura = h;
    T->cantidad = T->cantidad+1;
    T->der = auxavlmin(h-2,cont);
    return T;
  }else
    return NULL;
}

TAvl avlMin(nat h){
  int cont = 0;
  int aux = h;
  return auxavlmin(aux,&cont);
}

void imprimirAvl(TAvl avl){
  if ( avl != NULL) {
    TAvl centinela = new repAvl;
    centinela->dato = 0;
    centinela->altura = 1;
    centinela->cantidad = 1;
    centinela->izq = centinela->der = NULL;

    TPila p = crearPila(alturaDeAvl(avl) + cantidadEnAvl(avl));
    TColaAvls q = crearColaAvls();

    q = encolar(avl, q);    
    q = encolar(centinela,q);

    while (!estaVaciaColaAvls(q)) {
      avl = frente (q);
      q = desencolar(q);
      p = apilar(avl->dato, p);
      if(avl == centinela && !estaVaciaColaAvls(q))
        q = encolar(centinela,q);
      if (avl->der != NULL)
        q = encolar(avl->der,q);
      if (avl->izq != NULL)
        q = encolar(avl->izq,q);
    }      
    liberarColaAvls(q);

    p = desapilar(p);
    while(!estaVaciaPila(p)){
      if (cima(p) == centinela->dato){
        printf("\n");
        p = desapilar(p);
      } else {
        printf("%d ", cima(p));
        p = desapilar(p);
      }
    }
    liberarAvl(centinela);
    liberarPila(p);
    printf("\n");
  }
}

void liberarAvl(TAvl avl) {
  if (avl != NULL ) {
    liberarAvl(avl->izq);
    liberarAvl(avl->der);
    delete avl;
    avl = NULL;
  }
}