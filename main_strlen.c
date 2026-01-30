#include <stdio.h>
#include <string.h>

size_t ft_strlen(const char *s);

int main(void)
{
    const char *s = "hola mundo";
    const char *s1 = "h";
    const char *s2 = "0123456789";
    const char *s3 = "hola";
    const char *s4 = "";

	printf("TEST 0: %s\n", s);
    printf("ft_strlen: %zu\n", ft_strlen(s));
    printf("strlen   : %zu\n", strlen(s));

	printf("-------------------------------\n");

	printf("TEST 1: %s\n", s1);
	printf("ft_strlen: %zu\n", ft_strlen(s1));
    printf("strlen   : %zu\n", strlen(s1));

	printf("-------------------------------\n");

	printf("TEST 2: %s\n", s2);
    printf("ft_strlen: %zu\n", ft_strlen(s2));
    printf("strlen   : %zu\n", strlen(s2));

	printf("-------------------------------\n");

	printf("TEST 3: %s\n", s3);
	printf("ft_strlen: %zu\n", ft_strlen(s3));
    printf("strlen   : %zu\n", strlen(s3));

	printf("-------------------------------\n");

	printf("TEST 4: %s\n", s4);
	printf("ft_strlen: %zu\n", ft_strlen(s4));
    printf("strlen   : %zu\n", strlen(s4));

    return 0;
}
