/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:03:43 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/23 13:29:45 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	create_threads(t_philo *data)
{
	int	i;

	i = -1;
	while (++i < data->start_args->nb_philo)
	{
		pthread_create(data->philos[i]->thread,
			NULL, philo_routine, data->philos[i]);
	}
	i = -1;
	while (++i < data->start_args->nb_philo)
		pthread_join(*data->philos[i]->thread, NULL);
	return (0);
}
