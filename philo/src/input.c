/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:40:46 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/14 15:43:58 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	is_valid_num(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
			return (-1);
		i++;
	}
	return (0);
}

static void	print_error_message(int i)
{
	if (i == 1)
		printf("Invalid Number of Philosophers\n");
	else if (i == 2)
		printf("Invalid Time to Die\n");
	else if (i == 3)
		printf("Invalid Time to Eat\n");
	else if (i == 4)
		printf("Invalid Time to Sleep\n");
	else if (i == 5)
		printf("Invalid Number of Meals\n");
}

int	ft_input_check(char **argv)
{
	if (is_valid_num(argv[1]) == -1 || ft_atoi(argv[1]) <= 0)
		return (print_error_message(1), -1);
	if (is_valid_num(argv[2]) == -1 ||ft_atoi(argv[2]) <= 0)
		return (print_error_message(2), -1);
	if (is_valid_num(argv[3]) == -1 ||ft_atoi(argv[3]) <= 0)
		return (print_error_message(3), -1);
	if (is_valid_num(argv[4]) == -1 ||ft_atoi(argv[4]) <= 0)
		return (print_error_message(4), -1);
	if (argv[5] && (is_valid_num(argv[1]) == -1 || ft_atoi(argv[5]) < 0))
		return (print_error_message(5), -1);
	return (0);
}