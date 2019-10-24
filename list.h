typedef struct{
    int license_plate;
    int arrival;
    int departure;
    float discount;
}Car;

typedef Car elem; 

typedef struct node {
    elem info;
    struct node *next;
}Node;


typedef struct stack {
    Node *begin;
}Stack;

typedef struct{
    Node *begin, *end;
} Queue;

/*****************************
List of stack for courtyard 1
******************************/
void create_stack(Stack **s);
void empty_stack(Stack **s);
int checkSize_stack(Stack *s);
int isEmpty_stack(Stack *s);
int isFull_stack(Stack *s);
void push(Stack *s, elem x);
int pop(Stack *s, elem *x);

/*****************************
List of queue for courtyard 2
******************************/
void create_queue(Queue **q);
void empty_queue(Queue **q);
int checkSize_queue(Queue *q);
int isEmpty_queue(Queue *q);
int isFull_queue(Queue *q);
void in(Queue *q, elem x);
int out(Queue *q, elem *x);