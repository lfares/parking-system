#include <stdlib.h>
#include <stdio.h>
#include "list_queue.h"

void create_queue(Queue **q) {
    *q = malloc(sizeof(Queue)); 
    // make queue empty
    (*q)->begin = NULL;
    (*q)->end = NULL;
    return;
}

void empty_queue(Queue **q) {
    // erase all cars
    Node *aux;
    while ((*q)->begin != NULL) {
        aux = (*q)->begin;
        (*q)->begin = (*q)->begin->next;
        free(aux);
    }
    // erase queue
    free(*q);
    *q = NULL;
    return;
}

void in(Queue *q, elem x) {
    Node *aux;
    // cria Node
    aux = malloc(sizeof(Node));
    aux->info = x;
    aux->next = NULL;
    // atualiza ponteiros
    if (!isEmpty_queue(q))
        q->end->next = aux;
    q->end = aux;
    if (isEmpty_queue(q))
        q->begin = aux;
    return;
}

int checkSize_queue(Queue *q) {
    Node *aux = q->begin;
    int count = 0;
    while (aux != NULL) {
        count++;
        aux = aux->next;
    }
    return count;
}

int out(Queue *q, elem *x) {
    Node *aux;
    if (isEmpty_queue(q))
        return 1; // erro
    *x = q->begin->info; // copia info
    aux = q->begin; // guarda ponteiro a apagar
    q->begin = q->begin->next; // atualiza encadeamento
    free(aux); // apaga caixa
    return 0; // sucesso
}

int isEmpty_queue(Queue *q) {
    return (q->begin == NULL);
}

int isFull_queue(Queue *q){
    if (checkSize_queue(q) == 10){
        return 1;
    }
    else{
        return 0;
    }
}