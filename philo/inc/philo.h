/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:38:06 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/19 09:40:31 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "utils/philo_utils.h"
# include <pthread.h>

# define ENDLESS -1

# define FREE 0
# define TAKEN 1

typedef struct s_start_values
{
	int				nb_philo;
	int				ttd;
	int				tte;
	int				tts;
	int				total_meals;
	pthread_mutex_t	*tmeals_lock;
}					t_args;

typedef struct s_fork
{
	pthread_mutex_t	*lock;
	int				state;
}					t_fork;

typedef struct s_philo
{
	t_args		*start_args;
	pthread_t	**philos;
	t_fork		**forks;
}				t_philo;

#endif