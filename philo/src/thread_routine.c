/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:59:50 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/23 13:50:11 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	decrease_tmeals(t_thinker *thinker)
{
	pthread_mutex_lock(thinker->sval_link->tmeals_lock);
	thinker->sval_link->total_meals --;
	if (thinker->sval_link->total_meals == 0)
		free_and_exit(thinker->table, 0);
	pthread_mutex_unlock(thinker->sval_link->tmeals_lock);
}

t_bool	try_eat(t_thinker *thinker, int rf_id, int lf_id)
{
	if (thinker->sval_link->total_meals == 0)
		printf("NO MORE SPAGHETT\n"), free_and_exit(thinker->table, 0);
	if (take_forks(thinker, lf_id, rf_id) == TRUE)
	{
		if (thinker->sval_link->total_meals != ENDLESS)
			decrease_tmeals(thinker);
		thinker->state = EATING;
		print_state(thinker, thinker->state);
		usleep(thinker->sval_link->tte);
		pthread_mutex_unlock(thinker->table->forks[rf_id]->lock);
		thinker->table->forks[rf_id]->state = FREE;
		pthread_mutex_unlock(thinker->table->forks[lf_id]->lock);
		thinker->table->forks[lf_id]->state = FREE;
		return (TRUE);
	}
	return (FALSE);
}

void	ph_sleep(t_thinker *thinker)
{
	thinker->state = SLEEPING;
	usleep(thinker->sval_link->tts);
	print_state(thinker, thinker->state);
}

void	ph_think(t_thinker *thinker)
{
	if (thinker->state == THINKING)
		return ;
	thinker->state = THINKING;
	print_state(thinker, thinker->state);
}

void	*philo_routine(void *thinker)
{
	int			rf_id;
	int			lf_id;
	long int	start_t;
	long int	end_t;
	t_thinker	*thinker_cast;

	thinker_cast = (t_thinker *)thinker;
	rf_id = find_fork(thinker_cast, R_FORK);
	lf_id = find_fork(thinker_cast, L_FORK);
	while (thinker_cast->state != DEAD)
	{
		start_t = get_time_ld();
		ph_think(thinker_cast);
		if (try_eat(thinker_cast, rf_id, lf_id) == TRUE)
			ph_sleep(thinker_cast);
		end_t = get_time_ld();
		if ((start_t - end_t) > thinker_cast->sval_link->ttd)
			thinker_cast->state = DEAD, print_state(thinker_cast, thinker_cast->state);
	}
	return (NULL);
}
