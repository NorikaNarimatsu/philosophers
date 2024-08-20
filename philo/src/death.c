/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:15:00 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/20 17:35:30 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void ft_monitor(t_data *data)
{
	int	i;
	int	all_ate;

	while (1)
	{
		i = 0;
		all_ate = 1;
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->death_mutex);
			if (ft_time_diff(data->philosophers[i].last_meal_time, ft_timestamp()) > data->time_die)
			{
				data->someone_died = 1;
				printf("%lld %d died\n", ft_get_current_time(data->start_time), data->philosophers[i].index + 1);
				pthread_mutex_unlock(&data->death_mutex);
				return;
			}
			if (data->num_meals != -1 && data->philosophers[i].meal_count < data->num_meals)
				all_ate = 0;
			pthread_mutex_unlock(&data->death_mutex);
			i++;
		}
		if (all_ate && data->num_meals != -1)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->someone_died = 100;
			pthread_mutex_unlock(&data->death_mutex);
			break;
		}
		if (data->someone_died)
			break;
	}
}