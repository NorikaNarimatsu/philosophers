/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:15:40 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/14 17:21:23 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#define INPUT_ERROR "You need to input: \n\t\"./philo [number_of_philosophers] \\\n\t\t[time_to_die] [time_to_eat] [time_to_sleep] \\\n\t\t(number_of_times_each_philosopher_must_eat)\""

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_philo
{
	int			index;
	int			*right;
	int			*left;
	pthread_t	philo;
} t_philo;

typedef struct s_data
{
	int			num_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			num_meals;
	t_philo		*philosophers;
	int			*forks; // different data type used by one person
} t_data;


// libft.c
void	ft_putstr_fd(char	*s, int fd);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char	*nptr);

// input.c
int		ft_input_check(char **argv);


#endif
