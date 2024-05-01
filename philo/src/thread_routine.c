/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:21:53 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/05/01 20:28:33 by sgoldenb         ###   ########.fr       */
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
	usleep(tts);
}

static void	check_dead(t_thinker *phi)
{
	if (phi->state != THINKING)
		return ;
	pthread_mutex_lock(phi->env->struct_lock);
	if (get_time_ld() - phi->start >= phi->env->ttd_us / 1000)
	{
		pthread_mutex_unlock(phi->env->struct_lock);
		phi->state = DEAD;
		print_state(phi, phi->state);
		phi->env->dead_philo = TRUE;
	}
	pthread_mutex_unlock(phi->env->struct_lock);
}

static void	try_eat(t_thinker *phi)
{
	if (phi->state == SLEEPING)
		return ;
	pthread_mutex_lock(phi->env->forks[phi->lf_id]);
	pthread_mutex_lock(phi->env->forks[phi->rf_id]);
	pthread_mutex_lock(phi->env->struct_lock);
	phi->env->last_meal_t = get_time_ld() - phi->start;
	phi->state = EATING;
	usleep(phi->env->tte_us);
	pthread_mutex_unlock(phi->env->struct_lock);
	print_state(phi, phi->state);
	pthread_mutex_unlock(phi->env->forks[phi->rf_id]);
	pthread_mutex_unlock(phi->env->forks[phi->lf_id]);
}

void	*routine(void *phi)
{
	t_thinker	*phi_cast;

	printf("ENV = %p\n", phi);
	phi_cast = (t_thinker *)phi;
	phi_cast->lf_id = get_fork_id(phi, L_FORK);
	phi_cast->rf_id = get_fork_id(phi, R_FORK);
	while (phi_cast->state != DEAD)
	{
		phi_cast->start = get_time_ld();
		phi_cast->state = THINKING;
		try_eat(phi_cast);
		if (phi_cast->state == EATING)
			try_sleep(phi);
		check_dead(phi);
	}
	return (NULL);
}
