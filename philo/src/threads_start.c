/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:03:43 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/24 13:18:41 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	close_threads(t_philo *data, int already_closed)
{
	int	i;

	i = -1;
	while (++i < data->start_args->nb_philo)
		if (i != already_closed)
			return (pthread_cancel(*data->philos[i]->thread));
	return (0);
}

int	watchdog(t_philo *data)
{
	int	i;

	i = -1;
	while (++i < data->start_args->nb_philo)
	{
		if (pthread_join(*data->philos[i]->thread, NULL) == 0)
			return (close_threads(data, i));
	}
	return (-1);
}

int	create_threads(t_philo *data)
{
	int	i;

	i = -1;
	while (++i < data->start_args->nb_philo)
	{
		pthread_create(data->philos[i]->thread,
			NULL, philo_routine, data->philos[i]);
	}
	watchdog(data);
	return (0);
}
