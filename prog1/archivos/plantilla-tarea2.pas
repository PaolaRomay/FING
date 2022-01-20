{
 
 Este es el archivo tarea2.pas que es el único que se entrega.
 Solo se deben implementar los subprogramas pedidos y, tal vez, otros 
 auxiliares para ellos.
 
 NO se debe implementar aquí un progrma independiente.
 Este archivo se integra con principal2.pas, que lo incluye. 
  
 Se compila mediante: 
$ fpc -Co -Cr -Miso -gl principal2.pas

 y se ejecutan los casos de prueba mediante
$ ./principal2 < entradas/caso.txt

o  
$ ./principal2 < entradas/caso.txt > mios/caso,txt
$ diff salidas/caso.txt mios/caso,txt 

o de manera interactiva
$ ./principal2 
y siguiendo el instructivo publicado.

}

{ El resultado es true si y solo si 'a' y 'b' son la misma carta. }
function sonCartasIguales (a, b : TCarta) : boolean;
begin
end;


{ Copia en las primeras 'cantCols' de 't' las caratas de 'mazo' en orden 
  creciente de filas y cada fila de izquierda a derecha. 
  Se puede asumir que la cantidad de cartas de 'mazo' caben en esas columnas
  de 't'. }
procedure armarTablero (mazo: TMazo; cantCols: TRangoCols; var t: TTablero);
begin
end;


{ Copia las cartas de 't' en 'mazo' en orden creciente de columnas y cada 
  columna en orden creciente de filas. }
procedure levantarTablero (t: TTablero; var mazo: TMazo);
begin
end;


{ Determina en que columna de 't' está 'carta'.
  Se puede asumir que 'carta' está en el tablero 't'. 
  Se puede asumir que en t no hay cartas repetidas. }
function enQueColumna (carta : TCarta; t: TTablero): TRangoCols;
begin
end;


{ Deja en 'mazo' solo las cartas que también están en 'columna'.
  Las cartas quedan en el mismo orden relativo en que estaban. }
procedure estanEnAmbos (columna : TColumna; var mazo : TMazo);
begin
end;


{ Convierte 't' en 'tl'.
  En la recorrida de una columna de 'tl' desde el inicio hasta el final 
  se deben encontrar las mismas cartas en el mismo orden que en la recorrida 
  de la columna correspondiente de 't' desde la primera fila hasta la última. }
procedure convertirTablero (t : TTablero; var tl : TTableroL);
begin
end;        

