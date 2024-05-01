/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:27:47 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/05/01 20:21:50 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	usage(void)
{
	printf(YELLOW ITALIC "./philo [nb_philo] [ttd] [tte] [tts] (meals_nb)\n"
		RESET);
	return (EINVAL);
}

void	start_threads(t_env *env)
{
	int	nb_philos;

	nb_philos = env->nb_philo;
	pthread_create(env->monitoring, NULL, monitoring_routine, (void *)env);
	env->start_time = get_time_ld();
	while (--nb_philos > -1)
	{
		usleep(40);
		pthread_create(env->philos[nb_philos]->thread, NULL, routine,
			env);
	}
	pthread_join(*env->monitoring, NULL);
	while (nb_philos++ < env->nb_philo)
		pthread_cancel(*env->philos[nb_philos]->thread),
			pthread_join(*env->philos[nb_philos]->thread, NULL);
}

int	main(int argc, char **argv)
{
	t_env	*env;

	if (argc < 5 || argc > 6)
		return (usage());
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (1);
	if (init_env(argc, argv, env) == FALSE)
		return (1);
	debug_data(env, "INIT");
	start_threads(env);
	return (0);
}
