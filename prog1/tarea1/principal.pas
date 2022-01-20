{* fpc -Co -Cr -Miso -gl principal.pas *}

{
   InCo- Fing
   Laboratorio 2020 Segundo Semestre

   Programa Principal
}

program Principal;


{ Con esta directiva queda incluido el archivo tarea.pas }
{$INCLUDE tarea.pas}


(****************************************)
(* Variables del Programa *)
(****************************************)
var
  opcion : char;
  
  semilla : integer;
  limite : integer;  

(****************************************)
(* Programa Principal *)
(****************************************)

begin

  repeat
    read(opcion);
     
    case opcion of
      'g': begin {}
             read(semilla);
             writeln(generadora(semilla):1)
           end;
           
      'l': begin {}
             read(semilla, limite);
             writeln(longitud(semilla, limite):1)
           end;
    end
      
  until opcion = 'q';	
   
end.

