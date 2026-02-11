#include <stdio.h>
#include <string.h>

char *ft_strdup(const char *s);

int main()
{

    printf("TEST 0\n");
    printf("ft_strcpy: %s\n", ft_strdup("Hola"));
    printf("strcpy   : %s\n", strdup("Hola"));

	printf("-------------------------------\n");

    printf("TEST 1\n");
    printf("ft_strcpy: %s\n", ft_strdup(""));
    printf("strcpy   : %s\n", strdup(""));

	printf("-------------------------------\n");

    printf("TEST 2\n");
    printf("ft_strcpy: %s\n", ft_strdup("P"));
    printf("strcpy   : %s\n", strdup("P"));

	printf("-------------------------------\n");

    printf("TEST 3\n");
    printf("ft_strcpy: %s\n", ft_strdup(""));
    printf("strcpy   : %s\n", strdup(""));

}