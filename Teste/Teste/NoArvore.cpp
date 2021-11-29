#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "NoArvore.h"

NoArvore::NoArvore() {} // construtor padrao

NoArvore::NoArvore(int byte, int freq, NoArvore* esq, NoArvore* dir):
    byte(byte),freq(freq),Esq(esq),Dir(dir){}


int NoArvore::operator==(const NoArvore &n) 
{
    if (this->byte != n.byte) return 0;
    if (this->freq != n.freq) return 0;
    if (this->Esq != n.Esq) return 0;
    if (this->Dir != n.Dir) return 0;
    return 1;
}

int NoArvore::operator!= (const NoArvore &n) 
{
    if (*this == n)
        return 0;
    return 1;
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

