/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_dinner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 23:20:27 by librahim          #+#    #+#             */
/*   Updated: 2024/10/14 23:20:27 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	custom_usleep(long duration, t_table *t)
{
	long	start_time;

	(void)t;
	start_time = gettime();
	while ((gettime() - start_time) < duration
			&& !check_endsim(t))
		usleep(100);
}

void	take_forks_n_eat(t_philo *p)
{
	pthread_mutex_lock(&p->first_f->fork);
	print_state(p, liftfork);
	pthread_mutex_lock(&p->second_f->fork);
	print_state(p, liftfork);
	p->state = eating;
	print_state(p, eating);
	p->meals_count++;
	p->last_meal_t = gettime(usec);
	custom_usleep(p->t_ptr->time_to_eat, p->t_ptr);
	pthread_mutex_unlock(&p->first_f->fork);
	pthread_mutex_unlock(&p->second_f->fork);
	p->state = sleeping;
}

void	lone_philo_routine(t_philo *p)
{
	pthread_mutex_lock(&p->first_f->fork);
	print_state(p, liftfork);
	usleep(p->t_ptr->time_to_die);
	dyin_msg(p);
	return ;
}

int	check_endsim(t_table *t)
{
	pthread_mutex_unlock(&t->print_mtx);
	if (t->end_sim == YES)
	{
		pthread_mutex_unlock(&t->print_mtx);
		return (1);
	}
	pthread_mutex_unlock(&t->print_mtx);
	return (0);
}

void	*the_routine(void	*d)
{
	t_table	*t;
	t_philo	*p;

	(1) && (p = (t_philo *)d, t = p->t_ptr);
	if (t->philo_nbr == 1)
		return (lone_philo_routine(p), NULL);
	wait_everyone(t);
	if (p->id % 2)
		usleep(4000);
	p->last_meal_t = gettime();
	p->state = thinking;
	while(1)
	{
		if (check_endsim(t))
			break ;
		take_forks_n_eat(p);
		print_state(p, sleeping);
		custom_usleep(p->t_ptr->time_to_sleep, t);
		p->state = thinking;
		print_state(p, thinking);
		if (t->max_meals > 0 && p->meals_count == t->max_meals)
			break ;
	}
	return (NULL);
}

static int	monit_check(t_philo *p, t_table *t)
{
	if (p->state != eating
		&& (gettime() - p->last_meal_t) >= t->time_to_die)
	{
		print_state(p, dying);
		pthread_mutex_lock(&t->table_mutex);
		dyin_msg(p);
		t->end_sim = YES;
		pthread_mutex_unlock(&t->table_mutex);
		return (1);
	}
	if (p->meals_count == t->max_meals)
		return (1);
	return (0);
}

void	*monit_routine(void *d)
{
	t_table	*t;
	t_philo	*p;
	int		i;

	t = (t_table *)d;
	p = t->philo_array;
	wait_everyone(t);
	usleep(50000);
	while (1)
	{
		i = 0;
		if (t->philo_nbr == 1)
			break ;
		while (i < t->philo_nbr)
		{
			if (monit_check(&p[i], t) == 1)
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
