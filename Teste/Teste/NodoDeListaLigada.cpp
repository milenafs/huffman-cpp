#include <string.h>
#include <stdlib.h>
#include "NodoDeListaLigada.h"
#include "NoArvore.h"

NodoDeListaLigada::NodoDeListaLigada(NoArvore* no, NodoDeListaLigada* prox)
{
    this->info = no;
    this->prox = prox;
}

NodoDeListaLigada::NodoDeListaLigada(){}// construtor padrao
	
NodoDeListaLigada* NodoDeListaLigada::getProx() {return this->prox;}

NoArvore* NodoDeListaLigada::getInfo(){return this->info;}

void NodoDeListaLigada::setProx(NodoDeListaLigada* prox) 
{
    this->prox = prox;
}

void NodoDeListaLigada::setInfo(NoArvore* info)
{
    this->info = info;
}

