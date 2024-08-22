/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:22:27 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/22 13:30:39 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	create_philosopher_threads(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->sync);
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&data->philos[i].philo, NULL, \
			&routine, &data->philos[i]) != 0)
		{
			pthread_mutex_unlock(&data->sync);
			return (ft_cleanup(data), ft_putstr_fd(THREAD, 1), 1);
		}
		i++;
	}
	data->start_time = ft_timestamp();
	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].last_meal_time = ft_timestamp();
		i++;
	}
	pthread_mutex_unlock(&data->sync);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (ft_input_check(argc, argv) == -1)
		return (ft_putstr_fd(INPUT, 1), 1);
	if (ft_init_data(&data, argv))
		return (ft_cleanup(&data), ft_putstr_fd(INPUT, 1), 1);
	if (create_philosopher_threads(&data) != 0)
		return (1);
	ft_monitor(&data);
	i = 0;
	while (i < data.num_philo)
	{
		if (pthread_join(data.philos[i].philo, NULL) != 0)
			return (ft_cleanup(&data), ft_putstr_fd(THREAD, 1), 1);
		i++;
	}
	return (ft_cleanup(&data), 0);
}
