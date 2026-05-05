#include <stdio.h>
#include <stdlib.h>
#include "minhabib.h"

No *inserir(No *raiz, int valor)
{
    if (raiz == NULL)
    {
        No *novo = (No *)malloc(sizeof(No));
        novo->valor = valor;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else
        raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

int main()
{
    No *raiz = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 15, 25};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++)
        raiz = inserir(raiz, valores[i]);

    analisar_arvore(raiz, 30);

    return 0;
}