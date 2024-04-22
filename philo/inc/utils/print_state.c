/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:47:06 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/22 16:28:55 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_state(t_thinker *thinker, int flag)
{
	struct timeval	*time;

	time = (struct timeval *)malloc(sizeof(struct timeval));
	gettimeofday(time, NULL);
	if (flag == EATING)
		ft_printf("[%d:%d] : N°%d is eating\n", time->tv_sec, time->tv_usec, thinker->id);
	free(time);
}
