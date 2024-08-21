/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:15:08 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/21 14:46:59 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_print_initialization(t_data *data)
{
	int	i;

	printf("- Initialization Results:\n");
	printf("- Number of Philosophers: %d\n", data->num_philo);
	printf("- Time to Die: %d ms\n", data->time_die);
	printf("- Time to Eat: %d ms\n", data->time_eat);
	printf("- Time to Sleep: %d ms\n", data->time_sleep);
	printf("- Number of Meals: %d\n\n", data->num_meals);
	i = 0;
	while (i < data->num_philo)
	{
		printf("Philosopher[%d] has L[%p] and R[%p] with MC [%d] and LMT [%llu]\n",
				data->philosophers[i].index, (void *)data->philosophers[i].left_fork,
				(void *)data->philosophers[i].right_fork, data->philosophers[i].meal_count,
				data->philosophers[i].last_meal_time);
		i++;
	}
}
static int ft_init_philo(t_data *data)
{
	int i;

	data->philosophers = calloc(data->num_philo, sizeof(t_philo));
	if (data->philosophers == NULL)
		return (printf("Failed to allocate memory for philosophers\n"), 1);

	data->forks = calloc(data->num_philo, sizeof(pthread_mutex_t));
	if (data->forks == NULL)
	{
		free(data->philosophers);
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
			free(data->philosophers);
			free(data->forks);
			return 1;
		}
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		data->philosophers[i].index = i;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i + 1) % data->num_philo];
		data->philosophers[i].meal_count = 0;
		data->philosophers[i].last_meal_time = data->start_time;
		data->philosophers[i].data = data;
		i++;
	}
	return 0;
}

int	ft_init_data(t_data *data, char **argv)
{
	int error;

	error = 0;
	data->philosophers = NULL;
	data->forks = NULL;
	data->num_philo = ft_atoi_philo(argv[1], &error);
	data->time_die = ft_atoi_philo(argv[2], &error);
	data->time_eat = ft_atoi_philo(argv[3], &error);
	data->time_sleep = ft_atoi_philo(argv[4], &error);
	data->start_time = ft_timestamp();
	data->someone_died = 0;
	if (argv[5] != NULL)
		data->num_meals = ft_atoi_philo(argv[5], &error);
	else
		data->num_meals = -1;
	if (ft_input_range_check(data) == 1)
		return (1);
	if (ft_init_philo(data) == 1)
		return (1);
	return (0);
}

void	ft_cleanup(t_data *data)
{
	int	i;

	if (data->philosophers)
	{
		free(data->philosophers);
		data->philosophers = NULL;
	}

	if (data->forks)
	{
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}

	pthread_mutex_destroy(&data->death_mutex);
}
