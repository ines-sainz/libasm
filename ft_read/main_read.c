#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

ssize_t ft_read(int fd, void *buf, size_t count);

int main()
{
	char buf1[100];
	char *buf;
	int fd = open("prueba", O_RDONLY);
    printf("TEST 0\n");
    printf("     ft_read: %ld\n", ft_read(fd, buf1, 4));
	printf("Valor de errno: %d\n", errno);
    printf("     read   : %ld\n", read(fd, buf1, 4));
	printf("Valor de errno: %d\n", errno);
	printf("-------------------------------\n");

    printf("TEST 1\n");
    printf("     ft_read: %ld\n", ft_read(fd, buf1, 1));
	printf("Valor de errno: %d\n", errno);
    printf("     read   : %ld\n", read(fd, buf1, 1));
	printf("Valor de errno: %d\n", errno);

	printf("-------------------------------\n");

    printf("TEST 2\n");
    printf("     ft_read: %ld\n", ft_read(fd, buf1, -5));
	printf("Valor de errno: %d\n", errno);
    printf("     read   : %ld\n", read(fd, buf1, -5));
	printf("Valor de errno: %d\n", errno);

	printf("-------------------------------\n");

    printf("TEST 3\n");
    printf("     read   : %ld\n", read(fd, buf, 7));
	printf("Valor de errno: %d\n", errno);
    printf("     ft_read: %ld\n", ft_read(fd, buf, 7));
	printf("Valor de errno: %d\n", errno);

	printf("-------------------------------\n");

	printf("TEST 4\n");
    printf("     read   : %ld\n", read(fd, buf1, 7));
	printf("Valor de errno: %d\n", errno);
    printf("     ft_read: %ld\n", ft_read(fd, buf1, 7));
	printf("Valor de errno: %d\n", errno);
	return (0);
}