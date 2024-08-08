/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:11:34 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/08/08 19:32:06 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_digit(char **argv, int argc)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (++i < argc)
	{
		while (argv[i][++j])
			if (ft_isdigit(argv[i][j]) == 0)
				return (1);
		j = -1;
	}
	return (0);
}

long	get_time(int ret_code)
{
	struct timeval	time_struct;

	time_struct.tv_sec = 0;
	time_struct.tv_usec = 0;
	if (gettimeofday(&time_struct, NULL))
		return (-1);
	if (ret_code == S)
		return (time_struct.tv_sec + (time_struct.tv_usec / 1e6));
	else if (ret_code == MS)
		return ((time_struct.tv_sec * 1e3) + (time_struct.tv_usec / 1e3));
	else if (ret_code == US)
		return ((time_struct.tv_sec * 1e6) + time_struct.tv_usec);
	else
		return (0);
}

static void	destroy_philo_data(t_philo *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philos)
	{
		free(table->philos[i]->fork_ids);
		free(table->philos[i]->thread);
		if (pthread_mutex_destroy(table->philos[i]->phi_mut))
			return ;
		free(table->philos[i]->phi_mut);
	}
}

static void	destroy_mutex_array(pthread_mutex_t **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		if (pthread_mutex_destroy(array[i]))
			return ;
}

void	free_all(t_philo *vals)
{
	if (vals->philos)
		(destroy_philo_data(vals),
			ft_arrfree((void **)vals->philos), free(vals->philos));
	if (vals->forks)
		(destroy_mutex_array(vals->forks), ft_arrfree((void **)vals->forks),
			free(vals->forks));
	if (vals->locks)
		(destroy_mutex_array(vals->locks), ft_arrfree((void **)vals->locks),
			free(vals->locks));
	free(vals->monitor);
	free(vals);
}
