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
#include <string.h>

void	ft_log_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->someone_died || strcmp(action, "died") == 0)
	{
		printf("%lld %d %s\n",
			ft_get_current_time(philo->data->start_time),
			philo->index + 1,
			action);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	ft_monitor(t_data *data)
{
	int			i;
	int			is_meal_done;
	long long	time_since_last_meal;

	while (1)
	{
		i = 0;
		is_meal_done = 1;
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->death_mutex);
			time_since_last_meal = ft_time_diff(data->philosophers[i].last_meal_time, ft_timestamp());
			if (time_since_last_meal > data->time_die)
			{
				printf("true\n");
				data->someone_died = 1;
				ft_log_action(&data->philosophers[i], "died");
				pthread_mutex_unlock(&data->death_mutex);
				return;
			}
			if (data->num_meals != -1 && data->philosophers[i].meal_count < data->num_meals)
				is_meal_done = 0;
			pthread_mutex_unlock(&data->death_mutex);
			i++;
		}

		if (is_meal_done && data->num_meals != -1)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->someone_died = 100;
			pthread_mutex_unlock(&data->death_mutex);
			break;
		}
		if (data->someone_died)
			break;
		usleep(1000);  // Sleep briefly to reduce CPU usage
	}
}
