/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:15:00 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/21 22:53:20 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_log_action(t_philo *philo, char *action)
{
	if (strncmp(action, "died", 4) == 0) // HEREEEE
	{
		printf("%lld %d %s\n",
				ft_get_time(philo->data->start_time),
				philo->index + 1,
				action);
		return ;
	}
	pthread_mutex_lock(&philo->data->death_mutex);
	if (strncmp(action, "died", 4) == 0 || philo->data->someone_died == 0)
	{
		printf("%lld %d %s\n",
				ft_get_time(philo->data->start_time),
				philo->index + 1,
				action);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
}

void ft_monitor(t_data *data)
{
	int i;
	int is_meal_done;

	while (1)
	{
		i = 0;
		is_meal_done = 1;
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->death_mutex);
			pthread_mutex_lock(&data->philosophers[i].lastmeal);
			long long time_since_last_meal = ft_timediff(data->philosophers[i].last_meal_time, ft_timestamp());
			pthread_mutex_unlock(&data->philosophers[i].lastmeal);
			if (time_since_last_meal > data->time_die)
			{
				data->someone_died = 1;
				ft_log_action(&data->philosophers[i], "died");
				// printf("NOW DATA->SOMEONE_DIED is %d\n", data->someone_died);
				pthread_mutex_unlock(&data->death_mutex);
				return;
			}
			if (data->num_meals != -1 && data->philosophers[i].meal_count < data->num_meals)
			{
				is_meal_done = 0;
			}
			pthread_mutex_unlock(&data->death_mutex);
			i++;
		}
		if (is_meal_done && data->num_meals != -1)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_mutex);
			break;
		}
	}
}
