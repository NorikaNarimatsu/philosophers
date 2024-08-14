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

int	print_error_message(int i, int error)
{
	if (error == 1)
		return (printf("Integer Overflow Detected\n"), 1);
	if (i == 1)
		return (printf("Invalid Number of Philosophers\n"), 1);
	else if (i == 2)
		return (printf("Invalid Time to Die\n"), 1);
	else if (i == 3)
		return (printf("Invalid Time to Eat\n"), 1);
	else if (i == 4)
		return (printf("Invalid Time to Sleep\n"), 1);
	else if (i == 5)
		return (printf("Invalid Number of Meals\n"), 1);
	return (0);
}

int	ft_input_check(char **argv)
{
	int error;

	error = 0;
	if (is_valid_num(argv[1]) == -1 || 
		ft_atoi_philo(argv[1], &error) <= 0 || error)
		return (print_error_message(1, error), -1);
	if (is_valid_num(argv[2]) == -1 || 
		ft_atoi_philo(argv[2], &error) <= 0 || error)
		return (print_error_message(2, error), -1);
	if (is_valid_num(argv[3]) == -1 || 
		ft_atoi_philo(argv[3], &error) <= 0 || error)
		return (print_error_message(3, error), -1);
	if (is_valid_num(argv[4]) == -1 || 
		ft_atoi_philo(argv[4], &error) <= 0 || error)
		return (print_error_message(4, error), -1);
	if (argv[5] && (is_valid_num(argv[5]) == -1 || 
		ft_atoi_philo(argv[5], &error) < 0 || error))
		return (print_error_message(5, error), -1);
	return (0);
}
