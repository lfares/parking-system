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

typedef struct{
    Node *begin, *end;
} Queue;

void create_queue(Queue **q);
void empty_queue(Queue **q);
void in(Queue *q, elem x);
int checkSize_queue(Queue *q);
int out(Queue *q, elem *x);
int isEmpty_queue(Queue *q);
int isFull_queue(Queue *q);