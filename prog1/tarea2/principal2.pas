{* fpc -Co -Cr -Miso -gl principal2.pas *}

{
   InCo- Fing
   Laboratorio 2020 Segundo Semestre

   Programa Principal
}

program Principal2;

const
  COLS = 8;
  FILAS = 20;

  N =  COLS * FILAS;

type 
  TNumero = 1 .. N div 4;
  TPalo = (copas, bastos, espadas, oros);
  TCarta = record 
    case comodin: boolean of
      false : (numero: TNumero; palo: TPalo);
      true : ()
  end;

  TColumna = record
    tope : 0 .. FILAS;
    cartas : array [1 .. FILAS] of TCarta
  end;  
  TTablero = record
    tope : 0 .. COLS;
    columnas : array [1 .. COLS] of TColumna  
  end;

  TMazo = record
    tope : 0 .. N;
    cartas : array [1..N] of TCarta
  end;  

  TRangoCols = 1 .. COLS;

{ versión de columna y tablero implementado con listas }
  TColumnaL = ^ncartas;
  ncartas = record
    carta : TCarta;
    sig : TColumnaL
  end;
  
  TTableroL = record
    tope : 0 .. COLS;
    columnas : array [1 .. COLS] of TColumnaL  
  end;


{ Con esta directiva queda incluido el archivo tarea2.pas }
{$Include tarea2.pas}


procedure leerCarta (var carta: TCarta);
var
  num : 0 .. N div 4;
  p : char;
begin
  read (num);
  read (p);
  carta.comodin := p = 'J';
  if not carta.comodin then
  begin
    case p of
      'C': carta.palo := copas;
      'E': carta.palo := espadas;
      'B': carta.palo := bastos;
      'O': carta.palo := oros;
      else writeln ('ERROR palo inexistente')
    end;
    carta.numero := num
  end  
end;


procedure leerMazo (var mazo: TMazo);
var
  pos : 0 .. N;
begin
  read (mazo.tope);
  for pos := 1 to mazo.tope do
    leerCarta (mazo.cartas[pos])
end;


procedure leerColumna (var columna: TColumna);
var
  pos : 0 .. FILAS;
begin
  read (columna.tope);
  for pos := 1 to columna.tope do
    leerCarta (columna.cartas[pos])
end;


procedure mostrarCarta (carta : TCarta);
begin
  if carta.comodin then 
    write ('[  J  ]')
  else
  begin
    write ('[', carta.numero:2, ' ');
    case carta.palo of
      copas   : write('C');
      bastos  : write('B');
      espadas : write('E');
      oros    : write('O')
    end;
    write (' ]')
  end
end;


procedure mostrarMazo (mazo : TMazo);
var
  pos : 0 .. N;
begin
  for pos := 1 to mazo.tope do
    mostrarCarta (mazo.cartas[pos]);
  writeln ()
end;


procedure mostrarTablero (t: TTablero);
var
  c : 0 .. COLS;
  f : 0 .. FILAS;
begin
  if t.tope > 0 then
  begin
    for f := 1 to t.columnas[1].tope do 
    begin
      for c := 1 to t.tope do 
        if f <= t.columnas[c].tope then 
          mostrarCarta (t.columnas[c].cartas[f]);
      writeln ()
    end
  end  
end;


procedure mostrarLista (lst : TColumnaL);
begin
  while lst <> nil do
  begin
    mostrarCarta (lst^.carta);
    lst := lst^.sig  
  end;
end;


procedure mostrarTableroL (tl: TTableroL);
var
  c: 0 .. COLS + 1;
begin
  c := 1;
  while (c <= tl.tope) and (tl.columnas[c] <> nil)  do 
  begin
    mostrarLista (tl.columnas[c]);
    writeln ();
    c := c + 1
  end
end;



procedure adivinar (mazo: TMazo; cantCols: TRangoCols; elegida: TCarta);
var
  candidatos : TMazo;
  t : TTablero;
  idCol : 1 .. COLS;
begin
  candidatos := mazo;
  while candidatos.tope > 1 do 
  begin
    armarTablero (mazo, cantCols, t);
    idCol := enQueColumna (elegida, t);
    mostrarTablero (t);
    writeln('El público dice que está en la columna: ', idCol:1);
    estanEnAmbos (t.columnas[idCol], candidatos);
    levantarTablero (t, mazo)
  end;
  write ('La carta elegida es ');
  mostrarCarta (elegida);
  writeln () 
end;



var
  opcion : char; { identificador del comando }
  cantcols : 1 .. COLS;
  mazo, mazo2 : TMazo;
  columna : TColumna; 
  pos : 1 .. N;
  tablero : TTablero;
  elegida, carta1, carta2 : TCarta;
  tableroL : TTableroL;
		 
begin

  { inicializar el tablero vacío }
  tablero.tope := 0;


  repeat
    read (opcion);
     
    case opcion of

      's': { son cartas iguales }
        begin 
          leerCarta(carta1); leerCarta (carta2);
          
          if sonCartasIguales (carta1, carta2) then
            writeln ('Las cartas son iguales')
          else
            writeln ('Las cartas NO son iguales')
        end;
        
      'm': { desplegar el mazo en el tablero }
        begin
          read (cantCols);
          leerMazo (mazo);
          armarTablero (mazo, cantCols, tablero);
          writeln()
        end;

      't':  
        mostrarTablero (tablero);
        
      'l': { levantar el tablero }
        begin
          levantarTablero (tablero, mazo2);
          mostrarMazo (mazo2);
        end;
       
      'b': { buscar en que columna está la carta elegida. }
        begin
          if mazo.tope = 0 then
            writeln ('No se ha creado el mazo.')
          else
          begin
            read (pos);
            if pos > mazo.tope then writeln ('La posición elegida está fuera de rango.')
            else 
              writeln ('Está en la columna ', enQueColumna (mazo.cartas[pos], tablero):1)
          end    
        end;
        
      'e': { estanEnAmbas }
        begin
          leerColumna (columna);
          leerMazo (mazo2);
          estanEnAmbos (columna, mazo2);
          if mazo2.tope = 0 then
            writeln('Ninguna carta están en ambos.')
          else 
            begin  
              write ('Los que están en ambos son ');
              mostrarMazo (mazo2) 
            end                   
        end;
        
      'a': { adivinar }
        begin
          read (cantCols);
          leerMazo (mazo2);
          leerCarta (elegida);
          adivinar (mazo2, cantCols, elegida) 
        end;
        
      'c': { convertir }
        begin
          convertirTablero (tablero, tableroL);
          mostrarTableroL (tableroL)
        end;
           
    end
      
  until opcion = 'q';	

end.

