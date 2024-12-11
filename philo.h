/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:34:36 by librahim          #+#    #+#             */
/*   Updated: 2024/12/10 08:26:30 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# define LOCK 0
# define UNLOCK 1
# define CREATE 2
# define INIT 3
# define DESTROY 4
# define JOIN 5
# define NO 7
# define YES 8
# define usec 10
# define eating 12
# define thinking 13
# define sleeping 14
# define dying 15
# define liftfork 16
# define running 17
# define finished 18

typedef pthread_mutex_t	mtx;

// ************* STRUCTS ********************

typedef	struct s_fork
{
	mtx			fork;
}				t_fork;

typedef struct s_table t_table;

typedef	struct s_philo
{
	int			id;
	int			meals_count;
	int			state;
	long		last_meal_t;
	t_fork		*first_f;
	t_fork		*second_f;
	pthread_t	pth_id;
	t_table		*t_ptr;
}				t_philo;

typedef	struct s_table
{
	int				philo_nbr;
	int				time_to_sleep; //const
	int				time_to_die; //const
	int				time_to_eat; // const
	int				max_meals; //const
	int				ready_go;//var
	int				end_sim;//var
	long			time; // var
	mtx				print_mtx;
	mtx				table_mutex;
	pthread_t		mon;
	t_fork			*fork_array;
	t_philo			*philo_array; 
}					t_table;

// ************************************** fcts **************************************

int			parse_input(t_table	*t, char **v);
void		print_error(char	*s);
int			data_init(t_table	*t);
void		print_state(t_philo *p, int state);
void		gerer_pth_err(int st, int oc);
void		philo_init(t_table	*t);
int			thread_handle(pthread_t *t, void *(fct)(void *), void *data, int todo);
void		assign_forks(t_philo *p, t_fork	*forks);
void		free_data(t_table *t);
void		wait_everyone(t_table	*t);
void		*monit_routine(void *d);
void		*the_routine(void	*d);
int			launch_simu(t_table *t);
long int    gettime();
void		end_sim(t_table *t);
long		ft_atol(char *nptr);
int			check_endsim(t_table *t);
void		dyin_msg(t_philo *p);

// ***********************************************************************************

#endif

// ./philo	nbr_of_philos     time_to_die       time_to_eat   time_to_sleep  [max nbr of meals]

// ALLOWED FUNCTIONS

/*       memset,    printf,     malloc,     free,      write,
   usleep,      gettimeofday,      pthread_create,
   pthread_detach,      pthread_join,      pthread_mutex_init,
   pthread_mutex_destroy,      pthread_mutex_lock,
   pthread_mutex_unlock




SHEET TESTS : 




Do not test with more than 200 philosophers.

Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than 60 ms.

Test 1 800 200 200. The philosopher should not eat and should die.

Test 5 800 200 200. No philosopher should die.

Test 5 800 200 200 7. No philosopher should die and the simulation should stop when
						every philosopher has eaten at least 7 times.
						
Test 4 410 200 200. No philosopher should die.

Test 4 310 200 100. One philosopher should die.

Test with 2 philosophers and check the different times: a death delayed by more 
				than 10 ms is unacceptable.
							
Test with any values of your choice to verify all the requirements.


Ensure philosophers die at the right time, that they don't steal forks, and so forth.


*/