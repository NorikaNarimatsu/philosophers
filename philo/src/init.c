/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:15:08 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/22 13:24:02 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	ft_init_mutexes(t_data *data, int i)
{
	if (pthread_mutex_init(&data->philos[i].lastmeal, NULL) != 0 \
		|| pthread_mutex_init(&data->philos[i].mealcount, NULL) != 0)
	{
		printf("Failed to initialize mutexes for philosopher %d\n", i);
		while (i >= 0)
		{
			pthread_mutex_destroy(&data->philos[i].lastmeal);
			pthread_mutex_destroy(&data->philos[i].mealcount);
			i--;
		}
		return (1);
	}
	return (0);
}

static int	ft_init_forks(t_data *data)
{
	int	i;

	data->forks = calloc(data->num_philo, sizeof(pthread_mutex_t));
	if (data->forks == NULL)
	{
		free(data->philos);
		return (printf("Failed to allocate memory for forks\n"), 1);
	}
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("Failed to initialize mutex for fork %d\n", i);
			while (i >= 0)
				pthread_mutex_destroy(&data->forks[i--]);
			free(data->philos);
			free(data->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	ft_init_philo(t_data *data)
{
	int	i;

	data->philos = calloc(data->num_philo, sizeof(t_philo));		// FT_CALLOC!
	if (data->philos == NULL)
		return (printf("Failed to allocate memory for philosophers\n"), 1);	// FD = 2 for all the PRINTF
	if (ft_init_forks(data) != 0)
		return (1);
	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].index = i;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philo];
		data->philos[i].meal_count = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;
		if (ft_init_mutexes(data, i) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_init_data(t_data *data, char **argv)
{
	int	error;

	error = 0;
	data->num_philo = ft_atoi_philo(argv[1], &error);
	data->time_die = ft_atoi_philo(argv[2], &error);
	data->time_eat = ft_atoi_philo(argv[3], &error);
	data->time_sleep = ft_atoi_philo(argv[4], &error);
	if (argv[5] != NULL)
		data->num_meals = ft_atoi_philo(argv[5], &error);
	else
		data->num_meals = -1;
	data->philos = NULL;
	data->forks = NULL;
	data->start_time = ft_timestamp();
	data->someone_died = 0;
	if (error || ft_input_range_check(data) == 1 || ft_init_philo(data) == 1)
		return (1);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0 \
		|| pthread_mutex_init(&data->sync, NULL) != 0)
		return (1);
	return (0);
}
