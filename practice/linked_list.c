#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_root
{
	int value;
	struct s_root *right;
	struct s_root *left;
} t_root;

/*
If the value is bigger, it should be put in the right tree
if the value is lower, it should be put in the left tree
If the value is equal, nothing should happen.
If the tree input is NULL, it should return the first node.
*/

t_root	*ft_create_node(int value)
{
	t_root *new_node;

	new_node = (t_root *)malloc(1 * sizeof(t_root));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->right = NULL;
	new_node->left = NULL;
	return (new_node);
}

t_root	*ft_create_tree(t_root *head, int value)
{
	t_root	*head_root;

	head_root = head;
	if (head == NULL)
		return (ft_create_node(value));
	while (head)
	{
		if (value == head->value)
			return (head);
		else if (value > head->value)
		{
			if (head->right != NULL)
				head = head->right;
			else
			{
				head->right = ft_create_node(value);
				return (head_root);
			}
		}
		else
		{
			if (head->left != NULL)
				head = head->left;
			else
			{
				head->left = ft_create_node(value);
				return (head_root);
			}
		}
	}
	return (head_root);
}

// t_root	*ft_create_tree(t_root *head, int value)
// {
// 	t_root *new_node;

// 	if (head == NULL)
// 	{
// 		new_node = (t_root *)malloc(sizeof(t_root));
// 		if (!new_node)
// 			return (NULL);
// 		new_node->value = value;
// 		new_node->right = NULL;
// 		new_node->left = NULL;
// 		return (new_node);
// 	}
// 	if (value == head->value)
// 		return (head);
// 	else if (value > head->value)
// 	{
// 		if (head->right == NULL)
// 			head->right = ft_create_tree(head->right, value);
// 		else
// 			ft_create_tree(head->right, value);
// 	}
// 	else if (value < head->value)
// 	{
// 		if (head->left == NULL)
// 			head->left = ft_create_tree(head->left, value);
// 		else
// 			ft_create_tree(head->left, value);
// 	}
// 	return (head);
// }

int main()
{
	t_root	*root = NULL;
	int values[] = {8,4,10,3,5,9,15};
	int i = 0;

	while (i < 8)
	{
		root = ft_create_tree(root, values[i]);
		i++;
	}
	printf("root value is %d\n", root->value);
	printf("root's right is %d\n", root->right->value);
	printf("root's left is %d\n", root->left->value);
	printf("root's right right is %d\n", root->right->right->value);
	printf("root's right left is %d\n", root->right->left->value);
	printf("root's left right is %d\n", root->left->right->value);
	printf("root's left left is %d\n", root->left->left->value);
	return (0);
}



// 		8
// 	4		10

// 3     5    9   15