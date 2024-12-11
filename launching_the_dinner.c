/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launching_the_dinner.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 01:31:01 by librahim          #+#    #+#             */
/*   Updated: 2024/12/10 20:07:19 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_the_threads(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->philo_nbr)
	{
		if (thread_handle(&(t->philo_array[i].pth_id), NULL, NULL, JOIN))
			return (1);
	}
	return (0);
}

int	launch_simu(t_table *t)
{
	int	i;

	i = -1;
	if (t->max_meals == 0)
		return (1);
	t->time = gettime();
	while (++i < t->philo_nbr)
	{
		if (thread_handle(&(t->philo_array[i].pth_id), the_routine,
				(void *)&t->philo_array[i], CREATE))
			return (1);
	}
	if (thread_handle(&t->mon, monit_routine, (void *)t, CREATE))
		return (1);
	t->ready_go = YES;
	if (join_the_threads(t))
		return (1);
	if (thread_handle(&t->mon, NULL, NULL, JOIN))
		return (1);
	return (0);
}

int	thread_handle(pthread_t *t, void *(fct)(void *), void *data, int todo)
{
	if (todo == CREATE)
	{
		if (pthread_create(t, NULL, fct, data))
			return (1);
	}
	else if (todo == JOIN)
	{
		if (pthread_join(*t, NULL))
			return (1);
	}
	return (0);
}
