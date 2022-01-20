/* 5035742 */

#include "../include/usoTads.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>

static TCadena auxNivelEnBinario(nat l, TBinario b, nat cont, TCadena cad){
  if (b!=NULL){
    auxNivelEnBinario(l,izquierdo(b),cont+1,cad);
    if (l == cont)
      cad =insertarAlFinal(copiaInfo(raiz(b)),cad);
    auxNivelEnBinario(l,derecho(b),cont+1,cad);
  }
  return cad;
}

TCadena nivelEnBinario(nat l, TBinario b){
  TCadena cad = crearCadena();
  nat cont = 1;
  return auxNivelEnBinario(l,b,cont,cad);
}

bool esCamino(TCadena c, TBinario b){
  if (b == NULL && c == NULL){
    return true;
  }
  else if (b == NULL || c == NULL){
    return false;
  }
  else {
    TLocalizador loc = inicioCadena(c);
    while (loc!=NULL && b!=NULL && (natInfo(infoCadena(loc,c)) == natInfo(raiz(b)))) {
      loc= siguiente(loc,c);
      if(loc== NULL && izquierdo(b)==NULL && derecho(b)==NULL){
        return true;
      } else if (loc == NULL || (izquierdo(b)==NULL && derecho(b)==NULL)){
        return false;
      }
      if (natInfo(infoCadena(loc,c)) > natInfo(raiz(b))){
        b=derecho(b);
      }
      else
        b=izquierdo(b);
    }
  return (loc==NULL && b==NULL);
  }   
}

bool pertenece(nat elem, TCadena cad){
  return (siguienteClave(elem,inicioCadena(cad),cad) != NULL);
};

nat longitud(TCadena cad){
  nat l;
  if (esVaciaCadena(cad)) {
    l = 0;
  } else {
    nat i; i=1;
    while (kesimo(i,cad) != NULL) {
      i=i+1;  
    }
    l=i-1;
  }
  return l;
};

bool estaOrdenadaPorNaturales(TCadena cad){
  TLocalizador aux;
  bool res;
  if (esVaciaCadena(cad)){
    res = true;
  } else if (inicioCadena(cad) == finalCadena(cad)) {
    res = true;
  } else {
    aux = siguiente(inicioCadena(cad),cad);
    res = true;
    while (aux != NULL){
      if (res && natInfo(infoCadena(anterior(aux,cad),cad)) <= natInfo(infoCadena(aux,cad))) {
        res = true;
      } else {
      res = false;
      }
      aux = siguiente(aux,cad);
    }
  }
  return res;
};

bool hayNatsRepetidos(TCadena cad){
  bool res;
  if (inicioCadena(cad) == finalCadena(cad)){
    res = false;
  } else {
    TLocalizador aux;
    aux = inicioCadena(cad);
    while (aux != finalCadena(cad) && siguienteClave(natInfo(infoCadena(aux,cad)),siguiente(aux,cad),cad) == NULL){      
        aux = siguiente(aux,cad);
        res = false;    
    }
    if (aux != finalCadena(cad)){
      res = true;
    } else {
      res = false;
    }
  } 
  return res;
};

bool sonIgualesCadena(TCadena c1, TCadena c2){
  bool res;
  if (esVaciaCadena(c1) && esVaciaCadena(c2)) {
    res = true;
  } else if ((esVaciaCadena(c1) || esVaciaCadena(c2))){
    res = false;
  } else {
    TLocalizador auxc1;
    TLocalizador auxc2;
    auxc1 = inicioCadena(c1);
    auxc2 = inicioCadena(c2);
    while (auxc1 != NULL && auxc2 != NULL && sonIgualesInfo(infoCadena(auxc1,c1),infoCadena(auxc2,c2))) {
      auxc1 = siguiente (auxc1,c1);
      auxc2 = siguiente (auxc2,c2);
    }
    if (auxc1 == NULL && auxc2 == NULL) {
      res = true;
    } else {
      res = false;
    }
  }
  return res;
};

TCadena concatenar(TCadena c1, TCadena c2){
  TCadena res;
  res = copiarSegmento(inicioCadena(c1),finalCadena(c1),c1);
  res = insertarSegmentoDespues(copiarSegmento(inicioCadena(c2),finalCadena(c2),c2),finalCadena(res), res);
  return res;
};

TCadena ordenar(TCadena cad){
  assert(!hayNatsRepetidos(cad));
  if (esVaciaCadena(cad) || inicioCadena(cad) == finalCadena(cad)){
    cad = cad;
  } else {
    TLocalizador aux;
    aux = inicioCadena(cad);
    while (aux != NULL){
        intercambiar(menorEnCadena(aux,cad), aux, cad);
        aux = siguiente(aux,cad);
      }
    }
  return cad;
};

TCadena cambiarTodos(nat original, nat nuevo, TCadena cad){ 
  TLocalizador aux;
  aux = inicioCadena(cad);
    while (aux != NULL){
      if (natInfo(infoCadena(aux,cad)) == original ) {
        TInfo auxnuevo = crearInfo(nuevo,realInfo(infoCadena(aux,cad)));
        liberarInfo(infoCadena(aux,cad));
        cambiarEnCadena(auxnuevo,aux,cad);
      }
       aux = siguiente(aux,cad);
    }
  return cad;
};

TCadena subCadena(nat menor, nat mayor, TCadena cad){
  return copiarSegmento(siguienteClave(menor,inicioCadena(cad),cad),anteriorClave(mayor,finalCadena(cad),cad),cad);
};