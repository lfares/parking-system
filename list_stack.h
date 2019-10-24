#include "list_queue.h"

typedef struct stack {
    Node *begin;
}Stack;

void create_stack(Stack **s);
void empty_stack(Stack **s);
int checkSize (Stack *s);
int isEmpty_stack(Stack *s);
int isFull_stack(Stack *s);
void push(Stack *s, elem x);
int pop(Stack *s, elem *x);