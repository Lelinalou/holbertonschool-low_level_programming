#include "main.h"
/**
 * read_textfile - Reads a text file and prints it to the POSIX standard outpu
 * @filename: The name of the file to read.
 * @letters: The number of letters to read and print.
 *
 * Return: The actual number of letters read and printed, or 0 if an error occ
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	char *buf;
	int fd;
	ssize_t nread;
	ssize_t nwrite;

	if (filename == NULL)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	buf = malloc((letters + 1) * sizeof(char));
	if (buf == NULL)
	{
		close(fd);
		return (0);
	}
	nread = read(fd, buf, letters);
	if (nread == -1)
	{
		free(buf);
		close(fd);
		return (0);
	}
	nwrite = write(1, buf, nread);

	if (nwrite == -1 || nwrite < nread)
	{
		free(buf);
		close(fd);
		return (0);
	}
	free(buf);
	close(fd);
	return (nwrite);
}
