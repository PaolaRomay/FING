/* 5035742 */

#include "../include/mapping.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/cadena.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodo {
  TInfo dato;
  TLocalizador anterior;
  TLocalizador siguiente;
};

struct repMap{
  TCadena *hash;
  nat M;
  nat cant;
};

typedef repMap *TMapping;

TMapping crearMap(nat M){
 TMapping t = new repMap;
 t->hash = new TCadena[M];
  for (nat i = 0; i<M; i++){
    t->hash[i] = crearCadena();
  }
  t->M = M;
  t->cant = 0;
  return t;
}

TMapping asociarEnMap(nat clave, double valor, TMapping map){
  assert(!estaLlenoMap(map) && !existeAsociacionEnMap(clave, map));
  nat pos = clave % map->M;

  TInfo dato = crearInfo(clave,valor);

  if (esVaciaCadena(map->hash[pos])){
    map->hash[pos] = insertarAlFinal(dato,map->hash[pos]);
  } else {
    map->hash[pos]= insertarAntes(dato,inicioCadena(map->hash[pos]),map->hash[pos]);
  }
  map->cant = map->cant +1;
  return map;
}

TMapping desasociarEnMap(nat clave, TMapping map){
  assert(existeAsociacionEnMap(clave,map));
  nat pos = clave % map->M;

  TLocalizador aux = siguienteClave(clave, inicioCadena(map->hash[pos]), map->hash[pos]);
  map->hash[pos] = removerDeCadena(aux,map->hash[pos]);
  map->cant = map->cant -1;
  return map;
}

bool existeAsociacionEnMap(nat clave, TMapping map){
  nat pos = clave % map->M;

  TLocalizador aux = siguienteClave(clave, inicioCadena(map->hash[pos]), map->hash[pos]);
  if (aux != NULL)
    return true;
  else
    return false;
}

double valorEnMap(nat clave, TMapping map){
  assert(existeAsociacionEnMap(clave, map));
  nat pos = clave % map->M;
  TLocalizador aux = siguienteClave(clave, inicioCadena(map->hash[pos]), map->hash[pos]);
  return realInfo(infoCadena(aux,map->hash[pos]));
}

bool estaLlenoMap(TMapping map){
  return map->cant == map->M;
}

void liberarMap(TMapping map){
  for (nat i = 0; i < map->M; i++){
    liberarCadena(map->hash[i]);
  } 
  delete[] map->hash;
  delete map;
}