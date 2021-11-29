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

//Função utilizada nos testes para printar os bits de cada byte
void printBits(char num)
{
    for (int i = 7; 0 <= i; i--) {
        std::cout << (num & (1 << i)) ? '1' : '0';
    }
    std::cout << "\n";
}


int main()
{
    char opcao = 'C';
    char nomeArq[57];
    strcpy_s(nomeArq, sizeof(nomeArq), "");
    char nomeArqCompac[56];
    strcpy_s(nomeArqCompac, sizeof(nomeArqCompac), "");
    int sizeArq = 0;
    FILE* arqLer = NULL;
    FILE* arqCompactar = NULL;
    FILE* arqDescompactar = NULL;


    //visual studio recomenda uso std, meio q força, pois dá preferencia std, senão dá erro!!
    std::cout << "-----------------------------------------------------\n"
        << "Giovana Mendonça Zambanini                      20728\n"
        << "Isabela Clementino Ponciano Ferreira            20138\n"
        << "Milena Furuta Shishito                          20148\n"
        << "Pedro Henrique Perez Dias                       20152\n"
        << "-----------------------------------------------------\n"
        << "Bem-vindo(a)!";
    while (opcao != 'F' && opcao != 'f')
    {
        std::cout << "\n\nSelecione a tarefa que deseja realizar:\n"
            << "[C] Compactar\n"
            << "[D] Descompactar\n"
            << "[F] Fim\n"
            << "Digite aqui sua resposta: ";
        std::cin >> opcao;
        opcao = toupper(opcao);
        
        switch (opcao)
        {
            case 'C':
            {
                std::cout << "\n            C O M P A C T A R \n\n"
                    << "Digite aqui o nome do arquivo a ser compactado (Ex: arq.txt): \n";
                std::cin >> nomeArq; // pega o nome do arquivo

                fopen_s(&arqLer, nomeArq, "rb"); // Ler arquivo selecionado
                //Adiciona _.huff ao nome do arquivo, para indica q é um arquivo compactado 
                strcat_s(nomeArq, (strlen(nomeArq) + sizeof("._huff")), "_.huff\0");

                fopen_s(&arqCompactar, nomeArq, "wb"); //Criar arquivo para compactar
                if (arqLer == NULL) // Se não conseguiu achar o arquivo para leitura
                {
                    std::cout << "[ERROR] Problemas em ENCONTRAR o arquivo selecionado\n\n";
                    break;
                }

                // calcula o tamanho do arquivo
                fseek(arqLer, 0L, SEEK_END);
                sizeArq = ftell(arqLer);
                fseek(arqLer, 0, SEEK_SET);

                // cria e escreve a quantidade de bits a serem desprezados que inicialmente é 0
                unsigned char qtdBitsDesprez = 0;
                fwrite(&qtdBitsDesprez, sizeof(unsigned char), 1, arqCompactar);

                unsigned int tbFreq[256]; // tabela de frequencia de bytes.
                for (int pos = 0; pos <= 255; pos++) { tbFreq[pos] = 0; } // zera as posições da tabela de freq

                unsigned char c = NULL;
                while (fread(&c, sizeof(unsigned char), 1, arqLer)) // lê char por char do arquivo
                {
                    tbFreq[c]++;
                }

                //Criacao da Fila de prioridades
                ListaLigada* lista = new ListaLigada;

                for (int i = 0; i < 256; i++) {

                    ///printa a tabela de frequencia no novo arq
                    fwrite(&i, sizeof(unsigned int), 1, arqCompactar);
                    fwrite(&tbFreq[i], sizeof(unsigned int), 1, arqCompactar);

                    if (tbFreq[i] != 0) { // insere os bytes com freq > 0 na lista de prioridade
                        NoArvore* noArvore = new NoArvore(i, tbFreq[i], NULL, NULL);
                        NodoDeListaLigada* noLista = new NodoDeListaLigada(noArvore, NULL);
                        lista->Insira(noLista, lista->getPrimeiro());
                    }
                }

                NodoDeListaLigada* no = new NodoDeListaLigada;

                //Construcao da arvore a partir da fila de prioridades
                while (lista->getPrimeiro()->getProx() != NULL) // enquanto tiver dois ou mais nodos
                {
                    NoArvore* noArvore = new NoArvore(257, NULL, NULL, NULL);
                    no = new NodoDeListaLigada(noArvore, NULL);

                    no->getInfo()->setEsq(lista->getPrimeiro()->getInfo()); // esquerda
                    lista->Remova(lista->getPrimeiro(), lista->getPrimeiro());

                    no->getInfo()->setDir(lista->getPrimeiro()->getInfo()); // direita
                    lista->Remova(lista->getPrimeiro(), lista->getPrimeiro()); //VERIFICA O REMOVA

                    no->getInfo()->setFreq(no->getInfo()->getEsq()->getFreq() + no->getInfo()->getDir()->getFreq());
                    lista->Insira(no, lista->getPrimeiro());  // frequencia
                }


                // tirando a árvore da lista
                NoArvore* raiz = new NoArvore(no->getInfo()->getByte(), no->getInfo()->getFreq(), no->getInfo()->getEsq(), no->getInfo()->getDir());
                Arvore* arv = new Arvore(raiz);
                lista->Remova(lista->getPrimeiro(), lista->getPrimeiro());

                // compactando a o arquivo...
                fseek(arqLer, 0, SEEK_SET);     // volta no começo do arq de leitura
                unsigned char aux = NULL;
                int tamanhoArvore = arv->Altura(arv->getRaiz());
                int tamanhoCodigo = (tamanhoArvore * sizeof(char)) + 1;
                char* codigoHuffman = (char*)malloc(tamanhoCodigo); //Criado a partir do tamanho da árvore, para não ocupar memória desnecessária

                int tamanhoByte = 0;
                unsigned char auxiliar = 0;

                //lê char a char do arqLer e compacta cada byte
                while (fread(&aux, sizeof(unsigned char), 1, arqLer))
                {
                    strcpy_s(codigoHuffman, sizeof(codigoHuffman), "");
                    int posCaminho = 0;
                    if (tbFreq[aux] != 0) {
                        arv->percorrerArvore(arv->getRaiz(), aux, codigoHuffman, posCaminho); // guarda o caminho da raiz até a folha no codigoHuffman

                        //alteracao
                        for (int pos = 0; pos < strlen(codigoHuffman); pos++) // percorre o codigoHuffman
                        {
                            if (codigoHuffman[pos] == '1')
                            {
                                // auxiliar = 00000000
                                // 1        = 00000001   
                                auxiliar = auxiliar | (1 << (7 - (tamanhoByte % 8))); // move o 1 para a posição no codigoHuffman
                            }
                            tamanhoByte++;
                            if (tamanhoByte % 8 == 0) // formou um byte!!!!
                            {
                                fwrite(&auxiliar, sizeof(unsigned char), 1, arqCompactar);
                                auxiliar = 0;
                            }
                        }
                    }
                }
                qtdBitsDesprez = tamanhoByte % 8;
                fwrite(&auxiliar, 1, 1, arqCompactar); // ESCREVE O ULTIMO 
                fseek(arqCompactar, 0, SEEK_SET);      // volta pro começo do arquivo
                fwrite(&qtdBitsDesprez, sizeof(unsigned char), 1, arqCompactar); // reescreve o qtdBitsDesprez

                std::cout << "\n. . .SUCESSO!!!\n";
                delete lista;
                delete no;
                delete arv;
                fclose(arqCompactar);
                fclose(arqLer);
                break;
            }
            case 'D': 
            {
                std::cout << "\n            D E S C O M P A C T A R \n\n";
                std::cout << "Digite aqui o nome do arquivo a ser descompactado (Ex: arq.txt.huff): \n";
                std::cin >> nomeArqCompac;
                char* nomeArqDescompac;
                fopen_s(&arqCompactar, nomeArqCompac, "rb");

                //Remove o _.huff 
                char* next_token1 = NULL;
                nomeArqDescompac = strtok_s(nomeArqCompac, "_", &next_token1);


                fopen_s(&arqDescompactar, nomeArqDescompac, "wb");
                if (arqCompactar == NULL) // Se arquivo a ser descompactado não existir
                {
                    std::cout << "[ERROR] Problemas em ENCONTRAR o arquivo selecionado\n\n";
                    return 1;
                }

                //calcula o size do arquivo
                fseek(arqCompactar, 0L, SEEK_END);
                sizeArq = ftell(arqCompactar);
                fseek(arqCompactar, 0, SEEK_SET);

                ListaLigada* lis = new ListaLigada;

                //Lê o número que indica a qtdd de bits desprezados, que estão no ínicio do arquivo
                unsigned char desprezado;
                fread(&desprezado, sizeof(unsigned char), 1, arqCompactar);

                unsigned int ch = NULL;
                unsigned int f = 0;
                for (int i = 0; i < 256; i++) 
                {
                    fread(&ch, sizeof(unsigned int), 1, arqCompactar); // byte
                    fread(&f, sizeof(unsigned int), 1, arqCompactar); //freq
                    if (f != 0) { // os bytes q tem freq > 0 são inseridos na arvore
                        NoArvore* noArvore = new NoArvore(ch, f, NULL, NULL);
                        NodoDeListaLigada* noLista = new NodoDeListaLigada(noArvore, NULL);
                        lis->Insira(noLista, lis->getPrimeiro());
                    }
                }

                //Print da lista ligada
                NodoDeListaLigada* n = new NodoDeListaLigada;

                //Construção da arvore a partir da fila de prioridades
                while (lis->getPrimeiro()->getProx() != NULL) // enquanto tiver dois ou mais nodos
                {
                    NoArvore* noArvore = new NoArvore(257, NULL, NULL, NULL);
                    n = new NodoDeListaLigada(noArvore, NULL);

                    n->getInfo()->setEsq(lis->getPrimeiro()->getInfo()); // esquerda
                    lis->Remova(lis->getPrimeiro(), lis->getPrimeiro());

                    n->getInfo()->setDir(lis->getPrimeiro()->getInfo()); // direita
                    lis->Remova(lis->getPrimeiro(), lis->getPrimeiro()); //VERIFICAR O REMOVA

                    n->getInfo()->setFreq(n->getInfo()->getEsq()->getFreq() + n->getInfo()->getDir()->getFreq());
                    lis->Insira(n, lis->getPrimeiro());  // frequencia
                }
               

                // tirando a árvore da lista
                NoArvore* r = new NoArvore(n->getInfo()->getByte(), n->getInfo()->getFreq(), n->getInfo()->getEsq(), n->getInfo()->getDir());
                
                
                unsigned char bit = 0;
                unsigned char aux = 0;
                int posContraria = 1;
                int posAtual = ftell(arqCompactar); //Pega a posição atual do cursor
                
                //Leitura de todo o arquivo, menos o ultimo byte, devido aos bits desprezados
                while (fread(&bit, sizeof(unsigned char), 1, arqCompactar) && posAtual < (sizeArq - 1))
                {
                    for (int pos = 7, posContraria = 0; pos >= 0; pos--, posContraria++)
                    {
                        aux = (bit << posContraria); // bit vai para a primeira pos do byte (apaga os bits anteriores ao bit atual)
                        aux = (aux >> 7); // bit vai para a ultima posição do byte (apaga os bits depois do byte)
                        
                        if (aux == 0)
                            r = r->getEsq();
                        else if (aux == 1)
                            r = r->getDir();
                        if (r->getEsq() == NULL && r->getDir() == NULL) {
                            int b = r->getByte();
                            fwrite(&b, sizeof(unsigned char), 1, arqDescompactar); //achou folha
                            r = lis->getPrimeiro()->getInfo();
                        }
                    }
                    posAtual = ftell(arqCompactar); //Atualiza posAtual com o valor do cursor, para fazer a comparação no while
                }
                //leitura do ultimo byte, que possui bits a serem desprezados
                aux = 0;
                fread(&bit, sizeof(unsigned char), 1, arqCompactar);
                for (int pos = 7, posContraria = 0; pos >= 0 && posContraria < desprezado; pos--, posContraria++)
                {
                    aux = (bit << posContraria); // bit vai para a primeira pos do byte (apaga os bits anteriores ao bit atual)
                    aux = (aux >> 7); // bit vai para a ultima posição do byte (apaga os bits depois do byte)
                    
                    if (aux == 0)
                        r = r->getEsq();
                    else if (aux == 1)
                        r = r->getDir();
                    if (r->getEsq() == NULL && r->getDir() == NULL) {
                        int b = r->getByte();
                        fwrite(&b, sizeof(unsigned char), 1, arqDescompactar); //achou folha
                        r = lis->getPrimeiro()->getInfo();
                    }
                }
                delete r;
                
                std::cout << "\n. . .SUCESSO!!!\n";
                delete lis;
                
                
                
                fclose(arqDescompactar);
                fclose(arqCompactar);
                break;

            }
            case 'F':
            {
                std::cout << "\n. . .Obrigado por utilizar esse programa!!!\n";
                break;
            }
            default: 
            {
                break;
            }
        }
    }
    return 0;
}