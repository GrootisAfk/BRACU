#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct order_item {
    int quantity;
    float unit_price;
};

float calculate_total_bill(struct order_item Paratha, struct order_item Vegetables, struct order_item Mineralwater) {

    float total_bill = (Paratha.quantity * Paratha.unit_price) + (Vegetables.quantity * Vegetables.unit_price) +
                       (Mineralwater.quantity * Mineralwater.unit_price);

    return total_bill;
}

float calculate_individualpay(float total_bill, int num_people) {

    float individualpay = total_bill / num_people;

    return individualpay;
}

int main() {

    struct order_item Paratha, Vegetables, Mineralwater;

    
    printf("Quantity Of Paratha: ");
    scanf("%d", &Paratha.quantity);
    printf("Unit Price: ");
    scanf("%f", &Paratha.unit_price);

    
    printf("Quantity Of Vegetables: ");
    scanf("%d", &Vegetables.quantity);
    printf("Unit Price: ");
    scanf("%f", &Vegetables.unit_price);

    
    printf("Quantity Of Mineral Water: ");
    scanf("%d", &Mineralwater.quantity);
    printf("Unit Price: ");
    scanf("%f", &Mineralwater.unit_price);

    
    int num_people;
    printf("Number of People: ");
    scanf("%d", &num_people);

    
    float total_bill = calculate_total_bill(Paratha, Vegetables, Mineralwater);

    
    float individualpay = calculate_individualpay(total_bill, num_people);

   
    printf("Each person will pay: %.2f tk\n", individualpay);

    return 0;
}

