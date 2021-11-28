#ifndef NOARVORE
#define NOARVORE

class NoArvore
{
    private:
        int byte;
        int freq;
        NoArvore* Esq;
        NoArvore* Dir;
    public:
        NoArvore(int byte, int freq, NoArvore* Esq,  NoArvore* Dir);
        NoArvore();
        ~NoArvore();
        void Descarte(NoArvore* noAtual);
        int percorrerArvore(NoArvore* raiz, int byteProc, char* caminho, int posCaminho);
        int Altura(NoArvore* noAtual) const;
        int getByte();
        int getFreq();
        NoArvore* getEsq();
        NoArvore* getDir();
        void setByte(int byte);
        void setFreq(int freq);
        void setEsq(NoArvore* esq);
        void setDir(NoArvore* dir);
       
};
#endif
