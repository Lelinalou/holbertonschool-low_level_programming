#include "main.h"
/**
*free_grid - frees a 2D grid previously created by alloc_grid
*@grid: pointer to the 2D grid
*@height: height of the grid
*Return: void
*/
void free_grid(int **grid, int height)
{
	int i = 0;

	if (grid == NULL || height <= 0 )
	{
		return;
	}
	while (i < height)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}
