/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:15:40 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/21 15:04:24 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

#define MAXPHILO 200
#define MINTIME 60

#define INPUT "You need to input: \n\t\"./philo [number_of_philosophers] \\\n\t\t[time_to_die] [time_to_eat] [time_to_sleep] \\\n\t\t(number_of_times_each_philosopher_must_eat)\""
#define INIT "Failed to initialize mutex\n"
#define THREAD "Failed to create thread or join thread\n"
typedef	struct s_philo
{
	int				index;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		philo;
	long long		last_meal_time;
	int				meal_count;
	struct s_data	*data;
}	t_philo;

typedef	struct s_data
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_meals;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	int				someone_died;
	t_philo			*philosophers;
}	t_data;

void	ft_cleanup(t_data *data);

void ft_log_action(t_philo *philo, char *action);

// libft.c
void	ft_putstr_fd(char	*s, int fd);
size_t	ft_strlen(char *s);
int		ft_atoi_philo(char *nptr, int *error);

// input.c
int		ft_input_check(int argc, char **argv);
int		ft_input_range_check(t_data *data);

// init.c
void		ft_print_initialization(t_data *data);
int			ft_init_data(t_data *data, char **argv);

long long	ft_timestamp(void);
long long	ft_get_time(long long start_time);
long long	ft_timediff(long long past, long long pres);

void	*routine(void *arg);
void ft_monitor(t_data *data);

#endif
