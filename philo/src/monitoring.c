/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:14:32 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/05/02 13:25:55 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// GARDE LES LOCK JUSQUA ARRET TOTAL PROGRAMME POUR EMPECHER IMPRESSION ET BOUFFE
void	*monitoring_routine(void *env)
{
	t_env	*env_cast;

	env_cast = (t_env *)env;
	while (1)
	{
		usleep(50);
		pthread_mutex_lock(env_cast->struct_lock);
		if (env_cast->dead_philo == TRUE || get_time_ld()
			- env_cast->last_meal_t >= env_cast->ttd_us / 1000
			|| env_cast->total_meals == 0)
			break ;
		pthread_mutex_unlock(env_cast->struct_lock);
	}
	pthread_mutex_lock(env_cast->print_lock);
	printf("last_meal = %ld\tdead_philo = %d\ttotal_meals = %d\tTTD = %d / %ld\n",
		env_cast->last_meal_t, env_cast->dead_philo, env_cast->total_meals,
		env_cast->ttd_us / 1000, get_time_ld() - env_cast->last_meal_t);
	debug_data(env_cast, "MONIT_EXIT\n");
	return (NULL);
}
