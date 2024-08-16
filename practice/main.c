#include <stdlib.h>
#include <stdio.h>

typedef struct s_list
{
	int				value;
	struct s_list	*next;
}	t_list;

t_list	*ft_create_node(int value)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->next = NULL;

	return (new_node);
}

t_list	*ft_create_list(int *input, int size)
{
	t_list	*head;
	t_list	*current;
	t_list	*new_node;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (i < size)
	{
		new_node = ft_create_node(input[i]);
		if (head == NULL)
		{
			head = new_node;
			current = head;
		}
		else
		{
			current->next = new_node;
			current = current->next;
		}
		i++;
	}
	return (head);
}

void	ft_print_list(t_list *head)
{
	t_list	*current = head;
	while(current != NULL)
	{
		printf("%d ", current->value);
		current = current->next;
	}
	printf("\n");
}

void	ft_free_list(t_list *head)
{
	t_list	*current;
	t_list	*next_node;

	current = head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
}

int	main()
{
	t_list	*head;
	int		array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int		size = sizeof(array) / sizeof(array[0]);

	head =	ft_create_list(array, size);
	printf("Linked list values: ");
	ft_print_list(head);
	ft_free_list(head);
}
