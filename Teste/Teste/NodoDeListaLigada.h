#ifndef NODODELISTALIGADA
#define NODODELISTALIGADA
#include "NoArvore.h"

class NodoDeListaLigada
{
	private:

		NodoDeListaLigada* prox;
		NoArvore* info; // ponteiro de nodo de arvore
	public:	
		 NodoDeListaLigada(NoArvore* noArvore, NodoDeListaLigada* prox);
		 NodoDeListaLigada();
		 NodoDeListaLigada* getProx();
		 NoArvore* getInfo();
		 void setProx(NodoDeListaLigada* prox);
		 void setInfo(NoArvore* info);
};
#endif
