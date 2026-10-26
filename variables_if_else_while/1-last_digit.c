#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/**
    * main - prints the last digit of a number
    * Return: Always 0 (Success)
    */
int main(void)
{
int n;
int last;
srand(time(0));
n = rand() - RAND_MAX / 2;
last = n % 10;
if (n>5)
printf("Last digit of %d is and %d is greater than 5\n",n, last);
else if (n==0)
printf("Last digit of %d is and %d is 0\n",n, last);
else
printf("Last digit of %d is and %d is less than 6 and not 0",n, last);
return(0);
}
