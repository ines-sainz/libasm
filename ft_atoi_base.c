#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int check_base(const char *str, char *base)
{
	if (ft_strlen(base) < 2)
		return (1);
	int i;
	int j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
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

int ft_atoi_base(const char *str, char *base)
{
	if (check_base(str, base) == 1)
		return (0);
	int num;
	int i;
	int base_len;

	i = 0;
	num = 0;
	base_len = ft_strlen(base);
	while (str[i])
	{
		num = num * base_len + get_pos(str[i], base);//(str[i] - '0');
		i++;
	}
	return (num);
}

int main()
{
	printf("%i\n", ft_atoi_base("12", "0123456789"));
	printf("%i\n", ft_atoi_base("1000", "01"));
	printf("%i\n", ft_atoi_base("12A", "0123456789ABCDEF"));
}





// int	ft_atoi(const char *str)
// {
// 	int	number;
// 	int	i;
// 	int	sign;
// 
// 	number = 0;
// 	i = 0;
// 	sign = 1;
// 	while (str[i] == ' ' || (str[i] <= 13 && str[i] >= 9))
// 		i++;
// 	if (str[i] == '+' || str[i] == '-')
// 	{
// 		if (str[i] == '-')
// 			sign = -1;
// 		i++;
// 	}
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		number = number * 10 + (str[i] - '0');
// 		i++;
// 	}
// 	return (number * sign);
// }