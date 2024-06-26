/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:47:06 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/05/01 19:01:14 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_state(t_thinker *phi, int flag)
{
	pthread_mutex_lock(phi->env->print_lock);
	if (flag == EATING)
		printf(GREEN "[%ld] : N°%d is eating\n" RESET, (get_time_ld()
				- phi->env->start_time), phi->id + 1);
	else if (flag == R_FORK || flag == L_FORK)
		printf(BLUE "[%ld] : N°%d has taken a fork\n" RESET, (get_time_ld()
				- phi->env->start_time), phi->id + 1);
	else if (flag == DEAD)
		printf(RED "[%ld] : N°%d has died\n" RESET, (get_time_ld()
				- phi->env->start_time), phi->id + 1);
	else if (flag == SLEEPING)
		printf(YELLOW "[%ld] : N°%d is sleeping\n" RESET, (get_time_ld()
				- phi->env->start_time), phi->id + 1);
	else if (flag == THINKING)
		printf(CYAN "[%ld] : N°%d is thinking\n" RESET, (get_time_ld()
				- phi->env->start_time), phi->id + 1);
	if (flag != DEAD)
		pthread_mutex_unlock(phi->env->print_lock);
}
