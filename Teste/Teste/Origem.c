#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <limits.h>
#include <inttypes.h>
#include <string.h>

//Fun��o utilizada nos testes para printar os bits de cada byte
void printBits(char num)
{
    for (int i = 7; 0 <= i; i--) {
        printf("%c", (num & (1 << i)) ? '1' : '0');
    }
    printf("\n");
}

typedef struct NoArvore
{
    int byte;
    int freq;
    struct NoArvore* Esq;
    struct NoArvore* Dir;
} NoArvore;

NoArvore* criarNoArvore(int byte, int freq, struct NoArvore* Esq, struct NoArvore* Dir)
{
    struct NoArvore* no = (struct NoArvore*)malloc(sizeof(struct NoArvore));
    no->byte = byte;
    no->freq = freq;
    no->Esq = Esq;
    no->Dir = Dir;
    return no;
}

// percorrer �rvore para fazer o c�digo de cada byte
int percorrerArvore(struct NoArvore* raiz, int byteProc, char* caminho, int posCaminho)
{
    if (raiz->byte == byteProc)  // chegou na folha
    {
        caminho[posCaminho] = '\0';  // termina o vetor caminho
        return 1; // achou
    }
    else
    {
        int encontrado = 0; // n�o achou


        if (raiz->Esq != NULL) // se tiver filho esquerdo
        {
            caminho[posCaminho] = '0';
            encontrado = percorrerArvore(raiz->Esq, byteProc, caminho, posCaminho + 1); // recurs�o com o filho nodo esquerdo
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

const int Altura(NoArvore* noAtual)
{
    int alturaEsquerda,
        alturaDireita;
    if (noAtual == NULL)
        return 0;
    alturaEsquerda = Altura(noAtual->Esq);  //Recurs�o para contar o lado esquerdo desse n�
    alturaDireita = Altura(noAtual->Dir);   //Recurs�o para contar o lado direito desse n�
    if (alturaEsquerda >= alturaDireita)
        return 1 + alturaEsquerda;          //Se a �rvore for 'desbalanceada', retorna o maior valor (vale pra essa linha e pra debaixo)
    return 1 + alturaDireita;
}

//Structs Lista e No da Lista
typedef struct NodoDeListaLigada {
    NoArvore* info; // ponteiro de nodo de arvore
    struct NodoDeListaLigada* prox;
}  NodoDeListaLigada;

struct NodoDeListaLigada* criarNoDeListaLigada(struct NoArvore* noArvore) {
    struct NodoDeListaLigada* noLista = (struct NodoDeListaLigada*)malloc(sizeof(struct NodoDeListaLigada));
    noLista->info = noArvore;
    noLista->prox = NULL;
    return noLista;
}

typedef struct ListaLigada {
    NodoDeListaLigada* primeiro, * ultimo;
} ListaLigada;


struct NodoDeListaLigada* Insira(struct NodoDeListaLigada* NodoLista, struct NodoDeListaLigada* Inicio, struct ListaLigada* Lista)
{
    if (Inicio == NULL) // insere No in�cio
    {
        Inicio = NodoLista;
        Lista->primeiro = Inicio;
        return Inicio;
    }
    else if (NodoLista->info->freq < Inicio->info->freq) // se a frequ�ncia do NodoLista for menor que a do Inicio
    {
        struct NodoDeListaLigada* Novo = (struct NodoDeListaLigada*)malloc(sizeof(struct NodoDeListaLigada));
        Novo = NodoLista;       //Armazena o NodoLista na posi��o criada acima
        Novo->prox = Inicio;    //Transforma o Inicio no n� seguinte ao criado acima
        Lista->primeiro = Novo;
        return Novo;
    }
    else
    {
        Inicio->prox = Insira(NodoLista, Inicio->prox, Lista);
        Lista->primeiro = Inicio;
        return Inicio;
    }
}

struct NodoDeListaLigada* Remova(struct NodoDeListaLigada* NodoRemover, struct NodoDeListaLigada* Inicio, struct ListaLigada* Lista)
{
    if (Inicio == NULL)
        return Inicio;

    else if (NodoRemover->info->byte == Inicio->info->byte)
    {
        struct NodoDeListaLigada* Removido = Inicio;
        Inicio = Inicio->prox;
        Lista->primeiro = Inicio;
        free(Removido);  //Libera a posi��o de Removido da mem�ria
        return Inicio;
    }
    else
    {
        Inicio->prox = Remova(NodoRemover, Inicio->prox, Lista);  //Usando recurs�o, atualiza o valor de �nicio para uma nova compara��o
        Lista->primeiro = Inicio;  //Transforma o Inicio no primeiro da Lista
        return Inicio;
    }

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

    printf("-----------------------------------------------------\n"); fflush(stdout);
    printf("Giovana Mendon�a Zambanini                      20728\n"); fflush(stdout);
    printf("Isabela Clementino Ponciano Ferreira            20138\n"); fflush(stdout);
    printf("Milena Furuta Shishito                          20148\n"); fflush(stdout);
    printf("Pedro Henrique Perez Dias                       20152\n"); fflush(stdout);
    printf("-----------------------------------------------------\n"); fflush(stdout);
    printf("Bem-vindo(a)!"); fflush(stdout);
    while (opcao != 'F' && opcao != 'f')
    {
        printf("\n\nSelecione a tarefa que deseja realizar:\n"); fflush(stdout);
        printf("[C] Compactar\n"); fflush(stdout);
        printf("[D] Descompactar\n"); fflush(stdout);
        printf("[F] Fim\n"); fflush(stdout);
        printf("Digite aqui sua resposta: "); fflush(stdout);
        scanf_s(" %c", &opcao); fflush(stdin);
        opcao = toupper(opcao);
        
        switch (opcao)
        {
        case 'C':
            printf("\n            C O M P A C T A R \n\n");
            fflush(stdout);
            printf("Digite aqui o nome do arquivo a ser compactado (Ex: arq.txt): \n");
            fflush(stdout);
            scanf_s("%30s", nomeArq, sizeof(nomeArq)); // pega o nome do arquivo
            fflush(stdin);
            //printf("%s\n", nomeArq);
            //fflush(stdout);   
            fopen_s(&arqLer, nomeArq, "rb"); // Ler arquivo selecionado

            //Adiciona _.huff ao nome do arquivo, para indica q � um arquivo compactado 
            strcat_s(nomeArq, (strlen(nomeArq) + sizeof("._huff")), "_.huff\0");
            //printf("%s", nomeArq);
            //fflush(stdout);

            fopen_s(&arqCompactar, nomeArq, "wb"); //Criar arquivo para compactar
            if (arqLer == NULL) // Se n�o conseguiu achar o arquivo para leitura
            {
                printf("[ERROR] Problemas em ENCONTRAR o arquivo selecionado\n\n");
                fflush(stdout);
                break;
            }

            // calcula o tamanho do arquivo
            fseek(arqLer, 0L, SEEK_END);
            sizeArq = ftell(arqLer);
            fseek(arqLer, 0, SEEK_SET);

            // cria e escreve a quantidade de bits a serem desprezados que inicialmente � 0
            unsigned char qtdBitsDesprez = 0;
            fwrite(&qtdBitsDesprez, sizeof(unsigned char), 1, arqCompactar);

            unsigned int tbFreq[256]; // tabela de frequencia de bytes.
            for (int pos = 0; pos <= 255; pos++) { tbFreq[pos] = 0; } // zera as posi��es da tabela de freq

            //printf("\n--tabela de frequencia--\n\n");
            //fflush(stdout);
            unsigned char c = NULL;
            while (fread(&c, sizeof(unsigned char), 1, arqLer)) // l� char por char do arquivo
            {
                tbFreq[c]++;
                //printf("Byte: %d  \tFrequencia: %d\n", c, tbFreq[c]);
                //fflush(stdout);
            }

            //Criacao da Fila de prioridades
            struct ListaLigada* lista = (struct ListaLigada*)malloc(sizeof(struct ListaLigada));
            lista->primeiro = NULL;
            lista->ultimo = NULL;

            for (int i = 0; i < 256; i++) {

                ///printa a tabela de frequencia no novo arq
                fwrite(&i, sizeof(unsigned int), 1, arqCompactar);
                fwrite(&tbFreq[i], sizeof(unsigned int), 1, arqCompactar);

                if (tbFreq[i] != 0) { // insere os bytes com freq > 0 na lista de prioridade
                    Insira(criarNoDeListaLigada(criarNoArvore(i, tbFreq[i], NULL, NULL)), lista->primeiro, lista);
                }
            }

            //Print da lista ligada
            //printf("\n--lista ordenada--\n\n");
            fflush(stdout);
            struct NodoDeListaLigada* no = lista->primeiro;
            while (no != NULL) {
                //printf("%d :\t%d\n", no->info->byte, no->info->freq);
                fflush(stdout);
                no = no->prox;
            }

            //Construcao da arvore a partir da fila de prioridades
            while (lista->primeiro->prox != NULL) // enquanto tiver dois ou mais nodos
            {
                no = criarNoDeListaLigada(criarNoArvore(257, NULL, NULL, NULL));

                no->info->Esq = lista->primeiro->info; // esquerda
                Remova(lista->primeiro, lista->primeiro, lista);

                no->info->Dir = lista->primeiro->info; // direita
                Remova(lista->primeiro, lista->primeiro, lista);

                no->info->freq = no->info->Esq->freq + no->info->Dir->freq;
                Insira(no, lista->primeiro, lista);  // frequencia
            }

            // tirando a �rvore da lista
            struct NoArvore* raiz = criarNoArvore(no->info->byte, no->info->freq, no->info->Esq, no->info->Dir);
            Remova(lista->primeiro, lista->primeiro, lista);

            // compactando a o arquivo...
            fseek(arqLer, 0, SEEK_SET);     // volta no come�o do arq de leitura
            unsigned char aux = NULL;
            int tamanhoArvore = Altura(raiz);
            int tamanhoCodigo = (tamanhoArvore * sizeof(char)) + 1;
            char* codigoHuffman = (char*)malloc(tamanhoCodigo); //Criado a partir do tamanho da �rvore, para n�o ocupar mem�ria desnecess�ria

            printf("\n--compactando bytes--\n\n");
            fflush(stdout);
            printf("%d -- ALTURA, %d -- TAMANHO CHAR, %d -- TAMANHO CODIGO\n", tamanhoArvore, sizeof(char), sizeof(codigoHuffman));
            fflush(stdout);
            int tamanhoByte = 0;
            unsigned char auxiliar = 0;

            //l� char a char do arqLer e compacta cada byte
            while (fread(&aux, sizeof(unsigned char), 1, arqLer))
            {
                strcpy_s(codigoHuffman, sizeof(codigoHuffman), "");
                int posCaminho = 0;
                if (tbFreq[aux] != 0) {
                    percorrerArvore(raiz, aux, codigoHuffman, posCaminho); // guarda o caminho da raiz at� a folha no codigoHuffman

                    //printf("%s -- CODIGO\n", codigoHuffman)    
                    //alteracao
                    for (int pos = 0; pos < strlen(codigoHuffman); pos++) // percorre o codigoHuffman
                    {
                        if (codigoHuffman[pos] == '1')
                        {
                            // auxiliar = 00000000
                            // 1        = 00000001   
                            auxiliar = auxiliar | (1 << (7 - (tamanhoByte % 8))); // move o 1 para a posi��o no codigoHuffman
                            //printf("AUXILIAR ATUALIZADO");
                            //printBits(auxiliar);
                        }
                        tamanhoByte++;
                        if (tamanhoByte % 8 == 0) // formou um byte!!!!
                        {
                            //printf("\nFORMOU UM BYTE: %d ---- ", auxiliar);
                            //printBits(auxiliar);
                            fwrite(&auxiliar, sizeof(unsigned char), 1, arqCompactar);
                            auxiliar = 0;
                        }
                    }
                    //printf("Byte: %d\tCodigo: %s\tLenght: %d\n", aux, codigoHuffman, strlen(codigoHuffman));
                    //fflush(stdout);
                }
            }
            printBits(auxiliar);
            printf("---- numero com desprezados");
            qtdBitsDesprez = tamanhoByte % 8;
            fwrite(&auxiliar, 1, 1, arqCompactar); // ESCREVE O ULTIMO 
            fseek(arqCompactar, 0, SEEK_SET);      // volta pro come�o do arquivo
            fwrite(&qtdBitsDesprez, sizeof(unsigned char), 1, arqCompactar); // reescreve o qtdBitsDesprez

            printf("\n. . .SUCESSO!!!\n");
            fflush(stdout);
            free(lista);
            free(codigoHuffman);
            fclose(arqCompactar);
            fclose(arqLer);
            break;

        case 'D':
            printf("\n            D E S C O M P A C T A R \n\n");
            fflush(stdout);

            printf("Digite aqui o nome do arquivo a ser descompactado (Ex: arq.txt.huff): \n");
            fflush(stdout);
            scanf_s("%55s", nomeArqCompac, sizeof(nomeArqCompac));
            char* nomeArqDescompac;
            fopen_s(&arqCompactar, nomeArqCompac, "rb");
            printf("%s", nomeArqCompac);
            fflush(stdout);

            //Remove o _.huff 
            char* next_token1 = NULL;
            nomeArqDescompac = strtok_s(nomeArqCompac, "_", &next_token1);

            //printf("%s", nomeArqDescompac);
            //fflush(stdout);

            fopen_s(&arqDescompactar, nomeArqDescompac, "wb");
            if (arqCompactar == NULL) // Se arquivo a ser descompactado n�o existir
            {
                printf("[ERROR] Problemas em ENCONTRAR o arquivo selecionado\n\n");
                fflush(stdout);
                return;
            }

            //calcula o size do arquivo
            fseek(arqCompactar, 0L, SEEK_END);
            sizeArq = ftell(arqCompactar);
            fseek(arqCompactar, 0, SEEK_SET);

            struct ListaLigada* lis = (struct ListaLigada*)malloc(sizeof(struct ListaLigada));
            lis->primeiro = NULL;
            lis->ultimo = NULL;

            //L� o n�mero que indica a qtdd de bits desprezados, que est�o no �nicio do arquivo
            unsigned char desprezado;
            fread(&desprezado, sizeof(unsigned char), 1, arqCompactar);

            //printf("\n--tabela de frequencia--\n\n");
            //fflush(stdout);
            unsigned int ch = NULL;
            unsigned int f = 0;
            for (int i = 0; i < 256; i++) // cria a tabela freq 
            {
                fread(&ch, sizeof(unsigned int), 1, arqCompactar); // byte
                fread(&f, sizeof(unsigned int), 1, arqCompactar); //freq
                if (f != 0) { // os bytes q tem freq > 0 s�o inseridos na arvore
                    Insira(criarNoDeListaLigada(criarNoArvore(ch, f, NULL, NULL)), lis->primeiro, lis);
                    /*printf("Byte: %d", ch);
                    fflush(stdout);
                    printf("\tFrequencia: %d\n", f);
                    fflush(stdout);*/
                }
            }

            //Print da lista ligada
            //printf("\n--lista ordenada--\n\n");
            //fflush(stdout);
            struct NodoDeListaLigada* n = lis->primeiro;
            //while (n != NULL) {
               // printf("%d :\t%d\n", n->info->byte, n->info->freq);
               // fflush(stdout);
               // n = n->prox;
            //}

            //Constru��o da arvore a partir da fila de prioridades
            while (lis->primeiro->prox != NULL) // enquanto tiver dois ou mais nodos
            {
                n = criarNoDeListaLigada(criarNoArvore(NULL, NULL, NULL, NULL));

                n->info->Esq = lis->primeiro->info; // esquerda
                Remova(lis->primeiro, lis->primeiro, lis);

                n->info->Dir = lis->primeiro->info; // direita
                Remova(lis->primeiro, lis->primeiro, lis);

                n->info->freq = n->info->Esq->freq + n->info->Dir->freq;
                Insira(n, lis->primeiro, lis);  // frequencia
            }

            //cria um n� de �rvore a partir do �ltimo n� da lista
            struct NoArvore* r = criarNoArvore(n->info->byte, n->info->freq, n->info->Esq, n->info->Dir);
            unsigned char bit = 0;
            aux = 0;
            int posContraria = 1;
            int posAtual = ftell(arqCompactar); //Pega a posi��o atual do cursor

            //Leitura de todo o arquivo, menos o ultimo byte, devido aos bits desprezados
            while (fread(&bit, sizeof(unsigned char), 1, arqCompactar) && posAtual < (sizeArq - 1))
            {
                //printBits(bit);
                //printf("\n");
                //posContraria = 0;
                for (int pos = 7, posContraria = 0; pos >= 0; pos--, posContraria++)
                {
                    aux = (bit << posContraria); // bit vai para a primeira pos do byte (apaga os bits anteriores ao bit atual)
                    //printBits(aux);
                    aux = (aux >> 7); // bit vai para a ultima posi��o do byte (apaga os bits depois do byte)
                    //printBits(aux);

                    if (aux == 0)
                        r = r->Esq;
                    else if (aux == 1)
                        r = r->Dir;

                    if (r->Esq == NULL && r->Dir == NULL) {
                        //printf("%c", r->byte);
                        //fflush(stdout);
                        fwrite(&r->byte, sizeof(unsigned char), 1, arqDescompactar); //achou folha
                        r = lis->primeiro->info;
                    }
                }
                posAtual = ftell(arqCompactar); //Atualiza posAtual com o valor do cursor, para fazer a compara��o no while
            }

            //leitura do ultimo byte, que possui bits a serem desprezados
            aux = 0;
            fread(&bit, sizeof(unsigned char), 1, arqCompactar);
            for (int pos = 7, posContraria = 0; pos >= 0 && posContraria < desprezado; pos--, posContraria++)
            {
                aux = (bit << posContraria); // bit vai para a primeira pos do byte (apaga os bits anteriores ao bit atual)
                //printBits(aux);
                aux = (aux >> 7); // bit vai para a ultima posi��o do byte (apaga os bits depois do byte)
                //printBits(aux);

                if (aux == 0)
                    r = r->Esq;
                else if (aux == 1)
                    r = r->Dir;

                if (r->Esq == NULL && r->Dir == NULL) {
                    fwrite(&r->byte, sizeof(unsigned char), 1, arqDescompactar);
                    r = lis->primeiro->info;
                }
            }

            printf("\n. . .SUCESSO!!!\n");
            fflush(stdout);
            free(lis);
            fclose(arqDescompactar);
            fclose(arqCompactar);
            break;

        case 'F':
            printf("\n. . .Obrigado por utilizar esse programa!!!\n");
            fflush(stdout);
            break;
        default:
            break;
        }
    }


    return 0;
}