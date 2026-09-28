#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

ssize_t	ft_write(int fd, const void *buf, size_t count);

int	main(void)
{
    int	fd;
    ssize_t	ret_ft;
    ssize_t	ret_real;


    fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return (1);

    printf("TEST 0 - escribir \"Hola\"\n");

    ret_ft = ft_write(fd, "Hola\n", 5);
    ret_real = write(fd, "Hola\n", 5);

    printf("     ft_write: %ld\n", ret_ft);
    printf("     write   : %ld\n", ret_real);

    printf("-------------------------------\n");

    printf("TEST 1 - escribir una letra\n");

    ret_ft = ft_write(fd, "A\n", 2);
    ret_real = write(fd, "A\n", 2);

    printf("     ft_write: %ld\n", ret_ft);
    printf("     write   : %ld\n", ret_real);

    printf("-------------------------------\n");

    printf("TEST 2 - escribir menos caracteres que el string\n");

    ret_ft = ft_write(fd, "Patatas\n", 4);
    ret_real = write(fd, "Patatas\n", 4);

    printf("     ft_write: %ld\n", ret_ft);
    printf("     write   : %ld\n", ret_real);

    printf("-------------------------------\n");

    printf("TEST 3 - count = 0\n");

    ret_ft = ft_write(fd, "Esto no se escribe\n", 0);
    ret_real = write(fd, "Esto tampoco\n", 0);

    printf("     ft_write: %ld\n", ret_ft);
    printf("     write   : %ld\n", ret_real);

    printf("-------------------------------\n");

    printf("TEST 4 - escribir una frase\n");

    ret_ft = ft_write(fd, "Hola desde libasm\n", 18);
    ret_real = write(fd, "Hola desde libasm\n", 18);

    printf("     ft_write: %ld\n", ret_ft);
    printf("     write   : %ld\n", ret_real);

    printf("-------------------------------\n");

    close(fd);
    return (0);
}
