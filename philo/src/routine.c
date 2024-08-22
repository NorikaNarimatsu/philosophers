/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:19:40 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/22 13:00:55 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_death_check(t_philo *philo)
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
	return (0);
}

int	ft_check_eat(t_philo *philo)
{
	long long	start_time;

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
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->left_fork) != 0)
		return (1);
	ft_print_action(philo, "has taken a fork", 0);
	if (philo->data->num_philo == 1)
		return (pthread_mutex_unlock(philo->left_fork), \
				usleep(philo->data->time_die * 1200), 1);
	if (pthread_mutex_lock(philo->right_fork) != 0)
		return (pthread_mutex_unlock(philo->left_fork), 1);
	ft_print_action(philo, "has taken a fork", 0);
	ft_print_action(philo, "is eating", 0);
	if (ft_death_check(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->lastmeal);
	philo->last_meal_time = ft_timestamp();
	pthread_mutex_unlock(&philo->lastmeal);
	if (ft_check_eat(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->mealcount);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->mealcount);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	ft_sleep(t_philo *philo)
{
	long long	start_time;

	ft_print_action(philo, "is sleeping", 0);
	start_time = ft_timestamp();
	while (ft_timestamp() - start_time < philo->data->time_sleep)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		usleep(500);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->sync);
	pthread_mutex_unlock(&philo->data->sync);
	if (philo->index % 2 == 0 && philo->data->num_philo != 1)
	{
		ft_print_action(philo, "is thinking", 0);
		usleep(philo->data->time_eat * 1000 / 2);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		ft_eat(philo);
		ft_sleep(philo);
		ft_print_action(philo, "is thinking", 0);
	}
	return (NULL);
}
