/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:38:06 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/08/08 19:46:24 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo_utils.h"
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

# define ENDLESS -1

# define NB_LOCKS 3

# define FREE 0
# define TAKEN 1
# define INACTIVE -1

typedef struct s_philo	t_philo;

typedef enum e_timecodes
{
	S,
	MS,
	US
}						t_time_code;

typedef enum e_increase_decrease
{
	INCR,
	DECR
}						t_inc_dec;

typedef enum e_phifull
{
	HUNGRY,
	FULL
}						t_phifull;

typedef enum e_locks
{
	STRUCT,
	PRINT,
	MONITOR
}						t_mutex_id;

typedef enum e_forkside
{
	FIRST,
	LAST
}						t_fs;

typedef enum e_mutexcodes
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}						t_mutcodes;

typedef enum e_phistates
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	TAKE_FF,
	TAKE_SF,
}						t_phistates;

typedef struct s_thinker
{
	pthread_t			*thread;
	pthread_mutex_t		*phi_mut;
	int					id;
	int					eat_count;
	long				last_meal_t;
	t_bool				ate;
	t_philo				*table;
	int					*fork_ids;
}						t_thinker;

typedef struct s_philo
{
	int					nb_philos;
	int					nb_meals;
	t_bool				flag_stop;
	t_bool				flag_ready;
	long				start_time;
	int					tte;
	int					tts;
	int					ttd;
	int					running;
	pthread_t			*monitor;
	pthread_mutex_t		**forks;
	t_thinker			**philos;
	pthread_mutex_t		**locks;
}						t_philo;

long int				get_time(int ret_code);
t_philo					*init_data(int argc, char **argv);
t_bool					init_monitor(t_philo *table);
void					free_all(t_philo *vals);
void					print_vals(t_philo *vals);
int						check_digit(char **argv, int argc);
int						mutex_operation(pthread_mutex_t *mutex,
							t_mutcodes code);
int						thread_operation(pthread_t *thread, t_mutcodes code,
							void *(*var)(void *), void *data);
int						*get_fork_ids(t_philo *data, int phi_id);
int						set_value(pthread_mutex_t *mutex, int *val_ptr,
							int to_set);
int						get_value(pthread_mutex_t *mutex, int *to_get);
void					wait_ready(t_philo *table);
void					*philo_routine(void *data);
void					ft_usleep(long usec, t_philo *table);
void					print_state(t_thinker *phi, int phi_state);
t_bool					malloc_phi_mutexes(t_philo *table);
void					*monitor_thread(void *data);
int						update_value(pthread_mutex_t *mutex,
							int *to_update, t_inc_dec code);
long					get_value_l(pthread_mutex_t *mutex, long *to_get);
long					set_value_l(pthread_mutex_t *mutex,
							long *val_ptr, long to_set);
void					*print_full(t_philo *philo);
void					*lone_philo_routine(void *data);
#endif