#include <string.h>
#include <stdlib.h>
#include "ListaLigada.h"
#include "NodoDeListaLigada.h"

ListaLigada::ListaLigada(NodoDeListaLigada* inicio, NodoDeListaLigada* fim)
{
	this->primeiro = inicio;
    this->ultimo   = fim; 
}

ListaLigada::ListaLigada()
{
}
/*
Caso der erro, voltar a lista como parametro
*/
NodoDeListaLigada* ListaLigada::Insira(NodoDeListaLigada* NodoLista, NodoDeListaLigada* Inicio)
{
    if (Inicio == NULL) // insere No in�cio
    {
        Inicio = NodoLista;
        this->primeiro = Inicio;
        return Inicio;
    }
    else if (NodoLista->getInfo()->getFreq() < Inicio->getInfo()->getFreq()) // se a frequ�ncia do NodoLista for menor que a do Inicio
    {
        NodoDeListaLigada* Novo;
        Novo = NodoLista;       //Armazena o NodoLista na posi��o criada acima
        Novo->setProx(Inicio);    //Transforma o Inicio no n� seguinte ao criado acima
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
        delete Removido;  //Libera a posi��o de Removido da mem�ria
        
        return Inicio;
    }
    else
    {
        Inicio->setProx(Remova(NodoRemover, Inicio->getProx()));   //Usando recurs�o, atualiza o valor de �nicio para uma nova compara��o
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

/*
Fazer operators
Construtor de copia
Destrutor
*/