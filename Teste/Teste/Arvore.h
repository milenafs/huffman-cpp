#ifndef ARVORE
#define ARVORE
#include "NoArvore.h"
class Arvore
{
private:
    NoArvore* raiz;
public:
    Arvore();
    Arvore(NoArvore* );
    ~Arvore();
    int operator== (const Arvore&);
    int operator!= (const Arvore&);
    int Comparar(NoArvore* , NoArvore* );
    void Descarte(NoArvore* );
    int percorrerArvore(NoArvore* , int, char*, int); //Sera mudada na origem
    int Altura(NoArvore* ) const;
    NoArvore* getRaiz();
    void setRaiz(NoArvore* );

};
#endif
