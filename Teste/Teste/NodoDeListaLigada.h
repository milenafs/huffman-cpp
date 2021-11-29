#ifndef NODODELISTALIGADA
#define NODODELISTALIGADA
#include "NoArvore.h"

class NodoDeListaLigada
{	
	private:

		NodoDeListaLigada* prox;
		NoArvore* info; // ponteiro de nodo de arvore
	public:	
		 NodoDeListaLigada(NoArvore* , NodoDeListaLigada* );
		 NodoDeListaLigada();
		 ~NodoDeListaLigada();
		 int operator== (const NodoDeListaLigada&);
		 int operator!= (const NodoDeListaLigada&);
		 void Descarte(NodoDeListaLigada* );
		 NodoDeListaLigada* getProx();
		 NoArvore* getInfo();
		 void setProx(NodoDeListaLigada* );
		 void setInfo(NoArvore* );	
};
#endif
