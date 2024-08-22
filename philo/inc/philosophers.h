/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:15:40 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/22 14:37:03 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>

# define MAXPHILO 200
# define MINTIME 60
# define INPUT "You need to input: \n\t\"./philo [number_of_philosophers] \
				\\\n\t\t[time_to_die] [time_to_eat] [time_to_sleep] \\\n\t\t \
				(number_of_times_each_philosopher_must_eat)\""
# define INIT "Failed to initialize mutex\n"
# define THREAD "Failed to create thread or join thread\n"
# define MEMORY "Failed to allocate memory for forks\n"
# define NUMBER " : Not a valid number\n"
# define PHILO_NUM "Number of Philosophers must be between 1 - 200\n"
# define TIME "Time to Die/Eat/Sleep must be at least 60ms\n"

typedef struct s_philo
{
	int				index;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	lastmeal;
	pthread_mutex_t	mealcount;
	pthread_t		philo;
	long long		last_meal_time;
	int				meal_count;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_meals;
	long long		start_time;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	sync;
	t_philo			*philos;
}	t_data;

//input.c
int			ft_input_range_check(t_data *data);
int			ft_input_check(int argc, char **argv);

// init.c
int			ft_init_data(t_data *data, char **argv);

//libft.c
void		ft_putstr_fd(char	*s, int fd);
size_t		ft_strlen(char *s);
int			ft_atoi_philo(char *nptr, int *error);
void		*ft_calloc(size_t nmemb, size_t size);

//monitor.c
void		ft_monitor(t_data *data);

//clean.c
void		ft_cleanup(t_data *data);

//print.c
void		ft_print_action(t_philo *philo, char *action, bool death);
int			print_error_message(int i, int error);
// void		ft_print_initialization(t_data *data);

//time.c
long long	ft_timestamp(void);
long long	ft_get_time(long long start_time);
long long	ft_timediff(long long past, long long pres);

//routine.c
void		*routine(void *arg);

#endif
