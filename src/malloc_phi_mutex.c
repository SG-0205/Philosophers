/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_phi_mutex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:27:25 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/08/08 19:23:58 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_bool	malloc_phi_mutexes(t_philo *table)
{
	int	i;

	if (!table || !table->philos)
		return (FALSE);
	i = -1;
	while (++i < table->nb_philos)
	{
		table->philos[i]->phi_mut
			= (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!table->philos[i]->phi_mut
			|| mutex_operation(table->philos[i]->phi_mut, INIT))
			return (FALSE);
	}
	return (TRUE);
}
