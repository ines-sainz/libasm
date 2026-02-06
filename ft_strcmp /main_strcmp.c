#include <stdio.h>
#include <string.h>

int ft_strcmp(const char *s1, const char *s2);

int	main(void)
{
	char	*str1 = "hola";
	char	*str2 = "ho";

    printf("TEST 0 %s == %s\n", str1, str2);
    printf("ft_strcmp: %d\n", ft_strcmp(str1, str2));
    printf("strcmp   : %d\n", strcmp(str1, str2));

	printf("-------------------------------\n");

	str2 = "hola";
    printf("TEST 1 %s == %s\n", str1, str2);
    printf("ft_strcmp: %d\n", ft_strcmp(str1, str2));
    printf("strcmp   : %d\n", strcmp(str1, str2));

	printf("-------------------------------\n");

	str2 = "Hola";
    printf("TEST 2 %s == %s\n", str1, str2);
    printf("ft_strcmp: %d\n", ft_strcmp(str1, str2));
    printf("strcmp   : %d\n", strcmp(str1, str2));

	printf("-------------------------------\n");

	str2 = "";
    printf("TEST 3 %s == %s\n", str1, str2);
    printf("ft_strcmp: %d\n", ft_strcmp(str1, str2));
    printf("strcmp   : %d\n", strcmp(str1, str2));
	return (0);
}