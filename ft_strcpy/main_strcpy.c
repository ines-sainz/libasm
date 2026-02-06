#include <stdio.h>
#include <string.h>

char *ft_strcpy(char *dst, const char *src);

int main(void)
{
	char *str = "Hello";
    char str1[100];
    char str2[100];

    printf("TEST 0\n");
    printf("ft_strcpy: %s\n", ft_strcpy(str1, str));
    printf("strcpy   : %s\n", strcpy(str2, str));

	printf("-------------------------------\n");

	str = "a";
    printf("TEST 1\n");
    printf("ft_strcpy: %s\n", ft_strcpy(str1, str));
    printf("strcpy   : %s\n", strcpy(str2, str));

	printf("-------------------------------\n");

	str = "Patataaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    printf("TEST 2\n");
    printf("ft_strcpy: %s\n", ft_strcpy(str1, str));
    printf("strcpy   : %s\n", strcpy(str2, str));

	printf("-------------------------------\n");

	str = "";
    printf("TEST 3\n");
    printf("ft_strcpy: %s\n", ft_strcpy(str1, str));
    printf("strcpy   : %s\n", strcpy(str2, str));

}
