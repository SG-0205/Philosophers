/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:38:06 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/05/01 20:20:07 by sgoldenb         ###   ########.fr       */
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

typedef struct s_philosopher	t_thinker;

typedef struct s_start_values
{
	int					nb_philo;
	pthread_mutex_t		**forks;
	t_thinker			**philos;
	long int			last_meal_t;
	long int			start_time; 
	int					ttd_us;
	int					tte_us;
	int					tts_us;
	pthread_t			*monitoring;
	t_bool				dead_philo;
	int					total_meals;
	pthread_mutex_t		*struct_lock;
	pthread_mutex_t		*print_lock;
}						t_env;

typedef struct s_philosopher
{
	pthread_t			*thread;
	int					id;
	int					lf_id;
	int					rf_id;
	int					state;
	long int			start;
	t_env				*env;
}						t_thinker;

void	debug_data(t_env *env, char *src);
t_bool	init_env(int argc, char **argv, t_env *env);
int		rev_index(t_thinker *phi, int flag);
int		get_fork_id(t_thinker *phi, int flag);
void    *monitoring_routine(void *env);
void	*routine(void *phi);
void	print_state(t_thinker *phi, int flag);

#endif