
#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

typedef struct {
    int *elementos;   
    int tamanhoTotal; // Capacidade alocada 
    int qtdAtual;     // Quantidade de números já inseridos logicamente
} EstruturaAuxiliar;

EstruturaAuxiliar vetorPrincipal[TAM];

// (1 a 10)
int ehPosicaoValida(int posicao) {
    if (posicao < 1 || posicao > 10) {
        return POSICAO_INVALIDA;
    }
    return SUCESSO;
}

void inicializar() {
    for (int i = 0; i < TAM; i++) {
        vetorPrincipal[i].elementos = NULL;
        vetorPrincipal[i].tamanhoTotal = 0;
        vetorPrincipal[i].qtdAtual = 0;
    }
}

int criarEstruturaAuxiliar(int posicao, int tamanho) {
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;

    if (tamanho < 1)
        return TAMANHO_INVALIDO;

    int indice = posicao - 1; 

    if (vetorPrincipal[indice].elementos != NULL)
        return JA_TEM_ESTRUTURA_AUXILIAR;

    vetorPrincipal[indice].elementos = (int *)malloc(tamanho * sizeof(int));
    
    if (vetorPrincipal[indice].elementos == NULL)
        return SEM_ESPACO_DE_MEMORIA;

    vetorPrincipal[indice].tamanhoTotal = tamanho;
    vetorPrincipal[indice].qtdAtual = 0;

    return SUCESSO;
}

int inserirNumeroEmEstrutura(int posicao, int valor) {
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;

    int indice = posicao - 1;

    if (vetorPrincipal[indice].elementos == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    // Se a quantidade atual chegou no limite do tamanho, não cabe mais
    if (vetorPrincipal[indice].qtdAtual >= vetorPrincipal[indice].tamanhoTotal)
        return SEM_ESPACO;

    // Insere na próxima posição livre e aumenta o contador
    int posLivre = vetorPrincipal[indice].qtdAtual;
    vetorPrincipal[indice].elementos[posLivre] = valor;
    vetorPrincipal[indice].qtdAtual++;

    return SUCESSO;
}

int excluirNumeroDoFinaldaEstrutura(int posicao) {
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;

    int indice = posicao - 1;

    if (vetorPrincipal[indice].elementos == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    if (vetorPrincipal[indice].qtdAtual == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    
    vetorPrincipal[indice].qtdAtual--;

    return SUCESSO;
}

int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;

    int indice = posicao - 1;

    if (vetorPrincipal[indice].elementos == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    if (vetorPrincipal[indice].qtdAtual == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    int achou = 0;
    int indexRemover = -1;

    
    for (int i = 0; i < vetorPrincipal[indice].qtdAtual; i++) {
        if (vetorPrincipal[indice].elementos[i] == valor) {
            achou = 1;
            indexRemover = i;
            break; 
        }
    }

    if (!achou)
        return NUMERO_INEXISTENTE;


    for (int i = indexRemover; i < vetorPrincipal[indice].qtdAtual - 1; i++) {
        vetorPrincipal[indice].elementos[i] = vetorPrincipal[indice].elementos[i + 1];
    }

  
    vetorPrincipal[indice].qtdAtual--;

    return SUCESSO;
}

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;

    int indice = posicao - 1;

    if (vetorPrincipal[indice].elementos == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

   
    for (int i = 0; i < vetorPrincipal[indice].qtdAtual; i++) {
        vetorAux[i] = vetorPrincipal[indice].elementos[i];
    }

    return SUCESSO;
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
  
    int retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);
    if (retorno != SUCESSO)
        return retorno;

    int indice = posicao - 1;
    int qtd = vetorPrincipal[indice].qtdAtual;


    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - 1 - i; j++) {
            if (vetorAux[j] > vetorAux[j + 1]) {
                int temp = vetorAux[j];
                vetorAux[j] = vetorAux[j + 1];
                vetorAux[j + 1] = temp;
            }
        }
    }

    return SUCESSO;
}

int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int cont = 0; 
    
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].elementos != NULL) {
            for (int j = 0; j < vetorPrincipal[i].qtdAtual; j++) {
                vetorAux[cont] = vetorPrincipal[i].elementos[j];
                cont++;
            }
        }
    }

    if (cont == 0)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

    return SUCESSO;
}

int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int retorno = getDadosDeTodasEstruturasAuxiliares(vetorAux);
    if (retorno == TODAS_ESTRUTURAS_AUXILIARES_VAZIAS)
        return retorno;

    
    int cont = 0;
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].elementos != NULL) {
            cont += vetorPrincipal[i].qtdAtual;
        }
    }

    
    for (int i = 0; i < cont - 1; i++) {
        for (int j = 0; j < cont - 1 - i; j++) {
            if (vetorAux[j] > vetorAux[j + 1]) {
                int temp = vetorAux[j];
                vetorAux[j] = vetorAux[j + 1];
                vetorAux[j + 1] = temp;
            }
        }
    }

    return SUCESSO;
}

int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;

    int indice = posicao - 1;

    if (vetorPrincipal[indice].elementos == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    
    int tamanhoFinal = vetorPrincipal[indice].tamanhoTotal + novoTamanho;

    if (tamanhoFinal < 1)
        return NOVO_TAMANHO_INVALIDO;

 
    int *novoArray = (int *)realloc(vetorPrincipal[indice].elementos, tamanhoFinal * sizeof(int));
    if (novoArray == NULL)
        return SEM_ESPACO_DE_MEMORIA;

    vetorPrincipal[indice].elementos = novoArray;
    vetorPrincipal[indice].tamanhoTotal = tamanhoFinal;

  
    if (vetorPrincipal[indice].qtdAtual > tamanhoFinal) {
        vetorPrincipal[indice].qtdAtual = tamanhoFinal;
    }

    return SUCESSO;
}

int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
        return POSICAO_INVALIDA;

    int indice = posicao - 1;

    if (vetorPrincipal[indice].elementos == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    if (vetorPrincipal[indice].qtdAtual == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    return vetorPrincipal[indice].qtdAtual;
}

No *montarListaEncadeadaComCabecote() {

    No *cabecote = (No *)malloc(sizeof(No));
    if (cabecote == NULL) return NULL;
    cabecote->prox = NULL;
    
    No *atual = cabecote;
    int temElemento = 0; 

    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].elementos != NULL) {
            for (int j = 0; j < vetorPrincipal[i].qtdAtual; j++) {
                
                No *novo = (No *)malloc(sizeof(No));
                novo->conteudo = vetorPrincipal[i].elementos[j];
                novo->prox = NULL;
                
                atual->prox = novo;
                atual = novo; 
                temElemento = 1;
            }
        }
    }

   
    if (!temElemento) {
        free(cabecote);
        return NULL;
    }

    return cabecote;
}

void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
    if (inicio == NULL) return;

  
    No *atual = inicio->prox;
    int i = 0;
    while (atual != NULL) {
        vetorAux[i] = atual->conteudo;
        atual = atual->prox;
        i++;
    }
}

void destruirListaEncadeadaComCabecote(No **inicio) {
    if (inicio == NULL || *inicio == NULL) return;

    No *atual = *inicio;
    No *prox;

 
    while (atual != NULL) {
        prox = atual->prox;
        free(atual);
        atual = prox;
    }

    *inicio = NULL;
}

void finalizar() {
    // Garante o nao vazamento de memória liberando tudo
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i].elementos != NULL) {
            free(vetorPrincipal[i].elementos);
            vetorPrincipal[i].elementos = NULL;
            vetorPrincipal[i].tamanhoTotal = 0;
            vetorPrincipal[i].qtdAtual = 0;
        }
    }
}

void dobrar(int *x) {
    // Recebe o endereço e dobra o valor contido na memória apontada
    *x = (*x) * 2;
}