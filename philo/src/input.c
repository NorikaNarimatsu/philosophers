/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:40:46 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/22 13:45:09 by nnarimat         ###   ########.fr       */
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
			return (ft_putstr_fd(arg, 2), ft_putstr_fd(NUMBER, 2), 0);
		i++;
	}
	return (1);
}

int	ft_input_range_check(t_data *data)
{
	if (data->num_philo > MAXPHILO || data->num_philo < 1)
		return (ft_putstr_fd(PHILO_NUM, 2), 1);
	if (data->time_die < MINTIME || data->time_eat < MINTIME \
		|| data->time_sleep < MINTIME)
		return (ft_putstr_fd(TIME, 2), 1);
	return (0);
}

int	ft_input_check(int argc, char **argv)
{
	int	error;

	if (argc != 5 && argc != 6)
		return (-1);
	error = 0;
	if (is_valid_num(argv[1]) == 0 \
		|| ft_atoi_philo(argv[1], &error) <= 0 || error)
		return (print_error_message(1, error), -1);
	if (is_valid_num(argv[2]) == 0 \
		|| ft_atoi_philo(argv[2], &error) <= 0 || error)
		return (print_error_message(2, error), -1);
	if (is_valid_num(argv[3]) == 0 \
		|| ft_atoi_philo(argv[3], &error) <= 0 || error)
		return (print_error_message(3, error), -1);
	if (is_valid_num(argv[4]) == 0 \
		|| ft_atoi_philo(argv[4], &error) <= 0 || error)
		return (print_error_message(4, error), -1);
	if (argv[5] && (is_valid_num(argv[5]) == 0 \
		|| ft_atoi_philo(argv[5], &error) <= 0 || error))
		return (print_error_message(5, error), -1);
	return (0);
}
