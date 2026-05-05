#include <stdio.h>
#include <stdlib.h>
#include "minhabib.h"

void imprimir_nos_internos(No *raiz)
{
    if (raiz == NULL)
        return;
    if (raiz->esq != NULL || raiz->dir != NULL)
    {
        printf("\nNo: %-3d | End: %p ", raiz->valor, (void *)raiz);
    }
    imprimir_nos_internos(raiz->esq);
    imprimir_nos_internos(raiz->dir);
}

void imprimir_folhas(No *raiz)
{
    if (raiz == NULL)
        return;
    if (raiz->esq == NULL && raiz->dir == NULL)
    {
        printf("\nNo: %-3d | End: %p ", raiz->valor, (void *)raiz);
    }
    imprimir_folhas(raiz->esq);
    imprimir_folhas(raiz->dir);
}

void imprimir_niveis(No *raiz, int nivel_alvo)
{
    if (raiz == NULL)
        return;
    if (nivel_alvo == 0)
    {
        printf("%d ", raiz->valor);
    }
    else
    {
        imprimir_niveis(raiz->esq, nivel_alvo - 1);
        imprimir_niveis(raiz->dir, nivel_alvo - 1);
    }
}

int calcular_altura(No *no)
{
    if (no == NULL)
        return -1;
    int altEsq = calcular_altura(no->esq);
    int altDir = calcular_altura(no->dir);
    return (altEsq > altDir ? altEsq : altDir) + 1;
}

int calcular_profundidade(No *raiz, int valor, int prof_atual)
{
    if (raiz == NULL)
        return -1;
    if (raiz->valor == valor)
        return prof_atual;

    if (valor < raiz->valor)
        return calcular_profundidade(raiz->esq, valor, prof_atual + 1);
    else
        return calcular_profundidade(raiz->dir, valor, prof_atual + 1);
}

void imprimir_ancestrais(No *raiz, int valor)
{
    if (raiz == NULL || raiz->valor == valor)
        return;
    printf("%d ", raiz->valor);
    if (valor < raiz->valor)
        imprimir_ancestrais(raiz->esq, valor);
    else
        imprimir_ancestrais(raiz->dir, valor);
}

void imprimir_descendentes(No *no)
{
    if (no == NULL)
        return;
    if (no->esq != NULL)
    {
        printf("%d ", no->esq->valor);
        imprimir_descendentes(no->esq);
    }
    if (no->dir != NULL)
    {
        printf("%d ", no->dir->valor);
        imprimir_descendentes(no->dir);
    }
}

void analisar_arvore(No *raiz, int valorBusca)
{
    if (raiz == NULL)
        return;

    printf("\n--- DIAGNOSTICO GERAL ---\n");
    printf("Raiz: %d\n", raiz->valor, (void *)raiz);

    printf("Nos Internos: ");
    imprimir_nos_internos(raiz);

    printf("\nFolhas: ");
    imprimir_folhas(raiz);

    printf("\nExibicao por Niveis:\n");
    int h = calcular_altura(raiz);
    for (int i = 0; i <= h; i++)
    {
        printf("Nivel %d: ", i);
        imprimir_niveis(raiz, i);
        printf("\n");
    }

    No *atual = raiz;
    while (atual != NULL && atual->valor != valorBusca)
    {
        if (valorBusca < atual->valor)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    if (atual != NULL)
    {
        printf("\n--- DIAGNOSTICO ESPECIFICO (No %d) ---\n", valorBusca);

        int grau = (atual->esq != NULL) + (atual->dir != NULL);
        printf("Grau: %d\n", grau);

        printf("Ancestrais: ");
        imprimir_ancestrais(raiz, valorBusca);

        printf("\nDescendentes: ");
        imprimir_descendentes(atual);

        printf("\nAltura: %d", calcular_altura(atual));
        printf("\nProfundidade: %d", calcular_profundidade(raiz, valorBusca, 0));

        printf("\n\n--- SUB-ARVORE (Extracao) ---\n");
        int hSub = calcular_altura(atual);
        for (int i = 0; i <= hSub; i++)
        {
            imprimir_niveis(atual, i);
            printf("\n");
        }
    }
    else
        printf("\nValor %d nao encontrado na arvore.\n", valorBusca);
}