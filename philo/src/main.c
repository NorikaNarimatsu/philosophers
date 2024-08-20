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

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (ft_input_check(argc, argv) == -1)
		return (1);
	if (ft_init_data(&data, argv))
		return (ft_putstr_fd(INPUT_ERROR, 1), 1);
	pthread_mutex_init(&data.death_mutex, NULL);
	i = 0;
	while (i < data.num_philo)
	{
		if (pthread_create(&data.philosophers[i].philo, NULL, &routine, &data.philosophers[i]) != 0)
			return (ft_putstr_fd("Failed to create thread\n", 1), 1);
		i++;
	}
	ft_monitor(&data);
	i = 0;
	while (i < data.num_philo)
	{
		if (pthread_join(data.philosophers[i].philo, NULL) != 0)
			return (ft_putstr_fd("Failed to join thread\n", 1), 1);
		i++;
	}
	i = 0;
	while (i < data.num_philo)
	{
		pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data.death_mutex);
	return (free(data.philosophers), free(data.forks), 0);
}
