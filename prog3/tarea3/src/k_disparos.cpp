#include <stdio.h>
#include "../include/k_disparos.h"

int maximo(int a, int b)
{
  if (a < b)
  {
    return b;
  }
  else
  {
    return a;
  }
}

Estrategia *k_disparos(nat *precios, nat n, nat k)
{
  Estrategia *ret = new Estrategia;
  int ganancias[k + 1][n]; // matriz
  Intervalo *intervalos = new Intervalo[k];

  //Completo matriz
  ganancias[0][0] = 0;
  for (nat i = 1; i <= k; i++)
  {
    ganancias[i][0] = 0; //inicializo con 0 primera fila
    for (nat j = 1; j < n; j++)
    {
      ganancias[0][j] = 0; //inicializo con 0 primera columna
      int max = 0;
      for (nat k = 0; k < j; k++)
      {
        int Diff = precios[j + 1] - precios[k + 1] + ganancias[i - 1][k];
        max = maximo(Diff, max);
      }
      ganancias[i][j] = maximo(max, ganancias[i][j - 1]);
    }
  }
  nat i = k;
  nat j = n - 1;
  nat cant_disparos = k;
  while (i != 0 || j != 0)
  {
    Intervalo transaccion;
    if (ganancias[i][j] == ganancias[i][j - 1])
    {
      j--;
    }
    else
    {
      transaccion.fin = j + 1;
      nat Diff = ganancias[i][j] - precios[j + 1];
      int aux = j - 1;
      while (aux >= 0)
      {
        if (ganancias[i - 1][aux] - precios[aux + 1] == Diff)
        {
          i--;
          j = aux;
          transaccion.inicio = j + 1;
          aux = 0;
        }
        aux--;
      }
      intervalos[cant_disparos - 1] = transaccion;
      cant_disparos--;
    }
  }
  ret->intervalos = intervalos;
  ret->cant_intervalos = k;
  ret->ganancia_max = ganancias[k][n - 1];
  return ret;
}