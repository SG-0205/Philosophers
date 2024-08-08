/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:36:10 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/08/07 18:24:14 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	*get_fork_ids(t_philo *data, int phi_id)
{
	int	*fork_ids;

	fork_ids = (int *)malloc(sizeof(int) * 2);
	if (!fork_ids)
		return (NULL);
	if (phi_id % 2 == 0)
	{
		fork_ids[FIRST] = phi_id;
		fork_ids[LAST] = (phi_id + 1 % (data->nb_philos));
	}
	else
	{
		fork_ids[FIRST] = (phi_id + 1 % (data->nb_philos));
		fork_ids[LAST] = phi_id;
	}
	if (fork_ids[FIRST] >= data->nb_philos)
		fork_ids[FIRST] = 0;
	else if (fork_ids[LAST] >= data->nb_philos)
		fork_ids[LAST] = 0;
	return (fork_ids);
}

int	set_value(pthread_mutex_t *mutex, int *val_ptr, int to_set)
{
	int	state;

	state = mutex_operation(mutex, LOCK);
	*val_ptr = to_set;
	state = mutex_operation(mutex, UNLOCK);
	return (state);
}

long	set_value_l(pthread_mutex_t *mutex, long *val_ptr, long to_set)
{
	int	state;

	state = mutex_operation(mutex, LOCK);
	*val_ptr = to_set;
	state = mutex_operation(mutex, UNLOCK);
	return (state);
}

int	get_value(pthread_mutex_t *mutex, int *to_get)
{
	int	ret_val;

	ret_val = 0;
	mutex_operation(mutex, LOCK);
	ret_val = *to_get;
	mutex_operation(mutex, UNLOCK);
	return (ret_val);
}

long	get_value_l(pthread_mutex_t *mutex, long *to_get)
{
	long	ret_val;

	ret_val = 0;
	mutex_operation(mutex, LOCK);
	ret_val = *to_get;
	mutex_operation(mutex, UNLOCK);
	return (ret_val);
}

int	update_value(pthread_mutex_t *mutex, int *to_update, t_inc_dec code)
{
	int	state;

	state = mutex_operation(mutex, LOCK);
	if (code == INCR)
		*to_update += 1;
	else if (code == DECR)
		*to_update -= 1;
	state = mutex_operation(mutex, UNLOCK);
	return (state);
}
