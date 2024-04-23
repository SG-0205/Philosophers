/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_ld.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:22:27 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/23 11:27:26 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long int	get_time_ld(void)
{
	long int		f_time;
	struct timeval	b_time;

	f_time = 0;
	if (gettimeofday(&b_time, NULL) < 0)
		return (0);
	f_time = (b_time.tv_sec * 1000) + (b_time.tv_usec / 1000);
	return (f_time);
}
