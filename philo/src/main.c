/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:22:27 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/20 18:40:03 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_cleanup(t_data *data)
{
	int	i;

	if (data->philosophers)
	{
		free(data->philosophers);
		data->philosophers = NULL;
	}
	if (data->forks)
	{
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->print_mutex);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	data.philosophers = NULL;
	data.forks = NULL;
	if (ft_input_check(argc, argv) == -1)
		return (1);
	if (ft_init_data(&data, argv))
	{
		ft_cleanup(&data);
		ft_putstr_fd(INPUT_ERROR, 1);
		return (1);
	}
	if (pthread_mutex_init(&data.death_mutex, NULL) != 0 ||
		pthread_mutex_init(&data.print_mutex, NULL) != 0)
	{
		ft_cleanup(&data);
		ft_putstr_fd("Failed to initialize mutexes\n", 1);
		return (1);
	}
	i = 0;
	while (i < data.num_philo)
	{
		if (pthread_create(&data.philosophers[i].philo, NULL, &routine, &data.philosophers[i]) != 0)
		{
			ft_cleanup(&data);
			ft_putstr_fd("Failed to create thread\n", 1);
			return (1);
		}
		i++;
	}
	ft_monitor(&data);
	i = 0;
	while (i < data.num_philo)
	{
		if (pthread_join(data.philosophers[i].philo, NULL) != 0)
		{
			ft_putstr_fd("Failed to join thread\n", 1);
			return (1);
		}
		i++;
	}
	ft_cleanup(&data);
	return (0);
}
