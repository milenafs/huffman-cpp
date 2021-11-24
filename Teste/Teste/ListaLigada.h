#ifndef LISTALIGADA
#define LISTALIGADA
#include "NodoDeListaLigada.h"
class ListaLigada
{
	private:
		 NodoDeListaLigada* primeiro, * ultimo;
	public:
		ListaLigada();
		ListaLigada(NodoDeListaLigada* primeiro, NodoDeListaLigada* ultimo);
		NodoDeListaLigada* getPrimeiro();
		NodoDeListaLigada* getUltimo();
		void setPrimeiro(NodoDeListaLigada* primeiro);
		void setUltimo(NodoDeListaLigada* ultimo);
		NodoDeListaLigada* Insira( NodoDeListaLigada* NodoLista,  NodoDeListaLigada* Inicio);
		NodoDeListaLigada* Remova( NodoDeListaLigada* NodoRemover,  NodoDeListaLigada* Inicio);
};
#endif						