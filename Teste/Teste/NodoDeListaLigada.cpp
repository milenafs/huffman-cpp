#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "NodoDeListaLigada.h"
#include "NoArvore.h"

NodoDeListaLigada::NodoDeListaLigada() {}// construtor padrao

NodoDeListaLigada::NodoDeListaLigada(NoArvore* no, NodoDeListaLigada* prox):
    info(no),prox(prox){}


int NodoDeListaLigada::operator== (const NodoDeListaLigada& n)
{
    if (this->info != n.info) return 0;
    if(this->prox != n.prox) return 0;
    return 1;
}

int NodoDeListaLigada::operator!= (const NodoDeListaLigada& n)
{
    if(!(*this == n))
        return 1;
    return 0;
}

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

