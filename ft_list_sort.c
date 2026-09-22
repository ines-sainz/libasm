#include "bonus.h"

t_list	*ft_lstnew(void *data)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (tmp == NULL)
		return (NULL);
	tmp->data = data;
	tmp->next = NULL;
	return tmp;
}

void	ft_list_push_front1(t_list **begin_list, void *data)
{
	t_list	*node;
	node = ft_lstnew(data);
	if (node == NULL)
		return ;
	if (*begin_list == NULL)
	{
		*begin_list = node;
	}
	else
	{
		node->next = *begin_list;
		*begin_list = node;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}

void	ft_sort_int_tab(int *tab, int size)
{
	int	c;
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size)
		{
			if (tab[i] > tab[i + 1])
			{
				c = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = c;
			}
			j++;
		}
		i++;
	}
}

void	ft_sort_int_tab(int *tab, int size)
{
	int	c;
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i] > tab[i + 1])
		{
			c = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = c;
		}
		i++;
	}
}


int	ft_list_sort1(t_list **begin_list, int (*cmp)())
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void ft_list_sort(t_list **begin_list, int (*cmp)());

int main()
{
	t_list	*lista;
	t_list	*tmp;
	lista = NULL;

    printf("TEST 0: lista = NULL\n");
    printf("ft_list_size1: %u\n", ft_list_size1(lista));
    printf("ft_list_size : %u\n", ft_list_size(lista));

	printf("-------------------------------\n");

	ft_list_push_front1(&lista, "elemento1");

    printf("TEST 1: lista --> elemento1\n");
    printf("ft_list_size1: %u\n", ft_list_size1(lista));
    printf("ft_list_size : %u\n", ft_list_size(lista));

	printf("-------------------------------\n");

    ft_list_push_front1(&lista, "elemento2\n");

    printf("TEST 2: lista --> elemento2 --> elemento1\n");
    printf("ft_list_size1: %u\n", ft_list_size1(lista));
    printf("ft_list_size : %u\n", ft_list_size(lista));

	printf("-------------------------------\n");

    for (int i = 0; i < 5; i++)
        ft_list_push_front1(&lista, "elemento3");

    printf("TEST 3: lista with 7 elements\n");
    printf("ft_list_size1: %u\n", ft_list_size1(lista));
    printf("ft_list_size : %u\n", ft_list_size(lista));

	while (lista != NULL)
    {
		tmp = lista;
		lista = lista->next;
		free(tmp);
    }
}