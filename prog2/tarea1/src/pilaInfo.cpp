#include "../include/pilaInfo.h"
#include "../include/listaInfo.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdlib.h>

struct repPila
{
	TLista lst;
};

TPila crearPila()
{
	TPila resultado = new repPila;
	(*resultado).lst = crearLista();
	return resultado;
}

bool esVaciaPila(TPila p)
{
	return longitud((*p).lst) == 0;
}

TPila apilar(info_t nuevo, TPila p)
{
	(*p).lst = insertar(longitud((*p).lst) + 1, nuevo, (*p).lst);
	return p;
}

info_t cima(TPila p)
{
	assert(!esVaciaPila(p));
	return infoLista(longitud((*p).lst), (*p).lst);
}

TPila desapilar(TPila p)
{
	(*p).lst = remover(longitud((*p).lst), (*p).lst);
	return p;
}
