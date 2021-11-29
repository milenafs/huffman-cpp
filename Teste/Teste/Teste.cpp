#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>
#include <iostream>
#include "ListaLigada.h"
#include "NodoDeListaLigada.h"
#include "NoArvore.h"
#include "Arvore.h"

int main()
{
	

	NoArvore* na1 = new NoArvore(32, 2, NULL, NULL);
	NoArvore* na2 = new NoArvore(40, 1, NULL, NULL);
	NoArvore* na3 = new NoArvore(50, 3, NULL, NULL);
	NoArvore* na4 = new NoArvore(40, 1, NULL, NULL);
	na1->setEsq(na2);
	na1->setDir(na3);
	na3->setEsq(na4);
	Arvore* a = new Arvore(na1);
	std::cout << "conferir arvore";

	NodoDeListaLigada* no1 = new NodoDeListaLigada();
	no1->setInfo(na1);
	NodoDeListaLigada* no2 = new NodoDeListaLigada();
	no2->setInfo(na1);
	no1->setProx(no2);
	ListaLigada* li = new ListaLigada();
	li->setPrimeiro(no1);

	ListaLigada* li2 = new ListaLigada();
	li2->setPrimeiro(no1);
	std::cout << "conferir lista";

	if (na2 == na4)
		std::cout << "NOS DE ARVORE IGUAIS FUNCIONANDO\n";

	if(no1 != no1)
		std::cout << "NOS DE LISTA IGUAIS FUNCIONANDO\n";

	if(li == li2)
		std::cout << "LISTAS IGUAIS FUNCIONANDO\n";

	
	delete a;
	delete li;
	//delete li2;
	std::cout << "conferir deletes";

}