#include <string.h>
#include <stdlib.h>
#include "NoArvore.h"

NoArvore::NoArvore(int byte, int freq, NoArvore* Esq, NoArvore* Dir) 
{
    this->byte = byte;
    this->freq = freq;
    this->Esq = Esq;
    this->Dir = Dir;
}

NoArvore::NoArvore() {} // construtor padrao

int NoArvore::percorrerArvore(NoArvore* raiz, int byteProc, char* caminho, int posCaminho)
{
    if (raiz->byte == byteProc)  // chegou na folha
    {
        caminho[posCaminho] = '\0';  // termina o vetor caminho
        return 1; // achou
    }
    else
    {
        int encontrado = 0; // não achou


        if (raiz->Esq != NULL) // se tiver filho esquerdo
        {
            caminho[posCaminho] = '0';
            encontrado = percorrerArvore(raiz->Esq, byteProc, caminho, posCaminho + 1); // recursão com o filho nodo esquerdo
        }

        if (encontrado != 1 && raiz->Dir != NULL) // se tiver direita e n tiver encontrado na esquerda
        {
            caminho[posCaminho] = '1';
            encontrado = percorrerArvore(raiz->Dir, byteProc, caminho, posCaminho + 1); // se tive
        }
        if (encontrado != 1) // se for uma folha mas n for a folha procurada
        {
            caminho[posCaminho] = '\0'; // finaliza
        }
        return encontrado;
    }
}
int NoArvore::Altura(NoArvore* noAtual) const
{
    int alturaEsquerda,
        alturaDireita;
    if (noAtual == NULL)
        return 0;
    alturaEsquerda = Altura(noAtual->Esq);  //Recursão para contar o lado esquerdo desse nó
    alturaDireita = Altura(noAtual->Dir);   //Recursão para contar o lado direito desse nó
    if (alturaEsquerda >= alturaDireita)
        return 1 + alturaEsquerda;          //Se a árvore for 'desbalanceada', retorna o maior valor (vale pra essa linha e pra debaixo)
    return 1 + alturaDireita;
}


int NoArvore::getByte()
{
    return this->byte;
}

int NoArvore::getFreq()
{
    return this->freq;
}

NoArvore* NoArvore::getEsq()
{
    return this->Esq;
}

NoArvore* NoArvore::getDir()
{
    return this->Dir;
}

void NoArvore::setByte(int byte)
{
    this->byte = byte;
}

void NoArvore::setFreq(int freq)
{
    this->freq = freq;
}

void NoArvore::setEsq(NoArvore* esq)
{
    this->Esq = esq;
}
void NoArvore::setDir(NoArvore* dir)
{
    this->Dir = dir;
}

