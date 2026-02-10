#include <stdio.h>
#include <unistd.h>

ssize_t ft_write(int fd, const void *buf, size_t count);

int main()
{
    printf("TEST 0\n");
    printf("     ft_write: %ld\n", ft_write(1, "Hola", 4));
    printf("     write   : %ld\n", write(1, "Hola", 4));

	printf("-------------------------------\n");

    printf("TEST 1\n");
    printf("     ft_write: %ld\n", ft_write(1, "A", 1));
    printf("     write   : %ld\n", write(1, "A", 1));

	printf("-------------------------------\n");

    printf("TEST 2\n");
    printf("     ft_write: %ld\n", ft_write(1, "p", 2));
    printf("     write   : %ld\n", write(1, "p", 2));

	printf("-------------------------------\n");

    printf("TEST 3\n");
    printf("     write   : %ld\n", write(1, "", 7));
    printf("     ft_write: %ld\n", ft_write(1, "", 7));

	printf("-------------------------------\n");

	printf("TEST 4\n");
    printf("     ft_write: %ld\n", ft_write(1, "Patatassss", 7));
    printf("     write   : %ld\n", write(1, "Patatassss", 7));
	return (0);
}