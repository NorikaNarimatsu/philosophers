#include <stdlib.h>
#include <stdio.h>

typedef struct s_list
{
	int	value;
	struct s_list *next;
} t_list;

t_list	*ft_create_node(int value)
{
	t_list *new_node;

	new_node = malloc(sizeof(t_list) * 1);
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_list	*ft_create_list(int *array)
{
	t_list	*head;
	t_list	*new_node;
	t_list	*current;
	int		i;

	i = 0;
	while (array[i])
	{
		new_node = ft_create_node(array[i]);
		if (!new_node)
			return (NULL);
		if (!head)
		{
			head = new_node;
			current = head;
		}
		else{
			current->next = new_node;
			current = current->next;
		}
		i++;
	}
	return (head);
}

void	ft_print_list(t_list	*head)
{
	t_list *current;

	current = head;
	while (current)
	{
		printf("%d ", current->value);
		current = current->next;
	}
	printf("\n");
}

int main()
{
	t_list	*head;
	int array[] = {1, 2, 3, 4, 5};

}