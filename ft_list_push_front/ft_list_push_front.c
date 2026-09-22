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

void ft_list_push_front(t_list **begin_list, void *data);

int main()
{
	t_list	*lista;
	t_list	*tmp;

	lista = NULL;

	ft_list_push_front1(&lista, "elemento1");
    ft_list_push_front1(&lista, "elemento2");

	while (lista != NULL)
    {
        printf("Contenido: %s\n", (char *)lista->data);
		tmp = lista;
		lista = lista->next;
		free(tmp);
    }

	printf("------------------\n");

	t_list	*lista2;
	t_list	*tmp2;

	lista2 = NULL;

	ft_list_push_front1(&lista2, "elemento1");
    ft_list_push_front1(&lista2, "elemento2");

	while (lista2 != NULL)
    {
        printf("Contenido: %s\n", (char *)lista2->data);
		tmp2 = lista2;
		lista2 = lista2->next;
		free(tmp2);
    }
}