/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:41:21 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/22 12:49:00 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	ft_destroy_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->philos[i].lastmeal);
		pthread_mutex_destroy(&data->philos[i].mealcount);
		i++;
	}
	free(data->philos);
	data->philos = NULL;
}

static void	ft_destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	data->forks = NULL;
}

void	ft_cleanup(t_data *data)
{
	if (data->philos)
	{
		ft_destroy_philos(data);
	}
	if (data->forks)
	{
		ft_destroy_forks(data);
	}
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->sync);
}
