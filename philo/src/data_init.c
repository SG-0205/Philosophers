/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:31:40 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/04/22 16:05:46 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_bool	check_args(char **args, int nb_args)
{
	size_t	intlen;
	size_t	arg_len;

	intlen = 0;
	while (--nb_args > 0)
	{
		arg_len = ft_strlen(args[nb_args]);
		ft_intlen(ft_atoi(args[nb_args]), &intlen);
		if (intlen != arg_len)
			return (FALSE);
		else
			while (arg_len-- > 0)
				if (ft_isdigit(args[nb_args][arg_len]) == 0)
					return (FALSE);
		intlen = 0;
		arg_len = 0;
	}
	return (TRUE);
}

t_args	*save_args(char **args, int nb_args)
{
	t_args	*var;

	var = (t_args *)malloc(sizeof(t_args));
	if (!var)
		return (NULL);
	var->nb_philo = ft_atoi(args[1]);
	var->ttd = ft_atoi(args[2]);
	var->tte = ft_atoi(args[3]);
	var->tts = ft_atoi(args[4]);
	if (nb_args == 6)
	{
		var->total_meals = ft_atoi(args[5]);
		var->tmeals_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!var->tmeals_lock || pthread_mutex_init(var->tmeals_lock,
				NULL) != 0)
			return (NULL);
	}
	else
		var->total_meals = ENDLESS;
	return (var);
}

t_fork	**forge_forks(t_philo *data)
{
	t_fork	**forks;
	int		nb_forks;
	int		i;

	nb_forks = data->start_args->nb_philo;
	forks = (t_fork **)malloc(sizeof(t_fork *) * (nb_forks + 1));
	if (!forks)
		return (NULL);
	forks[nb_forks] = NULL;
	i = -1;
	while (++i < nb_forks)
	{
		forks[i] = (t_fork *)malloc(sizeof(t_fork));
		if (!forks[i] || setup_fork(forks[i]) == FALSE)
		{
			destroy_mutex_forks(forks);
			(ft_arrfree((void **)forks), free(forks));
			return (NULL);
		}
	}
	ft_printf("FORKSOK\n");
	return (forks);
}

t_thinker	**create_philos(t_philo *data)
{
	t_thinker	**philos;
	int			nb_philos;
	int			i;

	nb_philos = data->start_args->nb_philo;
	philos = (t_thinker **)malloc(sizeof(t_thinker *)
		* (nb_philos + 1));
	if (!philos)
		return (NULL);
	philos[nb_philos] = NULL;
	i = -1;
	while (++i < nb_philos)
	{
		philos[i] = (t_thinker *)malloc(sizeof(t_thinker));
		if (!philos[i]
			|| setup_thinkers(philos[i], data->start_args) == FALSE)
		{
			(ft_arrfree((void **)philos), free(philos));
			return (NULL);
		}
		philos[i]->id = i;
	}
	return (philos);
}

t_philo	*init_data(char **args, int nb_args)
{
	t_philo	*data;

	data = (t_philo *)malloc(sizeof(t_philo));
	if (!data)
		return (NULL);
	data->start_args = save_args(args, nb_args);
	if (!data->start_args)
		return (NULL);
	data->philos = create_philos(data);
	if (!data->philos)
		return (NULL);
	data->forks = forge_forks(data);
	return (data);
}
