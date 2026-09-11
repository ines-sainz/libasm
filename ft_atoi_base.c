#include <stdio.h>
#include <string.h>

int check_base(const char *str, char *base)
{
	if (strlen(base) < 2)
		return (1);
	int i;
	int j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || base[i] == ' ')
			return (1);
		j = 0;
		while (base[j])
		{
			if (base[i] == base[j] && i != j)
				return (1);
			j++;
		}
		i++;
	}

	i = 0;
	int eq;
	while (str[i])
	{
		j = 0;
		eq = 0;
		while (base[j])
		{
			if (str[i] == base[j])
				eq = 1;
			j++;
		}
		if (eq == 0)
			return (1);
		i++;
	}


	return (0);
}

int get_pos(char letter, char *base)
{
	int i;

	i = 0;
	while(base[i])
	{
		if (base[i] == letter)
			return (i);
		i++;
	}
	return (0);
}

int ft_atoi_base1(const char *str, char *base)
{
	if (check_base(str, base) == 1)
		return (0);
	int num;
	int i;
	int base_len;

	i = 0;
	num = 0;
	base_len = strlen(base);
	while (str[i])
	{
		printf("num(%i) = num(%i) * base_len(%i) + get_pos(%i)\n", (num * base_len + get_pos(str[i], base)), num, base_len, get_pos(str[i], base));
		num = num * base_len + get_pos(str[i], base);
		i++;
	}
	return (num);
}

int ft_atoi_base(const char *str, char *base);

int main(void)
{
	printf("TEST 0: %s   %s\n", "12", "0123456789");
    printf("ft_atoi_base1: %i\n", ft_atoi_base1("12", "0123456789"));
    printf("ft_atoi_base: %i\n", ft_atoi_base("12", "0123456789"));

	printf("-------------------------------\n");

	printf("TEST 1: %s   %s\n", "12", "0123456789");
    printf("ft_atoi_base1: %i\n", ft_atoi_base1("1000", "01"));
    printf("ft_atoi_base: %i\n", ft_atoi_base("1000", "01"));

	printf("-------------------------------\n");

	printf("TEST 2: %s   %s\n", "12", "0123456789");
    printf("ft_atoi_base1: %i\n", ft_atoi_base1("12A", "0123456789ABCDEF"));
    printf("ft_atoi_base: %i\n", ft_atoi_base("12A", "0123456789ABCDEF"));

	printf("-------------------------------\n");

    return 0;
}