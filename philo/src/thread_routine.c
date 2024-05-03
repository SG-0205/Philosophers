/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:21:53 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/05/03 13:07:28 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	try_sleep(t_thinker *phi)
{
	int	tts;

	tts = 0;
	if (phi->state != EATING)
		return ;
	pthread_mutex_lock(phi->env->struct_lock);
	tts = phi->env->tts_us;
	phi->state = SLEEPING;
	pthread_mutex_unlock(phi->env->struct_lock);
	print_state(phi, phi->state);
	usleep(tts);
}

static void	check_dead(t_thinker *phi)
{
	if (phi->state != THINKING)
		return ;
	printf("checkdead\n");
	pthread_mutex_lock(phi->env->struct_lock);
	printf("%ld\n", get_time_ld() - phi->start);
	printf("%d\n", phi->env->total_meals);
	if (get_time_ld() - phi->start >= phi->env->ttd_us / 1000)
	{
		phi->env->stop_b = TRUE;
		pthread_mutex_unlock(phi->env->struct_lock);
		phi->state = DEAD;
		print_state(phi, phi->state);
	}
	else if (phi->env->total_meals == 0)
		pthread_mutex_lock(phi->env->print_lock);
	pthread_mutex_unlock(phi->env->struct_lock);
}

static void	try_eat(t_thinker *phi)
{
	int	tte_us;

	tte_us = 0;
	pthread_mutex_lock(phi->env->forks[phi->lf_id]);
	print_state(phi, L_FORK);
	pthread_mutex_lock(phi->env->forks[phi->rf_id]);
	print_state(phi, R_FORK);
	pthread_mutex_lock(phi->env->struct_lock);
	phi->env->last_meal_t = get_time_ld();
	// printf("phi.env.lastmeal = %ld\n", phi->env->last_meal_t);
	phi->state = EATING;
	if (phi->env->total_meals != ENDLESS)
		phi->env->total_meals -= 1, printf("total_meals %d\n", phi->env->total_meals);
	tte_us = phi->env->tte_us;
	pthread_mutex_unlock(phi->env->struct_lock);
	print_state(phi, phi->state);
	usleep(tte_us);
	pthread_mutex_unlock(phi->env->forks[phi->rf_id]);
	pthread_mutex_unlock(phi->env->forks[phi->lf_id]);
}

static void	try_think(t_thinker *phi)
{
	int	ttt;

	ttt = 0;
	pthread_mutex_lock(phi->env->struct_lock);
	ttt = phi->env->ttt_us;
	phi->state = THINKING;
	pthread_mutex_unlock(phi->env->struct_lock);
	if (phi->state == THINKING)
		(usleep(ttt), print_state(phi, phi->state));
}

void	*routine(void *phi)
{
	t_thinker	*phi_cast;
	

	phi_cast = (t_thinker *)phi;
	phi_cast->lf_id = get_fork_id(phi, L_FORK);
	phi_cast->rf_id = get_fork_id(phi, R_FORK);
	printf("PHI[%d]\tL_F = %d | R_F = %d\n", phi_cast->id, phi_cast->lf_id, phi_cast->rf_id);
	while (1)
	{
		if (phi_cast->state == INACTIVE)
			phi_cast->start = get_time_ld();
		try_eat(phi_cast);
		if (phi_cast->state == EATING)
			try_sleep(phi);
		if (phi_cast->state == SLEEPING)
			try_think(phi);
		if (phi_cast->state == THINKING && get_time_ld() - phi_cast->start >= 800)
			check_dead(phi);
	}
	return (NULL);
}
