/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:22:22 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/08/08 15:04:41 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	eat(t_thinker *thinker)
{
	mutex_operation(thinker->table->forks[thinker->fork_ids[FIRST]], LOCK);
	print_state(thinker, TAKE_FF);
	mutex_operation(thinker->table->forks[thinker->fork_ids[LAST]], LOCK);
	print_state(thinker, TAKE_SF);
	set_value_l(thinker->phi_mut, &thinker->last_meal_t, get_time(MS));
	thinker->eat_count ++;
	// printf("%ld LMT\t%ld\n", thinker->last_meal_t, get_time(MS));
	print_state(thinker, EATING);
	ft_usleep(thinker->table->tte * 1e3, thinker->table);
	if (thinker->table->nb_meals > 0
		&& thinker->eat_count == thinker->table->nb_meals)
		set_value(thinker->phi_mut, (int*)&thinker->ate, FULL);
	mutex_operation(thinker->table->forks[thinker->fork_ids[FIRST]], UNLOCK);
	mutex_operation(thinker->table->forks[thinker->fork_ids[LAST]], UNLOCK);
}//TODO MARQUER PHILO EN FULL ET INTEGREER LA LIMITE DES REPAS

static void	think(t_thinker *thinker)
{
	print_state(thinker, THINKING);
}

void	*lone_philo_routine(void *data)
{
	t_thinker	*thinker;

	thinker = (t_thinker *)data;
	wait_ready(thinker->table);
	set_value_l(thinker->phi_mut, &thinker->last_meal_t, get_time(MS));
	print_state(thinker, TAKE_FF);
	while (!get_value(thinker->table->locks[STRUCT],
		&thinker->table->flag_stop))
		usleep((thinker->table->ttd + thinker->table->tte) * 1e3);
	return (NULL);
}

void	*philo_routine(void *data)
{
	t_thinker	*thinker;

	thinker = (t_thinker *)data;
	thinker->ate = HUNGRY;
	wait_ready(thinker->table);
	set_value_l(thinker->phi_mut, &thinker->last_meal_t, get_time(MS));
	while (!get_value(thinker->table->locks[STRUCT],
			&thinker->table->flag_stop))
	{
		if (thinker->ate == FULL)
			break;
		eat(thinker);
		think(thinker);
		print_state(thinker, SLEEPING);
		ft_usleep(thinker->table->tts * 1e3, thinker->table);
		//think
	}
	return (NULL);
}
