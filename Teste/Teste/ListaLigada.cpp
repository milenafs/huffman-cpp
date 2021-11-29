#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "ListaLigada.h"
#include "NodoDeListaLigada.h"

ListaLigada::ListaLigada() {} // construtor padrao

ListaLigada::ListaLigada(NodoDeListaLigada* inicio, NodoDeListaLigada* fim):
    primeiro(inicio),ultimo(fim){}

ListaLigada::~ListaLigada(){this->Descarte();} 

void ListaLigada::Descarte()
{
    for (NodoDeListaLigada* n = this->primeiro; this->primeiro != NULL;n = this->primeiro)
    {
        this->primeiro = this->primeiro->getProx();
        delete n;
    }
}


int ListaLigada::operator== (const ListaLigada& l)
{
    ListaLigada aux = l;
    while(this->primeiro != NULL && aux.primeiro != NULL)
    {
        if(this->primeiro != aux.primeiro)
            return 0;
        this->primeiro = this->primeiro->getProx();
        aux.setPrimeiro(aux.primeiro->getProx());
        
    }
    return 1;
}

int ListaLigada::operator!= (const ListaLigada& l)
{
    if(!(*this == l))
        return 1;
    return 0;
}

/*Caso der erro, voltar a lista como parametro*/
NodoDeListaLigada* ListaLigada::Insira(NodoDeListaLigada* NodoLista, NodoDeListaLigada* Inicio)
{
    if (Inicio == NULL) // insere No início
    {
        Inicio = NodoLista;
        this->primeiro = Inicio;
        return Inicio;
    }
    else if (NodoLista->getInfo()->getFreq() < Inicio->getInfo()->getFreq()) // se a frequência do NodoLista for menor que a do Inicio
    {
        NodoDeListaLigada* Novo;
        Novo = NodoLista;       //Armazena o NodoLista na posição criada acima
        Novo->setProx(Inicio);    //Transforma o Inicio no nó seguinte ao criado acima
        this->primeiro = Novo;
        return Novo;
    }
    else
    {
        Inicio->setProx(Insira(NodoLista, Inicio->getProx()));
        this->primeiro = Inicio;
        return Inicio;
    }
}

NodoDeListaLigada* ListaLigada::Remova(NodoDeListaLigada* NodoRemover, NodoDeListaLigada* Inicio)
{
    if (Inicio == NULL)
        return Inicio;

    else if (NodoRemover->getInfo()->getFreq() == Inicio->getInfo()->getFreq())
    {
        NodoDeListaLigada* Removido = new NodoDeListaLigada;
        *Removido = *Inicio;
        Inicio = Inicio-> getProx();
        this->primeiro = Inicio;
        delete Removido;  //Libera a posição de Removido da memória
        
        return Inicio;
    }
    else
    {
        Inicio->setProx(Remova(NodoRemover, Inicio->getProx()));   //Usando recursão, atualiza o valor de ínicio para uma nova comparação
        this->primeiro = Inicio;  //Transforma o Inicio no primeiro da Lista
        return Inicio;
    }
}

NodoDeListaLigada* ListaLigada::getPrimeiro()
{
    return this->primeiro;
}

NodoDeListaLigada* ListaLigada::getUltimo()
{
    return this->ultimo;
}

void ListaLigada::setPrimeiro(NodoDeListaLigada* primeiro)
{
    this->primeiro = primeiro;
}
void ListaLigada::setUltimo(NodoDeListaLigada* ultimo)
{
    this->ultimo = ultimo;
}
