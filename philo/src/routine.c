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
	int i = 0;

	while (i <= time)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->someone_died != 1)
		{
			usleep(100);
			i = i + 100;
			pthread_mutex_unlock(&philo->data->death_mutex);
		}
		else
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break;
		}
	}
}
void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (philo->data->someone_died != 1)
		printf("%lld %d has take a fork\n", ft_get_current_time(philo->data->start_time), philo->index + 1);
	pthread_mutex_lock(philo->right_fork);
	if (philo->data->someone_died != 1)
		printf("%lld %d has take a fork\n", ft_get_current_time(philo->data->start_time), philo->index + 1);
	if (philo->data->someone_died != 1)
		printf("%lld %d is eating\n", ft_get_current_time(philo->data->start_time), philo->index + 1);
	philo->last_meal_time = ft_timestamp();
	// ft_usleep(philo, philo->data->time_eat * 1000);
	usleep(philo->data->time_eat * 1000);
	philo->meal_count++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	if (philo->data->someone_died != 1)
	{
		printf("%lld %d is sleeping\n", ft_get_current_time(philo->data->start_time), philo->index + 1);
		// ft_usleep(philo, philo->data->time_sleep * 1000);
		usleep(philo->data->time_sleep * 1000);
	}
}

void	ft_think(t_philo *philo)
{
	if (philo->data->someone_died != 1)
	{
		printf("%lld %d is thinking\n", ft_get_current_time(philo->data->start_time), philo->index + 1);
		usleep(1000);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->meal_count == 0 && philo->index % 2 == 0)
		{
			ft_think(philo);
			usleep(philo->data->time_eat * 1000 / 2);
		}
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
		if (philo->data->num_meals != -1 && philo->meal_count >= philo->data->num_meals)
			break;
	}
	return (NULL);
}
