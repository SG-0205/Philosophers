/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:59:50 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/22 13:36:24 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	find_fork(t_thinker *thinker, int to_find)
{
	if (to_find == R_FORK)
	{
		if (thinker->id == thinker->sval_link->nb_philo - 1)
			return (0);
		else
			return (thinker->id + 1);
	}
	else if (to_find == L_FORK)
	{
		if (thinker->id == 0)
			return (thinker->sval_link->nb_philo - 1);
		else
			return (thinker->id - 1);
	}
	return (0);
}

t_bool	try_eat(t_thinker *thinker, int rf_id, int lf_id)
{
	if (pthread_mutex_lock(thinker->table->forks[lf_id]) == 0
		&& pthread_mutex_lock(thinker->table->forks[rf_id]) == 0)
	{
		thinker->state = EATING;
		usleep(thinker->sval_link->tte);
		pthread_mutex_unlock(thinker->table->forks[rf_id]);
		pthread_mutex_unlock(thinker->table->forks[lf_id]);
		return (TRUE);
	}
	return (FALSE);
}

int	philo_routine(t_thinker *thinker)
{
	int	rf_id;
	int	lf_id;

	rf_id = find_fork(thinker, R_FORK);
	lf_id = find_fork(thinker, L_FORK);
	while (thinker->state != DEAD)
	{
		if (try_eat(thinker, rf_id, lf_id) == FALSE)
		{
			
		}
	}
}
