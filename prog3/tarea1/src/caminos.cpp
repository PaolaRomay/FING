/*
  Módulo de implementación de `caminos'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/caminos.h"
#include "../include/lista.h"
#include "../include/pila.h"
#include "../include/grafo.h"
#include "../include/cola.h"

#include <assert.h>
#include <cstddef>

nat *CantCaminos(Grafo G, nat s)
{
  nat n = cantidad_vertices(G);
  Cola Q = crear_cola();
  encolar(s, Q);

  nat *nivel = new nat[n + 1];
  bool *explorado = new bool[n + 1];
  nat *cant_caminos = new nat[n + 1];

  for (nat i = 0; i < n + 1; i++)
  {
    nivel[i] = 0;
    explorado[i] = false;
    cant_caminos[i] = 0;
  }

  explorado[s] = true;
  cant_caminos[s] = 1;
  rep_lista *adyacentes_v = NULL;

  while (!es_vacia_cola(Q))
  {
    nat v = frente(Q);
    desencolar(Q);
    adyacentes_v = adyacentes(v, G);
    while (!es_vacia_lista(adyacentes_v))
    {
      nat ady_v = primero(adyacentes_v);
      if (!explorado[ady_v])
      {
        explorado[ady_v] = true;
        nivel[ady_v] = nivel[v] + 1;
        encolar(ady_v, Q);
      }
      if (nivel[ady_v] > nivel[v] + 1)
      {
        nivel[ady_v] = nivel[v] + 1;
        cant_caminos[ady_v] = cant_caminos[v];
      }
      else if (nivel[ady_v] == nivel[v] + 1)
      {
        cant_caminos[ady_v] = cant_caminos[ady_v] + cant_caminos[v];
      }
      adyacentes_v = resto(adyacentes_v);
    }
  }
  destruir_cola(Q);
  delete[] nivel;
  delete[] explorado;

  return cant_caminos;
}
