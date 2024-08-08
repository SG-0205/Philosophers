/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:36:10 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/08/08 19:22:57 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
