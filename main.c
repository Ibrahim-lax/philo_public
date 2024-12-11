/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:46:43 by librahim          #+#    #+#             */
/*   Updated: 2024/12/10 20:59:03 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_table	*gt;

	if (!(ac == 5 || ac == 6))
		return (write(2, "ERROR : invalid input\n", 23), EXIT_FAILURE);
	gt = NULL;
	gt = (t_table *)malloc(sizeof(t_table));
	if (!gt)
	{
		write(2, "ERROR : allocation failed\n", 27);
		return (EXIT_FAILURE);
	}
	if (parse_input(gt, av))
	{
		free(gt);
		write(2, "ERROR : invalid input\n", 23);
		return (EXIT_FAILURE);
	}
	if (data_init(gt) == -1)
		return (free_data(gt), 1);
	
	if (launch_simu(gt))
		return (free_data(gt), EXIT_FAILURE);
	free_data(gt);
	return (EXIT_SUCCESS);
}
