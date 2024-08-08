/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:26:22 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/08/05 15:26:21 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static t_bool	mutex_errors(int errcode, t_mutcodes mutcode)
{
	if (errcode == 0)
		return (0);
	if (errcode == EINVAL && (mutcode == LOCK || mutcode == UNLOCK))
		return (EINVAL);
	else if (errcode == EINVAL && (mutcode == INIT || mutcode == DESTROY))
		return (EINVAL);
	else if (errcode == EDEADLK)
		return (EDEADLK);
	else if (errcode == EPERM)
		return (EPERM);
	else if (errcode == ENOMEM)
		return (ENOMEM);
	else if (errcode == EBUSY)
		return (EBUSY);
	else
		return (-1);
}

int	mutex_operation(pthread_mutex_t *mutex, t_mutcodes code)
{
	if (code == LOCK)
		return (mutex_errors(pthread_mutex_lock(mutex), code));
	else if (code == UNLOCK)
		return (mutex_errors(pthread_mutex_unlock(mutex), code));
	else if (code == DESTROY)
		return (mutex_errors(pthread_mutex_destroy(mutex), code));
	else if (code == INIT)
		return (mutex_errors(pthread_mutex_init(mutex, NULL), code));
	else
		return (-1);
}

static t_bool	thread_errors(int errcode, t_mutcodes mutcode)
{
	if (errcode == 0)
		return (0);
	if (errcode == EINVAL && (mutcode == CREATE || mutcode == DETACH
			|| mutcode == JOIN))
		return (EINVAL);
	else if (errcode == ESRCH)
		return (ESRCH);
	else if (errcode == EAGAIN)
		return (EAGAIN);
	else if (errcode == EPERM)
		return (EPERM);
	else if (errcode == EDEADLK)
		return (EDEADLK);
	else
		return (-1);
}

int	thread_operation(pthread_t *thread, t_mutcodes code, void *(*var)(void *),
		void *data)
{
	if (code == CREATE)
		return (thread_errors(pthread_create(thread, NULL, var, data), code));
	else if (code == JOIN)
		return (thread_errors(pthread_join(*thread, NULL), code));
	else if (code == DETACH)
		return (thread_errors(pthread_detach(*thread), code));
	else
		return (-1);
}
