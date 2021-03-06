/*
  Módulo de definición de `Grafo'.

  `Grafo' representa a los grafos dirigidos o no dirigidos.

  Los vértices se identifican con enteros entre 1 y un cierto número `max'
  establecido al crearlo. No todos los números entre 1 y `max' tienen que ser
  vértices del grafo.

  En las funciones que tienen un parámetro `v' que es un identificador de
  vértice se asume la precondición implícita `1 <= v <= max'.
  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#ifndef _GRAFO_H
#define _GRAFO_H

#include "utils.h"
#include "lista.h"

struct rep_grafo; // representación de `grafo', definida en `grafo.cpp'.
typedef rep_grafo *Grafo;

/* 
   Devuelve un grafo vacío (sin aristas ni vértices) que podrá tener hasta `max'
  vértices. 
*/
Grafo crear_grafo(nat max, bool dirigido);

/* Devuelve la cantidad máxima de vértices que puede tener `g'. */
nat max_vertice(Grafo g);

/* Devuelve `true' si y sólo si `g' es dirigido. */
bool es_dirigido(Grafo g);

/* Devuelve una copia de `g'.
   El grafo devuelto no comparte memoria con `g'. */
Grafo copia_grafo(Grafo g);

/* Agrega `v' al conjunto de identificadores de vértices de ´g'.
   Si `existe_vertices(vg)' no se hace nada. */
void agregar_vertice(nat v, Grafo &g);

/* Remueve `v' del conjunto de identificadores de vértices de ´g'.
   Si `! existe_vertices(g)' no se hace nada.  */
void remover_vertice(nat v, Grafo &g);

/* 
   Devuelve `true' si y sólo si `v' pertenece al conjunto de identificadores de
   vértices de `g'. 
   Ejecuta en O(1).   
 */
bool existe_vertice(nat v, Grafo g);

/* 
   Devuelve la cantidad de aristas salientes en `v'. 
   Ejecuta en O(1).   
*/
nat out_grado(nat v, Grafo g);

/* 
   Devuelve la cantidad de aristas entrantes en `v'. 
   Ejecuta en O(1).   
*/
nat in_grado(nat v, Grafo g);

/* 
   Devuelve una lista con los identificadores de vértices de `g' en orden creciente.
   Ejecuta en O(n).
*/
Lista vertices(Grafo g);

/* 
   Devuelve la cantidad de vértices de `g'. 
   Ejecuta en O(1).
*/
nat cantidad_vertices(Grafo g);

/* Agrega una arista desde `v1' hacia `v2'.
   Si ya había una ariste desde `v1' hacia `v2' no se hace nada.
   Precondición: existe_vertice(v1, g) && existe_vertice(v2, g). */
void agregar_arista(nat v1, nat v2, Grafo g);

/* Remueve la arista desde `v1' hacia `v2'.
   Si no había una ariste desde `v1' hacia `v2' no se hace nada.
   Precondición: existe_vertice(v1, g) && existe_vertice(v2, g). */
void remover_arista(nat v1, nat v2, Grafo g);

/* 
   Devuelve `true' si y sólo si hay una arista desde `v1' hacia `v2'.
   Precondición: existe_vertice(v1, g) && existe_vertice(v2, g). 
   Ejecuta en O(m) (Siendo m la cantidad de aristas del grafo).    
*/
bool existe_arista(nat v1, nat v2, Grafo g);

/* 
   Devuelve la cantidad de aristas de `g'. 
   Ejecuta en O(1).    
*/
nat cantidad_aristas(Grafo g);

/* 
   Devuelve una lista con los identificadores de vértices adyacentes a `v'.
   Precondición: existe_vertice(v, g).
   La lista devuelta comparte memoria con `g'.
   Ejecuta en O(1).   
*/
Lista adyacentes(nat v, Grafo g);

/* Devuelve un grafo con el mismo conjunto de vértices que `g' y con cada
   arista en sentido opuesto.
   El grafo devuelto no comparte memoria con `g'. */
Grafo traspuesto(Grafo g);

/* Devuelve el subgrafo de `g' inducido por `vertices'.
   Precondición: pertenece (elem, vertices) => existe_vertice(elem, g).
   El grafo devuelto no comparte memoria con `g'. */
Grafo inducido(Lista vertices, Grafo g);

/* Libera la memoria asignada a `g'. */
void destruir_grafo(Grafo &g);

/* Devuelve un grafo leído desde la entrada estándar.
   En la primera línea lee el valor máximo posible de vértice y si es dirigido o
   no dirigido.
   Luego, lee un vértice por línea en orden creciente del identificador de
   vértice.
   Para cada vértice se lee:
   identificador: lista_de_adyacentes
   donde `lista_de_adyacentes' cumple el formato descrito en
   `imprimir_lista'. Si el grafo es no dirigido sólo se leen los identificadores
   mayores a los del vértice.
   Termina leyendo una línea con "0:". */
Grafo leer_grafo();

/* Imprime `g' en la salida estándar.
   Cumple el formato de leer_grafo.
   Luego agrega una línea con la cantidad de vértices, otra con la cantidad
   de aristas y una línea para cada vértice, en orden creciente con la cantidad
   de arisrtas salientes y cantidad de aristas entrantes. */
void imprimir_grafo(Grafo g);

#endif
