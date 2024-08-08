/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:47:06 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/08/07 20:52:23 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_state(t_thinker *phi, int phi_state)
{
	if (phi->ate == FULL)
		return ;
	mutex_operation(phi->table->locks[PRINT], LOCK);
	if (phi_state == EATING && !get_value(phi->table->locks[STRUCT],
			(int*)&phi->table->flag_stop))
		printf(GREEN "%ld %d is eating\n" RESET, (get_time(MS)
				- phi->table->start_time), phi->id + 1);
	else if ((phi_state == TAKE_FF || phi_state == TAKE_SF)
		&& !get_value(phi->table->locks[STRUCT], (int *)&phi->table->flag_stop))
		printf(BLUE "%ld %d has taken a fork\n" RESET, ((get_time(MS)
				- phi->table->start_time)), phi->id + 1);
	else if (phi_state == DEAD)
		printf(RED "%ld %d died\n" RESET, (get_time(MS)
				- phi->table->start_time), phi->id + 1);
	else if (phi_state == SLEEPING && !get_value(phi->table->locks[STRUCT],
			(int *)&phi->table->flag_stop))
		printf(YELLOW "%ld %d is sleeping\n" RESET, (get_time(MS)
				- phi->table->start_time), phi->id + 1);
	else if (phi_state == THINKING && !get_value(phi->table->locks[STRUCT],
			(int *)&phi->table->flag_stop))
		printf(CYAN "%ld %d is thinking\n" RESET, (get_time(MS)
				- phi->table->start_time), phi->id + 1);
	mutex_operation(phi->table->locks[PRINT], UNLOCK);
}
