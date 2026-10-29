#include<stdio.h>

int main() 
{
	int choice = -1;

	printf("Simple calculator\n");

	while (choice != 0)
	{
		printf("1) Add\n");
		printf("2) Subtract\n");
		printf("3) Multiply\n");
		printf("4) Divide\n");
		printf("0) Quit\n");
		if (scanf("%d", &choice) != 1)
		{
			printf("Invalid input.\n");
			break;
		}
		if (choice < 0 || choice > 4)
		{
			printf("Invalid input.\n");
		}
		if (choice == 0)
		{
			printf("Bye!\n");
		}
		if (choice == 1)
		{
		int A, B, result;
		scanf("%d", &A);
		scanf("%d", &B);
		result = A + B;
		printf("Result: %d\n", result);
		}
		if (choice == 2)
		{
		int A, B, result;
		scanf("%d", &A);
		scanf("%d", &B);
		result = A - B;
		printf("Result: %d\n", result);
		}
		if (choice == 3)
		{
		int A, B, result;
		scanf("%d", &A);
		scanf("%d", &B);
		result = A * B;
		printf("Result: %d\n", result);
		}
	}
	return 0;
}
