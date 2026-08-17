#include <stdio.h>
#include <string.h>
#include <errno.h>

char *ft_strdup(const char *s);

int main()
{

    printf("TEST 0\n");
    printf("ft_strdup: %s\n", ft_strdup("Hola"));
	printf("Valor de errno: %d\n", errno);
    printf("strdup   : %s\n", strdup("Hola"));
	printf("Valor de errno: %d\n", errno);

	printf("-------------------------------\n");

    printf("TEST 1\n");
    printf("ft_strdup: %s\n", ft_strdup(""));
	printf("Valor de errno: %d\n", errno);
    printf("strdup   : %s\n", strdup(""));
	printf("Valor de errno: %d\n", errno);

	printf("-------------------------------\n");

    printf("TEST 2\n");
    printf("ft_strdup: %s\n", ft_strdup("P"));
	printf("Valor de errno: %d\n", errno);
    printf("strdup   : %s\n", strdup("P"));
	printf("Valor de errno: %d\n", errno);

	printf("-------------------------------\n");

    printf("TEST 3\n");
    printf("ft_strdup: %s\n", ft_strdup(""));
	printf("Valor de errno: %d\n", errno);
    printf("strdup   : %s\n", strdup(""));
	printf("Valor de errno: %d\n", errno);

}