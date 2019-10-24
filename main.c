#include "list_queue.h"
#include "list_stack.h"
#include "pnf.h"
#include <stdbool.h>

int main(){
    Stack *courtyard_1;
    Queue *courtyard_2;

    create_stack(&courtyard_1);
    create_queue(&courtyard_2);

    Car new[15];
    int i = 0;

    bool running = true;
    while (running == true){
        printf("Escolha uma opção do menu principal.\n");
        printf("(1) Registrar carro.\n"
            "(2) Imprimir carro.\n"
            "(3) Sair.\n");
        
        int n;
        scanf("%d", &n);
        switch (n) {
            case 1:
                int checkIn_status = checkIn(courtyard_1, courtyard_2, new[i]);
                if (checkIn_status == 1)
                    printf("Carro rejeitado. Placa ja consta no patio.\n");
                else if (checkIn_status == 2)
                    printf("Carro rejeitado. Horario de entrada ou saida fora de funcionamento.\n");
                else{
                    checkOut(courtyard_1, courtyard_2, new[i]);
                    discount_raffle(courtyard_1, courtyard_2, new[i]);
                    int disponibility_status = disponibility(courtyard_1, courtyard_2, new[i]);
                    if (disponibility_status == 3)
                        printf("Carro rejeitado. Nenhuma das regras de disponibilidade foram aceitas.\n");
                    else
                        printf("Carro registrado.");  
                }              
                break;
            
            case 2:
                print_cars(courtyard_1, courtyard_2);
                break;
            
            case 3:
                empty_stack(&courtyard_1);
                empty_queue(&courtyard_2);
                running = false;
                break;
        }
        i++;
    }
    

    return 0;
}