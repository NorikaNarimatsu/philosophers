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

// void *routine(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;

// 	printf("Philosopher %d has L[%p] and R[%p] with MC [%d] and LMT [%lu] ::: Starting work...\n",
// 		philo->index, (void *)philo->left_fork, (void *)philo->right_fork, philo->meal_count, philo->last_meal_time);

// 	printf("Philosopher %d is saying HIIIII...\n", philo->index);
// 	usleep(100000); // Sleep for 100 milliseconds to simulate work
// 	printf("Philosopher %d: Finished work...\n", philo->index);
// 	return (NULL);
// }

#include <sys/time.h>

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	*routine(void *arg)
{
	t_philo *philo;
	int		i = 0;

	philo = (t_philo *)arg;
	printf("Philosopher %d Starting work...\n", philo->index);
	while (i < 5)
	{
		// Step 1: Philosopher Eats
		// Picking up forks (locking mutexes)
		pthread_mutex_lock(philo->left_fork);
		printf("[%lu] Philosopher %d picked up left fork.\n", get_current_time(), philo->index);
		pthread_mutex_lock(philo->right_fork);
		printf("[%lu] Philosopher %d picked up right fork.\n", get_current_time(), philo->index);

		// Eating
		printf("[%lu] Philosopher %d is eating...\n", get_current_time(), philo->index);
		philo->last_meal_time = get_current_time();
		usleep(philo->data->time_eat * 1000);
		philo->meal_count++;

		// Put down forks (unlocking mutexes)
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("[%lu] Philosopher %d put down forks.\n", get_current_time(), philo->index);

		// Step 2: Philosopher Sleeps
		printf("[%lu] Philosopher %d is sleeping...\n", get_current_time(), philo->index);
		usleep(philo->data->time_sleep * 1000);

		// Step 3: Philosopher Thinks
		printf("[%lu] Philosopher %d is thinking...\n", get_current_time(), philo->index);
		usleep(50000);  // Philosopher thinks for 50 milliseconds
		i++;
	}
	printf("Philosopher %d: Finished work...\n", philo->index);

	return (NULL);
}


int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if ((argc != 5 && argc != 6) || ft_input_check(argv) == -1)
		return (ft_putstr_fd(INPUT_ERROR, 1), 1);
	printf("\nINPUT IS VALID\n\n");
	if (ft_init_data(&data, argv))
		return (ft_putstr_fd(INPUT_ERROR, 1), 1);
	// ft_print_initialization(&data);

	i = 0;
	while (i < data.num_philo)
	{
		if (pthread_create(&data.philosophers[i].philo, NULL, &routine, &data.philosophers[i]) != 0)
			return (ft_putstr_fd("Failed to create thread\n", 1), 1);
		i++;
	}
	i = 0;
	while (i < data.num_philo)
	{
		if (pthread_join(data.philosophers[i].philo, NULL) != 0)
			return (ft_putstr_fd("Failed to join thread\n", 1), 1);
		i++;
	}
	// Clean up and exit
	free(data.philosophers);
	free(data.forks);

	return (0);
}
