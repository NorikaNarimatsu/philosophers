/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:15:00 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/22 13:33:25 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	ft_check_death(t_data *data)
{
	int			i;
	long long	hunger;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&data->death_mutex);
		pthread_mutex_lock(&data->philos[i].lastmeal);
		hunger = ft_timediff(data->philos[i].last_meal_time, ft_timestamp());
		pthread_mutex_unlock(&data->philos[i].lastmeal);
		if (hunger > data->time_die)
		{
			data->someone_died = 1;
			ft_print_action(&data->philos[i], "died", 1);
			pthread_mutex_unlock(&data->death_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->death_mutex);
		i++;
	}
	return (0);
}

static int	ft_check_meals_done(t_data *data)
{
	int	i;
	int	is_meal_done;

	i = 0;
	is_meal_done = 1;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&data->death_mutex);
		pthread_mutex_lock(&data->philos[i].mealcount);
		if (data->num_meals != -1 \
			&& data->philos[i].meal_count < data->num_meals)
			is_meal_done = 0;
		pthread_mutex_unlock(&data->philos[i].mealcount);
		pthread_mutex_unlock(&data->death_mutex);
		i++;
	}
	return (is_meal_done);
}

void	ft_monitor(t_data *data)
{
	while (1)
	{
		if (ft_check_death(data))
			return ;
		if (ft_check_meals_done(data) && data->num_meals != -1)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
	}
}
