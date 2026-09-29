#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

ssize_t	ft_write(int fd, const void *buf, size_t count);

int	main(void)
{
    int	fd;
    ssize_t	ret_ft;
    ssize_t	ret_real;


    fd = open("test.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
        return (1);

    dprintf(fd, "TEST 0 - escribir \"Hola\"\n");

    ret_ft = ft_write(fd, "Hola\n", 5);
    ret_real = write(fd, "Hola\n", 5);

    dprintf(fd, "     ft_write: %ld\n", ret_ft);
    dprintf(fd, "     write   : %ld\n", ret_real);

    dprintf(fd, "-------------------------------\n");

    dprintf(fd, "TEST 1 - escribir una letra\n");

    ret_ft = ft_write(fd, "A\n", 2);
    ret_real = write(fd, "A\n", 2);

    dprintf(fd, "     ft_write: %ld\n", ret_ft);
    dprintf(fd, "     write   : %ld\n", ret_real);

    dprintf(fd, "-------------------------------\n");

    dprintf(fd, "TEST 2 - escribir menos caracteres que el string\n");

    ret_ft = ft_write(fd, "Patatas\n", 4);
    ret_real = write(fd, "Patatas\n", 4);

    dprintf(fd, "     ft_write: %ld\n", ret_ft);
    dprintf(fd, "     write   : %ld\n", ret_real);

    dprintf(fd, "-------------------------------\n");

    dprintf(fd, "TEST 3 - count = 0\n");

    ret_ft = ft_write(fd, "Esto no se escribe\n", 0);
    ret_real = write(fd, "Esto tampoco\n", 0);

    dprintf(fd, "     ft_write: %ld\n", ret_ft);
    dprintf(fd, "     write   : %ld\n", ret_real);

    dprintf(fd, "-------------------------------\n");

    dprintf(fd, "TEST 4 - escribir una frase\n");

    ret_ft = ft_write(fd, "Hola desde libasm\n", 18);
    ret_real = write(fd, "Hola desde libasm\n", 18);

    dprintf(fd, "     ft_write: %ld\n", ret_ft);
    dprintf(fd, "     write   : %ld\n", ret_real);

    dprintf(fd, "-------------------------------\n");

    close(fd);
    return (0);
}






ssize_t	ft_write(int fd, const void *buf, size_t count);

static void	print_result(int out_fd, const char *name,
				ssize_t ret_ft, int errno_ft,
				ssize_t ret_real, int errno_real)
{
	dprintf(out_fd, "     %-10s: return = %ld", name, ret_ft);
	if (ret_ft == -1)
		dprintf(out_fd, ", errno = %d (%s)", errno_ft, strerror(errno_ft));
	dprintf(out_fd, "\n");

	dprintf(out_fd, "     %-10s: return = %ld", "write", ret_real);
	if (ret_real == -1)
		dprintf(out_fd, ", errno = %d (%s)",
			errno_real, strerror(errno_real));
	dprintf(out_fd, "\n");

	dprintf(out_fd, "-------------------------------\n");
}

int	main(void)
{
	int		fd;
	int		invalid_fd;
	ssize_t	ret_ft;
	ssize_t	ret_real;
	int		errno_ft;
	int		errno_real;

	fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (1);

	/*
	 * TEST 0
	 */
	dprintf(fd, "================================\n");
	dprintf(fd, "TEST 0 - escribir \"Hola\"\n");
	dprintf(fd, "================================\n");

	ret_ft = ft_write(fd, "Hola\n", 5);
	errno_ft = errno;

	ret_real = write(fd, "Hola\n", 5);
	errno_real = errno;

	print_result(fd, "ft_write", ret_ft, errno_ft,
		ret_real, errno_real);


	/*
	 * TEST 1
	 */
	dprintf(fd, "TEST 1 - escribir una letra\n");

	ret_ft = ft_write(fd, "A\n", 2);
	errno_ft = errno;

	ret_real = write(fd, "A\n", 2);
	errno_real = errno;

	print_result(fd, "ft_write", ret_ft, errno_ft,
		ret_real, errno_real);


	/*
	 * TEST 2
	 */
	dprintf(fd, "TEST 2 - escribir menos caracteres que el string\n");

	ret_ft = ft_write(fd, "Patatas\n", 4);
	errno_ft = errno;

	ret_real = write(fd, "Patatas\n", 4);
	errno_real = errno;

	print_result(fd, "ft_write", ret_ft, errno_ft,
		ret_real, errno_real);


	/*
	 * TEST 3
	 */
	dprintf(fd, "TEST 3 - count = 0\n");

	ret_ft = ft_write(fd, "Esto no se escribe\n", 0);
	errno_ft = errno;

	ret_real = write(fd, "Esto tampoco\n", 0);
	errno_real = errno;

	print_result(fd, "ft_write", ret_ft, errno_ft,
		ret_real, errno_real);


	/*
	 * TEST 4
	 */
	dprintf(fd, "TEST 4 - escribir una frase\n");

	ret_ft = ft_write(fd, "Hola desde libasm\n", 18);
	errno_ft = errno;

	ret_real = write(fd, "Hola desde libasm\n", 18);
	errno_real = errno;

	print_result(fd, "ft_write", ret_ft, errno_ft,
		ret_real, errno_real);


	/*
	 * TEST 5
	 */
	dprintf(fd, "TEST 5 - fd incorrecto (-1)\n");

	invalid_fd = -1;

	ret_ft = ft_write(invalid_fd, "ERROR TEST\n", 11);
	errno_ft = errno;

	ret_real = write(invalid_fd, "ERROR TEST\n", 11);
	errno_real = errno;

	print_result(fd, "ft_write", ret_ft, errno_ft,
		ret_real, errno_real);


	/*
	 * TEST 6
	 */
	dprintf(fd, "TEST 6 - fd cerrado\n");

	{
		int closed_fd;

		closed_fd = open("test_closed.txt",
			O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (closed_fd < 0)
		{
			dprintf(fd, "No se pudo crear test_closed.txt\n");
		}
		else
		{
			close(closed_fd);

			ret_ft = ft_write(closed_fd, "CLOSED\n", 7);
			errno_ft = errno;

			ret_real = write(closed_fd, "CLOSED\n", 7);
			errno_real = errno;

			print_result(fd, "ft_write", ret_ft, errno_ft,
				ret_real, errno_real);
		}
	}


	/*
	 * TEST 7
	 */
	dprintf(fd, "TEST 7 - string vacio con count = 0\n");

	ret_ft = ft_write(fd, "", 0);
	errno_ft = errno;

	ret_real = write(fd, "", 0);
	errno_real = errno;

	print_result(fd, "ft_write", ret_ft, errno_ft,
		ret_real, errno_real);


	/*
	 * FIN
	 */
	dprintf(fd, "\n");
	dprintf(fd, "================================\n");
	dprintf(fd, "FIN DE LOS TESTS\n");
	dprintf(fd, "================================\n");

	close(fd);

	return (0);
}