/* 5035742 */

#include "../include/colaDePrioridad.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct Dato{
  nat elem;
  double valor;
};

struct repCP{
  Dato *heap;
  nat tope;
  nat capacidad;
  nat *posiciones;
};

TColaDePrioridad crearCP(nat N){
  assert(N > 0);
  TColaDePrioridad cp = new repCP;
  cp->heap = new Dato[N+1];
  cp->posiciones = new nat[N+1];
  cp->tope = 0;
  cp->capacidad = N;

  for (nat i = 0; i<N+1; i++){
    cp->posiciones[i] = 0;
  }
  return cp;
}

nat rangoCP(TColaDePrioridad cp){
  return cp->capacidad;
}

static TColaDePrioridad filtradoAscendente(TColaDePrioridad &cp, nat pos){
  Dato swap = cp->heap[pos];
  while (pos != 1 && cp->heap[pos/2].valor > swap.valor){
    cp->heap[pos] = cp->heap[pos/2];
    cp->posiciones[cp->heap[pos/2].elem] = pos;
    pos = pos/2;
  }
  cp->heap[pos] = swap;
  cp->posiciones[swap.elem] = pos;
  return cp;
}

static TColaDePrioridad filtradoDescendente(TColaDePrioridad &cp, nat pos){
  Dato swap = cp->heap[pos];

  if(pos*2 <= cp->tope){
    while(pos*2 <= cp->tope && swap.valor > cp->heap[pos*2].valor){
      nat p_hijo = pos*2;
      
      if (((p_hijo)+1)<=cp->tope && cp->heap[(p_hijo)+1].valor < cp->heap[p_hijo].valor)
        p_hijo = p_hijo+1;

      if (swap.valor > cp->heap[p_hijo].valor){
        cp->heap[pos] = cp->heap[p_hijo];
        cp->posiciones[cp->heap[p_hijo].elem] = pos;
        pos = p_hijo;
      }
    }
    cp->heap[pos] = swap;
    cp->posiciones[swap.elem] = pos;
  }
  return cp;
}

TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp){
  cp->tope = cp->tope+1;
  cp->heap[cp->tope].elem = elem;
  cp->heap[cp->tope].valor = valor;
  cp->posiciones[elem] = cp->tope;
  cp = filtradoAscendente(cp,cp->tope);
  return cp;
}

bool estaVaciaCP(TColaDePrioridad cp){
  return cp->tope == 0;
}

nat prioritario(TColaDePrioridad cp){
  assert(!estaVaciaCP(cp));
  return cp->heap[1].elem;
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp){
  assert(!estaVaciaCP(cp));
  if (cp->tope == 1){
    cp->posiciones[(cp->heap[1]).elem] = 0;
    cp->tope = 0;
  } else{
    cp->posiciones[cp->heap[1].elem] = 0; 
    cp->heap[1] = cp->heap[cp->tope];
    cp->posiciones[cp->heap[cp->tope].elem] = 1;
    cp->tope = cp->tope-1;
    if(cp->tope > 1){
      cp = filtradoDescendente(cp,1);
    }
  }
  return cp;
}

bool estaEnCP(nat elem, TColaDePrioridad cp){
  if (estaVaciaCP(cp))
    return false;
  else
    return cp->posiciones[elem] != 0;
}

double prioridad(nat elem, TColaDePrioridad cp){
  assert(estaEnCP(elem,cp));
  return cp->heap[cp->posiciones[elem]].valor;
}

TColaDePrioridad actualizarEnCP(nat elem, double valor, TColaDePrioridad cp){
  assert(estaEnCP(elem,cp));

  nat pos = cp->posiciones[elem];
  double valor_ant = cp->heap[pos].valor;
  cp->heap[pos].elem = elem;
  cp->heap[pos].valor = valor;

  if (valor_ant > valor)
    cp = filtradoAscendente(cp,pos);
  else if (valor_ant < valor)
    cp = filtradoDescendente(cp,pos);
  return cp;
}

void liberarCP(TColaDePrioridad cp){
  delete [] cp->heap;
  delete [] cp->posiciones;
  delete cp;
}