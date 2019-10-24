#include <stdlib.h>
#include "list_stack.h"
#include "list_queue.h"

void create_stack(Stack **s) {
    *s = malloc(sizeof(Stack)); // aloca memoria
    (*s)->begin = NULL; // pilha vazia
    return;
}

void empty_stack(Stack **s) {
    Node *aux;
    // apaga elementos
    while (!isEmpty_stack(*s)) {
        aux = (*s)->begin;
        (*s)->begin = (*s)->begin->next;
        free(aux);
    }
    // apaga struct pilha
    free(*s);
    // atualizo ponteiro do usuario
    *s = NULL;
    return;
}

int checkSize(Stack *s) {
    Node *aux = s->begin;
    int count = 0;
    while (aux != NULL) {
        count++;
        aux = aux->next;
    }
    return count;
}

int isFull_stack(Stack *s){
    if (checkSize(s) == 10){
        return 1;
    }
    else{
        return 0;
    }
}

int isEmpty_stack(Stack *s) {
    return (s->begin == NULL);
}

void push(Stack *s, elem x) {
    Node *aux = malloc(sizeof(Node)); // cria caixa
    aux->info = x; // copia info
    // atualiza encadeamento
    aux->next = s->begin;
    s->begin = aux;
    return;
}

int pop(Stack *s, elem *x) {
    Node *aux;
    if (isEmpty(s))
        return 1; // erro
    *x = s->begin->info; // copia info
    aux = s->begin; // guarda ponteiro a apagar
    s->begin = s->begin->next; // atualiza encadeamento
    free(aux); // apaga caixa
    return 0; // sucesso
}
