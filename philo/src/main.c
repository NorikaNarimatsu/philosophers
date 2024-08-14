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

// void	*routine(void)
// {
// 	printf("IN ROUTINE\n");
// }

// void	ft_init_philo(t_data *data, char **argv)
// {
// 	int	i;

// 	data->num_philo = ft_atoi(argv[1]);
// 	data->time_die = ft_atoi(argv[2]);
// 	data->time_eat = ft_atoi(argv[3]);
// 	data->time_sleep = ft_atoi(argv[4]);
// 	if (argv[5])
// 		data->num_meals = argv[5];
// 	else
// 		data->num_meals = -1;
// 	data->philosophers = calloc(data->num_philo, sizeof(t_philo));
// 	data->forks = calloc(data->num_philo, sizeof(pthread_mutex_t));

	// // Initialize mutexes for each fork
	// for (i = 0; i < data->num_philo; i++)
	// 	pthread_mutex_init(&data->forks[i], NULL);

	// // Initialize each philosopher's data
	// for (i = 0; i < data->num_philo; i++)
	// {
	// 	data->philosophers[i].index = i;
	// 	data->philosophers[i].left_fork = &data->forks[i];  // Left fork is the philosopher's own fork
	// 	data->philosophers[i].right_fork = &data->forks[(i + 1) % data->num_philo]; // Right fork is the next philosopher's fork
	// 	data->philosophers[i].meal_count = 0;
	// 	data->philosophers[i].last_meal_time = 0;
	// 	data->philosophers[i].data = data; // Link to shared data structure
	// }
// }


int	main(int argc, char **argv)
{
	// t_data	data;
	// int		i;

	if ((argc != 5 && argc != 6) || ft_input_check(argv) == -1)
		return (ft_putstr_fd(INPUT_ERROR, 1), exit(EXIT_FAILURE), 1);
	// ft_init_philo(&data, argv);

	// i = 0;
	// while (i < data.num_philo)
	// {
	// 	if (data.philosophers[i].philo = pthread_create(&data.philosophers[i].philo, NULL, &routine, NULL) != 0)
	// }

	return (0);
}
