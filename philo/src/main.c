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


int	main(int argc, char **argv)
{
	t_data	data;

	if ((argc != 5 && argc != 6) || ft_input_check(argv) == -1)
		return (ft_putstr_fd(INPUT_ERROR, 1), 1);
	printf("\nINPUT IS VALID\n\n");
	if (ft_init_data(&data, argv))
		return (ft_putstr_fd(INPUT_ERROR, 1), 1);
	ft_print_initialization(&data);

	// Clean up and exit
	free(data.philosophers);
	free(data.forks);

	return (0);
}
