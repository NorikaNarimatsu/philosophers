/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:22:27 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/21 16:25:55 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (ft_input_check(argc, argv) == -1)
		return (1);
	if (ft_init_data(&data, argv))
		return (ft_cleanup(&data), ft_putstr_fd(INPUT, 1), 1);
	if (pthread_mutex_init(&data.death_mutex, NULL) != 0)
		return (ft_cleanup(&data), ft_putstr_fd(INIT, 1), 1);
	i = 0;
	while (i < data.num_philo)
	{
		if (pthread_create(&data.philosophers[i].philo, NULL, &routine, &data.philosophers[i]) != 0)
			return (ft_cleanup(&data), ft_putstr_fd(THREAD, 1), 1);
		i++;
	}
	ft_monitor(&data);
	i = 0;
	while (i < data.num_philo)
	{
		if (pthread_join(data.philosophers[i].philo, NULL) != 0)
			return (ft_cleanup(&data), ft_putstr_fd(THREAD, 1), 1);
		i++;
	}
	return (ft_cleanup(&data), 0);
}

/*valgrind thread */