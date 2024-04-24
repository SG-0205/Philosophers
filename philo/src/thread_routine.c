/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:59:50 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/24 15:08:35 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_bool	decrease_tmeals(t_thinker *thinker)
{
	if (pthread_mutex_lock(thinker->sval_link->tmeals_lock) == 0)
	{
		if (thinker->sval_link->total_meals == 0)
			return (FALSE);
		thinker->sval_link->total_meals --;
		pthread_mutex_unlock(thinker->sval_link->tmeals_lock);
	}
	return (TRUE);
}

t_bool	try_eat(t_thinker *thinker, int rf_id, int lf_id)
{
	if (take_forks(thinker, lf_id, rf_id) == TRUE)
	{
		thinker->state = EATING;
		print_state(thinker, thinker->state);
		if (thinker->sval_link->total_meals != ENDLESS)
			if (decrease_tmeals(thinker) == FALSE)
				return (FALSE);
		usleep(thinker->sval_link->tte);
		thinker->table->forks[lf_id]->state = FREE;
		thinker->table->forks[rf_id]->state = FREE;
		pthread_mutex_unlock(thinker->table->forks[rf_id]->lock);
		pthread_mutex_unlock(thinker->table->forks[lf_id]->lock);
		return (TRUE);
	}
	return (FALSE);
}

void	ph_sleep(t_thinker *thinker)
{
	if (thinker->state != EATING)
		return ;
	thinker->state = SLEEPING;
	print_state(thinker, thinker->state);
	usleep(thinker->sval_link->tts);
}

void	ph_think(t_thinker *thinker)
{
	if (thinker->state == THINKING)
		return ;
	thinker->state = THINKING;
	print_state(thinker, thinker->state);
}

t_bool	check_tmeals(t_thinker **addr_thinker)
{
	t_bool	ret_val;

	ret_val = ERROR;
	if (pthread_mutex_lock((*addr_thinker)->sval_link->tmeals_lock) == 0)
	{
		if ((*addr_thinker)->sval_link->total_meals == 0)
			ret_val = FALSE;
		else
			ret_val = TRUE;
		pthread_mutex_unlock((*addr_thinker)->sval_link->tmeals_lock);
	}
	return (ret_val);
}

void	*philo_routine(void *thinker)
{
	int			rf_id;
	int			lf_id;
	long int	start_t;
	// long int	end_t;
	t_thinker	*thinker_cast;

	thinker_cast = (t_thinker *)thinker;
	rf_id = find_fork(thinker_cast, R_FORK);
	lf_id = find_fork(thinker_cast, L_FORK);
	while (thinker_cast->state == INACTIVE || start_t > thinker_cast->sval_link->ttd)
	{
		if (thinker_cast->state == THINKING)
			start_t = get_time_ld();
		ph_think(thinker_cast);
		if (try_eat(thinker_cast, rf_id, lf_id) == FALSE)
			break ;
		ph_sleep(thinker_cast);
		if (thinker_cast->state == SLEEPING)
		start_t -= get_time_ld();
	}
	thinker_cast->state = DEAD, print_state(thinker_cast, thinker_cast->state);
	return (NULL);
}
