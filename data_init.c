/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:46:46 by librahim          #+#    #+#             */
/*   Updated: 2024/12/10 20:59:19 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_input(t_table	*t, char **v)
{
	t->philo_nbr = ft_atol(v[1]);
	if (t->philo_nbr > 200)
		return (1);
	if (t->philo_nbr < 0)
		return (1);
	t->time_to_die = ft_atol(v[2]) * 1000;
	t->time_to_eat = ft_atol(v[3]) * 1000;
	t->time_to_sleep = ft_atol(v[4]) * 1000;
	if (t->time_to_sleep < 60000
		|| t->time_to_die < 60000
		|| t->time_to_eat < 60000)
		return (1);
	if (v[5])
		t->max_meals = ft_atol(v[5]);
	else
		t->max_meals = -1;
	return (0);
}

int	data_init(t_table	*t)
{
	int	i;

	i = 0;
	t->end_sim = NO;
	t->ready_go = NO;
	t->philo_array = NULL;
	t->fork_array = NULL;
	t->philo_array = malloc(sizeof(t_philo) * t->philo_nbr);
	if ((!t->philo_array))
		return (write(2, "ERROR : allocation failed\n", 27), EXIT_FAILURE);
	t->fork_array = malloc(sizeof(t_fork) * t->philo_nbr);
	if (!t->fork_array)
		return (write(2, "ERROR : allocation failed\n", 27), EXIT_FAILURE);
	pthread_mutex_init(&t->table_mutex, NULL);
	pthread_mutex_init(&t->print_mtx, NULL);
	while (i < t->philo_nbr)
	{
		pthread_mutex_init(&t->fork_array[i].fork, NULL);
		i++;
	}
	philo_init(t);
	return (EXIT_SUCCESS);
}

void	philo_init(t_table	*t)
{
	int	i;

	i = -1;
	while (++i < t->philo_nbr)
	{
		t->philo_array[i].id = i + 1;
		t->philo_array[i].t_ptr = t;
		t->philo_array[i].meals_count = 0;
		assign_forks(&t->philo_array[i], t->fork_array);
	}
}

void	assign_forks(t_philo *p, t_fork	*forks)
{
	int	id;
	int n;

	n = p->t_ptr->philo_nbr;
	id = p->id;
	p->first_f = &forks[id - 1];
	p->second_f = &forks[id % n];
}

void	free_data(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->philo_nbr)
		pthread_mutex_destroy(&t->fork_array[i].fork);
	pthread_mutex_destroy(&t->table_mutex);
	pthread_mutex_destroy(&t->print_mtx);
	if (t->fork_array != NULL)
		free(t->fork_array);
	if (t->philo_array != NULL)
		free(t->philo_array);
	if (t != NULL)
		free(t);
}
