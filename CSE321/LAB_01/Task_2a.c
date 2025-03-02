#include <stdio.h>

int main() {

  int num,num2;
  printf("Number1: ");
  scanf("%d",&num);
  printf("number2: ");
  scanf("%d",&num2);

  if (num > num2) printf("Substraction = %d \n",num-num2);
  else if (num < num2) printf("Addition = %d \n",num+num2);
  else if (num2 == num2) printf("Multiplication = %d \n",num*num2);
  return 0;
}