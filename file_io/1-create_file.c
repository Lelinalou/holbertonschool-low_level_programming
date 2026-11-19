#include "main.h"
/**
 * create_file - Creates a file.
 * @filename: The name of the file to create.
 * @text_content: A NULL terminated string to write to the file.
 * Return: 1 on success, -1 on failure (file cannot be created, file
 * written, write “fails”, etc…).
 */
int create_file(const char *filename, char *text_content)
{
	int i = 0;
	int fd;
	ssize_t nwrite;

	if (filename == NULL)
		return (-1);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);
	if (text_content != NULL)
	{
		while (text_content[i] != '\0')
			i++;
	nwrite = write(fd, text_content, i);
	if (nwrite == -1 || nwrite < i)
	{
		close(fd);
		return (-1);
	}
	}
	close(fd);
	return (1);
}
