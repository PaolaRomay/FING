/* 5035742 */

#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct repBinario{
	TInfo dato;
	TBinario izq;
	TBinario der;
};

TBinario crearBinario(){ return NULL; }

TBinario insertarEnBinario(TInfo i, TBinario b){
	assert(esVacioBinario(buscarSubarbol(natInfo(i), b)));
	if (b == NULL) {
		b = new repBinario;
		b->dato = i;
		b->izq = b->der = NULL; 
	}
	else if (natInfo(b->dato) > natInfo(i))
		b->izq = insertarEnBinario(i,izquierdo(b));
	else if (natInfo(i) > natInfo(b->dato))
		b->der = insertarEnBinario(i,derecho(b));

	return b;
}

TInfo mayor(TBinario b){
	assert(!esVacioBinario(b));
	while (b->der != NULL){
		b = b->der;
	}
	return b->dato;
}

TBinario removerMayor(TBinario b){
	assert(!esVacioBinario(b));
	if (b->der == NULL) {
		TBinario aux;
		aux = b;
		b = b->izq;
		delete aux;
	} else{
		b->der =removerMayor(b->der);
	}
	return b;
}

TBinario removerDeBinario(nat elem, TBinario b){
	assert(!esVacioBinario(buscarSubarbol(elem, b)));
	TBinario aux;
	if (b != NULL){
		if (natInfo(b->dato) == elem){  

			if (b->izq == NULL){
				aux = b;
				aux->dato = b->dato;
				b = b->der;
				liberarInfo(aux->dato);
				delete(aux);
			} else if (b->der == NULL){
				aux = b;
				aux->dato = b->dato;	
				b = b->izq;
				liberarInfo(aux->dato);
				delete(aux);
			} else {
				liberarInfo(b->dato);
				b->dato =copiaInfo(mayor(b->izq));
				b->izq =removerDeBinario(natInfo(b->dato), b->izq);
			}
		}
		else if (natInfo(b->dato) > elem)
			b->izq = removerDeBinario(elem, b->izq);
		else 
			b->der = removerDeBinario(elem,b->der);
	}
	return b;
}

void liberarBinario(TBinario b){
	if (b != NULL){
		liberarBinario(b->izq);
		liberarBinario(b->der);
		liberarInfo(b->dato);
		delete b;
		b = NULL;
	}
}

bool esVacioBinario(TBinario b){
	if (b == NULL)
		return true;
	else
		return false;
}

static bool auxEsAvl(TBinario b, int* cont){ 
	int altIzq = 0, altDer = 0;
	int izq = 0, der = 0;

	if(b == NULL){
		*cont = 0;
		return 1;
	} 
	izq = auxEsAvl(b->izq, &altIzq);
	der = auxEsAvl(b->der, &altDer);
	*cont = (altIzq > altDer ? altIzq : altDer) +1;
	if(abs(altIzq-altDer) >= 2)
		return 0;
	else
		return izq && der;
 }

bool esAvl(TBinario b){
	int aux = 0;
	return auxEsAvl(b,&aux);
}

TInfo raiz(TBinario b){
	assert(!esVacioBinario(b));
	return b->dato;
}

TBinario izquierdo(TBinario b){
	assert(!esVacioBinario(b));
	return b->izq;
}

TBinario derecho(TBinario b){
	assert(!esVacioBinario(b));
	return b->der;
}

TBinario buscarSubarbol(nat elem, TBinario b){ 
	if (b == NULL){
		return b;
	} else if (natInfo(raiz(b)) == elem){
		return b;
	} else if (natInfo(raiz(b)) > elem){
		return buscarSubarbol(elem, izquierdo(b));
	} else { 
		return buscarSubarbol(elem, derecho(b));
	}	
}

nat alturaBinario(TBinario b){
	if (b == NULL) 
		return 0;
	else{
		nat alturaIzq = alturaBinario(b->izq);
		nat alturaDer = alturaBinario(b->der);
		if (alturaIzq >= alturaDer)
			return alturaIzq + 1;
		else
			return alturaDer + 1;
	}
}

nat cantidadBinario(TBinario b){
	if (b == NULL)
		return 0;
	else
		return 1 + cantidadBinario(b->izq) + cantidadBinario(b->der);
}

static double auxSumaUltimos(nat &i, TBinario b, double res){
	if (b != NULL){
		res = auxSumaUltimos(i,b->der,res);
		if (i > 0 && realInfo(raiz(b)) > 0){
			res = res + realInfo(b->dato);	
			i = i-1;
		}
		res = auxSumaUltimos(i,b->izq,res);
	}
	return res;
} 

double sumaUltimosPositivos(nat i, TBinario b){
	double res = 0;
	return auxSumaUltimos(i,b,res);
}

static TCadena auxLinealizacion(TCadena cad, TBinario b){
	if (b != NULL){
		auxLinealizacion(cad,b->izq);
		cad = insertarAlFinal(copiaInfo(b->dato),cad);
		auxLinealizacion(cad,b->der);
	}
	return cad;
} 

TCadena linealizacion(TBinario b){
	TCadena cad = crearCadena();
	return auxLinealizacion(cad,b);
}

TBinario menores(double cota, TBinario b){
	TBinario fizq, fder, res, mayor;
	TInfo imayor, raiz;
	if(b == NULL){
		res = NULL;		
	} else {
		fizq = menores(cota, b->izq);
		fder = menores(cota, b->der);
		raiz = b->dato;

		if (realInfo(raiz) < cota) {
			res = new repBinario;
			res->dato = copiaInfo(raiz);
			res->izq= fizq;
			res->der=fder;
		} else if (fizq == NULL) {			
			res = fder;
		} else if (fder == NULL) {
			res = fizq;
		} else {
			mayor = fizq;
			while (mayor->der != NULL){
				mayor = mayor->der;
			}
			imayor= mayor->dato;
			res = new repBinario;
			res->dato = imayor;
			res->der=fder;
			res->izq= removerMayor(fizq);
		}
	}
	return res;
}

static void auxImprimir(TBinario b, int cont){
	if (b != NULL){
		auxImprimir(b->der, cont+1);
		if (!esVacioBinario(b)){
			int aux=0;
			while (cont > aux){
				printf("-");
				aux = aux+1;
			}
			ArregloChars salida;
			salida = infoATexto(b->dato);
			printf("%s", salida);
			delete[] salida;
		}		
		auxImprimir(b->izq, cont+1);
	}else{
		printf("\n");
	}
}

void imprimirBinario(TBinario b){
		auxImprimir(b,0);
}
