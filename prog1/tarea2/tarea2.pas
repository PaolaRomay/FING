function sonCartasIguales (a, b : TCarta) : boolean;
var 
  igualdad: boolean;
begin
  igualdad := false;
  if (a.comodin and b.comodin) then
    igualdad := true
  else if (a.comodin or b.comodin) then
    igualdad := false
  else if (a.numero = b.numero) and (a.palo = b.palo) then
    igualdad := true
  else
    igualdad := false;

  sonCartasIguales := igualdad
end;

procedure armarTablero (mazo: TMazo; cantCols: TRangoCols; var t: TTablero);
var
  cartas, i, j, cantFilas, topeCol : integer;
begin
  cartas := 1;
  t.tope := cantCols;
  cantFilas := mazo.tope div cantCols;
  if ((mazo.tope mod cantCols) <> 0) then
    cantFilas := cantFilas +1;

  for i := 1 to cantFilas do
  begin
    for j := 1 to cantCols do
    begin
      if (i = 1) then
      begin
        topeCol := (mazo.tope-cartas+1) div cantCols;
        if ((mazo.tope-cartas+1) mod cantCols) <> 0 then
          topeCol := topeCol +1;

        t.columnas[j].tope := topeCol;
      end;

      if (t.columnas[j].tope > 0) then
      begin
        t.columnas[j].cartas[i] := mazo.cartas[cartas];
        cartas := cartas +1;
      end;
    end;
  end
end;

procedure levantarTablero (t: TTablero; var mazo: TMazo);
var
  i, fila, columna: integer;
begin
  i := 1;
  fila := 1;
  columna := 1;
  mazo.tope := 0;

  for columna := 1 to t.tope do
  begin
    if t.columnas[columna].tope > 0 then
    begin 
      for fila := 1 to t.columnas[columna].tope do
      begin
        mazo.cartas[i] := t.columnas[columna].cartas[fila];
        i := i +1;
        mazo.tope := mazo.tope +1;
      end;
    end;
  end
end;

function enQueColumna (carta : TCarta; t: TTablero): TRangoCols;
var
  fila, columna, posicion: integer;
begin
  columna := 1;
  fila := 1;
  posicion := 0;

  while (columna <= t.tope) and (posicion = 0) do
  begin
    while (fila < t.columnas[columna].tope) and (not sonCartasIguales(t.columnas[columna].cartas[fila], carta)) do
    begin
      fila := fila +1;
    end;
    if sonCartasIguales(t.columnas[columna].cartas[fila], carta) then
      posicion := columna;

    columna := columna +1;
    fila := 1;
  end;
  enQueColumna := posicion
end;

procedure estanEnAmbos (columna : TColumna; var mazo : TMazo);
var
  i, col, nuevomazo : integer;
begin
  nuevomazo := 1;
  i := 1;

  if (columna.tope = 0) or (mazo.tope = 0) then
    mazo.tope := 0
  else
  begin
    for i := 1 to mazo.tope do
    begin
      col := 1; 
      while (col <= columna.tope) and (not sonCartasIguales(mazo.cartas[i], columna.cartas[col])) do
        col := col +1;

      if (col <= columna.tope) and (sonCartasIguales(mazo.cartas[i], columna.cartas[col])) then
      begin
        mazo.cartas[nuevomazo] := mazo.cartas[i];
        nuevomazo:= nuevomazo+1;
      end;
    end; 
    mazo.tope := nuevomazo-1;
  end;
end;

procedure convertirTablero (t : TTablero; var tl : TTableroL);
var
  i, j : integer;
  p, q : TColumnaL;
begin
  tl.tope := t.tope;

  for i := 1 to tl.tope do
    tl.columnas[i] := nil;

  for i := 1 to t.tope do
  begin
    for j:= 1 to t.columnas[i].tope do
    begin
      if (tl.columnas[i] = nil) then
      begin
        new(p);
        p^.sig := nil;
        p^.carta := t.columnas[i].cartas[j];
        tl.columnas[i] := p;
      end
      else
      begin
        p := tl.columnas[i];
        while (p^.sig <> nil) do
          p := p^.sig;

        new(q);
        q^.sig := nil;
        q^.carta := t.columnas[i].cartas[j];
        p^.sig := q;
      end;
    end;
  end;
end;  