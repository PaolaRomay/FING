/* 5035742 */

#include "../include/conjunto.h"
#include "../include/avl.h"
#include "../include/iterador.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct repConjunto{
  TAvl  avl;
};

TConjunto crearConjunto(){
  TConjunto res = new repConjunto;
  res->avl = crearAvl();
  return res;
}

TConjunto singleton(nat elem){
  TConjunto res = crearConjunto();
  res->avl = insertarEnAvl(elem, res->avl);
  return res;
}

static TIterador unionIter(TIterador c1, TIterador c2){
  TIterador unionIt = crearIterador();
  c1 = reiniciarIterador(c1);
  c2 = reiniciarIterador(c2);

  while(estaDefinidaActual(c1) && estaDefinidaActual(c2)){
    if (actualEnIterador(c1) < actualEnIterador(c2)){
      unionIt = agregarAIterador(actualEnIterador(c1),unionIt);
      c1 = avanzarIterador(c1);
    }else if (actualEnIterador(c1) > actualEnIterador(c2)){
      unionIt = agregarAIterador(actualEnIterador(c2),unionIt);
      c2 = avanzarIterador(c2);
    } else if (actualEnIterador(c1) == actualEnIterador(c2)){
      unionIt = agregarAIterador(actualEnIterador(c2),unionIt);
      c2 = avanzarIterador(c2);
      c1 = avanzarIterador(c1);
    }
  }
  if (!estaDefinidaActual(c1)){
    while(estaDefinidaActual(c2)){
      unionIt = agregarAIterador(actualEnIterador(c2),unionIt);
      c2 = avanzarIterador(c2);
    }
  } else if (!estaDefinidaActual(c2)){
      while(estaDefinidaActual(c1)){
        unionIt = agregarAIterador(actualEnIterador(c1),unionIt);
        c1 = avanzarIterador(c1);
      }
    }
    liberarIterador(c1);
    liberarIterador(c2);
  return unionIt;
}

TConjunto unionDeConjuntos(TConjunto c1, TConjunto c2){ 
  if (estaVacioConjunto(c1) && (estaVacioConjunto(c2))){
    return crearConjunto();
  } 
  else{
    TIterador aux1 = iteradorDeConjunto(c1);
    TIterador aux2 = iteradorDeConjunto(c2);
    TIterador unionIt = unionIter(aux1,aux2);

    unionIt = reiniciarIterador(unionIt);

    nat tam_array = 0;
    while (estaDefinidaActual(unionIt)){
      tam_array = tam_array +1;
      unionIt = avanzarIterador(unionIt);
    }
    nat* array = new nat[tam_array];
    unionIt = reiniciarIterador(unionIt);

    for (nat i = 0; i < tam_array; i ++){
      array[i] = actualEnIterador(unionIt);
      unionIt = avanzarIterador(unionIt);
    }
    
    TConjunto res = arregloAConjunto(array,tam_array);
    liberarIterador(unionIt);
    delete [] array;
    return res;
  }
}

static TIterador difIter(TIterador c1, TIterador c2){
  TIterador difIter = crearIterador();
  c1 = reiniciarIterador(c1);
  c2 = reiniciarIterador(c2);
  bool bandera = true;

  while(estaDefinidaActual(c1)){
    while(estaDefinidaActual(c2) && bandera){
      if (actualEnIterador(c1) != actualEnIterador(c2)){
        c2 = avanzarIterador(c2);
        bandera = true;
      } else if (actualEnIterador(c1) == actualEnIterador(c2)){
        bandera = false;
      }
    }
    if (!estaDefinidaActual(c2) && bandera){
      difIter = agregarAIterador(actualEnIterador(c1),difIter);
      c1 = avanzarIterador(c1);
      c2 = reiniciarIterador(c2);
    } else if(!bandera){
      c1 = avanzarIterador(c1);
      c2 = reiniciarIterador(c2);
      bandera = true;     
    }
  }
  liberarIterador(c1);
  liberarIterador(c2);
  return difIter;
}

TConjunto diferenciaDeConjuntos(TConjunto c1, TConjunto c2){
  //if (estaVacioConjunto(c1) && (estaVacioConjunto(c2))){
    //return crearConjunto();
  //}else
   if (estaVacioConjunto(c1)){
    return crearConjunto();
  }else{
    TIterador difIt = difIter(iteradorDeConjunto(c1),iteradorDeConjunto(c2));

    difIt = reiniciarIterador(difIt);
    if (estaDefinidaActual(difIt)){ //////no se si es esta definida actual quiero q no sea null
      difIt = reiniciarIterador(difIt);
    } else {
      liberarIterador(difIt);
      return crearConjunto();
    }

    nat tam_array = 0;
    while (estaDefinidaActual(difIt)){
      tam_array = tam_array +1;
      difIt = avanzarIterador(difIt);
    }
    nat* array = new nat[tam_array];
    difIt = reiniciarIterador(difIt);

    for (nat i = 0; i < tam_array; i ++){
      array[i] = actualEnIterador(difIt);
      difIt = avanzarIterador(difIt);
    }
    TConjunto res = arregloAConjunto(array,tam_array);
    liberarIterador(difIt);
    delete [] array;
    return res;
  }
}

bool perteneceAConjunto(nat elem, TConjunto c){
  if (buscarEnAvl(elem, c->avl) != NULL)
    return true;
  else
    return false;
}

bool estaVacioConjunto(TConjunto c){
  if (c == NULL)
    return true;
  else
    return estaVacioAvl(c->avl);
}

nat cardinalidad(TConjunto c){
  return cantidadEnAvl(c->avl);
}

TConjunto arregloAConjunto(nat *elems, nat n){
  TConjunto res = new repConjunto;
  res->avl = arregloAAvl (elems, n);
  return res;
}

TIterador iteradorDeConjunto(TConjunto c){
  if (estaVacioConjunto(c))
    return crearIterador();
  else
    return enOrdenAvl(c->avl);
}

void liberarConjunto(TConjunto c){
    if (c != NULL ) {
    liberarAvl(c->avl);
    delete c;
  }
}


