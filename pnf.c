#include "pnf.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define SUCSSES 0
#define ERR_LICENSE_PLATE_REGISTERED 1
#define ERR_OUT_TIME 2
#define ERR_DISPONIBILITY 3


int checkLicensePlate (Stack *courtyard_1, Queue *courtyard_2, int license_plate){
    // Check courtyard 1
    Node *aux1 = courtyard_1->begin;
    while (aux1 != NULL) {
        if (aux1->info.license_plate == license_plate)
            return ERR_LICENSE_PLATE_REGISTERED;
        aux1 = aux1->next;
    }
    // Check courtyard 2
    Node *aux2 = courtyard_2->begin;
    while (aux2 != NULL) {
        if (aux2->info.license_plate == license_plate)
            return ERR_LICENSE_PLATE_REGISTERED;
        aux2 = aux2->next;
    }
    return SUCSSES; // license plate not on any courtyard
}

int checkIn(Stack *courtyard_1, Queue *courtyard_2, elem *new){
    int license_plate, arrival, hours_total, departure;
    printf("Informe a placa do veiculo: (4 dígitos)\n");
    scanf("%d", &license_plate);
    if (checkLicensePlate(courtyard_1, courtyard_2, license_plate) == 1){
        return ERR_LICENSE_PLATE_REGISTERED;
    }
    printf("Informe o horario de chegada: (hora cheia, padrao 24h)\n");
    scanf("%d", &arrival);
    printf("Informe o total de horas de permanência: (hora cheia)\n");
    scanf("%d", &hours_total);

    departure = arrival+hours_total;
    if ((arrival < 8) || (departure > 22))
        return ERR_OUT_TIME; 

    (*new).license_plate = license_plate;
    (*new).arrival = arrival;
    (*new).departure = departure;
    (*new).discount = 1.0;

    return SUCSSES;
}

void checkOut (Stack *courtyard_1, Queue *courtyard_2, elem new){
    // Remove cars from courtyard 1
    Node *aux1 = courtyard_1->begin;
    int payment_value;
    while(aux1 != NULL){
        if (aux1->info.departure <= new.arrival){
            printf("Placa: %d\n", aux1->info.license_plate);
            payment_value = (aux1->info.departure - aux1->info.arrival) * 3 * aux1->info.discount;
            printf("Valor a ser pago: %d\n", payment_value);
            pop(courtyard_1, &aux1->info);
        }
        aux1 = aux1->next;
    }
    free(aux1);
    // Remove cars from courtyard 2
    Node *aux2 = courtyard_2->begin;
    while(aux2 != NULL){
        if (aux2->info.departure <= new.arrival){
            printf("Placa: %d\n", aux2->info.license_plate);
            payment_value = (aux2->info.departure - aux2->info.arrival) * 3 * aux2->info.discount;
            printf("Valor a ser pago: %d\n", payment_value);
            out(courtyard_2, &aux2->info);
        }
        aux2 = aux2->next;
    }
    free(aux2);

    return;
}

elem *get_vector(Stack *courtyard_1, Queue *courtyard_2, int size){
    elem vector_cars[size];
    Node *aux1 = courtyard_1->begin;
    int i = 0;
    while(aux1 != NULL){
        vector_cars[i] = aux1->info;
        i++;
        aux1 = aux1->next;
    }
    free(aux1);
    Node *aux2 = courtyard_2->begin;
    while(aux2 != NULL){
        vector_cars[i] = aux2->info;
        i++;
        aux2 = aux2->next;
    }
    free(aux2);

    return vector_cars;
}

void discount_raffle (Stack *courtyard_1, Queue *courtyard_2, elem new){
    int total_cars = checkSize_stack(courtyard_1) + checkSize_queue(courtyard_2);
    elem *vector_cars;
    if (((new.arrival == 9) || (new.arrival == 12) || (new.arrival == 15) || (new.arrival == 18)) && (total_cars > 4)){
        // All parameters are okay to make the discount roulette and get the car discount
        vector_cars = get_vector(courtyard_1, courtyard_2, total_cars);
        int roulette_cursor = 0;
        roulette_cursor = rand() % 15;
        while (roulette_cursor > total_cars){
            roulette_cursor = 0;
            roulette_cursor = rand() % 15;
        }
        // Change discount value on drawn car
        elem aux; 
        bool found = false;
        // Check if car is on courtyard 1
        for(int i = 0; i < checkSize_stack(courtyard_1); i++){
            pop(courtyard_1, &aux);
            if (aux.license_plate == vector_cars[roulette_cursor].license_plate)
                aux.discount = 0.9; // discount of 10%
                found = true;
            push(courtyard_1, aux);
        }
        // If it is not in courtyard 1, check courtyard 2
        if (found == false){
            for(int i = 0; i < checkSize_queue(courtyard_2); i++){
                out(courtyard_2, &aux);
                if (aux.license_plate == vector_cars[roulette_cursor].license_plate)
                    aux.discount = 0.9; // discount of 10%
                    found = true;
                in(courtyard_2, aux);
            }
        }
    }
    else{
        printf("Sorteio de desconto não é aplicável.\n");          
    }   
    return;
}

int disponibility(Stack *courtyard_1, Queue *courtyard_2, elem new){
    if (isEmpty_stack(courtyard_1) && isEmpty_queue(courtyard_2))
        push(courtyard_1, new);
    else if (!isEmpty_stack(courtyard_1) && isEmpty_queue(courtyard_2))
        in(courtyard_2, new);
    else{
        if (!isFull_stack(courtyard_1) && (new.departure <= courtyard_1->begin->info.departure))
            push(courtyard_1, new);
        else if(!isFull_queue(courtyard_2) && (new.departure >= courtyard_2->end->info.departure))
            in(courtyard_2, new);
        else
            return ERR_DISPONIBILITY;      
    }
    return SUCSSES;
}

void print_cars(Stack *courtyard_1, Queue *courtyard_2){
    // Print cars from courtyard_1
    Node *aux1 = courtyard_1->begin;
    int payment_value;
    printf("Patio 1:\n");
    while(aux1 != NULL){
        payment_value = (aux1->info.departure - aux1->info.arrival) * 3 * aux1->info.discount;
        printf("Placa: %d\n", aux1->info.license_plate);
        printf("Valor a ser pago: %d\n", payment_value);
        aux1 = aux1->next;
    }
    // Print cars from courtyard_2
    Node *aux2 = courtyard_2->begin;
    printf("\nPatio 2:\n");
    while(aux2 != NULL){
        payment_value = (aux2->info.departure - aux2->info.arrival) * 3 * aux2->info.discount;
        printf("Placa: %d\n", aux2->info.license_plate);
        printf("Valor a ser pago: %d\n", payment_value);
        aux2 = aux2->next;
    }
    return;
}