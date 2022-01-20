/* 5035742 */

#include "../include/iterador.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>

typedef struct nodoIt *PNodoIt;
struct nodoIt {
	nat elem;
	PNodoIt sig;
};

struct repIterador {
	PNodoIt inicio, fin, actual;
	bool bloqueado;
};

TIterador crearIterador(){
	TIterador res = new repIterador;
	res->actual = res->inicio = res->fin = NULL;
	res->bloqueado = false;
	return res;
}

TIterador agregarAIterador(nat elem, TIterador iter){
	if (!iter->bloqueado){
		PNodoIt aux = new nodoIt;
		aux->sig = NULL;
		aux->elem = elem;
		if (iter->inicio == NULL && iter->fin == NULL){			
			iter->inicio = aux;
			iter->fin = aux;	
		} else {			
			iter->fin->sig = aux;
			iter->fin = aux;
		}
	}
	return iter;
}

TIterador reiniciarIterador(TIterador iter){
	if(iter != NULL)
		iter->actual = iter->inicio;
	return iter;
}

TIterador avanzarIterador(TIterador iter){
	if(estaDefinidaActual(iter))
		iter->actual = iter->actual->sig;
	if (iter->actual == NULL)
		iter->actual = NULL;
	return iter;
}

nat actualEnIterador(TIterador iter){
	assert(estaDefinidaActual(iter));
	return iter->actual->elem;
}

bool estaDefinidaActual(TIterador iter){
	return (iter->actual != NULL);
}

void liberarIterador(TIterador iter){
	PNodoIt a_borrar;
	while (iter->inicio != NULL) {
		a_borrar = iter->inicio;
		iter->inicio = iter->inicio->sig;
		delete a_borrar;
	}
	delete iter;
}

