/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:14:39 by sgoldenb          #+#    #+#             */
/*   Updated: 2024/08/08 15:07:25 by sgoldenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	usage_print(int errorcode)
{
	printf(RED BOLD "./philo [nb_philos] [ttd] [tte] [tts] (nb_meals)\n" RESET);
	return (errorcode);
}

void	start_simulation(t_philo *table)
{
	int	i;

	i = -1;
	if (table->nb_philos == 1)
		i = -1;
	while (++i < table->nb_philos)
	{
		thread_operation(table->philos[i]->thread, CREATE, philo_routine,
			(void *)table->philos[i]);
	}
	thread_operation(table->monitor, CREATE, monitor_thread, (void *)table);
	table->start_time = get_time(MS);
	set_value(table->forks[STRUCT], &table->flag_ready, TRUE);
	i = -1;
	while (++i < table->nb_philos)
		thread_operation(table->philos[i]->thread, JOIN, NULL, NULL);
	thread_operation(table->monitor, JOIN, NULL, NULL);
}

int	main(int argc, char **argv)
{
	t_philo	*vals;

	if (argc < 5 || argc > 6)
		return (usage_print(1));
	vals = init_data(argc, argv);
	if (!vals)
		return (usage_print(EINVAL));
	if (init_monitor(vals) == FALSE)
	{
		free_all(vals);
		return(ENOMEM);
	}
	start_simulation(vals);
	print_vals(vals);
	free_all(vals);
	return (0);
}
