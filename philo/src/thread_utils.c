/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:49:11 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/05/01 20:02:28 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	rev_index(t_thinker *phi, int flag)
{
	int	rev_index;

	rev_index = -1;
	if (flag == L_FORK)
	{
		pthread_mutex_lock(phi->env->struct_lock);
		rev_index = phi->env->nb_philo - 1;
		pthread_mutex_unlock(phi->env->struct_lock);
	}
	else if (flag == R_FORK)
		rev_index = 0;
	return (rev_index);
}

int	get_fork_id(t_thinker *phi, int flag)
{
	int	fork_id;

	fork_id = 0;
	if (flag == L_FORK)
	{
		if (phi->id == 0)
			return (rev_index(phi, flag));
		else
			return (phi->id - 1);
	}
	else if (flag == R_FORK)
	{
		pthread_mutex_lock(phi->env->struct_lock);
		if (phi->id == phi->env->nb_philo - 1)
			fork_id = rev_index(phi, flag);
		else
			fork_id = phi->id;
		pthread_mutex_unlock(phi->env->struct_lock);
	}
	return (fork_id);
}
