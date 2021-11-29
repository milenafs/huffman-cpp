#include <string.h>
#include <stdlib.h>
#include "NodoDeListaLigada.h"
#include "NoArvore.h"

NodoDeListaLigada::NodoDeListaLigada() {}// construtor padrao

NodoDeListaLigada::NodoDeListaLigada(NoArvore* no, NodoDeListaLigada* prox):
    info(no),prox(prox){}

NodoDeListaLigada::~NodoDeListaLigada() { this->Descarte(this); }

void NodoDeListaLigada::Descarte(NodoDeListaLigada* noAtual)
{}

int NodoDeListaLigada::operator== (const NodoDeListaLigada& n)
{
    if (this->getInfo() != n.info) return 0;
    if(this->getProx() != n.prox) return 0;
    return 1;
}

int NodoDeListaLigada::operator!= (const NodoDeListaLigada& n)
{
    if(!(*this == n))
        return 1;
    else
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

