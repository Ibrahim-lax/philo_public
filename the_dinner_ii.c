/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_dinner_ii.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 03:30:11 by librahim          #+#    #+#             */
/*   Updated: 2024/12/10 20:05:52 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_everyone(t_table	*t)
{
	while (t->ready_go == NO)
		;
}

void	dyin_msg(t_philo *p)
{
	long	t;

	t = (gettime() - p->t_ptr->time) / 1000;
	pthread_mutex_lock(&(p->t_ptr->print_mtx));
	printf("%ld %d died\n", t, p->id);
	pthread_mutex_unlock(&p->t_ptr->print_mtx);
}

void	print_state(t_philo *p, int state)
{
	long int	t;
	int			f;

	pthread_mutex_lock(&p->t_ptr->table_mutex);
	f = p->t_ptr->end_sim;
	t = (gettime() - p->t_ptr->time) / 1000;
	pthread_mutex_unlock(&p->t_ptr->table_mutex);
	pthread_mutex_lock(&p->t_ptr->print_mtx);
	if (f == YES)
	{
		pthread_mutex_unlock(&p->t_ptr->print_mtx);
		return ;
	}
	if (state == eating)
		printf("%ld %d is eating\n",t, p->id);
	else if (state == thinking)
		printf("%ld %d is thinking\n",t, p->id);
	else if (state == sleeping)
		printf("%ld %d is sleeping\n",t, p->id);
	else if (state == liftfork)
		printf("%ld %d has taken a fork\n",t, p->id);
	pthread_mutex_unlock(&p->t_ptr->print_mtx);
}
