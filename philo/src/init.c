/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:34:01 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/05/01 20:15:13 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static t_bool	create_forks(t_env *env, pthread_mutex_t **forks)
{
	int	nb_philos;

	if (!env)
		return (FALSE);
	nb_philos = env->nb_philo;
	forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *)
			* (nb_philos + 1));
	forks[nb_philos] = NULL;
	while (--nb_philos > -1)
	{
		printf("i philo %d\n", nb_philos);
		forks[nb_philos] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!forks[nb_philos]
			|| pthread_mutex_init(forks[nb_philos], NULL) != 0)
		{
			(ft_arrfree((void **)forks), free(forks));
			return (FALSE);
		}
	}
	env->forks = forks;
	return (TRUE);
}

static t_bool	setup_philo(t_env *env, t_thinker *philo, int id)
{
	philo->env = env;
	philo->id = id;
	philo->start = 0;
	philo->lf_id = INACTIVE;
	philo->rf_id = INACTIVE;
	philo->state = INACTIVE;
	philo->thread = (pthread_t *)malloc(sizeof(pthread_t));
	if (!philo->thread)
		return (FALSE);
	return (TRUE);
}

static t_bool	init_philos(t_env *env, t_thinker **philos)
{
	int	nb_philos;

	if (!env)
		return (FALSE);
	nb_philos = env->nb_philo;
	philos = (t_thinker **)malloc(sizeof(t_thinker *) * (nb_philos + 1));
	if (!philos)
		return (FALSE);
	philos[nb_philos] = NULL;
	while (--nb_philos > -1)
	{
		philos[nb_philos] = (t_thinker *)malloc(sizeof(t_thinker));
		if (!philos[nb_philos] || setup_philo(env, philos[nb_philos],
				nb_philos) == FALSE)
		{
			(ft_arrfree((void **)philos)), free(philos);
			return (FALSE);
		}
	}
	env->philos = philos;
	return (TRUE);
}

t_bool	init_env(int argc, char **argv, t_env *env)
{
	if (argc == 6)
		env->total_meals = ft_atoi(argv[5]);
	else
		env->total_meals = ENDLESS;
	env->nb_philo = ft_atoi(argv[1]);
	env->ttd_us = (ft_atoi(argv[2]) * 1000);
	env->tte_us = (ft_atoi(argv[3]) * 1000);
	env->tts_us = (ft_atoi(argv[4]) * 1000);
	if (init_philos(env, env->philos) == FALSE)
		return (FALSE);
	if (create_forks(env, env->forks) == FALSE)
		return (FALSE);
	env->dead_philo = FALSE;
	env->monitoring = (pthread_t *)malloc(sizeof(pthread_t));
	if (!env->monitoring)
		return (FALSE);
	env->print_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!env->print_lock || pthread_mutex_init(env->print_lock, NULL) != 0)
		return (FALSE);
	env->struct_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!env->print_lock || pthread_mutex_init(env->print_lock, NULL) != 0)
		return (FALSE);
	return (TRUE);
}
