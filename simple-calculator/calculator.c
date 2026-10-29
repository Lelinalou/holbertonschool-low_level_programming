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
			printf("Invalid Input.\n");
			break;
		}
		if (choice == 0)
		{
			printf("Bye!\n");
		}
	}
	return 0;
}
