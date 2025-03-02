#include <stdio.h>

int main() {
    int First_num, Last_num, i, j, sum;
    printf("Enter the first number: ");
    scanf("%d", &First_num);

    printf("Enter the last number: ");
    scanf("%d", &Last_num);

    for (i = First_num; i <= Last_num; i++) {
        sum = 0;

        for (j = 1; j < i; j++) {
            if (i % j == 0) {
                sum += j;
            }
        }

        if (sum == i) {
            printf("%d\n", i);
        }
    }

    return 0;
}

