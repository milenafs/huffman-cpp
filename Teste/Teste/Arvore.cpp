#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "Arvore.h"

Arvore::Arvore() {} // construtor padrao

Arvore::Arvore(NoArvore* r):raiz(r){}

Arvore::~Arvore() 
{ 
    this->Descarte(this->raiz); 
}

void Arvore::Descarte(NoArvore* noAtual) 
{
    if(noAtual->getEsq() != NULL)
        Descarte(noAtual->getEsq());
    else if (noAtual->getDir() != NULL)
        Descarte(noAtual->getDir());
    else
        delete noAtual;    
}

int Arvore::Comparar(NoArvore* atualA, NoArvore* atualB)
{
    if (atualA == NULL && atualB == NULL)
        return true;
    else if ((atualA == NULL) != (atualB == NULL)) // apenas um dos nós é
        return false; // nulo
    
    else if (atualA->getFreq() != atualB->getFreq() && atualA->getByte() != atualB->getByte())
        return false;
    else
        return Comparar(atualA->getEsq(), atualB->getEsq()) && Comparar(atualA->getDir(), atualB->getDir());
}


int Arvore::operator== (const Arvore& arv) 
{
    if (this->Comparar(this->raiz, arv.raiz))
        return 1;
    else
        return 0;
}


int Arvore::operator!= (const Arvore& n)
{
    if (!(*this == n))
        return 1;
    else
        return 0;
}

int Arvore::percorrerArvore(NoArvore* raiz, int byteProc, char* caminho, int posCaminho)
{
    if (raiz->getByte() == byteProc)  // chegou na folha
    {
        caminho[posCaminho] = '\0';  // termina o vetor caminho
        return 1; // achou
    }
    else
    {
        int encontrado = 0; // não achou


        if (raiz->getEsq() != NULL) // se tiver filho esquerdo
        {
            caminho[posCaminho] = '0';
            encontrado = percorrerArvore(raiz->getEsq(), byteProc, caminho, posCaminho + 1); // recursão com o filho nodo esquerdo
        }

        if (encontrado != 1 && raiz->getDir() != NULL) // se tiver direita e n tiver encontrado na esquerda
        {
            caminho[posCaminho] = '1';
            encontrado = percorrerArvore(raiz->getDir(), byteProc, caminho, posCaminho + 1); // se tive
        }
        if (encontrado != 1) // se for uma folha mas n for a folha procurada
        {
            caminho[posCaminho] = '\0'; // finaliza
        }
        return encontrado;
    }
}
int Arvore::Altura(NoArvore* noAtual) const
{
    int alturaEsquerda,
        alturaDireita;
    if (noAtual == NULL)
        return 0;
    alturaEsquerda = Altura(noAtual->getEsq());  //Recursão para contar o lado esquerdo desse nó
    alturaDireita = Altura(noAtual->getDir());   //Recursão para contar o lado direito desse nó
    if (alturaEsquerda >= alturaDireita)
        return 1 + alturaEsquerda;          //Se a árvore for 'desbalanceada', retorna o maior valor (vale pra essa linha e pra debaixo)
    return 1 + alturaDireita;
}


NoArvore* Arvore::getRaiz()
{
    return this->raiz;
}

void Arvore::setRaiz(NoArvore* r)
{
    this->raiz = r;
}

