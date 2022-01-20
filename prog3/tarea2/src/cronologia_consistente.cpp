/*
  Módulo de implementación de `cronologia_consistente'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
*/
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "../include/utils.h"
#include "../include/cronologia_consistente.h"
#include "../include/lista.h"
#include "../include/lista_datos.h"
#include "../include/grafo.h"

Cronologia cronologia_consistente(nat n, ListaDatos tipo1, ListaDatos tipo2)
{
  Grafo g = crear_grafo(2 * n, true);
  nat vertices = 2 * n;

  for (nat i = 1; i <= vertices; i++)
  {
    agregar_vertice(i, g);
  }
  for (nat i = 1; i <= n; i++)
  {
    agregar_arista(i, i + n, g);
  }
  ListaDatos puntero = tipo1;
  while (puntero != NULL)
  {
    dato aux = primer_dato(puntero);
    agregar_arista(id1(aux) + n, id2(aux), g);
    puntero = resto_datos(puntero);
  }
  puntero = tipo2;
  while (puntero != NULL)
  {
    dato aux = primer_dato(puntero);
    agregar_arista(id1(aux), id2(aux) + n, g);
    agregar_arista(id2(aux), id1(aux) + n, g);
    puntero = resto_datos(puntero);
  }

  nat *grado_nodos = new nat[vertices + 1];
  for (nat i = 1; i <= vertices; i++)
  {
    grado_nodos[i] = in_grado(i, g);
  }
  Lista sin_incidentes = crear_lista();
  for (nat i = 1; i <= vertices; i++)
  {
    if (grado_nodos[i] == 0)
    {
      insertar_al_inicio(i, sin_incidentes);
    }
  }
  Cronologia cr = new evento[2 * n];
  nat indice = 0;
  while (!es_vacia_lista(sin_incidentes))
  {
    nat aux2 = primero(sin_incidentes);
    if (aux2 <= n)
    {
      cr[indice].id = aux2;
      cr[indice].tipo = nace;
    }
    else
    {
      cr[indice].id = aux2 - n;
      cr[indice].tipo = muere;
    }
    indice = indice + 1;
    Lista lista_ady = adyacentes(aux2, g);
    while (!es_vacia_lista(lista_ady))
    {
      nat ady = primero(lista_ady);
      grado_nodos[ady] = grado_nodos[ady] - 1;
      if (grado_nodos[ady] == 0)
      {
        insertar_al_inicio(ady, sin_incidentes);
      }
      remover_al_inicio(lista_ady);
    }
    remover(aux2, sin_incidentes);
  }
  bool existe_cr_consistente = true;
  for (nat i = 1; i <= vertices; i++)
  {
    if (grado_nodos[i] != 0)
    {
      existe_cr_consistente = false;
    }
  }

  destruir_lista(sin_incidentes);
  destruir_grafo(g);
  delete[] grado_nodos;
  if (existe_cr_consistente)
  {
    return cr;
  }
  else
  {
    delete[] cr;
    return NULL;
  }
}
