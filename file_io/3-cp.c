#include "main.h"
/**
 * main - Entry point
 * @argc: The number of arguments passed to the program.
 * @argv: An array of pointers to the arguments.
 * Return: 0 on success, 98 or 99 on failure.
 */
int main(int argc, char *argv[]);
{
/**
 * cp - Copies the content of a file to another file.
 * @file_from: The name of the file to copy from.
 * @file_to: The name of the file to copy to.
 * Return: 1 on success, -1 on failure (file_from does not exist,
 * file_to cannot be created, write fails, etc…).
 */
	int cp(const char *file_from, const char *file_to)
	{
		int fdfrom, fdto;
		ssize_t nread, nwrite;
		char buf[1024];

		if (argc != 3)
		{
			dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
			exit(97);
		}
		fdfrom = open(file_from, O_RDONLY);
			if (fdfrom == -1)
			{
				dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
				exit(98);
			}
		fdto = open(file_to, O_CREAT | O_WRONLY | O_TRUNC, 0664);
			if (fdto == -1)
			{
				dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
				exit(99);
			}
		while ((nread = read(fdfrom, buf, 1024)) > 0)
		{
			nwrite = write(fdto, buf, nread);
			if (nread != nwrite)
			{
				dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
				exit(99);
			}
		}
		if (nread == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
			exit(98);
		}
		close_fd(fdfrom);
		close_fd(fdto);
		return (0);
	}
}
/**
 * close_fd - Closes a file descriptor.
 * @fd: The file descriptor to close.
 */
void close_fd(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}