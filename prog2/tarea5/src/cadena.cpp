/* 5035742 */
 
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodo {
	TInfo dato;
	TLocalizador anterior;
	TLocalizador siguiente;
};

struct repCadena {
	TLocalizador inicio;
	TLocalizador final;
};

bool esLocalizador(TLocalizador loc) {return loc != NULL; }

TCadena crearCadena() {
	TCadena res = new repCadena;
	res->inicio = res->final = NULL;
	return res;
}

void liberarCadena(TCadena cad) {
	TLocalizador a_borrar;
	while (cad->inicio != NULL) {
		a_borrar = cad->inicio;
		cad->inicio = cad->inicio->siguiente;
		liberarInfo(a_borrar->dato);
		delete a_borrar;
	}
	delete cad;
}

bool esVaciaCadena(TCadena cad) {
	assert(((cad->inicio == NULL) && (cad->final == NULL)) ||
		   ((cad->inicio != NULL) && (cad->final != NULL)));
	return (cad->inicio == NULL);
}

TLocalizador inicioCadena(TCadena cad) {
	TLocalizador res;
	if (esVaciaCadena(cad)) {
		res = NULL;
	} else {
		res = cad->inicio;
	}
	return res;
}

TLocalizador finalCadena(TCadena cad) {
	TLocalizador res;
	if (esVaciaCadena(cad)) {
		res = NULL;
	} else {
		res = cad->final;
	}
	return res;
}

TInfo infoCadena(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	return (loc->dato);
}

TLocalizador siguiente(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TLocalizador res;
	if (esFinalCadena(loc, cad)) {
		res = NULL;
	} else {
		res = loc->siguiente;
	}
	return res;
}

TLocalizador anterior(TLocalizador loc, TCadena cad) { 
	assert(localizadorEnCadena(loc, cad));
	TLocalizador res;
	if (esInicioCadena(loc, cad)) {
		res = NULL;
	} else {
		res = loc->anterior;
	}
	return res;
}

bool esFinalCadena(TLocalizador loc, TCadena cad) {
	bool res;
	if (esVaciaCadena(cad)) {
		res = false;
	} else {
		res = (loc == finalCadena(cad)); 
	}
	return res;
}

bool esInicioCadena(TLocalizador loc, TCadena cad) {
	bool res;
	if (esVaciaCadena(cad)) {
		res = false;
	} else {
		res = (loc == inicioCadena(cad));
	}
	return res;	
}

TCadena insertarAlFinal(TInfo i, TCadena cad) {
	if (esVaciaCadena(cad)) {
		TLocalizador nloc = new nodo;
		cad->inicio = nloc;
		cad->final =  nloc;
		nloc->dato = i;
		nloc->anterior = NULL;
		nloc->siguiente = NULL;
	} else {
		TLocalizador nloc = new nodo;
		nloc->anterior = cad->final;
		cad->final->siguiente = nloc;
		cad->final = nloc;
		nloc->dato = i;	
		nloc->siguiente = NULL;
	}
	return cad;
}


TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	if(loc == inicioCadena(cad)){
		TLocalizador nloc = new nodo;
		loc->anterior = nloc;
		nloc->anterior = NULL;
		nloc->siguiente = loc;
		nloc->dato = i;	
		cad->inicio = nloc;
	} else {
		TLocalizador nloc = new nodo;	
		anterior(loc,cad)->siguiente = nloc;
		nloc->anterior = loc->anterior;
		nloc->siguiente = loc;
		loc->anterior = nloc; 
		nloc->dato = i; 
	}
	return cad;
}

TCadena removerDeCadena(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	if (inicioCadena(cad) == finalCadena(cad)) { 
		liberarInfo(loc->dato);
		delete loc;
		cad->inicio = NULL;
		cad->final = NULL;	
	} else if (loc == finalCadena(cad)){  
		anterior(loc,cad)->siguiente = NULL;
		cad->final = loc->anterior;
		liberarInfo(loc->dato);
		delete loc;
	} else if (loc == inicioCadena(cad)){ 
		siguiente(loc,cad)->anterior = NULL;
		cad->inicio = loc->siguiente;
		liberarInfo(loc->dato);
		delete loc;
	} else { 
		loc->anterior->siguiente = loc->siguiente;
		loc->siguiente->anterior = loc->anterior;
		liberarInfo(loc->dato);
		delete loc;
	}		
	return cad;
}

void imprimirCadena(TCadena cad) {
	if (!esVaciaCadena(cad)){
		ArregloChars salida;
		TLocalizador aux; 
		aux = inicioCadena(cad);
		while (aux != NULL){
			salida = infoATexto(infoCadena(aux,cad));
			printf("%s", salida);
			delete[] salida;
			aux = siguiente(aux,cad);
		}
	}
	printf("\n");
}

TLocalizador kesimo(nat k, TCadena cad) {
	TLocalizador loc;
	if (k==0){
		loc = NULL;
	} else {
		nat i; i=1;
		loc = inicioCadena(cad);
		while (k>i){
			loc = siguiente(loc,cad);
			i=i+1;
		}
		if (k > i && loc == finalCadena(cad)){
			loc = NULL;
		}
	}
	return loc;
}

bool localizadorEnCadena(TLocalizador loc, TCadena cad) {
	TLocalizador cursor = inicioCadena(cad);
	while (esLocalizador(cursor) && (cursor != loc))
		cursor = siguiente(cursor, cad);
	return esLocalizador(cursor);
}

bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
	bool res;
	res = localizadorEnCadena(loc1, cad);
	if (res){
		TLocalizador cursor = loc1;
		while (esLocalizador(cursor) && (cursor != loc2))
			cursor = siguiente(cursor, cad);
		res = esLocalizador(cursor);
		assert(!res || localizadorEnCadena(loc2, cad));
	}
	return res;
}

TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad) {
	assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
	if (esVaciaCadena(cad)){
		cad->inicio = sgm->inicio;
		cad->final = sgm->final;
	} else if (esVaciaCadena(sgm)) {
		cad = cad;
	} 
	else {
		if ((loc == inicioCadena(cad) && loc == finalCadena(cad))) {
			cad->inicio->siguiente = sgm->inicio;
			cad->final = sgm->final;
			sgm->inicio->anterior = loc; 

		} else if (loc == finalCadena(cad)){
			loc->siguiente = inicioCadena(sgm);
			sgm->inicio->anterior = loc;
			cad->final = finalCadena(sgm);

		} else {
			loc->siguiente->anterior = finalCadena(sgm);
			finalCadena(sgm)->siguiente = loc->siguiente;
			loc->siguiente = inicioCadena(sgm);
			inicioCadena(sgm)->anterior = loc;
		}	
	}
	delete(sgm);
	return cad;
}

TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
	assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
	TCadena cadnueva;
	cadnueva = crearCadena();
	if (esVaciaCadena(cad)) {
		cadnueva = cadnueva;
	} else {
		if (desde == hasta){
			TLocalizador aux = new nodo;
			aux->dato = copiaInfo(desde->dato);
			cadnueva->inicio = aux;
			cadnueva->final = aux;
			aux->anterior = NULL;
			aux->siguiente = NULL;
		} else {
			TLocalizador aux2;
			TLocalizador aux3;
			aux2 = desde;
			cadnueva->inicio= new nodo;
			cadnueva->inicio->dato = copiaInfo(desde->dato);
			cadnueva->inicio->anterior = NULL; 
			aux3 = cadnueva->inicio;
			while (aux2 != hasta){
				aux2 = aux2->siguiente;
				aux3->siguiente = new nodo;
				aux3->siguiente->anterior = aux3;
				aux3->siguiente->dato = copiaInfo(aux2->dato);
				aux3 = aux3->siguiente;
			}
			cadnueva->final = aux3;
			aux3->siguiente = NULL;
		}
	}
	return cadnueva;
}

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
	assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
	if (esVaciaCadena(cad)) {
		cad = cad;
	} else {
		TLocalizador aux;
		TLocalizador auxdesde;
		TLocalizador auxhasta;
		aux = desde;

		if (desde == inicioCadena(cad) && hasta == finalCadena(cad)){ 
			while (aux != hasta){
				aux = aux->siguiente;
				removerDeCadena(aux->anterior,cad);
			}
			removerDeCadena(hasta,cad);
			cad->inicio = NULL;
			cad->final = NULL;

		} else if (hasta == cad->final){
			auxhasta = hasta->siguiente;
			auxdesde = desde->anterior;	
			while (aux != hasta){
				aux = aux->siguiente;
				removerDeCadena(aux->anterior,cad);
			}
			removerDeCadena(hasta,cad);
			auxdesde->siguiente = auxhasta;
			cad->final = auxdesde;

		} else if (desde == cad->inicio){
			auxhasta = hasta->siguiente;
			while (aux != hasta){
				aux = aux->siguiente;
				removerDeCadena(aux->anterior,cad);
			}
			removerDeCadena(hasta,cad);
			cad->inicio = auxhasta;
			cad->inicio->anterior = NULL;

		} else {
			auxdesde = desde->anterior;
			auxhasta = hasta->siguiente;
			while (aux != hasta){
				aux = aux->siguiente;
				removerDeCadena(aux->anterior,cad);
			}
			removerDeCadena(hasta,cad);
			auxdesde->siguiente = auxhasta;
			auxhasta->anterior = auxdesde;
		}
	}
	return cad;
}

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc,cad));
	loc->dato = i;
	return cad;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
	assert(localizadorEnCadena(loc1,cad) || localizadorEnCadena(loc2,cad));
	TLocalizador aux = new nodo;
	aux->dato = infoCadena(loc1,cad);
	loc1->dato = infoCadena(loc2,cad);
	loc2->dato = aux->dato;
	delete aux;
	return cad;
}

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad) {
	assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
	TLocalizador aux;
	aux = loc;
	if (esVaciaCadena(cad)) {
		loc = NULL;
	} else {
		while (esLocalizador(aux) && natInfo(infoCadena(aux,cad)) != clave) {
			aux = siguiente (aux,cad);
		}
		if (!esLocalizador(aux)) {
			loc = NULL;
		} else {
			loc = aux;
		}
	}
	return loc;
}

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad) {
	assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
	TLocalizador aux;
	aux = loc;
	if (esVaciaCadena(cad)) {
		loc = NULL;
	} else {
		while (aux!=NULL && natInfo(infoCadena(aux,cad)) != clave) {
			aux = anterior(aux,cad);
		}
		if (aux == NULL) {
			loc = NULL;
		} else {
			loc = aux;
		}
	}
	return loc;	
}

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad) {
	assert(localizadorEnCadena(loc, cad));
	TLocalizador aux;
	aux = finalCadena(cad);
	TLocalizador menor;
	menor = loc;
	while ( aux != loc){
		if (natInfo(aux->dato) <= natInfo(menor->dato)){
			menor = aux;
		}
	aux = aux->anterior;
	}
	menor = menor;	
	return menor;
}