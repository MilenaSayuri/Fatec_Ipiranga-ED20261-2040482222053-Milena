#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_PILHA 4

void exibirPilha(int pilha[]) {
    printf("\n[T: %d]", pilha[3]);
    printf("\n[Z: %d]",  pilha[2]);
    printf("\n[Y: %d]",  pilha[1]);
    printf("\n[X: %d] (Display)",  pilha[0]);
    printf("\n------------------------------\n");
}


void empurrar(int pilha[], int valor) {
    pilha[3] = pilha[2];
    pilha[2] = pilha[1];
    pilha[1] = pilha[0];
    pilha[0] = valor;
}


void executaOperacao(int pilha[], char op){
    int resultado = 0;
    int x = pilha[0];
    int y = pilha[1];
   
    if (op == '+') resultado = y + x;
    else if (op == '-') resultado = y - x;
    else if (op == '*') resultado = y * x;
    else if (op == '/') {
        if (x != 0) {
            resultado = y / x;
        } else {
            printf("\nErro: Divisao por zero!");
            return;
        }
    }
    
    pilha[0] = resultado;
    pilha[1] = pilha[2];
    pilha[2] = pilha[3];
    pilha[3] = 0;
}

int main() {
    int pilha[TAM_PILHA] = {0, 0, 0, 0}; 
    char entrada[100];

    printf("--- SIMULADOR LÓGICO HP12c (RPN) ---\n");
    printf("Digite a expressão RPN (ex: 10 5 + 2 *): ");
    fgets(entrada, sizeof(entrada), stdin);

    entrada[strcspn(entrada, "\n")] = 0;

    char *token = strtok(entrada, " ");

    while (token != NULL) {
        
        if (ispunct(token[0]) && strlen(token) == 1) {
            executaOperacao(pilha, token[0]);
        } else {
            
            empurrar(pilha, atoi(token));
        }

        
        printf("\nProcessando: %s", token);
        exibirPilha(pilha);

        token = strtok(NULL, " ");
    }

    printf("\n====================================");
    printf("\nO resultado final no console é: %d", pilha[0]);
    printf("\n====================================\n");

    return 0;
}
