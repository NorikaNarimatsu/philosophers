/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:40:49 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/22 13:38:04 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	ft_bzero(void *s, size_t n)
{
	char	*s_char;

	s_char = (char *)s;
	while (n > 0)
	{
		*s_char = '\0';
		s_char++;
		n--;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = 0;
	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	else if (((nmemb * size) / size) != nmemb)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

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
