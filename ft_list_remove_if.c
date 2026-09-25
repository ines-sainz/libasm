#include "bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	ft_list_remove_if1(t_list **begin_list, void *data_ref,
		int (*cmp)(), void (*free_fct)(void *))
{
	t_list	**current;
	t_list	*tmp;

	if (begin_list == NULL)
		return ;
	current = begin_list;
	while (*current != NULL)
	{
		if ((*cmp)((*current)->data, data_ref) == 0)
		{
			tmp = *current;
			*current = (*current)->next;
			(*free_fct)(tmp->data);
			free(tmp);
		}
		else
			current = &(*current)->next;
	}
}

void	ft_list_remove_if(t_list **begin_list, void *data_ref,
		int (*cmp)(), void (*free_fct)(void *));


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
		free(tmp->data);
		free(tmp);
	}
}

static void	test_empty_list(void)
{
	t_list	*list1;
	t_list	*list2;

	list1 = NULL;
	list2 = NULL;
	
	printf("\nTEST 0: Lista = NULL\n");

	ft_list_remove_if1(&list1, "hello", ft_strcmp, free);
	ft_list_remove_if(&list2, "hello", ft_strcmp, free);

	print_list("ft_list_remove_if1", list1);
	print_list("ft_list_remove_if ", list2);

	free_list(list1);
	free_list(list2);
}

static void	test_remove_first(void)
{
	t_list	*list1;
	t_list	*list2;

	list1 = NULL;
	list2 = NULL;
	
	printf("\nTEST 1: Borrar menos primer elemento\n");

	ft_list_push_front1(&list1, strdup("world"));
	ft_list_push_front1(&list1, strdup("hello"));
	ft_list_push_front1(&list1, strdup("hello"));

	ft_list_push_front1(&list2, strdup("world"));
	ft_list_push_front1(&list2, strdup("hello"));
	ft_list_push_front1(&list2, strdup("hello"));

	print_list("antes ft_list_remove_if1", list1);
	print_list("antes ft_list_remove_if", list2);

	ft_list_remove_if1(&list1, "hello", ft_strcmp, free);
	ft_list_remove_if(&list2, "hello", ft_strcmp, free);

	print_list("Despues ft_list_remove_if1", list1);
	print_list("Despues ft_list_remove_if ", list2);

	free_list(list1);
	free_list(list2);
}

static void	test_remove_middle(void)
{
	t_list	*list1;
	t_list	*list2;

	list1 = NULL;
	list2 = NULL;
	
	printf("\nTEST 2: Borrar el del medio\n");

	ft_list_push_front1(&list1, strdup("three"));
	ft_list_push_front1(&list1, strdup("hello"));
	ft_list_push_front1(&list1, strdup("one"));

	ft_list_push_front1(&list2, strdup("three"));
	ft_list_push_front1(&list2, strdup("hello"));
	ft_list_push_front1(&list2, strdup("one"));

	print_list("Antes ft_list_remove_if1", list1);
	print_list("Antes ft_list_remove_if ", list2);

	ft_list_remove_if1(&list1, "hello", ft_strcmp, free);
	ft_list_remove_if(&list2, "hello", ft_strcmp, free);

	print_list("Despues ft_list_remove_if1", list1);
	print_list("Despues ft_list_remove_if ", list2);

	free_list(list1);
	free_list(list2);
}

static void	test_remove_last(void)
{
	t_list	*list1;
	t_list	*list2;

	printf("\nTEST 3: Borrar el primero\n");

	list1 = NULL;
	list2 = NULL;

	ft_list_push_front1(&list1, strdup("hello"));
	ft_list_push_front1(&list1, strdup("two"));
	ft_list_push_front1(&list1, strdup("one"));

	ft_list_push_front1(&list2, strdup("hello"));
	ft_list_push_front1(&list2, strdup("two"));
	ft_list_push_front1(&list2, strdup("one"));

	print_list("Antes ft_list_remove_if1", list1);
	print_list("Antes ft_list_remove_if ", list2);

	ft_list_remove_if1(&list1, "hello", ft_strcmp, free);
	ft_list_remove_if(&list2, "hello", ft_strcmp, free);

	print_list("Despues ft_list_remove_if1", list1);
	print_list("Despues ft_list_remove_if ", list2);

	free_list(list1);
	free_list(list2);
}

static void	test_remove_multiple(void)
{
	t_list	*list1;
	t_list	*list2;

	list1 = NULL;
	list2 = NULL;
	
	printf("\nTEST 4: Borrar varios\n");

	ft_list_push_front1(&list1, strdup("hello"));
	ft_list_push_front1(&list1, strdup("two"));
	ft_list_push_front1(&list1, strdup("hello"));
	ft_list_push_front1(&list1, strdup("one"));
	ft_list_push_front1(&list1, strdup("hello"));

	ft_list_push_front1(&list2, strdup("hello"));
	ft_list_push_front1(&list2, strdup("two"));
	ft_list_push_front1(&list2, strdup("hello"));
	ft_list_push_front1(&list2, strdup("one"));
	ft_list_push_front1(&list2, strdup("hello"));

	print_list("Antes ft_list_remove_if1", list1);
	print_list("Antes ft_list_remove_if ", list2);

	ft_list_remove_if1(&list1, "hello", ft_strcmp, free);
	ft_list_remove_if(&list2, "hello", ft_strcmp, free);

	print_list("Despues ft_list_remove_if1", list1);
	print_list("Despues ft_list_remove_if ", list2);

	free_list(list1);
	free_list(list2);
}

static void	test_remove_consecutive(void)
{
	t_list	*list1;
	t_list	*list2;

	list1 = NULL;
	list2 = NULL;
	
	printf("\nTEST 5: Varios seguidos\n");

	ft_list_push_front1(&list1, strdup("three"));
	ft_list_push_front1(&list1, strdup("hello"));
	ft_list_push_front1(&list1, strdup("hello"));
	ft_list_push_front1(&list1, strdup("hello"));
	ft_list_push_front1(&list1, strdup("one"));

	ft_list_push_front1(&list2, strdup("three"));
	ft_list_push_front1(&list2, strdup("hello"));
	ft_list_push_front1(&list2, strdup("hello"));
	ft_list_push_front1(&list2, strdup("hello"));
	ft_list_push_front1(&list2, strdup("one"));

	print_list("Antes ft_list_remove_if1", list1);
	print_list("Antes ft_list_remove_if ", list2);

	ft_list_remove_if1(&list1, "hello", ft_strcmp, free);
	ft_list_remove_if(&list2, "hello", ft_strcmp, free);

	print_list("Despues ft_list_remove_if1", list1);
	print_list("Despues ft_list_remove_if ", list2);

	free_list(list1);
	free_list(list2);
}

static void	test_remove_all(void)
{
	t_list	*list1;
	t_list	*list2;

	printf("\nTEST 6: Borrar todos\n");

	list1 = NULL;
	list2 = NULL;

	ft_list_push_front1(&list1, strdup("hello"));
	ft_list_push_front1(&list1, strdup("hello"));
	ft_list_push_front1(&list1, strdup("hello"));

	ft_list_push_front1(&list2, strdup("hello"));
	ft_list_push_front1(&list2, strdup("hello"));
	ft_list_push_front1(&list2, strdup("hello"));

	print_list("Antes ft_list_remove_if1", list1);
	print_list("Antes ft_list_remove_if ", list2);

	ft_list_remove_if1(&list1, "hello", ft_strcmp, free);
	ft_list_remove_if(&list2, "hello", ft_strcmp, free);

	print_list("Despues ft_list_remove_if1", list1);
	print_list("Despues ft_list_remove_if ", list2);

	free_list(list1);
	free_list(list2);
}

static void	test_no_match(void)
{
	t_list	*list1;
	t_list	*list2;

	printf("\nTEST 7: No encontrado\n");

	list1 = NULL;
	list2 = NULL;

	ft_list_push_front1(&list1, strdup("three"));
	ft_list_push_front1(&list1, strdup("two"));
	ft_list_push_front1(&list1, strdup("one"));

	ft_list_push_front1(&list2, strdup("three"));
	ft_list_push_front1(&list2, strdup("two"));
	ft_list_push_front1(&list2, strdup("one"));

	print_list("Antes ft_list_remove_if1", list1);
	print_list("Antes ft_list_remove_if ", list2);

	ft_list_remove_if1(&list1, "hello", ft_strcmp, free);
	ft_list_remove_if(&list2, "hello", ft_strcmp, free);

	print_list("Despues ft_list_remove_if1", list1);
	print_list("Despues ft_list_remove_if ", list2);

	free_list(list1);
	free_list(list2);
}

int	main(void)
{
	test_empty_list();
	test_remove_first();
	test_remove_middle();
	test_remove_last();
	test_remove_multiple();
	test_remove_consecutive();
	test_remove_all();
	test_no_match();

	return (0);
}
