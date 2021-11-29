#ifndef LISTALIGADA
#define LISTALIGADA
#include "NodoDeListaLigada.h"
class ListaLigada
{
	private:
		 NodoDeListaLigada* primeiro, * ultimo;
	public:
		ListaLigada();
		~ListaLigada();
		int operator== (const ListaLigada&);
		int operator!= (const ListaLigada&);
		void Descarte(ListaLigada* );
		ListaLigada(NodoDeListaLigada* , NodoDeListaLigada* );
		NodoDeListaLigada* getPrimeiro();
		NodoDeListaLigada* getUltimo();
		void setPrimeiro(NodoDeListaLigada* );
		void setUltimo(NodoDeListaLigada* );
		NodoDeListaLigada* Insira( NodoDeListaLigada* ,  NodoDeListaLigada* );
		NodoDeListaLigada* Remova( NodoDeListaLigada* ,  NodoDeListaLigada* );
};
#endif						