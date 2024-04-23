/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:38:06 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/23 13:19:59 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "utils/philo_utils.h"
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

# define ENDLESS -1

# define FREE 0
# define TAKEN 1
# define INACTIVE -1

# define EATING 10
# define THINKING 11
# define SLEEPING 12
# define DEAD 13

# define R_FORK 20
# define L_FORK 21

typedef struct s_philo	t_philo;

typedef struct s_start_values
{
	int					nb_philo;
	long int			start_time;
	int					ttd;
	int					tte;
	int					tts;
	int					total_meals;
	pthread_mutex_t		*tmeals_lock;
}						t_args;

typedef struct s_fork
{
	pthread_mutex_t		*lock;
	int					state;
}						t_fork;

typedef struct s_philosopher
{
	pthread_t			*thread;
	int					id;
	int					state;
	t_args				*sval_link;
	t_philo				*table;
}						t_thinker;

typedef struct s_philo
{
	t_args				*start_args;
	t_thinker			**philos;
	t_fork				**forks;
}						t_philo;

int						create_threads(t_philo *data);
void					*philo_routine(void *thinker);
int						find_fork(t_thinker *thinker, int to_find);
t_bool					take_forks(t_thinker *thinker, int lfid, int rfid);
long int				get_time_ld(void);
int						destroy_mutex_forks(t_fork **list);
int						destroy_pthread_philos(t_thinker **list);
t_bool					setup_thinkers(t_thinker *philo, t_args *sval_addr,
							t_philo *table);
t_args					*save_args(char **args, int nb_args);
t_bool					setup_fork(t_fork *fork);
t_bool					check_args(char **args, int nb_args);
int						free_and_exit(t_philo *data, int exitcode);
t_philo					*init_data(char **args, int nb_args);
int						error_message(int errcode, char *source);
void					print_state(t_thinker *thinker, int flag);

#endif