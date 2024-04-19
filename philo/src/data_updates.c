/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_updates.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:29:20 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/19 17:44:30 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	destroy_pthread_philos(t_thinker **list)
{
	int	listlen;

	if (!list || !*list)
		return (0);
	listlen = ft_arrlen((void **)list);
	while (--listlen > -1)
	{
		if (pthread_cancel(*list[listlen]->thread) != 0)
			return (error_message(errno, "destroy_philos"));
		if (pthread_join(*list[listlen]->thread, NULL) != 0)
			return (error_message(errno, "destroy_philos"));
	}
	return (0);
}

int	destroy_mutex_forks(t_fork **list)
{
	int	listlen;

	if (!list || !*list)
		return (0);
	listlen = ft_arrlen((void **)list);
	while (--listlen > -1)
	{
		if (pthread_mutex_destroy(list[listlen]->lock) != 0)
			return (error_message(errno, "destroy_forks"));
		free(list[listlen]->lock);
		list[listlen]->state = INACTIVE;
	}
	return (0);
}

t_bool	setup_fork(t_fork *fork)
{
	if (!fork)
		return (FALSE);
	fork->state = INACTIVE;
	fork->lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!fork->lock || pthread_mutex_init(fork->lock, NULL) != 0)
		return (FALSE);
	return (TRUE);
}

t_bool	setup_thinkers(t_thinker *philo, t_args *sval_addr)
{
	if (!philo)
		return (FALSE);
	philo->state = INACTIVE;
	philo->sval_link = sval_addr;
	philo->thread = (pthread_t *)malloc(sizeof(pthread_t));
	if (!philo->thread)
		return (FALSE);
	return (TRUE);
}

int	free_and_exit(t_philo *data, int exitcode)
{
	if (!data)
		return (errno);
	if (data->forks)
		(destroy_mutex_forks(data->forks),
			ft_arrfree((void **)data->forks), free(data->forks));
	if (data->philos)
		(destroy_pthread_philos(data->philos),
			ft_arrfree((void **)data->philos), free(data->philos));
	if (data->start_args)
	{
		if (data->start_args->tmeals_lock)
		{
			if (pthread_mutex_destroy(data->start_args->tmeals_lock) != 0)
				return (errno);
			free(data->start_args->tmeals_lock);
		}
		free(data->start_args);
	}
	free(data);
	return (exitcode);
}
