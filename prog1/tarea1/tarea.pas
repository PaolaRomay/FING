function generadora (n: integer): integer;
var
	digito1, digito2, digito3, mayor, menor, medio, a, b : integer;
begin
	digito3 := n mod 10;
	n := n div 10;
	digito2 := n mod 10;
	n := n div 10;
	digito1 := n mod 10;

	if ((digito1 = digito2) and (digito2 = digito3)) then
		generadora := 000
	else
	begin
		if ((digito1 >= digito2) and (digito1 >= digito3)) then
			mayor := digito1
		else if((digito2 >= digito1) and (digito2 >= digito3)) then
			mayor := digito2
		else 
			mayor := digito3;

		if ((digito1 <= digito2) and (digito1 <= digito3)) then
			menor := digito1
		else if((digito2 <= digito1) and (digito2 <= digito3)) then
			menor := digito2
		else 
			menor := digito3;

		if ((mayor = digito1) or (mayor = digito2)) then
		begin
			if((menor = digito1) or (menor = digito2)) then
				medio := digito3
		end
		else if ((mayor = digito1) or (mayor = digito3)) then
		begin
			if((menor = digito1) or (menor = digito3)) then
				medio := digito2;
		end
		else
			medio := digito1;

		a := mayor * 100 + medio * 10 + menor;
		b := menor * 100 + medio * 10 + mayor;

		generadora := a-b
	end
end;

function longitud (semilla: integer; limite: integer): integer;
var
	cont, aux: integer;
begin
	cont := 0;
	aux := semilla;

	while (aux <> generadora(aux)) and (cont  < limite) do 
	begin
		cont:= cont +1;
		aux:= generadora(aux);
	end;

	if (cont  < limite) and (aux = generadora(aux)) then 
		cont := cont + 1
	else
		cont := -1;

	longitud := cont
end;
