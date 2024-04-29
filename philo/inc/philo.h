/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:38:06 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/29 14:12:10 by sgoldenb         ###   ########.fr       */
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
	long int			start_time;
	int					ttd_ms;
	int					tte_ms;
	int					tts_ms;
	pthread_t			*monitoring;
	t_bool				dead_philo;
	int					total_meals;
	pthread_mutex_t		*struct_lock;
}						t_env;

typedef struct s_philosopher
{
	pthread_t			*thread;
	int					id;
	int					state;
	t_env				*env;
}						t_thinker;

void	debug_data(t_env *env, char *src);
t_bool	init_env(int argc, char **argv, t_env *env);

#endif