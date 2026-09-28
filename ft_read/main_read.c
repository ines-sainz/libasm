#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

ssize_t	ft_read(int fd, void *buf, size_t count);

int	main(void)
{
	int		fd_ft;
	int		fd_real;
	ssize_t	ret_ft;
	ssize_t	ret_real;
	char	buf_ft[100];
	char	buf_real[100];

	fd_ft = open("test.txt", O_RDONLY);
	fd_real = open("test.txt", O_RDONLY);
	if (fd_ft < 0 || fd_real < 0)
		return (1);

	printf("TEST 0 - leer 4 caracteres\n");

	ret_ft = ft_read(fd_ft, buf_ft, 4);
	ret_real = read(fd_real, buf_real, 4);

	printf("     ft_read: %ld\n", ret_ft);
	printf("     read   : %ld\n", ret_real);
	printf("     ft_read contenido: %.*s\n", (int)ret_ft, buf_ft);
	printf("     read contenido   : %.*s\n", (int)ret_real, buf_real);

	printf("-------------------------------\n");

	printf("TEST 1 - leer 1 caracter\n");

	ret_ft = ft_read(fd_ft, buf_ft, 1);
	ret_real = read(fd_real, buf_real, 1);

	printf("     ft_read: %ld\n", ret_ft);
	printf("     read   : %ld\n", ret_real);
	printf("     ft_read contenido: %.*s\n", (int)ret_ft, buf_ft);
	printf("     read contenido   : %.*s\n", (int)ret_real, buf_real);

	printf("-------------------------------\n");

	printf("TEST 2 - leer 7 caracteres\n");

	ret_ft = ft_read(fd_ft, buf_ft, 7);
	ret_real = read(fd_real, buf_real, 7);

	printf("     ft_read: %ld\n", ret_ft);
	printf("     read   : %ld\n", ret_real);
	printf("     ft_read contenido: %.*s\n", (int)ret_ft, buf_ft);
	printf("     read contenido   : %.*s\n", (int)ret_real, buf_real);

	printf("-------------------------------\n");

	printf("TEST 3 - count = 0\n");

	ret_ft = ft_read(fd_ft, buf_ft, 0);
	ret_real = read(fd_real, buf_real, 0);

	printf("     ft_read: %ld\n", ret_ft);
	printf("     read   : %ld\n", ret_real);

	printf("-------------------------------\n");

	close(fd_ft);
	close(fd_real);

	printf("TEST 4 - fd invalido\n");

	ret_ft = ft_read(-1, buf_ft, 5);

	printf("     ft_read: %ld\n", ret_ft);
	printf("     errno  : %d\n", errno);

	ret_real = read(-1, buf_real, 5);

	printf("     read   : %ld\n", ret_real);
	printf("     errno  : %d\n", errno);

	printf("-------------------------------\n");

return (0);

}
