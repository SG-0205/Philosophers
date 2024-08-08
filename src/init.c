/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:12:50 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/08/08 19:32:06 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static t_bool	arg_checks(int argc, char **argv)
{
	int	i;

	i = 0;
	if (check_digit(argv, argc) != 0)
		return (FALSE);
	while (++i < argc)
		if (ft_atoi(argv[i]) < 1 || ft_atoi(argv[i]) > __INT_MAX__)
			return (FALSE);
	return (TRUE);
}

static pthread_mutex_t	**init_mutexes(int nb_mutexes)
{
	pthread_mutex_t	**new;
	int				i;

	new = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * (nb_mutexes
				+ 1));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < nb_mutexes)
	{
		new[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!new[i] || pthread_mutex_init(new[i], NULL))
		{
			ft_arrfree((void **)new);
			free(new);
			return (NULL);
		}
	}
	new[nb_mutexes] = NULL;
	return (new);
}

static t_thinker	**init_philos(int nb_philos, t_philo *table)
{
	t_thinker	**new;
	int			i;

	new = (t_thinker **)malloc(sizeof(t_thinker *) * (nb_philos + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < nb_philos)
	{
		new[i] = (t_thinker *)malloc(sizeof(t_thinker));
		new[i]->thread = (pthread_t *)malloc(sizeof(pthread_t));
		if (!new[i] || !new[i]->thread)
		{
			ft_arrfree((void **)new);
			free(new);
			return (NULL);
		}
		new[i]->eat_count = 0;
		new[i]->id = i;
		new[i]->last_meal_t = 0;
		new[i]->table = table;
		new[i]->fork_ids = get_fork_ids(new[i]->table, new[i]->id);
	}
	new[nb_philos] = NULL;
	return (new);
}

static t_bool	alloc_arrays(t_philo *vals)
{
	if (!vals)
		return (FALSE);
	vals->forks = init_mutexes(vals->nb_philos);
	if (!vals->forks)
		return (FALSE);
	vals->locks = init_mutexes(NB_LOCKS);
	if (!vals->forks)
		return (FALSE);
	vals->philos = init_philos(vals->nb_philos, vals);
	if (!vals->philos)
		return (printf("ERRALLOC"));
	return (TRUE);
}

t_philo	*init_data(int argc, char **argv)
{
	t_philo	*vals;

	if (arg_checks(argc, argv) == FALSE)
		return (NULL);
	vals = (t_philo *)malloc(sizeof(t_philo));
	if (!vals)
		return (NULL);
	if (argc == 6)
		vals->nb_meals = ft_atoi(argv[5]);
	else
		vals->nb_meals = ENDLESS;
	vals->nb_philos = ft_atoi(argv[1]);
	vals->ttd = ft_atoi(argv[2]);
	vals->tte = ft_atoi(argv[3]);
	vals->tts = ft_atoi(argv[4]);
	vals->flag_stop = FALSE;
	vals->flag_ready = FALSE;
	vals->running = 0;
	vals->start_time = 0;
	if (alloc_arrays(vals) == FALSE || malloc_phi_mutexes(vals) == FALSE)
		return (NULL);
	return (vals);
}
