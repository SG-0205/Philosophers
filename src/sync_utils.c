/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:00:26 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/08/07 19:42:12 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_ready(t_philo *table)
{
	while (!get_value(table->locks[STRUCT], &table->flag_ready))
		;
	update_value(table->locks[MONITOR], &table->running, INCR);
}

void	ft_usleep(long usec, t_philo *table)
{
	long	start;
	long	end_t;
	long	current_t;

	start = get_time(US);
	while (get_time(US) - start < usec)
	{
		if (get_value(table->locks[STRUCT], &table->flag_stop))
			return ;
		current_t = get_time(US) - start;
		end_t = usec - current_t;
		if (end_t > 1000)
			usleep(end_t / 2);
		else
			while (get_time(US) - start < usec)
				;
	}
}
