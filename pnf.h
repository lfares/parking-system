#include "list_queue.h"
#include "list_stack.h"

int checkLicensePlate (Stack *courtyard_1, Queue *courtyard_2, int license_plate);
int checkIn(Stack *courtyard_1, Queue *courtyard_2, elem new);
void checkOut (Stack *courtyard_1, Queue *courtyard_2, elem new);
void discount_raffle (Stack *courtyard_1, Queue *courtyard_2, elem new);
int disponibility(Stack *courtyard_1, Queue *courtyard_2, elem new);
void print_cars(Stack *courtyard_1, Queue *courtyard_2);