/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:40:49 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/14 15:46:18 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

size_t	ft_strlen(char *s)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}

void	ft_putstr_fd(char	*s, int fd)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
}

int	ft_atoi_philo(char *nptr, int *error)
{
	long	num;

	num = 0;
	*error = 0;

	while ((*nptr == ' ') || ((*nptr >= '\t') && (*nptr <= '\r')))
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (num > (LONG_MAX - (*nptr - '0')) / 10)
			return (*error = 1, 0);
		num = num * 10 + (*nptr - '0');
		nptr++;
	}
	if ((num) < INT_MIN || (num) > INT_MAX)
		return (*error = 1, 0);
	return ((int)(num));
}
