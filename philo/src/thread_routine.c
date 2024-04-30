/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:21:53 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/30 13:21:53 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"



void	routine(void *phi)
{
	t_thinker	*phi_cast;

	phi_cast->lf_id = get_fork_id(phi, L_FORK);
	phi_cast->rf_id = get_fork_id(phi, R_FORK);
	while (phi_cast->state != DEAD)
	{
		phi_cast->start = get_time_ld();
		
	}
}