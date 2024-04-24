/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:54:59 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/24 14:51:19 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_bool	take_forks(t_thinker *thinker, int lfid, int rfid)
{
	if (pthread_mutex_lock(thinker->table->forks[lfid]->lock) == 0)
	{
			if (thinker->table->forks[lfid]->state == TAKEN
				|| thinker->table->forks[rfid]->state == TAKEN)
			return (FALSE);
		thinker->table->forks[lfid]->state = TAKEN;
		print_state(thinker, L_FORK);
		if (pthread_mutex_lock(thinker->table->forks[rfid]->lock) == 0)
		{
			thinker->table->forks[rfid]->state = TAKEN;
			print_state(thinker, R_FORK);
			return (TRUE);
		}
		else
		{
			pthread_mutex_unlock(thinker->table->forks[lfid]->lock);
			thinker->table->forks[lfid]->state = FREE;
		}
	}
	return (FALSE);
}
