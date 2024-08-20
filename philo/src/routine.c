/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:19:40 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/20 19:53:43 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_usleep(t_philo *philo, int time)
{
	int waited_time = 0;

	while (waited_time < time)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		usleep(500);
		waited_time += 500;
	}
}


void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_log_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	ft_log_action(philo, "has taken a fork");
	ft_log_action(philo, "is eating");
	philo->last_meal_time = ft_timestamp();
	philo->meal_count++;
	ft_usleep(philo, philo->data->time_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_log_action(philo, "is sleeping");
	ft_usleep(philo, philo->data->time_sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	ft_log_action(philo, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);

		if (philo->meal_count == 0 && philo->index % 2 == 0 && philo->data->num_philo != 1)
		{
			ft_think(philo);
			usleep(philo->data->time_eat * 1000 / 2);
		}

		ft_eat(philo);
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);

		ft_sleep(philo);
		ft_think(philo);
		if (philo->data->num_meals != -1 && philo->meal_count >= philo->data->num_meals)
			break;
	}
	return (NULL);
}
