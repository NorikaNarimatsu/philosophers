/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:19:40 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/21 23:04:03 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_eat(t_philo *philo)
{
	long long start_time;

	start_time = ft_timestamp();
	if (pthread_mutex_lock(philo->left_fork) != 0)
		return (1);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died)
		return (pthread_mutex_unlock(&philo->data->death_mutex), pthread_mutex_unlock(philo->left_fork), 1);
	pthread_mutex_unlock(&philo->data->death_mutex);
	ft_log_action(philo, "has taken a fork");
	if (philo->data->num_philo  == 1)
		return (usleep(philo->data->time_die  * 1100), 1);
	if (ft_timestamp() - start_time > philo->data->time_die)
		return (pthread_mutex_unlock(philo->left_fork), 1);
	if (pthread_mutex_lock(philo->right_fork) != 0)
		return (pthread_mutex_unlock(philo->left_fork), 1);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	ft_log_action(philo, "has taken a fork");
	ft_log_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->lastmeal);
	philo->last_meal_time = ft_timestamp();
	pthread_mutex_unlock(&philo->lastmeal);
	pthread_mutex_unlock(&philo->data->death_mutex);
	start_time = ft_timestamp();
	while (ft_timestamp() - start_time < philo->data->time_eat)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		usleep(500);
	}
	philo->meal_count++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	ft_sleep(t_philo *philo)
{
	long long start_time;

	ft_log_action(philo, "is sleeping");

	start_time = ft_timestamp();
	while (ft_timestamp() - start_time < philo->data->time_sleep)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			return;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		usleep(500);
	}
}


void	ft_think(t_philo *philo)
{
	ft_log_action(philo, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->sync);
	pthread_mutex_unlock(&philo->data->sync);
	// printf ("%p\n", &philo->last_meal_time);
	if (philo->meal_count == 0 && philo->index % 2 == 0 && philo->data->num_philo != 1)
	{
		ft_think(philo);
		usleep(philo->data->time_eat * 1000 / 2);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
		// if (philo->data->num_meals != -1 && philo->meal_count >= philo->data->num_meals)
		// 	break;
	}
	return (NULL);
}
