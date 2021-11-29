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
        NoArvore(int , int , NoArvore* ,  NoArvore* );
        NoArvore();

        int operator== (const NoArvore&);
        int operator!= (const NoArvore&);
        int getByte();
        int getFreq();
        NoArvore* getEsq();
        NoArvore* getDir();
        void setByte(int );
        void setFreq(int );
        void setEsq(NoArvore* );
        void setDir(NoArvore* );
       
};
#endif
