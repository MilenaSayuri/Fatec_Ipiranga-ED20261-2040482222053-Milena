#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    double x, y, z, t;
} HP12c;

void exibirPilha(HP12c *p)
{
    printf("\n--- ESTADO DOS REGISTRADORES ---");
    printf("\n T: %10.2f", p->t);
    printf("\n Z: %10.2f", p->z);
    printf("\n Y: %10.2f", p->y);
    printf("\n X: %10.2f (Display)", p->x);
    printf("\n--------------------------------\n");
}

void push(HP12c *p, double valor)
{
    p->t = p->z;
    p->z = p->y;
    p->y = p->x;
    p->x = valor;
}

void executarOperacao(HP12c *p, char op)
{
    double resultado = 0;

    switch (op)
    {
    case '+':
        resultado = p->y + p->x;
        break;
    case '-':
        resultado = p->y - p->x;
        break;
    case '*':
        resultado = p->y * p->x;
        break;
    case '/':
        if (p->x != 0)
            resultado = p->y / p->x;
        else
        {
            printf("\nErro: Divisao por zero!\n");
            return;
        }
        break;
    default:
        return;
    }

    p->x = resultado;
    p->y = p->z;
    p->z = p->t;
}

int main()
{
    HP12c pilha = {0, 0, 0, 0};
    char entrada[256];

    printf("--- SIMULADOR LÓGICO HP12c (RPN) ---\n");
    printf("Digite a expressão RPN (ex: 10 5 + 2 *): ");

    fgets(entrada, sizeof(entrada), stdin);

    entrada[strcspn(entrada, "\n")] = 0;

    char *token = strtok(entrada, " ");

    while (token != NULL)
    {
        if (strlen(token) == 1 && strpbrk(token, "+-*/"))
        {
            printf("\nOperador detectado: %s", token);
            executarOperacao(&pilha, token[0]);
        }
        else
        {
            printf("\nNúmero detectado: %s", token);
            push(&pilha, atof(token));
        }

        exibirPilha(&pilha);
        token = strtok(NULL, " ");
    }

    printf("\n====================================");
    printf("\nO resultado final no console é: %.2f", pilha.x);
    printf("\n====================================\n");

    return 0;
}