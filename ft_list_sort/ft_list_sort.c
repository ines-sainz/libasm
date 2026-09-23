#include "bonus.h"
#include <stdio.h>
#include <stdlib.h>

t_list	*ft_lstnew(void *data)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (tmp == NULL)
		return (NULL);
	tmp->data = data;
	tmp->next = NULL;
	return (tmp);
}

void	ft_list_push_front1(t_list **begin_list, void *data)
{
	t_list	*node;

	node = ft_lstnew(data);
	if (node == NULL)
		return ;
	node->next = *begin_list;
	*begin_list = node;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	ft_list_sort1(t_list **begin_list, int (*cmp)())
{
	t_list	*node;
	t_list	*next_node;
	void	*tmp;

	if (!begin_list || !*begin_list || !cmp)
		return ;
	node = *begin_list;
	while (node)
	{
		next_node = node->next;
		while (next_node)
		{
			if (cmp(node->data, next_node->data) > 0)
			{
				tmp = node->data;
				node->data = next_node->data;
				next_node->data = tmp;
			}
			next_node = next_node->next;
		}
		node = node->next;
	}
}

static void	print_list(char *name, t_list *list)
{
	printf("%s: ", name);
	while (list)
	{
		printf("\"%s\"", (char *)list->data);
		if (list->next)
		printf(" -> ");
		list = list->next;
	}
	printf("\n");
}

static void	free_list(t_list *list)
{
	t_list	*tmp;
	
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

void	ft_list_sort(t_list **begin_list, int (*cmp)());

int	main(void)
{
	t_list	*lista;
	t_list	*lista2;

	lista = NULL;
	lista2 = NULL;

	printf("\nTEST 0: lista = NULL\n");

	ft_list_sort1(&lista, ft_strcmp);
	ft_list_sort(&lista2, ft_strcmp);

	print_list("sort1", lista);
	print_list("sort ", lista2);

	printf("\nTEST 1\n");

	ft_list_push_front1(&lista, "elemento1");
	ft_list_push_front1(&lista2, "elemento1");

	print_list("antes sort1", lista);
	print_list("antes sort ", lista2);

	ft_list_sort1(&lista, ft_strcmp);
	ft_list_sort(&lista2, ft_strcmp);

	print_list("despues sort1", lista);
	print_list("despues sort ", lista2);

	printf("\nTEST 2\n");

	ft_list_push_front1(&lista, "elemento2");
	ft_list_push_front1(&lista2, "elemento2");

	print_list("antes sort1", lista);
	print_list("antes sort ", lista2);

	ft_list_sort1(&lista, ft_strcmp);
	ft_list_sort(&lista2, ft_strcmp);

	print_list("despues sort1", lista);
	print_list("despues sort ", lista2);

	printf("\nTEST 3\n");

	ft_list_push_front1(&lista, "elemento3");
	ft_list_push_front1(&lista, "elemento3");
	ft_list_push_front1(&lista, "elemento3");

	ft_list_push_front1(&lista2, "elemento3");
	ft_list_push_front1(&lista2, "elemento3");
	ft_list_push_front1(&lista2, "elemento3");

	print_list("antes sort1", lista);
	print_list("antes sort ", lista2);

	ft_list_sort1(&lista, ft_strcmp);
	ft_list_sort(&lista2, ft_strcmp);

	print_list("despues sort1", lista);
	print_list("despues sort ", lista2);

	printf("\nTEST 4\n");

	ft_list_push_front1(&lista, "zelemento4");
	ft_list_push_front1(&lista, "relemento4");
	ft_list_push_front1(&lista, "lelemento4");
	ft_list_push_front1(&lista, "Aelemento4");
	ft_list_push_front1(&lista, "aelemento4");

	ft_list_push_front1(&lista2, "zelemento4");
	ft_list_push_front1(&lista2, "relemento4");
	ft_list_push_front1(&lista2, "lelemento4");
	ft_list_push_front1(&lista2, "Aelemento4");
	ft_list_push_front1(&lista2, "aelemento4");

	print_list("antes sort1", lista);
	print_list("antes sort ", lista2);

	ft_list_sort1(&lista, ft_strcmp);
	ft_list_sort(&lista2, ft_strcmp);

	print_list("despues sort1", lista);
	print_list("despues sort ", lista2);

	printf("\nTEST 5\n");

	ft_list_sort1(&lista, ft_strcmp);
	ft_list_sort(&lista2, ft_strcmp);

	print_list("sort1", lista);
	print_list("sort ", lista2);

	free_list(lista);
	free_list(lista2);

	return (0);
}