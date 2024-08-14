/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:16:01 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/14 17:21:36 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

#define MAXPHILO 200
#define MINTIME 60

void	*routine(void)
{
	printf("IN ROUTINE\n");
}

void	ft_init_philo(t_data *data, char ** argv)
{
	int	i;

	data->num_philo = ft_atoi(argv[1]);
	if (data->num_philo > MAXPHILO)
		return (ft_putstr_fd("TOO BIG PHILO", 1), exit(EXIT_FAILURE), 1);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (data->num_philo < MINTIME || data->time_eat < MINTIME
		|| data->time_sleep < MINTIME)
		return (ft_putstr_fd("TOO LITTLE TIME", 1), exit(EXIT_FAILURE), 1);
	if (argv[5])
		data->num_meals = ft_atoi(argv[5]);
	data->philosophers = calloc(sizeof(t_philo), (data->num_philo + 1));
	data->forks = calloc(sizeof(int), (data->num_philo + 1));
	i = 0;
	while (i < data->num_philo)
	{
		data->philosophers[i].index = i;
		data->philosophers[i].right = i;
		if (i < data->num_philo - 1)
			data->philosophers[i].left = i + 1;
		else
			data->philosophers[i].left = 0;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if ((argc != 5 && argc != 6) || ft_input_check(argv) == -1)
		return (ft_putstr_fd(INPUT_ERROR, 1), exit(EXIT_FAILURE), 1);
	ft_init_philo(&data, argv);

	i = 0;
	while (i < data.num_philo)
	{
		if (data.philosophers[i].philo = pthread_create(&data.philosophers[i].philo, NULL, &routine, NULL) != 0)
	}

	return (0);
}
