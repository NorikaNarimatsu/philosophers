/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:27:32 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/22 12:59:06 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_print_action(t_philo *philo, char *action, bool death)
{
	if (death)
	{
		printf("%lld %d %s\n", \
				ft_get_time(philo->data->start_time), \
				philo->index + 1, \
				action);
		return ;
	}
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died == 0)
	{
		printf("%lld %d %s\n", \
				ft_get_time(philo->data->start_time), \
				philo->index + 1, \
				action);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
}

int	print_error_message(int i, int error)
{
	if (error == 1)
		return (printf("Integer Overflow Detected\n"), 1);
	if (i == 1)
		return (printf("Invalid Number of Philosophers [1 - 200]\n"), 1);
	else if (i == 2)
		return (printf("Invalid Time to Die [60 ms ~ ]\n"), 1);
	else if (i == 3)
		return (printf("Invalid Time to Eat [60 ms ~ ]\n"), 1);
	else if (i == 4)
		return (printf("Invalid Time to Sleep [60 ms ~ ]\n"), 1);
	else if (i == 5)
		return (printf("Invalid Number of Meals [Pptional]]\n"), 1);
	return (0);
}

// void	ft_print_initialization(t_data *data)
// {
// 	int	i;

// 	printf("- Initialization Results:\n");
// 	printf("- Number of Philosophers: %d\n", data->num_philo);
// 	printf("- Time to Die: %d ms\n", data->time_die);
// 	printf("- Time to Eat: %d ms\n", data->time_eat);
// 	printf("- Time to Sleep: %d ms\n", data->time_sleep);
// 	printf("- Number of Meals: %d\n\n", data->num_meals);
// 	i = 0;
// 	while (i < data->num_philo)
// 	{
// 		printf("Philo[%d] has L[%p] and R[%p] with MC [%d] and LMT [%llu]\n",
// 				data->philos[i].index, (void *)data->philos[i].left_fork,
// 				(void *)data->philos[i].right_fork, data->philos[i].meal_count,
// 				data->philos[i].last_meal_time);
// 		i++;
// 	}
// }
