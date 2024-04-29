/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:34:01 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/29 14:49:18 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static t_bool	setup_philo(t_env *env, t_thinker *philo, int id)
{
	philo->env = env;
	philo->id = id;
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
	philos = (t_thinker **)malloc(sizeof(t_thinker *) * nb_philos + 1);
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
	if (!env)
		return (FALSE);
	if (argc == 6)
		env->total_meals = ft_atoi(argv[5]);
	else
		env->total_meals = ENDLESS;
	env->nb_philo = ft_atoi(argv[1]);
	env->ttd_ms = (ft_atoi(argv[2]) * 1000);
	env->tte_ms = (ft_atoi(argv[3]) * 1000);
	env->tts_ms = (ft_atoi(argv[4]) * 1000);
	if (init_philos(env, env->philos) == FALSE)
		return (FALSE);
	return (TRUE);
}
